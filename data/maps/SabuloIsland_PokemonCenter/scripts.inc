SabuloIsland_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SabuloIsland_PokemonCenter_OnTransition
	.byte 0

SabuloIsland_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_SABULO_ISLAND
	end

SabuloIsland_PokemonCenter_EventScript_OldMan::
	msgbox SabuloIsland_PokemonCenter_Text_TrainersFlockToSabuloIsland, MSGBOX_NPC
	end

SabuloIsland_PokemonCenter_Text_TrainersFlockToSabuloIsland:
	.string "Trainers flock to Sabulo Island,\n"
	.string "clamoring for the Mega Ring.\p"
	.string "What they don't realize is it's\n"
	.string "useless without Mega Stones!$"

SabuloIsland_PokemonCenter_EventScript_AceTrainerF::
	msgbox SabuloIsland_PokemonCenter_Text_HaveYouTriedLookingForShards, MSGBOX_NPC
	end

SabuloIsland_PokemonCenter_Text_HaveYouTriedLookingForShards:
	.string "Have you tried looking for Shards\n"
	.string "with an Itemfinder?\p"
	.string "Shard Tutors value them highly.\p"
	.string "They'll teach Pokémon special\n"
	.string "moves in exchange.$"
