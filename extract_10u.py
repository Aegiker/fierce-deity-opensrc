#!/usr/bin/python3

import os
import sys
import struct
from multiprocessing import Pool, cpu_count


ROM_FILE_NAME = '10u.z64'
FILE_TABLE_OFFSET = 0x7430

FILE_NAMES = [
    'skip', # makerom
    'skip', # boot
    'skip', # dmadata
    'skip', # Audiobank
    'skip', # Audioseq
    'skip', # Audiotable
    'skip', # kanji
    'skip', # link_animetion
    'icon_item_static',
    'icon_item_24_static',
    'skip', # icon_item_field_static
    'skip', # icon_item_dungeon_static
    'skip', # icon_item_gameover_static
    'skip', # icon_item_jpn_static
    'icon_item_nes_static',
    'skip', # item_name_static
    'skip', # map_name_static
    'skip', # do_action_static
    'message_static',
    'skip', # message_data_static
    'message_texture_static',
    'skip', # nes_font_static
    'skip', # nes_message_data_static
    'skip', # staff_message_data_static
    'skip', # map_grand_static
    'skip', # map_i_static
    'skip', # map_48x85_static
    'skip', # code
    'skip', # n64dd
    'skip', # ovl_title
    'skip', # ovl_select
    'skip', # ovl_opening
    'skip', # ovl_file_choose
    'skip', # ovl_kaleido_scope
    'skip', # ovl_player_actor
    'skip', # ovl_map_mark_data
    'skip', # ovl_En_Test
    'skip', # ovl_En_GirlA
    'skip', # ovl_En_Part
    'skip', # ovl_En_Light
    'skip', # ovl_En_Door
    'skip', # ovl_En_Box
    'skip', # ovl_En_Poh
    'skip', # ovl_En_Okuta
    'skip', # ovl_En_Bom
    'skip', # ovl_En_Wallmas
    'skip', # ovl_En_Dodongo
    'skip', # ovl_En_Firefly
    'skip', # ovl_En_Horse
    'skip', # ovl_En_Arrow
    'skip', # ovl_En_Elf
    'skip', # ovl_En_Niw
    'skip', # ovl_En_Tite
    'skip', # ovl_En_Reeba
    'skip', # ovl_En_Peehat
    'skip', # ovl_En_Holl
    'skip', # ovl_En_Scene_Change
    'skip', # ovl_En_Zf
    'skip', # ovl_En_Hata
    'skip', # ovl_Boss_Dodongo
    'skip', # ovl_Boss_Goma
    'skip', # ovl_En_Zl1
    'skip', # ovl_En_Viewer
    'skip', # ovl_En_Goma
    'skip', # ovl_Bg_Pushbox
    'skip', # ovl_En_Bubble
    'skip', # ovl_Door_Shutter
    'skip', # ovl_En_Dodojr
    'skip', # ovl_En_Bdfire
    'skip', # ovl_En_Boom
    'skip', # ovl_En_Torch2
    'skip', # ovl_En_Bili
    'skip', # ovl_En_Tp
    'skip', # ovl_En_St
    'skip', # ovl_En_Bw
    'skip', # ovl_En_Eiyer
    'skip', # ovl_En_River_Sound
    'skip', # ovl_En_Horse_Normal
    'skip', # ovl_En_Ossan
    'skip', # ovl_Bg_Treemouth
    'skip', # ovl_Bg_Dodoago
    'skip', # ovl_Bg_Hidan_Dalm
    'skip', # ovl_Bg_Hidan_Hrock
    'skip', # ovl_En_Horse_Ganon
    'skip', # ovl_Bg_Hidan_Rock
    'skip', # ovl_Bg_Hidan_Rsekizou
    'skip', # ovl_Bg_Hidan_Sekizou
    'skip', # ovl_Bg_Hidan_Sima
    'skip', # ovl_Bg_Hidan_Syoku
    'skip', # ovl_En_Xc
    'skip', # ovl_Bg_Hidan_Curtain
    'skip', # ovl_Bg_Spot00_Hanebasi
    'skip', # ovl_En_Mb
    'skip', # ovl_En_Bombf
    'skip', # ovl_Bg_Hidan_Firewall
    'skip', # ovl_Bg_Dy_Yoseizo
    'skip', # ovl_En_Zl2
    'skip', # ovl_Bg_Hidan_Fslift
    'skip', # ovl_En_OE2
    'skip', # ovl_Bg_Ydan_Hasi
    'skip', # ovl_Bg_Ydan_Maruta
    'skip', # ovl_Boss_Ganondrof
    'skip', # ovl_En_Am
    'skip', # ovl_En_Dekubaba
    'skip', # ovl_En_M_Fire1
    'skip', # ovl_En_M_Thunder
    'skip', # ovl_Bg_Ddan_Jd
    'skip', # ovl_Bg_Breakwall
    'skip', # ovl_En_Jj
    'skip', # ovl_En_Horse_Zelda
    'skip', # ovl_Bg_Ddan_Kd
    'skip', # ovl_Door_Warp1
    'skip', # ovl_Obj_Syokudai
    'skip', # ovl_Item_B_Heart
    'skip', # ovl_En_Dekunuts
    'skip', # ovl_Bg_Menkuri_Kaiten
    'skip', # ovl_Bg_Menkuri_Eye
    'skip', # ovl_En_Vali
    'skip', # ovl_Bg_Mizu_Movebg
    'skip', # ovl_Bg_Mizu_Water
    'skip', # ovl_Arms_Hook
    'skip', # ovl_En_fHG
    'skip', # ovl_Bg_Mori_Hineri
    'skip', # ovl_En_Bb
    'skip', # ovl_Bg_Toki_Hikari
    'skip', # ovl_En_Yukabyun
    'skip', # ovl_Bg_Toki_Swd
    'skip', # ovl_En_Fhg_Fire
    'skip', # ovl_Bg_Mjin
    'skip', # ovl_Bg_Hidan_Kousi
    'skip', # ovl_Door_Toki
    'skip', # ovl_Bg_Hidan_Hamstep
    'skip', # ovl_En_Bird
    'skip', # ovl_En_Wood02
    'skip', # ovl_En_Lightbox
    'skip', # ovl_En_Pu_box
    'skip', # ovl_En_Trap
    'skip', # ovl_En_Arow_Trap
    'skip', # ovl_En_Vase
    'skip', # ovl_En_Ta
    'skip', # ovl_En_Tk
    'skip', # ovl_Bg_Mori_Bigst
    'skip', # ovl_Bg_Mori_Elevator
    'skip', # ovl_Bg_Mori_Kaitenkabe
    'skip', # ovl_Bg_Mori_Rakkatenjo
    'skip', # ovl_En_Vm
    'skip', # ovl_Demo_Effect
    'skip', # ovl_Demo_Kankyo
    'skip', # ovl_Bg_Hidan_Fwbig
    'skip', # ovl_En_Floormas
    'skip', # ovl_En_Heishi1
    'skip', # ovl_En_Rd
    'skip', # ovl_En_Po_Sisters
    'skip', # ovl_Bg_Heavy_Block
    'skip', # ovl_Bg_Po_Event
    'skip', # ovl_Obj_Mure
    'skip', # ovl_En_Sw
    'skip', # ovl_Boss_Fd
    'skip', # ovl_Object_Kankyo
    'skip', # ovl_En_Du
    'skip', # ovl_En_Fd
    'skip', # ovl_En_Horse_Link_Child
    'skip', # ovl_Door_Ana
    'skip', # ovl_Bg_Spot02_Objects
    'skip', # ovl_Bg_Haka
    'skip', # ovl_Magic_Wind
    'skip', # ovl_Magic_Fire
    'skip', # ovl_En_Ru1
    'skip', # ovl_Boss_Fd2
    'skip', # ovl_En_Fd_Fire
    'skip', # ovl_En_Dh
    'skip', # ovl_En_Dha
    'skip', # ovl_En_Rl
    'skip', # ovl_En_Encount1
    'skip', # ovl_Demo_Du
    'skip', # ovl_Demo_Im
    'skip', # ovl_Demo_Tre_Lgt
    'skip', # ovl_En_Fw
    'skip', # ovl_Bg_Vb_Sima
    'skip', # ovl_En_Vb_Ball
    'skip', # ovl_Bg_Haka_Megane
    'skip', # ovl_Bg_Haka_MeganeBG
    'skip', # ovl_Bg_Haka_Ship
    'skip', # ovl_Bg_Haka_Sgami
    'skip', # ovl_En_Heishi2
    'skip', # ovl_En_Encount2
    'skip', # ovl_En_Fire_Rock
    'skip', # ovl_En_Brob
    'skip', # ovl_Mir_Ray
    'skip', # ovl_Bg_Spot09_Obj
    'skip', # ovl_Bg_Spot18_Obj
    'skip', # ovl_Boss_Va
    'skip', # ovl_Bg_Haka_Tubo
    'skip', # ovl_Bg_Haka_Trap
    'skip', # ovl_Bg_Haka_Huta
    'skip', # ovl_Bg_Haka_Zou
    'skip', # ovl_Bg_Spot17_Funen
    'skip', # ovl_En_Syateki_Itm
    'skip', # ovl_En_Syateki_Man
    'skip', # ovl_En_Tana
    'skip', # ovl_En_Nb
    'skip', # ovl_Boss_Mo
    'skip', # ovl_En_Sb
    'skip', # ovl_En_Bigokuta
    'skip', # ovl_En_Karebaba
    'skip', # ovl_Bg_Bdan_Objects
    'skip', # ovl_Demo_Sa
    'skip', # ovl_Demo_Go
    'skip', # ovl_En_In
    'skip', # ovl_En_Tr
    'skip', # ovl_Bg_Spot16_Bombstone
    'skip', # ovl_Bg_Hidan_Kowarerukabe
    'skip', # ovl_Bg_Bombwall
    'skip', # ovl_En_Ru2
    'skip', # ovl_Obj_Dekujr
    'skip', # ovl_Bg_Mizu_Uzu
    'skip', # ovl_Bg_Spot06_Objects
    'skip', # ovl_Bg_Ice_Objects
    'skip', # ovl_Bg_Haka_Water
    'skip', # ovl_En_Ma2
    'skip', # ovl_En_Bom_Chu
    'skip', # ovl_En_Horse_Game_Check
    'skip', # ovl_Boss_Tw
    'skip', # ovl_En_Rr
    'skip', # ovl_En_Ba
    'skip', # ovl_En_Bx
    'skip', # ovl_En_Anubice
    'skip', # ovl_En_Anubice_Fire
    'skip', # ovl_Bg_Mori_Hashigo
    'skip', # ovl_Bg_Mori_Hashira4
    'skip', # ovl_Bg_Mori_Idomizu
    'skip', # ovl_Bg_Spot16_Doughnut
    'skip', # ovl_Bg_Bdan_Switch
    'skip', # ovl_En_Ma1
    'skip', # ovl_Boss_Ganon
    'skip', # ovl_Boss_Sst
    'skip', # ovl_En_Ny
    'skip', # ovl_En_Fr
    'skip', # ovl_Item_Shield
    'skip', # ovl_Bg_Ice_Shelter
    'skip', # ovl_En_Ice_Hono
    'skip', # ovl_Item_Ocarina
    'skip', # ovl_Magic_Dark
    'skip', # ovl_Demo_6K
    'skip', # ovl_En_Anubice_Tag
    'skip', # ovl_Bg_Haka_Gate
    'skip', # ovl_Bg_Spot15_Saku
    'skip', # ovl_Bg_Jya_Goroiwa
    'skip', # ovl_Bg_Jya_Zurerukabe
    'skip', # ovl_Bg_Jya_Cobra
    'skip', # ovl_Bg_Jya_Kanaami
    'skip', # ovl_Fishing
    'skip', # ovl_Obj_Oshihiki
    'skip', # ovl_Bg_Gate_Shutter
    'skip', # ovl_Eff_Dust
    'skip', # ovl_Bg_Spot01_Fusya
    'skip', # ovl_Bg_Spot01_Idohashira
    'skip', # ovl_Bg_Spot01_Idomizu
    'skip', # ovl_Bg_Po_Syokudai
    'skip', # ovl_Bg_Ganon_Otyuka
    'skip', # ovl_Bg_Spot15_Rrbox
    'skip', # ovl_Bg_Umajump
    'skip', # ovl_En_Insect
    'skip', # ovl_En_Butte
    'skip', # ovl_En_Fish
    'skip', # ovl_Bg_Spot08_Iceblock
    'skip', # ovl_Item_Etcetera
    'skip', # ovl_Arrow_Fire
    'skip', # ovl_Arrow_Ice
    'skip', # ovl_Arrow_Light
    'skip', # ovl_Obj_Kibako
    'skip', # ovl_Obj_Tsubo
    'skip', # ovl_En_Wonder_Item
    'skip', # ovl_En_Ik
    'skip', # ovl_Demo_Ik
    'skip', # ovl_En_Skj
    'skip', # ovl_En_Skjneedle
    'skip', # ovl_En_G_Switch
    'skip', # ovl_Demo_Ext
    'skip', # ovl_Demo_Shd
    'skip', # ovl_En_Dns
    'skip', # ovl_Elf_Msg
    'skip', # ovl_En_Honotrap
    'skip', # ovl_En_Tubo_Trap
    'skip', # ovl_Obj_Ice_Poly
    'skip', # ovl_Bg_Spot03_Taki
    'skip', # ovl_Bg_Spot07_Taki
    'skip', # ovl_En_Fz
    'skip', # ovl_En_Po_Relay
    'skip', # ovl_Bg_Relay_Objects
    'skip', # ovl_En_Diving_Game
    'skip', # ovl_En_Kusa
    'skip', # ovl_Obj_Bean
    'skip', # ovl_Obj_Bombiwa
    'skip', # ovl_Obj_Switch
    'skip', # ovl_Obj_Elevator
    'skip', # ovl_Obj_Lift
    'skip', # ovl_Obj_Hsblock
    'skip', # ovl_En_Okarina_Tag
    'skip', # ovl_En_Yabusame_Mark
    'skip', # ovl_En_Goroiwa
    'skip', # ovl_En_Ex_Ruppy
    'skip', # ovl_En_Toryo
    'skip', # ovl_En_Daiku
    'skip', # ovl_En_Nwc
    'skip', # ovl_En_Blkobj
    'skip', # ovl_Item_Inbox
    'skip', # ovl_En_Ge1
    'skip', # ovl_Obj_Blockstop
    'skip', # ovl_En_Sda
    'skip', # ovl_En_Clear_Tag
    'skip', # ovl_En_Niw_Lady
    'skip', # ovl_En_Gm
    'skip', # ovl_En_Ms
    'skip', # ovl_En_Hs
    'skip', # ovl_Bg_Ingate
    'skip', # ovl_En_Kanban
    'skip', # ovl_En_Heishi3
    'skip', # ovl_En_Syateki_Niw
    'skip', # ovl_En_Attack_Niw
    'skip', # ovl_Bg_Spot01_Idosoko
    'skip', # ovl_En_Sa
    'skip', # ovl_En_Wonder_Talk
    'skip', # ovl_Bg_Gjyo_Bridge
    'skip', # ovl_En_Ds
    'skip', # ovl_En_Mk
    'skip', # ovl_En_Bom_Bowl_Man
    'skip', # ovl_En_Bom_Bowl_Pit
    'skip', # ovl_En_Owl
    'skip', # ovl_En_Ishi
    'skip', # ovl_Obj_Hana
    'skip', # ovl_Obj_Lightswitch
    'skip', # ovl_Obj_Mure2
    'skip', # ovl_En_Go
    'skip', # ovl_En_Fu
    'skip', # ovl_En_Changer
    'skip', # ovl_Bg_Jya_Megami
    'skip', # ovl_Bg_Jya_Lift
    'skip', # ovl_Bg_Jya_Bigmirror
    'skip', # ovl_Bg_Jya_Bombchuiwa
    'skip', # ovl_Bg_Jya_Amishutter
    'skip', # ovl_Bg_Jya_Bombiwa
    'skip', # ovl_Bg_Spot18_Basket
    'skip', # ovl_En_Ganon_Organ
    'skip', # ovl_En_Siofuki
    'skip', # ovl_En_Stream
    'skip', # ovl_En_Mm
    'skip', # ovl_En_Ko
    'skip', # ovl_En_Kz
    'skip', # ovl_En_Weather_Tag
    'skip', # ovl_Bg_Sst_Floor
    'skip', # ovl_En_Ani
    'skip', # ovl_En_Ex_Item
    'skip', # ovl_Bg_Jya_Ironobj
    'skip', # ovl_En_Js
    'skip', # ovl_En_Jsjutan
    'skip', # ovl_En_Cs
    'skip', # ovl_En_Md
    'skip', # ovl_En_Hy
    'skip', # ovl_En_Ganon_Mant
    'skip', # ovl_En_Okarina_Effect
    'skip', # ovl_En_Mag
    'skip', # ovl_Door_Gerudo
    'skip', # ovl_Elf_Msg2
    'skip', # ovl_Demo_Gt
    'skip', # ovl_En_Po_Field
    'skip', # ovl_Efc_Erupc
    'skip', # ovl_Bg_Zg
    'skip', # ovl_En_Heishi4
    'skip', # ovl_En_Zl3
    'skip', # ovl_Boss_Ganon2
    'skip', # ovl_En_Kakasi
    'skip', # ovl_En_Takara_Man
    'skip', # ovl_Obj_Makeoshihiki
    'skip', # ovl_Oceff_Spot
    'skip', # ovl_End_Title
    'skip', # ovl_En_Torch
    'skip', # ovl_Demo_Ec
    'skip', # ovl_Shot_Sun
    'skip', # ovl_En_Dy_Extra
    'skip', # ovl_En_Wonder_Talk2
    'skip', # ovl_En_Ge2
    'skip', # ovl_Obj_Roomtimer
    'skip', # ovl_En_Ssh
    'skip', # ovl_En_Sth
    'skip', # ovl_Oceff_Wipe
    'skip', # ovl_Effect_Ss_Dust
    'skip', # ovl_Effect_Ss_KiraKira
    'skip', # ovl_Effect_Ss_Bomb
    'skip', # ovl_Effect_Ss_Bomb2
    'skip', # ovl_Effect_Ss_Blast
    'skip', # ovl_Effect_Ss_G_Spk
    'skip', # ovl_Effect_Ss_D_Fire
    'skip', # ovl_Effect_Ss_Bubble
    'skip', # ovl_Effect_Ss_G_Ripple
    'skip', # ovl_Effect_Ss_G_Splash
    'skip', # ovl_Effect_Ss_G_Magma
    'skip', # ovl_Effect_Ss_G_Fire
    'skip', # ovl_Effect_Ss_Lightning
    'skip', # ovl_Effect_Ss_Dt_Bubble
    'skip', # ovl_Effect_Ss_Hahen
    'skip', # ovl_Effect_Ss_Stick
    'skip', # ovl_Effect_Ss_Sibuki
    'skip', # ovl_Effect_Ss_Sibuki2
    'skip', # ovl_Effect_Ss_G_Magma2
    'skip', # ovl_Effect_Ss_Stone1
    'skip', # ovl_Effect_Ss_HitMark
    'skip', # ovl_Effect_Ss_Fhg_Flash
    'skip', # ovl_Effect_Ss_K_Fire
    'skip', # ovl_Effect_Ss_Solder_Srch_Ball
    'skip', # ovl_Effect_Ss_Kakera
    'skip', # ovl_Effect_Ss_Ice_Piece
    'skip', # ovl_Effect_Ss_En_Ice
    'skip', # ovl_Effect_Ss_Fire_Tail
    'skip', # ovl_Effect_Ss_En_Fire
    'skip', # ovl_Effect_Ss_Extra
    'skip', # ovl_Effect_Ss_Fcircle
    'skip', # ovl_Effect_Ss_Dead_Db
    'skip', # ovl_Effect_Ss_Dead_Dd
    'skip', # ovl_Effect_Ss_Dead_Ds
    'skip', # ovl_Effect_Ss_Dead_Sound
    'skip', # ovl_Oceff_Storm
    'skip', # ovl_En_Weiyer
    'skip', # ovl_Bg_Spot05_Soko
    'skip', # ovl_Bg_Jya_1flift
    'skip', # ovl_Bg_Jya_Haheniron
    'skip', # ovl_Bg_Spot12_Gate
    'skip', # ovl_Bg_Spot12_Saku
    'skip', # ovl_En_Hintnuts
    'skip', # ovl_En_Nutsball
    'skip', # ovl_Bg_Spot00_Break
    'skip', # ovl_En_Shopnuts
    'skip', # ovl_En_It
    'skip', # ovl_En_GeldB
    'skip', # ovl_Oceff_Wipe2
    'skip', # ovl_Oceff_Wipe3
    'skip', # ovl_En_Niw_Girl
    'skip', # ovl_En_Dog
    'skip', # ovl_En_Si
    'skip', # ovl_Bg_Spot01_Objects2
    'skip', # ovl_Obj_Comb
    'skip', # ovl_Bg_Spot11_Bakudankabe
    'skip', # ovl_Obj_Kibako2
    'skip', # ovl_En_Dnt_Demo
    'skip', # ovl_En_Dnt_Jiji
    'skip', # ovl_En_Dnt_Nomal
    'skip', # ovl_En_Guest
    'skip', # ovl_Bg_Bom_Guard
    'skip', # ovl_En_Hs2
    'skip', # ovl_Demo_Kekkai
    'skip', # ovl_Bg_Spot08_Bakudankabe
    'skip', # ovl_Bg_Spot17_Bakudankabe
    'skip', # ovl_Obj_Mure3
    'skip', # ovl_En_Tg
    'skip', # ovl_En_Mu
    'skip', # ovl_En_Go2
    'skip', # ovl_En_Wf
    'skip', # ovl_En_Skb
    'skip', # ovl_Demo_Gj
    'skip', # ovl_Demo_Geff
    'skip', # ovl_Bg_Gnd_Firemeiro
    'skip', # ovl_Bg_Gnd_Darkmeiro
    'skip', # ovl_Bg_Gnd_Soulmeiro
    'skip', # ovl_Bg_Gnd_Nisekabe
    'skip', # ovl_Bg_Gnd_Iceblock
    'skip', # ovl_Bg_Ydan_Sp
    'skip', # ovl_En_Gb
    'skip', # ovl_En_Gs
    'skip', # ovl_Bg_Mizu_Bwall
    'skip', # ovl_Bg_Mizu_Shutter
    'skip', # ovl_En_Daiku_Kakariko
    'skip', # ovl_Bg_Bowl_Wall
    'skip', # ovl_En_Wall_Tubo
    'skip', # ovl_En_Po_Desert
    'skip', # ovl_En_Crow
    'skip', # ovl_Door_Killer
    'skip', # ovl_Bg_Spot11_Oasis
    'skip', # ovl_Bg_Spot18_Futa
    'skip', # ovl_Bg_Spot18_Shutter
    'skip', # ovl_En_Ma3
    'skip', # ovl_En_Cow
    'skip', # ovl_Bg_Ice_Turara
    'skip', # ovl_Bg_Ice_Shutter
    'skip', # ovl_En_Kakasi2
    'skip', # ovl_En_Kakasi3
    'skip', # ovl_Oceff_Wipe4
    'skip', # ovl_En_Eg
    'skip', # ovl_Bg_Menkuri_Nisekabe
    'skip', # ovl_En_Zo
    'skip', # ovl_Effect_Ss_Ice_Smoke
    'skip', # ovl_Obj_Makekinsuta
    'skip', # ovl_En_Ge3
    'skip', # ovl_Obj_Timeblock
    'skip', # ovl_Obj_Hamishi
    'skip', # ovl_En_Zl4
    'skip', # ovl_En_Mm2
    'skip', # ovl_Bg_Jya_Block
    'skip', # ovl_Obj_Warp2block
    'skip', # gameplay_keep
    'skip', # gameplay_field_keep
    'skip', # gameplay_dangeon_keep
    'skip', # gameplay_object_exchange_static
    'object_link_boy', # object_link_boy
    'skip', # object_link_child
    'skip', # object_box
    'skip', # object_human
    'skip', # object_okuta
    'skip', # object_poh
    'skip', # object_wallmaster
    'skip', # object_dy_obj
    'skip', # object_firefly
    'skip', # object_dodongo
    'skip', # object_fire
    'skip', # object_niw
    'skip', # object_tite
    'skip', # object_reeba
    'skip', # object_peehat
    'skip', # object_kingdodongo
    'skip', # object_horse
    'skip', # object_zf
    'skip', # object_goma
    'skip', # object_zl1
    'skip', # object_gol
    'skip', # object_bubble
    'skip', # object_dodojr
    'skip', # object_torch2
    'skip', # object_bl
    'skip', # object_tp
    'skip', # object_oA1
    'skip', # object_st
    'skip', # object_bw
    'skip', # object_ei
    'skip', # object_horse_normal
    'skip', # object_oB1
    'skip', # object_o_anime
    'skip', # object_spot04_objects
    'skip', # object_ddan_objects
    'skip', # object_hidan_objects
    'skip', # object_horse_ganon
    'skip', # object_oA2
    'skip', # object_spot00_objects
    'skip', # object_mb
    'skip', # object_bombf
    'skip', # object_sk2
    'skip', # object_oE1
    'skip', # object_oE_anime
    'skip', # object_oE2
    'skip', # object_ydan_objects
    'skip', # object_gnd
    'skip', # object_am
    'skip', # object_dekubaba
    'skip', # object_oA3
    'skip', # object_oA4
    'skip', # object_oA5
    'skip', # object_oA6
    'skip', # object_oA7
    'skip', # object_jj
    'skip', # object_oA8
    'skip', # object_oA9
    'skip', # object_oB2
    'skip', # object_oB3
    'skip', # object_oB4
    'skip', # object_horse_zelda
    'skip', # object_opening_demo1
    'skip', # object_warp1
    'skip', # object_b_heart
    'skip', # object_dekunuts
    'skip', # object_oE3
    'skip', # object_oE4
    'skip', # object_menkuri_objects
    'skip', # object_oE5
    'skip', # object_oE6
    'skip', # object_oE7
    'skip', # object_oE8
    'skip', # object_oE9
    'skip', # object_oE10
    'skip', # object_oE11
    'skip', # object_oE12
    'skip', # object_vali
    'skip', # object_oA10
    'skip', # object_oA11
    'skip', # object_mizu_objects
    'skip', # object_fhg
    'skip', # object_ossan
    'skip', # object_mori_hineri1
    'skip', # object_Bb
    'skip', # object_toki_objects
    'skip', # object_yukabyun
    'skip', # object_zl2
    'skip', # object_mjin
    'skip', # object_mjin_flash
    'skip', # object_mjin_dark
    'skip', # object_mjin_flame
    'skip', # object_mjin_ice
    'skip', # object_mjin_soul
    'skip', # object_mjin_wind
    'skip', # object_mjin_oka
    'skip', # object_haka_objects
    'skip', # object_spot06_objects
    'skip', # object_ice_objects
    'skip', # object_relay_objects
    'skip', # object_mori_hineri1a
    'skip', # object_mori_hineri2
    'skip', # object_mori_hineri2a
    'skip', # object_mori_objects
    'skip', # object_mori_tex
    'skip', # object_spot08_obj
    'skip', # object_warp2
    'skip', # object_hata
    'skip', # object_bird
    'skip', # object_wood02
    'skip', # object_lightbox
    'skip', # object_pu_box
    'skip', # object_trap
    'skip', # object_vase
    'skip', # object_im
    'skip', # object_ta
    'skip', # object_tk
    'skip', # object_xc
    'skip', # object_vm
    'skip', # object_bv
    'skip', # object_hakach_objects
    'skip', # object_efc_crystal_light
    'skip', # object_efc_fire_ball
    'skip', # object_efc_flash
    'skip', # object_efc_lgt_shower
    'skip', # object_efc_star_field
    'skip', # object_god_lgt
    'skip', # object_light_ring
    'skip', # object_triforce_spot
    'skip', # object_medal
    'skip', # object_bdan_objects
    'skip', # object_sd
    'skip', # object_rd
    'skip', # object_po_sisters
    'skip', # object_heavy_object
    'skip', # object_gndd
    'skip', # object_fd
    'skip', # object_du
    'skip', # object_fw
    'skip', # object_horse_link_child
    'skip', # object_spot02_objects
    'skip', # object_haka
    'skip', # object_ru1
    'skip', # object_syokudai
    'skip', # object_fd2
    'skip', # object_dh
    'skip', # object_rl
    'skip', # object_efc_tw
    'skip', # object_demo_tre_lgt
    'skip', # object_gi_key
    'skip', # object_mir_ray
    'skip', # object_brob
    'skip', # object_gi_jewel
    'skip', # object_spot09_obj
    'skip', # object_spot18_obj
    'skip', # object_bdoor
    'skip', # object_spot17_obj
    'skip', # object_shop_dungen
    'skip', # object_nb
    'skip', # object_mo
    'skip', # object_sb
    'skip', # object_gi_melody
    'skip', # object_gi_heart
    'skip', # object_gi_compass
    'skip', # object_gi_bosskey
    'skip', # object_gi_medal
    'skip', # object_gi_nuts
    'skip', # object_sa
    'skip', # object_gi_hearts
    'skip', # object_gi_arrowcase
    'skip', # object_gi_bombpouch
    'skip', # object_in
    'skip', # object_tr
    'skip', # object_spot16_obj
    'skip', # object_oE1s
    'skip', # object_oE4s
    'skip', # object_os_anime
    'skip', # object_gi_bottle
    'skip', # object_gi_stick
    'skip', # object_gi_map
    'skip', # object_oF1d_map
    'skip', # object_ru2
    'skip', # object_gi_shield_1
    'skip', # object_dekujr
    'skip', # object_gi_magicpot
    'skip', # object_gi_bomb_1
    'skip', # object_oF1s
    'skip', # object_ma2
    'skip', # object_gi_purse
    'skip', # object_hni
    'skip', # object_tw
    'skip', # object_rr
    'skip', # object_bxa
    'skip', # object_anubice
    'skip', # object_gi_gerudo
    'skip', # object_gi_arrow
    'skip', # object_gi_bomb_2
    'skip', # object_gi_egg
    'skip', # object_gi_scale
    'skip', # object_gi_shield_2
    'skip', # object_gi_hookshot
    'skip', # object_gi_ocarina
    'skip', # object_gi_milk
    'skip', # object_ma1
    'skip', # object_ganon
    'skip', # object_sst
    'skip', # object_ny
    'skip', # object_fr
    'skip', # object_gi_pachinko
    'skip', # object_gi_boomerang
    'skip', # object_gi_bow
    'skip', # object_gi_glasses
    'skip', # object_gi_liquid
    'skip', # object_ani
    'skip', # object_demo_6k
    'object_gi_shield_3', # object_gi_shield_3
    'skip', # object_gi_letter
    'skip', # object_spot15_obj
    'skip', # object_jya_obj
    'skip', # object_gi_clothes
    'skip', # object_gi_bean
    'skip', # object_gi_fish
    'skip', # object_gi_saw
    'skip', # object_gi_hammer
    'skip', # object_gi_grass
    'skip', # object_gi_longsword
    'skip', # object_spot01_objects
    'skip', # object_md
    'skip', # object_km1
    'skip', # object_kw1
    'skip', # object_zo
    'skip', # object_kz
    'skip', # object_umajump
    'skip', # object_masterkokiri
    'skip', # object_masterkokirihead
    'skip', # object_mastergolon
    'skip', # object_masterzoora
    'skip', # object_aob
    'skip', # object_ik
    'skip', # object_ahg
    'skip', # object_cne
    'skip', # object_gi_niwatori
    'skip', # object_skj
    'skip', # object_gi_bottle_letter
    'skip', # object_bji
    'skip', # object_bba
    'skip', # object_gi_ocarina_0
    'skip', # object_ds
    'skip', # object_ane
    'skip', # object_boj
    'skip', # object_spot03_object
    'skip', # object_spot07_object
    'skip', # object_fz
    'skip', # object_bob
    'skip', # object_ge1
    'skip', # object_yabusame_point
    'skip', # object_gi_boots_2
    'skip', # object_gi_seed
    'skip', # object_gnd_magic
    'skip', # object_d_elevator
    'skip', # object_d_hsblock
    'skip', # object_d_lift
    'skip', # object_mamenoki
    'skip', # object_goroiwa
    'skip', # object_toryo
    'skip', # object_daiku
    'skip', # object_nwc
    'skip', # object_blkobj
    'skip', # object_gm
    'skip', # object_ms
    'skip', # object_hs
    'skip', # object_ingate
    'skip', # object_lightswitch
    'skip', # object_kusa
    'skip', # object_tsubo
    'skip', # object_gi_gloves
    'skip', # object_gi_coin
    'skip', # object_kanban
    'skip', # object_gjyo_objects
    'skip', # object_owl
    'skip', # object_mk
    'skip', # object_fu
    'skip', # object_gi_ki_tan_mask
    'skip', # object_gi_redead_mask
    'skip', # object_gi_skj_mask
    'skip', # object_gi_rabit_mask
    'skip', # object_gi_truth_mask
    'skip', # object_ganon_objects
    'skip', # object_siofuki
    'skip', # object_stream
    'skip', # object_mm
    'skip', # object_fa
    'skip', # object_os
    'skip', # object_gi_eye_lotion
    'skip', # object_gi_powder
    'skip', # object_gi_mushroom
    'skip', # object_gi_ticketstone
    'skip', # object_gi_brokensword
    'skip', # object_js
    'skip', # object_cs
    'skip', # object_gi_prescription
    'skip', # object_gi_bracelet
    'skip', # object_gi_soldout
    'skip', # object_gi_frog
    'object_mag',
    'skip', # object_door_gerudo
    'skip', # object_gt
    'skip', # object_efc_erupc
    'skip', # object_zl2_anime1
    'skip', # object_zl2_anime2
    'skip', # object_gi_golonmask
    'skip', # object_gi_zoramask
    'skip', # object_gi_gerudomask
    'skip', # object_ganon2
    'skip', # object_ka
    'skip', # object_ts
    'skip', # object_zg
    'skip', # object_gi_hoverboots
    'skip', # object_gi_m_arrow
    'skip', # object_ds2
    'skip', # object_ec
    'skip', # object_fish
    'skip', # object_gi_sutaru
    'skip', # object_gi_goddess
    'skip', # object_ssh
    'skip', # object_bigokuta
    'skip', # object_bg
    'skip', # object_spot05_objects
    'skip', # object_spot12_obj
    'skip', # object_bombiwa
    'skip', # object_hintnuts
    'skip', # object_rs
    'skip', # object_spot00_break
    'skip', # object_gla
    'skip', # object_shopnuts
    'skip', # object_geldb
    'skip', # object_gr
    'skip', # object_dog
    'skip', # object_jya_iron
    'skip', # object_jya_door
    'skip', # object_spot01_objects2
    'skip', # object_spot11_obj
    'skip', # object_kibako2
    'skip', # object_dns
    'skip', # object_dnk
    'skip', # object_gi_fire
    'skip', # object_gi_insect
    'skip', # object_gi_butterfly
    'skip', # object_gi_ghost
    'skip', # object_gi_soul
    'skip', # object_bowl
    'skip', # object_po_field
    'skip', # object_demo_kekkai
    'skip', # object_efc_doughnut
    'skip', # object_gi_dekupouch
    'skip', # object_ganon_anime1
    'skip', # object_ganon_anime2
    'skip', # object_ganon_anime3
    'skip', # object_gi_rupy
    'skip', # object_spot01_matoya
    'skip', # object_spot01_matoyab
    'skip', # object_po_composer
    'skip', # object_mu
    'skip', # object_wf
    'skip', # object_skb
    'skip', # object_gj
    'skip', # object_geff
    'skip', # object_haka_door
    'skip', # object_gs
    'skip', # object_ps
    'skip', # object_bwall
    'skip', # object_crow
    'skip', # object_cow
    'skip', # object_cob
    'skip', # object_gi_sword_1
    'skip', # object_door_killer
    'skip', # object_ouke_haka
    'skip', # object_timeblock
    'skip', # object_zl4
    'skip', # g_pn_01
    'skip', # g_pn_02
    'skip', # g_pn_03
    'skip', # g_pn_04
    'skip', # g_pn_05
    'skip', # g_pn_06
    'skip', # g_pn_07
    'skip', # g_pn_08
    'skip', # g_pn_09
    'skip', # g_pn_10
    'skip', # g_pn_11
    'skip', # g_pn_12
    'skip', # g_pn_13
    'skip', # g_pn_14
    'skip', # g_pn_15
    'skip', # g_pn_16
    'skip', # g_pn_17
    'skip', # g_pn_18
    'skip', # g_pn_19
    'skip', # g_pn_20
    'skip', # g_pn_21
    'skip', # g_pn_22
    'skip', # g_pn_23
    'skip', # g_pn_24
    'skip', # g_pn_25
    'skip', # g_pn_26
    'skip', # g_pn_27
    'skip', # g_pn_28
    'skip', # g_pn_29
    'skip', # g_pn_30
    'skip', # g_pn_31
    'skip', # g_pn_32
    'skip', # g_pn_33
    'skip', # g_pn_34
    'skip', # g_pn_35
    'skip', # g_pn_36
    'skip', # g_pn_37
    'skip', # g_pn_38
    'skip', # g_pn_39
    'skip', # g_pn_40
    'skip', # g_pn_41
    'skip', # g_pn_42
    'skip', # g_pn_43
    'skip', # g_pn_44
    'skip', # g_pn_45
    'skip', # g_pn_46
    'skip', # g_pn_47
    'skip', # g_pn_48
    'skip', # g_pn_49
    'skip', # g_pn_50
    'skip', # g_pn_51
    'skip', # g_pn_52
    'skip', # g_pn_53
    'skip', # g_pn_54
    'skip', # g_pn_55
    'skip', # g_pn_56
    'skip', # g_pn_57
    'skip', # z_select_static
    'skip', # nintendo_rogo_static
    'title_static',
    'skip', # parameter_static
    'skip', # vr_fine0_static
    'skip', # vr_fine0_pal_static
    'skip', # vr_fine1_static
    'skip', # vr_fine1_pal_static
    'skip', # vr_fine2_static
    'skip', # vr_fine2_pal_static
    'skip', # vr_fine3_static
    'skip', # vr_fine3_pal_static
    'skip', # vr_cloud0_static
    'skip', # vr_cloud0_pal_static
    'skip', # vr_cloud1_static
    'skip', # vr_cloud1_pal_static
    'skip', # vr_cloud2_static
    'skip', # vr_cloud2_pal_static
    'skip', # vr_cloud3_static
    'skip', # vr_cloud3_pal_static
    'skip', # vr_holy0_static
    'skip', # vr_holy0_pal_stati
    'skip', # vr_holy1_static
    'skip', # vr_holy1_pal_static
    'skip', # vr_MDVR_static
    'skip', # vr_MDVR_pal_static
    'skip', # vr_MNVR_static
    'skip', # vr_MNVR_pal_static
    'skip', # vr_RUVR_static
    'skip', # vr_RUVR_pal_static
    'skip', # vr_LHVR_static
    'skip', # vr_LHVR_pal_static
    'skip', # vr_KHVR_static
    'skip', # vr_KHVR_pal_static
    'skip', # vr_K3VR_static
    'skip', # vr_K3VR_pal_static
    'skip', # vr_K4VR_static
    'skip', # vr_K4VR_pal_static
    'skip', # vr_K5VR_static
    'skip', # vr_K5VR_pal_static
    'skip', # vr_SP1a_static
    'skip', # vr_SP1a_pal_static
    'skip', # vr_MLVR_static
    'skip', # vr_MLVR_pal_static
    'skip', # vr_KKRVR_static
    'skip', # vr_KKRVR_pal_static
    'skip', # vr_KR3VR_static
    'skip', # vr_KR3VR_pal_static
    'skip', # vr_IPVR_static
    'skip', # vr_IPVR_pal_static
    'skip', # vr_KSVR_static
    'skip', # vr_KSVR_pal_static
    'skip', # vr_GLVR_static
    'skip', # vr_GLVR_pal_static
    'skip', # vr_ZRVR_static
    'skip', # vr_ZRVR_pal_static
    'skip', # vr_DGVR_static
    'skip', # vr_DGVR_pal_static
    'skip', # vr_ALVR_static
    'skip', # vr_ALVR_pal_static
    'skip', # vr_NSVR_static
    'skip', # vr_NSVR_pal_static
    'skip', # vr_LBVR_static
    'skip', # vr_LBVR_pal_static
    'skip', # vr_TTVR_static
    'skip', # vr_TTVR_pal_static
    'skip', # vr_FCVR_static
    'skip', # vr_FCVR_pal_static
    'skip', # elf_message_field
    'skip', # elf_message_ydan
    'ddan_scene',
    'ddan_room_0',
    'ddan_room_1',
    'ddan_room_2',
    'ddan_room_3',
    'ddan_room_4',
    'ddan_room_5',
    'ddan_room_6',
    'ddan_room_7',
    'ddan_room_8',
    'ddan_room_9',
    'ddan_room_10',
    'ddan_room_11',
    'ddan_room_12',
    'ddan_room_13',
    'ddan_room_14',
    'ddan_room_15',
    'ddan_room_16',
    'spot00_scene',
    'spot00_room_0',
    'spot01_scene',
    'spot01_room_0',
    'spot02_scene',
    'spot02_room_0',
    'spot02_room_1',
    'spot03_scene',
    'spot03_room_0',
    'spot03_room_1',
    'spot04_scene',
    'spot04_room_0',
    'spot04_room_1',
    'spot04_room_2',
    'spot05_scene',
    'spot05_room_0',
    'spot06_scene',
    'spot06_room_0',
    'spot07_scene',
    'spot07_room_0',
    'spot07_room_1',
    'spot08_scene',
    'spot08_room_0',
    'spot09_scene',
    'spot09_room_0',
    'spot10_scene',
    'spot10_room_0',
    'spot10_room_1',
    'spot10_room_2',
    'spot10_room_3',
    'spot10_room_4',
    'spot10_room_5',
    'spot10_room_6',
    'spot10_room_7',
    'spot10_room_8',
    'spot10_room_9',
    'spot11_scene',
    'spot11_room_0',
    'spot12_scene',
    'spot12_room_0',
    'spot12_room_1',
    'spot13_scene',
    'spot13_room_0',
    'spot13_room_1',
    'spot15_scene',
    'spot15_room_0',
    'spot16_scene',
    'spot16_room_0',
    'spot17_scene',
    'spot17_room_0',
    'spot17_room_1',
    'spot18_scene',
    'spot18_room_0',
    'spot18_room_1',
    'spot18_room_2',
    'spot18_room_3',
    'market_day_scene',
    'market_day_room_0',
    'market_night_scene',
    'market_night_room_0',
    'HIDAN_scene',
    'HIDAN_room_0',
    'HIDAN_room_1',
    'HIDAN_room_2',
    'HIDAN_room_3',
    'HIDAN_room_4',
    'HIDAN_room_5',
    'HIDAN_room_6',
    'HIDAN_room_7',
    'HIDAN_room_8',
    'HIDAN_room_9',
    'HIDAN_room_10',
    'HIDAN_room_11',
    'HIDAN_room_12',
    'HIDAN_room_13',
    'HIDAN_room_14',
    'HIDAN_room_15',
    'HIDAN_room_16',
    'HIDAN_room_17',
    'HIDAN_room_18',
    'HIDAN_room_19',
    'HIDAN_room_20',
    'HIDAN_room_21',
    'HIDAN_room_22',
    'HIDAN_room_23',
    'HIDAN_room_24',
    'HIDAN_room_25',
    'HIDAN_room_26',
    'Bmori1_scene',
    'Bmori1_room_0',
    'Bmori1_room_1',
    'Bmori1_room_2',
    'Bmori1_room_3',
    'Bmori1_room_4',
    'Bmori1_room_5',
    'Bmori1_room_6',
    'Bmori1_room_7',
    'Bmori1_room_8',
    'Bmori1_room_9',
    'Bmori1_room_10',
    'Bmori1_room_11',
    'Bmori1_room_12',
    'Bmori1_room_13',
    'Bmori1_room_14',
    'Bmori1_room_15',
    'Bmori1_room_16',
    'Bmori1_room_17',
    'Bmori1_room_18',
    'Bmori1_room_19',
    'Bmori1_room_20',
    'Bmori1_room_21',
    'Bmori1_room_22',
    'ydan_scene',
    'ydan_room_0',
    'ydan_room_1',
    'ydan_room_2',
    'ydan_room_3',
    'ydan_room_4',
    'ydan_room_5',
    'ydan_room_6',
    'ydan_room_7',
    'ydan_room_8',
    'ydan_room_9',
    'ydan_room_10',
    'ydan_room_11',
    'kenjyanoma_scene',
    'kenjyanoma_room_0',
    'tokinoma_scene',
    'tokinoma_room_0',
    'tokinoma_room_1',
    'link_home_scene',
    'link_home_room_0',
    'kokiri_shop_scene',
    'kokiri_shop_room_0',
    'MIZUsin_scene',
    'MIZUsin_room_0',
    'MIZUsin_room_1',
    'MIZUsin_room_2',
    'MIZUsin_room_3',
    'MIZUsin_room_4',
    'MIZUsin_room_5',
    'MIZUsin_room_6',
    'MIZUsin_room_7',
    'MIZUsin_room_8',
    'MIZUsin_room_9',
    'MIZUsin_room_10',
    'MIZUsin_room_11',
    'MIZUsin_room_12',
    'MIZUsin_room_13',
    'MIZUsin_room_14',
    'MIZUsin_room_15',
    'MIZUsin_room_16',
    'MIZUsin_room_17',
    'MIZUsin_room_18',
    'MIZUsin_room_19',
    'MIZUsin_room_20',
    'MIZUsin_room_21',
    'MIZUsin_room_22',
    'kokiri_home_scene',
    'kokiri_home_room_0',
    'kakusiana_scene',
    'kakusiana_room_0',
    'kakusiana_room_1',
    'kakusiana_room_2',
    'kakusiana_room_3',
    'kakusiana_room_4',
    'kakusiana_room_5',
    'kakusiana_room_6',
    'kakusiana_room_7',
    'kakusiana_room_8',
    'kakusiana_room_9',
    'kakusiana_room_10',
    'kakusiana_room_11',
    'kakusiana_room_12',
    'kakusiana_room_13',
    'entra_scene',
    'entra_room_0',
    'bdan_scene',
    'bdan_room_0',
    'bdan_room_1',
    'bdan_room_2',
    'bdan_room_3',
    'bdan_room_4',
    'bdan_room_5',
    'bdan_room_6',
    'bdan_room_7',
    'bdan_room_8',
    'bdan_room_9',
    'bdan_room_10',
    'bdan_room_11',
    'bdan_room_12',
    'bdan_room_13',
    'bdan_room_14',
    'bdan_room_15',
    'HAKAdan_scene',
    'HAKAdan_room_0',
    'HAKAdan_room_1',
    'HAKAdan_room_2',
    'HAKAdan_room_3',
    'HAKAdan_room_4',
    'HAKAdan_room_5',
    'HAKAdan_room_6',
    'HAKAdan_room_7',
    'HAKAdan_room_8',
    'HAKAdan_room_9',
    'HAKAdan_room_10',
    'HAKAdan_room_11',
    'HAKAdan_room_12',
    'HAKAdan_room_13',
    'HAKAdan_room_14',
    'HAKAdan_room_15',
    'HAKAdan_room_16',
    'HAKAdan_room_17',
    'HAKAdan_room_18',
    'HAKAdan_room_19',
    'HAKAdan_room_20',
    'HAKAdan_room_21',
    'HAKAdan_room_22',
    'moribossroom_scene',
    'moribossroom_room_0',
    'moribossroom_room_1',
    'syatekijyou_scene',
    'syatekijyou_room_0',
    'men_scene',
    'men_room_0',
    'men_room_1',
    'men_room_2',
    'men_room_3',
    'men_room_4',
    'men_room_5',
    'men_room_6',
    'men_room_7',
    'men_room_8',
    'men_room_9',
    'men_room_10',
    'shop1_scene',
    'shop1_room_0',
    'hairal_niwa_scene',
    'hairal_niwa_room_0',
    'ganon_tou_scene',
    'ganon_tou_room_0',
    'market_alley_scene',
    'market_alley_room_0',
    'spot20_scene',
    'spot20_room_0',
    'market_ruins_scene',
    'market_ruins_room_0',
    'entra_n_scene',
    'entra_n_room_0',
    'enrui_scene',
    'enrui_room_0',
    'market_alley_n_scene',
    'market_alley_n_room_0',
    'hiral_demo_scene',
    'hiral_demo_room_0',
    'kokiri_home3_scene',
    'kokiri_home3_room_0',
    'jyasinzou_scene',
    'jyasinzou_room_0',
    'jyasinzou_room_1',
    'jyasinzou_room_2',
    'jyasinzou_room_3',
    'jyasinzou_room_4',
    'jyasinzou_room_5',
    'jyasinzou_room_6',
    'jyasinzou_room_7',
    'jyasinzou_room_8',
    'jyasinzou_room_9',
    'jyasinzou_room_10',
    'jyasinzou_room_11',
    'jyasinzou_room_12',
    'jyasinzou_room_13',
    'jyasinzou_room_14',
    'jyasinzou_room_15',
    'jyasinzou_room_16',
    'jyasinzou_room_17',
    'jyasinzou_room_18',
    'jyasinzou_room_19',
    'jyasinzou_room_20',
    'jyasinzou_room_21',
    'jyasinzou_room_22',
    'jyasinzou_room_23',
    'jyasinzou_room_24',
    'jyasinzou_room_25',
    'jyasinzou_room_26',
    'jyasinzou_room_27',
    'jyasinzou_room_28',
    'ice_doukutu_scene',
    'ice_doukutu_room_0',
    'ice_doukutu_room_1',
    'ice_doukutu_room_2',
    'ice_doukutu_room_3',
    'ice_doukutu_room_4',
    'ice_doukutu_room_5',
    'ice_doukutu_room_6',
    'ice_doukutu_room_7',
    'ice_doukutu_room_8',
    'ice_doukutu_room_9',
    'ice_doukutu_room_10',
    'ice_doukutu_room_11',
    'malon_stable_scene',
    'malon_stable_room_0',
    'kakariko_scene',
    'kakariko_room_0',
    'bdan_boss_scene',
    'bdan_boss_room_0',
    'bdan_boss_room_1',
    'FIRE_bs_scene',
    'FIRE_bs_room_0',
    'FIRE_bs_room_1',
    'hut_scene',
    'hut_room_0',
    'daiyousei_izumi_scene',
    'daiyousei_izumi_room_0',
    'hakaana_scene',
    'hakaana_room_0',
    'yousei_izumi_tate_scene',
    'yousei_izumi_tate_room_0',
    'yousei_izumi_yoko_scene',
    'yousei_izumi_yoko_room_0',
    'golon_scene',
    'golon_room_0',
    'zoora_scene',
    'zoora_room_0',
    'drag_scene',
    'drag_room_0',
    'alley_shop_scene',
    'alley_shop_room_0',
    'night_shop_scene',
    'night_shop_room_0',
    'impa_scene',
    'impa_room_0',
    'labo_scene',
    'labo_room_0',
    'tent_scene',
    'tent_room_0',
    'nakaniwa_scene',
    'nakaniwa_room_0',
    'skip', ##todo: investigate why this scene (ddan_boss_scene) did not extract correctly.
    'skip',
    'skip',
    'ydan_boss_scene',
    'ydan_boss_room_0',
    'ydan_boss_room_1',
    'HAKAdan_bs_scene',
    'HAKAdan_bs_room_0',
    'HAKAdan_bs_room_1',
    'MIZUsin_bs_scene',
    'MIZUsin_bs_room_0',
    'MIZUsin_bs_room_1',
    'ganon_scene',
    'ganon_room_0',
    'ganon_room_1',
    'ganon_room_2',
    'ganon_room_3',
    'ganon_room_4',
    'ganon_room_5',
    'ganon_room_6',
    'ganon_room_7',
    'ganon_room_8',
    'ganon_room_9',
    'ganon_boss_scene',
    'ganon_boss_room_0',
    'jyasinboss_scene',
    'jyasinboss_room_0',
    'jyasinboss_room_1',
    'jyasinboss_room_2',
    'jyasinboss_room_3',
    'kokiri_home4_scene',
    'kokiri_home4_room_0',
    'kokiri_home5_scene',
    'kokiri_home5_room_0',
    'ganon_final_scene',
    'ganon_final_room_0',
    'kakariko3_scene',
    'kakariko3_room_0',
    'hakasitarelay_scene',
    'hakasitarelay_room_0',
    'hakasitarelay_room_1',
    'hakasitarelay_room_2',
    'hakasitarelay_room_3',
    'hakasitarelay_room_4',
    'hakasitarelay_room_5',
    'hakasitarelay_room_6',
    'shrine_scene',
    'shrine_room_0',
    'turibori_scene',
    'turibori_room_0',
    'shrine_n_scene',
    'shrine_n_room_0',
    'shrine_r_scene',
    'shrine_r_room_0',
    'ganontika_scene',
    'ganontika_room_0',
    'ganontika_room_1',
    'ganontika_room_2',
    'ganontika_room_3',
    'ganontika_room_4',
    'ganontika_room_5',
    'ganontika_room_6',
    'ganontika_room_7',
    'ganontika_room_8',
    'ganontika_room_9',
    'ganontika_room_10',
    'ganontika_room_11',
    'ganontika_room_12',
    'ganontika_room_13',
    'ganontika_room_14',
    'ganontika_room_15',
    'ganontika_room_16',
    'ganontika_room_17',
    'ganontika_room_18',
    'ganontika_room_19',
    'hakaana2_scene',
    'hakaana2_room_0',
    'gerudoway_scene',
    'gerudoway_room_0',
    'gerudoway_room_1',
    'gerudoway_room_2',
    'gerudoway_room_3',
    'gerudoway_room_4',
    'gerudoway_room_5',
    'HAKAdanCH_scene',
    'HAKAdanCH_room_0',
    'HAKAdanCH_room_1',
    'HAKAdanCH_room_2',
    'HAKAdanCH_room_3',
    'HAKAdanCH_room_4',
    'HAKAdanCH_room_5',
    'HAKAdanCH_room_6',
    'hairal_niwa_n_scene',
    'hairal_niwa_n_room_0',
    'bowling_scene',
    'bowling_room_0',
    'hakaana_ouke_scene',
    'hakaana_ouke_room_0',
    'hakaana_ouke_room_1',
    'hakaana_ouke_room_2',
    'hylia_labo_scene',
    'hylia_labo_room_0',
    'souko_scene',
    'souko_room_0',
    'souko_room_1',
    'souko_room_2',
    'miharigoya_scene',
    'miharigoya_room_0',
    'mahouya_scene',
    'mahouya_room_0',
    'takaraya_scene',
    'takaraya_room_0',
    'takaraya_room_1',
    'takaraya_room_2',
    'takaraya_room_3',
    'takaraya_room_4',
    'takaraya_room_5',
    'takaraya_room_6',
    'ganon_sonogo_scene',
    'ganon_sonogo_room_0',
    'ganon_sonogo_room_1',
    'ganon_sonogo_room_2',
    'ganon_sonogo_room_3',
    'ganon_sonogo_room_4',
    'ganon_demo_scene',
    'ganon_demo_room_0',
    'face_shop_scene',
    'face_shop_room_0',
    'kinsuta_scene',
    'kinsuta_room_0',
    'ganontikasonogo_scene',
    'ganontikasonogo_room_0',
    'ganontikasonogo_room_1',
    'skip', # bump_texture_static
    'skip', # anime_model_1_static
    'skip', # anime_model_2_static
    'skip', # anime_model_3_static
    'skip', # anime_model_4_static
    'skip', # anime_model_5_static
    'skip', # anime_model_6_static
    'skip', # anime_texture_1_static
    'skip', # anime_texture_2_static
    'skip', # anime_texture_3_static
    'skip', # anime_texture_4_static
    'skip', # anime_texture_5_static
    'skip', # anime_texture_6_static
    'skip', # softsprite_matrix_static
]

romData = None


def initialize_worker(rom_data):
    global romData
    romData = rom_data

def read_uint32_be(offset):
    return struct.unpack('>I', romData[offset:offset+4])[0]

def write_output_file(name, offset, size):
    try:
        with open(name, 'wb') as f:
            f.write(romData[offset:offset+size])
    except IOError:
        print('failed to write file ' + name)

def ExtractFunc(i):
    filename = 'baserom/' + FILE_NAMES[i]
    entryOffset = FILE_TABLE_OFFSET + 16 * i

    virtStart = read_uint32_be(entryOffset + 0)
    virtEnd   = read_uint32_be(entryOffset + 4)
    physStart = read_uint32_be(entryOffset + 8)
    physEnd   = read_uint32_be(entryOffset + 12)

    if physEnd == 0:  # uncompressed
        compressed = False
        size = virtEnd - virtStart
    else:             # compressed
        compressed = True
        size = physEnd - physStart

    print('extracting ' + filename + " (0x%08X, 0x%08X)" % (virtStart, virtEnd))
    write_output_file(filename, physStart, size)
    if compressed:
        os.system('tools/yaz0 -d ' + filename + ' ' + filename)

#####################################################################

def main():
    try:
        os.mkdir('baserom')
    except:
        pass

    # read baserom data
    try:
        with open(ROM_FILE_NAME, 'rb') as f:
            rom_data = f.read()
    except IOError:
        print('failed to read file' + ROM_FILE_NAME)
        sys.exit(1)

    # extract files
    num_cores = cpu_count()
    print("Extracting baserom 1.0 (U) files with " + str(num_cores) + " CPU cores.")
    with Pool(num_cores, initialize_worker, (rom_data,)) as p:
        p.map(ExtractFunc, range(len(FILE_NAMES)))

if __name__ == "__main__":
    main()
