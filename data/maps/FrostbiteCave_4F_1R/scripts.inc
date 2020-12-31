.equ LOCALID_EUNICE, 5
.equ LOCALID_EAST_GRUNT, 6
.equ LOCALID_SOUTH_GRUNT, 7

FrostbiteCave_4F_1R_MapScripts::
	.byte 0

FrostbiteCave_4F_1R_EventScript_EuniceSceneTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto FrostbiteCave_4F_1R_EventScript_EuniceScene
	end

FrostbiteCave_4F_1R_EventScript_EuniceSceneTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto FrostbiteCave_4F_1R_EventScript_EuniceScene
	end

FrostbiteCave_4F_1R_EventScript_EuniceSceneTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto FrostbiteCave_4F_1R_EventScript_EuniceScene
	end

FrostbiteCave_4F_1R_EventScript_EuniceScene::
	playbgm MUS_MT_PYRE, 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq FrostbiteCave_4F_1R_EventScript_PanCameraToEunice0
	compare VAR_0x8008, 1
	call_if_eq FrostbiteCave_4F_1R_EventScript_PanCameraToEunice1
	compare VAR_0x8008, 2
	call_if_eq FrostbiteCave_4F_1R_EventScript_PanCameraToEunice2
	msgbox FrostbiteCave_4F_1R_Text_WhatIsTheStatus, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SOUTH_GRUNT, Common_Movement_FaceLeft
	waitmovement 0
	delay 20
	playse SE_PIN
	applymovement LOCALID_SOUTH_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SOUTH_GRUNT, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_SOUTH_GRUNT, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 20
	msgbox FrostbiteCave_4F_1R_Text_UhhEuniceMaam, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox FrostbiteCave_4F_1R_Text_WhatIsIt, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SOUTH_GRUNT, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 20
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 20
	playse SE_PIN
	applymovement LOCALID_EUNICE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_EUNICE, Common_Movement_Delay48
	waitmovement 0
	msgbox FrostbiteCave_4F_1R_Text_TheChildFromTheMuseum, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_SOUTH_GRUNT, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq FrostbiteCave_4F_1R_EventScript_PanCameraToPlayer0
	compare VAR_0x8008, 1
	call_if_eq FrostbiteCave_4F_1R_EventScript_PanCameraToPlayer1
	compare VAR_0x8008, 2
	call_if_eq FrostbiteCave_4F_1R_EventScript_PanCameraToPlayer2
	fadedefaultbgm
	setvar VAR_FROSTBITE_CAVE_STATE, 2
	releaseall
	end

FrostbiteCave_4F_1R_EventScript_PanCameraToEunice0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, FrostbiteCave_4F_1R_Movement_PanToEunice0
	waitmovement 0
	special RemoveCameraObject
	return

FrostbiteCave_4F_1R_EventScript_PanCameraToEunice1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, FrostbiteCave_4F_1R_Movement_PanToEunice1
	waitmovement 0
	special RemoveCameraObject
	return

FrostbiteCave_4F_1R_EventScript_PanCameraToEunice2:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, FrostbiteCave_4F_1R_Movement_PanToEunice2
	waitmovement 0
	special RemoveCameraObject
	return

FrostbiteCave_4F_1R_EventScript_PanCameraToPlayer0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, FrostbiteCave_4F_1R_Movement_PanToPlayer0
	waitmovement 0
	special RemoveCameraObject
	return

FrostbiteCave_4F_1R_EventScript_PanCameraToPlayer1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, FrostbiteCave_4F_1R_Movement_PanToPlayer1
	waitmovement 0
	special RemoveCameraObject
	return

FrostbiteCave_4F_1R_EventScript_PanCameraToPlayer2:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, FrostbiteCave_4F_1R_Movement_PanToPlayer2
	waitmovement 0
	special RemoveCameraObject
	return

FrostbiteCave_4F_1R_Text_WhatIsTheStatus:
	.string "Eunice: {COLOR RED}What is the status of\n"
	.string "the operation?\p"
	.string "{COLOR DARK_GREY}Grunt: {COLOR BLUE}The target is secured,\n"
	.string "ma'am.\p"
	.string "We have {COLOR GREEN}Regice{COLOR BLUE}, but it is\n"
	.string "still dormant.\p"
	.string "{COLOR DARK_GREY}Eunice: {COLOR RED}Hm…\n"
	.string "Very well.\p"
	.string "Gather the others and leave.\n"
	.string "Ensure you are not spotted.\p"
	.string "The last thing we need is civilian\ninterference.$"

FrostbiteCave_4F_1R_Text_UhhEuniceMaam:
	.string "Grunt: {COLOR BLUE}Uh…\n"
	.string "Eunice, ma'am…$"

FrostbiteCave_4F_1R_Text_WhatIsIt:
	.string "Eunice: {COLOR RED}What is it?\p"
	.string "Well?\n"
	.string "Spit it out!$"

FrostbiteCave_4F_1R_Text_TheChildFromTheMuseum:
	.string "Eunice: {COLOR RED}The child from the\n"
	.string "Museum?\p"
	.string "Hmph.\n"
	.string "You must be lost.\p"
	.string "This place is not safe for the\n"
	.string "likes of you.\p"
	.string "Go back the way you came, and\n"
	.string "leave the adults alone, okay?$"

FrostbiteCave_4F_1R_Movement_PanToEunice0:
	walk_right
	walk_right
	walk_down
	walk_right
	step_end

FrostbiteCave_4F_1R_Movement_PanToEunice1:
	walk_right
	walk_right
	walk_right
	step_end

FrostbiteCave_4F_1R_Movement_PanToEunice2:
	walk_right
	walk_right
	walk_up
	walk_right
	step_end

FrostbiteCave_4F_1R_Movement_PanToPlayer0:
	walk_left
	walk_left
	walk_up
	walk_left
	step_end

FrostbiteCave_4F_1R_Movement_PanToPlayer1:
	walk_left
	walk_left
	walk_left
	step_end

FrostbiteCave_4F_1R_Movement_PanToPlayer2:
	walk_left
	walk_left
	walk_down
	walk_left
	step_end

FrostbiteCave_4F_1R_EventScript_EuniceBattleSceneTrigger::
	lockall
	setvar VAR_0x8008, 0
	goto FrostbiteCave_4F_1R_EventScript_EuniceBattleScene
	end

FrostbiteCave_4F_1R_EventScript_Eunice::
	lockall
	setvar VAR_0x8008, 1
	goto FrostbiteCave_4F_1R_EventScript_EuniceBattleScene
	end

FrostbiteCave_4F_1R_EventScript_EuniceBattleScene::
	playbgm MUS_MT_PYRE, 0
	savebgm MUS_MT_PYRE
	applymovement LOCALID_EUNICE, Common_Movement_FacePlayer
	waitmovement 0
	delay 20
	playse SE_PIN
	applymovement LOCALID_EUNICE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_EUNICE, Common_Movement_Delay48
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq FrostbiteCave_4F_1R_EventScript_TurnPlayerToEunice0
	msgbox FrostbiteCave_4F_1R_Text_WasINotClear, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox FrostbiteCave_4F_1R_Text_DealWithThisChild, MSGBOX_DEFAULT
	applymovement LOCALID_SOUTH_GRUNT, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox FrostbiteCave_4F_1R_Text_YesEuniceMaam, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq FrostbiteCave_4F_1R_EventScript_WalkGruntToPlayer0
	compare VAR_0x8008, 1
	call_if_eq FrostbiteCave_4F_1R_EventScript_WalkGruntToPlayer1
	playbgm MUS_ENCOUNTER_MAGMA, 0
	msgbox FrostbiteCave_4F_1R_Text_GruntMIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_FROSTBITE_CAVE_GRUNT_5
	trainerbattle_no_intro TRAINER_FROSTBITE_CAVE_GRUNT_5, FrostbiteCave_4F_1R_Text_GruntMDefeated
	compare VAR_0x8008, 0
	call_if_eq FrostbiteCave_4F_1R_EventScript_EuniceFaceGrunt0
	compare VAR_0x8008, 1
	call_if_eq FrostbiteCave_4F_1R_EventScript_EuniceFaceGrunt1
	msgbox FrostbiteCave_4F_1R_Text_Fool, MSGBOX_DEFAULT
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox FrostbiteCave_4F_1R_Text_ContinueWithTheMissionAsPlanned, MSGBOX_DEFAULT
	applymovement LOCALID_EAST_GRUNT, FrostbiteCave_4F_1R_Movement_ExitGrunt
	delay 10
	applymovement LOCALID_EUNICE, Common_Movement_FacePlayer
	waitmovement 0
	delay 10
	compare VAR_0x8008, 0
	call_if_eq FrostbiteCave_4F_1R_EventScript_TurnPlayerToEunice0
	compare VAR_0x8008, 1
	call_if_eq FrostbiteCave_4F_1R_EventScript_TurnPlayerToEunice1
	msgbox FrostbiteCave_4F_1R_Text_EuniceIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_FROSTBITE_CAVE_EUNICE
	trainerbattle_no_intro TRAINER_FROSTBITE_CAVE_EUNICE, FrostbiteCave_4F_1R_Text_EuniceDefeated
	msgbox FrostbiteCave_4F_1R_Text_HmmFineIConcede, MSGBOX_DEFAULT
	closemessage
	delay 10
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_EUNICE
	removeobject LOCALID_EAST_GRUNT
	removeobject LOCALID_SOUTH_GRUNT
	playse SE_EXIT
	waitse
	delay 24
	fadedefaultbgm
	fadescreen FADE_FROM_BLACK
	setvar VAR_FROSTBITE_CAVE_STATE, 3
	releaseall
	end

FrostbiteCave_4F_1R_EventScript_TurnPlayerToEunice0:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

FrostbiteCave_4F_1R_EventScript_TurnPlayerToEunice1:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

FrostbiteCave_4F_1R_EventScript_WalkGruntToPlayer0:
	applymovement LOCALID_SOUTH_GRUNT, FrostbiteCave_4F_1R_Movement_WalkGruntToPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

FrostbiteCave_4F_1R_EventScript_WalkGruntToPlayer1:
	applymovement LOCALID_SOUTH_GRUNT, FrostbiteCave_4F_1R_Movement_WalkGruntToPlayer1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

FrostbiteCave_4F_1R_EventScript_EuniceFaceGrunt0:
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

FrostbiteCave_4F_1R_EventScript_EuniceFaceGrunt1:
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

FrostbiteCave_4F_1R_Text_WasINotClear:
	.string "{COLOR DARK_GREY}Eunice: {COLOR RED}Was I not clear?\n"
	.string "You're testing my patience!$"

FrostbiteCave_4F_1R_Text_DealWithThisChild:
	.string "{COLOR DARK_GREY}Eunice: {COLOR RED}You!\n"
	.string "Deal with this child!$"

FrostbiteCave_4F_1R_Text_YesEuniceMaam:
	.string "{COLOR DARK_GREY}Grunt: {COLOR BLUE}Y-yes, Eunice ma'am!$"

FrostbiteCave_4F_1R_Text_GruntMIntro:
	.string "{COLOR DARK_GREY}Grunt: {COLOR BLUE}Orders are orders!$"

FrostbiteCave_4F_1R_Text_GruntMDefeated:
	.string "This isn't good…$"

FrostbiteCave_4F_1R_Text_Fool:
	.string "{COLOR DARK_GREY}Eunice: {COLOR RED}Fool!$"

FrostbiteCave_4F_1R_Text_ContinueWithTheMissionAsPlanned:
	.string "{COLOR DARK_GREY}Eunice: {COLOR RED}You, continue with the\n"
	.string "mission as planned.\p"
	.string "I'll have to take care of this\n"
	.string "child myself.$"

FrostbiteCave_4F_1R_Text_EuniceIntro:
	.string "{COLOR DARK_GREY}Eunice: {COLOR RED}Your insistence is rather\n"
	.string "irritating, child.\p"
	.string "{PLAY_BGM}{MUS_ENCOUNTER_MAGMA}My name is Eunice, Elder Knight of\n"
	.string "the New Elders!\p"
	.string "I will make you regret disobeying\n"
	.string "my orders!$"

FrostbiteCave_4F_1R_Text_EuniceDefeated:
	.string "Child, I will not forget this.$"

FrostbiteCave_4F_1R_Text_HmmFineIConcede:
	.string "{COLOR DARK_GREY}Eunice: {COLOR RED}Hmm…\n"
	.string "Fine. I concede.\p"
	.string "You may pass, but speak of this to\n"
	.string "no-one.\p"
	.string "Believe me, child, the dawn of a\n"
	.string "new age is imminent.\p"
	.string "It would be dangerous for you to\n"
	.string "get involved any further.\p"
	.string "Farewell.$"

FrostbiteCave_4F_1R_Movement_WalkGruntToPlayer0:
	walk_left
	walk_up
	walk_up
	walk_in_place_fastest_right
	step_end

FrostbiteCave_4F_1R_Movement_WalkGruntToPlayer1:
	walk_left
	walk_in_place_fastest_up
	step_end

FrostbiteCave_4F_1R_Movement_ExitGrunt:
	walk_right
	walk_right
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end

FrostbiteCave_4F_1R_EventScript_GruntM::
	lock
	faceplayer
	msgbox FrostbiteCave_4F_1R_Text_YouReallyDontWantToAnnoyEunice, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	release
	end

FrostbiteCave_4F_1R_Text_YouReallyDontWantToAnnoyEunice:
	.string "You really don't want to annoy\n"
	.string "Eunice.\p"
	.string "You should head back the way you\n"
	.string "came, while you still can.$"
