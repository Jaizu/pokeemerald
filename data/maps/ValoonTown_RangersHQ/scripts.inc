.set LOCALID_CONTEST_CLERK, 1

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
	goto_if_unset FLAG_NEMESIS_CAVE_RANGERS_RETURNED, ValoonTown_RangersHQ_EventScript_TheBugCatchingContestWillStartSoon
	msgbox ValoonTown_RangersHQ_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonTown_RangersHQ_EventScript_PleaseComeAgain
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq ValoonTown_RangersHQ_EventScript_PleaseMakeRoom
	call_if_unset FLAG_RECEIVED_FREE_PARK_BALLS, ValoonTown_RangersHQ_EventScript_TryGiveFreeParkBalls
	msgbox ValoonTown_RangersHQ_Text_TheContestWillBeginSoon, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8008, VAR_0x8009
	compare VAR_0x8008, 9
	call_if_eq ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve0
	compare VAR_0x8008, 10
	call_if_eq ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve1
	compare VAR_0x8008, 11
	call_if_eq ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve2
	// TODO: Add the Valoon Reserve map
	// warp VALOON_RESERVE, 0, 0, 0
	// waitstate
	release
	end

ValoonTown_RangersHQ_EventScript_PleaseMakeRoom:
	msgbox ValoonTown_RangersHQ_Text_PleaseMakeRoom, MSGBOX_DEFAULT
	release
	end

ValoonTown_RangersHQ_EventScript_TryGiveFreeParkBalls:
	msgbox ValoonTown_RangersHQ_Text_AsThisIsYourFirstTime, MSGBOX_DEFAULT
	giveitem ITEM_PARK_BALL, 15
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_FREE_PARK_BALLS
	msgbox ValoonTown_RangersHQ_Text_YouCanBuyMore, MSGBOX_DEFAULT
	return

ValoonTown_RangersHQ_EventScript_PleaseComeAgain:
	msgbox ValoonTown_RangersHQ_Text_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

ValoonTown_RangersHQ_EventScript_TheBugCatchingContestWillStartSoon:
	msgbox ValoonTown_RangersHQ_Text_TheBugCatchingContestWillStartSoon, MSGBOX_DEFAULT
	release
	end

ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve0:
	applymovement LOCALID_CONTEST_CLERK, Common_Movement_WalkRight
	waitmovement 0
	applymovement LOCALID_CONTEST_CLERK, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ValoonTown_RangersHQ_Movement_PlayerEnterValoonReserve0
	waitmovement 0
	return

ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve1:
	applymovement LOCALID_CONTEST_CLERK, Common_Movement_WalkLeft
	waitmovement 0
	applymovement LOCALID_CONTEST_CLERK, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ValoonTown_RangersHQ_Movement_PlayerEnterValoonReserve1
	waitmovement 0
	return

ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve2:
	applymovement LOCALID_CONTEST_CLERK, Common_Movement_WalkLeft
	waitmovement 0
	applymovement LOCALID_CONTEST_CLERK, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ValoonTown_RangersHQ_Movement_PlayerEnterValoonReserve2
	waitmovement 0
	return

ValoonTown_RangersHQ_Text_WouldYouLikeToEnter:
	.string "Would you like to enter the\n"
	.string "Bug-Catching Contest?$"

ValoonTown_RangersHQ_Text_PleaseMakeRoom:
	.string "Your party appears to be full.\n"
	.string "Please make room before we begin.$"

ValoonTown_RangersHQ_Text_AsThisIsYourFirstTime:
	.string "As this is your first time, take\n"
	.string "these complementary Park Balls!$"

ValoonTown_RangersHQ_Text_YouCanBuyMore:
	.string "Park Balls are special Balls that\n"
	.string "perform best in the Valoon Reserve.\p"
	.string "You can buy more from my colleague\n"
	.string "over by the computer.$"

ValoonTown_RangersHQ_Text_TheContestWillBeginSoon:
	.string "Great! Go on through, the contest\n"
	.string "will begin soon!$"

ValoonTown_RangersHQ_Text_PleaseComeAgain:
	.string "Please come again.$"

ValoonTown_RangersHQ_Text_TheBugCatchingContestWillStartSoon:
	.string "The Bug-Catching Contest will\n"
	.string "start once the other Rangers get\l"
	.string "back from Nemesis Cave.$"

ValoonTown_RangersHQ_Movement_PlayerEnterValoonReserve0:
	walk_right
	walk_up
	set_invisible
	step_end

ValoonTown_RangersHQ_Movement_PlayerEnterValoonReserve1:
	walk_up
	walk_up
	set_invisible
	step_end

ValoonTown_RangersHQ_Movement_PlayerEnterValoonReserve2:
	walk_left
	walk_up
	set_invisible
	step_end

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
	goto_if_set FLAG_NEMESIS_CAVE_RANGERS_RETURNED, ValoonTown_RangersHQ_EventScript_ImGoingToEnter
	msgbox ValoonTown_RangersHQ_Text_HeyThere, MSGBOX_DEFAULT
	release
	end

ValoonTown_RangersHQ_EventScript_ImGoingToEnter:
	msgbox ValoonTown_RangersHQ_Text_ImGoingToEnter, MSGBOX_DEFAULT
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

ValoonTown_RangersHQ_Text_ImGoingToEnter:
	.string "{COLOR DARK_GREY}Vernon: {COLOR BLUE}Hey there!\p"
	.string "I'm going to enter in the next\n"
	.string "Bug-Catching Contest.$"
