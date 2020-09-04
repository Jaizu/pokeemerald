ArchanHills_MapScripts::
	.byte 0

ArchanHills_EventScript_Psyduck::
	lock
	waitse
	playmoncry SPECIES_PSYDUCK, 0
	msgbox ArchanHills_Text_ThePsyduckAreStandingFirm, MSGBOX_DEFAULT
	closemessage
	release
	end

ArchanHills_Text_ThePsyduckAreStandingFirm:
	.string "The Psyduck are standing firm.\n"
	.string "They aren't inclined to move at all.$"

ArchanHills_EventScript_FatMan::
	msgbox ArchanHills_Text_ThosePsyduckWontBudge, MSGBOX_NPC
	end

ArchanHills_Text_ThosePsyduckWontBudge:
	.string "Those Psyduck won't budge!\n"
	.string "How will I get to Aerous City now?$"

AerousRoad_EventScript_Becca::
	trainerbattle_single TRAINER_BECCA_1, AerousRoad_Text_BeccaIntro, AerousRoad_Text_BeccaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_BeccaRematch
	msgbox AerousRoad_Text_BeccaPostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_BeccaRematch::
	trainerbattle_rematch TRAINER_BECCA_1, AerousRoad_Text_BeccaRematchIntro, AerousRoad_Text_BeccaDefeat
	msgbox AerousRoad_Text_BeccaRematchPostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_BeccaIntro:
	.string "My darling Pokémon will destroy\n"
	.string "you!$"

AerousRoad_Text_BeccaDefeat:
	.string "N-no!\n"
	.string "My darling Pokémon!$"

AerousRoad_Text_BeccaPostBattle:
	.string "You scoundrel!\n"
	.string "You harmed my babies…$"

AerousRoad_Text_BeccaRematchIntro:
	.string "You're the scoundrel that harmed\n"
	.string "my babies!\p"
	.string "Well, we won't lose this time!$"

AerousRoad_Text_BeccaRematchPostBattle:
	.string "How dare you harm my darling\n"
	.string "Pokémon?$"

ArchanHills_EventScript_OpposHouseSign::
	msgbox ArchanHills_Text_OpposHouseSign, MSGBOX_NPC
	end

ArchanHills_Text_OpposHouseSign:
	.string "Oppos's house$"
