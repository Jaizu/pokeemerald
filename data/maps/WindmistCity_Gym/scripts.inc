WindmistCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, WindmistCity_Gym_OnResume
	.byte 0

WindmistCity_Gym_OnResume:
	compare VAR_WINDMIST_GYM_STATE, 1
	call_if_ge WindmistCity_Gym_EventScript_MeltPillars0
	compare VAR_WINDMIST_GYM_STATE, 2
	call_if_ge WindmistCity_Gym_EventScript_MeltPillars1
	compare VAR_WINDMIST_GYM_STATE, 3
	call_if_ge WindmistCity_Gym_EventScript_MeltPillars2
	end

WindmistCity_Gym_EventScript_MeltPillars0:
	setmetatile 2, 23, METATILE_DewfordGym_GymFloor_Shadow, 0
	setmetatile 3, 23, METATILE_DewfordGym_GymFloor, 0
	setmetatile 4, 23, METATILE_DewfordGym_GymFloor, 0
	setmetatile 5, 23, METATILE_DewfordGym_GymFloor, 0
	setmetatile 6, 23, METATILE_DewfordGym_GymFloor, 0
	setmetatile 2, 24, METATILE_DewfordGym_GymFloorSouthBorder_Shadow, 0
	setmetatile 3, 24, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 4, 24, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 5, 24, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 6, 24, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 2, 25, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 3, 25, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 4, 25, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 5, 25, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 6, 25, METATILE_DewfordGym_MeltedPillar, 0
	return

WindmistCity_Gym_EventScript_MeltPillars1:
	setmetatile 17, 21, METATILE_DewfordGym_GymFloor_Shadow, 0
	setmetatile 18, 21, METATILE_DewfordGym_GymFloor, 0
	setmetatile 19, 21, METATILE_DewfordGym_GymFloor, 0
	setmetatile 20, 21, METATILE_DewfordGym_GymFloor, 0
	setmetatile 17, 22, METATILE_DewfordGym_GymFloorSouthBorder_Shadow, 0
	setmetatile 18, 22, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 19, 22, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 20, 22, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 17, 23, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 18, 23, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 19, 23, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 20, 23, METATILE_DewfordGym_MeltedPillar, 0
	return

WindmistCity_Gym_EventScript_MeltPillars2:
	setmetatile 28, 9, METATILE_DewfordGym_GymFloor_Shadow, 0
	setmetatile 29, 9, METATILE_DewfordGym_GymFloor, 0
	setmetatile 30, 9, METATILE_DewfordGym_GymFloor, 0
	setmetatile 31, 9, METATILE_DewfordGym_GymFloor, 0
	setmetatile 28, 10, METATILE_DewfordGym_GymFloorSouthBorder_Shadow, 0
	setmetatile 29, 10, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 30, 10, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 31, 10, METATILE_DewfordGym_GymFloorSouthBorder, 0
	setmetatile 28, 11, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 29, 11, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 30, 11, METATILE_DewfordGym_MeltedPillar, 0
	setmetatile 31, 11, METATILE_DewfordGym_MeltedPillar, 0
	return

WindmistCity_Gym_EventScript_GymSign::
	msgbox WindmistCity_Gym_Text_GymSign, MSGBOX_SIGN
	end

WindmistCity_Gym_Text_GymSign:
	.string "Windmist City Pokémon Gym\p"
	.string "Leader: Nina\n"
	.string "“The Furnace in the Snow.”$"

WindmistCity_Gym_EventScript_JimGai::
	lock
	faceplayer
	goto_if_set FLAG_BADGE03_GET, WindmistCity_Gym_EventScript_CongratulatePlayer
	msgbox WindmistCity_Gym_Text_WelcomeChamp, MSGBOX_DEFAULT
	release
	end

WindmistCity_Gym_EventScript_CongratulatePlayer:
	msgbox WindmistCity_Gym_Text_NiceGoingChamp, MSGBOX_DEFAULT
	release
	end

WindmistCity_Gym_Text_WelcomeChamp:
	.string "Hey!\p"
	.string "If you want to take down Nina, you\n"
	.string "need to know about her team, right?\p"
	.string "Well, she specializes in the\n"
	.string "feisty {COLOR GREEN}Fire-type{COLOR BLUE}!\p"
	.string "You should prepare yourself with a\n"
	.string "{COLOR GREEN}Water-type Pokémon{COLOR BLUE}!$"

WindmistCity_Gym_Text_NiceGoingChamp:
	.string "Nice one, {PLAYER}!\n"
	.string "You must've battled well!$"

WindmistCity_Gym_EventScript_Hector::
	trainerbattle_single TRAINER_HECTOR, WindmistCity_Gym_Text_HectorIntro, WindmistCity_Gym_Text_HectorDefeat, WindmistCity_Gym_EventScript_HectorDefeated
	msgbox WindmistCity_Gym_Text_HectorPostBattle, MSGBOX_AUTOCLOSE
	end

WindmistCity_Gym_EventScript_HectorDefeated:
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox WindmistCity_Gym_Text_HectorMelt, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	fadescreen FADE_TO_WHITE
	playse SE_W052
	call WindmistCity_Gym_EventScript_MeltPillars0
	special DrawWholeMapView
	waitse
	setvar VAR_WINDMIST_GYM_STATE, 1
	fadescreen FADE_FROM_WHITE
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_Gym_Text_HectorIntro:
	.string "Here's a quick rundown on the Gym:\n"
	.string "beat a Trainer, the ice melts!\p"
	.string "Get it?\n"
	.string "You'll learn pretty fast!$"

WindmistCity_Gym_Text_HectorDefeat:
	.string "Ice cold!\n"
	.string "You overwhelmed me!$"

WindmistCity_Gym_Text_HectorPostBattle:
	.string "You can pass now!$"

WindmistCity_Gym_Text_HectorMelt:
	.string "You beat me, so I'll melt the\n"
	.string "pillars!$"

WindmistCity_Gym_EventScript_Angelica::
	trainerbattle_single TRAINER_ANGELICA, WindmistCity_Gym_Text_AngelicaIntro, WindmistCity_Gym_Text_AngelicaDefeat, WindmistCity_Gym_EventScript_AngelicaDefeated
	msgbox WindmistCity_Gym_Text_AngelicaPostBattle, MSGBOX_AUTOCLOSE
	end

WindmistCity_Gym_EventScript_AngelicaDefeated:
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox WindmistCity_Gym_Text_AngelicaMelt, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	fadescreen FADE_TO_WHITE
	playse SE_W052
	call WindmistCity_Gym_EventScript_MeltPillars1
	special DrawWholeMapView
	waitse
	setvar VAR_WINDMIST_GYM_STATE, 2
	fadescreen FADE_FROM_WHITE
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_Gym_Text_AngelicaIntro:
	.string "So, that first Trainer was a\n"
	.string "breeze, eh?\p"
	.string "Well, it's time to turn up the\n"
	.string "heat!$"

WindmistCity_Gym_Text_AngelicaDefeat:
	.string "I overheated…$"

WindmistCity_Gym_Text_AngelicaPostBattle:
	.string "There you go, you can pass!$"

WindmistCity_Gym_Text_AngelicaMelt:
	.string "I can't believe I lost…\p"
	.string "Well, a deal's a deal!$"

WindmistCity_Gym_EventScript_Junior::
	trainerbattle_single TRAINER_JUNIOR, WindmistCity_Gym_Text_JuniorIntro, WindmistCity_Gym_Text_JuniorDefeat, WindmistCity_Gym_EventScript_JuniorDefeated
	msgbox WindmistCity_Gym_Text_JuniorPostBattle, MSGBOX_AUTOCLOSE
	end

WindmistCity_Gym_EventScript_JuniorDefeated:
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox WindmistCity_Gym_Text_JuniorMelt, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	fadescreen FADE_TO_WHITE
	playse SE_W052
	call WindmistCity_Gym_EventScript_MeltPillars2
	special DrawWholeMapView
	waitse
	setvar VAR_WINDMIST_GYM_STATE, 3
	fadescreen FADE_FROM_WHITE
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_Gym_Text_JuniorIntro:
	.string "Those other two buffoons may have\n"
	.string "lost to you, but me…\p"
	.string "I'm Nina's strongest Trainer.\n"
	.string "I won't lose to you!$"

WindmistCity_Gym_Text_JuniorDefeat:
	.string "I-impossible!$"

WindmistCity_Gym_Text_JuniorPostBattle:
	.string "Ugh, you can pass, or, whatever…$"

WindmistCity_Gym_Text_JuniorMelt:
	.string "T-this… This can't be happening!\n"
	.string "Ugh… You can pass…$"

WindmistCity_Gym_EventScript_Nina::
	trainerbattle_single TRAINER_LEADER_NINA_1, WindmistCity_Gym_Text_NinaIntro, WindmistCity_Gym_Text_NinaDefeat, WindmistCity_Gym_EventScript_NinaDefeated, NO_MUSIC
	call_if_unset FLAG_RECEIVED_TM43, WindmistCity_Gym_EventScript_GiveFlameCharge
	msgbox WindmistCity_Gym_Text_NinaPostBattle, MSGBOX_DEFAULT
	release
	end

WindmistCity_Gym_EventScript_NinaDefeated:
	setflag FLAG_BADGE03_GET
	call WindmistCity_Gym_EventScript_GiveFlameCharge
	setvar VAR_0x8008, 2
	call Common_EventScript_SetGymTrainers
	setflag FLAG_DEFEATED_WINDMIST_GYM
	setvar VAR_WINDMIST_CITY_STATE, 1
	clearflag FLAG_HIDE_WINDMIST_CITY_REDWOOD
	release
	end

WindmistCity_Gym_EventScript_GiveFlameCharge:
	msgbox WindmistCity_Gym_Text_TakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM43
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_TM43
	msgbox WindmistCity_Gym_Text_ExplainTM43, MSGBOX_DEFAULT
	return
	
WindmistCity_Gym_Text_NinaIntro:
	.string "So! You managed to sear my\n"
	.string "Gym Trainers?\p"
	.string "Nice going, hotshot!\n"
	.string "Not many have done that!\p"
	.string "But…\n"
	.string "Have you burned yourself out?\p"
	.string "Are you ready for the maelstrom of\n"
	.string "fire my Pokémon and I will bring?\p"
	.string "We burn with a fiery passion for\n"
	.string "battling. I have but one question!\p"
	.string "Does that same flame burn within\n"
	.string "you?\p"
	.string "There's only one way to find out!{PLAY_BGM}{MUS_RG_EXEYE}$"

WindmistCity_Gym_Text_NinaDefeat:
	.string "What? No way this happened!\n"
	.string "Here, take the Ember Badge.\p"
	.string "{PLAYER} received the Ember Badge\n"
	.string "from Nina!{PAUSE_MUSIC}{PLAY_BGM}{MUS_ME_BACHI}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}\p"
	.string "…I can't believe I actually lost.$"

WindmistCity_Gym_Text_TakeThis:
	.string "Take this!$"

WindmistCity_Gym_Text_ExplainTM43:
	.string "TM43 is Flame Charge.\p"
	.string "When a Pokémon uses Flame Charge,\n"
	.string "they become cloaked in fire…\p"
	.string "And then they strike!\n"
	.string "Wahahaha!\p"
	.string "The adrenaline rush boosts their\n"
	.string "Speed stat, too. Isn't that great?\p"
	.string "Flame Charge is a personal favorite\n"
	.string "of mine.\p"
	.string "Thanks again for that spicy battle,\n"
	.string "{PLAYER}!$"

WindmistCity_Gym_Text_NinaPostBattle:
	.string "Our battle was hot,\n"
	.string "{PLAYER}!\p"
	.string "You've got potential!\n"
	.string "The next Gym is in Valoon Town.$"
