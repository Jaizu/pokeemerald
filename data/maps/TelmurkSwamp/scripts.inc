.set TRAINER_ELIJAH_1, 1
.set TRAINER_HANK_1, 1
.set TRAINER_LISIA_1, 1
.set TRAINER_FELICIA_1, 1
.set TRAINER_RAIDEN_1, 1

TelmurkSwamp_MapScripts::
	.byte 0

TelmurkSwamp_EventScript_RouteSign::
	msgbox TelmurkSwamp_Text_RouteSign, MSGBOX_SIGN
	end

TelmurkSwamp_Text_RouteSign::
	.string "Telmurk Swamp\n"
	.string "{UP_ARROW} Valoon Town {RIGHT_ARROW} Battle Marsh$"

TelmurkSwamp_EventScript_Elijah::
	trainerbattle_single TRAINER_ELIJAH_1, TelmurkSwamp_Text_ElijahIntro, TelmurkSwamp_Text_ElijahDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq TelmurkSwamp_EventScript_ElijahRematch
	msgbox TelmurkSwamp_Text_ElijahPostBattle, MSGBOX_DEFAULT
	release
	end

TelmurkSwamp_EventScript_ElijahRematch::
	trainerbattle_rematch TRAINER_ELIJAH_1, TelmurkSwamp_Text_ElijahRematchIntro, TelmurkSwamp_Text_ElijahDefeat
	msgbox TelmurkSwamp_Text_ElijahPostBattle, MSGBOX_AUTOCLOSE
	end

TelmurkSwamp_Text_ElijahIntro:
	.string "As a Ranger, I'm always prepared\n"
	.string "for the unexpected!$"

TelmurkSwamp_Text_ElijahDefeat:
	.string "You were unexpectedly strong!$"

TelmurkSwamp_Text_ElijahPostBattle:
	.string "We Rangers must be valiant, brave,\n"
	.string "and, most of all, prepared!$"

TelmurkSwamp_Text_ElijahRematchIntro:
	.string "I'm prepared to fight you again!$"

TelmurkSwamp_EventScript_Hank::
	trainerbattle_single TRAINER_HANK_1, TelmurkSwamp_Text_HankIntro, TelmurkSwamp_Text_HankDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq TelmurkSwamp_EventScript_HankRematch
	msgbox TelmurkSwamp_Text_HankPostBattle, MSGBOX_DEFAULT
	release
	end

TelmurkSwamp_EventScript_HankRematch::
	trainerbattle_rematch TRAINER_HANK_1, TelmurkSwamp_Text_HankRematchIntro, TelmurkSwamp_Text_HankDefeat
	msgbox TelmurkSwamp_Text_HankPostBattle, MSGBOX_AUTOCLOSE
	end

TelmurkSwamp_Text_HankIntro:
	.string "This is my swamp, you hear?\n"
    .string "And you're not invited!$"

TelmurkSwamp_Text_HankDefeat:
	.string "This is mutiny!$"

TelmurkSwamp_Text_HankPostBattle:
	.string "Get out of my swamp, loser!$"

TelmurkSwamp_Text_HankRematchIntro:
	.string "This time, you're gonna stay out\n"
    .string "of my swamp for good!$"

TelmurkSwamp_EventScript_Lisia::
	trainerbattle_single TRAINER_LISIA_1, TelmurkSwamp_Text_LisiaIntro, TelmurkSwamp_Text_LisiaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq TelmurkSwamp_EventScript_LisiaRematch
	msgbox TelmurkSwamp_Text_LisiaPostBattle, MSGBOX_DEFAULT
	release
	end

TelmurkSwamp_EventScript_LisiaRematch::
	trainerbattle_rematch TRAINER_LISIA_1, TelmurkSwamp_Text_LisiaRematchIntro, TelmurkSwamp_Text_LisiaDefeat
	msgbox TelmurkSwamp_Text_LisiaPostBattle, MSGBOX_AUTOCLOSE
	end

TelmurkSwamp_Text_LisiaIntro:
	.string "My friend said that ever since I\n"
    .string "became a Ranger, the power has\l"
    .string "gone to my head.\p"
    .string "You agree with her, don't you?!$"

TelmurkSwamp_Text_LisiaDefeat:
	.string "How dare you?!$"

TelmurkSwamp_Text_LisiaPostBattle:
	.string "Maybe I did get a little\n"
    .string "hot-headed back there…$"

TelmurkSwamp_Text_LisiaRematchIntro:
	.string "I'm not going to lose to you\n"
    .string "again, you peasant!$"

TelmurkSwamp_EventScript_Felicia::
	trainerbattle_single TRAINER_FELICIA_1, TelmurkSwamp_Text_FeliciaIntro, TelmurkSwamp_Text_FeliciaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq TelmurkSwamp_EventScript_FeliciaRematch
	msgbox TelmurkSwamp_Text_FeliciaPostBattle, MSGBOX_DEFAULT
	release
	end

TelmurkSwamp_EventScript_FeliciaRematch::
	trainerbattle_rematch TRAINER_FELICIA_1, TelmurkSwamp_Text_FeliciaRematchIntro, TelmurkSwamp_Text_FeliciaDefeat
	msgbox TelmurkSwamp_Text_FeliciaPostBattle, MSGBOX_AUTOCLOSE
	end

TelmurkSwamp_Text_FeliciaIntro:
	.string "As Rangers, our Pokémon have to be\n"
    .string "top-notch at all times.\p"
    .string "That means I have to use you for\n"
    .string "training!$"

TelmurkSwamp_Text_FeliciaDefeat:
	.string "That was a tough workout!$"

TelmurkSwamp_Text_FeliciaPostBattle:
	.string "I've got to train my Pokémon more,\n"
    .string "so they won't lose again.$"

TelmurkSwamp_Text_FeliciaRematchIntro:
	.string "I've trained my Pokémon more, and\n"
    .string "now we're ready to take you down!$"

TelmurkSwamp_EventScript_Raiden::
	trainerbattle_single TRAINER_RAIDEN_1, TelmurkSwamp_Text_RaidenIntro, TelmurkSwamp_Text_RaidenDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq TelmurkSwamp_EventScript_RaidenRematch
	msgbox TelmurkSwamp_Text_RaidenPostBattle, MSGBOX_DEFAULT
	release
	end

TelmurkSwamp_EventScript_RaidenRematch::
	trainerbattle_rematch TRAINER_RAIDEN_1, TelmurkSwamp_Text_RaidenRematchIntro, TelmurkSwamp_Text_RaidenDefeat
	msgbox TelmurkSwamp_Text_RaidenPostBattle, MSGBOX_AUTOCLOSE
	end

TelmurkSwamp_Text_RaidenIntro:
	.string "Most Trainers would avoid the\n"
    .string "swamp because of its smell.\p"
    .string "What makes you different?$"

TelmurkSwamp_Text_RaidenDefeat:
	.string "The smell of defeat stinks…$"

TelmurkSwamp_Text_RaidenPostBattle:
	.string "I reek of being a loser…$"

TelmurkSwamp_Text_RaidenRematchIntro:
	.string "Is that a rematch I smell?\n"
    .string "Let's go!$"

TelmurkSwamp_EventScript_OldWoman::
	msgbox TelmurkSwamp_Text_TheRootsOfTheSwamp, MSGBOX_NPC
	end

TelmurkSwamp_Text_TheRootsOfTheSwamp:
	.string "The deep roots of the swamp's\n"
	.string "trees connect us all.$"

TelmurkSwamp_EventScript_Youngster::
	msgbox TelmurkSwamp_Text_IWannaHallucinate, MSGBOX_NPC
	end

TelmurkSwamp_Text_IWannaHallucinate:
	.string "There have been cases of people\n"
	.string "seeing strange things out here.\p"
	.string "They say it's noxious gases that\n"
	.string "cause people to hallucinate.\p"
	.string "I kinda want to see what that\n"
	.string "would feel like, y'know?$"

TelmurkSwamp_EventScript_Maniac::
	msgbox TelmurkSwamp_Text_CollectingMushroomsIsMyFavoritePastime, MSGBOX_NPC
	end

TelmurkSwamp_Text_CollectingMushroomsIsMyFavoritePastime:
	.string "Collecting mushrooms is my\n"
	.string "favorite pastime!$"

TelmurkSwamp_EventScript_PokeManiac::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM09, TelmurkSwamp_EventScript_ReceivedTM09
	msgbox TelmurkSwamp_Text_WhoaYouManagedToReachMe, MSGBOX_DEFAULT
	giveitem ITEM_TM09
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM09
	goto TelmurkSwamp_EventScript_ReceivedTM09
	end

TelmurkSwamp_EventScript_ReceivedTM09:
	msgbox TelmurkSwamp_Text_ExplainTM09, MSGBOX_DEFAULT
	release
	end

TelmurkSwamp_Text_WhoaYouManagedToReachMe:
	.string "Whoa, you managed to reach me!\p"
	.string "I thought nobody would be able to\n"
	.string "get here…\p"
	.string "Hm, I feel like you deserve\n"
	.string "someting for getting here.\p"
	.string "Oh, I know!$"

TelmurkSwamp_Text_ExplainTM09:
	.string "That TM contains Energy Ball.\n"
	.string "It's my favorite move!$"
