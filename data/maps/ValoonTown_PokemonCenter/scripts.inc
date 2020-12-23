ValoonTown_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ValoonTown_PokemonCenter_OnTransition
	.byte 0

ValoonTown_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_VALOON_TOWN
	end

ValoonTown_PokemonCenter_EventScript_PkmnRangerM::
	msgbox ValoonTown_PokemonCenter_Text_DontThinkImWeak, MSGBOX_NPC
	end

ValoonTown_PokemonCenter_Text_DontThinkImWeak:
	.string "Don't think I am a weak Ranger\n"
	.string "because I'm here all the time!\p"
	.string "It's because I have a crush\n"
	.string "on the Nurse…$"

ValoonTown_PokemonCenter_EventScript_Youngster::
	msgbox ValoonTown_PokemonCenter_Text_TheBlueShardMeisterNextDoor, MSGBOX_NPC
	end

ValoonTown_PokemonCenter_Text_TheBlueShardMeisterNextDoor:
	.string "The Blue Shard Meister next-door\n"
	.string "isn't the only one.\p"
	.string "There's a Red Shard Meister in\n"
	.string "Ikos Town.\p"
	.string "The Green Shard Meister is usually\n"
	.string "Diving near Sabulo Cross.\p"
	.string "And the Yellow Shard Meister lives\n"
	.string "up on a hill along Aerous Road.$"

ValoonTown_PokemonCenter_EventScript_Lass::
	msgbox ValoonTown_PokemonCenter_Text_LookingForSomeShards, MSGBOX_NPC
	end

ValoonTown_PokemonCenter_Text_LookingForSomeShards:
	.string "Looking for some Shards for the\n"
	.string "Move Tutor?\p"
	.string "A good place to find them is in\n"
	.string "those breakable rocks.\p"
	.string "You know, the ones you can use\n"
	.string "Rock Smash on!$"
