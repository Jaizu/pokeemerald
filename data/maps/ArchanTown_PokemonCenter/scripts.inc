ArchanTown_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArchanTown_PokemonCenter_OnTransition
	.byte 0

ArchanTown_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_ARCHAN_TOWN
	end

ArchanTown_PokemonCenter_EventScript_Camper::
	msgbox ArchanTown_PokemonCenter_Text_HiddenGrottoRumors, MSGBOX_NPC
	end

ArchanTown_PokemonCenter_Text_HiddenGrottoRumors:
	.string "Have you heard the rumors?\p"
	.string "They say Archan Town has a\n"
	.string "{COLOR GREEN}Hidden Grotto{COLOR BLUE}!$"

ArchanTown_PokemonCenter_EventScript_Worker::
	msgbox ArchanTown_PokemonCenter_Text_TunnelConstructionHalted, MSGBOX_NPC
	end

ArchanTown_PokemonCenter_Text_TunnelConstructionHalted:
	.string "Construction on the Archan Tunnel\n"
	.string "has been forced to halt.\p"
	.string "It's just too dangerous, with the\n"
	.string "constant earthquakes.$"
