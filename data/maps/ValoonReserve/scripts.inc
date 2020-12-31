.set BCC_STATE_WHITE_OUT, 	  1
.set BCC_STATE_JUDGING_ROUND, 2

ValoonReserve_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, ValoonReserve_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ValoonReserve_OnFrame
	.byte 0

ValoonReserve_OnResume:
	special GetClearBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq ValoonReserve_EventScript_TriggerWhiteOut
	end

ValoonReserve_EventScript_TriggerWhiteOut:
	setvar VAR_VALOON_RESERVE_STATE, BCC_STATE_WHITE_OUT
	end

ValoonReserve_OnFrame:
	map_script_2 VAR_VALOON_RESERVE_STATE, BCC_STATE_WHITE_OUT, 	ValoonReserve_EventScript_WhiteOut
	map_script_2 VAR_VALOON_RESERVE_STATE, BCC_STATE_JUDGING_ROUND, ValoonReserve_EventScript_JudgingRound
	.2byte 0

ValoonReserve_EventScript_WhiteOut::
	setvar VAR_VALOON_RESERVE_STATE, 0
	goto ValoonReserve_EventScript_BugCatchingContestWhiteOut
	end

ValoonReserve_EventScript_JudgingRound::
	setvar VAR_VALOON_RESERVE_STATE, 0
	goto ValoonReserve_EventScript_BugCatchingContestJudgingRound
	end

ValoonReserve_EventScript_BugCatchingContestWhiteOut::
	message ValoonReserve_Text_PlayerIsOutOfUsablePokemon
	waitmessage
	waitbuttonpress
	special LoadPlayerParty
	setrespawn HEAL_LOCATION_VALOON_TOWN_RANGERS_HQ
	special Script_FadeOutMapMusic
	waitstate
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate
	end

ValoonReserve_Text_PlayerIsOutOfUsablePokemon:
	.string "Announcer: {COLOR BLUE}Oh dear!\n"
	.string "We have a disqualification!\p"
	.string "{PLAYER} is out of usable\n"
	.string "Pokémon, and therefore forfeits!\p"
	.string "Better luck next time!$"

ValoonReserve_EventScript_BugCatchingContestJudgingRound::
	fadescreen FADE_TO_BLACK
	setobjectxy OBJ_EVENT_ID_PLAYER, 27, 10
	setobjectxyperm OBJ_EVENT_ID_PLAYER, 27, 10
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	fadescreen FADE_FROM_BLACK
	// TODO: Implement
	end

ValoonReserve_EventScript_ForfeitClerk::
	lock
	faceplayer
	msgbox ValoonReserve_Text_WouldYouLikeToForfeit, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonReserve_EventScript_GoCatchTheBestBug
	msgbox ValoonReserve_Text_PleaseComeBackSoon, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_SYS_NO_PAYOUT
	special LoadPlayerParty
	warp MAP_VALOON_TOWN_RANGERS_HQ, 255, 10, 3
	waitstate
	release
	end

ValoonReserve_Text_WouldYouLikeToForfeit:
	.string "Would you like to forfeit?$"

ValoonReserve_Text_PleaseComeBackSoon:
	.string "Alright, then.\n"
	.string "Please come back soon!$"

ValoonReserve_EventScript_Judge::
	lock
	faceplayer
	specialvar VAR_RESULT, PlayerHasCaughtBug
	compare VAR_RESULT, FALSE
	goto_if_eq ValoonReserve_EventScript_GoCatchTheBestBug
	msgbox ValoonReserve_Text_WouldYouLikeToBeginTheJudgingRound, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonReserve_EventScript_GoCatchTheBestBug
	msgbox ValoonReserve_Text_VeryWell, MSGBOX_DEFAULT
	closemessage
	setvar VAR_VALOON_RESERVE_STATE, BCC_STATE_JUDGING_ROUND
	release
	end

ValoonReserve_Text_WouldYouLikeToBeginTheJudgingRound:
	.string "Would you like to begin the\n"
	.string "judging round?$"

ValoonReserve_Text_VeryWell:
	.string "Very well!\n"
	.string "I will gather the contestants.$"

ValoonReserve_EventScript_GoCatchTheBestBug::
	msgbox ValoonReserve_Text_GoCatchTheBestBug, MSGBOX_DEFAULT
	release
	end

ValoonReserve_Text_GoCatchTheBestBug:
	.string "Go out there and catch the\n"
	.string "strongest Bug-type you can find!$"
