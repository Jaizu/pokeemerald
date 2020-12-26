.set LOCALID_JAMES, 2
.set LOCALID_CLAUDE, 3
.set LOCALID_KENT, 4
.set LOCALID_RUBY, 5
.set LOCALID_KEIGO, 6
.set LOCALID_CALE, 7

ValoonTown_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, ValoonTown_Gym_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, ValoonTown_Gym_OnTransition
	.byte 0

ValoonTown_Gym_OnLoad::
	call_if_set FLAG_VALOON_GYM_PATH_CLEARED, ValoonTown_Gym_EventScript_ClearPathAndActivateCombeeTiles
	end

ValoonTown_Gym_EventScript_ClearPathAndActivateCombeeTiles:
	setmetatile  7,  5, METATILE_DewfordGym_ClearedPath, 0
	setmetatile  3, 14, METATILE_DewfordGym_CombeeTile_Active, 0
	setmetatile 11, 14, METATILE_DewfordGym_CombeeTile_Active, 0
	setmetatile  7, 11, METATILE_DewfordGym_CombeeTile_Active, 0
	setmetatile 11,  6, METATILE_DewfordGym_CombeeTile_Active, 0
	setmetatile  3,  4, METATILE_DewfordGym_CombeeTile_Active, 0
	return

ValoonTown_Gym_OnTransition::
	call_if_unset FLAG_VALOON_GYM_PATH_CLEARED, ValoonTown_Gym_EventScript_ResetGymState
	call_if_defeated TRAINER_JAMES, ValoonTown_Gym_EventScript_MoveJames
	call_if_defeated TRAINER_CLAUDE, ValoonTown_Gym_EventScript_MoveClaude
	call_if_defeated TRAINER_KENT, ValoonTown_Gym_EventScript_MoveKent
	call_if_defeated TRAINER_RUBY, ValoonTown_Gym_EventScript_MoveRuby
	call_if_defeated TRAINER_KEIGO, ValoonTown_Gym_EventScript_MoveKeigo
	call_if_defeated TRAINER_CALE, ValoonTown_Gym_EventScript_MoveCale
	end

ValoonTown_Gym_EventScript_ResetGymState::
	setvar VAR_VALOON_GYM_STATE, 0
	return

ValoonTown_Gym_EventScript_MoveJames::
	setobjectxyperm LOCALID_JAMES, 4, 13
	setobjectmovementtype LOCALID_JAMES, MOVEMENT_TYPE_FACE_DOWN
	return

ValoonTown_Gym_EventScript_MoveClaude::
	setobjectxyperm LOCALID_CLAUDE, 10, 15
	setobjectmovementtype LOCALID_CLAUDE, MOVEMENT_TYPE_FACE_UP
	return

ValoonTown_Gym_EventScript_MoveKent::
	setobjectxyperm LOCALID_KENT, 6, 12
	setobjectmovementtype LOCALID_KENT, MOVEMENT_TYPE_FACE_RIGHT
	return

ValoonTown_Gym_EventScript_MoveRuby::
	setobjectxyperm LOCALID_RUBY, 8, 10
	setobjectmovementtype LOCALID_RUBY, MOVEMENT_TYPE_FACE_DOWN
	return

ValoonTown_Gym_EventScript_MoveKeigo::
	setobjectxyperm LOCALID_KEIGO, 12, 6
	setobjectmovementtype LOCALID_KEIGO, MOVEMENT_TYPE_FACE_LEFT
	return

ValoonTown_Gym_EventScript_MoveCale::
	setobjectxyperm LOCALID_CALE, 2, 5
	setobjectmovementtype LOCALID_CALE, MOVEMENT_TYPE_FACE_RIGHT
	return

ValoonTown_Gym_EventScript_GymSign::
	msgbox ValoonTown_Gym_Text_GymSign, MSGBOX_SIGN
	end

ValoonTown_Gym_Text_GymSign::
	.string "Valoon Town Pokémon Gym\p"
	.string "Leader: Vernon\n"
	.string "“He wouldn't harm a Joltik!”$"

ValoonTown_Gym_EventScript_JimGai::
	lock
	faceplayer
	goto_if_set FLAG_BADGE04_GET, ValoonTown_Gym_EventScript_CongratulatePlayer
	msgbox ValoonTown_Gym_Text_WelcomeChamp, MSGBOX_DEFAULT
	release
	end

ValoonTown_Gym_EventScript_CongratulatePlayer:
	msgbox ValoonTown_Gym_Text_NiceGoingChamp, MSGBOX_DEFAULT
	release
	end

ValoonTown_Gym_Text_WelcomeChamp:
	.string "Hey, champ!\n"
	.string "We just re-opened.\p"
	.string "Vernon was busy over at the\n"
	.string "Bug-Catching Contest.\p"
	.string "I heard he came first place!\p"
	.string "Anyway, to challenge him you'll\n"
	.string "need to activate each Combee tile.\p"
	.string "Once all the Combee are smiling,\n"
	.string "the honeycomb will clear!\p"
	.string "Simple, right?$"

ValoonTown_Gym_Text_NiceGoingChamp:
	.string "Nice going, champ!\p"
	.string "Not many Trainers manage to take\n"
	.string "Vernon down, so good on you!$"

ValoonTown_Gym_EventScript_MoveLastTalkedDown:
	applymovement VAR_LAST_TALKED, Common_Movement_WalkDown
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

ValoonTown_Gym_EventScript_MoveLastTalkedUp:
	applymovement VAR_LAST_TALKED, Common_Movement_WalkUp
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

ValoonTown_Gym_EventScript_MoveLastTalkedLeft:
	applymovement VAR_LAST_TALKED, Common_Movement_WalkLeft
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

ValoonTown_Gym_EventScript_MoveLastTalkedRight:
	applymovement VAR_LAST_TALKED, Common_Movement_WalkRight
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return
	
ValoonTown_Gym_EventScript_James::
	trainerbattle_single TRAINER_JAMES, ValoonTown_Gym_Text_JamesIntro, ValoonTown_Gym_Text_JamesDefeat, ValoonTown_Gym_EventScript_JamesDefeated
	msgbox ValoonTown_Gym_Text_JamesPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonTown_Gym_EventScript_JamesDefeated:
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox ValoonTown_Gym_Text_JamesClearPath, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8005, 13
	call_if_eq ValoonTown_Gym_EventScript_MoveLastTalkedDown
	compare VAR_0x8005, 13
	call_if_ne ValoonTown_Gym_EventScript_MoveLastTalkedUp
	call ValoonTown_Gym_EventScript_MoveJames
	release
	end

ValoonTown_Gym_Text_JamesIntro:
	.string "I'm more than just a Bug Catcher,\n"
	.string "I'm a maniac!$"

ValoonTown_Gym_Text_JamesDefeat:
	.string "Ah!\n"
	.string "No!$"

ValoonTown_Gym_Text_JamesPostBattle:
	.string "I can't believe you beat me!$"

ValoonTown_Gym_Text_JamesClearPath:
	.string "No!\n"
	.string "My Bug-types!$"

ValoonTown_Gym_EventScript_Claude::
	trainerbattle_single TRAINER_CLAUDE, ValoonTown_Gym_Text_ClaudeIntro, ValoonTown_Gym_Text_ClaudeDefeat, ValoonTown_Gym_EventScript_ClaudeDefeated
	msgbox ValoonTown_Gym_Text_ClaudePostBattle, MSGBOX_AUTOCLOSE
	end

ValoonTown_Gym_EventScript_ClaudeDefeated:
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox ValoonTown_Gym_Text_ClaudeClearPath, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8005, 15
	call_if_eq ValoonTown_Gym_EventScript_MoveLastTalkedUp
	compare VAR_0x8005, 15
	call_if_ne ValoonTown_Gym_EventScript_MoveLastTalkedDown
	call ValoonTown_Gym_EventScript_MoveClaude
	release
	end

ValoonTown_Gym_Text_ClaudeIntro:
	.string "If you can beat my Pokémon, I'll\n"
	.string "let you get to the Combee tile!$"

ValoonTown_Gym_Text_ClaudeDefeat:
	.string "I'm done for!$"

ValoonTown_Gym_Text_ClaudePostBattle:
	.string "Even though I lost, I'm still a\n"
	.string "proud user of Bug-types!$"

ValoonTown_Gym_Text_ClaudeClearPath:
	.string "You won, fair and square!$"

ValoonTown_Gym_EventScript_Kent::
	trainerbattle_single TRAINER_KENT, ValoonTown_Gym_Text_KentIntro, ValoonTown_Gym_Text_KentDefeat, ValoonTown_Gym_EventScript_KentDefeated
	msgbox ValoonTown_Gym_Text_KentPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonTown_Gym_EventScript_KentDefeated:
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox ValoonTown_Gym_Text_KentClearPath, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 6
	call_if_eq ValoonTown_Gym_EventScript_MoveLastTalkedRight
	compare VAR_0x8004, 6
	call_if_ne ValoonTown_Gym_EventScript_MoveLastTalkedLeft
	call ValoonTown_Gym_EventScript_MoveKent
	release
	end

ValoonTown_Gym_Text_KentIntro:
	.string "Are you ready to fight?\n"
	.string "I won't hold back!$"

ValoonTown_Gym_Text_KentDefeat:
	.string "I didn't not-hold-back enough!$"

ValoonTown_Gym_Text_KentPostBattle:
	.string "Durant get hunted by the\n"
	.string "Fire-type, Heatmor!$"

ValoonTown_Gym_Text_KentClearPath:
	.string "You'll never beat Vernon!$"

ValoonTown_Gym_EventScript_Ruby::
	trainerbattle_single TRAINER_RUBY, ValoonTown_Gym_Text_RubyIntro, ValoonTown_Gym_Text_RubyDefeat, ValoonTown_Gym_EventScript_RubyDefeated
	msgbox ValoonTown_Gym_Text_RubyPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonTown_Gym_EventScript_RubyDefeated:
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox ValoonTown_Gym_Text_RubyClearPath, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8005, 10
	call_if_eq ValoonTown_Gym_EventScript_MoveLastTalkedRight
	compare VAR_0x8005, 10
	call_if_ne ValoonTown_Gym_EventScript_MoveLastTalkedUp
	call ValoonTown_Gym_EventScript_MoveRuby
	release
	end

ValoonTown_Gym_Text_RubyIntro:
	.string "Kaboom!\n"
	.string "Are you ready?$"

ValoonTown_Gym_Text_RubyDefeat:
	.string "Boom!\n"
	.string "And it's over!$"

ValoonTown_Gym_Text_RubyPostBattle:
	.string "Kaboom!\n"
	.string "Explosion is a risky move.$"

ValoonTown_Gym_Text_RubyClearPath:
	.string "Boom!\n"
	.string "You can pass.$"

ValoonTown_Gym_EventScript_Keigo::
	trainerbattle_single TRAINER_KEIGO, ValoonTown_Gym_Text_KeigoIntro, ValoonTown_Gym_Text_KeigoDefeat, ValoonTown_Gym_EventScript_KeigoDefeated
	msgbox ValoonTown_Gym_Text_KeigoPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonTown_Gym_EventScript_KeigoDefeated:
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox ValoonTown_Gym_Text_KeigoClearPath, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 12
	call_if_eq ValoonTown_Gym_EventScript_MoveLastTalkedLeft
	compare VAR_0x8004, 12
	call_if_ne ValoonTown_Gym_EventScript_MoveLastTalkedRight
	call ValoonTown_Gym_EventScript_MoveKeigo
	release
	end

ValoonTown_Gym_Text_KeigoIntro:
	.string "Bug-types are my specialty!\n"
	.string "I won't lose.$"

ValoonTown_Gym_Text_KeigoDefeat:
	.string "I guess losing is my specialty too.$"

ValoonTown_Gym_Text_KeigoPostBattle:
	.string "Vernon is the best Bug-type\n"
	.string "Trainer I know!$"

ValoonTown_Gym_Text_KeigoClearPath:
	.string "That was a fun battle.\n"
	.string "I'll move out of your way.$"

ValoonTown_Gym_EventScript_Cale::
	trainerbattle_single TRAINER_CALE, ValoonTown_Gym_Text_CaleIntro, ValoonTown_Gym_Text_CaleDefeat, ValoonTown_Gym_EventScript_CaleDefeated
	msgbox ValoonTown_Gym_Text_CalePostBattle, MSGBOX_AUTOCLOSE
	end

ValoonTown_Gym_EventScript_CaleDefeated:
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox ValoonTown_Gym_Text_CaleClearPath, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 2
	call_if_eq ValoonTown_Gym_EventScript_MoveLastTalkedRight
	compare VAR_0x8004, 2
	call_if_ne ValoonTown_Gym_EventScript_MoveLastTalkedLeft
	call ValoonTown_Gym_EventScript_MoveCale
	release
	end

ValoonTown_Gym_Text_CaleIntro:
	.string "I won't be the Trainer that lets\n"
	.string "you get to Vernon!\p"
	.string "Your challenge ends here!$"

ValoonTown_Gym_Text_CaleDefeat:
	.string "Aw man, I was certain you were\n"
	.string "going to be weak!$"

ValoonTown_Gym_Text_CalePostBattle:
	.string "I suppose I lost…$"

ValoonTown_Gym_Text_CaleClearPath:
	.string "Well, you won!$"

ValoonTown_Gym_EventScript_Vernon::
	trainerbattle_single TRAINER_LEADER_VERNON_1, ValoonTown_Gym_Text_VernonIntro, ValoonTown_Gym_Text_VernonDefeat, ValoonTown_Gym_EventScript_VernonDefeated, NO_MUSIC
	call_if_unset FLAG_RECEIVED_TM49, ValoonTown_Gym_EventScript_GiveUTurn
	msgbox ValoonTown_Gym_Text_VernonPostBattle, MSGBOX_DEFAULT
	release
	end

ValoonTown_Gym_EventScript_VernonDefeated:
	setflag FLAG_BADGE04_GET
	call ValoonTown_Gym_EventScript_GiveUTurn
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers
	setflag FLAG_DEFEATED_VALOON_GYM
	setvar VAR_VALOON_TOWN_STATE, 2
	release
	end

ValoonTown_Gym_EventScript_GiveUTurn:
	msgbox ValoonTown_Gym_Text_TakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM49
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_TM49
	msgbox ValoonTown_Gym_Text_ExplainTM49, MSGBOX_DEFAULT
	return
	
ValoonTown_Gym_Text_VernonIntro:
	.string "Why, hey there!\p"
	.string "Say, you're the newcomer that came\n"
	.string "third in the Bug-Catching Contest!\p"
	.string "It was mighty fun competing\n"
	.string "against you.\p"
	.string "I find talented Pokémon hunters\n"
	.string "tend to be equally great battlers!\p"
	.string "Why don't we put that theory to\n"
	.string "the test?{PLAY_BGM}{MUS_RG_EXEYE}$"

ValoonTown_Gym_Text_VernonDefeat:
	.string "It looks like my theory was right!\n"
	.string "Take this, please.\p"
	.string "{PLAYER} received the\n"
	.string "Honeycomb Badge from Vernon!{PAUSE_MUSIC}{PLAY_BGM}{MUS_ME_BACHI}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}\p"
	.string "That fight was fun!$"

ValoonTown_Gym_Text_TakeThis:
	.string "Oh, please, don't leave yet!\n"
	.string "I have a special surprise for you…$"

ValoonTown_Gym_Text_ExplainTM49:
	.string "That right there is my favorite\n"
	.string "move ever -- U-turn!\p"
	.string "It lets your Pokémon get out of\n"
	.string "battle in the nick of time.\p"
	.string "It also deals a hefty amount of\n"
	.string "damage, too.$"

ValoonTown_Gym_Text_VernonPostBattle:
	.string "I really enjoyed our battle.\n"
	.string "I had so much fun!$"
