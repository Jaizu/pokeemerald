NestpineClimb_MapScripts::
	.byte 0

NestpineClimb_EventScript_RouteSign::
	msgbox NestpineClimb_Text_RouteSign, MSGBOX_SIGN
	end

NestpineClimb_Text_RouteSign:
	.string "Nestpine Climb\n"
	.string "{DOWN_ARROW} Celanto Path {UP_ARROW} Nestpine Town$"

NestpineClimb_EventScript_NetasHouseSign::
	msgbox NestpineClimb_Text_NetasHouseSign, MSGBOX_SIGN
	end

NestpineClimb_Text_NetasHouseSign:
	.string "Neta's house$"

NestpineClimb_EventScript_Martha::
	trainerbattle_single TRAINER_MARTHA_1, NestpineClimb_Text_MarthaIntro, NestpineClimb_Text_MarthaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq NestpineClimb_EventScript_MarthaRematch
	msgbox NestpineClimb_Text_MarthaPostBattle, MSGBOX_DEFAULT
	release
	end

NestpineClimb_EventScript_MarthaRematch::
	trainerbattle_rematch TRAINER_MARTHA_1, NestpineClimb_Text_MarthaIntro, NestpineClimb_Text_MarthaDefeat
	msgbox NestpineClimb_Text_MarthaPostBattle, MSGBOX_AUTOCLOSE
	end

NestpineClimb_Text_MarthaIntro:
	.string "Prepare to face the awe\n"
	.string "of Mt. Ignis!$"

NestpineClimb_Text_MarthaDefeat:
	.string "That was awful…$"

NestpineClimb_Text_MarthaPostBattle:
	.string "It's said the Elders of Orbtus\n"
	.string "somehow predicted their downfall.\p"
	.string "I wonder how that must have felt.$"

NestpineClimb_EventScript_Lucy::
	trainerbattle_single TRAINER_LUCY_1, NestpineClimb_Text_LucyIntro, NestpineClimb_Text_LucyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq NestpineClimb_EventScript_LucyRematch
	msgbox NestpineClimb_Text_LucyPostBattle, MSGBOX_DEFAULT
	release
	end

NestpineClimb_EventScript_LucyRematch::
	trainerbattle_rematch TRAINER_LUCY_1, NestpineClimb_Text_LucyIntro, NestpineClimb_Text_LucyDefeat
	msgbox NestpineClimb_Text_LucyPostBattle, MSGBOX_AUTOCLOSE
	end

NestpineClimb_Text_LucyIntro:
	.string "Watch out, the victory train is\n"
	.string "coming through!$"

NestpineClimb_Text_LucyDefeat:
	.string "Choo choo…$"

NestpineClimb_Text_LucyPostBattle:
	.string "You totally derailed my winning\n"
	.string "streak…$"

NestpineClimb_EventScript_Yoshiro::
	lock
	faceplayer
	goto_if_set TRAINER_FLAGS_START + TRAINER_YOSHIRO, NestpineClimb_EventScript_YoshiroPostBattle
	msgbox NestpineClimb_Text_HelloYoungTraveler, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne NestpineClimb_EventScript_DeclineYoshiro
	msgbox NestpineClimb_Text_LetTheSparCommence, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_YOSHIRO, NestpineClimb_Text_YoshiroDefeat
	goto NestpineClimb_EventScript_YoshiroPostBattle
	end

NestpineClimb_EventScript_DeclineYoshiro:
	msgbox NestpineClimb_Text_VeryWell, MSGBOX_DEFAULT
	release
	end

NestpineClimb_EventScript_YoshiroPostBattle:
	msgbox NestpineClimb_Text_WouldYouLikeMeToHeal, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne NestpineClimb_EventScript_DeclineYoshiro
	fadescreen FADE_TO_BLACK
	closemessage
	playse SE_KAIFUKU
	special HealPlayerParty
	waitse
	fadescreen FADE_FROM_BLACK
	msgbox NestpineClimb_Text_ThereYouGo, MSGBOX_DEFAULT
	release
	end

NestpineClimb_Text_HelloYoungTraveler:
	.string "Hello, young traveler. The journey\n"
	.string "ahead of you is an arduous one.\p"
	.string "I will heal your Pokémon, if you\n"
	.string "can best me in combat.\p"
	.string "What say you to my proposal?$"

NestpineClimb_Text_VeryWell:
	.string "Very well.\n"
	.string "Brave the journey alone.$"

NestpineClimb_Text_LetTheSparCommence:
	.string "Let the spar commence!$"

NestpineClimb_Text_YoshiroDefeat:
	.string "Ah! Well fought.\n"
	.string "That was an enthralling battle!$"

NestpineClimb_Text_WouldYouLikeMeToHeal:
	.string "Would you like me to heal\n"
	.string "your Pokémon for you?$"

NestpineClimb_Text_ThereYouGo:
	.string "There you go, traveler.\n"
	.string "Good luck on your journey.$"

NestpineClimb_EventScript_Ralph::
	trainerbattle_single TRAINER_RALPH_1, NestpineClimb_Text_RalphIntro, NestpineClimb_Text_RalphDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq NestpineClimb_EventScript_RalphRematch
	msgbox NestpineClimb_Text_RalphPostBattle, MSGBOX_DEFAULT
	release
	end

NestpineClimb_EventScript_RalphRematch::
	trainerbattle_rematch TRAINER_RALPH_1, NestpineClimb_Text_RalphRematchIntro, NestpineClimb_Text_RalphRematchDefeat
	msgbox NestpineClimb_Text_RalphPostBattle, MSGBOX_AUTOCLOSE
	end

NestpineClimb_Text_RalphIntro:
	.string "If I told you that I, myself, fell\n"
	.string "this great tree…\p"
	.string "Would you believe me?$"

NestpineClimb_Text_RalphDefeat:
	.string "You're right, I was lying…$"

NestpineClimb_Text_RalphPostBattle:
	.string "Trees can be home to many\n"
	.string "different types of Pokémon.$"

NestpineClimb_Text_RalphRematchIntro:
	.string "Have you returned for me to chop\n"
	.string "you down like a tree?$"

NestpineClimb_Text_RalphRematchDefeat:
	.string "In the end, it was me who was\n"
	.string "felled…$"

NestpineClimb_EventScript_Brett::
	trainerbattle_single TRAINER_BRETT_1, NestpineClimb_Text_BrettIntro, NestpineClimb_Text_BrettDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq NestpineClimb_EventScript_BrettRematch
	msgbox NestpineClimb_Text_BrettPostBattle, MSGBOX_DEFAULT
	release
	end

NestpineClimb_EventScript_BrettRematch::
	trainerbattle_rematch TRAINER_BRETT_1, NestpineClimb_Text_BrettRematchIntro, NestpineClimb_Text_BrettDefeat
	msgbox NestpineClimb_Text_BrettPostBattle, MSGBOX_AUTOCLOSE
	end

NestpineClimb_Text_BrettIntro:
	.string "Are you headed to get\n"
	.string "Aria's Badge?$"

NestpineClimb_Text_BrettDefeat:
	.string "Oh no! Now I have to go back to\n"
	.string "the Pokémon Center!$"

NestpineClimb_Text_BrettPostBattle:
	.string "The Gym Leader in Nestpine Town\n"
	.string "uses Flying-types, so my Bug-types\l"
	.string "won't be much good against her.$"

NestpineClimb_Text_BrettRematchIntro:
	.string "Do you have Aria's Badge yet?\n"
	.string "I'm still training!$"

NestpineClimb_EventScript_July::
	trainerbattle_single TRAINER_JULY_1, NestpineClimb_Text_JulyIntro, NestpineClimb_Text_JulyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq NestpineClimb_EventScript_JulyRematch
	msgbox NestpineClimb_Text_JulyPostBattle, MSGBOX_DEFAULT
	release
	end

NestpineClimb_EventScript_JulyRematch::
	trainerbattle_rematch TRAINER_JULY_1, NestpineClimb_Text_JulyIntro, NestpineClimb_Text_JulyDefeat
	msgbox NestpineClimb_Text_JulyPostBattle, MSGBOX_AUTOCLOSE
	end

NestpineClimb_Text_JulyIntro:
	.string "The mountainous soil here is\n"
	.string "great for growing flowers!$"

NestpineClimb_Text_JulyDefeat:
	.string "I was just telling you about\n"
	.string "the soil here…$"

NestpineClimb_Text_JulyPostBattle:
	.string "Roselia are beautiful Pokémon.\p"
	.string "I once found one that had purple\n"
	.string "and black flowers!\p"
	.string "I hate purple, though, so I didn't\n"
	.string "catch it…$"

NestpineClimb_EventScript_Ludwig::
	lock
	faceplayer
	goto_if_set TRAINER_FLAGS_START + TRAINER_LUDWIG, NestpineClimb_EventScript_LudwigPostBattle
	msgbox NestpineClimb_Text_DoYouLikeCamping, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne NestpineClimb_EventScript_LudwigBattle
	msgbox NestpineClimb_Text_MeToo, MSGBOX_DEFAULT
	release
	end

NestpineClimb_EventScript_LudwigBattle:
	msgbox NestpineClimb_Text_WhatFightMeNow, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LUDWIG, NestpineClimb_Text_LudwigDefeat
	goto NestpineClimb_EventScript_LudwigPostBattle
	end

NestpineClimb_EventScript_LudwigPostBattle:
	msgbox NestpineClimb_Text_DontEvenTalkToMe, MSGBOX_DEFAULT
	release
	end

NestpineClimb_Text_DoYouLikeCamping:
	.string "Do you like camping?$"

NestpineClimb_Text_MeToo:
	.string "Me too!\n"
	.string "Nice!$"

NestpineClimb_Text_WhatFightMeNow:
	.string "What?\n"
	.string "Fight me, now!$"

NestpineClimb_Text_LudwigDefeat:
	.string "I hate you!$"

NestpineClimb_Text_DontEvenTalkToMe:
	.string "Don't even try to talk to me.$"

NestpineClimb_EventScript_Lady::
	msgbox NestpineClimb_Text_ThatsNetasHouse, MSGBOX_NPC
	end

NestpineClimb_Text_ThatsNetasHouse:
	.string "That's Neta's house.\n"
	.string "She maintains the Storage System!$"

NestpineClimb_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_NESTPINE_CLIMB_PERSIM_BERRIES, NestpineClimb_EventScript_ReceivedRevivalHerb
	msgbox NestpineClimb_Text_YoWearyTraveler, MSGBOX_DEFAULT
	giveitem ITEM_PERSIM_BERRY, 3
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_NESTPINE_CLIMB_PERSIM_BERRIES
	goto NestpineClimb_EventScript_ReceivedRevivalHerb
	end

NestpineClimb_EventScript_ReceivedRevivalHerb:
	msgbox NestpineClimb_Text_ExplainPersimBerry, MSGBOX_DEFAULT
	release
	end

NestpineClimb_Text_YoWearyTraveler:
	.string "Yo, weary traveler!\n"
	.string "Your Pokémon look hungry!\p"
	.string "They've got to eat yummy Berries,\n"
	.string "right?\p"
	.string "Well, I've got tons in my knapsack.\n"
	.string "Here, you can take a few!$"

NestpineClimb_Text_ExplainPersimBerry:
	.string "Feed a Persim Berry to a confused\n"
    .string "Pokémon and it'll come to!$"

NestpineClimb_EventScript_BlackBelt::
	msgbox NestpineClimb_Text_AfterWorkImHeadedToTheRestStop, MSGBOX_NPC
	end

NestpineClimb_Text_AfterWorkImHeadedToTheRestStop:
	.string "After work, I'm headed to the\n"
	.string "Lumberjack Rest Stop in Windmist!$"
