SerosPath_MapScripts::
	.byte 0

SerosPath_EventScript_RouteSign::
	msgbox SerosPath_Text_RouteSign, MSGBOX_SIGN
	end

SerosPath_Text_RouteSign:
	.string "Seros Path\n"
	.string "{UP_ARROW} Wisp Forest {RIGHT_ARROW} Seros Village$"

SerosPath_EventScript_WispForestSign::
	msgbox SerosPath_Text_WispForestSign, MSGBOX_SIGN
	end

SerosPath_Text_WispForestSign:
	.string "{UP_ARROW} Wisp Forest\n"
	.string "Those unprepared, turn back now!$"

SerosPath_EventScript_Jenson::
	trainerbattle_single TRAINER_JENSON_1, SerosPath_Text_JensonIntro, SerosPath_Text_JensonDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SerosPath_EventScript_JensonRematch
	msgbox SerosPath_Text_JensonPostBattle, MSGBOX_DEFAULT
	release
	end

SerosPath_EventScript_JensonRematch::
	trainerbattle_rematch TRAINER_JENSON_1, SerosPath_Text_JensonRematchIntro, SerosPath_Text_JensonDefeat
	msgbox SerosPath_Text_JensonPostBattle, MSGBOX_AUTOCLOSE
	end

SerosPath_Text_JensonIntro:
	.string "You look like a brave Trainer.\p"
	.string "Not brave enough to go into Wisp\n"
	.string "Forest, though! Hahaha!$"

SerosPath_Text_JensonDefeat:
	.string "Whoa…\n"
	.string "You are pretty brave, huh?$"

SerosPath_Text_JensonPostBattle:
	.string "Wisp Forest is haunted!$"

SerosPath_Text_JensonRematchIntro:
	.string "Back to prove your bravery, huh?$"

SerosPath_EventScript_Lanessa::
	trainerbattle_single TRAINER_LANESSA_1, SerosPath_Text_LanessaIntro, SerosPath_Text_LanessaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SerosPath_EventScript_LanessaRematch
	msgbox SerosPath_Text_LanessaPostBattle, MSGBOX_DEFAULT
	release
	end

SerosPath_EventScript_LanessaRematch::
	trainerbattle_rematch TRAINER_LANESSA_1, SerosPath_Text_LanessaRematchIntro, SerosPath_Text_LanessaDefeat
	msgbox SerosPath_Text_LanessaPostBattle, MSGBOX_AUTOCLOSE
	end

SerosPath_Text_LanessaIntro:
	.string "I'm not scared to go into\n"
	.string "Wisp Forest! You are!$"

SerosPath_Text_LanessaDefeat:
	.string "Fine, I admit it!\n"
	.string "I am scared!$"

SerosPath_Text_LanessaPostBattle:
	.string "No way I'm going in that forest.$"

SerosPath_Text_LanessaRematchIntro:
	.string "I'm not scared about losing!\n"
	.string "You're the one scared!$"

SerosPath_EventScript_Lass::
	msgbox SerosPath_Text_DidYouKnow, MSGBOX_NPC
	end

SerosPath_Text_DidYouKnow:
	.string "Did you know?\p"
	.string "Wild Pokémon can be found in these\n"
	.string "patches of flowers!$"

SerosPath_EventScript_RockWithAncientGlyphs::
	msgbox SerosPath_Text_RockWithAncientGlyphs, MSGBOX_SIGN
	end

SerosPath_Text_RockWithAncientGlyphs:
	.string "The rock is inscribed with\n"
	.string "ancient glyphs.$"

SerosPath_EventScript_YoungsterPikachu::
	lock
	msgbox SerosPath_Text_PikachuUseThunderWave, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_PIKACHU, 0
	release
	end

SerosPath_Text_PikachuUseThunderWave:
	.string "{COLOR BLUE}Pikachu!\n"
	.string "Use Thunder Wave!$"

SerosPath_EventScript_LassMarill::
	lock
	msgbox SerosPath_Text_MarillHitThemWithWaterGun, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MARILL, 0
	release
	end

SerosPath_Text_MarillHitThemWithWaterGun:
	.string "{COLOR RED}Marill, hit them with Water Gun!$"
