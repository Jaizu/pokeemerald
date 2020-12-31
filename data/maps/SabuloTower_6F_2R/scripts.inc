.set LOCALID_BELLE, 1

// TODO: Add Mega Ring item
.set ITEM_MEGA_RING, 0

SabuloTower_6F_2R_MapScripts::
	.byte 0

SabuloTower_6F_2R_EventScript_BelleFightTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto SabuloTower_6F_2R_EventScript_BelleFightScene
	end

SabuloTower_6F_2R_EventScript_BelleFightTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto SabuloTower_6F_2R_EventScript_BelleFightScene
	end

SabuloTower_6F_2R_EventScript_BelleFightTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto SabuloTower_6F_2R_EventScript_BelleFightScene
	end

SabuloTower_6F_2R_EventScript_BelleFightScene:
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 8  @ x
	setvar VAR_0x8005, 15 @ y
	special TeleportCamera
	fadescreen FADE_FROM_BLACK
	msgbox SabuloTower_6F_2R_Text_WelcomeTrainer, MSGBOX_DEFAULT
	applymovement LOCALID_BELLE, Common_Movement_FaceRight
	waitmovement 0
	msgbox SabuloTower_6F_2R_Text_ThisTower, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq SabuloTower_6F_2R_EventScript_PanCameraWalkBelleToPlayer0
	compare VAR_0x8008, 1
	call_if_eq SabuloTower_6F_2R_EventScript_PanCameraWalkBelleToPlayer1
	compare VAR_0x8008, 2
	call_if_eq SabuloTower_6F_2R_EventScript_PanCameraWalkBelleToPlayer2
	special ReturnCameraToPlayer
	msgbox SabuloTower_6F_2R_Text_ThenDefeatMeInBattle, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BELLE_1, SabuloTower_6F_2R_Text_BelleDefeat
	additem ITEM_MEGA_RING
	setflag FLAG_RECEIVED_MEGA_RING
	msgbox SabuloTower_6F_2R_Text_AreYouFamiliarWithMegaEvolution, MSGBOX_YESNO
	compare VAR_RESULT, NO
	call_if_eq SabuloTower_6F_2R_EventScript_ExplainMegaEvolution
	msgbox SabuloTower_6F_2R_Text_IHaveNoDoubt, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_FieldHeal
	msgbox SabuloTower_6F_2R_Text_Farewell, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq SabuloTower_6F_2R_EventScript_ExitBelle0
	compare VAR_0x8008, 1
	call_if_eq SabuloTower_6F_2R_EventScript_ExitBelle1
	compare VAR_0x8008, 2
	call_if_eq SabuloTower_6F_2R_EventScript_ExitBelle2
	playse SE_EXIT
	waitse
	removeobject LOCALID_BELLE
	setvar VAR_SABULO_TOWER_STATE, 1
	setvar VAR_SABULO_ISLAND_STATE, 1
	releaseall
	end

SabuloTower_6F_2R_EventScript_PanCameraWalkBelleToPlayer0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SabuloTower_6F_2R_Movement_PanCameraToPlayer0
	applymovement LOCALID_BELLE, SabuloTower_6F_2R_Movement_WalkToPlayer0
	waitmovement 0
	special RemoveCameraObject
	return

SabuloTower_6F_2R_EventScript_PanCameraWalkBelleToPlayer1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SabuloTower_6F_2R_Movement_PanCameraToPlayer1
	applymovement LOCALID_BELLE, SabuloTower_6F_2R_Movement_WalkToPlayer1
	waitmovement 0
	special RemoveCameraObject
	return

SabuloTower_6F_2R_EventScript_PanCameraWalkBelleToPlayer2:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SabuloTower_6F_2R_Movement_PanCameraToPlayer2
	applymovement LOCALID_BELLE, SabuloTower_6F_2R_Movement_WalkToPlayer2
	waitmovement 0
	special RemoveCameraObject
	return

SabuloTower_6F_2R_EventScript_ExplainMegaEvolution:
	textcolor 1 // Red
	msgbox MegaEvolution_Text_ExplainMegaEvolution, MSGBOX_DEFAULT
	textcolor 0xFF
	return

SabuloTower_6F_2R_EventScript_ExitBelle0:
	applymovement LOCALID_BELLE, SabuloTower_6F_2R_Movement_ExitBelle0
	waitmovement 0
	return

SabuloTower_6F_2R_EventScript_ExitBelle1:
	applymovement LOCALID_BELLE, SabuloTower_6F_2R_Movement_ExitBelle1
	waitmovement 0
	return

SabuloTower_6F_2R_EventScript_ExitBelle2:
	applymovement LOCALID_BELLE, SabuloTower_6F_2R_Movement_ExitBelle2
	waitmovement 0
	return

SabuloTower_6F_2R_Text_WelcomeTrainer:
	.string "Belle: {COLOR RED}Welcome, Trainer.\n"
	.string "I am Successor Belle.$"

SabuloTower_6F_2R_Text_ThisTower:
	.string "Belle: {COLOR RED}This tower…\p"
	.string "When stood at the base, it appears\n"
	.string "to endlessly stretch to the skies.\p"
	.string "Truth… commitment… willpower…\p"
	.string "These qualities epitomize what it\n"
	.string "takes to reach the top.\p"
	.string "Indeed, they're also what a Trainer\n"
	.string "needs to achieve {COLOR GREEN}Mega Evolution{COLOR RED}.\p"
	.string "You may therefore assume you are\n"
	.string "worthy. That is false.\p"
	.string "You deserve nothing.\n"
	.string "Not yet.\p"
	.string "If you wish to unlock the true\n"
	.string "power of Mega Evolution…$"

SabuloTower_6F_2R_Text_ThenDefeatMeInBattle:
	.string "{COLOR RED}…then defeat me in battle!$"

SabuloTower_6F_2R_Text_BelleDefeat:
	.string "Astounding!\p"
	.string "Even with the advantage of Mega\n"
	.string "Evolution, I lost.\p"
	.string "You have demonstrated a powerful\n"
	.string "bond with your Pokémon.\p"
	.string "You are now worthy of this.\n"
	.string "Take it with pride!\p"
	.string "{PLAYER} received the\n"
	.string "Mega Ring from Belle!{PAUSE_MUSIC}{PLAY_BGM}{MUS_OBTAIN_BADGE}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}\p"
	.string "You have achieved a great feat,\n"
	.string "{PLAYER}.$"

SabuloTower_6F_2R_Text_AreYouFamiliarWithMegaEvolution:
	.string "{COLOR RED}The Mega Ring lets you harness\n"
	.string "the power of Mega Evolution.\p"
	.string "Are you familiar with how to\n"
	.string "Mega Evolve?$"

SabuloTower_6F_2R_Text_IHaveNoDoubt:
	.string "{COLOR RED}I have no doubt you will wield\n"
	.string "this power responsibly.\p"
	.string "Let me heal your Pokémon.$"

SabuloTower_6F_2R_Text_Farewell:
	.string "Belle: {COLOR RED}Farewell, {PLAYER}.$"

SabuloTower_6F_2R_Movement_PanCameraToPlayer0:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

SabuloTower_6F_2R_Movement_WalkToPlayer0:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	step_end

SabuloTower_6F_2R_Movement_PanCameraToPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SabuloTower_6F_2R_Movement_WalkToPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SabuloTower_6F_2R_Movement_PanCameraToPlayer2:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

SabuloTower_6F_2R_Movement_WalkToPlayer2:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	step_end

SabuloTower_6F_2R_Movement_ExitBelle0:
	walk_down
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end

SabuloTower_6F_2R_Movement_ExitBelle1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end

SabuloTower_6F_2R_Movement_ExitBelle2:
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end
