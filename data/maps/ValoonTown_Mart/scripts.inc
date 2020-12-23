ValoonTown_Mart_MapScripts::
	.byte 0

ValoonTown_Mart_EventScript_PkmnRangerM::
	msgbox ValoonTown_Mart_Text_HowOutrageous, MSGBOX_NPC
	end

ValoonTown_Mart_Text_HowOutrageous:
	.string "How outrageous!\p"
	.string "That clerk refused to give\n"
	.string "me a discount.\p"
	.string "Does he not know who I am?\p"
	.string "I'm the greatest Ranger\n"
	.string "in this town!$"

ValoonTown_Mart_EventScript_AceTrainerF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_VALOON_TOWN_AIR_BALLOON, ValoonTown_Mart_EventScript_ReceivedAirBalloon
	msgbox ValoonTown_Mart_Text_YouNeverKnowWhatYouMightStepOn, MSGBOX_DEFAULT
	giveitem ITEM_AIR_BALLOON
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_VALOON_TOWN_AIR_BALLOON
	goto ValoonTown_Mart_EventScript_ReceivedAirBalloon
	end

ValoonTown_Mart_EventScript_ReceivedAirBalloon:
	msgbox ValoonTown_Mart_Text_GiveAPokemonThatAirBalloon, MSGBOX_DEFAULT
	release
	end

ValoonTown_Mart_Text_YouNeverKnowWhatYouMightStepOn:
	.string "You never know what you might step\n"
	.string "on around these parts.\p"
	.string "The swamplands can ruin your shoes,\n"
	.string "too, if you aren't careful.\p"
	.string "I have just the thing for you.\n"
	.string "Don't be shy, it's free!$"

ValoonTown_Mart_Text_GiveAPokemonThatAirBalloon:
	.string "Give a Pokémon that Air Balloon and\n"
	.string "it will float over the ground!$"
