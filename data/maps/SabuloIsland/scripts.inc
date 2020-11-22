.set LOCALID_SABULO_CAVE_GUARD, 5
.set LOCALID_REGIROCK, 6
.set LOCALID_BELLE, 7

SabuloIsland_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SabuloIsland_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SabuloIsland_OnFrame
	.byte 0

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
	savebgm MUS_M_DUNGON
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
	setflag FLAG_HIDE_SABULO_ISLAND_CIVILIANS
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
