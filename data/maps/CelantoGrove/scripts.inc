.equ LOCALID_WORKER, 1

CelantoGrove_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CelantoGrove_OnTransition
	.byte 0

CelantoGrove_OnTransition::
	compare VAR_CELANTO_GROVE_STATE, 0
	call_if_gt CelantoGrove_EventScript_SetWorkerPos
	end
	
CelantoGrove_EventScript_SetWorkerPos:
	setobjectxyperm LOCALID_WORKER, 17, 16
	setobjectmovementtype LOCALID_WORKER, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT
	return

CelantoGrove_EventScript_WorkerCantPass_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto CelantoGrove_EventScript_WorkerCantPass
	end

CelantoGrove_EventScript_WorkerCantPass_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto CelantoGrove_EventScript_WorkerCantPass
	end

CelantoGrove_EventScript_WorkerCantPass:
	playse SE_PIN
	applymovement LOCALID_WORKER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WORKER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_WORKER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CelantoGrove_Text_WhoaThereKid, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq CelantoGrove_EventScript_PlayerFaceDown
	compare VAR_0x8008, 1
	call_if_eq CelantoGrove_EventScript_PlayerFaceUp
	msgbox CelantoGrove_Text_ICantLetYouPass, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft
	waitmovement 0
	applymovement LOCALID_WORKER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

CelantoGrove_EventScript_PlayerFaceDown:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	return

CelantoGrove_EventScript_PlayerFaceUp:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	return
	
CelantoGrove_Text_WhoaThereKid:
	.string "{COLOR BLUE}Whoa there, kid!$"

CelantoGrove_Text_ICantLetYouPass:
	.string "{COLOR BLUE}I can't let you pass at the\n"
	.string "moment.\p"
	.string "The Cable Car isn't working!$"

CelantoGrove_EventScript_Worker::
	lock
	faceplayer
	compare VAR_CELANTO_GROVE_STATE, 0
	goto_if_eq CelantoGrove_EventScript_ExplainCableCarIsDown
	goto_if_set FLAG_RECEIVED_TM32, CelantoGrove_EventScript_ExplainStealthRocks
	msgbox CelantoGrove_Text_EvenTheSmallestRocksCanBeAThreat, MSGBOX_DEFAULT
	giveitem ITEM_TM32
	setflag FLAG_RECEIVED_TM32
	goto CelantoGrove_EventScript_ExplainStealthRocks
	end

CelantoGrove_EventScript_ExplainCableCarIsDown:
	msgbox CelantoGrove_Text_TremorsCausedMiniAvalanche, MSGBOX_DEFAULT
	release
	end

CelantoGrove_EventScript_ExplainStealthRocks:
	msgbox CelantoGrove_Text_StealthRockWorksEvenAgainstFlyingTypes, MSGBOX_DEFAULT
	release
	end

CelantoGrove_Text_TremorsCausedMiniAvalanche:
	.string "The tremors caused a\n"
	.string "mini-avalanche.\p"
	.string "We've got guys on the line,\n"
	.string "clearing the snow.\p"
	.string "In the mean time, the Cable Car\n"
	.string "is off-limits!\p"
	.string "Sorry, kid.$"

CelantoGrove_Text_EvenTheSmallestRocksCanBeAThreat:
	.string "Even the smallest of rocks can be\n"
	.string "a threat.\p"
	.string "Just look at what the mini-\n"
	.string "avalanche did to the Cable Car!\p"
	.string "But with gumption and a bit of\n"
	.string "elbow grease, we got it working!\p"
	.string "…\p"
	.string "Kid, I like you! Most people don't\n"
	.string "stick around for my work rambles.\p"
	.string "Here, take this!\n"
	.string "It's TM32, Stealth Rock!$"

CelantoGrove_Text_StealthRockWorksEvenAgainstFlyingTypes:
	.string "Stealth Rock works even against\n"
	.string "Flying-type Pokémon.\p"
	.string "In fact, it hurts them more!\p"
	.string "After all, Rock-type is super\n"
	.string "effective against Flying-types…$"

CelantoGrove_EventScript_CableCarSign::
	msgbox CelantoGrove_Text_MtIgnisCableCar, MSGBOX_SIGN
	end

CelantoGrove_Text_MtIgnisCableCar::
	.string "Mt. Ignis Cable Car\n"
	.string "Take a ride up the mountain!$"
