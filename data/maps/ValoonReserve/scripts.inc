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

ValoonReserve_EventScript_OutOfBallsMidBattle::
	specialvar VAR_RESULT, PlayerHasCaughtBug
	compare VAR_RESULT, TRUE
	goto_if_eq ValoonReserve_EventScript_OutOfBallsBeginJudging
	setvar VAR_VALOON_RESERVE_STATE, 0
	msgbox ValoonReserve_Text_OutOfBallsNothingCaught, MSGBOX_DEFAULT
	closemessage
	goto ValoonReserve_EventScript_Retire
	end

ValoonReserve_Text_OutOfBallsNothingCaught:
	.string "Announcer: {COLOR BLUE}Oh dear!\n"
	.string "We have a disqualification!\p"
	.string "{PLAYER} is out of Park Balls, and\n"
	.string "has not caught anything!\p"
	.string "Better luck next time!$"

ValoonReserve_EventScript_OutOfBallsBeginJudging::
	msgbox ValoonReserve_Text_OutOfBallsBeginJudging, MSGBOX_DEFAULT
	closemessage
	setvar VAR_VALOON_RESERVE_STATE, BCC_STATE_JUDGING_ROUND
	end

ValoonReserve_Text_OutOfBallsBeginJudging:
	.string "Announcer: {COLOR BLUE}{PLAYER} is out of\n"
	.string "Park Balls, and so must stop!\p"
	.string "Please wait for the Judging Round\n"
	.string "to begin.$"

ValoonReserve_EventScript_BugCatchingContestWhiteOut::
	message ValoonReserve_Text_PlayerIsOutOfUsablePokemon
	waitmessage
	waitbuttonpress
	special ExitBugCatchingContestMode
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
	.string "Pokémon, and therefore retires!\p"
	.string "Better luck next time!$"

ValoonReserve_EventScript_BugCatchingContestJudgingRound::
	specialvar VAR_RESULT, IsVernonCompeting
	compare VAR_RESULT, TRUE
	call_if_eq ValoonReserve_EventScript_UnlockValoonGym
	special ExitBugCatchingContestMode
	textcolor 0 // Blue
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 27 @ x
	setvar VAR_0x8005, 8  @ y
	special TeleportCamera
	setobjectxy OBJ_EVENT_ID_PLAYER, 27, 10
	setobjectxyperm OBJ_EVENT_ID_PLAYER, 27, 10
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	fadescreen FADE_FROM_BLACK
	msgbox ValoonReserve_Text_WeWillNowJudgeThePokemon, MSGBOX_DEFAULT
	special SelectBugCatchingContestWinners
	setvar VAR_RESULT, 0
	special BufferBugCatchingContestStrings
	msgbox ValoonReserve_Text_PlacingThirdIs, MSGBOX_DEFAULT
	special BufferBugCatchingContestScore
	msgbox ValoonReserve_Text_TheScoreWas, MSGBOX_DEFAULT
	setvar VAR_RESULT, 1
	special BufferBugCatchingContestStrings
	msgbox ValoonReserve_Text_PlacingSecondIs, MSGBOX_DEFAULT
	special BufferBugCatchingContestScore
	msgbox ValoonReserve_Text_TheScoreWas, MSGBOX_DEFAULT
	setvar VAR_RESULT, 2
	special BufferBugCatchingContestStrings
	msgbox ValoonReserve_Text_ThisBugCatchingContestWinnerIs, MSGBOX_DEFAULT
	special BufferBugCatchingContestScore
	msgbox ValoonReserve_Text_TheScoreWas, MSGBOX_DEFAULT
	msgbox ValoonReserve_Text_ThankYouAllForCompeting, MSGBOX_DEFAULT
	textcolor 2 // Dark Grey
	special BufferCaughtBugSpecies
	specialvar VAR_RESULT, GiveAndResetCaughtBug
	compare VAR_RESULT, 0
	goto_if_eq ValoonReserve_EventScript_ReceiveCaughtBugParty
	compare VAR_RESULT, 1
	goto_if_eq ValoonReserve_EventScript_ReceiveCaughtBugPC
	msgbox gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
	goto ValoonReserve_EventScript_Exit
	end

ValoonReserve_EventScript_ReceiveCaughtBugParty::
	msgbox ValoonReserve_Text_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ValoonReserve_EventScript_Exit
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto ValoonReserve_EventScript_Exit
	end

ValoonReserve_EventScript_ReceiveCaughtBugPC::
	msgbox ValoonReserve_Text_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ValoonReserve_EventScript_SendCaughtBugToPC
	call Common_EventScript_NameReceivedBoxMon
	goto ValoonReserve_EventScript_SendCaughtBugToPC
	end

ValoonReserve_EventScript_SendCaughtBugToPC::
	call Common_EventScript_TransferredToPC
	goto ValoonReserve_EventScript_Exit
	end

ValoonReserve_Text_WeWillNowJudgeThePokemon:
	.string "We will now judge the Pokémon\n"
	.string "you have caught.\p"
	.string "… …\n"
	.string "… …\p"
	.string "We have chosen the winners!\n"
	.string "Are you ready for this?$"

ValoonReserve_Text_PlacingThirdIs:
	.string "Placing third is {STR_VAR_1}\n"
	.string "{STR_VAR_2}, who caught a writhing\l"
	.string "{STR_VAR_3}!$"

ValoonReserve_Text_PlacingSecondIs:
	.string "Placing second is {STR_VAR_1}\n"
	.string "{STR_VAR_2}, who caught a wriggling\l"
	.string "{STR_VAR_3}!$"

ValoonReserve_Text_ThisBugCatchingContestWinnerIs:
	.string "This Bug-Catching Contest winner is…\p"
	.string "{STR_VAR_1} {STR_VAR_2}, who\n"
	.string "caught a whopping {STR_VAR_3}!$"

ValoonReserve_Text_TheScoreWas:
	.string "The score was {STR_VAR_1} points!$"

ValoonReserve_Text_ThankYouAllForCompeting:
	.string "We'll return the Pokémon we kept\n"
	.string "for you. Here you go!\p"
	.string "Thank you all for competing!\n"
	.string "We hope to see you again.$"

ValoonReserve_Text_NicknameThisPokemon:
	.string "Would you like to give a nickname\n"
	.string "to the {STR_VAR_1} you caught?$"

ValoonReserve_EventScript_UnlockValoonGym:
	setflag FLAG_UNLOCK_VALOON_GYM_DOOR
	setflag FLAG_HIDE_VALOON_TOWN_RANGERS_HQ_VERNON
	return

ValoonReserve_EventScript_RetirePrompt::
	lockall
	msgbox ValoonReserve_Text_WouldYouLikeToExit, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq ValoonReserve_EventScript_Retire
	releaseall
	end

ValoonReserve_EventScript_Retire:
	special ExitBugCatchingContestMode
	goto ValoonReserve_EventScript_Exit
	end

ValoonReserve_EventScript_Exit:
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
	goto_if_ne ValoonReserve_EventScript_TryPromptJudgingRound
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
	goto ValoonReserve_EventScript_TryPromptJudgingRound
	end

ValoonReserve_EventScript_TryPromptJudgingRound::
	specialvar VAR_RESULT, PlayerHasCaughtBug
	compare VAR_RESULT, FALSE
	goto_if_eq ValoonReserve_EventScript_GoCatchTheBestBug
	msgbox ValoonReserve_Text_AreYouReadyForJudging, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonReserve_EventScript_GoCatchTheBestBug
	msgbox ValoonReserve_Text_VeryWell, MSGBOX_DEFAULT
	closemessage
	setvar VAR_VALOON_RESERVE_STATE, BCC_STATE_JUDGING_ROUND
	release
	end

ValoonReserve_Text_AreYouReadyForJudging:
	.string "Are you ready for the Judging Round\n"
	.string "to begin?$"

ValoonReserve_Text_VeryWell:
	.string "Very well! Please wait here for the\n"
	.string "Judging Round to begin.$"

ValoonReserve_EventScript_GoCatchTheBestBug::
	msgbox ValoonReserve_Text_GoCatchTheBestBug, MSGBOX_DEFAULT
	release
	end

ValoonReserve_Text_GoCatchTheBestBug:
	.string "Go out there and catch the\n"
	.string "strongest Bug-type you can find!$"
