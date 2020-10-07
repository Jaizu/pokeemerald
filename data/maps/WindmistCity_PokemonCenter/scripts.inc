WindmistCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WindmistCity_PokemonCenter_OnTransition
	.byte 0

WindmistCity_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_WINDMIST_CITY
	end

WindmistCity_PokemonCenter_EventScript_Kindler::
	msgbox WindmistCity_PokemonCenter_Text_MachopAndI, MSGBOX_NPC
	end

WindmistCity_PokemonCenter_Text_MachopAndI:
	.string "My Machop and I run a roof-\n"
	.string "cleaning service!\p"
	.string "We'll shovel snow off your roof\n"
	.string "for a low, low price!\p"
	.string "What?\n"
	.string "You're not a home-owner?\p"
	.string "…Oh.$"

WindmistCity_PokemonCenter_EventScript_Machop::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOP, 0
	msgbox WindmistCity_PokemonCenter_Text_Machop, MSGBOX_DEFAULT
	closemessage
	release
	end

WindmistCity_PokemonCenter_Text_Machop:
	.string "Machop: {COLOR BLUE}Guoh! Gogogoh!$"

WindmistCity_PokemonCenter_EventScript_Picnicker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WINDMIST_CITY_CHOICE_SCARF, WindmistCity_PokemonCenter_EventScript_ReceivedChoiceScarf
	msgbox WindmistCity_PokemonCenter_Text_IBoughtThisScarf, MSGBOX_DEFAULT
	giveitem ITEM_CHOICE_SCARF
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WINDMIST_CITY_CHOICE_SCARF
	goto WindmistCity_PokemonCenter_EventScript_ReceivedChoiceScarf
	end

WindmistCity_PokemonCenter_EventScript_ReceivedChoiceScarf:
	msgbox WindmistCity_PokemonCenter_Text_IWonderIfPokemonCouldWearThatScarf, MSGBOX_DEFAULT
	release
	end

WindmistCity_PokemonCenter_Text_IBoughtThisScarf:
	.string "I bought this scarf a while back,\n"
	.string "but it doesn't keep me warm.\p"
	.string "I guess you can take it instead.$"

WindmistCity_PokemonCenter_Text_IWonderIfPokemonCouldWearThatScarf:
	.string "I wonder if Pokémon could wear\n"
	.string "that scarf?$"
