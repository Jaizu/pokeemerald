SerosVillage_House_MapScripts::
	.byte 0

SerosVillage_House_EventScript_RareBoneManiac::
	lock
	faceplayer
	msgbox SerosVillage_House_Text_YouKnowAboutRareBones, MSGBOX_DEFAULT
	checkitem ITEM_RARE_BONE, 1
	compare VAR_RESULT, FALSE
	goto_if_ne SerosVillage_House_EventScript_OfferToBuy
	release
	end

SerosVillage_House_EventScript_OfferToBuy:
	showmoneybox 0, 0, 0
	msgbox SerosVillage_House_Text_WillYouSellToMe, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_House_EventScript_SellRareBone
	msgbox SerosVillage_House_Text_OhAlright, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

SerosVillage_House_EventScript_SellRareBone:
	removeitem ITEM_RARE_BONE, 1
	playse SE_REGI
	addmoney 10000, 0
	updatemoneybox 0, 0
	waitse
	playfanfare MUS_FANFA4
	message SerosVillage_House_Text_PlayerSoldOneRareBone
	waitfanfare
	hidemoneybox
	msgbox SerosVillage_House_Text_WhatADeal, MSGBOX_DEFAULT
	release
	end

SerosVillage_House_Text_YouKnowAboutRareBones:
	.string "You know about {COLOR GREEN}Rare Bones{COLOR BLUE},\n"
	.string "right?\p"
	.string "I collect them!\n"
	.string "You should bring me any you find.\p"
	.string "I'll make it worth your while!$"

SerosVillage_House_Text_WillYouSellToMe:
	.string "What's up?\p"
	.string "Whoa!\n"
	.string "You found one?\p"
	.string "Will you sell it to me?\n"
	.string "I'll pay {COLOR GREEN}¥10000{COLOR BLUE} for it!$"

SerosVillage_House_Text_OhAlright:
	.string "Oh, alright…$"

SerosVillage_House_Text_PlayerSoldOneRareBone:
	.string "{COLOR DARK_GREY}{PLAYER} sold 1 Rare Bone\n"
	.string "to the man for ¥10000!$"

SerosVillage_House_Text_WhatADeal:
	.string "What a deal!$"
