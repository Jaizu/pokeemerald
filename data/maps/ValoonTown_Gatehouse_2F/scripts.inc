ValoonTown_Gatehouse_2F_MapScripts::
	.byte 0

ValoonTown_Gatehouse_2F_EventScript_LeftBinoculars::
	msgbox ValoonTown_Gatehouse_2F_Text_LetsSeeWhatTheBinocularsHaveToShow, MSGBOX_DEFAULT
	setvar VAR_0x8004, SPECIES_YANMEGA
	showmonpic VAR_0x8004, 10, 3
	special SetSeenMon
	bufferspeciesname 0, VAR_0x8004
	msgbox ValoonTown_Gatehouse_2F_Text_WhoaItsAYanmega, MSGBOX_DEFAULT
	hidemonpic
	closemessage
	end

ValoonTown_Gatehouse_2F_EventScript_RightBinoculars::
	msgbox ValoonTown_Gatehouse_2F_Text_LetsSeeWhatTheBinocularsHaveToShow, MSGBOX_DEFAULT
	msgbox ValoonTown_Gatehouse_2F_Text_ThereArePeopleCapturingPokemon, MSGBOX_DEFAULT
	closemessage
	end

ValoonTown_Gatehouse_2F_Text_LetsSeeWhatTheBinocularsHaveToShow:
	.string "Let's see what the binoculars have\n"
	.string "to show…$"

ValoonTown_Gatehouse_2F_Text_WhoaItsAYanmega:
	.string "Whoa!\n"
	.string "It's a {STR_VAR_1}!$"

ValoonTown_Gatehouse_2F_Text_ThereArePeopleCapturingPokemon:
	.string "There are people capturing Pokémon\n"
	.string "in the Valoon Reserve!$"

ValoonTown_Gatehouse_2F_EventScript_ExpertM::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_SPIRITOMB
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	goto_if_set FLAG_VALOON_NPC_TRADE_COMPLETED, ValoonTown_Gatehouse_2F_EventScript_TradeCompleted
	msgbox ValoonTown_Gatehouse_2F_Text_HaveYouAZangoose, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ValoonTown_Gatehouse_2F_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	compare VAR_0x8004, 255
	goto_if_eq ValoonTown_Gatehouse_2F_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne ValoonTown_Gatehouse_2F_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname 0, VAR_0x8009
	msgbox ValoonTown_Gatehouse_2F_Text_WiseChoiceYoungOne, MSGBOX_DEFAULT
	setflag FLAG_VALOON_NPC_TRADE_COMPLETED
	release
	end

ValoonTown_Gatehouse_2F_EventScript_DeclineTrade::
	msgbox ValoonTown_Gatehouse_2F_Text_YoureAFool, MSGBOX_DEFAULT
	release
	end

ValoonTown_Gatehouse_2F_EventScript_NotRequestedMon::
	bufferspeciesname 0, VAR_0x8009
	msgbox ValoonTown_Gatehouse_2F_Text_ThatIsNoZangoose, MSGBOX_DEFAULT
	release
	end

ValoonTown_Gatehouse_2F_EventScript_TradeCompleted::
	msgbox ValoonTown_Gatehouse_2F_Text_WellMetYoungOne, MSGBOX_DEFAULT
	release
	end

ValoonTown_Gatehouse_2F_Text_HaveYouAZangoose:
	.string "Have you a {STR_VAR_1}?\p"
	.string "Bring me one, and I shall bestow\n"
	.string "unto you my {STR_VAR_2}…$"

ValoonTown_Gatehouse_2F_Text_WiseChoiceYoungOne:
	.string "Wise choice, young one.$"

ValoonTown_Gatehouse_2F_Text_ThatIsNoZangoose:
	.string "That is no {STR_VAR_1}!$"

ValoonTown_Gatehouse_2F_Text_YoureAFool:
	.string "You're a fool!$"

ValoonTown_Gatehouse_2F_Text_WellMetYoungOne:
	.string "Well met, young one.\n"
	.string "How fares {STR_VAR_2}?$"
