WindmistCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WindmistCity_OnTransition
	.byte 0

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

WindmistCity_EventScript_TimberGuildSign::
	msgbox WindmistCity_Text_TimberGuildSign, MSGBOX_SIGN
	end

WindmistCity_Text_TimberGuildSign:
	.string "Windmist Timber Guild$"
