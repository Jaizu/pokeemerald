.equ LOCALID_BOB, 5
.equ LOCALID_STINGA, 7

ArchanTunnel_B2F_1R_MapScripts::
	.byte 0

ArchanTunnel_B2F_1R_EventScript_TremorTrigger::
	lockall
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_BOB, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	applymovement LOCALID_BOB, Common_Movement_Delay48
	waitmovement 0
	setvar VAR_ARCHAN_TUNNEL_STATE, 2
	releaseall
	end

ArchanTunnel_B2F_1R_EventScript_Stinga::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WEEDLE, 0
	msgbox ArchanTunnel_B2F_1R_Text_Stinga, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_STINGA, Common_Movement_Heart
	waitmovement 0
	applymovement LOCALID_STINGA, Common_Movement_Delay48
	waitmovement 0
	msgbox ArchanTunnel_B2F_1R_Text_WouldYouLikeToRescueStinga, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq ArchanTunnel_B2F_1R_EventScript_RescueStinga
	release
	end

ArchanTunnel_B2F_1R_Text_Stinga:
	.string "Stinga: {COLOR BLUE}Burrk!$"

ArchanTunnel_B2F_1R_Text_WouldYouLikeToRescueStinga:
	.string "Would you like to rescue\n"
	.string "Stinga, the boy's Weedle?$"

ArchanTunnel_B2F_1R_EventScript_RescueStinga:
	closemessage
	playse SE_PIN
	applymovement LOCALID_STINGA, Common_Movement_Heart
	waitmovement 0
	applymovement LOCALID_STINGA, Common_Movement_Delay48
	waitmovement 0
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setflag FLAG_DONT_TRANSITION_MUSIC
	setvar VAR_STINGA_STATE, 1
	warp MAP_ARCHAN_TUNNEL_1F_1R, -1, 7, 3
	waitstate
	release
	end

ArchanTunnel_B2F_1R_EventScript_Georg::
	trainerbattle_single TRAINER_GEORG, ArchanTunnel_B2F_1R_Text_GeorgIntro, ArchanTunnel_B2F_1R_Text_GeorgDefeated
	msgbox ArchanTunnel_B2F_1R_Text_GeorgPostBattle, MSGBOX_AUTOCLOSE
	end

ArchanTunnel_B2F_1R_Text_GeorgIntro:
	.string "Howdy!\n"
	.string "Let's have us a battle!$"

ArchanTunnel_B2F_1R_Text_GeorgDefeated:
	.string "Well, shucks…$"

ArchanTunnel_B2F_1R_Text_GeorgPostBattle:
	.string "You're quite the lil' Trainer!$"

ArchanTunnel_B2F_1R_EventScript_Bob::
	trainerbattle_single TRAINER_BOB, ArchanTunnel_B2F_1R_Text_BobIntro, ArchanTunnel_B2F_1R_Text_BobDefeated
	msgbox ArchanTunnel_B2F_1R_Text_BobPostBattle, MSGBOX_AUTOCLOSE
	end

ArchanTunnel_B2F_1R_Text_BobIntro:
	.string "Oh, that tremor was terrifying!$"

ArchanTunnel_B2F_1R_Text_BobDefeated:
	.string "That battle was terrifying, too!$"

ArchanTunnel_B2F_1R_Text_BobPostBattle:
	.string "Is it even safe to be here?$"

ArchanTunnel_B2F_1R_EventScript_Iggy::
	trainerbattle_single TRAINER_IGGY, ArchanTunnel_B2F_1R_Text_IggyIntro, ArchanTunnel_B2F_1R_Text_IggyDefeated
	msgbox ArchanTunnel_B2F_1R_Text_IggyPostBattle, MSGBOX_AUTOCLOSE
	end

ArchanTunnel_B2F_1R_Text_IggyIntro:
	.string "Tremors aside, this tunnel has got\n"
	.string "great acoustics!$"

ArchanTunnel_B2F_1R_Text_IggyDefeated:
	.string "Dude, not cool…$"

ArchanTunnel_B2F_1R_Text_IggyPostBattle:
	.string "As a hardcore rock-and-roller,\n"
	.string "I just love Roggenrola!$"
