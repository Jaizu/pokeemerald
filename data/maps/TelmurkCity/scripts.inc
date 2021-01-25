TelmurkCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TelmurkCity_OnTransition
	.byte 0

TelmurkCity_OnTransition::
	setflag FLAG_VISITED_TELMURK_CITY
	end
