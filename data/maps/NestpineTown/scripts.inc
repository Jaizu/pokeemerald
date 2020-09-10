NestpineTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NestpineTown_OnTransition
	.byte 0

NestpineTown_OnTransition::
	setflag FLAG_VISITED_NESTPINE_TOWN
	end

NestpineTown_EventScript_TownSign::
	msgbox NestpineTown_Text_TownSign, MSGBOX_SIGN
	end

NestpineTown_Text_TownSign:
	.string "Nestpine Town\n"
	.string "The Mountainside Nest on Mt. Ignis.$"

NestpineTown_EventScript_GymSign::
	msgbox NestpineTown_Text_GymSign, MSGBOX_SIGN
	end

NestpineTown_Text_GymSign:
	.string "Nestpine Town Pokémon Gym\p"
	.string "Leader: Aria\n"
	.string "“The Circling Songbird.”$"

NestpineTown_EventScript_FrostbiteCaveSign::
	msgbox NestpineTown_Text_FrostbiteCaveSign, MSGBOX_SIGN
	end

NestpineTown_Text_FrostbiteCaveSign:
	.string "{UP_ARROW} Frostbite Cave\n"
	.string "Follow through to Windmist City!$"

NestpineTown_EventScript_MoveDeletersHouseSign::
	msgbox NestpineTown_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

NestpineTown_Text_MoveDeletersHouseSign:
	.string "Move Deleter's house$"
