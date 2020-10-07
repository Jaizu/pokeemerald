.set LOCALID_ATTENDANT, 1

WindmistCity_CableCarStation_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WindmistCity_CableCarStation_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, WindmistCity_CableCarStation_OnFrame
	.byte 0

WindmistCity_CableCarStation_OnTransition:
	compare VAR_CABLE_CAR_STATION_STATE, 1
	call_if_eq WindmistCity_CableCarStation_EventScript_MoveAttendantAside
	end

WindmistCity_CableCarStation_EventScript_MoveAttendantAside::
	setobjectxyperm LOCALID_ATTENDANT, 5, 4
	setobjectmovementtype LOCALID_ATTENDANT, MOVEMENT_TYPE_FACE_RIGHT
	return

WindmistCity_CableCarStation_OnFrame:
	map_script_2 VAR_CABLE_CAR_STATION_STATE, 1, WindmistCity_CableCarStation_EventScript_ExitCableCar
	.2byte 0

WindmistCity_CableCarStation_EventScript_ExitCableCar::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, WindmistCity_CableCarStation_Movement_ExitCableCar
	applymovement LOCALID_ATTENDANT, WindmistCity_CableCarStation_Movement_FollowPlayerOutFromCableCar
	waitmovement 0
	setvar VAR_CABLE_CAR_STATION_STATE, 0
	setobjectxyperm LOCALID_ATTENDANT, 6, 7
	setobjectmovementtype LOCALID_ATTENDANT, MOVEMENT_TYPE_FACE_DOWN
	releaseall
	end

WindmistCity_CableCarStation_EventScript_Attendant::
	lock
	faceplayer
	msgbox WindmistCity_CableCarStation_Text_CableCarReadyGetOn, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq WindmistCity_CableCarStation_EventScript_RideCableCar
	compare VAR_RESULT, NO
	goto_if_eq WindmistCity_CableCarStation_EventScript_DeclineRide
	end

WindmistCity_CableCarStation_EventScript_RideCableCar::
	msgbox WindmistCity_CableCarStation_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, WindmistCity_CableCarStation_Movement_LeadPlayerToCableCar
	applymovement OBJ_EVENT_ID_PLAYER, WindmistCity_CableCarStation_Movement_BoardCableCar
	waitmovement 0
	setvar VAR_0x8004, 1
	setvar VAR_CABLE_CAR_STATION_STATE, 2
	incrementgamestat GAME_STAT_RODE_CABLE_CAR
	special CableCarWarp
	special CableCar
	waitstate
	release
	end

WindmistCity_CableCarStation_EventScript_DeclineRide::
	msgbox WindmistCity_CableCarStation_Text_RideAnotherTime, MSGBOX_DEFAULT
	release
	end

WindmistCity_CableCarStation_Movement_LeadPlayerToCableCar:
	walk_up
	walk_up
	walk_left
	walk_in_place_fastest_right
	step_end

WindmistCity_CableCarStation_Movement_FollowPlayerOutFromCableCar:
	delay_16
	walk_right
	walk_down
	walk_down
	step_end

WindmistCity_CableCarStation_Movement_BoardCableCar:
	walk_up
	walk_up
	walk_up
	delay_16
	step_end

WindmistCity_CableCarStation_Movement_ExitCableCar:
	walk_down
	walk_down
	walk_down
	delay_16
	step_end

WindmistCity_CableCarStation_Text_CableCarReadyGetOn:
	.string "The Cable Car is ready to go down.\n"
	.string "Would you like to be on it?$"

WindmistCity_CableCarStation_Text_StepThisWay:
	.string "Please step this way.$"

WindmistCity_CableCarStation_Text_RideAnotherTime:
	.string "Please ride with us another time.$"
