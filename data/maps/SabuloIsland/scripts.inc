.set LOCALID_SABULO_CAVE_GUARD, 5
.set LOCALID_REGIROCK, 6
.set LOCALID_BELLE, 7
.set LOCALID_ENOCH, 8
.set LOCALID_GRUNT_1, 9
.set LOCALID_GRUNT_2, 10

SabuloIsland_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SabuloIsland_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SabuloIsland_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SabuloIsland_OnFrame
	.byte 0

SabuloIsland_OnLoad:
	compare VAR_SABULO_ISLAND_STATE, 2
	call_if_eq SabuloIsland_EventScript_LockAllDoors
	end

SabuloIsland_EventScript_LockAllDoors::
	setmetatile  6,  7, METATILE_Mauville_Door_Tan_Locked, 1
	setmetatile 18, 16, METATILE_Mauville_Door_Tan_Locked, 1
	setmetatile  4, 21, METATILE_Mauville_Door_Tan_Locked, 1
	setmetatile 24, 27, METATILE_Mauville_Door_Tan_Locked, 1
	return

SabuloIsland_EventScript_UnlockAllDoors::
	setmetatile  6,  7, METATILE_Mauville_Door_Tan, 1
	setmetatile 18, 16, METATILE_Mauville_Door_Tan, 1
	setmetatile  4, 21, METATILE_Mauville_Door_Tan, 1
	setmetatile 24, 27, METATILE_Mauville_Door_Tan, 1
	return

SabuloIsland_OnTransition::
	setflag FLAG_VISITED_SABULO_ISLAND
	end

SabuloIsland_OnFrame:
	map_script_2 VAR_SABULO_ISLAND_STATE, 1, SabuloIsland_EventScript_RegirockScene
	.2byte 0

SabuloIsland_EventScript_RegirockScene:
	lockall
	delay 32
	call SabuloIsland_EventScript_Earthquake
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, SabuloIsland_Movement_WalkPlayerToFaceSabuloCave
	waitmovement 0
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 43 @ x
	setvar VAR_0x8005, 18 @ y
	special TeleportCamera
	fadescreen FADE_FROM_BLACK
	playbgm MUS_M_DUNGON, 0
	playse SE_PIN
	applymovement LOCALID_SABULO_CAVE_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SABULO_CAVE_GUARD, Common_Movement_Delay48
	waitmovement 0
	waitse
	playmoncry SPECIES_REGIROCK, 0
	waitmoncry
	call SabuloIsland_EventScript_Earthquake
	playse SE_PIN
	applymovement LOCALID_SABULO_CAVE_GUARD, SabuloIsland_Movement_SabuloCaveGuardWalkDown
	waitmovement 0
	waitse
	playmoncry SPECIES_REGIROCK, 0
	waitmoncry
	fadescreen FADE_TO_WHITE
	addobject LOCALID_REGIROCK
	clearflag FLAG_HIDE_SABULO_ISLAND_REGIROCK
	fadescreen FADE_FROM_WHITE
	playse SE_PIN
	applymovement LOCALID_SABULO_CAVE_GUARD, SabuloIsland_Movement_ExitSabuloCaveGuard
	waitmovement 0
	removeobject LOCALID_SABULO_CAVE_GUARD
	playmoncry SPECIES_REGIROCK, 0
	waitmoncry
	delay 10
	fadescreen FADE_TO_BLACK
	special ReturnCameraToPlayer
	fadescreen FADE_FROM_BLACK
	addobject LOCALID_BELLE
	playse SE_KAIDAN
	applymovement LOCALID_BELLE, Common_Movement_WalkDown
	waitmovement 0
	waitse
	msgbox SabuloIsland_Text_Player, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SabuloIsland_Movement_WalkPlayerToBelle
	waitmovement 0
	msgbox SabuloIsland_Text_WhatWasThatExplosion, MSGBOX_DEFAULT
	playfanfare MUS_FANFA4
	message SabuloIsland_Text_ObtainedTheHyperPotionsAndRevives
	additem ITEM_HYPER_POTION, 5
	additem ITEM_REVIVE, 5
	waitfanfare
	msgbox SabuloIsland_Text_PlayerPutSuppliesInBag, MSGBOX_DEFAULT
	closemessage
	delay 10
	msgbox SabuloIsland_Text_PleaseBeBrave, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BELLE, Common_Movement_WalkUp
	waitmovement 0
	playse SE_KAIDAN
	waitse
	removeobject LOCALID_BELLE
	setrespawn HEAL_LOCATION_SABULO_ISLAND
	setflag FLAG_HIDE_SABULO_ISLAND_CIVILIANS
	call SabuloIsland_EventScript_LockAllDoors
	special DrawWholeMapView
	clearflag FLAG_UNLOCK_SABULO_ISLAND_DOORS
	setvar VAR_SABULO_ISLAND_STATE, 2
	releaseall
	end

SabuloIsland_EventScript_Earthquake:
	setvar VAR_0x8004, 9  @ vertical pan
	setvar VAR_0x8005, 0  @ horizontal pan
	setvar VAR_0x8006, 15 @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	return

SabuloIsland_Text_Player:
	.string "Belle: {COLOR RED}{PLAYER}!$"

SabuloIsland_Text_WhatWasThatExplosion:
	.string "Belle: {COLOR RED}What was that explosion?\n"
	.string "Are you safe?\p"
	.string "It came from Sabulo Cave?\n"
	.string "Oh dear.\p"
	.string "If Sabulo Cave is in danger, that\n"
	.string "puts the Tower at risk, too.\p"
	.string "I can't risk abandoning my post.\p"
	.string "{PLAYER}, you've already demonstrated\n"
	.string "your prowess as a Trainer.\p"
	.string "I trust that you can contain\n"
	.string "this situation.\p"
	.string "Take these emergency supplies!$"

SabuloIsland_Text_ObtainedTheHyperPotionsAndRevives:
	.string "Obtained 5 Hyper Potions\n"
	.string "and 5 Revives!$"

SabuloIsland_Text_PlayerPutSuppliesInBag:
	.string "{PLAYER} put away the\n"
	.string "supplies in the Items Pocket.$"

SabuloIsland_Text_PleaseBeBrave:
	.string "Belle: {COLOR RED}I am depending on you,\n"
	.string "{PLAYER}! Please, be brave!$"

SabuloIsland_Movement_WalkPlayerToFaceSabuloCave:
	walk_fast_down
	walk_fast_right
	step_end

SabuloIsland_Movement_SabuloCaveGuardWalkDown:
	emote_exclamation_mark
	walk_down
	walk_down
	face_up
	step_end

SabuloIsland_Movement_ExitSabuloCaveGuard:
	emote_exclamation_mark
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

SabuloIsland_Movement_WalkPlayerToBelle:
	walk_left
	face_up
	step_end

SabuloIsland_EventScript_NewEldersTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto SabuloIsland_EventScript_NewEldersScene
	end

SabuloIsland_EventScript_NewEldersTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto SabuloIsland_EventScript_NewEldersScene
	end

SabuloIsland_EventScript_NewEldersTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto SabuloIsland_EventScript_NewEldersScene
	end

SabuloIsland_EventScript_NewEldersScene:
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 43 @ x
	setvar VAR_0x8005, 20 @ y
	special TeleportCamera
	fadescreen FADE_FROM_BLACK
	delay 32
	fadescreen FADE_TO_WHITE
	addobject LOCALID_ENOCH
	addobject LOCALID_GRUNT_1
	addobject LOCALID_GRUNT_2
	fadescreen FADE_FROM_WHITE
	delay 10
	applymovement LOCALID_ENOCH, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 10
	msgbox SabuloIsland_Text_YouSeemToKeepFindingYourselfInvolved, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ENOCH, Common_Movement_WalkUp
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq SabuloIsland_EventScript_PanCameraAndWalkGrunt1ToPlayer0
	compare VAR_0x8008, 1
	call_if_eq SabuloIsland_EventScript_PanCameraAndWalkGrunt1ToPlayer1
	compare VAR_0x8008, 2
	call_if_eq SabuloIsland_EventScript_PanCameraAndWalkGrunt1ToPlayer2
	special ReturnCameraToPlayer
	msgbox SabuloIsland_Text_Grunt1Intro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SABULO_ISLAND_GRUNT_1
	trainerbattle_no_intro TRAINER_SABULO_ISLAND_GRUNT_1, SabuloIsland_Text_Grunt1Defeated
	compare VAR_0x8008, 0
	call_if_eq SabuloIsland_EventScript_Grunt1StepBackGrunt2WalkToPlayer0
	compare VAR_0x8008, 1
	call_if_eq SabuloIsland_EventScript_Grunt1StepBackGrunt2WalkToPlayer1
	compare VAR_0x8008, 2
	call_if_eq SabuloIsland_EventScript_Grunt1StepBackGrunt2WalkToPlayer2
	msgbox SabuloIsland_Text_Grunt2Intro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SABULO_ISLAND_GRUNT_2
	trainerbattle_no_intro TRAINER_SABULO_ISLAND_GRUNT_2, SabuloIsland_Text_Grunt2Defeated
	compare VAR_0x8008, 0
	call_if_eq SabuloIsland_EventScript_Grunt2StepBackEnochWalkToPlayer0
	compare VAR_0x8008, 1
	call_if_eq SabuloIsland_EventScript_Grunt2StepBackEnochWalkToPlayer1
	compare VAR_0x8008, 2
	call_if_eq SabuloIsland_EventScript_Grunt2StepBackEnochWalkToPlayer2
	msgbox SabuloIsland_Text_EnochIntro, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_SABULO_ISLAND_ENOCH
	trainerbattle_no_intro TRAINER_SABULO_ISLAND_ENOCH, SabuloIsland_Text_EnochDefeated
	msgbox SabuloIsland_Text_WeWereGoingToStormTheTower, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq SabuloIsland_EventScript_PanCameraAndWalkEnochToRegirock0
	compare VAR_0x8008, 1
	call_if_eq SabuloIsland_EventScript_PanCameraAndWalkEnochToRegirock1
	compare VAR_0x8008, 2
	call_if_eq SabuloIsland_EventScript_PanCameraAndWalkEnochToRegirock2
	msgbox SabuloIsland_Text_RelicBallGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_WHITE
	playse SE_NAGERU
	waitse
	playse SE_BOWA2
	waitse
	playse SE_KON4
	waitse
	playmoncry SPECIES_REGIROCK, 0
	waitmoncry
	delay 10
	removeobject LOCALID_REGIROCK
	fadescreen FADE_FROM_WHITE
	delay 10
	applymovement LOCALID_ENOCH, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox SabuloIsland_Text_NextTimeIWillBeReady, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	special ReturnCameraToPlayer
	removeobject LOCALID_ENOCH
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	clearflag FLAG_HIDE_SABULO_ISLAND_CIVILIANS
	setflag FLAG_UNLOCK_SABULO_ISLAND_DOORS
	call SabuloIsland_EventScript_UnlockAllDoors
	special DrawWholeMapView
	fadescreen FADE_FROM_BLACK
	setvar VAR_SABULO_ISLAND_STATE, 3
	fadedefaultbgm
	releaseall
	end

SabuloIsland_EventScript_PanCameraAndWalkGrunt1ToPlayer0:
	special SpawnCameraObject
	applymovement LOCALID_GRUNT_1, SabuloIsland_Movement_Grunt1WalkToPlayer0
	applymovement OBJ_EVENT_ID_CAMERA, SabuloIsland_Movement_CameraPanToPlayer0
	waitmovement 0
	special RemoveCameraObject
	return

SabuloIsland_EventScript_PanCameraAndWalkGrunt1ToPlayer1:
	special SpawnCameraObject
	applymovement LOCALID_GRUNT_1, SabuloIsland_Movement_Grunt1WalkToPlayer1
	applymovement OBJ_EVENT_ID_CAMERA, SabuloIsland_Movement_CameraPanToPlayer1
	waitmovement 0
	special RemoveCameraObject
	return

SabuloIsland_EventScript_PanCameraAndWalkGrunt1ToPlayer2:
	special SpawnCameraObject
	applymovement LOCALID_GRUNT_1, SabuloIsland_Movement_Grunt1WalkToPlayer2
	applymovement OBJ_EVENT_ID_CAMERA, SabuloIsland_Movement_CameraPanToPlayer2
	waitmovement 0
	special RemoveCameraObject
	return

SabuloIsland_EventScript_Grunt1StepBackGrunt2WalkToPlayer0:
	applymovement LOCALID_GRUNT_1, SabuloIsland_Movement_Grunt1StepBack0
	waitmovement 0
	applymovement LOCALID_GRUNT_2, SabuloIsland_Movement_Grunt2WalkToPlayer0
	waitmovement 0
	return

SabuloIsland_EventScript_Grunt1StepBackGrunt2WalkToPlayer1:
	applymovement LOCALID_GRUNT_1, SabuloIsland_Movement_Grunt1StepBack1
	waitmovement 0
	applymovement LOCALID_GRUNT_2, SabuloIsland_Movement_Grunt2WalkToPlayer1
	waitmovement 0
	return

SabuloIsland_EventScript_Grunt1StepBackGrunt2WalkToPlayer2:
	applymovement LOCALID_GRUNT_1, SabuloIsland_Movement_Grunt1StepBack2
	waitmovement 0
	applymovement LOCALID_GRUNT_2, SabuloIsland_Movement_Grunt2WalkToPlayer2
	waitmovement 0
	return

SabuloIsland_EventScript_Grunt2StepBackEnochWalkToPlayer0:
	applymovement LOCALID_GRUNT_2, SabuloIsland_Movement_Grunt2StepBack0
	waitmovement 0
	applymovement LOCALID_ENOCH, SabuloIsland_Movement_EnochWalkToPlayer0
	waitmovement 0
	return

SabuloIsland_EventScript_Grunt2StepBackEnochWalkToPlayer1:
	applymovement LOCALID_GRUNT_2, SabuloIsland_Movement_Grunt2StepBack1
	waitmovement 0
	applymovement LOCALID_ENOCH, SabuloIsland_Movement_EnochWalkToPlayer1
	waitmovement 0
	return

SabuloIsland_EventScript_Grunt2StepBackEnochWalkToPlayer2:
	applymovement LOCALID_GRUNT_2, SabuloIsland_Movement_Grunt2StepBack2
	waitmovement 0
	applymovement LOCALID_ENOCH, SabuloIsland_Movement_EnochWalkToPlayer2
	waitmovement 0
	return

SabuloIsland_EventScript_PanCameraAndWalkEnochToRegirock0:
	special SpawnCameraObject
	applymovement LOCALID_ENOCH, SabuloIsland_Movement_EnochWalkFromPlayerToRegirock0
	applymovement OBJ_EVENT_ID_CAMERA, SabuloIsland_Movement_CameraPanToRegirock0
	waitmovement 0
	special RemoveCameraObject
	return

SabuloIsland_EventScript_PanCameraAndWalkEnochToRegirock1:
	special SpawnCameraObject
	applymovement LOCALID_ENOCH, SabuloIsland_Movement_EnochWalkFromPlayerToRegirock1
	applymovement OBJ_EVENT_ID_CAMERA, SabuloIsland_Movement_CameraPanToRegirock1
	waitmovement 0
	special RemoveCameraObject
	return

SabuloIsland_EventScript_PanCameraAndWalkEnochToRegirock2:
	special SpawnCameraObject
	applymovement LOCALID_ENOCH, SabuloIsland_Movement_EnochWalkFromPlayerToRegirock2
	applymovement OBJ_EVENT_ID_CAMERA, SabuloIsland_Movement_CameraPanToRegirock2
	waitmovement 0
	special RemoveCameraObject
	return

SabuloIsland_Text_YouSeemToKeepFindingYourselfInvolved:
	.string "Enoch: {COLOR BLUE}You seem to keep finding\n"
	.string "yourself involved with us, child.\p"
	.string "I have warned you once already.\p"
	.string "If you are here to interfere, you\n"
	.string "shall feel my wrath!\p"
	.string "…\p"
	.string "Very well!\n"
	.string "These two will crush you.\p"
	.string "I have more pressing business to\n"
	.string "attend to.$"

SabuloIsland_Text_Grunt1Intro:
	.string "{COLOR BLUE}You should've fled while you had\n"
	.string "the chance, kid…$"

SabuloIsland_Text_Grunt1Defeated:
	.string "Argh.\n"
	.string "I need to bide more time.$"

SabuloIsland_Text_Grunt2Intro:
	.string "{COLOR BLUE}You've seen nothing, yet.\n"
	.string "I'm much stronger!$"

SabuloIsland_Text_Grunt2Defeated:
	.string "This is absurd. How have we lost\n"
	.string "to some kid?$"

SabuloIsland_Text_EnochIntro:
	.string "Enoch: {COLOR BLUE}Fine!\n"
	.string "I'll crush you myself, then!$"

SabuloIsland_Text_EnochDefeated:
	.string "Enough games!$"

SabuloIsland_Text_WeWereGoingToStormTheTower:
	.string "Enoch: {COLOR BLUE}Argh!\p"
	.string "We were going to storm the Tower,\n"
	.string "but it's clear there's no time.\p"
	.string "I must achieve my main objective…$"

SabuloIsland_Text_RelicBallGo:
	.string "Enoch: {COLOR BLUE}Relic Ball, go!$"

SabuloIsland_Text_NextTimeIWillBeReady:
	.string "Enoch: {COLOR BLUE}Next time we meet, I will\n"
	.string "be ready for your meddling.\p"
	.string "Farewell, child.$"

SabuloIsland_Movement_CameraPanToPlayer0:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

SabuloIsland_Movement_CameraPanToPlayer1:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	step_end

SabuloIsland_Movement_CameraPanToPlayer2:
	delay_16
	delay_16
	walk_down
	walk_right
	walk_down
	walk_down
	step_end

SabuloIsland_Movement_Grunt1WalkToPlayer0:
	walk_down
	walk_down
	walk_down
	step_end

SabuloIsland_Movement_Grunt1WalkToPlayer1:
	walk_down
	walk_right
	walk_down
	walk_down
	step_end

SabuloIsland_Movement_Grunt1WalkToPlayer2:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

SabuloIsland_Movement_Grunt1StepBack0:
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

SabuloIsland_Movement_Grunt1StepBack1:
	walk_up
	walk_left
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

SabuloIsland_Movement_Grunt1StepBack2:
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

SabuloIsland_Movement_Grunt2WalkToPlayer0:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

SabuloIsland_Movement_Grunt2WalkToPlayer1:
	walk_down
	walk_down
	walk_left
	walk_down
	step_end

SabuloIsland_Movement_Grunt2WalkToPlayer2:
	walk_down
	walk_down
	walk_down
	step_end

SabuloIsland_Movement_Grunt2StepBack0:
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

SabuloIsland_Movement_Grunt2StepBack1:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

SabuloIsland_Movement_Grunt2StepBack2:
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

SabuloIsland_Movement_EnochWalkToPlayer0:
	walk_down
	walk_down
	walk_left
	walk_down
	step_end

SabuloIsland_Movement_EnochWalkToPlayer1:
	walk_down
	walk_down
	walk_down
	step_end

SabuloIsland_Movement_EnochWalkToPlayer2:
	walk_down
	walk_down
	walk_right
	walk_down
	step_end

SabuloIsland_Movement_CameraPanToRegirock0:
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	step_end

SabuloIsland_Movement_CameraPanToRegirock1:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SabuloIsland_Movement_CameraPanToRegirock2:
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	step_end

SabuloIsland_Movement_EnochWalkFromPlayerToRegirock0:
	delay_16
	walk_up
	walk_right
	walk_up
	walk_up
	step_end

SabuloIsland_Movement_EnochWalkFromPlayerToRegirock1:
	delay_16
	walk_up
	walk_up
	walk_up
	step_end

SabuloIsland_Movement_EnochWalkFromPlayerToRegirock2:
	delay_16
	walk_up
	walk_left
	walk_up
	walk_up
	step_end

SabuloIsland_EventScript_BellesWordsEcho::
	lockall
	msgbox SabuloIsland_Text_BellesWordsEcho, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	releaseall
	end

SabuloIsland_Text_BellesWordsEcho:
	.string "Belle's words echo…\n"
	.string "Best go investigate that explosion!$"

SabuloIsland_EventScript_LockedDoor::
	lock
	msgbox SabuloIsland_Text_BellesWordsEcho, MSGBOX_DEFAULT
	release
	end

SabuloIsland_EventScript_CitySign::
	msgbox SabuloIsland_Text_CitySign, MSGBOX_SIGN
	end

SabuloIsland_Text_CitySign::
	.string "Sabulo Island\n"
	.string "The Isle of Potential.$"

SabuloIsland_EventScript_SabuloTowerSign::
	msgbox SabuloIsland_Text_SabuloTowerSign, MSGBOX_SIGN
	end

SabuloIsland_Text_SabuloTowerSign::
	.string "Sabulo Tower\p"
	.string "The secrets of Mega Evolution held\n"
	.string "within!$"

SabuloIsland_EventScript_Fisherman::
	msgbox SabuloIsland_Text_AreYouHereToTakeOnBelle, MSGBOX_NPC
	end

SabuloIsland_Text_AreYouHereToTakeOnBelle::
	.string "You look like quite a strong\n"
	.string "Trainer!\p"
	.string "Are you here to take on Belle?$"

SabuloIsland_EventScript_Sailor::
	msgbox SabuloIsland_Text_WhatsInSabuloCave, MSGBOX_NPC
	end

SabuloIsland_Text_WhatsInSabuloCave::
	.string "Do you ever wonder what's in\n"
	.string "Sabulo Cave?\p"
	.string "And why is that old man always\n"
	.string "guarding it, anyway?$"

SabuloIsland_EventScript_OldWoman::
	msgbox SabuloIsland_Text_TheKeyStoneHoldsPower, MSGBOX_NPC
	end

SabuloIsland_Text_TheKeyStoneHoldsPower::
	.string "Successor Belle rewards Trainers\n"
	.string "who show promise a Mega Ring!\p"
	.string "The Key Stone in a Mega Ring holds\n"
	.string "a peculiar power!$"

SabuloIsland_EventScript_AceTrainerF::
	msgbox SabuloIsland_Text_ICantDecideWhichPokemon, MSGBOX_NPC
	end

SabuloIsland_Text_ICantDecideWhichPokemon::
	.string "I can't decide which Pokémon I\n"
	.string "should give a Mega Stone to!$"

SabuloIsland_EventScript_SabuloCaveGuard::
	lock
	faceplayer
	msgbox SabuloIsland_Text_OnlyThoseWellVersedMayEnter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SABULO_CAVE_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SabuloIsland_Text_OnlyThoseWellVersedMayEnter:
	.string "Only those well-versed in the way\n"
	.string "of the world are permitted entry\l"
	.string "to Sabulo Cave. Leave!$"
