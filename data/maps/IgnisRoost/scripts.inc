.set LOCALID_COULTER, 7

IgnisRoost_MapScripts::
	.byte 0

IgnisRoost_EventScript_CoulterMeeting_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto IgnisRoost_EventScript_CoulterMeetingScene
	end

IgnisRoost_EventScript_CoulterMeeting_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto IgnisRoost_EventScript_CoulterMeetingScene
	end

IgnisRoost_EventScript_CoulterMeeting_Trigger2::
	lockall
	setvar VAR_0x8008, 2
	goto IgnisRoost_EventScript_CoulterMeetingScene
	end

IgnisRoost_EventScript_CoulterMeetingScene::
	playbgm MUS_MGM0, 0
	compare VAR_0x8008, 0
	call_if_eq IgnisRoost_EventScript_PanCameraToCoulter0
	compare VAR_0x8008, 1
	call_if_eq IgnisRoost_EventScript_PanCameraToCoulter1
	compare VAR_0x8008, 2
	call_if_eq IgnisRoost_EventScript_PanCameraToCoulter2
	delay 10
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 10
	playse SE_PIN
	applymovement LOCALID_COULTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_Delay48
	waitmovement 0
	msgbox IgnisRoost_Text_Player, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq IgnisRoost_EventScript_WalkPlayerToCoulter0
	compare VAR_0x8008, 1
	call_if_eq IgnisRoost_EventScript_WalkPlayerToCoulter1
	compare VAR_0x8008, 2
	call_if_eq IgnisRoost_EventScript_WalkPlayerToCoulter2
	call IgnisRoost_EventScript_CoulterExplainSituation
	fadedefaultbgm
	setvar VAR_IGNIS_ROOST_STATE, 1
	releaseall
	end

IgnisRoost_EventScript_PanCameraToCoulter0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, IgnisRoost_Movement_PanCameraToCoulter0
	waitmovement 0
	special RemoveCameraObject
	return

IgnisRoost_EventScript_PanCameraToCoulter1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, IgnisRoost_Movement_PanCameraToCoulter1
	waitmovement 0
	special RemoveCameraObject
	return

IgnisRoost_EventScript_PanCameraToCoulter2:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, IgnisRoost_Movement_PanCameraToCoulter2
	waitmovement 0
	special RemoveCameraObject
	return

IgnisRoost_EventScript_WalkPlayerToCoulter0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, IgnisRoost_Movement_PanCameraToPlayer0
	waitmovement 0
	special RemoveCameraObject
	applymovement OBJ_EVENT_ID_PLAYER, IgnisRoost_Movement_WalkPlayerToCoulter0
	waitmovement 0
	return

IgnisRoost_EventScript_WalkPlayerToCoulter1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, IgnisRoost_Movement_PanCameraToPlayer1
	waitmovement 0
	special RemoveCameraObject
	applymovement OBJ_EVENT_ID_PLAYER, IgnisRoost_Movement_WalkPlayerToCoulter1
	waitmovement 0
	return

IgnisRoost_EventScript_WalkPlayerToCoulter2:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, IgnisRoost_Movement_PanCameraToPlayer2
	waitmovement 0
	special RemoveCameraObject
	applymovement OBJ_EVENT_ID_PLAYER, IgnisRoost_Movement_WalkPlayerToCoulter2
	waitmovement 0
	return

IgnisRoost_Text_Player:
	.string "{RIVAL}: {COLOR BLUE}{PLAYER}!$"

IgnisRoost_Movement_PanCameraToCoulter0:
	walk_up
	walk_up
	walk_right
	walk_up
	step_end

IgnisRoost_Movement_PanCameraToCoulter1:
	walk_up
	walk_up
	walk_up
	step_end

IgnisRoost_Movement_PanCameraToCoulter2:
	walk_up
	walk_up
	walk_left
	walk_up
	step_end

IgnisRoost_Movement_PanCameraToPlayer0:
	walk_down
	walk_down
	walk_left
	walk_down
	step_end

IgnisRoost_Movement_PanCameraToPlayer1:
	walk_down
	walk_down
	walk_down
	step_end

IgnisRoost_Movement_PanCameraToPlayer2:
	walk_down
	walk_down
	walk_right
	walk_down
	step_end

IgnisRoost_Movement_WalkPlayerToCoulter0:
	walk_up
	walk_up
	walk_right
	walk_in_place_fastest_up
	step_end

IgnisRoost_Movement_WalkPlayerToCoulter1:
	walk_up
	walk_up
	step_end

IgnisRoost_Movement_WalkPlayerToCoulter2:
	walk_up
	walk_up
	walk_left
	walk_in_place_fastest_up
	step_end

IgnisRoost_EventScript_CoulterAndGrunt::
	lock
	applymovement LOCALID_COULTER, Common_Movement_FacePlayer
	waitmovement 0
	call IgnisRoost_EventScript_CoulterExplainSituation
	release
	end

IgnisRoost_EventScript_CoulterExplainSituation:
	msgbox IgnisRoost_Text_ThisIsCrazy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COULTER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	return

IgnisRoost_Text_ThisIsCrazy:
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}This is crazy!\n"
	.string "Who are these guys?\p"
	.string "They just started attacking me,\n"
	.string "completely unprovoked!\p"
	.string "I've got this guy, you go check out\n"
	.string "the Temple and get some answers!$"

IgnisRoost_EventScript_GruntM1::
	trainerbattle_single TRAINER_IGNIS_ROOST_GRUNT_1, IgnisRoost_Text_GruntM1Intro, IgnisRoost_Text_GruntM1Defeated
	msgbox IgnisRoost_Text_GruntM1PostBattle, MSGBOX_AUTOCLOSE
	end

IgnisRoost_Text_GruntM1Intro:
	.string "This is the highest point in\n"
	.string "Orbtus.\p"
	.string "We're literally reaching for the\n"
	.string "skies to achieve our goal.$"

IgnisRoost_Text_GruntM1Defeated:
	.string "That's a long way to fall…$"

IgnisRoost_Text_GruntM1PostBattle:
	.string "I have let down the boss…$"

IgnisRoost_EventScript_GruntF::
	trainerbattle_single TRAINER_IGNIS_ROOST_GRUNT_2, IgnisRoost_Text_GruntFIntro, IgnisRoost_Text_GruntFDefeated
	msgbox IgnisRoost_Text_GruntFPostBattle, MSGBOX_AUTOCLOSE
	end

IgnisRoost_Text_GruntFIntro:
	.string "We're here to find some important\n"
	.string "information!$"

IgnisRoost_Text_GruntFDefeated:
	.string "Stop trying to foil our plans!$"

IgnisRoost_Text_GruntFPostBattle:
	.string "The Elders of Orbtus knew how to\n"
	.string "live. Modernity is evil!$"

IgnisRoost_EventScript_GruntM2::
	trainerbattle_single TRAINER_IGNIS_ROOST_GRUNT_3, IgnisRoost_Text_GruntM2Intro, IgnisRoost_Text_GruntM2Defeated
	msgbox IgnisRoost_Text_GruntM2PostBattle, MSGBOX_AUTOCLOSE
	end

IgnisRoost_Text_GruntM2Intro:
	.string "What's a couple of kids like you\n"
	.string "doing up here, anyway?$"

IgnisRoost_Text_GruntM2Defeated:
	.string "This was supposed to be a brief\n"
	.string "knowledge-gathering mission!$"

IgnisRoost_Text_GruntM2PostBattle:
	.string "I don't think Enoch expected\n"
	.string "antagonism up here…\p"
	.string "What do you guys what with the\n"
	.string "Temple, anyway?$"

IgnisRoost_EventScript_Grunt::
	lock
	faceplayer
	msgbox IgnisRoost_Text_YikesThatsALongWayDown, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

IgnisRoost_Text_YikesThatsALongWayDown:
	.string "Yikes…\n"
	.string "That's a long way down.\p"
	.string "…Hey, where is your uniform?$"
