NestpineTown_House1_MapScripts::
	.byte 0

NestpineTown_House1_EventScript_AromaLady::
	lock
	faceplayer
	msgbox NestpineTown_House1_Text_AtNightYouCanSeeTheStars, MSGBOX_DEFAULT
	checkitem ITEM_STAR_PIECE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq NestpineTown_House1_EventScript_OfferTrade
	release
	end

NestpineTown_House1_EventScript_OfferTrade:
	msgbox NestpineTown_House1_Text_AhYouHaveOneTradeForMyPPUp, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne NestpineTown_House1_EventScript_Goodbye
	playfanfare MUS_FANFA4
	message NestpineTown_House1_Text_PlayerTradedOneStarPiece
	waitfanfare
	removeitem ITEM_STAR_PIECE, 1
	additem ITEM_PP_UP, 1
	bufferitemnameplural 1, ITEM_PP_UP, 1
	bufferstdstring 2, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	msgbox NestpineTown_House1_Text_NiceDoingBusinessWithYou, MSGBOX_DEFAULT
	release
	end
	
NestpineTown_House1_EventScript_Goodbye:
	msgbox NestpineTown_House1_Text_OhOkayGoodbye, MSGBOX_DEFAULT
	release
	end

NestpineTown_House1_Text_AtNightYouCanSeeTheStars:
	.string "At night you can see the stars\n"
	.string "shine brilliantly up here.\p"
	.string "{COLOR GREEN}Star Pieces{COLOR RED} remind me of that\n"
	.string "beauty.$"

NestpineTown_House1_Text_AhYouHaveOneTradeForMyPPUp:
	.string "Ah, you have one!\n"
	.string "Trade for my PP Up?$"

NestpineTown_House1_Text_PlayerTradedOneStarPiece:
	.string "{COLOR DARK_GREY}{PLAYER} traded 1 Star Piece\n"
	.string "for 1 PP Up!$"

NestpineTown_House1_Text_NiceDoingBusinessWithYou:
	.string "Nice doing business with you!$"

NestpineTown_House1_Text_OhOkayGoodbye:
	.string "Oh, okay…\n"
	.string "Goodbye.$"
