.set LOCALID_SABULO_CAVE_GUARD, 4

SabuloTower_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SabuloTower_1F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SabuloTower_1F_OnFrame
	.byte 0

SabuloTower_1F_OnLoad:
	call_if_unset FLAG_RECEIVED_MEGA_RING, SabuloTower_1F_EventScript_DeactivateWarpPad
	end

SabuloTower_1F_EventScript_DeactivateWarpPad::
	setmetatile 12, 13, METATILE_SabuloTower_WarpPad_Deactivated, 0
	return

SabuloTower_1F_OnFrame:
	map_script_2 VAR_SABULO_TOWER_STATE, 2, SabuloTower_1F_EventScript_GoCheckOutSabuloCave
	.2byte 0

SabuloTower_1F_EventScript_GoCheckOutSabuloCave::
	lockall
	playse SE_PIN
	applymovement LOCALID_SABULO_CAVE_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SABULO_CAVE_GUARD, Common_Movement_Delay48
	waitmovement 0
	msgbox SabuloTower_1F_Text_OhItsYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SABULO_CAVE_GUARD, SabuloTower_1F_Movement_ChasePlayerOut
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	warp MAP_SABULO_ISLAND, 3, 0, 0
	waitstate
	releaseall
	end

SabuloTower_1F_Text_OhItsYou:
	.string "{COLOR BLUE}Ah! It's you!\n"
	.string "Is Sabulo Cave safe yet?\p"
	.string "You haven't checked?\n"
	.string "Oh, you must go, quickly!\p"
	.string "Go! Go! Go!$"

SabuloTower_1F_Movement_ChasePlayerOut:
	walk_down
	walk_in_place_fastest_down
	step_end

SabuloTower_1F_EventScript_JimGai::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MEGA_RING, SabuloTower_1F_EventScript_TryExplainMegaRing
	msgbox SabuloTower_1F_Text_HeyChampWelcome, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloTower_1F_EventScript_TryExplainMegaRing:
	msgbox SabuloTower_1F_Text_NiceGoingChampDoYouRemember, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SabuloTower_1F_EventScript_ExplainMegaRing
	msgbox SabuloTower_1F_Text_JustAskIfYouForget, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloTower_1F_EventScript_ExplainMegaRing:
	msgbox MegaEvolution_Text_ExplainMegaEvolution, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloTower_1F_Text_HeyChampWelcome:
	.string "Hey, champ!\n"
	.string "Welcome to Sabulo Tower.\p"
	.string "If you can climb to the top and\n"
	.string "defeat Successor Belle…\p"
	.string "You'll get a Mega Ring!\n"
	.string "Quite the prize, no?$"

SabuloTower_1F_Text_NiceGoingChampDoYouRemember:
	.string "Nice going, champ!\p"
	.string "Do you remember how to use that\n"
	.string "Mega Ring?$"

SabuloTower_1F_Text_JustAskIfYouForget:
	.string "Alright!\n"
	.string "Just ask if you forget.\p"
	.string "By the way, you can use that\n"
	.string "teleporter to go to the top floor.$"

SabuloTower_1F_EventScript_Nikolai::
	trainerbattle_single TRAINER_NIKOLAI, SabuloTower_1F_Text_NikolaiIntro, SabuloTower_1F_Text_NikolaiDefeated
	msgbox SabuloTower_1F_Text_NikolaiPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloTower_1F_Text_NikolaiIntro:
	.string "Welcome, young one. I shall be\n"
	.string "your first challenge. Let's begin!$"

SabuloTower_1F_Text_NikolaiDefeated:
	.string "You show promise!$"

SabuloTower_1F_Text_NikolaiPostBattle:
	.string "You've defeated me, but the\n"
	.string "challenge has just begun!$"
