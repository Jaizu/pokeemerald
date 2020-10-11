WindmistCity_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, WindmistCity_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, WindmistCity_OnTransition
	.byte 0

WindmistCity_OnLoad::
	call_if_unset FLAG_UNLOCK_WINDMIST_GYM_DOOR, WindmistCity_EventScript_LockGymDoor
	end

WindmistCity_EventScript_LockGymDoor:
	setmetatile 30, 12, METATILE_Winter_Door_GymLocked, 1
	return

WindmistCity_OnTransition::
	setflag FLAG_VISITED_WINDMIST_CITY
	compare VAR_CELANTO_GROVE_STATE, 0
	call_if_eq WindmistCity_EventScript_ClearCelantoGroveRoadblock
	end

WindmistCity_EventScript_ClearCelantoGroveRoadblock:
	setvar VAR_CELANTO_GROVE_STATE, 1
	return

WindmistCity_EventScript_CitySign::
	msgbox WindmistCity_Text_CitySign, MSGBOX_SIGN
	end

WindmistCity_Text_CitySign::
	.string "Windmist City\n"
	.string "An Icy Pocket on the Mountain.$"

WindmistCity_EventScript_FrostbiteCaveSign::
	msgbox WindmistCity_Text_FrostbiteCaveSign, MSGBOX_SIGN
	end

WindmistCity_Text_FrostbiteCaveSign::
	.string "{UP_ARROW} Frostbite Cave\n"
	.string "Follow through to Nestpine Town.$"

WindmistCity_EventScript_GymSign::
	msgbox WindmistCity_Text_GymSign, MSGBOX_SIGN
	end

WindmistCity_Text_GymSign:
	.string "Windmist City Pokémon Gym\p"
	.string "Leader: Nina\n"
	.string "“The Furnace in the Snow.”$"

WindmistCity_EventScript_CableCarSign::
	msgbox WindmistCity_Text_MtIgnisCableCar, MSGBOX_SIGN
	end

WindmistCity_Text_MtIgnisCableCar::
	.string "Mt. Ignis Cable Car\n"
	.string "Take a ride down the mountain!$"

WindmistCity_EventScript_KnickKnackStoreSign::
	msgbox WindmistCity_Text_KnickKnackStoreSign, MSGBOX_SIGN
	end

WindmistCity_Text_KnickKnackStoreSign:
	.string "Windmist City Knick-knack Store\n"
	.string "Come here for all your… needs!$"

WindmistCity_EventScript_LumberjackRestStopSign::
	msgbox WindmistCity_Text_LumberjackRestStopSign, MSGBOX_SIGN
	end

WindmistCity_Text_LumberjackRestStopSign:
	.string "Lumberjack Rest Stop$"

WindmistCity_EventScript_Explorer::
	msgbox WindmistCity_Text_OhIveNeverSeenYouBefore, MSGBOX_NPC
	end

WindmistCity_Text_OhIveNeverSeenYouBefore:
	.string "Oh, I've never seen you before!\p"
	.string "It's not often we see new faces\n"
	.string "around here.\p"
	.string "…Especially with so few clothes\non!$"

WindmistCity_EventScript_Kindler::
	msgbox WindmistCity_Text_NinaIsGoodFriendsWithAria, MSGBOX_NPC
	end

WindmistCity_Text_NinaIsGoodFriendsWithAria:
	.string "Nina is good friends with the\n"
	.string "Nestpine Gym Leader, Aria.$"

WindmistCity_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM13, WindmistCity_EventScript_ThankYou
	msgbox WindmistCity_Text_BrrItsFreezingOutHere, MSGBOX_DEFAULT
	checkitem ITEM_RED_SCARF, 1
	compare VAR_RESULT, TRUE
	goto_if_eq WindmistCity_EventScript_OfferTradeForTM13
	release
	end

WindmistCity_EventScript_OfferTradeForTM13:
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox WindmistCity_Text_WhatsThatYouHaveARedScarf, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq WindmistCity_EventScript_DeclineTrade
	playfanfare MUS_FANFA4
	message WindmistCity_Text_PlayerTradedRedScarfForTM13
	waitfanfare
	removeitem ITEM_RED_SCARF, 1
	additem ITEM_TM13
	setflag FLAG_RECEIVED_TM13
	bufferitemnameplural 1, ITEM_TM13, 1
	bufferstdstring 2, STDSTRING_TMHMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	goto WindmistCity_EventScript_ThankYou
	end

WindmistCity_EventScript_ThankYou:
	msgbox WindmistCity_Text_ThanksImNiceAndWarmNow, MSGBOX_DEFAULT
	release
	end

WindmistCity_EventScript_DeclineTrade:
	msgbox WindmistCity_Text_Brr, MSGBOX_DEFAULT
	release
	end

WindmistCity_Text_BrrItsFreezingOutHere:
	.string "Brr…\n"
	.string "It's freezing out here.\p"
	.string "I want a Red Scarf…$"

WindmistCity_Text_WhatsThatYouHaveARedScarf:
	.string "What's that?\n"
	.string "You have a Red Scarf?\p"
	.string "Oh!\n"
	.string "Wanna trade it, for my TM?$"

WindmistCity_Text_PlayerTradedRedScarfForTM13:
	.string "{COLOR DARK_GREY}{PLAYER} traded the\n"
	.string "Red Scarf for TM13 Ice Beam!$"

WindmistCity_Text_ThanksImNiceAndWarmNow:
	.string "Thanks!\n"
	.string "I'm nice and warm now!$"

WindmistCity_Text_Brr:
	.string "Brr…$"

WindmistCity_EventScript_Abbie::
	lock
	faceplayer
	goto_if_set TRAINER_FLAGS_START + TRAINER_ABBIE, WindmistCity_EventScript_AbbiePostBattle
	msgbox WindmistCity_Text_ItsSoCold, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne WindmistCity_EventScript_DeclineAbbie
	msgbox WindmistCity_Text_LetsDoThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ABBIE, WindmistCity_Text_AbbieDefeat
	goto WindmistCity_EventScript_AbbiePostBattle
	end

WindmistCity_EventScript_DeclineAbbie:
	msgbox WindmistCity_Text_IceCold, MSGBOX_DEFAULT
	release
	end

WindmistCity_EventScript_AbbiePostBattle:
	msgbox WindmistCity_Text_AhhImWarmerNow, MSGBOX_DEFAULT
	release
	end

WindmistCity_Text_ItsSoCold:
	.string "I-it's so c-cold! W-wanna battle?\n"
	.string "That c-could get us heated up!$"

WindmistCity_Text_LetsDoThis:
	.string "L-let's do this!$"

WindmistCity_Text_AbbieDefeat:
	.string "Fiery fury!$"

WindmistCity_Text_IceCold:
	.string "Ice cold…$"

WindmistCity_Text_AhhImWarmerNow:
	.string "Ahh… I'm warmer now!\p"
	.string "A heated battle was just what the\n"
	.string "doctor ordered!$"

WindmistCity_EventScript_Hiker::
	lock
	faceplayer
	msgbox WindmistCity_Text_ICanSeeSoFar, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_Text_ICanSeeSoFar:
	.string "Whoa! I can see so far up here!\n"
	.string "It's kind of dizzying!$"

WindmistCity_EventScript_LockedDoor::
	lock
	faceplayer
	msgbox WindmistCity_Text_TheDoorIsLocked, MSGBOX_DEFAULT
	release
	end

WindmistCity_Text_TheDoorIsLocked:
	.string "{COLOR DARK_GREY}The door is locked…$"
