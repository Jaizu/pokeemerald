.equ LOCALID_EUNICE, 3
.equ LOCALID_GRUNT, 4

FrostbiteCave_2F_1R_MapScripts::
	.byte 0

FrostbiteCave_2F_1R_EventScript_GruntM::
	trainerbattle_single TRAINER_FROSTBITE_CAVE_GRUNT_3, FrostbiteCave_2F_1R_Text_GruntMIntro, FrostbiteCave_2F_1R_Text_GruntMDefeated
	msgbox FrostbiteCave_2F_1R_Text_GruntMPostBattle, MSGBOX_AUTOCLOSE
	end

FrostbiteCave_2F_1R_Text_GruntMIntro:
	.string "Kids like you have no respect for\n"
	.string "our traditions. We'll teach you!$"

FrostbiteCave_2F_1R_Text_GruntMDefeated:
	.string "Whoa, you held your own!\n"
	.string "Maybe you should join us…$"

FrostbiteCave_2F_1R_Text_GruntMPostBattle:
	.string "I'm warning you, kid, you'll\n"
	.string "regret sticking around.$"

FrostbiteCave_2F_1R_EventScript_IcyRock::
	msgbox FrostbiteCave_2F_1R_Text_IcyRock, MSGBOX_SIGN
	end

FrostbiteCave_2F_1R_Text_IcyRock:
	.string "It's a rock that is covered in ice.\p"
	.string "Touching it seems likely to freeze\n"
	.string "you solid!$"

FrostbiteCave_2F_1R_EventScript_EuniceGruntScene::
	lock
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 24
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 9  @ x
	setvar VAR_0x8005, 3  @ y
	special TeleportCamera
	fadescreen FADE_FROM_BLACK
	playbgm MUS_M_DUNGON, 0
	msgbox FrostbiteCave_2F_1R_Text_TheseTremorsAreScary, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, Common_Movement_WalkUp
	waitmovement 0
	removeobject LOCALID_GRUNT
	playse SE_KAIDAN
	waitse
	applymovement LOCALID_EUNICE, FrostbiteCave_2F_1R_Movement_ExitEunice
	waitmovement 0
	removeobject LOCALID_EUNICE
	playse SE_KAIDAN
	waitse
	fadedefaultbgm
	delay 24
	fadescreen FADE_TO_BLACK
	special ReturnCameraToPlayer
	fadescreen FADE_FROM_BLACK
	setvar VAR_FROSTBITE_CAVE_STATE, 1
	release
	end

FrostbiteCave_2F_1R_Text_TheseTremorsAreScary:
	.string "Grunt: {COLOR BLUE}These tremors are scary.\n"
	.string "Are you sure we should be here?\p"
	.string "{COLOR DARK_GREY}Eunice: {COLOR RED}You've got your orders.\n"
	.string "Just do as you're told.\p"
	.string "{COLOR DARK_GREY}Grunt: {COLOR BLUE}Y-yes Eunice, ma'am.$"

FrostbiteCave_2F_1R_Movement_ExitEunice:
	walk_right
	walk_up
	step_end
