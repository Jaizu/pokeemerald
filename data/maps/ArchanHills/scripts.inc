.set LOCALID_PSYDUCK_1, 1
.set LOCALID_PSYDUCK_2, 2
.set LOCALID_PSYDUCK_3, 3
.set LOCALID_PSYDUCK_4, 4
.set LOCALID_PSYDUCK_5, 5
.set LOCALID_PSYDUCK_6, 6
.set LOCALID_PSYDUCK_7, 7

ArchanHills_MapScripts::
	.byte 0

ArchanHills_EventScript_Psyduck::
	lock
	waitse
	playmoncry SPECIES_PSYDUCK, 0
	msgbox ArchanHills_Text_ThePsyduckAreStandingFirm, MSGBOX_DEFAULT
	checkitem ITEM_SECRET_POTION, 1
	compare VAR_RESULT, TRUE
	call_if_eq ArchanHills_EventScript_TryClearPsyduck
	closemessage
	release
	end

ArchanHills_EventScript_TryClearPsyduck:
	msgbox ArchanHills_Text_WouldYouLikeToUseTheSecretPotion, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq ArchanHills_EventScript_ClearPsyduck
	return

ArchanHills_EventScript_ClearPsyduck:
	playfanfare MUS_FANFA4
	message ArchanHills_Text_UsedTheSecretPotion
	waitfanfare
	removeitem ITEM_SECRET_POTION, 1
	msgbox ArchanHills_Text_ThePsyduckAppearToBeCured, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_PSYDUCK_1, Common_Movement_ExclamationMark
	applymovement LOCALID_PSYDUCK_2, Common_Movement_ExclamationMark
	applymovement LOCALID_PSYDUCK_3, Common_Movement_ExclamationMark
	applymovement LOCALID_PSYDUCK_4, Common_Movement_ExclamationMark
	applymovement LOCALID_PSYDUCK_5, Common_Movement_ExclamationMark
	applymovement LOCALID_PSYDUCK_6, Common_Movement_ExclamationMark
	applymovement LOCALID_PSYDUCK_7, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PSYDUCK_1, Common_Movement_Delay48
	waitmovement 0
	fadescreen FADE_TO_BLACK
	playse SE_NIGERU
	removeobject LOCALID_PSYDUCK_1
	removeobject LOCALID_PSYDUCK_2
	removeobject LOCALID_PSYDUCK_3
	removeobject LOCALID_PSYDUCK_4
	removeobject LOCALID_PSYDUCK_5
	removeobject LOCALID_PSYDUCK_6
	removeobject LOCALID_PSYDUCK_7
	waitse
	fadescreen FADE_FROM_BLACK
	msgbox ArchanHills_Text_ThePsyduckWaddledAway, MSGBOX_DEFAULT
	return

ArchanHills_Text_ThePsyduckAreStandingFirm:
	.string "The Psyduck are standing firm.\n"
	.string "They aren't inclined to move at all.$"

ArchanHills_Text_WouldYouLikeToUseTheSecretPotion:
	.string "Would you like to use the\n"
	.string "SecretPotion?$"

ArchanHills_Text_UsedTheSecretPotion:
	.string "{PLAYER} used the\n"
	.string "SecretPotion!$"

ArchanHills_Text_ThePsyduckAppearToBeCured:	
	.string "The Psyduck appear to all be cured\n"
	.string "of their chronic headache!$"

ArchanHills_Text_ThePsyduckWaddledAway:
	.string "The Psyduck waddled away…\n"
	.string "The path has cleared!$"

ArchanHills_EventScript_FatMan::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_ARCHAN_HILLS_PSYDUCK, ArchanHills_EventScript_FatManPsyduckCleared
	msgbox ArchanHills_Text_ThosePsyduckWontBudge, MSGBOX_DEFAULT
	closemessage
	release
	end

ArchanHills_EventScript_FatManPsyduckCleared:
	msgbox ArchanHills_Text_WhoaYouGotThosePsyduckToMove, MSGBOX_DEFAULT
	closemessage
	release
	end

ArchanHills_Text_ThosePsyduckWontBudge:
	.string "Those Psyduck won't budge!\n"
	.string "How will I get to Aerous City now?$"

ArchanHills_Text_WhoaYouGotThosePsyduckToMove:
	.string "Whoa! You got those Psyduck to\n"
	.string "move!\p"
	.string "…Why did I want to go to\n"
	.string "Aerous City, again…?$"

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
