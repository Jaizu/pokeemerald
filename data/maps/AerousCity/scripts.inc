AerousCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AerousCity_OnTransition
	.byte 0

AerousCity_OnTransition::
	setflag FLAG_VISITED_AEROUS_CITY
	end
