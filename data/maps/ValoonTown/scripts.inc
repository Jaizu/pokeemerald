.set LOCALID_RANGER_1, 1
.set LOCALID_RANGER_2, 2
.set LOCALID_RANGER_3, 3
.set LOCALID_COULTER, 10

ValoonTown_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, ValoonTown_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ValoonTown_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, ValoonTown_OnTransition
	.byte 0

ValoonTown_OnLoad::
	call_if_unset FLAG_UNLOCK_VALOON_GYM_DOOR, ValoonTown_EventScript_LockGymDoor
	end

ValoonTown_EventScript_LockGymDoor:
	setmetatile 42, 3, METATILE_General_Door_GymLocked, 1
	return

ValoonTown_OnFrame:
	map_script_2 VAR_VALOON_TOWN_STATE, 2, ValoonTown_EventScript_CoulterGasMaskScene
	.byte 0

ValoonTown_OnTransition::
	setflag FLAG_VISITED_VALOON_TOWN
	compare VAR_VALOON_TOWN_STATE, 0
	call_if_eq ValoonTown_EventScript_MoveRanger
	end

ValoonTown_EventScript_MoveRanger::
	setobjectxyperm LOCALID_RANGER_1, 17, 6
	setobjectmovementtype LOCALID_RANGER_1, MOVEMENT_TYPE_FACE_RIGHT
	return

ValoonTown_EventScript_CoulterGasMaskScene::
	lockall
	addobject LOCALID_COULTER
	msgbox ValoonTown_Text_Player, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	applymovement LOCALID_COULTER, ValoonTown_Movement_WalkToPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	msgbox ValoonTown_Text_GiveGasMask, MSGBOX_DEFAULT
	giveitem ITEM_GAS_MASK
	msgbox ValoonTown_Text_ExplainGasMask, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COULTER, ValoonTown_Movement_ExitCoulter
	waitmovement 0
	removeobject LOCALID_COULTER
	fadedefaultbgm
	setvar VAR_VALOON_TOWN_GATEHOUSE_STATE, 1
	setvar VAR_VALOON_TOWN_STATE, 3
	releaseall
	end

ValoonTown_Text_Player:
	.string "{RIVAL}: {COLOR BLUE}{PLAYER}!$"

ValoonTown_Text_GiveGasMask:
	.string "{RIVAL}: {COLOR BLUE}Looks like I beat you this\n"
	.string "time!\p"
	.string "I got Vernon's Badge before he\n"
	.string "closed his Gym to enter the\l"
	.string "Bug-Catching Contest.\p"
	.string "Anyway, looks like they're not\n"
	.string "letting people into Telmurk Swamp.\p"
	.string "Something about noxious gases.\p"
	.string "Lucky for you, I had the foresight\n"
	.string "to buy these! Here's yours.$"

ValoonTown_Text_ExplainGasMask:
	.string "{RIVAL}: {COLOR BLUE}With these Gas Masks,\n"
	.string "we'll be able to get through.\p"
	.string "It's been a while since we've had\n"
	.string "a battle, hasn't it?\p"
	.string "Maybe when we get to Telmurk City,\n"
	.string "we can battle again.\p"
	.string "I look forward to it.\n"
	.string "Later, {PLAYER}!$"

ValoonTown_Movement_WalkToPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

ValoonTown_Movement_ExitCoulter:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

ValoonTown_EventScript_RangersSceneTrigger::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	delay 10
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 18 @ x
	setvar VAR_0x8005, 6  @ y
	special TeleportCamera
	fadescreen FADE_FROM_BLACK
	applymovement LOCALID_RANGER_1, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox ValoonTown_Text_WeNeedToGoCheck, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RANGER_1, ValoonTown_Movement_ExitRangers
	applymovement LOCALID_RANGER_2, ValoonTown_Movement_ExitRangers
	applymovement LOCALID_RANGER_3, ValoonTown_Movement_ExitRangers
	waitmovement 0
	removeobject LOCALID_RANGER_1
	removeobject LOCALID_RANGER_2
	removeobject LOCALID_RANGER_3
	delay 10
	fadescreen FADE_TO_BLACK
	special ReturnCameraToPlayer
	fadescreen FADE_FROM_BLACK
	setvar VAR_VALOON_TOWN_STATE, 1
	releaseall
	end

ValoonTown_Text_WeNeedToGoCheck:
	.string "Ranger: {COLOR BLUE}We need to go and check\n"
	.string "{COLOR GREEN}Nemesis Cave{COLOR BLUE}!\p"
	.string "People might've got hurt in the\n"
	.string "earthquake!\p"
	.string "Let's move out, team!$"

ValoonTown_Movement_ExitRangers:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

ValoonTown_EventScript_TownSign::
	msgbox ValoonTown_Text_TownSign, MSGBOX_SIGN
	end

ValoonTown_Text_TownSign::
	.string "Valoon Town\n"
	.string "A Habitat for Pokémon and People.$"

ValoonTown_EventScript_GymSign::
	msgbox ValoonTown_Text_GymSign, MSGBOX_SIGN
	end

ValoonTown_Text_GymSign::
	.string "Valoon Town Pokémon Gym\p"
	.string "Leader: Vernon\n"
	.string "“He wouldn't harm a Joltik!”$"

ValoonTown_EventScript_RangersHQSign::
	msgbox ValoonTown_Text_RangersHQSign, MSGBOX_SIGN
	end

ValoonTown_Text_RangersHQSign::
	.string "Valoon Rangers Headquarters\p"
	.string "Take part in the\n"
	.string "Bug-Catching Contest!$"

ValoonTown_EventScript_BlueShardMeisterSign::
	msgbox ValoonTown_Text_BlueShardMeisterSign, MSGBOX_SIGN
	end

ValoonTown_Text_BlueShardMeisterSign::
	.string "Blue Shard Meister's house\p"
	.string "“I will teach Pokémon moves for\n"
	.string "Blue Shards!”$"

ValoonTown_EventScript_PkmnRangerM::
	msgbox ValoonTown_Text_MyJobIsToProtect, MSGBOX_NPC
	end

ValoonTown_Text_MyJobIsToProtect::
	.string "As a Ranger, my job is to protect\n"
	.string "the townspeople and their Pokémon.$"

ValoonTown_EventScript_LittleGirl::
	msgbox ValoonTown_Text_WhenImOlder, MSGBOX_NPC
	end

ValoonTown_Text_WhenImOlder::
	.string "When I'm older, I want to become a\n"
	.string "Ranger, just like my big sister!$"

ValoonTown_EventScript_OldMan::
	msgbox ValoonTown_Text_MyNidorinoWasInjured, MSGBOX_NPC
	end

ValoonTown_Text_MyNidorinoWasInjured::
	.string "My Nidorino was injured in the\n"
	.string "wild, but the Rangers rescued him!$"

ValoonTown_EventScript_Nidorino::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_NIDORINO, 0
	msgbox ValoonTown_Text_Nidorino, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ValoonTown_Text_Nidorino:
	.string "Nidorino: {COLOR BLUE}Kurii-oh!!$"

ValoonTown_EventScript_AceTrainerM::
	msgbox ValoonTown_Text_EveryNowAndAgain, MSGBOX_NPC
	end

ValoonTown_Text_EveryNowAndAgain::
	.string "Every now and again, Vernon closes\n"
	.string "his Gym.\p"
	.string "I think he does it so he can go and\n"
	.string "capture more Bug-type Pokémon.$"

ValoonTown_EventScript_RichBoy::
	msgbox ValoonTown_Text_HaveYouEnteredTheContest, MSGBOX_NPC
	end

ValoonTown_Text_HaveYouEnteredTheContest::
	.string "Have you entered the Bug-Catching\n"
	.string "Contest?\p"
	.string "It's highly competitive, but the\n"
	.string "prizes are worth it.$"

ValoonTown_EventScript_LockedDoor::
	lock
	msgbox ValoonTown_Text_TheDoorIsLocked, MSGBOX_DEFAULT
	release
	end

ValoonTown_Text_TheDoorIsLocked:
	.string "{COLOR DARK_GREY}The door is locked…$"
