.equ LOCALID_COULTER, 1

CelantoPath_MapScripts::
	.byte 0

CelantoPath_EventScript_RouteSign::
	msgbox CelantoPath_Text_RouteSign, MSGBOX_SIGN
	end

CelantoPath_Text_RouteSign:
	.string "Celanto Path\n"
	.string "{LEFT_ARROW} Archan Town {RIGHT_ARROW} Celanto Town\l"
	.string "{UP_ARROW} Nestpine Climb$"

CelantoPath_EventScript_Youngster::
	msgbox CelantoPath_Text_JustPastThisLedge, MSGBOX_NPC
	end

CelantoPath_Text_JustPastThisLedge:
	.string "Just past this ledge is\n"
	.string "Archan Town.\p"
	.string "You've got to walk through the\n"
	.string "tall grass to get there from here.$"

CelantoPath_EventScript_OldMan::
	msgbox CelantoPath_Text_HeadedToNestpineTown, MSGBOX_NPC
	end

CelantoPath_Text_HeadedToNestpineTown:
	.string "Headed to Nestpine Town?\p"
	.string "The tremors caused a rock-slide,\n"
	.string "so you'll need Rock Smash to pass.\p"
	.string "Carry on to the west if you're\n"
	.string "headed to Archan Town, though.$"

CelantoPath_EventScript_CoulterFight_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto CelantoPath_EventScript_CoulterFightScene
	end

CelantoPath_EventScript_CoulterFight_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto CelantoPath_EventScript_CoulterFightScene
	end

CelantoPath_EventScript_CoulterFight_Trigger2::
	lockall
	setvar VAR_0x8008, 2
	goto CelantoPath_EventScript_CoulterFightScene
	end

CelantoPath_EventScript_CoulterFightScene:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq CelantoPath_EventScript_CameraPanToCoulter0
	compare VAR_0x8008, 1
	call_if_eq CelantoPath_EventScript_CameraPanToCoulter1
	compare VAR_0x8008, 2
	call_if_eq CelantoPath_EventScript_CameraPanToCoulter2
	compare VAR_STARTER_MON, 0 // Player chose Turtwig
	call_if_eq CelantoPath_EventScript_BufferChimchar
	compare VAR_STARTER_MON, 1 // Player chose Chimchar
	call_if_eq CelantoPath_EventScript_BufferPiplup
	compare VAR_STARTER_MON, 2 // Player chose Piplup
	call_if_eq CelantoPath_EventScript_BufferTurtwig
	msgbox CelantoPath_Text_OkayReadyLetsTakeOurFirstStep, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COULTER, Common_Movement_FaceRight
	waitmovement 0
	delay 10
	playse SE_PIN
	applymovement LOCALID_COULTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_Delay48
	waitmovement 0
	playbgm MUS_RG_RIVAL1, 0
	compare VAR_0x8008, 0
	call_if_eq CelantoPath_EventScript_CoulterWalkToPlayer0
	compare VAR_0x8008, 1
	call_if_eq CelantoPath_EventScript_CoulterWalkToPlayer1
	compare VAR_0x8008, 2
	call_if_eq CelantoPath_EventScript_CoulterWalkToPlayer2
	msgbox CelantoPath_Text_OhItsPlayer, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0 // Player chose Turtwig
	call_if_eq CelantoPath_EventScript_StartCoulterBattleChimchar
	compare VAR_STARTER_MON, 1 // Player chose Chimchar
	call_if_eq CelantoPath_EventScript_StartCoulterBattlePiplup
	compare VAR_STARTER_MON, 2 // Player chose Piplup
	call_if_eq CelantoPath_EventScript_StartCoulterBattleTurtwig
	msgbox CelantoPath_Text_ArghICantBelieveIt, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL2, 0
	compare VAR_0x8008, 0
	call_if_eq CelantoPath_EventScript_CoulterExit0
	compare VAR_0x8008, 1
	call_if_eq CelantoPath_EventScript_CoulterExit1
	compare VAR_0x8008, 2
	call_if_eq CelantoPath_EventScript_CoulterExit2
	removeobject LOCALID_COULTER
	fadedefaultbgm
	delay 10
	setvar VAR_CELANTO_PATH_STATE, 1
	releaseall
	end

CelantoPath_EventScript_CameraPanToCoulter0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, CelantoPath_Movement_CameraPanToCoulter0
	waitmovement 0
	special RemoveCameraObject
	return

CelantoPath_EventScript_CameraPanToCoulter1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, CelantoPath_Movement_CameraPanToCoulter1
	waitmovement 0
	special RemoveCameraObject
	return

CelantoPath_EventScript_CameraPanToCoulter2:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, CelantoPath_Movement_CameraPanToCoulter2
	waitmovement 0
	special RemoveCameraObject
	return

CelantoPath_EventScript_BufferChimchar:
	bufferspeciesname 0, SPECIES_CHIMCHAR
	return

CelantoPath_EventScript_BufferPiplup:
	bufferspeciesname 0, SPECIES_PIPLUP
	return

CelantoPath_EventScript_BufferTurtwig:
	bufferspeciesname 0, SPECIES_TURTWIG
	return

CelantoPath_EventScript_CoulterWalkToPlayer0:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, CelantoPath_Movement_CoulterWalkToPlayer0
	applymovement OBJ_EVENT_ID_CAMERA, CelantoPath_Movement_CameraPanToPlayer0
	waitmovement 0
	special RemoveCameraObject
	return

CelantoPath_EventScript_CoulterWalkToPlayer1:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, CelantoPath_Movement_CoulterWalkToPlayer1
	applymovement OBJ_EVENT_ID_CAMERA, CelantoPath_Movement_CameraPanToPlayer1
	waitmovement 0
	special RemoveCameraObject
	return

CelantoPath_EventScript_CoulterWalkToPlayer2:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, CelantoPath_Movement_CoulterWalkToPlayer2
	applymovement OBJ_EVENT_ID_CAMERA, CelantoPath_Movement_CameraPanToPlayer2
	waitmovement 0
	special RemoveCameraObject
	return

CelantoPath_EventScript_StartCoulterBattleChimchar:
	trainerbattle_no_intro TRAINER_COULTER_CELANTO_PATH_CHIMCHAR, CelantoPath_Text_CoulterDefeat
	return

CelantoPath_EventScript_StartCoulterBattlePiplup:
	trainerbattle_no_intro TRAINER_COULTER_CELANTO_PATH_PIPLUP, CelantoPath_Text_CoulterDefeat
	return

CelantoPath_EventScript_StartCoulterBattleTurtwig:
	trainerbattle_no_intro TRAINER_COULTER_CELANTO_PATH_TURTWIG, CelantoPath_Text_CoulterDefeat
	return

CelantoPath_EventScript_CoulterExit0:
	applymovement LOCALID_COULTER, CelantoPath_Movement_CoulterExit0
	waitmovement 0
	return

CelantoPath_EventScript_CoulterExit1:
	applymovement LOCALID_COULTER, CelantoPath_Movement_CoulterExit1
	waitmovement 0
	return

CelantoPath_EventScript_CoulterExit2:
	applymovement LOCALID_COULTER, CelantoPath_Movement_CoulterExit2
	waitmovement 0
	return
	
CelantoPath_Text_OkayReadyLetsTakeOurFirstStep:
	.string "{RIVAL}: {COLOR BLUE}Okay, {STR_VAR_1}.\n"
	.string "Ready?\p"
	.string "Let's take our first step into the\n"
	.string "tall grass together!$"

CelantoPath_Text_OhItsPlayer:
	.string "{RIVAL}: {COLOR BLUE}Oh, it's {PLAYER}!\p"
	.string "Is this your first time going into\n"
	.string "the tall grass, too?\p"
	.string "It looks like we have no choice,\n"
	.string "if we want to get to Archan Town.\p"
	.string "Say…\n"
	.string "We should train up first!\p"
	.string "C'mon, this will be fun.\n"
	.string "Don't hold back, {PLAYER}!$"

CelantoPath_Text_CoulterDefeat:
	.string "W-what?\n"
	.string "How did I lose?!$"

CelantoPath_Text_ArghICantBelieveIt:
	.string "{RIVAL}: {COLOR BLUE}Argh!\n"
	.string "I can't believe it!$"

CelantoPath_Movement_CameraPanToCoulter0:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

CelantoPath_Movement_CameraPanToCoulter1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

CelantoPath_Movement_CameraPanToCoulter2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

CelantoPath_Movement_CoulterWalkToPlayer0:
	walk_right
	walk_right
	walk_right
	step_end

CelantoPath_Movement_CoulterWalkToPlayer1:
	walk_right
	walk_right
	walk_down
	walk_right
	step_end

CelantoPath_Movement_CoulterWalkToPlayer2:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	step_end
	
CelantoPath_Movement_CameraPanToPlayer0:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

CelantoPath_Movement_CameraPanToPlayer1:
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	step_end

CelantoPath_Movement_CameraPanToPlayer2:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

CelantoPath_Movement_CoulterExit0:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

CelantoPath_Movement_CoulterExit1:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

CelantoPath_Movement_CoulterExit2:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	step_end
