RimewoodForest_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, RimewoodForest_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, RimewoodForest_OnTransition
	.byte 0

RimewoodForest_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, RimewoodForest_TryRemoveAbomasnow
	end

RimewoodForest_TryRemoveAbomasnow:
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

RimewoodForest_OnTransition:
	call_if_unset FLAG_DEFEATED_RIMEWOOD_FOREST_ABOMASNOW, RimewoodForest_EventScript_TryShowAbomasnow
	end

RimewoodForest_EventScript_TryShowAbomasnow:
	goto_if_unset FLAG_CAUGHT_RIMEWOOD_FOREST_ABOMASNOW, RimewoodForest_EventScript_ShowAbomasnow
	return
 
RimewoodForest_EventScript_ShowAbomasnow:
	clearflag FLAG_HIDE_RIMEWOOD_FOREST_ABOMASNOW
	return

RimewoodForest_EventScript_Abomasnow::
	lock
	faceplayer
	setwildbattle SPECIES_ABOMASNOW, 40, ITEM_ABOMASITE
	waitse
	playmoncry SPECIES_ABOMASNOW, 2
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_0x8000, MOVE_ICE_SHARD
	setvar VAR_0x8001, MOVE_ICE_PUNCH
	setvar VAR_0x8002, MOVE_INGRAIN
	setvar VAR_0x8003, MOVE_WOOD_HAMMER
	special StartCustomMovesBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq RimewoodForest_EventScript_DefeatedAbomasnow
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq RimewoodForest_EventScript_RanFromAbomasnow
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq RimewoodForest_EventScript_RanFromAbomasnow
	setflag FLAG_CAUGHT_RIMEWOOD_FOREST_ABOMASNOW
	release
	end

RimewoodForest_EventScript_DefeatedAbomasnow::
	setflag FLAG_DEFEATED_RIMEWOOD_FOREST_ABOMASNOW
	goto Common_EventScript_RemoveStaticPokemon
	end

RimewoodForest_EventScript_RanFromAbomasnow::
	setvar VAR_0x8004, SPECIES_ABOMASNOW
	goto Common_EventScript_PokemonFled
	end

RimewoodForest_EventScript_RoarTrigger::
	lockall
	waitse
	playmoncry SPECIES_ABOMASNOW, 0
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	addvar VAR_RIMEWOOD_FOREST_STATE, 1
	releaseall
	end
