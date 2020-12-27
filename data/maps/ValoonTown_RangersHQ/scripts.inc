ValoonTown_RangersHQ_MapScripts::
	.byte 0

ValoonTown_RangersHQ_EventScript_BulletinBoard::
	msgbox ValoonTown_RangersHQ_Text_BulletinBoard, MSGBOX_SIGN
	end

ValoonTown_RangersHQ_Text_BulletinBoard:
	.string "It is a bulletin board.$"

ValoonTown_RangersHQ_EventScript_ContestClerk::
	lock
	faceplayer
	msgbox ValoonTown_RangersHQ_Text_TheBugCatchingContestWillStartSoon, MSGBOX_DEFAULT
	release
	end

ValoonTown_RangersHQ_Text_TheBugCatchingContestWillStartSoon:
	.string "The Bug-Catching Contest will\n"
	.string "start once the other Rangers get\l"
	.string "back from Nemesis Cave.$"

ValoonTown_RangersHQ_EventScript_ParkBallSalesman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_FREE_PARK_BALLS, ValoonTown_RangersHQ_EventScript_TrySellParkBalls
	msgbox ValoonTown_RangersHQ_Text_ExplainParkBalls, MSGBOX_DEFAULT
	giveitem ITEM_PARK_BALL, 15
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FREE_PARK_BALLS
	msgbox ValoonTown_RangersHQ_Text_IfYouRunOut, MSGBOX_DEFAULT
	release
	end

ValoonTown_RangersHQ_EventScript_TrySellParkBalls::
	message ValoonTown_RangersHQ_Text_WouldYouLikeToBuyParkBalls
	waitmessage
	pokemart ValoonTown_RangersHQ_Pokemart_ParkBalls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

ValoonTown_RangersHQ_Text_ExplainParkBalls:
	.string "Welcome to the Valoon Rangers HQ!\n"
	.string "We sell Park Balls here.\p"
	.string "They are Poké Balls which are more\n"
	.string "effective in the Valoon Reserve.\p"
	.string "Here, take some for free!$"

ValoonTown_RangersHQ_Text_IfYouRunOut:
	.string "If you run out of Park Balls, come\n"
	.string "talk to me!$"

ValoonTown_RangersHQ_Text_WouldYouLikeToBuyParkBalls:
	.string "Hi, there!\n"
	.string "Would you like to buy Park Balls?$"

ValoonTown_RangersHQ_Pokemart_ParkBalls::
	.2byte ITEM_PARK_BALL
	.2byte ITEM_NONE
	release
	end

ValoonTown_RangersHQ_EventScript_PkmnRangerF1::
	msgbox ValoonTown_RangersHQ_Text_ThereDontSeemToBeAnyNewMissions, MSGBOX_NPC
	end

ValoonTown_RangersHQ_Text_ThereDontSeemToBeAnyNewMissions:
	.string "There don't seem to be any new\n"
	.string "missions…$"

ValoonTown_RangersHQ_EventScript_PkmnRangerM::
	msgbox ValoonTown_RangersHQ_Text_IWishICouldHaveGone, MSGBOX_NPC
	end

ValoonTown_RangersHQ_Text_IWishICouldHaveGone:
	.string "I wish I could've gone to\n"
	.string "Nemesis Cave with those guys…$"

ValoonTown_RangersHQ_EventScript_BugCatcher::
	msgbox ValoonTown_RangersHQ_Text_ExplainBugCatchingContestRules, MSGBOX_NPC
	end

ValoonTown_RangersHQ_Text_ExplainBugCatchingContestRules:
	.string "The first Pokémon you capture in\n"
	.string "the Bug-Catching Contest is the\l"
	.string "one you enter, so choose wisely!$"

ValoonTown_RangersHQ_EventScript_AceTrainerF::
	msgbox ValoonTown_RangersHQ_Text_AlwaysGetLowScoringBugs, MSGBOX_NPC
	end

ValoonTown_RangersHQ_Text_AlwaysGetLowScoringBugs:
	.string "Are you going to enter the\n"
	.string "Bug-Catching Contest?\p"
	.string "I would, but I only ever find\n"
	.string "low-scoring Pokémon like Weedle!$"

ValoonTown_RangersHQ_EventScript_PkmnRangerF2::
	msgbox ValoonTown_RangersHQ_Text_AreYouANewRecruit, MSGBOX_NPC
	end

ValoonTown_RangersHQ_Text_AreYouANewRecruit:
	.string "Are you a new recruit?\n"
	.string "Didn't think so…$"

ValoonTown_RangersHQ_EventScript_Vernon::
	lock
	faceplayer
	msgbox ValoonTown_RangersHQ_Text_HeyThere, MSGBOX_DEFAULT
	release
	end

ValoonTown_RangersHQ_Text_HeyThere:
	.string "Why, hey there!\n"
	.string "I'm the Valoon Gym Leader, Vernon.\p"
	.string "I'm taking a break from my Gym for\n"
	.string "a little while.\p"
	.string "I want to enter the Bug-Catching\n"
	.string "Contest, but…\p"
	.string "We have to wait until those\n"
	.string "Rangers get back, first.\p"
	.string "I think they were headed to\n"
	.string "Nemesis Cave.$"
