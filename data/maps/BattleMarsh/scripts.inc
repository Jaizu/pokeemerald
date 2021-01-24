.set TRAINER_COULTER_BATTLE_MARSH_INFERNAPE, 1
.set TRAINER_COULTER_BATTLE_MARSH_EMPOLEON, 1
.set TRAINER_COULTER_BATTLE_MARSH_TORTERRA, 1
.set TRAINER_ADRIANA_1, 1
.set TRAINER_DEAN_1, 1
.set TRAINER_SHANE_1, 1
.set TRAINER_EARL_1, 1
.set TRAINER_JENNIE_1, 1
.set TRAINER_LLOYD_1, 1
.set TRAINER_DORIS_1, 1
.set TRAINER_CARLA_1, 1

.set LOCALID_COULTER, 7

BattleMarsh_MapScripts::
	.byte 0

BattleMarsh_EventScript_RouteSign::
	msgbox BattleMarsh_Text_RouteSign, MSGBOX_SIGN
	end

BattleMarsh_Text_RouteSign:
	.string "{LEFT_ARROW} Telmurk Swamp {RIGHT_ARROW} Telmurk City$"

BattleMarsh_EventScript_BattleMarshSign::
	msgbox BattleMarsh_Text_BattleMarshSign, MSGBOX_SIGN
	end

BattleMarsh_Text_BattleMarshSign:
	.string "Battle Marsh\n"
	.string "Where Trainers are put to the test!$"

BattleMarsh_EventScript_CoulterFight_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFight_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFight_Trigger2::
	lockall
	setvar VAR_0x8008, 2
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFight_Trigger3::
	lockall
	setvar VAR_0x8008, 3
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFight_Trigger4::
	lockall
	setvar VAR_0x8008, 4
	goto BattleMarsh_EventScript_CoulterFightScene
	end

BattleMarsh_EventScript_CoulterFightScene:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter0
	compare VAR_0x8008, 1
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter1
	compare VAR_0x8008, 2
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter2
	compare VAR_0x8008, 3
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter3
	compare VAR_0x8008, 4
	call_if_eq BattleMarsh_EventScript_CameraPanToCoulter4
	msgbox BattleMarsh_Text_WeAreNotGonnaLose, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	delay 10
	playse SE_PIN
	applymovement LOCALID_COULTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleMarsh_Text_OhYoureHere, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	compare VAR_0x8008, 0
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer0
	compare VAR_0x8008, 1
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer1
	compare VAR_0x8008, 2
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer2
	compare VAR_0x8008, 3
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer3
	compare VAR_0x8008, 4
	call_if_eq BattleMarsh_EventScript_CoulterWalkToPlayer4
	msgbox BattleMarsh_Text_ThisPlaceIsCool, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_FieldHeal
	msgbox BattleMarsh_Text_NowPlayerIChallengeYou, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0 // Player chose Turtwig
	call_if_eq BattleMarsh_EventScript_StartCoulterBattleInfernape
	compare VAR_STARTER_MON, 1 // Player chose Chimchar
	call_if_eq BattleMarsh_EventScript_StartCoulterBattleEmpoleon
	compare VAR_STARTER_MON, 2 // Player chose Piplup
	call_if_eq BattleMarsh_EventScript_StartCoulterBattleTorterra
	msgbox BattleMarsh_Text_ItsJustMaddening, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	applymovement LOCALID_COULTER, BattleMarsh_Movement_ExitCoulter
	waitmovement 0
	removeobject LOCALID_COULTER
	fadedefaultbgm
	delay 10
	setvar VAR_BATTLE_MARSH_STATE, 1
	releaseall
	end

BattleMarsh_EventScript_CameraPanToCoulter0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter0
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CameraPanToCoulter1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter1
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CameraPanToCoulter2:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter2
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CameraPanToCoulter3:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter3
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CameraPanToCoulter4:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToCoulter4
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer0:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer0
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer0
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer1:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer1
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer1
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer2:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer2
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer2
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer3:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer3
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer3
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_CoulterWalkToPlayer4:
	special SpawnCameraObject
	applymovement LOCALID_COULTER, BattleMarsh_Movement_CoulterWalkToPlayer4
	applymovement OBJ_EVENT_ID_CAMERA, BattleMarsh_Movement_CameraPanToPlayer4
	waitmovement 0
	special RemoveCameraObject
	return

BattleMarsh_EventScript_StartCoulterBattleInfernape:
	trainerbattle_no_intro TRAINER_COULTER_BATTLE_MARSH_INFERNAPE, BattleMarsh_Text_CoulterDefeat
	return

BattleMarsh_EventScript_StartCoulterBattleEmpoleon:
	trainerbattle_no_intro TRAINER_COULTER_BATTLE_MARSH_EMPOLEON, BattleMarsh_Text_CoulterDefeat
	return

BattleMarsh_EventScript_StartCoulterBattleTorterra:
	trainerbattle_no_intro TRAINER_COULTER_BATTLE_MARSH_TORTERRA, BattleMarsh_Text_CoulterDefeat
	return

BattleMarsh_Text_WeAreNotGonnaLose:
	.string "{RIVAL}: {COLOR BLUE}We're not going to lose to\n"
	.string "{PLAYER} again, team.$"

BattleMarsh_Text_OhYoureHere:
	.string "{RIVAL}: {COLOR BLUE}Oh\n"
	.string "You're here!$"

BattleMarsh_Text_ThisPlaceIsCool:
	.string "{RIVAL}: {COLOR BLUE}This place is cool,\n"
	.string "isn't it?\p"
	.string "Maybe once we're finished helping\n"
	.string "the Professor, we could take the\l"
	.string "Battle Marsh on!\p"
	.string "Anyway, I said we were going to\n"
	.string "battle, and I meant it!\p"
	.string "You look tired, though, so I'll\n"
	.string "heal your Pokémon, first.$"

BattleMarsh_Text_NowPlayerIChallengeYou:
	.string "{RIVAL}: {COLOR BLUE}Now, {PLAYER}!\p"
	.string "I challenge you to a Pokémon\n"
	.string "battle!$"

BattleMarsh_Text_CoulterDefeat:
	.string "Argh! I don't… How?!\n"
	.string "W-why does this… Argh!$"

BattleMarsh_Text_ItsJustMaddening:
	.string "{RIVAL}: {COLOR BLUE}I-it's just…\n"
	.string "It's maddening, you know?\p"
	.string "I try to contain my anger, but…\n"
	.string "Losing is painful, alright?!\p"
	.string "Sigh…\p"
	.string "Maybe I'm not cut out to be a\n"
	.string "Pokémon Trainer after all.\p"
	.string "…\p"
	.string "You're right, I shouldn't be so\n"
	.string "hard on myself.\p"
	.string "I've got a job to do!\n"
	.string "We both have!\p"
	.string "Let's go, {PLAYER}!$"

BattleMarsh_Movement_CameraPanToCoulter0:
	walk_right
	walk_right
	walk_up
	step_end

BattleMarsh_Movement_CameraPanToCoulter1:
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

BattleMarsh_Movement_CameraPanToCoulter2:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

BattleMarsh_Movement_CameraPanToCoulter3:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleMarsh_Movement_CameraPanToCoulter4:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleMarsh_Movement_CoulterWalkToPlayer0:
	walk_down
	walk_left
	step_end

BattleMarsh_Movement_CoulterWalkToPlayer1:
	walk_down
	walk_down
	walk_left
	step_end

BattleMarsh_Movement_CoulterWalkToPlayer2:
	walk_down
	walk_down
	walk_down
	walk_left
	step_end
	
BattleMarsh_Movement_CoulterWalkToPlayer3:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end
	
BattleMarsh_Movement_CoulterWalkToPlayer4:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end
	
BattleMarsh_Movement_CameraPanToPlayer0:
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_CameraPanToPlayer1:
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_CameraPanToPlayer2:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_CameraPanToPlayer3:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_CameraPanToPlayer4:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

BattleMarsh_Movement_ExitCoulter:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

BattleMarsh_EventScript_Adriana::
	trainerbattle_single TRAINER_ADRIANA_1, BattleMarsh_Text_AdrianaIntro, BattleMarsh_Text_AdrianaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleMarsh_EventScript_AdrianaRematch
	msgbox BattleMarsh_Text_AdrianaPostBattle, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_AdrianaRematch::
	trainerbattle_rematch TRAINER_ADRIANA_1, BattleMarsh_Text_AdrianaRematchIntro, BattleMarsh_Text_AdrianaDefeat
	msgbox BattleMarsh_Text_AdrianaPostBattle, MSGBOX_AUTOCLOSE
	end

BattleMarsh_Text_AdrianaIntro:
	.string "Whoa, you have Badges!\p"
	.string "You're gonna be a great\n"
	.string "match for me!$"

BattleMarsh_Text_AdrianaDefeat:
	.string "I'm too weak!$"

BattleMarsh_Text_AdrianaPostBattle:
	.string "Did you get the Honeycomb Badge\n"
	.string "from Vernon?$"

BattleMarsh_Text_AdrianaRematchIntro:
	.string "Whoa, do you have even more Badges?$"

BattleMarsh_EventScript_Dean::
	trainerbattle_single TRAINER_DEAN_1, BattleMarsh_Text_DeanIntro, BattleMarsh_Text_DeanDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleMarsh_EventScript_DeanRematch
	msgbox BattleMarsh_Text_DeanPostBattle, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_DeanRematch::
	trainerbattle_rematch TRAINER_DEAN_1, BattleMarsh_Text_DeanRematchIntro, BattleMarsh_Text_DeanDefeat
	msgbox BattleMarsh_Text_DeanPostBattle, MSGBOX_AUTOCLOSE
	end

BattleMarsh_Text_DeanIntro:
	.string "Service and sacrifice, those are\n"
	.string "the tenets of being a Ranger!$"

BattleMarsh_Text_DeanDefeat:
	.string "I sacrificed my Pokémon in vain…$"

BattleMarsh_Text_DeanPostBattle:
	.string "I serve the people!$"

BattleMarsh_Text_DeanRematchIntro:
	.string "Prepare to get served!$"

BattleMarsh_EventScript_Shane::
	trainerbattle_single TRAINER_SHANE_1, BattleMarsh_Text_ShaneIntro, BattleMarsh_Text_ShaneDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleMarsh_EventScript_ShaneRematch
	msgbox BattleMarsh_Text_ShanePostBattle, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_ShaneRematch::
	trainerbattle_rematch TRAINER_SHANE_1, BattleMarsh_Text_ShaneRematchIntro, BattleMarsh_Text_ShaneDefeat
	msgbox BattleMarsh_Text_ShanePostBattle, MSGBOX_AUTOCLOSE
	end

BattleMarsh_Text_ShaneIntro:
	.string "I'm the groundskeeper for the\n"
	.string "Battle Marsh.\p"
	.string "Don't mess anything up!$"

BattleMarsh_Text_ShaneDefeat:
	.string "It was just a polite warning…$"

BattleMarsh_Text_ShanePostBattle:
	.string "Working here, I've met my fair\n"
	.string "share of impressive Trainers.$"

BattleMarsh_Text_ShaneRematchIntro:
	.string "I'm the groundskeeper for the\n"
	.string "Battle Marsh.\p"
	.string "Back to cause trouble, are you?$"

BattleMarsh_EventScript_Earl::
	trainerbattle_single TRAINER_EARL_1, BattleMarsh_Text_EarlIntro, BattleMarsh_Text_EarlDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleMarsh_EventScript_EarlRematch
	msgbox BattleMarsh_Text_EarlPostBattle, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_EarlRematch::
	trainerbattle_rematch TRAINER_EARL_1, BattleMarsh_Text_EarlRematchIntro, BattleMarsh_Text_EarlRematchDefeat
	msgbox BattleMarsh_Text_EarlPostBattle, MSGBOX_AUTOCLOSE
	end

BattleMarsh_Text_EarlIntro:
	.string "Are you headed for Telmurk City?\n"
	.string "You'd better be tough enough!$"

BattleMarsh_Text_EarlDefeat:
	.string "Yeah, I think you'll be fine there.$"

BattleMarsh_Text_EarlPostBattle:
	.string "The gangsters that run\n"
	.string "Telmurk City are unforgiving…$"

BattleMarsh_Text_EarlRematchIntro:
	.string "Are you tough enough to rebattle\n"
	.string "me? Let's find out!$"

BattleMarsh_Text_EarlRematchDefeat:
	.string "Yeah, I think you're still tough\n"
	.string "enough…$"

BattleMarsh_EventScript_Jennie::
	trainerbattle_single TRAINER_JENNIE_1, BattleMarsh_Text_JennieIntro, BattleMarsh_Text_JennieDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleMarsh_EventScript_JennieRematch
	msgbox BattleMarsh_Text_JenniePostBattle, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_JennieRematch::
	trainerbattle_rematch TRAINER_JENNIE_1, BattleMarsh_Text_JennieIntro, BattleMarsh_Text_JennieDefeat
	msgbox BattleMarsh_Text_JenniePostBattle, MSGBOX_AUTOCLOSE
	end

BattleMarsh_Text_JennieIntro:
	.string "You never know what you'll find in\n"
	.string "the swamp!$"

BattleMarsh_Text_JennieDefeat:
	.string "I just meant weird mushrooms…$"

BattleMarsh_Text_JenniePostBattle:
	.string "I plan to make a delicious stew\n"
	.string "with the ingredients I've found\l"
	.string "out here!$"

BattleMarsh_EventScript_Lloyd::
	trainerbattle_single TRAINER_LLOYD_1, BattleMarsh_Text_LloydIntro, BattleMarsh_Text_LloydDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleMarsh_EventScript_LloydRematch
	msgbox BattleMarsh_Text_LloydPostBattle, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_LloydRematch::
	trainerbattle_rematch TRAINER_LLOYD_1, BattleMarsh_Text_LloydRematchIntro, BattleMarsh_Text_LloydDefeat
	msgbox BattleMarsh_Text_LloydPostBattle, MSGBOX_AUTOCLOSE
	end

BattleMarsh_Text_LloydIntro:
	.string "I'm scouting here for my boss.$"

BattleMarsh_Text_LloydDefeat:
	.string "You're scary strong, kid!$"

BattleMarsh_Text_LloydPostBattle:
	.string "I wonder what {COLOR GREEN}Akuto{COLOR BLUE} will think\n"
    .string "of you…$"

BattleMarsh_Text_LloydRematchIntro:
	.string "Back for more, eh kid?$"

BattleMarsh_EventScript_Doris::
	trainerbattle_single TRAINER_DORIS_1, BattleMarsh_Text_DorisIntro, BattleMarsh_Text_DorisDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleMarsh_EventScript_DorisRematch
	msgbox BattleMarsh_Text_DorisPostBattle, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_DorisRematch::
	trainerbattle_rematch TRAINER_DORIS_1, BattleMarsh_Text_DorisRematchIntro, BattleMarsh_Text_DorisDefeat
	msgbox BattleMarsh_Text_DorisPostBattle, MSGBOX_AUTOCLOSE
	end

BattleMarsh_Text_DorisIntro:
	.string "Are you a part of that heinous\n"
    .string "gang?$"

BattleMarsh_Text_DorisDefeat:
	.string "Sorry for judging you…$"

BattleMarsh_Text_DorisPostBattle:
	.string "Be careful if you're going into\n"
    .string "Telmurk, okay?$"

BattleMarsh_Text_DorisRematchIntro:
	.string "I presume you're prepared to lose\n"
    .string "if you're back for more!$"

BattleMarsh_EventScript_Carla::
	trainerbattle_single TRAINER_CARLA_1, BattleMarsh_Text_CarlaIntro, BattleMarsh_Text_CarlaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq BattleMarsh_EventScript_CarlaRematch
	msgbox BattleMarsh_Text_CarlaPostBattle, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_CarlaRematch::
	trainerbattle_rematch TRAINER_CARLA_1, BattleMarsh_Text_CarlaRematchIntro, BattleMarsh_Text_CarlaDefeat
	msgbox BattleMarsh_Text_CarlaPostBattle, MSGBOX_AUTOCLOSE
	end

BattleMarsh_Text_CarlaIntro:
	.string "I'm not here to play games.\n"
	.string "I'll crush you!$"

BattleMarsh_Text_CarlaDefeat:
	.string "Wow, you outmatched me.$"

BattleMarsh_Text_CarlaPostBattle:
	.string "Here at the Battle Marsh, we all\n"
	.string "take battling very seriously!$"

BattleMarsh_Text_CarlaRematchIntro:
	.string "This time, I'll crush you for real!$"

BattleMarsh_EventScript_AceTrainerM::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_DRIFLOON
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	goto_if_set FLAG_BATTLE_MARSH_NPC_TRADE_COMPLETED, BattleMarsh_EventScript_TradeCompleted
	msgbox BattleMarsh_Text_IKeepLosingInThere, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleMarsh_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	lock
	copyvar VAR_0x800A, VAR_0x8004
	compare VAR_0x8004, 255
	goto_if_eq BattleMarsh_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne BattleMarsh_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname 0, VAR_0x8009
	msgbox BattleMarsh_Text_MaybeNowMyLuckWillChange, MSGBOX_DEFAULT
	setflag FLAG_BATTLE_MARSH_NPC_TRADE_COMPLETED
	release
	end

BattleMarsh_EventScript_DeclineTrade::
	msgbox BattleMarsh_Text_IllKeepTrainingThen, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_NotRequestedMon::
	bufferspeciesname 0, VAR_0x8009
	msgbox BattleMarsh_Text_YouProbablyWontLastLong, MSGBOX_DEFAULT
	release
	end

BattleMarsh_EventScript_TradeCompleted::
	msgbox BattleMarsh_Text_HaveYouWonAnyBattles, MSGBOX_DEFAULT
	release
	end

BattleMarsh_Text_IKeepLosingInThere:
	.string "I keep losing in there…\p"
	.string "My {STR_VAR_2} just isn't\n"
	.string "up to scratch!\p"
	.string "I'll trade it to you for\n"
	.string "an {STR_VAR_1}!\p"
	.string "That's fair, right?$"

BattleMarsh_Text_MaybeNowMyLuckWillChange:
	.string "Great!\n"
	.string "Maybe now my luck will change…$"

BattleMarsh_Text_YouProbablyWontLastLong:
	.string "You probably won't last long in\n"
	.string "the Battle Marsh if you think\l"
	.string "that's an {STR_VAR_1}!$"

BattleMarsh_Text_IllKeepTrainingThen:
	.string "I'll keep training, then!$"

BattleMarsh_Text_HaveYouWonAnyBattles:
	.string "Have you won any battles in there\n"
	.string "with my {STR_VAR_2}?$"

BattleMarsh_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BATTLE_MARSH_CHOICE_SPECS, BattleMarsh_EventScript_ReceivedChoiceSpecs
	msgbox BattleMarsh_Text_ImOnAWinStreak, MSGBOX_DEFAULT
	giveitem ITEM_CHOICE_SPECS
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_BATTLE_MARSH_CHOICE_SPECS
	goto BattleMarsh_EventScript_ReceivedChoiceSpecs
	end

BattleMarsh_EventScript_ReceivedChoiceSpecs:
	msgbox BattleMarsh_Text_ExplainChoiceSpecs, MSGBOX_DEFAULT
	release
	end

BattleMarsh_Text_ImOnAWinStreak:
	.string "I'm on a win streak!\n"
	.string "I should share my success.\p"
	.string "I know!\n"
	.string "You, take this!$"

BattleMarsh_Text_ExplainChoiceSpecs:
	.string "Give a Pokémon those\n"
	.string "Choice Specs to hold.\p"
	.string "It boosts their Special Attack,\n"
	.string "but limits them to only one move.\p"
	.string "It's a tricky trade-off,\n"
	.string "but it's worth it.$"

BattleMarsh_EventScript_BattleGirl::
	msgbox BattleMarsh_Text_ItMustTakeALotOfWork, MSGBOX_NPC
	end

BattleMarsh_Text_ItMustTakeALotOfWork:
	.string "It must take a lot of work for the\n"
	.string "Battle Marsh to clean these pools!\p"
	.string "Maybe a swamp isn't the best place\n"
	.string "for a prestigious battle facility…$"

BattleMarsh_EventScript_Lady::
	msgbox BattleMarsh_Text_HeyCuteGasMask, MSGBOX_NPC
	end

BattleMarsh_Text_HeyCuteGasMask:
	.string "Hey, cute Gas Mask!\p"
	.string "Uh…\p"
	.string "…Do you think I need one?$"

BattleMarsh_EventScript_Gentleman::
	msgbox BattleMarsh_Text_HaveYouHeardTheRumorsOfArbokMan, MSGBOX_NPC
	end

BattleMarsh_Text_HaveYouHeardTheRumorsOfArbokMan:
	.string "Have you heard the rumors of\n"
	.string "Arbok-Man?\p"
	.string "He's a masked, crime-fighting\n"
	.string "vigilante!\p"
	.string "Although he doesn't seem very\n"
	.string "effective…$"

BattleMarsh_EventScript_Biker::
	msgbox BattleMarsh_Text_ImADaredevil, MSGBOX_NPC
	end

BattleMarsh_Text_ImADaredevil:
	.string "I'm a daredevil, cycling at high\n"
	.string "speed across such a rickety bridge!$"
