.set TRAINER_COULTER_BATTLE_MARSH_INFERNAPE, 1
.set TRAINER_COULTER_BATTLE_MARSH_EMPOLEON, 1
.set TRAINER_COULTER_BATTLE_MARSH_TORTERRA, 1
.set LOCALID_COULTER, 7

BattleMarsh_MapScripts::
	.byte 0

BattleMarsh_EventScript_RouteSign::
	msgbox BattleMarsh_Text_RouteSign, MSGBOX_SIGN
	end

BattleMarsh_Text_RouteSign:
	.string "{LEFT_ARROW} Telmurk Swamp {RIGHT_ARROW} Telmurk City$"

BattleMarsh_EventScript_BattleMarshSign::
	msgbox BattleMarsh_Text_BattleMarshSign, MSGBOX_SIGN
	end

BattleMarsh_Text_BattleMarshSign:
	.string "Battle Marsh\n"
	.string "Where Trainers are put to the test!$"

BattleMarsh_EventScript_CoulterFight_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFight_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFight_Trigger2::
	lockall
	setvar VAR_0x8008, 2
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFight_Trigger3::
	lockall
	setvar VAR_0x8008, 3
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFight_Trigger4::
	lockall
	setvar VAR_0x8008, 4
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFightScene:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter0
	compare VAR_0x8008, 1
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter1
	compare VAR_0x8008, 2
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter2
	compare VAR_0x8008, 3
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter3
	compare VAR_0x8008, 4
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter4
	msgbox BattleMarsh_Text_WeAreNotGonnaLose, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	delay 10
	playse SE_PIN
	applymovement LOCALID_COULTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleMarsh_Text_OhYoureHere, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	compare VAR_0x8008, 0
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer0
	compare VAR_0x8008, 1
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer1
	compare VAR_0x8008, 2
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer2
	compare VAR_0x8008, 3
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer3
	compare VAR_0x8008, 4
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer4
	msgbox BattleMarsh_Text_ThisPlaceIsCool, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_FieldHeal
	msgbox BattleMarsh_Text_NowPlayerIChallengeYou, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0 // Player chose Turtwig
	call_if_eq BattleMarsh_EventScript_StartCoulterBattleInfernape
	compare VAR_STARTER_MON, 1 // Player chose Chimchar
	call_if_eq BattleMarsh_EventScript_StartCoulterBattleEmpoleon
	compare VAR_STARTER_MON, 2 // Player chose Piplup
	call_if_eq BattleMarsh_EventScript_StartCoulterBattleTorterra
	msgbox BattleMarsh_Text_ItsJustMaddening, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	applymovement LOCALID_COULTER, BattleMarsh_Movement_ExitCoulter
	waitmovement 0
	removeobject LOCALID_COULTER
	fadedefaultbgm
	delay 10
	setvar VAR_BATTLE_MARSH_STATE, 1
	releaseall
	end

BattleMarsh_EventScript_CameraPanToCoulter0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter0
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CameraPanToCoulter1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter1
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CameraPanToCoulter2:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter2
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CameraPanToCoulter3:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter3
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CameraPanToCoulter4:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter4
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer0:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer0
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer0
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer1:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer1
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer1
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer2:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer2
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer2
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer3:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer3
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer3
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer4:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer4
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer4
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_StartCoulterBattleInfernape:
	trainerbattle_no_intro TRAINER_COULTER_BATTLE_MARSH_INFERNAPE, BattleMarsh_Text_CoulterDefeat
	return

BattleMarsh_EventScript_StartCoulterBattleEmpoleon:
	trainerbattle_no_intro TRAINER_COULTER_BATTLE_MARSH_EMPOLEON, BattleMarsh_Text_CoulterDefeat
	return

BattleMarsh_EventScript_StartCoulterBattleTorterra:
	trainerbattle_no_intro TRAINER_COULTER_BATTLE_MARSH_TORTERRA, BattleMarsh_Text_CoulterDefeat
	return

BattleMarsh_Text_WeAreNotGonnaLose:
	.string "{RIVAL}: {COLOR BLUE}We're not going to lose to\n"
	.string "{PLAYER} again, team.$"

BattleMarsh_Text_OhYoureHere:
	.string "{RIVAL}: {COLOR BLUE}Oh\n"
	.string "You're here!$"

BattleMarsh_Text_ThisPlaceIsCool:
	.string "{RIVAL}: {COLOR BLUE}This place is cool,\n"
	.string "isn't it?\p"
	.string "Maybe once we're finished helping\n"
	.string "the Professor, we could take the\l"
	.string "Battle Marsh on!\p"
	.string "Anyway, I said we were going to\n"
	.string "battle, and I meant it!\p"
	.string "You look tired, though, so I'll\n"
	.string "heal your Pokémon, first.$"

BattleMarsh_Text_NowPlayerIChallengeYou:
	.string "{RIVAL}: {COLOR BLUE}Now, {PLAYER}!\p"
	.string "I challenge you to a Pokémon\n"
	.string "battle!$"

BattleMarsh_Text_CoulterDefeat:
	.string "Argh! I don't… How?!\n"
	.string "W-why does this… Argh!$"

BattleMarsh_Text_ItsJustMaddening:
	.string "{RIVAL}: {COLOR BLUE}I-it's just…\n"
	.string "It's maddening, you know?\p"
	.string "I try to contain my anger, but…\n"
	.string "Losing is painful, alright?!\p"
	.string "Sigh…\p"
	.string "Maybe I'm not cut out to be a\n"
	.string "Pokémon Trainer after all.\p"
	.string "…\p"
	.string "You're right, I shouldn't be so\n"
	.string "hard on myself.\p"
	.string "I've got a job to do!\n"
	.string "We both have!\p"
	.string "Let's go, {PLAYER}!$"

BattleMarsh_Movement_CameraPanToCoulter0:
	walk_right
	walk_right
	walk_up
	step_end

BattleMarsh_Movement_CameraPanToCoulter1:
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

BattleMarsh_Movement_CameraPanToCoulter2:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

BattleMarsh_Movement_CameraPanToCoulter3:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleMarsh_Movement_CameraPanToCoulter4:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleMarsh_Movement_CoulterWalkToPlayer0:
	walk_down
	walk_left
	step_end

BattleMarsh_Movement_CoulterWalkToPlayer1:
	walk_down
	walk_down
	walk_left
	step_end

BattleMarsh_Movement_CoulterWalkToPlayer2:
	walk_down
	walk_down
	walk_down
	walk_left
	step_end
	
BattleMarsh_Movement_CoulterWalkToPlayer3:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end
	
BattleMarsh_Movement_CoulterWalkToPlayer4:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end
	
BattleMarsh_Movement_CameraPanToPlayer0:
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_CameraPanToPlayer1:
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_CameraPanToPlayer2:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_CameraPanToPlayer3:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_CameraPanToPlayer4:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_ExitCoulter:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
