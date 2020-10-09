WindmistCity_House3_MapScripts::
	.byte 0

WindmistCity_House3_EventScript_AceTrainerM::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WINDMIST_CITY_ABILITY_PILL, WindmistCity_House3_EventScript_ReceivedAbilityPill
	msgbox WindmistCity_House3_Text_ImAFitnessFreak, MSGBOX_DEFAULT
	giveitem ITEM_ABILITY_CAPSULE
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WINDMIST_CITY_ABILITY_PILL
	goto WindmistCity_House3_EventScript_ReceivedAbilityPill
	end

WindmistCity_House3_EventScript_ReceivedAbilityPill:
	msgbox WindmistCity_House3_Text_YouCanBuyMoreAbilityPills, MSGBOX_DEFAULT
	release
	end

WindmistCity_House3_Text_ImAFitnessFreak:
	.string "I'm a fitness freak, so when I\n"
	.string "heard Snorlax can have Thick Fat…\p"
	.string "I rushed out and bought an Ability\n"
	.string "Pill immediately!\p"
	.string "In my haste, I forgot my Snorlax's\n"
	.string "Ability has always been Immunity!\p"
	.string "Crisis averted, I suppose! But…\n"
	.string "Now I don't need the Ability Pill!\p"
	.string "You can have it instead.$"

WindmistCity_House3_Text_YouCanBuyMoreAbilityPills:
	.string "You can buy more Ability Pills at\n"
	.string "the Battle Marsh.\p"
	.string "Of course, you're going to have to\n"
	.string "earn Battle Points first.$"
