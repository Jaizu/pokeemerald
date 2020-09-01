.set LOCALID_DAYCARE_LADY, 1

SerosVillage_DayCareCenter_MapScripts::
	.byte 0

SerosVillage_DayCareCenter_EventScript_DaycareWoman:: @ 8291D11
	lock
	faceplayer
	goto_if_unset FLAG_FERNANDO_STORMED_OFF, SerosVillage_DayCareCenter_EventScript_FullCapacityRightNow
	goto_if_unset FLAG_FERNANDO_RESCUED, SerosVillage_DayCareCenter_EventScript_PleaseHelpFernando
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_EGG_WAITING
	goto_if_eq SerosVillage_DayCareCenter_EventScript_EggWaiting
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq SerosVillage_DayCareCenter_EventScript_OneMonInDaycare
	compare VAR_RESULT, DAYCARE_TWO_MONS
	goto_if_eq SerosVillage_DayCareCenter_EventScript_TwoMonsInDaycare
	msgbox SerosVillage_DayCareCenter_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_GiveMonToRaise
	msgbox SerosVillage_DayCareCenter_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_FullCapacityRightNow:
	msgbox SerosVillage_DayCareCenter_Text_WeAreAtFullCapacity, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_PleaseHelpFernando:
	msgbox SerosVillage_DayCareCenter_Text_PleaseHelpFernando, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_GiveMonToRaise:: @ 8291D56
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 1
	goto_if_eq SerosVillage_DayCareCenter_EventScript_OnlyOneMon
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	compare VAR_RESULT, 2
	goto_if_eq SerosVillage_DayCareCenter_EventScript_OnlyTwoAliveMons
	msgbox SerosVillage_DayCareCenter_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseSendDaycareMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq SerosVillage_DayCareCenter_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	compare VAR_RESULT, 0
	goto_if_eq SerosVillage_DayCareCenter_EventScript_OnlyOneAliveMon
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry VAR_0x8005, 0
	msgbox SerosVillage_DayCareCenter_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq SerosVillage_DayCareCenter_EventScript_CanRaiseOneMore
	release
	end

SerosVillage_DayCareCenter_EventScript_ComeAgain:: @ 8291DCA
	msgbox SerosVillage_DayCareCenter_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_CanRaiseOneMore:: @ 8291DD4
	msgbox SerosVillage_DayCareCenter_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_GiveMonToRaise
	goto SerosVillage_DayCareCenter_EventScript_ComeAgain
	end

SerosVillage_DayCareCenter_EventScript_OnlyOneMon:: @ 8291DED
	msgbox SerosVillage_DayCareCenter_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_OnlyOneAliveMon:: @ 8291DF7
	msgbox SerosVillage_DayCareCenter_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_OnlyTwoAliveMons:: @ 8291E01
	msgbox SerosVillage_DayCareCenter_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_EggWaiting:: @ 8291E0B
	msgbox SerosVillage_DayCareCenter_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_YourMonHasGrownXLevels:: @ 8291E15
	msgbox SerosVillage_DayCareCenter_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

SerosVillage_DayCareCenter_EventScript_DisplayLevelsGained:: @ 8291E1E
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	compare VAR_RESULT, 0
	call_if_ne SerosVillage_DayCareCenter_EventScript_YourMonHasGrownXLevels
	return

SerosVillage_DayCareCenter_EventScript_OneMonInDaycare:: @ 8291E2F
	msgbox SerosVillage_DayCareCenter_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call SerosVillage_DayCareCenter_EventScript_DisplayLevelsGained
	msgbox SerosVillage_DayCareCenter_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_GiveMonToRaise
	msgbox SerosVillage_DayCareCenter_Text_TakeYourMonBack, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_TryRetrieveMon
	goto SerosVillage_DayCareCenter_EventScript_ComeAgain
	end

SerosVillage_DayCareCenter_EventScript_TryRetrieveMon:: @ 8291E6D
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq SerosVillage_DayCareCenter_EventScript_NoRoom
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq SerosVillage_DayCareCenter_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	compare VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU
	goto_if_eq SerosVillage_DayCareCenter_EventScript_ComeAgain
	goto SerosVillage_DayCareCenter_EventScript_CostPrompt
	end

SerosVillage_DayCareCenter_EventScript_CostPrompt:: @ 8291EAC
	special GetDaycareCost
	msgbox SerosVillage_DayCareCenter_Text_ItWillCostX, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_CheckEnoughMoney
	goto SerosVillage_DayCareCenter_EventScript_ComeAgain
	end

SerosVillage_DayCareCenter_EventScript_CheckEnoughMoney:: @ 8291EC8
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	compare VAR_RESULT, 1
	goto_if_eq SerosVillage_DayCareCenter_EventScript_RetrieveMon
	msgbox SerosVillage_DayCareCenter_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_RetrieveMon:: @ 8291EE2
	applymovement LOCALID_DAYCARE_LADY, SerosVillage_DayCareCenter_Movement_RetrieveDaycareMon
	waitmovement 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_REGI
	msgbox SerosVillage_DayCareCenter_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry VAR_RESULT, 0
	msgbox SerosVillage_DayCareCenter_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq SerosVillage_DayCareCenter_EventScript_AskRetrieveOtherMon
	goto SerosVillage_DayCareCenter_EventScript_ComeAgain
	end

SerosVillage_DayCareCenter_EventScript_AskRetrieveOtherMon:: @ 8291F24
	msgbox SerosVillage_DayCareCenter_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_TryRetrieveMon
	goto SerosVillage_DayCareCenter_EventScript_ComeAgain
	end

SerosVillage_DayCareCenter_EventScript_NoRoom:: @ 8291F3D
	msgbox SerosVillage_DayCareCenter_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_Movement_RetrieveDaycareMon: @ 8291F47
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_right
	delay_16
	delay_16
	face_up
	walk_slow_up
	set_invisible
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	set_visible
	walk_slow_down
	step_end

SerosVillage_DayCareCenter_EventScript_TwoMonsInDaycare:: @ 8291F5C
	msgbox SerosVillage_DayCareCenter_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call SerosVillage_DayCareCenter_EventScript_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call SerosVillage_DayCareCenter_EventScript_DisplayLevelsGained
	msgbox SerosVillage_DayCareCenter_Text_TakeYourMonBack, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_TryRetrieveMon
	msgbox SerosVillage_DayCareCenter_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_Text_WeAreAtFullCapacity:
	.string "I'm the Day-Care Lady.\n"
	.string "We're at full capacity right now.\p"
	.string "Sorry, but we can't raise any\n"
	.string "more Pokémon right now.$"

SerosVillage_DayCareCenter_Text_PleaseHelpFernando:
	.string "Oh my, is my dear Fernando safe?\p"
	.string "Please, you must help him!$"

SerosVillage_DayCareCenter_Text_WouldYouLikeUsToRaiseAMon: @ 82922F4
	.string "I'm the Day-Care Lady.\p"
	.string "We can raise Pokémon for you.\p"
	.string "Would you like us to raise one?$"

SerosVillage_DayCareCenter_Text_WhichMonShouldWeRaise: @ 8292349
	.string "Which Pokémon should we raise for\n"
	.string "you?$"

SerosVillage_DayCareCenter_Text_WellRaiseYourMon: @ 8292370
	.string "Fine, we'll raise your {STR_VAR_1}\n"
	.string "for a while.\p"
	.string "Come back for it later.$"

SerosVillage_DayCareCenter_Text_WeCanRaiseOneMore: @ 82923AF
	.string "We can raise two of your Pokémon.\n"
	.string "Would you like us to raise one more?$"

SerosVillage_DayCareCenter_Text_HusbandWasLookingForYou: @ 82923F6
	.string "My husband was looking for you.$"

SerosVillage_DayCareCenter_Text_FineThenComeAgain: @ 8292416
	.string "Oh, fine, then.\n"
	.string "Come again.$"

SerosVillage_DayCareCenter_Text_NotEnoughMoney: @ 8292432
	.string "You don't have enough money…$"

SerosVillage_DayCareCenter_Text_TakeOtherOneBackToo: @ 829244F
	.string "Will you take back the other one,\n"
	.string "too?$"

SerosVillage_DayCareCenter_Text_ComeAgain: @ 8292476
	.string "Fine.\n"
	.string "Come again.$"

SerosVillage_DayCareCenter_Text_GoodToSeeYou: @ 8292488
	.string "Ah, it's you! Good to see you.\n"
	.string "Your Pokémon can only be doing good!$"

SerosVillage_DayCareCenter_Text_YourMonHasGrownXLevels: @ 82924CC
	.string "By level, your {STR_VAR_1} has\n"
	.string "grown by {STR_VAR_2}.$"

SerosVillage_DayCareCenter_Text_YourTeamIsFull: @ 82924EF
	.string "Your Pokémon team is full.\n"
	.string "Make room, then come see me.$"

SerosVillage_DayCareCenter_Text_ItWillCostX: @ 8292549
	.string "If you want your {STR_VAR_1} back,\n"
	.string "it will cost ¥{STR_VAR_2}.$"

SerosVillage_DayCareCenter_Text_HeresYourMon: @ 8292575
	.string "Perfect!\n"
	.string "Here's your Pokémon.$"

SerosVillage_DayCareCenter_Text_TookBackMon: @ 8292593
	.string "{PLAYER} took back {STR_VAR_1} from\n"
	.string "the Day-Care Lady.$"

SerosVillage_DayCareCenter_Text_YouHaveJustOneMon: @ 82925BB
	.string "Oh? But you have just one\n"
	.string "Pokémon.\p"
	.string "Come back another time.$"

SerosVillage_DayCareCenter_Text_TakeYourMonBack: @ 82925F6
	.string "Will you take your Pokémon back?$"

SerosVillage_DayCareCenter_Text_WhatWillYouBattleWith: @ 8292617
	.string "If you leave me that Pokémon,\n"
	.string "what will you battle with?\p"
	.string "Come back another time.$"

SerosVillage_DayCareCenter_Text_YoullBeLeftWithJustOne: @ 829266D
	.string "Huh?\n"
	.string "Now, now.\p"
	.string "If you leave that Pokémon with\n"
	.string "me, you'll be left with just one.\p"
	.string "You will be better off if you catch\n"
	.string "some more, I dare say.$"
