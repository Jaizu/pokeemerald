.equ LOCALID_MUSEUM_CLERK, 3

AerousCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AerousCity_OnTransition
	.byte 0

AerousCity_OnTransition::
	setflag FLAG_VISITED_AEROUS_CITY
	end

AerousCity_EventScript_CitySign::
	msgbox AerousCity_Text_CitySign, MSGBOX_SIGN
	end

AerousCity_Text_CitySign:
	.string "Aerous City\n"
	.string "The Cultural Capital City.$"

AerousCity_EventScript_MuseumSign::
	msgbox AerousCity_Text_MuseumSign, MSGBOX_SIGN
	end

AerousCity_Text_MuseumSign:
	.string "Aerous City Museum$"

AerousCity_EventScript_ArtClubSign::
	msgbox AerousCity_Text_ArtClubSign, MSGBOX_SIGN
	end

AerousCity_Text_ArtClubSign:
	.string "Aerous Art Club\n"
    .string "“Check out the upstairs café!”$"

AerousCity_EventScript_PortSign::
	msgbox AerousCity_Text_PortSign, MSGBOX_SIGN
	end

AerousCity_Text_PortSign:
	.string "{DOWN_ARROW} Aerous City port$"

AerousCity_EventScript_BikeShopSign::
	msgbox AerousCity_Text_BikeShopSign, MSGBOX_SIGN
	end

AerousCity_Text_BikeShopSign:
	.string "Bicycle shop$"

AerousCity_EventScript_NameRaterSign::
	msgbox AerousCity_Text_NameRaterSign, MSGBOX_SIGN
	end

AerousCity_Text_NameRaterSign:
	.string "The Name Rater's house$"

AerousCity_EventScript_MuseumClerk::
	lock
	faceplayer
	msgbox AerousCity_Text_TheAerousMuseumIsHavingAnExhibit, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MUSEUM_CLERK, AerousCity_Text_MuseumClerkDefeat
	msgbox AerousCity_Text_IGottaTellTheBoss, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MUSEUM_CLERK, Common_Movement_WalkUp
	waitmovement 0
	playse SE_KAIDAN
	waitse
	removeobject LOCALID_MUSEUM_CLERK
	release
	end

AerousCity_Text_TheAerousMuseumIsHavingAnExhibit:
	.string "{COLOR DARK_GREY}???: {COLOR BLUE}The Aerous Museum is… er…\p"
	.string "Having an exhibit!\n"
	.string "Yeah…\p"
	.string "…You don't believe me?\n"
	.string "Argh, you're a belligerent child!\p"
	.string "I'll make you pay!{PLAY_BGM}{MUS_MGM0}$"

AerousCity_Text_MuseumClerkDefeat:
	.string "Oh man…\n"
	.string "This isn't good!$"

AerousCity_Text_IGottaTellTheBoss:
	.string "{COLOR DARK_GREY}???: {COLOR BLUE}This is bad…\n"
	.string "I gotta tell the boss!$"
