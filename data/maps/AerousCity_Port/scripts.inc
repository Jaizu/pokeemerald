.set MAP_SABULO_ISLAND_PORT, MAP_AEROUS_CITY_PORT
.set LOCALID_BRAVETON, 1
.set LOCALID_SS_WAKE, 2

AerousCity_Port_MapScripts::
	.byte 0

AerousCity_Port_EventScript_Braveton::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_AEROUS_CITY_PORT_SS_WAKE, AerousCity_Port_EventScript_TryToBoard
	goto_if_set FLAG_BADGE03_GET, AerousCity_Port_EventScript_TryBattleBraveton
	msgbox AerousCity_Port_Text_TheSSWakeIsntBackYet, MSGBOX_DEFAULT
	closemessage
	release
	end

AerousCity_Port_EventScript_TryBattleBraveton:
	msgbox AerousCity_Port_Text_WantToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq AerousCity_Port_EventScript_BattleBraveton
	msgbox AerousCity_Port_Text_NotTheFightingType, MSGBOX_DEFAULT
	closemessage
	release
	end

AerousCity_Port_EventScript_BattleBraveton:
	msgbox AerousCity_Port_Text_BravetonIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BRAVETON, AerousCity_Port_Text_BravetonDefeat
	msgbox AerousCity_Port_Text_ThatWasAGreatBattle, MSGBOX_DEFAULT
	closemessage
	delay 20
	playse SE_RG_KITEKI
	delay 20
	applymovement LOCALID_BRAVETON, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_BRAVETON, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BRAVETON, Common_Movement_Delay48
	waitmovement 0
	delay 10
	applymovement LOCALID_BRAVETON, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox AerousCity_Port_Text_TalkAboutGoodTiming, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	addobject LOCALID_SS_WAKE
	clearflag FLAG_HIDE_AEROUS_CITY_PORT_SS_WAKE
	fadescreen FADE_FROM_BLACK
	goto AerousCity_Port_EventScript_TryToBoard
	end

AerousCity_Port_EventScript_TryToBoard:
	msgbox AerousCity_Port_Text_SetSailForSabulo, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq AerousCity_Port_EventScript_LeaveForSabuloIsland
	closemessage
	release
	end

AerousCity_Port_EventScript_LeaveForSabuloIsland:
	msgbox AerousCity_Port_Text_AllAboard, MSGBOX_DEFAULT
	closemessage
	delay 20
	warp MAP_SABULO_ISLAND_PORT, -1, 8, 5
	waitstate
	release
	end

AerousCity_Port_Text_TheSSWakeIsntBackYet:
	.string "The S.S. Wake isn't back yet.\n"
	.string "Come back later, skip!$"

AerousCity_Port_Text_WantToBattle:
	.string "The S.S. Wake isn't back yet.\n"
	.string "Say, is that the Ember Badge?\p"
	.string "I've been itching to battle a\n"
	.string "strong Trainer. You up for it?$"

AerousCity_Port_Text_NotTheFightingType:
	.string "Not the fightin' type, are we?$"

AerousCity_Port_Text_BravetonIntro:
	.string "Full steam ahead!$"

AerousCity_Port_Text_BravetonDefeat:
	.string "Well, that didn't kill much time\n"
	.string "at all…$"

AerousCity_Port_Text_ThatWasAGreatBattle:
	.string "Woohoo!\n"
	.string "That was a great battle, young fry!$"

AerousCity_Port_Text_TalkAboutGoodTiming:
	.string "Talk about good timing!\n"
	.string "The S.S. Wake is back!$"

AerousCity_Port_Text_SetSailForSabulo:
	.string "Would you like to set sail\n"
	.string "for {COLOR GREEN}Sabulo Island{COLOR BLUE}?$"

AerousCity_Port_Text_AllAboard:
	.string "All right!\n"
	.string "All aboard the S.S. Wake!$"
