.equ LOCALID_WOMAN, 1
.equ LOCALID_MEOWTH, 2

CelantoTown_House2_MapScripts::
	.byte 0

CelantoTown_House2_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_FED_CELANTO_MEOWTH, CelantoTown_House2_EventScript_TryGiveWhiteHerb
	msgbox CelantoTown_House2_Text_OhDear, MSGBOX_DEFAULT
	checkitem ITEM_ORAN_BERRY, 1
	compare VAR_RESULT, TRUE
	goto_if_eq CelantoTown_House2_EventScript_PlayerHasBerry
	release
	end

CelantoTown_House2_EventScript_PlayerHasBerry:
	playse SE_PIN
	applymovement LOCALID_WOMAN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WOMAN, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_House2_Text_OhYouHaveOne, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq CelantoTown_House2_EventScript_FeedMeowth
	msgbox CelantoTown_House2_Text_HowCruel, MSGBOX_DEFAULT
	release
	end

CelantoTown_House2_EventScript_FeedMeowth:
	removeitem ITEM_ORAN_BERRY, 1
	msgbox CelantoTown_House2_Text_ThankYouSoMuchDarling, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement LOCALID_WOMAN, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 10
	msgbox CelantoTown_House2_Text_HereYouGoMeowth, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MEOWTH, 2
	applymovement LOCALID_MEOWTH, Common_Movement_Heart
	waitmovement 0
	waitmoncry
	delay 10
	applymovement LOCALID_WOMAN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CelantoTown_House2_Text_PleaseTakeThis, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_FED_CELANTO_MEOWTH
	goto CelantoTown_House2_EventScript_TryGiveWhiteHerb
	end

CelantoTown_House2_EventScript_TryGiveWhiteHerb:
	goto_if_set FLAG_GOT_CELANTO_WHITE_HERB, CelantoTown_House2_EventScript_MeowthIsBetter
	giveitem ITEM_WHITE_HERB
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_CELANTO_WHITE_HERB
	goto CelantoTown_House2_EventScript_MeowthIsBetter
	end

CelantoTown_House2_EventScript_MeowthIsBetter:
	msgbox CelantoTown_House2_Text_MeowthIsAllBetterNow, MSGBOX_DEFAULT
	closemessage
	release
	end

CelantoTown_House2_Text_OhDear:
	.string "Oh dear!\n"
	.string "My darling Meowth is hungry!\p"
	.string "I wish I had an {COLOR GREEN}Oran Berry{COLOR RED} to\n"
	.string "give her…$"

CelantoTown_House2_Text_OhYouHaveOne:
	.string "Oh? You have one?\n"
	.string "May I have it?$"

CelantoTown_House2_Text_HowCruel:
	.string "How cruel!\n"
	.string "Please, leave us alone!$"

CelantoTown_House2_Text_ThankYouSoMuchDarling:
	.string "Thank you so much, darling!$"

CelantoTown_House2_Text_HereYouGoMeowth:
	.string "Here you go, Meowth.$"

CelantoTown_House2_Text_PleaseTakeThis:
	.string "Please, take this as a sign of my\n"
	.string "gratitude. Meowth's, too!$"

CelantoTown_House2_Text_MeowthIsAllBetterNow:
	.string "Meowth is all better now!\n"
	.string "Thank you.$"

CelantoTown_House2_EventScript_Meowth::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, 2
	msgbox CelantoTown_House2_Text_Meowth, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CelantoTown_House2_Text_Meowth:
	.string "Meowth: {COLOR RED}Crii-ru!$"
