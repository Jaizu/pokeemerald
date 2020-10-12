WindmistSummit_MapScripts::
	.byte 0

WindmistSummit_EventScript_RouteSign::
	msgbox WindmistSummit_Text_RouteSign, MSGBOX_SIGN
	end

WindmistSummit_Text_RouteSign:
	.string "Windmist Summit\n"
	.string "{UP_ARROW} Ignis Roost, Apex Temple\p"
	.string "{RIGHT_ARROW} Ignis Valley\n"
	.string "{DOWN_ARROW} Windmist City, Frostbite Cave$"

WindmistSummit_EventScript_RimewoodForestSign::
	msgbox WindmistSummit_Text_RimewoodForestSign, MSGBOX_SIGN
	end

WindmistSummit_Text_RimewoodForestSign:
	.string "Rimewood Forest\n"
	.string "Beware of the monster!$"

WindmistSummit_EventScript_Brody::
	trainerbattle_single TRAINER_BRODY_1, WindmistSummit_Text_BrodyIntro, WindmistSummit_Text_BrodyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq WindmistSummit_EventScript_BrodyRematch
	msgbox WindmistSummit_Text_BrodyPostBattle, MSGBOX_DEFAULT
	release
	end

WindmistSummit_EventScript_BrodyRematch::
	trainerbattle_rematch TRAINER_BRODY_1, WindmistSummit_Text_BrodyIntro, WindmistSummit_Text_BrodyDefeat
	msgbox WindmistSummit_Text_BrodyPostBattle, MSGBOX_AUTOCLOSE
	end

WindmistSummit_Text_BrodyIntro:
	.string "Hehehe…\n"
	.string "You didn't see me there, did you?$"

WindmistSummit_Text_BrodyDefeat:
	.string "My flame has been put out…$"

WindmistSummit_Text_BrodyPostBattle:
	.string "Shh!\n"
	.string "I'm hiding.$"

WindmistSummit_EventScript_Marcas::
	trainerbattle_single TRAINER_MARCAS_1, WindmistSummit_Text_MarcasIntro, WindmistSummit_Text_MarcasDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq WindmistSummit_EventScript_MarcasRematch
	msgbox WindmistSummit_Text_MarcasPostBattle, MSGBOX_DEFAULT
	release
	end

WindmistSummit_EventScript_MarcasRematch::
	trainerbattle_rematch TRAINER_MARCAS_1, WindmistSummit_Text_MarcasIntro, WindmistSummit_Text_MarcasDefeat
	msgbox WindmistSummit_Text_MarcasPostBattle, MSGBOX_AUTOCLOSE
	end

WindmistSummit_Text_MarcasIntro:
	.string "I strike from the shadows!\n"
	.string "Hi-yah!$"

WindmistSummit_Text_MarcasDefeat:
	.string "Back to the shadows I go…$"

WindmistSummit_Text_MarcasPostBattle:
	.string "I can't believe you managed to\n"
	.string "beat my super tough Pokémon…$"

WindmistSummit_EventScript_Harleigh::
	trainerbattle_single TRAINER_HARLEIGH_1, WindmistSummit_Text_HarleighIntro, WindmistSummit_Text_HarleighDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq WindmistSummit_EventScript_HarleighRematch
	msgbox WindmistSummit_Text_HarleighPostBattle, MSGBOX_DEFAULT
	release
	end

WindmistSummit_EventScript_HarleighRematch::
	trainerbattle_rematch TRAINER_HARLEIGH_1, WindmistSummit_Text_HarleighIntro, WindmistSummit_Text_HarleighDefeat
	msgbox WindmistSummit_Text_HarleighPostBattle, MSGBOX_AUTOCLOSE
	end

WindmistSummit_Text_HarleighIntro:
	.string "My nose won't stop dribbling,\n"
	.string "and it's making me mad!$"

WindmistSummit_Text_HarleighDefeat:
	.string "Sniff… I'm not crying, it's just\n"
	.string "the wind hurting my eyes!$"

WindmistSummit_Text_HarleighPostBattle:
	.string "I don't like the cold… It makes\n"
	.string "my eyes and nose run!$"

WindmistSummit_EventScript_Davina::
	trainerbattle_single TRAINER_DAVINA_1, WindmistSummit_Text_DavinaIntro, WindmistSummit_Text_DavinaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq WindmistSummit_EventScript_DavinaRematch
	msgbox WindmistSummit_Text_DavinaPostBattle, MSGBOX_DEFAULT
	release
	end

WindmistSummit_EventScript_DavinaRematch::
	trainerbattle_rematch TRAINER_DAVINA_1, WindmistSummit_Text_DavinaIntro, WindmistSummit_Text_DavinaDefeat
	msgbox WindmistSummit_Text_DavinaPostBattle, MSGBOX_AUTOCLOSE
	end

WindmistSummit_Text_DavinaIntro:
	.string "Like a block of ice, I shall\n"
    .string "shatter you into a million pieces!$"

WindmistSummit_Text_DavinaDefeat:
	.string "You have bested me.$"

WindmistSummit_Text_DavinaPostBattle:
	.string "I like training my Pokémon here.\p"
    .string "Fighting-types are strong against\n"
    .string "the Ice-type wild Pokémon here!$"

WindmistSummit_EventScript_Brandon::
	trainerbattle_single TRAINER_BRANDON_1, WindmistSummit_Text_BrandonIntro, WindmistSummit_Text_BrandonDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq WindmistSummit_EventScript_BrandonRematch
	msgbox WindmistSummit_Text_BrandonPostBattle, MSGBOX_DEFAULT
	release
	end

WindmistSummit_EventScript_BrandonRematch::
	trainerbattle_rematch TRAINER_BRANDON_1, WindmistSummit_Text_BrandonRematchIntro, WindmistSummit_Text_BrandonDefeat
	msgbox WindmistSummit_Text_BrandonPostBattle, MSGBOX_AUTOCLOSE
	end

WindmistSummit_Text_BrandonIntro:
	.string "My Pokémon are really rare!\n"
    .string "Check them out!$"

WindmistSummit_Text_BrandonDefeat:
	.string "No! How?$"

WindmistSummit_Text_BrandonPostBattle:
	.string "If I train my Pokémon enough,\n"
	.string "do you think they will evolve?$"

WindmistSummit_Text_BrandonRematchIntro:
	.string "I've trained my Pokémon!\n"
	.string "Now they're both rare and strong!$"

WindmistSummit_EventScript_Olympia::
	trainerbattle_single TRAINER_OLYMPIA_1, WindmistSummit_Text_OlympiaIntro, WindmistSummit_Text_OlympiaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq WindmistSummit_EventScript_OlympiaRematch
	msgbox WindmistSummit_Text_OlympiaPostBattle, MSGBOX_DEFAULT
	release
	end

WindmistSummit_EventScript_OlympiaRematch::
	trainerbattle_rematch TRAINER_OLYMPIA_1, WindmistSummit_Text_OlympiaIntro, WindmistSummit_Text_OlympiaDefeat
	msgbox WindmistSummit_Text_OlympiaPostBattle, MSGBOX_AUTOCLOSE
	end

WindmistSummit_Text_OlympiaIntro:
	.string "My Pokémon and I love aiming for\n"
	.string "new heights!$"

WindmistSummit_Text_OlympiaDefeat:
	.string "You are an obstacle we failed to\n"
	.string "overcome…$"

WindmistSummit_Text_OlympiaPostBattle:
	.string "My Pokémon and I always strive to\n"
	.string "reach new heights.$"

WindmistSummit_EventScript_RimewoodForestGuardLeft::
	msgbox WindmistSummit_Text_WhoaKid, MSGBOX_NPC
	end

WindmistSummit_Text_WhoaKid:
	.string "Whoa, kid!\n"
	.string "You can't go past.\p"
	.string "That monster will tear you\n"
	.string "to shreds!$"

WindmistSummit_EventScript_RimewoodForestGuardRight::
	msgbox WindmistSummit_Text_YoureNotStrongEnoughToPass, MSGBOX_NPC
	end

WindmistSummit_Text_YoureNotStrongEnoughToPass:
	.string "You're not strong enough to pass.\p"
	.string "Come back when you've won the\n"
	.string "{COLOR GREEN}Honeycomb Badge{COLOR BLUE}, kid.$"

WindmistSummit_EventScript_AceTrainerF::
	msgbox WindmistSummit_Text_ClimbHighEnough, MSGBOX_NPC
	end

WindmistSummit_Text_ClimbHighEnough:
	.string "Climb high enough and you'll reach\n"
	.string "Apex Temple.\p"
	.string "It is at a higher altitude than the\n"
	.string "clouds, so there's no snow there.$"

WindmistSummit_EventScript_BlackBelt::
	msgbox WindmistSummit_Text_BeingALumberjack, MSGBOX_NPC
	end

WindmistSummit_Text_BeingALumberjack:
	.string "Being a lumberjack takes all\n"
	.string "you've got…\p"
	.string "You need strength, willpower,\n"
	.string "and determination!$"

WindmistSummit_EventScript_Hiker::
	msgbox WindmistSummit_Text_ISawSomePeople, MSGBOX_NPC
	end

WindmistSummit_Text_ISawSomePeople:
	.string "I saw some people dressed up all\n"
	.string "strange head up to the Temple.$"
