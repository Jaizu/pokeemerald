.set LOCALID_COULTER, 6
.set LOCALID_AKUTO, 7

TelmurkCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TelmurkCity_OnTransition
	.byte 0

TelmurkCity_OnTransition::
	setflag FLAG_VISITED_TELMURK_CITY
	end

TelmurkCity_EventScript_AkutoIntroductionTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto TelmurkCity_EventScript_AkutoIntroductionScene
	end

TelmurkCity_EventScript_AkutoIntroductionTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto TelmurkCity_EventScript_AkutoIntroductionScene
	end

TelmurkCity_EventScript_AkutoIntroductionTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto TelmurkCity_EventScript_AkutoIntroductionScene
	end

TelmurkCity_EventScript_AkutoIntroductionScene:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	applymovement LOCALID_COULTER, Common_Movement_FaceLeft
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq TelmurkCity_EventScript_WalkPlayerToCoulter0
	compare VAR_0x8008, 1
	call_if_eq TelmurkCity_EventScript_WalkPlayerToCoulter1
	compare VAR_0x8008, 2
	call_if_eq TelmurkCity_EventScript_WalkPlayerToCoulter2
	msgbox TelmurkCity_Text_SoThisIsTelmurk, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_COULTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	applymovement LOCALID_COULTER, Common_Movement_FaceRight
	waitmovement 0
	applymovement LOCALID_AKUTO, TelmurkCity_Movement_EnterAkuto
	waitmovement 0
	msgbox TelmurkCity_Text_AkutoSpeech, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_AKUTO, TelmurkCity_Movement_ExitAkutoAndCoulter
	waitmovement 0
	removeobject LOCALID_AKUTO
	compare VAR_0x8008, 0
	call_if_eq TelmurkCity_EventScript_PlayerCoulterFaceEachOther0
	compare VAR_0x8008, 0
	call_if_gt TelmurkCity_EventScript_PlayerCoulterFaceEachOther1
	msgbox TelmurkCity_Text_WhatWasThatAllAbout, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COULTER, TelmurkCity_Movement_ExitAkutoAndCoulter
	waitmovement 0
	removeobject LOCALID_COULTER
	setvar VAR_TELMURK_CITY_STATE, 1
	releaseall
	end

TelmurkCity_EventScript_WalkPlayerToCoulter0:
	applymovement OBJ_EVENT_ID_PLAYER, TelmurkCity_Movement_WalkPlayerToCoulter0
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_FaceUp
	waitmovement 0
	return

TelmurkCity_EventScript_WalkPlayerToCoulter1:
	applymovement OBJ_EVENT_ID_PLAYER, TelmurkCity_Movement_WalkPlayerToCoulter1
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_FaceDown
	waitmovement 0
	return

TelmurkCity_EventScript_WalkPlayerToCoulter2:
	applymovement OBJ_EVENT_ID_PLAYER, TelmurkCity_Movement_WalkPlayerToCoulter2
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_FaceDown
	waitmovement 0
	return

TelmurkCity_EventScript_PlayerCoulterFaceEachOther0:
	applymovement LOCALID_COULTER, Common_Movement_FaceUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	return

TelmurkCity_EventScript_PlayerCoulterFaceEachOther1:
	applymovement LOCALID_COULTER, Common_Movement_FaceDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	return

TelmurkCity_Text_SoThisIsTelmurk:
	.string "{RIVAL}: {COLOR BLUE}So, this is Telmurk!\p"
	.string "It looks huge, doesn't it?\p"
	.string "{COLOR DARK_GREY}???: {COLOR BLUE}Oi!$"

TelmurkCity_Text_AkutoSpeech:
	.string "???: {COLOR BLUE}Nyeh…\n"
	.string "I never seen the two of you's.\p"
	.string "The name's {COLOR GREEN}Akuto{COLOR BLUE}.\p"
	.string "{COLOR DARK_GREY}Akuto: {COLOR BLUE}I run things 'round\n"
	.string "here, like the big boss, y'know?\p"
	.string "Me and my underlings, we run an…\n"
	.string "Organization, shall we say?\p"
	.string "{COLOR DARK_GREY}Akuto: {COLOR BLUE}We're known as\n"
	.string "{COLOR GREEN}The Mighty Mightyenas{COLOR BLUE}.\p"
	.string "Don't go interfering with our\n"
	.string "endeavors, kids.\p"
	.string "You might not like whachya find!\p"
	.string "{COLOR DARK_GREY}Akuto: {COLOR BLUE}Don't talk outta line,\n"
	.string "or you might be in deep trouble!\p"
	.string "…\p"
	.string "Enjoy your stay.$"

TelmurkCity_Text_WhatWasThatAllAbout:
	.string "{RIVAL}: {COLOR BLUE}What was that all about?\p"
	.string "He seemed kind of sketchy,\n"
	.string "wouldn't you say?\p"
	.string "Hm…\p"
	.string "Anyway, I'm gonna go ask around!\p"
	.string "Let's see if we can gather any\n"
	.string "more info about the New Elders.\p"
	.string "Seeya, {PLAYER}!$"

TelmurkCity_Movement_WalkPlayerToCoulter0:
	walk_right
	walk_right
	face_down
	step_end

TelmurkCity_Movement_WalkPlayerToCoulter1:
	walk_right
	walk_down
	walk_right
	face_up
	step_end

TelmurkCity_Movement_WalkPlayerToCoulter2:
	walk_right
	walk_right
	face_up
	step_end

TelmurkCity_Movement_EnterAkuto:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

TelmurkCity_Movement_ExitAkutoAndCoulter:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

TelmurkCity_EventScript_CitySign::
	msgbox TelmurkCity_Text_CitySign, MSGBOX_SIGN
	end

TelmurkCity_Text_CitySign:
	.string "Telmurk City\n"
	.string "The Mighty Marsh Metropolis.$"

TelmurkCity_EventScript_GymSign::
	msgbox TelmurkCity_Text_GymSign, MSGBOX_SIGN
	end

TelmurkCity_Text_GymSign:
	.string "Telmurk City Pokémon Gym\p"
	.string "Leader: Sid\n"
	.string "“Still water is the most dangerous…”$"

TelmurkCity_EventScript_UndergroudPathSign::
	msgbox TelmurkCity_Text_UndergroudPathSign, MSGBOX_SIGN
	end

TelmurkCity_Text_UndergroudPathSign:
	.string "Underground Path\n"
	.string "Now leaving Telmurk!$"

TelmurkCity_EventScript_MsMurkrowSign::
	msgbox TelmurkCity_Text_MsMurkrowSign, MSGBOX_SIGN
	end

TelmurkCity_Text_MsMurkrowSign:
	.string "Ms. Murkrow's Special Poké Balls$"
