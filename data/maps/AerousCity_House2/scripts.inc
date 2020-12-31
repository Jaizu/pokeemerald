AerousCity_House2_MapScripts::
	.byte 0

AerousCity_House2_EventScript_Rocker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM34, AerousCity_House2_EventScript_ThankYou
	msgbox AerousCity_House2_Text_ManIMissMyGirlfriend, MSGBOX_DEFAULT
	checkitem ITEM_HARBOR_MAIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq AerousCity_House2_EventScript_OfferTradeForTM34
	release
	end

AerousCity_House2_EventScript_OfferTradeForTM34:
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox AerousCity_House2_Text_ThatHarborMailIsExactlyWhatImLookingFor, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq AerousCity_House2_EventScript_DeclineTrade
	playfanfare MUS_OBTAIN_ITEM
	message AerousCity_House2_Text_PlayerTradedHarborMailForTM34
	waitfanfare
	removeitem ITEM_HARBOR_MAIL, 1
	additem ITEM_TM34
	setflag FLAG_RECEIVED_TM34
	bufferitemnameplural 1, ITEM_TM34, 1
	bufferstdstring 2, STDSTRING_TMHMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	goto AerousCity_House2_EventScript_ThankYou
	end

AerousCity_House2_EventScript_ThankYou:
	msgbox AerousCity_House2_Text_MyGirlfriendIsGonnaBeSoHappy, MSGBOX_DEFAULT
	release
	end

AerousCity_House2_EventScript_DeclineTrade:
	msgbox AerousCity_House2_Text_AwManNotCool, MSGBOX_DEFAULT
	release
	end

AerousCity_House2_Text_ManIMissMyGirlfriend:
	.string "Man, I miss my girlfriend…\p"
	.string "I want to write her a message, but\n"
	.string "on {COLOR GREEN}paper that captures the\l"
	.string "essence of the sea{COLOR BLUE}.$"

AerousCity_House2_Text_ThatHarborMailIsExactlyWhatImLookingFor:
	.string "Hey!\p"
	.string "That {COLOR GREEN}Harbor Mail{COLOR BLUE} is exactly\n"
	.string "what I'm talking about!\p"
	.string "Let me have it?\n"
	.string "I'll give you something in return!$"

AerousCity_House2_Text_PlayerTradedHarborMailForTM34:
	.string "{COLOR DARK_GREY}{PLAYER} traded the\n"
	.string "Harbor Mail for TM34 Shock Wave!$"

AerousCity_House2_Text_MyGirlfriendIsGonnaBeSoHappy:
	.string "My girlfriend is gonna be so happy\n"
	.string "when she receives my letter!$"

AerousCity_House2_Text_AwManNotCool:
	.string "Aw, man…\n"
	.string "Not cool.$"
