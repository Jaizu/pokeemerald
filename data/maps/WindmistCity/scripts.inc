.set LOCALID_REDWOOD, 11

WindmistCity_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, WindmistCity_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, WindmistCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, WindmistCity_OnFrame
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
	call_if_set FLAG_WHITEOUT_TO_WINDMIST, WindmistCity_EventScript_ClearWindmistWhiteOut
	compare VAR_WINDMIST_CITY_STATE, 1
	call_if_eq WindmistCity_EventScript_CheckSetRedwoodPos
	compare VAR_WINDMIST_CITY_STATE, 1
	call_if_eq WindmistCity_EventScript_HideMapNamePopup
	end

WindmistCity_EventScript_ClearCelantoGroveRoadblock:
	setvar VAR_CELANTO_GROVE_STATE, 1
	return

WindmistCity_EventScript_ClearWindmistWhiteOut:
	clearflag FLAG_WHITEOUT_TO_WINDMIST
	return

WindmistCity_EventScript_CheckSetRedwoodPos:
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 15
	goto_if_eq WindmistCity_EventScript_SetRedwoodPos
	return

WindmistCity_EventScript_SetRedwoodPos:
	setobjectxyperm LOCALID_REDWOOD, 23, 6
	return

WindmistCity_EventScript_HideMapNamePopup:
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

WindmistCity_OnFrame:
	map_script_2 VAR_WINDMIST_CITY_STATE, 1, WindmistCity_EventScript_RedwoodMeeting
	.2byte 0

WindmistCity_EventScript_RedwoodMeeting::
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	compare VAR_0x8008, 15
	call_if_eq WindmistCity_EventScript_RedwoodWalkFromKnickKnackStore
	compare VAR_0x8008, 15
	call_if_ne WindmistCity_EventScript_RedwoodNoticePlayer
	delay 20
	msgbox WindmistCity_Text_ISeeYouveAlsoWonNinasBadge, MSGBOX_DEFAULT
	fadedefaultbgm
	giveitem ITEM_BIKE_VOUCHER
	msgbox WindmistCity_Text_DoYouWantToComeWithMe, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq WindmistCity_EventScript_WarpToAerousPort
	msgbox WindmistCity_Text_WellThatsFineToo, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8008, VAR_0x8009
	compare VAR_0x8008, 15
	call_if_eq WindmistCity_EventScript_ExitRedwoodFromPokemonCenter
	compare VAR_0x8008, 15
	call_if_ne WindmistCity_EventScript_ExitRedwoodFromGym
	removeobject LOCALID_REDWOOD
	setvar VAR_AEROUS_CITY_STATE, 2
	setvar VAR_WINDMIST_CITY_STATE, 2
	releaseall
	end

WindmistCity_EventScript_WarpToAerousPort:
	msgbox WindmistCity_Text_GreatLetsLeave, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_AEROUS_CITY_REDWOOD
	setvar VAR_AEROUS_CITY_STATE, 1
	setflag FLAG_HIDE_WINDMIST_CITY_REDWOOD
	setvar VAR_WINDMIST_CITY_STATE, 2
	warp MAP_AEROUS_CITY, -1, 28, 33
	waitstate
	releaseall
	end

WindmistCity_EventScript_RedwoodWalkFromKnickKnackStore:
	msgbox WindmistCity_Text_Player, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	playbgm MUS_RG_OHKIDO, 0
	applymovement LOCALID_REDWOOD, WindmistCity_Movement_RedwoodWalkToPlayerFromKnickKnackStore
	waitmovement 0
	return

WindmistCity_EventScript_RedwoodNoticePlayer:
	delay 10
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_REDWOOD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_REDWOOD, Common_Movement_Delay48
	waitmovement 0
	msgbox WindmistCity_Text_Player, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playbgm MUS_RG_OHKIDO, 0
	applymovement LOCALID_REDWOOD, WindmistCity_Movement_RedwoodWalkToPlayerFromGym
	waitmovement 0
	return

WindmistCity_EventScript_ExitRedwoodFromPokemonCenter:
	applymovement LOCALID_REDWOOD, WindmistCity_Movement_ExitRedwoodFromPokemonCenter
	waitmovement 0
	return

WindmistCity_EventScript_ExitRedwoodFromGym:
	applymovement LOCALID_REDWOOD, WindmistCity_Movement_ExitRedwoodFromGym
	waitmovement 0
	return

WindmistCity_Text_Player:
	.string "Redwood: {COLOR BLUE}{PLAYER}!$"

WindmistCity_Text_ISeeYouveAlsoWonNinasBadge:
	.string "Redwood: {COLOR BLUE}I see you've also\n"
	.string "won Nina's Badge.\p"
	.string "{RIVAL} won his, and now he's\n"
	.string "headed to {COLOR GREEN}Sabulo Island{COLOR BLUE}.\p"
	.string "I finally got the machine part I\n"
	.string "needed.\p"
	.string "That means I'll be able to revive\n"
	.string "{COLOR GREEN}Fossil Pokémon{COLOR BLUE} using the machine at\l"
	.string "my home again!\p"
	.string "You and {RIVAL} are free to\n"
	.string "use it, too, of course.\p"
	.string "Speaking of {RIVAL}, I gave him\n"
	.string "one of these. Here's yours!$"

WindmistCity_Text_DoYouWantToComeWithMe:
	.string "Redwood: {COLOR BLUE}You can redeem that for a\n"
	.string "Bicycle in Aerous City.\p"
	.string "I'm headed back there now, myself.\n"
	.string "Do you want to come with me?$"

WindmistCity_Text_GreatLetsLeave:
	.string "Redwood: {COLOR BLUE}Great, let's leave!$"

WindmistCity_Text_WellThatsFineToo:
	.string "Redwood: {COLOR BLUE}Well, that's fine too.\p"
	.string "After all, you've got your\n"
	.string "Town Map if you get lost.\p"
	.string "Now, I'm going to head home and\n"
	.string "study that book you found.\p"
	.string "Perhaps it will have some answers!\n"
	.string "See you around, {PLAYER}!$"

WindmistCity_Movement_RedwoodWalkToPlayerFromKnickKnackStore:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

WindmistCity_Movement_RedwoodWalkToPlayerFromGym:
	walk_right
	walk_right
	step_end

WindmistCity_Movement_ExitRedwoodFromPokemonCenter:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

WindmistCity_Movement_ExitRedwoodFromGym:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_slow_diag_southwest
	walk_left
	step_end

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
