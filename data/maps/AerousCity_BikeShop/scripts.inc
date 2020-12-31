AerousCity_BikeShop_MapScripts::
	.byte 0

AerousCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, AerousCity_BikeShop_EventScript_AlreadyGotBike
	checkitem ITEM_BIKE_VOUCHER, 1
	compare VAR_RESULT, TRUE
	goto_if_eq AerousCity_BikeShop_EventScript_ExchangeBikeVoucher
	showmoneybox 0, 0, 0
	message AerousCity_BikeShop_Text_WelcomeToBikeShop
	waitmessage
	multichoice 21, 8, MULTI_BIKE_SHOP, FALSE
	switch VAR_RESULT
	case 0, AerousCity_BikeShop_EventScript_TryPurchaseBicycle
	case 1, AerousCity_BikeShop_EventScript_ClerkGoodbye
	case 127, AerousCity_BikeShop_EventScript_ClerkGoodbye
	end

AerousCity_BikeShop_EventScript_TryPurchaseBicycle:
	msgbox AerousCity_BikeShop_Text_SorryYouCantAffordIt
	goto AerousCity_BikeShop_EventScript_ClerkGoodbye
	end

AerousCity_BikeShop_EventScript_ClerkGoodbye:
	msgbox AerousCity_BikeShop_Text_ThankYouComeAgain
	hidemoneybox
	release
	end

AerousCity_BikeShop_EventScript_ExchangeBikeVoucher:
	msgbox AerousCity_BikeShop_Text_OhBikeVoucherHereYouGo
	playfanfare MUS_OBTAIN_ITEM
	message AerousCity_BikeShop_Text_ExchangedVoucherForBicycle
	additem ITEM_BICYCLE
	setflag FLAG_RECEIVED_BIKE
	removeitem ITEM_BIKE_VOUCHER
	waitfanfare
	msgbox AerousCity_BikeShop_Text_ThankYouComeAgain
	release
	end

AerousCity_BikeShop_EventScript_AlreadyGotBike:
	msgbox AerousCity_BikeShop_Text_HowIsYourNewBicycleTreatingYou
	release
	end

AerousCity_BikeShop_Text_WelcomeToBikeShop:
	.string "Yo!\n"
	.string "Welcome to our Bike Shop!\p"
	.string "Interested in buying?\n"
	.string "We've got the Bike for you!$"

AerousCity_BikeShop_Text_SorryYouCantAffordIt:
	.string "Sorry!\n"
	.string "You can't afford it!$"

AerousCity_BikeShop_Text_OhBikeVoucherHereYouGo:
	.string "Oh, that's…\p"
	.string "A Bike Voucher!\p"
	.string "Okay!\n"
	.string "Here you go!$"

AerousCity_BikeShop_Text_ExchangedVoucherForBicycle:
	.string "{COLOR DARK_GREY}{PLAYER} exchanged the\n"
	.string "Bike Voucher for a Bicycle.$"

AerousCity_BikeShop_Text_ThankYouComeAgain:
	.string "Thank you!\n"
	.string "Come back again sometime!$"

AerousCity_BikeShop_Text_HowIsYourNewBicycleTreatingYou:
	.string "How is your new Bicycle treating\n"
	.string "you? Does it ride well?\p"
	.string "Try riding on Gyarados Bridge!\n"
	.string "There are lots of Cyclists there.$"

AerousCity_BikeShop_EventScript_Youngster::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, AerousCity_BikeShop_EventScript_YourBikeIsSoCool
	msgbox AerousCity_BikeShop_Text_CoolButExpensive, MSGBOX_DEFAULT
	release
	end

AerousCity_BikeShop_EventScript_YourBikeIsSoCool:
	msgbox AerousCity_BikeShop_Text_YourBikeIsSoCool, MSGBOX_DEFAULT
	release
	end

AerousCity_BikeShop_Text_CoolButExpensive:
	.string "Cool… but expensive!\n"
	.string "What a quandry!$"

AerousCity_BikeShop_Text_YourBikeIsSoCool:
	.string "Your Bike is so cool!$"

AerousCity_BikeShop_EventScript_Bike::
	msgbox AerousCity_BikeShop_Text_AShinyNewBicycle, MSGBOX_SIGN
	end

AerousCity_BikeShop_Text_AShinyNewBicycle:
	.string "A shiny new Bicycle!$"
