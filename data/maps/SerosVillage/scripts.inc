.equ LOCALID_REDWOOD, 4
.equ LOCALID_COULTER, 5
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

SerosVillage_EventScript_DayCareMan::
	lock
	faceplayer
	// TODO: Implement the Day-Care Man's script
	release
	end

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
