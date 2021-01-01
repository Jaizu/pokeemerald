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
	map_script_2 VAR_VALOON_RESERVE_STATE, BCC_STATE_WHITE_OUT,     ValoonReserve_EventScript_WhiteOut
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
	setvar VAR_RANGERS_HQ_STATE, 1
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
	.string "Pokémon, and therefore Retires!\p"
	.string "Better luck next time!$"

ValoonReserve_EventScript_BugCatchingContestJudgingRound::
	textcolor 0 // Blue
	fadescreen FADE_TO_BLACK
	setobjectxy OBJ_EVENT_ID_PLAYER, 27, 10
	setobjectxyperm OBJ_EVENT_ID_PLAYER, 27, 10
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	fadescreen FADE_FROM_BLACK
	msgbox ValoonReserve_Text_WeWillNowJudgeThePokemon, MSGBOX_DEFAULT
	// TODO: Implement
	msgbox ValoonReserve_Text_ThankYouAllForCompeting, MSGBOX_DEFAULT
	goto ValoonReserve_EventScript_Retire
	end

ValoonReserve_Text_WeWillNowJudgeThePokemon:
	.string "We will now judge the Pokémon\n"
	.string "you have caught.\p"
	.string "… …\n"
	.string "… …\p"
	.string "We have chosen the winners!\n"
	.string "Are you ready for this?$"

ValoonReserve_Text_ThankYouAllForCompeting:
	.string "Thank you all for competing!\n"
	.string "We hope to see you again.$"

ValoonReserve_EventScript_RetirePrompt::
	lockall
	msgbox ValoonReserve_Text_WouldYouLikeToExit, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq ValoonReserve_EventScript_Retire
	releaseall
	end

ValoonReserve_EventScript_Retire:
	setvar VAR_RANGERS_HQ_STATE, 1
	warp MAP_VALOON_TOWN_RANGERS_HQ, 255, 10, 3
	waitstate
	releaseall
	end

ValoonReserve_Text_WouldYouLikeToExit:
	.string "Would you like to exit?$"

ValoonReserve_EventScript_RetireClerk::
	lock
	faceplayer
	msgbox ValoonReserve_Text_WouldYouLikeToExit, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonReserve_EventScript_GoCatchTheBestBug
	msgbox ValoonReserve_Text_PleaseComeBackSoon, MSGBOX_DEFAULT
	closemessage
	goto ValoonReserve_EventScript_Retire
	end

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
