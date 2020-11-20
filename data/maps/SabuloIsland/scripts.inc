.set LOCALID_SABULO_CAVE_GUARD, 5

SabuloIsland_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SabuloIsland_OnTransition
	.byte 0

SabuloIsland_OnTransition::
	setflag FLAG_VISITED_SABULO_ISLAND
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
