.set LOCALID_ERIC, 4

ValoonWay_MapScripts::
	.byte 0

ValoonWay_EventScript_RouteSign::
	msgbox ValoonWay_Text_RouteSign, MSGBOX_SIGN
	end

ValoonWay_Text_RouteSign::
	.string "Valoon Way\n"
	.string "{LEFT_ARROW} Sharpgust Span {RIGHT_ARROW} Valoon Town$"

ValoonWay_EventScript_TremorTrigger::
	lockall
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_ERIC, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	applymovement LOCALID_ERIC, Common_Movement_Delay48
	waitmovement 0
	setvar VAR_VALOON_WAY_STATE, 1
	releaseall
	end

ValoonWay_EventScript_Natasha::
	trainerbattle_single TRAINER_NATASHA_1, ValoonWay_Text_NatashaIntro, ValoonWay_Text_NatashaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq ValoonWay_EventScript_NatashaRematch
	msgbox ValoonWay_Text_NatashaPostBattle, MSGBOX_DEFAULT
	release
	end

ValoonWay_EventScript_NatashaRematch::
	trainerbattle_rematch TRAINER_NATASHA_1, ValoonWay_Text_NatashaIntro, ValoonWay_Text_NatashaDefeat
	msgbox ValoonWay_Text_NatashaPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonWay_Text_NatashaIntro:
	.string "As a long-distance swimmer, I need\n"
	.string "to perfect my body in every way!$"

ValoonWay_Text_NatashaDefeat:
	.string "Imperfections are unacceptable!$"

ValoonWay_Text_NatashaPostBattle:
	.string "I have to keep training to stay\n"
	.string "fit and strong!$"

ValoonWay_EventScript_Hans::
	trainerbattle_single TRAINER_HANS_1, ValoonWay_Text_HansIntro, ValoonWay_Text_HansDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq ValoonWay_EventScript_HansRematch
	msgbox ValoonWay_Text_HansPostBattle, MSGBOX_DEFAULT
	release
	end

ValoonWay_EventScript_HansRematch::
	trainerbattle_rematch TRAINER_HANS_1, ValoonWay_Text_HansIntro, ValoonWay_Text_HansDefeat
	msgbox ValoonWay_Text_HansPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonWay_Text_HansIntro:
	.string "I swam all the way from Aerous.\n"
	.string "I won't give up now!$"

ValoonWay_Text_HansDefeat:
	.string "I give up, I give up!$"

ValoonWay_Text_HansPostBattle:
	.string "Swimmers and Pokémon Trainers\n"
	.string "alike need stamina and tenacity.$"

ValoonWay_EventScript_Olivia::
	lock
	faceplayer
	goto_if_defeated TRAINER_OLIVIA, ValoonWay_EventScript_OliviaPostBattle
	msgbox ValoonWay_Text_HeyThere, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonWay_EventScript_DeclineOlivia
	msgbox ValoonWay_Text_DontHoldBack, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_OLIVIA, ValoonWay_Text_OliviaDefeat
	goto ValoonWay_EventScript_OliviaPostBattle
	end

ValoonWay_EventScript_DeclineOlivia:
	msgbox ValoonWay_Text_Alright, MSGBOX_DEFAULT
	release
	end

ValoonWay_EventScript_OliviaPostBattle:
	msgbox ValoonWay_Text_WouldYouLikeMeToHeal, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonWay_EventScript_DeclineOlivia
	call Common_EventScript_FieldHeal
	msgbox ValoonWay_Text_ThereYouGo, MSGBOX_DEFAULT
	release
	end

ValoonWay_Text_HeyThere:
	.string "Hey there!\n"
	.string "Would you like a Pokémon battle?\p"
	.string "If you win, I'll heal your Pokémon!\n"
	.string "What do you say?$"

ValoonWay_Text_Alright:
	.string "Alright!$"

ValoonWay_Text_DontHoldBack:
	.string "Don't hold back!$"

ValoonWay_Text_OliviaDefeat:
	.string "Yay, you won!$"

ValoonWay_Text_WouldYouLikeMeToHeal:
	.string "Would you like me to heal\n"
	.string "your Pokémon for you?$"

ValoonWay_Text_ThereYouGo:
	.string "There you go!\n"
	.string "Be careful out there.$"

ValoonWay_EventScript_Eric::
	trainerbattle_single TRAINER_ERIC_1, ValoonWay_Text_EricIntro, ValoonWay_Text_EricDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq ValoonWay_EventScript_EricRematch
	msgbox ValoonWay_Text_EricPostBattle, MSGBOX_DEFAULT
	release
	end

ValoonWay_EventScript_EricRematch::
	trainerbattle_rematch TRAINER_ERIC_1, ValoonWay_Text_EricRematchIntro, ValoonWay_Text_EricRematchDefeat
	msgbox ValoonWay_Text_EricRematchPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonWay_Text_EricIntro:
	.string "Yikes!\n"
	.string "Was that another quake?$"

ValoonWay_Text_EricDefeat:
	.string "You can't expect me to battle\n"
    .string "while the ground is shaking!$"

ValoonWay_Text_EricPostBattle:
	.string "These earthquakes are getting out\n"
    .string "of hand…$"

ValoonWay_Text_EricRematchIntro:
	.string "I'm an Aipom maniac!$"

ValoonWay_Text_EricRematchDefeat:
	.string "Ooh, ooh…\n"
    .string "Ah…$"

ValoonWay_Text_EricRematchPostBattle:
	.string "Is there a Pokémon as elegant and\n"
    .string "graceful as Aipom?\p"
    .string "Yes!\n"
    .string "It's called Ambipom.$"

ValoonWay_EventScript_Doug::
	trainerbattle_single TRAINER_DOUG_1, ValoonWay_Text_DougIntro, ValoonWay_Text_DougDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq ValoonWay_EventScript_DougRematch
	msgbox ValoonWay_Text_DougPostBattle, MSGBOX_DEFAULT
	release
	end

ValoonWay_EventScript_DougRematch::
	trainerbattle_rematch TRAINER_DOUG_1, ValoonWay_Text_DougIntro, ValoonWay_Text_DougDefeat
	msgbox ValoonWay_Text_DougPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonWay_Text_DougIntro:
	.string "Let's battle to let off some steam!$"

ValoonWay_Text_DougDefeat:
	.string "I'm suffocating…$"

ValoonWay_Text_DougPostBattle:
	.string "You can find Pansear, Panpour and\n"
    .string "Pansage here!$"

ValoonWay_EventScript_Sammy::
	trainerbattle_single TRAINER_SAMMY_1, ValoonWay_Text_SammyIntro, ValoonWay_Text_SammyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq ValoonWay_EventScript_SammyRematch
	msgbox ValoonWay_Text_SammyPostBattle, MSGBOX_DEFAULT
	release
	end

ValoonWay_EventScript_SammyRematch::
	trainerbattle_rematch TRAINER_SAMMY_1, ValoonWay_Text_SammyIntro, ValoonWay_Text_SammyDefeat
	msgbox ValoonWay_Text_SammyPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonWay_Text_SammyIntro:
	.string "My Bug-types will squash you!$"

ValoonWay_Text_SammyDefeat:
	.string "Squished like a bug…$"

ValoonWay_Text_SammyPostBattle:
	.string "I raised my Pokémon from the\n"
    .string "second they hatched from their Egg!$"

ValoonWay_EventScript_Colton::
	trainerbattle_single TRAINER_COLTON_1, ValoonWay_Text_ColtonIntro, ValoonWay_Text_ColtonDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq ValoonWay_EventScript_ColtonRematch
	msgbox ValoonWay_Text_ColtonPostBattle, MSGBOX_DEFAULT
	release
	end

ValoonWay_EventScript_ColtonRematch::
	trainerbattle_rematch TRAINER_COLTON_1, ValoonWay_Text_ColtonRematchIntro, ValoonWay_Text_ColtonRematchDefeat
	msgbox ValoonWay_Text_ColtonPostBattle, MSGBOX_AUTOCLOSE
	end

ValoonWay_Text_ColtonIntro:
	.string "You look exhausted, but I'm not\n"
    .string "going to go easy on you for that!$"

ValoonWay_Text_ColtonDefeat:
	.string "Whoa, I underestimated you!$"

ValoonWay_Text_ColtonPostBattle:
	.string "I'm a Pokémon Ranger.\n"
    .string "Our base is in Valoon Town.$"

ValoonWay_Text_ColtonRematchIntro:
	.string "Last time we fought, I\n"
    .string "underestimated your power…\p"
    .string "Not this time!$"

ValoonWay_Text_ColtonRematchDefeat:
	.string "Argh, I keep underestimating you!$"
