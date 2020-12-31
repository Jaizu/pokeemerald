.set BCC_STATE_WHITE_OUT, 1

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
	map_script_2 VAR_VALOON_RESERVE_STATE, BCC_STATE_WHITE_OUT, ValoonReserve_EventScript_WhiteOut
	.2byte 0

ValoonReserve_EventScript_WhiteOut::
	setvar VAR_VALOON_RESERVE_STATE, 0
	goto ValoonReserve_EventScript_BugCatchingContestWhiteOut
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
