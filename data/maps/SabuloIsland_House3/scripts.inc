SabuloIsland_House3_MapScripts::
	.byte 0

SabuloIsland_House3_EventScript_Reuben::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_GOOD_ROD, SabuloIsland_House3_EventScript_MyLifeWillBeDull
	goto_if_set TRAINER_FLAGS_START + TRAINER_REUBEN, SabuloIsland_House3_EventScript_TryGiveGoodRod
	msgbox SabuloIsland_House3_Text_DoYouWantABattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne SabuloIsland_House3_EventScript_DeclineReuben
	msgbox SabuloIsland_House3_Text_LetsDoThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_REUBEN, SabuloIsland_House3_Text_ReubenDefeat
	goto SabuloIsland_House3_EventScript_TryGiveGoodRod
	end

SabuloIsland_House3_EventScript_DeclineReuben:
	msgbox SabuloIsland_House3_Text_HahaSoYoureJustACoward, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloIsland_House3_EventScript_TryGiveGoodRod:
	msgbox SabuloIsland_House3_Text_SoYouBeatMe, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne SabuloIsland_House3_EventScript_DeclineGoodRod
	giveitem ITEM_GOOD_ROD
	setflag FLAG_RECEIVED_GOOD_ROD
	goto SabuloIsland_House3_EventScript_MyLifeWillBeDull
	end

SabuloIsland_House3_EventScript_DeclineGoodRod:
	msgbox SabuloIsland_House3_Text_OhHowMerciful, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloIsland_House3_EventScript_MyLifeWillBeDull:
	msgbox SabuloIsland_House3_Text_MyLifeWillBeDull, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloIsland_House3_Text_DoYouWantABattle:
	.string "Do you want a battle?\p"
	.string "…\p"
	.string "Your expression looks like you\n"
	.string "don't want to.\p"
	.string "I'll up the ante, then!\p"
	.string "If you win, I'll hand over my\n"
	.string "prized fishing rod.\p"
	.string "What do you say?$"

SabuloIsland_House3_Text_HahaSoYoureJustACoward:
	.string "Haha!\n"
	.string "So you're just a coward, then?$"

SabuloIsland_House3_Text_LetsDoThis:
	.string "Let's do this!\n"
	.string "The stakes are sky-high!$"

SabuloIsland_House3_Text_ReubenDefeat:
	.string "Oh… oh no!\n"
	.string "My fishing rod!$"

SabuloIsland_House3_Text_SoYouBeatMe:
	.string "So, you beat me!\n"
	.string "Fair enough…\p"
	.string "Do you want to take my Good Rod,\n"
	.string "then?$"

SabuloIsland_House3_Text_OhHowMerciful:
	.string "Oh, thank you!\n"
	.string "How merciful of you!$"

SabuloIsland_House3_Text_MyLifeWillBeDull:
	.string "I'm a man of my word, but my life\n"
	.string "will be dull without fishing…$"

SabuloIsland_House3_EventScript_AceTrainerF::
	lock
	faceplayer
	msgbox SabuloIsland_House3_Text_HmIThinkINeedSurf, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SabuloIsland_House3_Text_HmIThinkINeedSurf:
	.string "Hm, I think if I want to get to\n"
	.string "Valoon Town I'll need HM03 Surf…$"
