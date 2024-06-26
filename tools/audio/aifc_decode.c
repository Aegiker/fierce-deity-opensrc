/**
 * Bruteforcing decoder for converting ADPCM-encoded AIFC into AIFF, in a way
 * that roundtrips with vadpcm_enc.
 */
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef signed char s8;
typedef short s16;
typedef int s32;
typedef long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

#define bswap16(x) __builtin_bswap16(x)
#define bswap32(x) __builtin_bswap32(x)
#define BSWAP16(x) x = __builtin_bswap16(x)
#define BSWAP32(x) x = __builtin_bswap32(x)
#define BSWAP16_MANY(x, n) for (s32 _i = 0; _i < n; _i++) BSWAP16((x)[_i])

#define NORETURN __attribute__((noreturn))
#define UNUSED __attribute__((unused))

typedef struct {
    u32 ckID;
    u32 ckSize;
} ChunkHeader;

typedef struct {
    u32 ckID;
    u32 ckSize;
    u32 formType;
} Chunk;

typedef struct {
    s16 numChannels;
    u16 numFramesH;
    u16 numFramesL;
    s16 sampleSize;
    s16 sampleRate[5]; // 80-bit float
    u16 compressionTypeH;
    u16 compressionTypeL;
} CommonChunk;

typedef struct {
    s16 MarkerID;
    u16 positionH;
    u16 positionL;
} Marker;

typedef struct {
    s16 playMode;
    s16 beginLoop;
    s16 endLoop;
} Loop;

typedef struct {
    s8 baseNote;
    s8 detune;
    s8 lowNote;
    s8 highNote;
    s8 lowVelocity;
    s8 highVelocity;
    s16 gain;
    Loop sustainLoop;
    Loop releaseLoop;
} InstrumentChunk;

typedef struct {
    s32 offset;
    s32 blockSize;
} SoundDataChunk;

typedef struct {
    s16 version;
    s16 order;
    s16 nEntries;
} CodeChunk;

typedef struct {
    u32 start;
    u32 end;
    u32 count;
    s16 state[16];
} ALADPCMloop;


static char usage[] = "input.aifc output.aiff";
static const char *progname, *infilename;
static int framesize = 9;

#define checked_fread(a, b, c, d) if (fread(a, b, c, d) != c) fail_parse("error parsing file")

NORETURN
void fail_parse(const char *fmt, ...)
{
    char *formatted = NULL;
    va_list ap;
    va_start(ap, fmt);
    int size = vsnprintf(NULL, 0, fmt, ap);
    va_end(ap);
    if (size >= 0) {
        size++;
        formatted = malloc(size);
        if (formatted != NULL) {
            va_start(ap, fmt);
            size = vsnprintf(formatted, size, fmt, ap);
            va_end(ap);
            if (size < 0) {
                free(formatted);
                formatted = NULL;
            }
        }
    }

    if (formatted != NULL) {
        fprintf(stderr, "%s: %s [%s]\n", progname, formatted, infilename);
        free(formatted);
    }
    exit(1);
}

s32 myrand()
{
    static u64 state = 1619236481962341ULL;
    state *= 3123692312237ULL;
    state += 1;
    return state >> 33;
}

s16 qsample(f32 x, s32 scale)
{
    if (x > 0.0f) {
        return (s16) ((x / scale) + 0.4999999);
    } else {
        return (s16) ((x / scale) - 0.4999999);
    }
}

void clamp_to_s16(f32 *in, s32 *out)
{
    f32 llevel = -0x8000;
    f32 ulevel = 0x7fff;

    for (s32 i = 0; i < 16; i++) {
        if (in[i] > ulevel) in[i] = ulevel;
        if (in[i] < llevel) in[i] = llevel;

        if (in[i] > 0.0f) {
            out[i] = (s32) (in[i] + 0.5);
        } else {
            out[i] = (s32) (in[i] - 0.5);
        }
    }
}

s16 clamp_bits(s32 x, s32 bits)
{
    s32 lim = 1 << (bits - 1);
    if (x < -lim) return -lim;
    if (x > lim - 1) return lim - 1;
    return x;
}

s32 readaifccodebook(FILE *fhandle, s32 ****table, s16 *order, s16 *npredictors)
{
    checked_fread(order, sizeof(s16), 1, fhandle);
    BSWAP16(*order);
    checked_fread(npredictors, sizeof(s16), 1, fhandle);
    BSWAP16(*npredictors);
    *table = malloc(*npredictors * sizeof(s32 **));
    for (s32 i = 0; i < *npredictors; i++) {
        (*table)[i] = malloc(8 * sizeof(s32 *));
        for (s32 j = 0; j < 8; j++) {
            (*table)[i][j] = malloc((*order + 8) * sizeof(s32));
        }
    }

    for (s32 i = 0; i < *npredictors; i++) {
        s32 **table_entry = (*table)[i];
        for (s32 j = 0; j < *order; j++) {
            for (s32 k = 0; k < 8; k++) {
                s16 ts;
                checked_fread(&ts, sizeof(s16), 1, fhandle);
                BSWAP16(ts);
                table_entry[k][j] = ts;
            }
        }

        for (s32 k = 1; k < 8; k++) {
            table_entry[k][*order] = table_entry[k - 1][*order - 1];
        }

        table_entry[0][*order] = 1 << 11;

        for (s32 k = 1; k < 8; k++) {
            s32 j = 0;
            for (; j < k; j++) {
                table_entry[j][k + *order] = 0;
            }

            for (; j < 8; j++) {
                table_entry[j][k + *order] = table_entry[j - k][*order];
            }
        }
    }
    return 0;
}

ALADPCMloop *readlooppoints(FILE *ifile, s16 *nloops)
{
    checked_fread(nloops, sizeof(s16), 1, ifile);
    BSWAP16(*nloops);
    ALADPCMloop *al = malloc(*nloops * sizeof(ALADPCMloop));
    for (s32 i = 0; i < *nloops; i++) {
        checked_fread(&al[i], sizeof(ALADPCMloop), 1, ifile);
        BSWAP32(al[i].start);
        BSWAP32(al[i].end);
        BSWAP32(al[i].count);
        BSWAP16_MANY(al[i].state, 16);
    }
    return al;
}

s32 inner_product(s32 length, s32 *v1, s32 *v2)
{
    s32 out = 0;
    for (s32 i = 0; i < length; i++) {
        out += v1[i] * v2[i];
    }

    // Compute "out / 2^11", rounded down.
    s32 dout = out / (1 << 11);
    s32 fiout = dout * (1 << 11);
    return dout - (out - fiout < 0);
}

void my_decodeframe(u8 *frame, s32 *decompressed, s32 *state, s32 order, s32 ***coefTable)
{
    s32 ix[16];

    u8 header = frame[0];
    s32 scale = 1 << (header >> 4);
    s32 optimalp = header & 0xf;

    if (framesize == 5) {
        for (s32 i = 0; i < 16; i += 4) {
            u8 c = frame[1 + i/4];
            ix[i] = c >> 6;
            ix[i + 1] = (c >> 4) & 0x3;
            ix[i + 2] = (c >> 2) & 0x3;
            ix[i + 3] = c & 0x3;
        }
    } else {
        for (s32 i = 0; i < 16; i += 2) {
            u8 c = frame[1 + i/2];
            ix[i] = c >> 4;
            ix[i + 1] = c & 0xf;
        }
    }

    for (s32 i = 0; i < 16; i++) {
        if (framesize == 5) {
            if (ix[i] >= 2) ix[i] -= 4;
        } else {
            if (ix[i] >= 8) ix[i] -= 16;
        }
        decompressed[i] = ix[i];
        ix[i] *= scale;
    }

    for (s32 j = 0; j < 2; j++) {
        s32 in_vec[16];
        if (j == 0) {
            for (s32 i = 0; i < order; i++) {
                in_vec[i] = state[16 - order + i];
            }
        } else {
            for (s32 i = 0; i < order; i++) {
                in_vec[i] = state[8 - order + i];
            }
        }

        for (s32 i = 0; i < 8; i++) {
            s32 ind = j * 8 + i;
            in_vec[order + i] = ix[ind];
            state[ind] = inner_product(order + i, coefTable[optimalp][i], in_vec) + ix[ind];
        }
    }
}

void my_encodeframe(u8 *out, s16 *inBuffer, s32 *origState, s32 ***coefTable, s32 order, s32 npredictors)
{
    s16 ix[16];
    s32 prediction[16];
    s32 inVector[16];
    s32 optimalp = 0;
    s32 scale;
    s32 encBits = (framesize == 5 ? 2 : 4);
    s32 llevel = -(1 << (encBits - 1));
    s32 ulevel = -llevel - 1;
    s32 ie[16];
    f32 e[16];
    f32 min = 1e30;
    s32 scaleFactor = 16 - encBits;

    for (s32 k = 0; k < npredictors; k++) {
        for (s32 j = 0; j < 2; j++) {
            for (s32 i = 0; i < order; i++) {
                inVector[i] = (j == 0 ? origState[16 - order + i] : inBuffer[8 - order + i]);
            }

            for (s32 i = 0; i < 8; i++) {
                prediction[j * 8 + i] = inner_product(order + i, coefTable[k][i], inVector);
                inVector[i + order] = inBuffer[j * 8 + i] - prediction[j * 8 + i];
                e[j * 8 + i] = (f32) inVector[i + order];
            }
        }

        f32 se = 0.0f;
        for (s32 j = 0; j < 16; j++) {
            se += e[j] * e[j];
        }

        if (se < min) {
            min = se;
            optimalp = k;
        }
    }

    for (s32 j = 0; j < 2; j++) {
        for (s32 i = 0; i < order; i++) {
            inVector[i] = (j == 0 ? origState[16 - order + i] : inBuffer[8 - order + i]);
        }

        for (s32 i = 0; i < 8; i++) {
            prediction[j * 8 + i] = inner_product(order + i, coefTable[optimalp][i], inVector);
            e[j * 8 + i] = inVector[i + order] = inBuffer[j * 8 + i] - prediction[j * 8 + i];
        }
    }

    clamp_to_s16(e, ie);

    s32 max = 0;
    for (s32 i = 0; i < 16; i++) {
        if (abs(ie[i]) > abs(max)) {
            max = ie[i];
        }
    }

    for (scale = 0; scale <= scaleFactor; scale++) {
        if (max <= ulevel && max >= llevel) break;
        max /= 2;
    }

    s32 state[16];
    for (s32 i = 0; i < 16; i++) {
        state[i] = origState[i];
    }

    s32 nIter, again;
    for (nIter = 0, again = 1; nIter < 2 && again; nIter++) {
        again = 0;
        if (nIter == 1) scale++;
        if (scale > scaleFactor) {
            scale = scaleFactor;
        }

        for (s32 j = 0; j < 2; j++) {
            s32 base = j * 8;
            for (s32 i = 0; i < order; i++) {
                inVector[i] = (j == 0 ?
                        origState[16 - order + i] : state[8 - order + i]);
            }

            for (s32 i = 0; i < 8; i++) {
                prediction[base + i] = inner_product(order + i, coefTable[optimalp][i], inVector);
                f32 se = (f32) inBuffer[base + i] - (f32) prediction[base + i];
                ix[base + i] = qsample(se, 1 << scale);
                s32 cV = clamp_bits(ix[base + i], encBits) - ix[base + i];
                if (cV > 1 || cV < -1) again = 1;
                ix[base + i] += cV;
                inVector[i + order] = ix[base + i] * (1 << scale);
                state[base + i] = prediction[base + i] + inVector[i + order];
            }
        }
    }

    u8 header = (scale << 4) | (optimalp & 0xf);
    out[0] = header;
    if (framesize == 5) {
        for (s32 i = 0; i < 16; i += 4) {
            u8 c = ((ix[i] & 0x3) << 6) | ((ix[i + 1] & 0x3) << 4) | ((ix[i + 2] & 0x3) << 2) | (ix[i + 3] & 0x3);
            out[1 + i/4] = c;
        }
    } else {
        for (s32 i = 0; i < 16; i += 2) {
            u8 c = ((ix[i] & 0xf) << 4) | (ix[i + 1] & 0xf);
            out[1 + i/2] = c;
        }
    }
}

void permute(s32 *out, s32 *in, s32 *decompressed, s32 scale)
{
    int normal = myrand() % 3 == 0;
    for (s32 i = 0; i < 16; i++) {
        s32 lo = in[i] - scale / 2;
        s32 hi = in[i] + scale / 2;
        if (framesize == 9) {
            if (decompressed[i] == -8 && myrand() % 10 == 0) lo -= scale * 3/2;
            else if (decompressed[i] == 7 && myrand() % 10 == 0) hi += scale * 3/2;
        }
        else if (decompressed[i] == -2 && myrand() % 7 == 0) lo -= scale * 3/2;
        else if (decompressed[i] == 1 && myrand() % 10 == 0) hi += scale * 3/2;
        else if (normal) {}
        else if (decompressed[i] == 0) {
            if (myrand() % 3) {
                lo = in[i] - scale / 5;
                hi = in[i] + scale / 5;
            }
            else if (myrand() % 2) {
                lo = in[i] - scale / 3;
                hi = in[i] + scale / 3;
            }
        }
        else if (myrand() % 3) {
            if (decompressed[i] < 0) lo = in[i] + scale / 4;
            if (decompressed[i] > 0) hi = in[i] - scale / 4;
        }
        else if (myrand() % 2) {
            if (decompressed[i] < 0) lo = in[i] - scale / 4;
            if (decompressed[i] > 0) hi = in[i] + scale / 4;
        }
        out[i] = clamp_bits(lo + myrand() % (hi - lo + 1), 16);
    }
}

void get_bounds(s32 *in, s32 *decompressed, s32 scale, s32 *minVals, s32 *maxVals)
{
    s32 minv, maxv;
    if (framesize == 9) {
        minv = -8;
        maxv = 7;
    } else {
        minv = -2;
        maxv = 1;
    }
    for (s32 i = 0; i < 16; i++) {
        s32 lo = in[i] - scale / 2;
        s32 hi = in[i] + scale / 2;
        lo -= scale;
        hi += scale;
        if (decompressed[i] == minv) lo -= scale;
        else if (decompressed[i] == maxv) hi += scale;
        minVals[i] = lo;
        maxVals[i] = hi;
    }
}

s64 scored_encode(s32 *inBuffer, s32 *origState, s32 ***coefTable, s32 order, s32 npredictors, s32 wantedPredictor, s32 wantedScale, s32 wantedIx[16])
{
    s32 prediction[16];
    s32 inVector[16];
    s32 optimalp = 0;
    s32 scale;
    s32 encBits = (framesize == 5 ? 2 : 4);
    s32 llevel = -(1 << (encBits - 1));
    s32 ulevel = -llevel - 1;
    s32 ie[16];
    f32 e[16];
    f32 min = 1e30;
    s32 scaleFactor = 16 - encBits;
    f32 errs[4];
    s64 scoreA = 0, scoreB = 0, scoreC = 0;

    for (s32 k = 0; k < npredictors; k++) {
        for (s32 j = 0; j < 2; j++) {
            for (s32 i = 0; i < order; i++) {
                inVector[i] = (j == 0 ? origState[16 - order + i] : inBuffer[8 - order + i]);
            }

            for (s32 i = 0; i < 8; i++) {
                prediction[j * 8 + i] = inner_product(order + i, coefTable[k][i], inVector);
                inVector[i + order] = inBuffer[j * 8 + i] - prediction[j * 8 + i];
                e[j * 8 + i] = (f32) inVector[i + order];
            }
        }

        f32 se = 0.0f;
        for (s32 j = 0; j < 16; j++) {
            se += e[j] * e[j];
        }

        errs[k] = se;

        if (se < min) {
            min = se;
            optimalp = k;
        }
    }

    for (s32 k = 0; k < npredictors; k++) {
        if (errs[k] < errs[wantedPredictor]) {
            scoreA += (s64)(errs[wantedPredictor] - errs[k]);
        }
    }
    if (optimalp != wantedPredictor) {
        // probably penalized above, but add extra penalty in case the error
        // values were the exact same
        scoreA += 1;
    }
    optimalp = wantedPredictor;

    for (s32 j = 0; j < 2; j++) {
        for (s32 i = 0; i < order; i++) {
            inVector[i] = (j == 0 ? origState[16 - order + i] : inBuffer[8 - order + i]);
        }

        for (s32 i = 0; i < 8; i++) {
            prediction[j * 8 + i] = inner_product(order + i, coefTable[optimalp][i], inVector);
            e[j * 8 + i] = inVector[i + order] = inBuffer[j * 8 + i] - prediction[j * 8 + i];
        }
    }

    clamp_to_s16(e, ie);

    s32 max = 0;
    for (s32 i = 0; i < 16; i++) {
        if (abs(ie[i]) > abs(max)) {
            max = ie[i];
        }
    }

    for (scale = 0; scale <= scaleFactor; scale++) {
        if (max <= ulevel && max >= llevel) break;
        max /= 2;
    }

    // Preliminary ix computation, computes whether scale needs to be incremented
    s32 state[16];
    s32 again = 0;
    for (s32 j = 0; j < 2; j++) {
        s32 base = j * 8;
        for (s32 i = 0; i < order; i++) {
            inVector[i] = (j == 0 ?
                    origState[16 - order + i] : state[8 - order + i]);
        }

        for (s32 i = 0; i < 8; i++) {
            prediction[base + i] = inner_product(order + i, coefTable[optimalp][i], inVector);
            f32 se = (f32) inBuffer[base + i] - (f32) prediction[base + i];
            s32 ix = qsample(se, 1 << scale);
            s32 clampedIx = clamp_bits(ix, encBits);
            s32 cV = clampedIx - ix;
            if (cV > 1 || cV < -1) {
                again = 1;
            }
            inVector[i + order] = clampedIx * (1 << scale);
            state[base + i] = prediction[base + i] + inVector[i + order];
        }
    }

    if (again && scale < scaleFactor) {
        scale++;
    }

    if (scale != wantedScale) {
        // We could do math to penalize scale mismatches accurately, but it's
        // simpler to leave it as a constraint by setting an infinite penalty.
        scoreB += 100000000;
        scale = wantedScale;
    }

    // Then again for real, but now also with penalty computation
    for (s32 j = 0; j < 2; j++) {
        s32 base = j * 8;
        for (s32 i = 0; i < order; i++) {
            inVector[i] = (j == 0 ?
                    origState[16 - order + i] : state[8 - order + i]);
        }

        for (s32 i = 0; i < 8; i++) {
            prediction[base + i] = inner_product(order + i, coefTable[optimalp][i], inVector);
            s64 ise = (s64) inBuffer[base + i] - (s64) prediction[base + i];
            f32 se = (f32) inBuffer[base + i] - (f32) prediction[base + i];
            s32 ix = qsample(se, 1 << scale);
            s32 clampedIx = clamp_bits(ix, encBits);
            s32 val = wantedIx[base + i] * (1 << scale);
            if (clampedIx != wantedIx[base + i]) {
                assert(ix != wantedIx[base + i]);
                s32 lo = val - (1 << scale) / 2;
                s32 hi = val + (1 << scale) / 2;
                s64 diff = 0;
                if (ise < lo) diff = lo - ise;
                else if (ise > hi) diff = ise - hi;
                scoreC += diff * diff + 1;
            }
            inVector[i + order] = val;
            state[base + i] = prediction[base + i] + val;
        }
    }

    // Penalties for going outside s16
    for (s32 i = 0; i < 16; i++) {
        s64 diff = 0;
        if (inBuffer[i] < -0x8000) diff = -0x8000 - inBuffer[i];
        if (inBuffer[i] > 0x7fff) diff = inBuffer[i] - 0x7fff;
        scoreC += diff * diff;
    }

    return scoreA + scoreB + 10 * scoreC;
}

s32 descent(s32 guess[16], s32 minVals[16], s32 maxVals[16], u8 input[9], s32 lastState[16], s32 ***coefTable, s32 order, s32 npredictors, s32 wantedPredictor, s32 wantedScale, s32 wantedIx[32])
{
    (void) input;

    const f64 inf = 1e100;
    s64 curScore = scored_encode(guess, lastState, coefTable, order, npredictors, wantedPredictor, wantedScale, wantedIx);
    for (;;) {
        f64 delta[16];
        if (curScore == 0) {
            return 1;
        }

        // Compute gradient, and how far to move along it at most.
        f64 maxMove = inf;
        for (s32 i = 0; i < 16; i++) {
            guess[i] += 1;
            s64 scoreUp = scored_encode(guess, lastState, coefTable, order, npredictors, wantedPredictor, wantedScale, wantedIx);
            guess[i] -= 2;
            s64 scoreDown = scored_encode(guess, lastState, coefTable, order, npredictors, wantedPredictor, wantedScale, wantedIx);
            guess[i] += 1;
            if (scoreUp >= curScore && scoreDown >= curScore) {
                // Don't touch this coordinate
                delta[i] = 0;
            } else if (scoreDown < scoreUp) {
                if (guess[i] == minVals[i]) {
                    // Don't allow moving out of bounds
                    delta[i] = 0;
                } else {
                    delta[i] = -(f64)(curScore - scoreDown);
                    maxMove = fmin(maxMove, (minVals[i] - guess[i]) / delta[i]);
                }
            } else {
                if (guess[i] == maxVals[i]) {
                    delta[i] = 0;
                } else {
                    delta[i] = (f64)(curScore - scoreUp);
                    maxMove = fmin(maxMove, (maxVals[i] - guess[i]) / delta[i]);
                }
            }
        }
        if (maxMove == inf || maxMove <= 0) {
            return 0;
        }

        // Try exponentially spaced candidates along the gradient.
        s32 nguess[16];
        s32 bestGuess[16];
        s64 bestScore = curScore;
        for (;;) {
            s32 changed = 0;
            for (s32 i = 0; i < 16; i++) {
                nguess[i] = (s32)round(guess[i] + delta[i] * maxMove);
                if (nguess[i] != guess[i]) changed = 1;
            }
            if (!changed) break;
            s64 score = scored_encode(nguess, lastState, coefTable, order, npredictors, wantedPredictor, wantedScale, wantedIx);
            if (score < bestScore) {
                bestScore = score;
                memcpy(bestGuess, nguess, sizeof(nguess));
            }
            maxMove *= 0.7;
        }

        if (bestScore == curScore) {
            // No improvements along that line, give up.
            return 0;
        }
        curScore = bestScore;
        memcpy(guess, bestGuess, sizeof(bestGuess));
    }
}

s32 bruteforce(s32 guess[16], u8 input[9], s32 decoded[16], s32 decompressed[16], s32 lastState[16], s32 ***coefTable, s32 order, s32 npredictors)
{
    s32 scale = input[0] >> 4, predictor = input[0] & 0xF;

    s32 minVals[16], maxVals[16];
    get_bounds(decoded, decompressed, 1 << scale, minVals, maxVals);

    for (;;) {
        s64 bestScore = -1;
        s32 bestGuess[16];
        for (s32 it = 0; it < 100; it++) {
            permute(guess, decoded, decompressed, 1 << scale);
            s64 score = scored_encode(guess, lastState, coefTable, order, npredictors, predictor, scale, decompressed);
            if (score == 0) {
                return 1;
            }
            if (bestScore == -1 || score < bestScore) {
                bestScore = score;
                memcpy(bestGuess, guess, sizeof(bestGuess));
            }
        }
        memcpy(guess, bestGuess, sizeof(bestGuess));
        if (descent(guess, minVals, maxVals, input, lastState, coefTable, order, npredictors, predictor, scale, decompressed)) {
            return 1;
        }
    }
}

void write_header(FILE *ofile, const char *id, s32 size)
{
    fwrite(id, 4, 1, ofile);
    BSWAP32(size);
    fwrite(&size, sizeof(s32), 1, ofile);
}

int main(int argc, char **argv)
{
    s16 order = -1;
    s16 nloops = 0;
    ALADPCMloop *aloops = NULL;
    s16 npredictors = -1;
    s32 ***coefTable = NULL;
    s32 state[16];
    s32 decompressed[16];
    s32 soundPointer = -1;
    s32 currPos = 0;
    s32 nSamples = 0;
    Chunk FormChunk;
    ChunkHeader Header;
    CommonChunk CommChunk;
    InstrumentChunk InstChunk;
    SoundDataChunk SndDChunk;
    FILE *ifile;
    FILE *ofile;
    progname = argv[0];

    if (argc < 3) {
        fprintf(stderr, "%s %s\n", progname, usage);
        exit(1);
    }

    infilename = argv[1];

    if ((ifile = fopen(infilename, "rb")) == NULL) {
        fail_parse("AIFF-C file could not be opened");
        exit(1);
    }

    if ((ofile = fopen(argv[2], "wb")) == NULL) {
        fprintf(stderr, "%s: output file could not be opened [%s]\n", progname, argv[2]);
        exit(1);
    }

    memset(&InstChunk, 0, sizeof(InstChunk));

    checked_fread(&FormChunk, sizeof(FormChunk), 1, ifile);
    BSWAP32(FormChunk.ckID);
    BSWAP32(FormChunk.formType);
    if ((FormChunk.ckID != 0x464f524d) || (FormChunk.formType != 0x41494643)) { // FORM, AIFC
        fail_parse("not an AIFF-C file");
    }

    for (;;) {
        s32 num = fread(&Header, sizeof(Header), 1, ifile);
        u32 ts;
        if (num <= 0) break;
        BSWAP32(Header.ckID);
        BSWAP32(Header.ckSize);

        Header.ckSize++;
        Header.ckSize &= ~1;
        s32 offset = ftell(ifile);

        switch (Header.ckID) {
        case 0x434f4d4d: // COMM
            checked_fread(&CommChunk, sizeof(CommChunk), 1, ifile);
            BSWAP16(CommChunk.numChannels);
            BSWAP16(CommChunk.numFramesH);
            BSWAP16(CommChunk.numFramesL);
            BSWAP16(CommChunk.sampleSize);
            BSWAP16(CommChunk.compressionTypeH);
            BSWAP16(CommChunk.compressionTypeL);
            s32 cType = (CommChunk.compressionTypeH << 16) + CommChunk.compressionTypeL;
            if (cType == 0x56415043 || cType == 0x41445039) { // VAPC or ADP9
                framesize = 9;
            } else if (cType == 0x41445035) { // ADP5
                framesize = 5;
            } else if (cType == 0x4850434d) { // HPCM
                framesize = 16;
            } else {
                char comprType[5] = {
                    CommChunk.compressionTypeH >> 8,
                    CommChunk.compressionTypeH & 0xFF,
                    CommChunk.compressionTypeL >> 8,
                    CommChunk.compressionTypeL & 0xFF,
                    0
                };
                fail_parse("file is of the wrong compression type [got %s (%08x)]", &comprType, cType);
            }
            if (CommChunk.numChannels != 1) {
                fail_parse("file contains %d channels, only 1 channel supported", CommChunk.numChannels);
            }
            if (CommChunk.sampleSize != 16) {
                fail_parse("file contains %d bit samples, only 16 bit samples supported", CommChunk.sampleSize);
            }

            nSamples = (CommChunk.numFramesH << 16) + CommChunk.numFramesL;

            // Allow broken input lengths
            if (nSamples % 16) {
                nSamples -= (nSamples % 16);
            }

            if (nSamples % 16 != 0) {
                fail_parse("number of chunks must be a multiple of 16, found %d with remainder %d", nSamples, nSamples % 16);
            }
            break;

        case 0x53534e44: // SSND
            checked_fread(&SndDChunk, sizeof(SndDChunk), 1, ifile);
            BSWAP32(SndDChunk.offset);
            BSWAP32(SndDChunk.blockSize);
            assert(SndDChunk.offset == 0);
            assert(SndDChunk.blockSize == 0);
            soundPointer = ftell(ifile);
            break;

        case 0x4150504c: // APPL
            checked_fread(&ts, sizeof(u32), 1, ifile);
            BSWAP32(ts);
            if (ts == 0x73746f63) { // stoc
                u8 len;
                checked_fread(&len, 1, 1, ifile);
                if (len == 11) {
                    char ChunkName[12];
                    s16 version;
                    checked_fread(ChunkName, 11, 1, ifile);
                    ChunkName[11] = '\0';
                    if (strcmp("VADPCMCODES", ChunkName) == 0) {
                        checked_fread(&version, sizeof(s16), 1, ifile);
                        BSWAP16(version);
                        if (version != 1) {
                            fail_parse("Unknown codebook chunk version");
                        }
                        readaifccodebook(ifile, &coefTable, &order, &npredictors);
                    }
                    else if (strcmp("VADPCMLOOPS", ChunkName) == 0) {
                        checked_fread(&version, sizeof(s16), 1, ifile);
                        BSWAP16(version);
                        if (version != 1) {
                            fail_parse("Unknown loop chunk version");
                        }
                        aloops = readlooppoints(ifile, &nloops);
                        if (nloops != 1) {
                            fail_parse("Only a single loop supported");
                        }
                    }
                }
            }
            break;
        }

        fseek(ifile, offset + Header.ckSize, SEEK_SET);
    }

    if (coefTable == NULL) {
        fail_parse("Codebook missing from bitstream");
    }

    for (s32 i = 0; i < order; i++) {
        state[15 - i] = 0;
    }

    u32 outputBytes = nSamples * sizeof(s16);
    u8 *outputBuf = malloc(outputBytes);

    fseek(ifile, soundPointer, SEEK_SET);
    s32 fails = 0;
    while (currPos < nSamples) {
        u8 input[9];
        u8 encoded[9];
        s32 lastState[16];
        s32 decoded[16];
        s16 guess[16];
        s16 origGuess[16];

        memcpy(lastState, state, sizeof(state));
        checked_fread(input, framesize, 1, ifile);

        // Decode for real
        my_decodeframe(input, decompressed, state, order, coefTable);
        memcpy(decoded, state, sizeof(state));

        // Create a guess from that, by clamping to 16 bits
        for (s32 i = 0; i < 16; i++) {
            origGuess[i] = clamp_bits(state[i], 16);
        }

        // Encode the guess
        memcpy(guess, origGuess, sizeof(guess));
        my_encodeframe(encoded, guess, lastState, coefTable, order, npredictors);

        // If it doesn't match, bruteforce the matching.
        if (memcmp(input, encoded, framesize) != 0) {
            s32 guess32[16];
            if (bruteforce(guess32, input, decoded, decompressed, lastState, coefTable, order, npredictors)) {
                for (int i = 0; i < 16; i++) {
                    assert(-0x8000 <= guess32[i] && guess32[i] <= 0x7fff);
                    guess[i] = guess32[i];
                }
                my_encodeframe(encoded, guess, lastState, coefTable, order, npredictors);
                assert(memcmp(input, encoded, framesize) == 0);
            } else {
                fails++;
                fprintf(stderr, "FAIL [%d/%d]\n", currPos, nSamples);
            }

            // Bring the matching closer to the original decode (not strictly
            // necessary, but it will move us closer to the target on average).
            for (s32 failures = 0; failures < 50; failures++) {
                s32 ind = myrand() % 16;
                s32 old = guess[ind];
                if (old == origGuess[ind]) continue;
                guess[ind] = origGuess[ind];
                if (myrand() % 2) guess[ind] += (old - origGuess[ind]) / 2;
                my_encodeframe(encoded, guess, lastState, coefTable, order, npredictors);
                if (memcmp(input, encoded, framesize) == 0) {
                    failures = -1;
                }
                else {
                    guess[ind] = old;
                }
            }
        }

        memcpy(state, decoded, sizeof(state));
        BSWAP16_MANY(guess, 16);
        memcpy(outputBuf + currPos * 2, guess, sizeof(guess));
        currPos += 16;
    }
    if (fails) {
        fprintf(stderr, "%s %d\n", infilename, fails);
    }

    // Write an incomplete file header. We'll fill in the size later.
    fwrite("FORM\0\0\0\0AIFF", 12, 1, ofile);

    // Subtract 4 from the COMM size to skip the compression field.
    write_header(ofile, "COMM", sizeof(CommonChunk) - 4);
    CommChunk.numFramesH = nSamples >> 16;
    CommChunk.numFramesL = nSamples & 0xffff;
    BSWAP16(CommChunk.numChannels);
    BSWAP16(CommChunk.numFramesH);
    BSWAP16(CommChunk.numFramesL);
    BSWAP16(CommChunk.sampleSize);
    fwrite(&CommChunk, sizeof(CommonChunk) - 4, 1, ofile);

    if (nloops > 0) {
        s32 startPos = aloops[0].start, endPos = aloops[0].end;
        const char *markerNames[2] = {"start", "end"};
        Marker markers[2] = {
            {1, startPos >> 16, startPos & 0xffff},
            {2, endPos >> 16, endPos & 0xffff}
        };
        write_header(ofile, "MARK", 2 + 2 * sizeof(Marker) + 1 + 5 + 1 + 3);
        s16 numMarkers = bswap16(2);
        fwrite(&numMarkers, sizeof(s16), 1, ofile);
        for (s32 i = 0; i < 2; i++) {
            u8 len = (u8) strlen(markerNames[i]);
            BSWAP16(markers[i].MarkerID);
            BSWAP16(markers[i].positionH);
            BSWAP16(markers[i].positionL);
            fwrite(&markers[i], sizeof(Marker), 1, ofile);
            fwrite(&len, 1, 1, ofile);
            fwrite(markerNames[i], len, 1, ofile);
        }

        write_header(ofile, "INST", sizeof(InstrumentChunk));
        InstChunk.sustainLoop.playMode = bswap16(1);
        InstChunk.sustainLoop.beginLoop = bswap16(1);
        InstChunk.sustainLoop.endLoop = bswap16(2);
        InstChunk.releaseLoop.playMode = 0;
        InstChunk.releaseLoop.beginLoop = 0;
        InstChunk.releaseLoop.endLoop = 0;
        fwrite(&InstChunk, sizeof(InstrumentChunk), 1, ofile);
    }

    // Save the coefficient table for use when encoding. Ideally this wouldn't
    // be needed and "tabledesign -s 1" would generate the right table, but in
    // practice it's difficult to adjust samples to make that happen.
    write_header(ofile, "APPL", 4 + 12 + sizeof(CodeChunk) + npredictors * order * 8 * 2);
    fwrite("stoc", 4, 1, ofile);
    CodeChunk cChunk;
    cChunk.version = bswap16(1);
    cChunk.order = bswap16(order);
    cChunk.nEntries = bswap16(npredictors);
    fwrite("\x0bVADPCMCODES", 12, 1, ofile);
    fwrite(&cChunk, sizeof(CodeChunk), 1, ofile);
    for (s32 i = 0; i < npredictors; i++) {
        for (s32 j = 0; j < order; j++) {
            for (s32 k = 0; k < 8; k++) {
                s16 ts = bswap16(coefTable[i][k][j]);
                fwrite(&ts, sizeof(s16), 1, ofile);
            }
        }
    }

    write_header(ofile, "SSND", outputBytes + 8);
    SndDChunk.offset = 0;
    SndDChunk.blockSize = 0;
    fwrite(&SndDChunk, sizeof(SoundDataChunk), 1, ofile);
    fwrite(outputBuf, outputBytes, 1, ofile);

    // Fix the size in the header
    s32 fileSize = bswap32(ftell(ofile) - 8);
    fseek(ofile, 4, SEEK_SET);
    fwrite(&fileSize, 4, 1, ofile);

    fclose(ifile);
    fclose(ofile);
    return 0;
}
