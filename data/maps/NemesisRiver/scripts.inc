// TODO: Create Broken Tool item
.set ITEM_BROKEN_TOOL, ITEM_FULL_RESTORE

NemesisRiver_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, NemesisRiver_OnResume
	.byte 0

NemesisRiver_OnResume:
	call_if_unset FLAG_CLEAR_PATH_TO_SECRET_LAB, NemesisRiver_EventScript_ClearPathToSecretLab
	end

NemesisRiver_EventScript_ClearPathToSecretLab:
	setmetatile 49, 16, METATILE_Lavaridge_BarbedWireFence_Top, 0
	setmetatile 50, 16, METATILE_Lavaridge_BarbedWireFence_Top, 0
	setmetatile 51, 16, METATILE_Lavaridge_BarbedWireFence_Top, 0
	setmetatile 49, 17, METATILE_Lavaridge_BarbedWireFence_Bottom, 1
	setmetatile 50, 17, METATILE_Lavaridge_BarbedWireFence_Bottom, 1
	setmetatile 51, 17, METATILE_Lavaridge_BarbedWireFence_Bottom, 1
	return

NemesisRiver_EventScript_RouteSign::
	msgbox NemesisRiver_Text_RouteSign, MSGBOX_SIGN
	end

NemesisRiver_Text_RouteSign::
	.string "Nemesis River\n"
	.string "{UP_ARROW} Nemesis Cave {DOWN_ARROW} Valoon Town$"

NemesisRiver_EventScript_Wendy::
	trainerbattle_single TRAINER_WENDY_1, NemesisRiver_Text_WendyIntro, NemesisRiver_Text_WendyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq NemesisRiver_EventScript_WendyRematch
	msgbox NemesisRiver_Text_WendyPostBattle, MSGBOX_DEFAULT
	release
	end

NemesisRiver_EventScript_WendyRematch::
	trainerbattle_rematch TRAINER_WENDY_1, NemesisRiver_Text_WendyIntro, NemesisRiver_Text_WendyDefeat
	msgbox NemesisRiver_Text_WendyPostBattle, MSGBOX_AUTOCLOSE
	end

NemesisRiver_Text_WendyIntro:
	.string "I'm tasked with protecting the\n"
	.string "wilderness.\p"
	.string "All threats must be terminated!$"

NemesisRiver_Text_WendyDefeat:
	.string "Hopefully you aren't a threat…$"

NemesisRiver_Text_WendyPostBattle:
	.string "The wilderness must be kept safe!\n"
	.string "That is my duty as a Ranger.$"

NemesisRiver_EventScript_Scientist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_VS_SEEKER, NemesisRiver_EventScript_ExplainVSSeeker
	goto_if_set FLAG_ITEM_TELMURK_SWAMP_BROKEN_TOOL, NemesisRiver_EventScript_GiveVSSeeker
	msgbox NemesisRiver_Text_ILostMyTool, MSGBOX_DEFAULT
	release
	end

NemesisRiver_EventScript_GiveVSSeeker:
	msgbox NemesisRiver_Text_OhYouSayYouveFoundIt, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_W231 // SE_M_HARDEN
	waitse
	delay 10
	fadescreen FADE_FROM_BLACK
	msgbox NemesisRiver_Text_ThereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_VS_SEEKER
	removeitem ITEM_BROKEN_TOOL
	setflag FLAG_RECEIVED_VS_SEEKER
	msgbox NemesisRiver_Text_IGuessIllBuyANewTool, MSGBOX_DEFAULT
	goto NemesisRiver_EventScript_ExplainVSSeeker
	end

NemesisRiver_EventScript_ExplainVSSeeker:
	msgbox NemesisRiver_Text_ExplainVSSeeker, MSGBOX_DEFAULT
	release
	end

NemesisRiver_Text_ILostMyTool:
	.string "I think I lost my tool somewhere,\n"
	.string "in Telmurk Swamp.\p"
	.string "I have no Pokémon, so I can't risk\n"
	.string "going back there.\p"
	.string "If you find it, please, come\n"
	.string "here and return it to me!$"

NemesisRiver_Text_OhYouSayYouveFoundIt:
	.string "Oh, you say you've found it?\p"
	.string "… … …\p"
	.string "…That isn't my tool.\p"
	.string "That's a {COLOR GREEN}VS Seeker{COLOR BLUE}.\n"
	.string "It appears to be broken, too.\p"
	.string "I guess someone like you wouldn't\n"
	.string "know the difference.\p"
	.string "I have no use for this, so I guess\n"
	.string "I will fix it for you.$"

NemesisRiver_Text_ThereYouGo:
	.string "There you go!$"

NemesisRiver_Text_IGuessIllBuyANewTool:
	.string "I guess I will have to purchase a\n"
	.string "new tool. Thanks for nothing…$"

NemesisRiver_Text_ExplainVSSeeker:
	.string "You know how that VS Seeker works,\n"
	.string "right?\p"
	.string "The battery gets charged by just\n"
	.string "walking around.\p"
	.string "Once you have enough charge, use it\n"
	.string "to signal to nearby Trainers that\l"
	.string "you want to battle.\p"
	.string "If they are receptive, they'll let\n"
	.string "you know! Easy, right?$"

NemesisRiver_EventScript_Rocker::
	msgbox NemesisRiver_Text_ExplainNemesisCaveName, MSGBOX_NPC
	end

NemesisRiver_Text_ExplainNemesisCaveName:
	.string "They call it Nemesis Cave because\n"
	.string "of the rivaling Durant and Heatmor.$"
