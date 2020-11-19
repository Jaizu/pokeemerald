SabuloIsland_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SabuloIsland_OnTransition
	.byte 0

SabuloIsland_OnTransition::
	setflag FLAG_VISITED_SABULO_ISLAND
	end
