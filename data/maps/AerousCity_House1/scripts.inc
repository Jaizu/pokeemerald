AerousCity_House1_MapScripts::
	.byte 0

AerousCity_House1_EventScript_Gentleman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_AMULET_COIN, AerousCity_House1_EventScript_ExplainAmuletCoin
	msgbox AerousCity_House1_Text_YouLookLikeALearnedExecutiveToMe, MSGBOX_DEFAULT
	showmoneybox 0, 0, 0
	msgbox AerousCity_House1_Text_IveGotTheDealOfTheCentury, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq AerousCity_House1_EventScript_TryBuyAmuletCoin
	msgbox AerousCity_House1_Text_BeingStingyWillGetYouNowhere, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

AerousCity_House1_EventScript_TryBuyAmuletCoin:
	checkmoney 5000, 0
	compare VAR_RESULT, FALSE
	goto_if_eq AerousCity_House1_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 5000, 0
	updatemoneybox 0, 0
	waitse
	giveitem ITEM_AMULET_COIN
	setflag FLAG_RECEIVED_AMULET_COIN
	hidemoneybox
	goto AerousCity_House1_EventScript_ExplainAmuletCoin
	end

AerousCity_House1_EventScript_NotEnoughMoney:
	msgbox AerousCity_House1_Text_YouCantAffordThis, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

AerousCity_House1_EventScript_ExplainAmuletCoin:
	msgbox AerousCity_House1_Text_ThatAmuletCoinWillMakeYouRich, MSGBOX_DEFAULT
	release
	end

AerousCity_House1_Text_YouLookLikeALearnedExecutiveToMe:
	.string "Hello!\p"
	.string "You look like a learned executive\n"
	.string "to me!$"

AerousCity_House1_Text_IveGotTheDealOfTheCentury:
	.string "I've got the deal of the century\n"
	.string "here, kid.\p"
	.string "For the low, low price of {COLOR GREEN}¥5000{COLOR BLUE},\n"
	.string "you can take this amazing item!\p"
	.string "What do you say, kid?$"

AerousCity_House1_Text_BeingStingyWillGetYouNowhere:
	.string "Being stingy will get you nowhere!$"

AerousCity_House1_Text_YouCantAffordThis:
	.string "You can't afford this!$"

AerousCity_House1_Text_ThatAmuletCoinWillMakeYouRich:
	.string "That Amulet Coin will make you\n"
	.string "rich!\p"
	.string "A wise investment indeed!$"
