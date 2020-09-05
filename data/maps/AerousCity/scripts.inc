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
