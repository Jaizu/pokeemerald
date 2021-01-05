.set LOCALID_CONTEST_HELPER, 1

ValoonTown_RangersHQ_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ValoonTown_RangersHQ_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, ValoonTown_RangersHQ_OnWarp
	.byte 0

ValoonTown_RangersHQ_OnFrame:
	map_script_2 VAR_RANGERS_HQ_STATE, 1, ValoonTown_RangersHQ_EventScript_ReturnFromContest
	.2byte 0

ValoonTown_RangersHQ_EventScript_ReturnFromContest:
	lockall
	msgbox ValoonTown_RangersHQ_Text_PleaseComeAgain, MSGBOX_DEFAULT
	closemessage
	setrespawn HEAL_LOCATION_VALOON_TOWN
	setvar VAR_RANGERS_HQ_STATE, 0
	releaseall
	end

ValoonTown_RangersHQ_OnWarp:
	map_script_2 VAR_RANGERS_HQ_STATE, 1, ValoonTown_RangersHQ_EventScript_PlayerTurnNorth
	.2byte 0

ValoonTown_RangersHQ_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

ValoonTown_RangersHQ_EventScript_ContestHelper::
	lock
	faceplayer
	goto_if_unset FLAG_NEMESIS_CAVE_RANGERS_RETURNED, ValoonTown_RangersHQ_EventScript_TheBugCatchingContestWillStartSoon
	msgbox ValoonTown_RangersHQ_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonTown_RangersHQ_EventScript_PleaseComeAgain
	setvar VAR_0x8004, 0
	getpartysize
	compare VAR_RESULT, 1
	call_if_ne ValoonTown_RangersHQ_EventScript_PleaseSelectAPokemon
	special EnterBugCatchingContestMode
	msgbox ValoonTown_RangersHQ_Text_HereAreTheParkBalls, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message ValoonTown_RangersHQ_Text_PlayerObtainedParkBalls
	waitfanfare
	msgbox ValoonTown_RangersHQ_Text_ExplainRules, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8008, VAR_0x8009
	compare VAR_0x8008, 9
	call_if_eq ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve0
	compare VAR_0x8008, 10
	call_if_eq ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve1
	compare VAR_0x8008, 11
	call_if_eq ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve2
	warp MAP_VALOON_RESERVE, 0, 0, 0
	waitstate
	release
	end

ValoonTown_RangersHQ_EventScript_PleaseSelectAPokemon:
	msgbox ValoonTown_RangersHQ_Text_PleaseSelectAPokemon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	compare VAR_RESULT, 255
	goto_if_eq ValoonTown_RangersHQ_EventScript_PleaseComeAgain
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq ValoonTown_RangersHQ_EventScript_CantCompeteWithAnEgg
	specialvar VAR_RESULT, IsSelectedMonHealthy
	compare VAR_RESULT, FALSE
	goto_if_eq ValoonTown_RangersHQ_EventScript_CantCompeteWithAFaintedPokemon
	bufferpartymonnick 0, VAR_0x8004
	msgbox ValoonTown_RangersHQ_Text_MonWillJoinYou, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonTown_RangersHQ_EventScript_PleaseSelectAPokemon
	playfanfare MUS_OBTAIN_ITEM
	message ValoonTown_RangersHQ_Text_PlayerLeftWithTheContestHelper
	waitfanfare
	return

ValoonTown_RangersHQ_EventScript_CantCompeteWithAnEgg:
	msgbox ValoonTown_RangersHQ_Text_CantCompeteWithAnEgg, MSGBOX_DEFAULT
	goto ValoonTown_RangersHQ_EventScript_PleaseSelectAPokemon
	end

ValoonTown_RangersHQ_EventScript_CantCompeteWithAFaintedPokemon:
	msgbox ValoonTown_RangersHQ_Text_CantCompeteWithAFaintedPokemon, MSGBOX_DEFAULT
	goto ValoonTown_RangersHQ_EventScript_PleaseSelectAPokemon
	end

ValoonTown_RangersHQ_EventScript_TheBugCatchingContestWillStartSoon:
	msgbox ValoonTown_RangersHQ_Text_TheBugCatchingContestWillStartSoon, MSGBOX_DEFAULT
	goto ValoonTown_RangersHQ_EventScript_PleaseComeAgain
	end

ValoonTown_RangersHQ_EventScript_PleaseComeAgain:
	msgbox ValoonTown_RangersHQ_Text_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve0:
	applymovement LOCALID_CONTEST_HELPER, Common_Movement_WalkRight
	waitmovement 0
	applymovement LOCALID_CONTEST_HELPER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ValoonTown_RangersHQ_Movement_PlayerEnterValoonReserve0
	waitmovement 0
	return

ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve1:
	applymovement LOCALID_CONTEST_HELPER, Common_Movement_WalkLeft
	waitmovement 0
	applymovement LOCALID_CONTEST_HELPER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ValoonTown_RangersHQ_Movement_PlayerEnterValoonReserve1
	waitmovement 0
	return

ValoonTown_RangersHQ_EventScript_PlayerEnterValoonReserve2:
	applymovement LOCALID_CONTEST_HELPER, Common_Movement_WalkLeft
	waitmovement 0
	applymovement LOCALID_CONTEST_HELPER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ValoonTown_RangersHQ_Movement_PlayerEnterValoonReserve2
	waitmovement 0
	return

ValoonTown_RangersHQ_Text_WouldYouLikeToEnter:
	.string "Would you like to enter the\n"
	.string "Bug-Catching Contest?$"

ValoonTown_RangersHQ_Text_PleaseSelectAPokemon:
	.string "Please select one Pokémon to\n"
	.string "take with you.$"

ValoonTown_RangersHQ_Text_CantCompeteWithAnEgg:
	.string "You cannot compete with an Egg!$"

ValoonTown_RangersHQ_Text_CantCompeteWithAFaintedPokemon:
	.string "You cannot compete with a\n"
	.string "Pokémon that has fainted!$"

ValoonTown_RangersHQ_Text_MonWillJoinYou:
	.string "{STR_VAR_1} will join you.\p"
	.string "I will look after your other\n"
	.string "Pokémon. Is this okay?$"

ValoonTown_RangersHQ_Text_PlayerLeftWithTheContestHelper:
	.string "{COLOR DARK_GREY}{PLAYER}'s Pokémon were\n"
	.string "left with the Contest Helper.$"

ValoonTown_RangersHQ_Text_HereAreTheParkBalls:
	.string "Here are the Park Balls for\n"
	.string "the Contest.$"

ValoonTown_RangersHQ_Text_PlayerObtainedParkBalls:
	.string "{COLOR DARK_GREY}Obtained 20 Park Balls!$"

ValoonTown_RangersHQ_Text_ExplainRules:
	.string "The person who gets the strongest\n"
	.string "Bug-type Pokémon is the winner.\p"
	.string "If you white out or run out of\n"
	.string "Park Balls, you're done.\p"
	.string "You can keep the last Pokémon you\n"
	.string "catch as your own.\p"
	.string "Good luck out there!$"

ValoonTown_RangersHQ_Text_TheBugCatchingContestWillStartSoon:
	.string "The Bug-Catching Contest will\n"
	.string "start once the other Rangers get\l"
	.string "back from Nemesis Cave.$"

ValoonTown_RangersHQ_Text_PleaseComeAgain:
	.string "{COLOR BLUE}Please come again.$"

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

ValoonTown_RangersHQ_EventScript_BulletinBoard::
	msgbox ValoonTown_RangersHQ_Text_BulletinBoard, MSGBOX_SIGN
	end

ValoonTown_RangersHQ_Text_BulletinBoard:
	.string "It is a bulletin board.$"

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
	.string "low-scoring Pokémon like Combee!$"

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
