.equ LOCALID_NURSE, 1

AerousCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AerousCity_PokemonCenter_OnTransition
	.byte 0

AerousCity_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_AEROUS_CITY
	end

AerousCity_PokemonCenter_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

AerousCity_PokemonCenter_EventScript_Youngster::
	lock
	faceplayer
	msgbox AerousCity_PokemonCenter_Text_WillTheyHaveToRedrawMaps, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousCity_PokemonCenter_Text_WillTheyHaveToRedrawMaps:
	.string "I wonder if they will have to\n"
	.string "redraw these maps if the tremors\l"
	.string "do enough damage to the region…$"

AerousCity_PokemonCenter_EventScript_GameboyKid1::
	lock
	faceplayer
	msgbox AerousCity_PokemonCenter_Text_ImTradingWithMyFriend, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousCity_PokemonCenter_Text_ImTradingWithMyFriend:
	.string "I'm trading with my friend.$"

AerousCity_PokemonCenter_EventScript_GameboyKid2::
	lock
	faceplayer
	msgbox AerousCity_PokemonCenter_Text_MyFriendIsTradingMeHisBoldore, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousCity_PokemonCenter_Text_MyFriendIsTradingMeHisBoldore:
	.string "My friend is trading me his\n"
	.string "Boldore, so it will evolve.\p"
	.string "Boldore also evolve when you train\n"
	.string "them enough, but I'm too lazy.$"
