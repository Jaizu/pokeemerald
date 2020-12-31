.set LOCALID_DAYCARE_WOMAN, 1
.set LOCALID_DAYCARE_MAN, 2
.set LOCALID_FERNANDO, 3

SerosVillage_DayCareCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SerosVillage_DayCareCenter_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SerosVillage_DayCareCenter_OnFrame
	.byte 0

SerosVillage_DayCareCenter_OnTransition:
	compare VAR_DAY_CARE_CENTER_STATE, 1
	call_if_eq SerosVillage_DayCareCenter_EventScript_MoveDayCareWoman
	end

SerosVillage_DayCareCenter_EventScript_MoveDayCareWoman:
	setobjectxyperm LOCALID_DAYCARE_WOMAN, 8, 3
	setobjectmovementtype LOCALID_DAYCARE_WOMAN, MOVEMENT_TYPE_FACE_LEFT
	return

SerosVillage_DayCareCenter_OnFrame:
	map_script_2 VAR_DAY_CARE_CENTER_STATE, 1, SerosVillage_DayCareCenter_EventScript_GiveHM01Scene
	.2byte 0

SerosVillage_DayCareCenter_EventScript_GiveHM01Scene:
	lockall
	setflag FLAG_FERNANDO_RESCUED
	msgbox SerosVillage_DayCareCenter_Text_ThankYou, MSGBOX_DEFAULT
	giveitem ITEM_HM01
	setflag FLAG_RECEIVED_HM01
	msgbox SerosVillage_DayCareCenter_Text_ThatHMContainsCut, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DAYCARE_WOMAN, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox SerosVillage_DayCareCenter_Text_IWantToThankYou, MSGBOX_DEFAULT
	applymovement LOCALID_FERNANDO, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox SerosVillage_DayCareCenter_Text_GrandmaImNotLikeThatAnymore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FERNANDO, SerosVillage_DayCareCenter_Movement_ExitFernando
	waitmovement 0
	playse SE_EXIT
	waitse
	removeobject LOCALID_FERNANDO
	clearflag FLAG_HIDE_SEROS_GYM_FERNANDO
	delay 10
	msgbox SerosVillage_DayCareCenter_Text_IAlsoNeedToGetBackToWork, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DAYCARE_MAN, SerosVillage_DayCareCenter_Movement_ExitDayCareMan
	waitmovement 0
	playse SE_EXIT
	waitse
	removeobject LOCALID_DAYCARE_MAN
	fadescreen FADE_TO_BLACK
	setobjectxy LOCALID_DAYCARE_WOMAN, 1, 3
	setobjectxyperm LOCALID_DAYCARE_WOMAN, 1, 3
	setobjectmovementtype LOCALID_DAYCARE_WOMAN, MOVEMENT_TYPE_FACE_DOWN
	turnobject LOCALID_DAYCARE_WOMAN, DIR_SOUTH
	fadescreen FADE_FROM_BLACK
	setvar VAR_DAY_CARE_CENTER_STATE, 2
	releaseall
	end

SerosVillage_DayCareCenter_Text_ThankYou:
	.string "Day-Care Man: {COLOR BLUE}Thank you for\n"
	.string "bringing my grandson back.\p"
	.string "We were so worried about him!\p"
	.string "Especially because he had no\n"
	.string "Pokémon.\p"
	.string "Anyway, I would like to give you\n"
	.string "this, as a token of my appreciation.$"

SerosVillage_DayCareCenter_Text_ThatHMContainsCut:
	.string "Day-Care Man: {COLOR BLUE}That's HM01.\n"
	.string "It contains the move Cut.\p"
	.string "I am sure a Trainer like you will\n"
	.string "find it very useful!$"

SerosVillage_DayCareCenter_Text_IWantToThankYou:
	.string "Day-Care Lady: {COLOR RED}I want to thank\n"
	.string "you for knocking some sense into\l"
	.string "my grandson.\p"
	.string "He's a… sensitive one.$"

SerosVillage_DayCareCenter_Text_GrandmaImNotLikeThatAnymore:
	.string "Fernando: {COLOR BLUE}Grandma!\n"
	.string "I'm not like that anymore.\p"
	.string "From now on I'm going to be like\n"
	.string "{PLAYER}.\p"
	.string "I'm going to be a cool, silent\n"
	.string "Trainer!\p"
	.string "Now!\n"
	.string "I've got a Gym to go run.$"

SerosVillage_DayCareCenter_Text_IAlsoNeedToGetBackToWork:
	.string "Day-Care Man: {COLOR BLUE}I also need to get\n"
	.string "back to work.\p"
	.string "Thanks again, {PLAYER}, and feel\n"
	.string "free to leave your Pokémon here if\l"
	.string "they ever need a rest!$"

SerosVillage_DayCareCenter_Movement_ExitFernando:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end

SerosVillage_DayCareCenter_Movement_ExitDayCareMan:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end

SerosVillage_DayCareCenter_EventScript_DaycareWoman::
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

SerosVillage_DayCareCenter_EventScript_GiveMonToRaise::
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

SerosVillage_DayCareCenter_EventScript_ComeAgain::
	msgbox SerosVillage_DayCareCenter_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_CanRaiseOneMore::
	msgbox SerosVillage_DayCareCenter_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_GiveMonToRaise
	goto SerosVillage_DayCareCenter_EventScript_ComeAgain
	end

SerosVillage_DayCareCenter_EventScript_OnlyOneMon::
	msgbox SerosVillage_DayCareCenter_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_OnlyOneAliveMon::
	msgbox SerosVillage_DayCareCenter_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_OnlyTwoAliveMons::
	msgbox SerosVillage_DayCareCenter_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_EggWaiting::
	msgbox SerosVillage_DayCareCenter_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_YourMonHasGrownXLevels::
	msgbox SerosVillage_DayCareCenter_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

SerosVillage_DayCareCenter_EventScript_DisplayLevelsGained::
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	compare VAR_RESULT, 0
	call_if_ne SerosVillage_DayCareCenter_EventScript_YourMonHasGrownXLevels
	return

SerosVillage_DayCareCenter_EventScript_OneMonInDaycare::
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

SerosVillage_DayCareCenter_EventScript_TryRetrieveMon::
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

SerosVillage_DayCareCenter_EventScript_CostPrompt::
	special GetDaycareCost
	msgbox SerosVillage_DayCareCenter_Text_ItWillCostX, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_CheckEnoughMoney
	goto SerosVillage_DayCareCenter_EventScript_ComeAgain
	end

SerosVillage_DayCareCenter_EventScript_CheckEnoughMoney::
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	compare VAR_RESULT, 1
	goto_if_eq SerosVillage_DayCareCenter_EventScript_RetrieveMon
	msgbox SerosVillage_DayCareCenter_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_EventScript_RetrieveMon::
	applymovement LOCALID_DAYCARE_WOMAN, SerosVillage_DayCareCenter_Movement_RetrieveDaycareMon
	waitmovement 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_SHOP
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

SerosVillage_DayCareCenter_EventScript_AskRetrieveOtherMon::
	msgbox SerosVillage_DayCareCenter_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_DayCareCenter_EventScript_TryRetrieveMon
	goto SerosVillage_DayCareCenter_EventScript_ComeAgain
	end

SerosVillage_DayCareCenter_EventScript_NoRoom::
	msgbox SerosVillage_DayCareCenter_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

SerosVillage_DayCareCenter_Movement_RetrieveDaycareMon:
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

SerosVillage_DayCareCenter_EventScript_TwoMonsInDaycare::
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

SerosVillage_DayCareCenter_Text_WouldYouLikeUsToRaiseAMon:
	.string "Oh, {PLAYER}!\n"
	.string "How are you?\p"
	.string "We can raise Pokémon for you.\p"
	.string "Would you like us to raise one?$"

SerosVillage_DayCareCenter_Text_WhichMonShouldWeRaise:
	.string "Which Pokémon should we raise for\n"
	.string "you?$"

SerosVillage_DayCareCenter_Text_WellRaiseYourMon:
	.string "Fine, we'll raise your {STR_VAR_1}\n"
	.string "for a while.\p"
	.string "Come back for it later.$"

SerosVillage_DayCareCenter_Text_WeCanRaiseOneMore:
	.string "We can raise two of your Pokémon.\n"
	.string "Would you like us to raise one more?$"

SerosVillage_DayCareCenter_Text_HusbandWasLookingForYou:
	.string "My husband was looking for you.$"

SerosVillage_DayCareCenter_Text_FineThenComeAgain:
	.string "Oh, fine, then.\n"
	.string "Come again.$"

SerosVillage_DayCareCenter_Text_NotEnoughMoney:
	.string "You don't have enough money…$"

SerosVillage_DayCareCenter_Text_TakeOtherOneBackToo:
	.string "Will you take back the other one,\n"
	.string "too?$"

SerosVillage_DayCareCenter_Text_ComeAgain:
	.string "Fine.\n"
	.string "Come again.$"

SerosVillage_DayCareCenter_Text_GoodToSeeYou:
	.string "Ah, {PLAYER}!\n"
	.string "Your Pokémon can only be doing good!$"

SerosVillage_DayCareCenter_Text_YourMonHasGrownXLevels:
	.string "By level, your {STR_VAR_1} has\n"
	.string "grown by {STR_VAR_2}.$"

SerosVillage_DayCareCenter_Text_YourTeamIsFull:
	.string "Your Pokémon team is full.\n"
	.string "Make room, then come see me.$"

SerosVillage_DayCareCenter_Text_ItWillCostX:
	.string "If you want your {STR_VAR_1} back,\n"
	.string "it will cost ¥{STR_VAR_2}.$"

SerosVillage_DayCareCenter_Text_HeresYourMon:
	.string "Perfect!\n"
	.string "Here's your Pokémon.$"

SerosVillage_DayCareCenter_Text_TookBackMon:
	.string "{PLAYER} took back {STR_VAR_1} from\n"
	.string "the Day-Care Lady.$"

SerosVillage_DayCareCenter_Text_YouHaveJustOneMon:
	.string "Oh? But you have just one\n"
	.string "Pokémon.\p"
	.string "Come back another time.$"

SerosVillage_DayCareCenter_Text_TakeYourMonBack:
	.string "Will you take your Pokémon back?$"

SerosVillage_DayCareCenter_Text_WhatWillYouBattleWith:
	.string "If you leave me that Pokémon,\n"
	.string "what will you battle with?\p"
	.string "Come back another time.$"

SerosVillage_DayCareCenter_Text_YoullBeLeftWithJustOne:
	.string "Huh?\n"
	.string "Now, now.\p"
	.string "If you leave that Pokémon with\n"
	.string "me, you'll be left with just one.\p"
	.string "You will be better off if you catch\n"
	.string "some more, I dare say.$"
