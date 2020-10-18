// TODO: Create SecretPotion item
NestpineTown_House2_MapScripts::
	.byte 0

NestpineTown_House2_EventScript_HexManiac::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_DROWZEE
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	goto_if_set FLAG_NESTPINE_NPC_TRADE_COMPLETED, NestpineTown_House2_EventScript_TradeCompleted
	msgbox NestpineTown_House2_Text_IveBeenTryingToFindAnAbra, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq NestpineTown_House2_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	compare VAR_0x8004, 255
	goto_if_eq NestpineTown_House2_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne NestpineTown_House2_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname 0, VAR_0x8009
	msgbox NestpineTown_House2_Text_OhThankYou, MSGBOX_DEFAULT
	setflag FLAG_NESTPINE_NPC_TRADE_COMPLETED
	release
	end

NestpineTown_House2_EventScript_DeclineTrade::
	msgbox NestpineTown_House2_Text_AwSeeYouAround, MSGBOX_DEFAULT
	release
	end

NestpineTown_House2_EventScript_NotRequestedMon::
	bufferspeciesname 0, VAR_0x8009
	msgbox NestpineTown_House2_Text_ThatsNotAnAbra, MSGBOX_DEFAULT
	release
	end

NestpineTown_House2_EventScript_TradeCompleted::
	msgbox NestpineTown_House2_Text_HowIsMyDrowzeeDoing, MSGBOX_DEFAULT
	release
	end

NestpineTown_House2_Text_IveBeenTryingToFindAnAbra:
	.string "I've been trying to find an {STR_VAR_1}.\n"
	.string "I think they're just so cute!\p"
	.string "I'll trade my {STR_VAR_2} for your\n"
	.string "{STR_VAR_1}?$"

NestpineTown_House2_Text_OhThankYou:
	.string "Oh, thank you!$"

NestpineTown_House2_Text_ThatsNotAnAbra:
	.string "That's not an {STR_VAR_1}!\n"
	.string "Although it is cute…$"

NestpineTown_House2_Text_AwSeeYouAround:
	.string "Aw…\n"
	.string "See you around…$"

NestpineTown_House2_Text_HowIsMyDrowzeeDoing:
	.string "How is my {STR_VAR_2} doing?$"

NestpineTown_House2_EventScript_AromaLady::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SECRET_POTION, NestpineTown_House2_EventScript_ReceivedSecretPotion
	msgbox NestpineTown_House2_Text_MeAndMySisterBrewSpecialPotions, MSGBOX_DEFAULT
	giveitem ITEM_SECRET_POTION
	setflag FLAG_RECEIVED_SECRET_POTION
	goto NestpineTown_House2_EventScript_ReceivedSecretPotion
	end

NestpineTown_House2_EventScript_ReceivedSecretPotion:
	msgbox NestpineTown_House2_Text_ThatSecretPotionReallyPacksAPunch, MSGBOX_DEFAULT
	release
	end

NestpineTown_House2_Text_MeAndMySisterBrewSpecialPotions:
	.string "Me and my sister brew special\n"
	.string "Potions! Here, take one!$"

NestpineTown_House2_Text_ThatSecretPotionReallyPacksAPunch:
	.string "That SecretPotion really packs\n"
	.string "a punch!\p"
	.string "It will heal a chronically ill\n"
	.string "Pokémon right away!$"
