.equ LOCALID_MOM, 1

CelantoTown_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CelantoTown_PlayersHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CelantoTown_PlayersHouse_1F_OnFrame
	.byte 0

CelantoTown_PlayersHouse_1F_OnLoad:
	compare VAR_PLAYERS_HOUSE_STATE, 4
	call_if_lt CelantoTown_PlayersHouse_1F_EventScript_LockDoor
	end

CelantoTown_PlayersHouse_1F_EventScript_LockDoor::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_LockedDoor, 0
	return

CelantoTown_PlayersHouse_1F_OnFrame::
	map_script_2 VAR_PLAYERS_HOUSE_STATE, 1, CelantoTown_PlayersHouse_1F_EventScript_DeliverLetterScene
	.2byte 0

CelantoTown_PlayersHouse_1F_EventScript_DeliverLetterScene::
	lockall
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOM, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_PlayersHouse_1F_Text_OhHiPlayer, MSGBOX_AUTOCLOSE
	applymovement LOCALID_MOM, CelantoTown_PlayersHouse_1F_Movement_MomApproachPlayer
	waitmovement 0
	msgbox CelantoTown_PlayersHouse_1F_Text_WeGotThisLetter, MSGBOX_AUTOCLOSE
	additem ITEM_LETTER
	// TODO: Implement Letter display special
	// special nullsub_37
	// waitstate
	msgbox CelantoTown_PlayersHouse_1F_Text_SoMeetAtReliquia
	goto_if_unset FLAG_HIDE_DUSTY_TOME, CelantoTown_PlayersHouse_1F_EventScript_GoGetTheBook
	msgbox CelantoTown_PlayersHouse_1F_Text_HowStrange
	call CelantoTown_PlayersHouse_1F_EventScript_GiveRunningShoes
	applymovement LOCALID_MOM, CelantoTown_PlayersHouse_1F_Movement_MomReturnToTable
	waitmovement 0
	releaseall
	end

CelantoTown_PlayersHouse_1F_EventScript_GoGetTheBook:
	msgbox CelantoTown_PlayersHouse_1F_Text_MaybeYouShouldGetIt, MSGBOX_AUTOCLOSE
	applymovement LOCALID_MOM, CelantoTown_PlayersHouse_1F_Movement_MomReturnToTable
	waitmovement 0	
	setvar VAR_PLAYERS_HOUSE_STATE, 2
	releaseall
	end

CelantoTown_PlayersHouse_1F_Text_OhHiPlayer:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}Oh!\n"
	.string "Hi, {PLAYER}!$"

CelantoTown_PlayersHouse_1F_Movement_MomApproachPlayer:
	walk_up
	walk_up
	walk_right
	step_end

CelantoTown_PlayersHouse_1F_Text_WeGotThisLetter:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}We got this {COLOR GREEN}Letter{COLOR RED} in\n"
	.string "the mail.\p"
	.string "It's addressed to you!\n"
	.string "Here, read it.$"

CelantoTown_PlayersHouse_1F_Text_SoMeetAtReliquia:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}So, they want to meet at\n"
	.string "the {COLOR GREEN}Reliquia Ruins{COLOR RED}?\p"
	.string "And they mentioned that book you\n"
	.string "have, from the Library?$"

CelantoTown_PlayersHouse_1F_Text_HowStrange:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}How strange.\p"
	.string "I suppose you shouldn't keep them\n"
	.string "waiting, though!$"

CelantoTown_PlayersHouse_1F_Movement_MomReturnToTable:
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_left
	step_end

CelantoTown_PlayersHouse_1F_Text_MaybeYouShouldGetIt:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}Maybe you should get it from\n"
	.string "upstairs, and bring it with you.$"

CelantoTown_PlayersHouse_1F_EventScript_GiveRunningShoesTrigger::
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOM, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_PlayersHouse_1F_Text_OhPlayer, MSGBOX_AUTOCLOSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	applymovement LOCALID_MOM, CelantoTown_PlayersHouse_1F_Movement_MomWalkToExit
	waitmovement 0
	call CelantoTown_PlayersHouse_1F_EventScript_GiveRunningShoes
	applymovement LOCALID_MOM, CelantoTown_PlayersHouse_1F_Movement_MomWalkFromExitToTable
	waitmovement 0
	releaseall
	end

CelantoTown_PlayersHouse_1F_Movement_MomWalkToExit:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end

CelantoTown_PlayersHouse_1F_Movement_MomWalkFromExitToTable:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_fastest_left
	step_end

CelantoTown_PlayersHouse_1F_EventScript_GiveRunningShoes::
	msgbox CelantoTown_PlayersHouse_1F_Text_OhIJustRemembered
	playfanfare MUS_FANFA4
	message CelantoTown_PlayersHouse_1F_Text_SwitchShoesWithRunningShoes
	waitfanfare
	setflag FLAG_SYS_B_DASH
	waitmessage
	delay 30
	msgbox CelantoTown_PlayersHouse_1F_Text_ExplainRunningShoes, MSGBOX_AUTOCLOSE
	setvar VAR_PLAYERS_HOUSE_STATE, 4
	setmetatile 3, 7, METATILE_Indoors_UnlockedDoor, 0
	special DrawWholeMapView
	return

CelantoTown_PlayersHouse_1F_Text_OhPlayer:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}Oh, {PLAYER}!$"

CelantoTown_PlayersHouse_1F_Text_OhIJustRemembered:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}I just remembered!\p"
	.string "These {COLOR GREEN}Running Shoes{COLOR RED} came in the\n"
	.string "mail, too! Go ahead, try them on.$"

CelantoTown_PlayersHouse_1F_Text_SwitchShoesWithRunningShoes:
	.string "{COLOR DARK_GREY}{PLAYER} switched shoes with the\n"
	.string "Running Shoes. A perfect fit!$"

CelantoTown_PlayersHouse_1F_Text_ExplainRunningShoes:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}You know how to use them,\n"
	.string "right? Just hold down the B Button!\p"
	.string "Now, you be careful out there.\n"
	.string "I love you!$"

CelantoTown_PlayersHouse_1F_EventScript_GetTheBookTrigger::
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOM, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_PlayersHouse_1F_Text_OhPlayer, MSGBOX_AUTOCLOSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox CelantoTown_PlayersHouse_1F_Text_GetTheBookFirst, MSGBOX_AUTOCLOSE
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	end

CelantoTown_PlayersHouse_1F_Text_GetTheBookFirst:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}Don't forget to get your\n"
	.string "book, from upstairs, first!$"

CelantoTown_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	compare VAR_PLAYERS_HOUSE_STATE, 4
	call_if_eq CelantoTown_PlayersHouse_1F_EventScript_MomAfterGivenRunningShoes
	compare VAR_PLAYERS_HOUSE_STATE, 3
	call_if_eq CelantoTown_PlayersHouse_1F_EventScript_GiveRunningShoes
	compare VAR_PLAYERS_HOUSE_STATE, 2
	call_if_eq CelantoTown_PlayersHouse_1F_EventScript_MomGoGetBook
	applymovement LOCALID_MOM, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CelantoTown_PlayersHouse_1F_EventScript_MomAfterGivenRunningShoes:
	compare VAR_CELANTO_TOWN_STATE, 2
	goto_if_ge CelantoTown_PlayersHouse_1F_EventScript_MomHaveYouCheckedLibrary
	msgbox CelantoTown_PlayersHouse_1F_Text_ThoseRunningShoesShouldHelp
	return

CelantoTown_PlayersHouse_1F_Text_ThoseRunningShoesShouldHelp:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}Those Running Shoes should\n"
	.string "help you get there faster!\p"
	.string "The Letter asked to meet at the\n"
	.string "{COLOR GREEN}Reliquia Ruins{COLOR RED}, right?\p"
	.string "Well, make sure you stay safe!\n"
	.string "I love you, {PLAYER}!$"

CelantoTown_PlayersHouse_1F_EventScript_MomHaveYouCheckedLibrary:
	msgbox CelantoTown_PlayersHouse_1F_Text_HaveYouCheckLibrary
	return

CelantoTown_PlayersHouse_1F_Text_HaveYouCheckLibrary:
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}Have you checked out\n"
	.string "the {COLOR GREEN}Celanto Library{COLOR RED} yet?\p"
	.string "Prof. Redwood is giving out\n"
	.string "Pokémon to Trainers there!\p"
	.string "Isn't that exciting?\n"
	.string "You should go see him.$"

CelantoTown_PlayersHouse_1F_EventScript_MomGoGetBook:
	msgbox CelantoTown_PlayersHouse_1F_Text_GetTheBookFirst
	return
