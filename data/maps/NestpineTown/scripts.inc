NestpineTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NestpineTown_OnTransition
	.byte 0

NestpineTown_OnTransition::
	setflag FLAG_VISITED_NESTPINE_TOWN
	end
