.equ LOCALID_NURSE, 1

NestpineTown_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NestpineTown_PokemonCenter_OnTransition
	.byte 0

NestpineTown_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_NESTPINE_TOWN
	end

NestpineTown_PokemonCenter_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

NestpineTown_PokemonCenter_EventScript_NestBallSwapper::
	lock
	faceplayer
	msgbox NestpineTown_PokemonCenter_Text_ThisTownIsLikeAWarmNest, MSGBOX_DEFAULT
	bufferleadmonspeciesname 0
	specialvar VAR_RESULT GetLeadMonBall
	compare VAR_RESULT, ITEM_NEST_BALL
	goto_if_ne NestpineTown_PokemonCenter_EventScript_OfferToSwap
	msgbox NestpineTown_PokemonCenter_Text_HahaEvenYourPokemonIsInANestBall, MSGBOX_DEFAULT
	release
	end

NestpineTown_PokemonCenter_EventScript_OfferToSwap:
	msgbox NestpineTown_PokemonCenter_Text_SpeakingOfNests, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq NestpineTown_PokemonCenter_EventScript_SwapBallForNest
	msgbox NestpineTown_PokemonCenter_Text_OhOkay, MSGBOX_DEFAULT
	release
	end

NestpineTown_PokemonCenter_EventScript_SwapBallForNest:
	msgbox NestpineTown_PokemonCenter_Text_Alright, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004 ITEM_NEST_BALL
	special SetLeadMonBall
	fadescreen FADE_FROM_BLACK
	msgbox NestpineTown_PokemonCenter_Text_ThereWeGo, MSGBOX_DEFAULT
	release
	end

NestpineTown_PokemonCenter_Text_ThisTownIsLikeAWarmNest:
	.string "This town is like a warm nest!$"

NestpineTown_PokemonCenter_Text_HahaEvenYourPokemonIsInANestBall:
	.string "Haha, even your {STR_VAR_1}\n"
	.string "is in a Nest Ball!$"

NestpineTown_PokemonCenter_Text_SpeakingOfNests:
	.string "Speaking of nests…\n"
	.string "I love Nest Balls!\p"
	.string "How about I change {STR_VAR_1}'s\n"
	.string "Ball for a Nest Ball?$"
	
NestpineTown_PokemonCenter_Text_OhOkay:
	.string "Oh, okay…$"

NestpineTown_PokemonCenter_Text_Alright:
	.string "Alright!$"

NestpineTown_PokemonCenter_Text_ThereWeGo:
	.string "There we go!\n"
	.string "All nice and cozy!$"

NestpineTown_PokemonCenter_EventScript_Youngster::
	msgbox NestpineTown_PokemonCenter_Text_NestpineTownIsVeryQuiet, MSGBOX_NPC
	end

NestpineTown_PokemonCenter_Text_NestpineTownIsVeryQuiet:
	.string "Nestpine Town is very quiet…\n"
	.string "Not much happens here.$"
