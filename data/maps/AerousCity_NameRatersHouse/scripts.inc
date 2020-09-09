AerousCity_NameRatersHouse_MapScripts::
	.byte 0

AerousCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox AerousCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq AerousCity_NameRatersHouse_EventScript_ChooseMonToRate
	compare VAR_RESULT, NO
	goto_if_eq AerousCity_NameRatersHouse_EventScript_DeclineNameRate
	end

AerousCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox AerousCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_ne AerousCity_NameRatersHouse_EventScript_RateMonNickname
	compare VAR_0x8004, 255
	goto_if_eq AerousCity_NameRatersHouse_EventScript_DeclineNameRate
	end

AerousCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox AerousCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

AerousCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq AerousCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	compare VAR_RESULT, TRUE
	goto_if_eq AerousCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	compare VAR_RESULT, TRUE
	goto_if_eq AerousCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox AerousCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq AerousCity_NameRatersHouse_EventScript_ChangeNickname
	compare VAR_RESULT, NO
	goto_if_eq AerousCity_NameRatersHouse_EventScript_DeclineNameRate
	end

AerousCity_NameRatersHouse_EventScript_CantRateEgg::
	msgbox AerousCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

AerousCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox AerousCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

AerousCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox AerousCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	compare VAR_RESULT, TRUE
	goto_if_eq AerousCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox AerousCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

AerousCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox AerousCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

AerousCity_NameRatersHouse_Text_PleasedToRateMonNickname:
	.string "Hi, hi! I'm the Name Rater!\n"
	.string "I'm the fortune-teller of names!\p"
	.string "I shall be pleased to rate your\n"
	.string "Pokémon's nickname.$"

AerousCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
	.string "Which Pokémon's nickname should\n"
	.string "I critique?$"

AerousCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
	.string "Hmmm… {STR_VAR_1}, is it? That is\n"
	.string "quite a fine name you bestowed.\p"
	.string "But! What say you, if I were to\n"
	.string "suggest a slightly better name?$"

AerousCity_NameRatersHouse_Text_WhatShallNewNameBe:
	.string "Ah, good. Then, what shall the new\n"
	.string "nickname be?$"

AerousCity_NameRatersHouse_Text_MonShallBeKnownAsName:
	.string "Done! From now on, this Pokémon\n"
	.string "shall be known as {STR_VAR_1}!\p"
	.string "It is a better name than before!\n"
	.string "How fortunate for you!$"

AerousCity_NameRatersHouse_Text_DoVisitAgain:
	.string "I see.\n"
	.string "Do come visit again.$"

AerousCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
	.string "Done! From now on, this Pokémon\n"
	.string "shall be known as {STR_VAR_1}!\p"
	.string "It looks no different from before,\n"
	.string "and yet, this is vastly superior!\p"
	.string "How fortunate for you!$"

AerousCity_NameRatersHouse_Text_MagnificentName:
	.string "Hmmm… {STR_VAR_1} it is!\p"
	.string "This is a magnificent nickname!\n"
	.string "It is impeccably beyond reproach!\p"
	.string "You'll do well to cherish your\n"
	.string "{STR_VAR_1} now and beyond.$"

AerousCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
	.string "Now, now.\n"
	.string "That is merely an Egg!$"
