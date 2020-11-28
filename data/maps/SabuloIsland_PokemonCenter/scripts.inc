SabuloIsland_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SabuloIsland_PokemonCenter_OnTransition
	.byte 0

SabuloIsland_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_SABULO_ISLAND
	end

SabuloIsland_PokemonCenter_EventScript_OldMan::
	lock
	faceplayer
	compare VAR_SABULO_ISLAND_STATE, 2
	goto_if_eq SabuloIsland_PokemonCenter_EventScript_DearMe
	msgbox SabuloIsland_PokemonCenter_Text_TrainersFlockToSabuloIsland, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloIsland_PokemonCenter_Text_TrainersFlockToSabuloIsland:
	.string "Trainers flock to Sabulo Island,\n"
	.string "clamoring for the Mega Ring.\p"
	.string "What they don't realize is it's\n"
	.string "useless without Mega Stones!$"

SabuloIsland_PokemonCenter_EventScript_DearMe:
	msgbox SabuloIsland_PokemonCenter_Text_DearMe, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloIsland_PokemonCenter_Text_DearMe:
	.string "Dear me!\p"
	.string "What on earth could be going on\n"
	.string "out there?$"

SabuloIsland_PokemonCenter_EventScript_AceTrainerF::
	lock
	faceplayer
	compare VAR_SABULO_ISLAND_STATE, 2
	goto_if_eq SabuloIsland_PokemonCenter_EventScript_IsSomethingHappening
	msgbox SabuloIsland_PokemonCenter_Text_HaveYouTriedLookingForShards, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloIsland_PokemonCenter_Text_HaveYouTriedLookingForShards:
	.string "Have you tried looking for Shards\n"
	.string "with an Itemfinder?\p"
	.string "Shard Tutors value them highly.\p"
	.string "They'll teach Pokémon special\n"
	.string "moves in exchange.$"

SabuloIsland_PokemonCenter_EventScript_IsSomethingHappening:
	msgbox SabuloIsland_PokemonCenter_Text_IsSomethingHappening, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloIsland_PokemonCenter_Text_IsSomethingHappening:
	.string "Is something happening to\n"
	.string "Sabulo Cave? How scary!$"
