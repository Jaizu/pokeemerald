.equ LOCALID_REDWOOD, 1
.equ LOCALID_COULTER, 2

ArchanTown_RedwoodResidence_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArchanTown_RedwoodResidence_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ArchanTown_RedwoodResidence_OnFrame
	.byte 0

ArchanTown_RedwoodResidence_OnTransition::
	compare VAR_REDWOOD_RESIDENCE_STATE, 0
	call_if_eq ArchanTown_RedwoodResidence_EventScript_MoveRedwood
	end

ArchanTown_RedwoodResidence_OnFrame:
	map_script_2 VAR_ARCHAN_TOWN_STATE, 0, ArchanTown_RedwoodResidence_EventScript_CarePackageScene
	.2byte 0

ArchanTown_RedwoodResidence_EventScript_MoveRedwood:
	setobjectxyperm LOCALID_REDWOOD, 7, 5
	setobjectmovementtype LOCALID_REDWOOD, MOVEMENT_TYPE_FACE_DOWN
	return	

ArchanTown_RedwoodResidence_EventScript_CarePackageScene:
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	msgbox ArchanTown_RedwoodResidence_Text_AhPlayer, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 10
	playfanfare MUS_OBTAIN_ITEM
	message ArchanTown_RedwoodResidence_Text_ObtainedTheCarePackage
	waitfanfare
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox ArchanTown_RedwoodResidence_Text_AndYoursRival, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 10
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox ArchanTown_RedwoodResidence_Text_OpenedItUp, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message ArchanTown_RedwoodResidence_Text_ObtainedTheOrbtusPokedex
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	waitfanfare
	msgbox ArchanTown_RedwoodResidence_Text_PlayerPutPokedexInBag, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message ArchanTown_RedwoodResidence_Text_ObtainedTheRedwoodCardAndMap
	additem ITEM_REDWOOD_CARD
	additem ITEM_TOWN_MAP
	waitfanfare
	msgbox ArchanTown_RedwoodResidence_Text_PlayerPutCardAndMapInBag, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message ArchanTown_RedwoodResidence_Text_ObtainedThePokeBallsAndPotions
	additem ITEM_POKE_BALL, 10
	additem ITEM_POTION, 5
	waitfanfare
	msgbox ArchanTown_RedwoodResidence_Text_PlayerPutPokeBallsAndPotionsInBag, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox ArchanTown_RedwoodResidence_Text_QuiteTheSetOfGear, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setflag FLAG_DONT_TRANSITION_MUSIC
	setflag FLAG_DONT_CLEAR_SAVED_MUSIC
	playbgm MUS_FOLLOW_ME, 0
	savebgm MUS_FOLLOW_ME
	applymovement LOCALID_REDWOOD, ArchanTown_RedwoodResidence_Movement_ExitRedwood
	waitmovement 0	
	playse SE_EXIT
	waitse
	removeobject LOCALID_REDWOOD
	applymovement LOCALID_COULTER, ArchanTown_RedwoodResidence_Movement_ExitCoulter
	applymovement OBJ_EVENT_ID_PLAYER, ArchanTown_RedwoodResidence_Movement_ExitPlayer
	delay 50
	playse SE_EXIT
	waitse
	removeobject LOCALID_COULTER
	waitmovement 0
	clearflag FLAG_HIDE_ARCHAN_TOWN_REDWOOD
	clearflag FLAG_HIDE_ARCHAN_TOWN_COULTER
	setvar VAR_ARCHAN_TOWN_STATE, 1
	setvar VAR_REDWOOD_RESIDENCE_STATE, 1
	warp MAP_ARCHAN_TOWN, 2, 0, 0
	waitstate
	releaseall
	end

ArchanTown_RedwoodResidence_Text_AhPlayer:
	.string "Redwood: {COLOR BLUE}Ah, {PLAYER}!\n"
	.string "You made it!\p"
	.string "I was just explaining to\n"
	.string "{RIVAL}.\p"
	.string "To be effective helpers, you two\n"
	.string "will need the right gear!\p"
	.string "So, to get you started, I made you\n"
	.string "these {COLOR GREEN}Care Packages{COLOR BLUE}!\p"
	.string "Take yours, {PLAYER}!$"

ArchanTown_RedwoodResidence_Text_ObtainedTheCarePackage:
	.string "Obtained the Care Package!$"

ArchanTown_RedwoodResidence_Text_AndYoursRival:
	.string "Redwood: {COLOR BLUE}And yours,\n"
	.string "{RIVAL}!$"

ArchanTown_RedwoodResidence_Text_OpenedItUp:
	.string "{PLAYER} opened up\n"
	.string "Prof. Redwood's Care Package…$"

ArchanTown_RedwoodResidence_Text_ObtainedTheOrbtusPokedex:
	.string "Obtained the Orbtus Pokédex!$"

ArchanTown_RedwoodResidence_Text_PlayerPutPokedexInBag:
	.string "{PLAYER} put away the Pokédex\n"
	.string "in the Bag.$"

ArchanTown_RedwoodResidence_Text_ObtainedTheRedwoodCardAndMap:
	.string "Obtained the Redwood Card\n"
	.string "and the Orbtus Town Map!$"

ArchanTown_RedwoodResidence_Text_PlayerPutCardAndMapInBag:
	.string "{PLAYER} put them away\n"
	.string "in the Key Items Pocket.$"

ArchanTown_RedwoodResidence_Text_ObtainedThePokeBallsAndPotions:
	.string "Obtained 10 Poké Balls\n"
	.string "and 5 Potions!$"

ArchanTown_RedwoodResidence_Text_PlayerPutPokeBallsAndPotionsInBag:
	.string "{PLAYER} put away the Poké Balls\n"
	.string "in the Poké Balls Pocket.\p"
	.string "{PLAYER} put away the Potions\n"
	.string "in the Items Pocket.$"

ArchanTown_RedwoodResidence_Text_QuiteTheSetOfGear:
	.string "Redwood: {COLOR BLUE}Quite the set of\n"
	.string "gear, no?\p"
	.string "The {COLOR GREEN}Orbtus Pokédex{COLOR BLUE} records data on\n"
	.string "Pokémon you capture.\p"
	.string "The {COLOR GREEN}Town Map{COLOR BLUE} is a map of the\n"
	.string "Orbtus region!\p"
	.string "It's handy for navigation.\p"
	.string "The {COLOR GREEN}Redwood Card{COLOR BLUE} officially makes\n"
	.string "you members of my research team.\p"
	.string "It's recognized in many circles,\n"
	.string "so it's very useful! Don't lose it!\p"
	.string "And, of course, you can buy more\n"
	.string "Poké Balls and Potions at Marts.\p"
	.string "Now, onto the matter at hand!\p"
	.string "I should probably tell you what it\n"
	.string "is I am researching!\p"
	.string "But, it's better to show you.\n"
	.string "Follow me!$"

ArchanTown_RedwoodResidence_Movement_ExitRedwood:
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_fastest_down
	step_end

ArchanTown_RedwoodResidence_Movement_ExitCoulter:
	walk_down
	walk_down
	walk_left
	walk_in_place_fastest_down
	step_end

ArchanTown_RedwoodResidence_Movement_ExitPlayer:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end

ArchanTown_RedwoodResidence_Redwood::
	lock
	faceplayer
	release
	end
