.equ LOCALID_FERNANDO, 14

WispForest_MapScripts::
	.byte 0

WispForest_EventScript_FernandoRescue_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto WispForest_EventScript_FernandoRescueScene
	end

WispForest_EventScript_FernandoRescue_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto WispForest_EventScript_FernandoRescueScene
	end

WispForest_EventScript_FernandoRescueScene::
	delay 10
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 10
	addobject LOCALID_FERNANDO
	applymovement LOCALID_FERNANDO, WispForest_Movement_FernandoPacing
	compare VAR_0x8008, 0
	call_if_eq WispForest_EventScript_PanCameraToFernando0
	compare VAR_0x8008, 1
	call_if_eq WispForest_EventScript_PanCameraToFernando1
	playse SE_PIN
	applymovement LOCALID_FERNANDO, WispForest_Movement_Surprised
	waitmovement 0
	applymovement LOCALID_FERNANDO, Common_Movement_Delay48
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq WispForest_EventScript_PanCameraToPlayerFernandoWalkToPlayer0
	compare VAR_0x8008, 1
	call_if_eq WispForest_EventScript_PanCameraToPlayerFernandoWalkToPlayer1
	msgbox WispForest_Text_ImSorry, MSGBOX_DEFAULT
	setflag FLAG_BADGE01_GET
	message WispForest_Text_ReceivedMysticBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	applymovement LOCALID_FERNANDO, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox WispForest_Text_QuickLetsGetOutOfHere, MSGBOX_DEFAULT
	setflag FLAG_HIDE_WISP_FOREST_FERNANDO
	setvar VAR_DAY_CARE_CENTER_STATE, 1
	setvar VAR_WISP_FOREST_STATE, 1
	warp MAP_SEROS_VILLAGE_DAY_CARE_CENTER, -1, 7, 3
	waitstate
	releaseall
	end

WispForest_EventScript_PanCameraToFernando0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, WispForest_Movement_PanCameraToFernando0
	waitmovement 0
	special RemoveCameraObject
	return

WispForest_EventScript_PanCameraToFernando1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, WispForest_Movement_PanCameraToFernando1
	waitmovement 0
	special RemoveCameraObject
	return

WispForest_EventScript_PanCameraToPlayerFernandoWalkToPlayer0:
	special SpawnCameraObject
	applymovement LOCALID_FERNANDO, WispForest_Movement_FernandoWalkToPlayer0
	applymovement OBJ_EVENT_ID_CAMERA, WispForest_Movement_PanCameraToPlayer0
	waitmovement 0
	special RemoveCameraObject
	return

WispForest_EventScript_PanCameraToPlayerFernandoWalkToPlayer1:
	special SpawnCameraObject
	applymovement LOCALID_FERNANDO, WispForest_Movement_FernandoWalkToPlayer1
	applymovement OBJ_EVENT_ID_CAMERA, WispForest_Movement_PanCameraToPlayer1
	waitmovement 0
	special RemoveCameraObject
	return

WispForest_Text_ImSorry:
	.string "Fernando: {COLOR BLUE}I-I'm sorry!\p"
	.string "I didn't mean it!\p"
	.string "I-I'm too s-scared for apologies!\p"
	.string "Just take the {COLOR GREEN}Mystic Badge{COLOR BLUE},\n"
	.string "and let's go home!$"

WispForest_Text_ReceivedMysticBadge:
	.string "{PLAYER} received the Mystic Badge\n"
	.string "from Fernando.$"

WispForest_Text_QuickLetsGetOutOfHere:	
	.string "Fernando: {COLOR BLUE}Quick!\n"
	.string "Let's get out of here!$"

WispForest_Movement_PanCameraToFernando0:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

WispForest_Movement_PanCameraToFernando1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

WispForest_Movement_FernandoPacing:
	walk_down
	walk_down
	walk_up
	walk_up
	walk_up
	walk_down
	walk_down
	walk_up
	face_left
	step_end

WispForest_Movement_FernandoWalkToPlayer0:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

WispForest_Movement_PanCameraToPlayer0:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

WispForest_Movement_FernandoWalkToPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

WispForest_Movement_PanCameraToPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

WispForest_Movement_Surprised:
	emote_exclamation_mark
	jump_in_place_left
	step_end

WispForest_EventScript_Dmitri::
	trainerbattle_single TRAINER_DMITRI, WispForest_Text_DmitriIntro, WispForest_Text_DmitriDefeated
	msgbox WispForest_Text_DmitriPostBattle, MSGBOX_AUTOCLOSE
	end

WispForest_Text_DmitriIntro:
	.string "W-what was that noise?$"

WispForest_Text_DmitriDefeated:
	.string "Oh no…\n"
	.string "I'm scared!$"

WispForest_Text_DmitriPostBattle:
	.string "M-maybe I'm not brave enough to be\n"
	.string "here right now…$"

WispForest_EventScript_Shiro::
	trainerbattle_single TRAINER_SHIRO, WispForest_Text_ShiroIntro, WispForest_Text_ShiroDefeated
	msgbox WispForest_Text_ShiroPostBattle, MSGBOX_AUTOCLOSE
	end

WispForest_Text_ShiroIntro:
	.string "Hey, let's battle to distract\n"
	.string "ourselves from how scared we are!$"

WispForest_Text_ShiroDefeated:
	.string "T-that didn't work…$"

WispForest_Text_ShiroPostBattle:
	.string "I need to get out of here!$"

WispForest_EventScript_Cadence::
	trainerbattle_single TRAINER_CADENCE, WispForest_Text_CadenceIntro, WispForest_Text_CadenceDefeated
	msgbox WispForest_Text_CadencePostBattle, MSGBOX_AUTOCLOSE
	end

WispForest_Text_CadenceIntro:
	.string "People around here are so\n"
	.string "concerned with Ghost-types.\p"
	.string "I'm not scared of them, I'm\n"
	.string "friends with them!$"

WispForest_Text_CadenceDefeated:
	.string "I said I'm friends with them, not\n"
	.string "good at battling with them!$"

WispForest_Text_CadencePostBattle:
	.string "I can't wait for my Pokémon\n"
	.string "to evolve!$"

WispForest_EventScript_Youngster::
	msgbox WispForest_Text_HaveYouSeenPumpkaboo, MSGBOX_NPC
	end

WispForest_Text_HaveYouSeenPumpkaboo:
	.string "Have you seen a Pumpkaboo?\n"
	.string "They come in all sorts of sizes!$"
