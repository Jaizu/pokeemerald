ValoonTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ValoonTown_OnTransition
	.byte 0

ValoonTown_OnTransition::
	setflag FLAG_VISITED_VALOON_TOWN
	end

ValoonTown_EventScript_TownSign::
	msgbox ValoonTown_Text_TownSign, MSGBOX_SIGN
	end

ValoonTown_Text_TownSign::
	.string "Valoon Town\n"
	.string "A Habitat for Pokémon and People.$"

ValoonTown_EventScript_GymSign::
	msgbox ValoonTown_Text_GymSign, MSGBOX_SIGN
	end

ValoonTown_Text_GymSign::
	.string "Valoon Town Pokémon Gym\p"
	.string "Leader: Vernon\n"
	.string "“He wouldn't harm a Joltik!”$"

ValoonTown_EventScript_RangersHeadquartersSign::
	msgbox ValoonTown_Text_RangersHeadquartersSign, MSGBOX_SIGN
	end

ValoonTown_Text_RangersHeadquartersSign::
	.string "Valoon Rangers Headquarters\p"
	.string "Take part in the Bug-Catching\n"
	.string "Contest!$"

ValoonTown_EventScript_BlueShardMeisterSign::
	msgbox ValoonTown_Text_BlueShardMeisterSign, MSGBOX_SIGN
	end

ValoonTown_Text_BlueShardMeisterSign::
	.string "Blue Shard Meister's house\p"
	.string "“I will teach Pokémon moves for\n"
	.string "Blue Shards!”$"
