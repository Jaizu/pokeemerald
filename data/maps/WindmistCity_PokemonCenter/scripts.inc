WindmistCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WindmistCity_PokemonCenter_OnTransition
	.byte 0

WindmistCity_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_WINDMIST_CITY
	end

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

WindmistCity_PokemonCenter_EventScript_Explorer::
	msgbox WindmistCity_PokemonCenter_Text_ExplainSnowWarning, MSGBOX_NPC
	end

WindmistCity_PokemonCenter_Text_ExplainSnowWarning:
	.string "When my Snover is sent out in\n"
	.string "battle it summons a hailstorm!\p"
	.string "Impressive, right?$"
