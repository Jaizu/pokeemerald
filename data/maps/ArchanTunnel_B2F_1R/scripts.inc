.equ LOCALID_BOB, 5

ArchanTunnel_B2F_1R_MapScripts::
	.byte 0

Archan_Tunnel_B2F_1R_EventScript_TremorTrigger::
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

Archan_Tunnel_B2F_1R_EventScript_Georg::
	trainerbattle_single TRAINER_GEORG, Archan_Tunnel_B2F_1R_Text_GeorgIntro, Archan_Tunnel_B2F_1R_Text_GeorgDefeated
	msgbox Archan_Tunnel_B2F_1R_Text_GeorgPostBattle, MSGBOX_AUTOCLOSE
	end

Archan_Tunnel_B2F_1R_Text_GeorgIntro:
	.string "Howdy!\n"
	.string "Let's have us a battle!$"

Archan_Tunnel_B2F_1R_Text_GeorgDefeated:
	.string "Well, shucks…$"

Archan_Tunnel_B2F_1R_Text_GeorgPostBattle:
	.string "You're quite the lil' Trainer!$"

Archan_Tunnel_B2F_1R_EventScript_Bob::
	trainerbattle_single TRAINER_BOB, Archan_Tunnel_B2F_1R_Text_BobIntro, Archan_Tunnel_B2F_1R_Text_BobDefeated
	msgbox Archan_Tunnel_B2F_1R_Text_BobPostBattle, MSGBOX_AUTOCLOSE
	end

Archan_Tunnel_B2F_1R_Text_BobIntro:
	.string "Oh, that tremor was terrifying!$"

Archan_Tunnel_B2F_1R_Text_BobDefeated:
	.string "That battle was terrifying, too!$"

Archan_Tunnel_B2F_1R_Text_BobPostBattle:
	.string "Is it even safe to be here?$"

Archan_Tunnel_B2F_1R_EventScript_Iggy::
	trainerbattle_single TRAINER_IGGY, Archan_Tunnel_B2F_1R_Text_IggyIntro, Archan_Tunnel_B2F_1R_Text_IggyDefeated
	msgbox Archan_Tunnel_B2F_1R_Text_IggyPostBattle, MSGBOX_AUTOCLOSE
	end

Archan_Tunnel_B2F_1R_Text_IggyIntro:
	.string "Tremors aside, this tunnel has got\n"
	.string "great acoustics!$"

Archan_Tunnel_B2F_1R_Text_IggyDefeated:
	.string "Dude, not cool…$"

Archan_Tunnel_B2F_1R_Text_IggyPostBattle:
	.string "As a hardcore rock-and-roller,\n"
	.string "I just love Roggenrola!$"
