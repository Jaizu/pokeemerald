SabuloIsland_House4_MapScripts::
	.byte 0

SabuloIsland_House4_EventScript_AceTrainerM::
	msgbox SabuloIsland_House4_Text_BelleIsSoBeautiful, MSGBOX_NPC
	end

SabuloIsland_House4_Text_BelleIsSoBeautiful:
	.string "Belle is so beautiful, and\n"
	.string "powerful, and smart.\p"
	.string "She terrifies me!$"

SabuloIsland_House4_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SABULO_ISLAND_TWISTED_SPOON, SabuloIsland_House4_EventScript_ReceivedTwistedSpoon
	msgbox SabuloIsland_House4_Text_AwIBrokeMySpoon, MSGBOX_DEFAULT
	giveitem ITEM_TWISTED_SPOON
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SABULO_ISLAND_TWISTED_SPOON
	goto SabuloIsland_House4_EventScript_ReceivedTwistedSpoon
	end

SabuloIsland_House4_EventScript_ReceivedTwistedSpoon:
	msgbox SabuloIsland_House4_Text_DidYouKnowPsychicTypesCanTwistSpoons, MSGBOX_DEFAULT
	release
	end

SabuloIsland_House4_Text_AwIBrokeMySpoon:
	.string "Aw, I broke my spoon!\n"
	.string "You can have it I guess.$"

SabuloIsland_House4_Text_DidYouKnowPsychicTypesCanTwistSpoons:
	.string "Did you know Psychic-types can\n"
	.string "twist spoons with their powers?$"
