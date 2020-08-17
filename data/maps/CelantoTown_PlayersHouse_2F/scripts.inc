// TODO: Remove temporary defines:
.equ ITEM_DUSTY_TOME, 267 // TODO: Actually add Dusty Tome item

CelantoTown_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, CelantoTown_PlayersHouse_2F_OnWarp
	.byte 0

CelantoTown_PlayersHouse_2F_OnWarp:
	map_script_2 VAR_CELANTO_TOWN_STATE, 0, CelantoTown_PlayersHouse_2F_EventScript_TurnPlayerNorth
	.2byte 0

CelantoTown_PlayersHouse_2F_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
    setvar VAR_CELANTO_TOWN_STATE, 1
	end

CelantoTown_PlayersHouse_2F_EventScript_PC::
	lockall
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

CelantoTown_PlayersHouse_2F_EventScript_NES::
    msgbox CelantoTown_PlayersHouse_2F_Text_PlayedWithTheNES, MSGBOX_SIGN
    end

CelantoTown_PlayersHouse_2F_Text_PlayedWithTheNES::
    .string "{PLAYER} played with the NES.\p"
    .string "…Okay!\n"
    .string "It's time to go!$"

CelantoTown_PlayersHouse_2F_EventScript_DustyTome::
    finditem ITEM_DUSTY_TOME
    compare VAR_CELANTO_TOWN_STATE, 2
    call_if_eq CelantoTown_PlayersHouse_2F_EventScript_EnableRunningShoesTrigger
    end
    
CelantoTown_PlayersHouse_2F_EventScript_EnableRunningShoesTrigger:
    setvar VAR_CELANTO_TOWN_STATE, 3
    return
