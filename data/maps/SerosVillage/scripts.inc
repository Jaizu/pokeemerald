.equ LOCALID_REDWOOD, 4
.equ LOCALID_COULTER, 5
.equ LOCALID_DAYCARE_MAN, 6
.equ COULTERS_HOUSE_DOOR_X, 32
.equ COULTERS_HOUSE_DOOR_Y, 15

SerosVillage_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SerosVillage_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SerosVillage_OnFrame
	.byte 0

SerosVillage_OnTransition:
	setflag FLAG_VISITED_SEROS_VILLAGE
	end

SerosVillage_OnFrame:
	map_script_2 VAR_SEROS_VILLAGE_STATE, 0, SerosVillage_EventScript_WelcomeScene
	map_script_2 VAR_SEROS_VILLAGE_STATE, 2, SerosVillage_EventScript_DayCareManScene
	.2byte 0

SerosVillage_EventScript_WelcomeScene:
	lockall
	delay 10
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_REDWOOD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_REDWOOD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox SerosVillage_Text_AhYouMadeIt, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SerosVillage_Movement_PlayerWalkToProf
	waitmovement 0
	msgbox SerosVillage_Text_SoNoSignOfSecondTablet, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox SerosVillage_Text_ICouldAskMyParents, MSGBOX_DEFAULT
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox SerosVillage_Text_ThenItsSettled, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, SerosVillage_Movement_RedwoodExit
	delay 10
	applymovement LOCALID_COULTER, Common_Movement_WalkLeft
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox SerosVillage_Text_LooksLikeIWonTheRaceHere, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL2, 0
	applymovement LOCALID_COULTER, SerosVillage_Movement_CoulterWalkToParentsHouse
	waitmovement 0
	opendoor COULTERS_HOUSE_DOOR_X, COULTERS_HOUSE_DOOR_Y
	waitdooranim
	applymovement LOCALID_COULTER, SerosVillage_Movement_CoulterEnterParentsHouse
	waitmovement 0
	removeobject LOCALID_COULTER
	closedoor COULTERS_HOUSE_DOOR_X, COULTERS_HOUSE_DOOR_Y
	waitdooranim
	fadedefaultbgm
	removeobject LOCALID_REDWOOD
	setvar VAR_SEROS_VILLAGE_STATE, 1
	releaseall
	end

SerosVillage_Text_AhYouMadeIt:
	.string "Redwood: {COLOR BLUE}Ah, you made it!\n"
	.string "Welcome to Seros Village!$"

SerosVillage_Text_SoNoSignOfSecondTablet:
	.string "Redwood: {COLOR BLUE}So! No sign of a second\n"
	.string "Tablet in there, then?\p"
	.string "Hmm…\n"
	.string "Well, my tools are never wrong!\p"
	.string "Perhaps there's a {COLOR GREEN}another\n"
	.string "entrance to the Tunnel{COLOR BLUE}?$"

SerosVillage_Text_ICouldAskMyParents:
	.string "{RIVAL}: {COLOR BLUE}I could ask my parents\n"
	.string "about a second entrance!$"

SerosVillage_Text_ThenItsSettled:
	.string "Redwood: {COLOR BLUE}Then it's settled!\p"
	.string "I'll go to the Pokémon Center, and\n"
	.string "ask there. Good luck, you two!$"

SerosVillage_Text_LooksLikeIWonTheRaceHere:
	.string "{RIVAL}: {COLOR BLUE}Looks like I won the\n"
	.string "race here, at least!\p"
	.string "I hope you're looking forward to\n"
	.string "our next battle.\p"
	.string "You're a pretty good Trainer, all\n"
	.string "things considered!\p"
	.string "…Hey, maybe you should try out\n"
	.string "the Gym!\p"
	.string "The Gym Leader's {COLOR GREEN}Fernando{COLOR BLUE}.\n"
	.string "He uses {COLOR GREEN}Fairy-type{COLOR BLUE} Pokémon!\p"
	.string "Mull it over, eh {PLAYER}?\n"
	.string "Seeya!$"

SerosVillage_Movement_PlayerWalkToProf:
	walk_down
	walk_down
	step_end

SerosVillage_Movement_RedwoodExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

SerosVillage_Movement_CoulterWalkToParentsHouse:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

SerosVillage_Movement_CoulterEnterParentsHouse:
	walk_up
	set_invisible
	step_end

SerosVillage_EventScript_DayCareManScene:
	lockall
	addobject LOCALID_DAYCARE_MAN
	setobjectxy LOCALID_DAYCARE_MAN, 14, 16
	msgbox SerosVillage_Text_ExcuseMe, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement LOCALID_DAYCARE_MAN, SerosVillage_Movement_EnterDayCareMan
	waitmovement 0
	msgbox SerosVillage_Text_SorryToBotherYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DAYCARE_MAN, SerosVillage_Movement_ExitDayCareMan
	waitmovement 0
	setobjectxy LOCALID_DAYCARE_MAN, 7, 15
	setobjectmovementtype LOCALID_DAYCARE_MAN, MOVEMENT_TYPE_FACE_DOWN
	setflag FLAG_HIDE_SEROS_PATH_BATTLING_TRAINERS
	setvar VAR_SEROS_VILLAGE_STATE, 3
	releaseall
	end

SerosVillage_Text_ExcuseMe:
	.string "???: {COLOR BLUE}Excuse me!$"

SerosVillage_Text_SorryToBotherYou:
	.string "Day-Care Man: {COLOR BLUE}Sorry to bother\n"
	.string "you, but…\p"
	.string "Are you the Trainer that just\n"
	.string "defeated Fernando?\p"
	.string "He's my grandson, and he seems to\n"
	.string "be in… quite the state.\p"
	.string "He ran off to {COLOR GREEN}Wisp Forest{COLOR BLUE}, but\n"
	.string "he has no Pokémon with him.\p"
	.string "Would you do me a kindness, and\n"
	.string "chase after him?\p"
	.string "I couldn't bear to see him get\n"
	.string "harmed.\p"
	.string "…\p"
	.string "Oh, thank you!\p"
	.string "Wisp Forest is to the west of the\n"
	.string "village.\p"
	.string "Just {COLOR GREEN}follow Seros Path{COLOR BLUE}, you\n"
	.string "can't miss it.\p"
	.string "Thank you, Trainer!$"

SerosVillage_Movement_EnterDayCareMan:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SerosVillage_Movement_ExitDayCareMan:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SerosVillage_EventScript_TownSign::
	msgbox SerosVillage_Text_TownSign, MSGBOX_SIGN
	end

SerosVillage_Text_TownSign:
	.string "Seros Village\n"
	.string "The Flowery Heart of Orbtus!$"

SerosVillage_EventScript_GymSign::
	msgbox SerosVillage_Text_GymSign, MSGBOX_SIGN
	end

SerosVillage_Text_GymSign:
	.string "Seros Village Pokémon Gym\p"
	.string "Leader: Fernando\n"
	.string "“The Young Fairy-type Trainer!”$"

SerosVillage_EventScript_DayCareSign::
	msgbox SerosVillage_Text_DayCareSign, MSGBOX_SIGN
	end

SerosVillage_Text_DayCareSign:
	.string "Seros Village Day-Care Center\n"
	.string "“Let us raise your Pokémon!”$"

SerosVillage_EventScript_CoultersHouseSign::
	msgbox SerosVillage_Text_RivalsHouseSign, MSGBOX_SIGN
	end

SerosVillage_Text_RivalsHouseSign:
	.string "{RIVAL}'s house$"

SerosVillage_EventScript_AceTrainerF::
	msgbox SerosVillage_Text_HowStrange, MSGBOX_NPC
	end

SerosVillage_Text_HowStrange:
	.string "How strange…\p"
	.string "I left two of my Pokémon at the\n"
	.string "Day-Care Center.\p"
	.string "Next thing I knew, Fernando's\n"
	.string "grandpa was giving me an Egg!$"

SerosVillage_EventScript_AromaLady::
	msgbox SerosVillage_Text_ThereAreLotsOfFlowersAround, MSGBOX_NPC
	end

SerosVillage_Text_ThereAreLotsOfFlowersAround:
	.string "There are lots of flowers around\n"
	.string "these parts.\p"
	.string "When the wind is in the right\n"
	.string "direction, the whole village\l"
	.string "smells of perfume!\p"
	.string "It's why this is my favorite place\n"
	.string "in all of Orbtus.$"

SerosVillage_EventScript_Picnicker::
	msgbox SerosVillage_Text_SoManyColorfulFlabebe, MSGBOX_NPC
	end

SerosVillage_Text_SoManyColorfulFlabebe:
	.string "So many colorful Flabébé live in\n"
	.string "the flowers along the Seros Path!\p"
	.string "I want to try and catch all of\n"
	.string "them.$"

SerosVillage_EventScript_DaycareMan:: @ 8291C18
	lock
	faceplayer
	call_if_set FLAG_FERNANDO_STORMED_OFF, SerosVillage_EventScript_CheckIfFernandoIsBack
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_EGG_WAITING
	goto_if_eq SerosVillage_EventScript_DaycareEggWaiting
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq SerosVillage_EventScript_CheckOnOneMon
	compare VAR_RESULT, DAYCARE_TWO_MONS
	goto_if_eq SerosVillage_EventScript_CheckOnTwoMons
	msgbox SerosVillage_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

SerosVillage_EventScript_CheckIfFernandoIsBack:
	goto_if_unset FLAG_FERNANDO_RESCUED, SerosVillage_EventScript_PleaseHelpFernando
	return

SerosVillage_EventScript_PleaseHelpFernando:
	msgbox SerosVillage_Text_PleaseHelpFernando, MSGBOX_DEFAULT
	release
	end

SerosVillage_EventScript_DaycareEggWaiting::
	msgbox SerosVillage_Text_DoYouWantEgg, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_EventScript_DaycareAcceptEgg
	msgbox SerosVillage_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_EventScript_DaycareAcceptEgg
	msgbox SerosVillage_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

SerosVillage_EventScript_DaycareAcceptEgg::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	compare VAR_RESULT, PARTY_SIZE
	goto_if_ne SerosVillage_EventScript_DaycareReceiveEgg
	msgbox SerosVillage_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

SerosVillage_EventScript_DaycareReceiveEgg::
	message SerosVillage_Text_ReceivedEgg
	playfanfare MUS_FANFA1
	waitfanfare
	waitbuttonpress
	msgbox SerosVillage_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag FLAG_PENDING_DAYCARE_EGG
	release
	end

SerosVillage_EventScript_CheckMonReceivedMail::
	specialvar VAR_RESULT, CheckDaycareMonReceivedMail
	compare VAR_RESULT, 1
	call_if_eq SerosVillage_EventScript_MonReceivedMail
	return

SerosVillage_EventScript_MonReceivedMail::
	msgbox SerosVillage_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

SerosVillage_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox SerosVillage_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call SerosVillage_EventScript_CheckMonReceivedMail
	release
	end

SerosVillage_EventScript_CheckOnTwoMons::
	special GetDaycareMonNicknames
	msgbox SerosVillage_Text_YourMonsAreDoingFine, MSGBOX_DEFAULT
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call SerosVillage_EventScript_CheckMonReceivedMail
	setvar VAR_0x8004, 1
	call SerosVillage_EventScript_CheckMonReceivedMail
	release
	end

SerosVillage_Text_PleaseHelpFernando:
	.string "Wisp Forest is to the west of the\n"
	.string "village.\p"
	.string "Just {COLOR GREEN}follow Seros Path{COLOR BLUE}, you\n"
	.string "can't miss it.\p"
	.string "Thank you, Trainer!$"

SerosVillage_Text_SeeWifeIfYoudLikeMeToRaiseMon:
	.string "I'm the Day-Care Man.\p"
	.string "I help take care of the precious\n"
	.string "Pokémon of Trainers.\p"
	.string "If you'd like me to raise your Pokémon,\n"
	.string "have a word with my wife.$"

SerosVillage_Text_DoYouWantEgg:
	.string "Ah, it's you!\p"
	.string "We were raising your Pokémon,\n"
	.string "and my goodness, were we surprised!\p"
	.string "Your Pokémon had an Egg!\p"
	.string "We don't know how it got there,\n"
	.string "but your Pokémon had it.\p"
	.string "You do want it, yes?$"

SerosVillage_Text_YourMonIsDoingFine: @ 8292114
	.string "Ah, it's you! Good to see you.\n"
	.string "Your {STR_VAR_1}'s doing fine.$"

SerosVillage_Text_IllKeepIt: @ 8292149
	.string "Well then, I'll keep it.\n"
	.string "Thanks!$"

SerosVillage_Text_YouHaveNoRoomForIt: @ 829216A
	.string "You have no room for it…\n"
	.string "Come back when you've made room.$"

SerosVillage_Text_ReceivedEgg: @ 82921A4
	.string "{PLAYER} received the Egg from\n"
	.string "the Day-Care Man.$"

SerosVillage_Text_TakeGoodCareOfIt: @ 82921CF
	.string "Take good care of it.$"

SerosVillage_Text_FriendlyWithOtherTrainersMon: @ 82921E5
	.string "By the way, about your {STR_VAR_1},\n"
	.string "it seemed to be friendly with\l"
	.string "{STR_VAR_2}'s {STR_VAR_3}.\p"
	.string "I may even have seen it receiving\n"
	.string "a piece of Mail.$"

SerosVillage_Text_YourMonsAreDoingFine: @ 8292299
	.string "Ah, it's you! Your {STR_VAR_1} and\n"
	.string "{STR_VAR_2} are doing fine.$"

SerosVillage_Text_IWillKeepDoYouWantIt: @ 82922C6
	.string "I really will keep it.\n"
	.string "You do want this, yes?$"
