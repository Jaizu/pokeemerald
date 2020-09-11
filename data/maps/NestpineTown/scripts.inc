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

NestpineTown_EventScript_Hiker::
	msgbox NestpineTown_Text_HeardTheLegendsOfEmeraldPeak, MSGBOX_NPC
	end

NestpineTown_Text_HeardTheLegendsOfEmeraldPeak:
	.string "Have you heard the legends of the\n"
	.string "Emerald Peak?\p"
	.string "They say it's a peak of Mt. Ignis\n"
	.string "where a rare Pokémon goes to roost.$"

NestpineTown_EventScript_Scientist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_UP_GRADE, NestpineTown_EventScript_ExplainWhereToFindPorygon
	goto_if_set FLAG_BADGE02_GET, NestpineTown_EventScript_TryGiveUpGrade
	msgbox NestpineTown_Text_YoureATrainer, MSGBOX_DEFAULT
	release
	end

NestpineTown_EventScript_TryGiveUpGrade:
	msgbox NestpineTown_Text_ISeeYouGotThePlumeBadge, MSGBOX_DEFAULT
	giveitem ITEM_UP_GRADE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_UP_GRADE
	goto NestpineTown_EventScript_ExplainWhereToFindPorygon
	end

NestpineTown_EventScript_ExplainWhereToFindPorygon:
	msgbox NestpineTown_Text_CuriousAboutWhereToFindPorygon, MSGBOX_DEFAULT
	release
	end

NestpineTown_Text_YoureATrainer:
	.string "A Trainer, huh?\n"
	.string "Hmm…\p"
	.string "If you can win the Plume Badge, I\n"
	.string "may have something for you…$"

NestpineTown_Text_ISeeYouGotThePlumeBadge:
	.string "I see you got the Plume Badge?\p"
	.string "Maybe a Trainer like you can make\n"
	.string "use of this, then.$"

NestpineTown_Text_CuriousAboutWhereToFindPorygon:
	.string "Curious about where to find\n"
	.string "Porygon?\p"
	.string "Last I heard, the Game Corner in\n"
	.string "Telmurk City offers them as prizes.$"

NestpineTown_EventScript_OldMan::
	msgbox NestpineTown_Text_SawSomeShadyPeopleInFrostbiteCave, MSGBOX_NPC
	end

NestpineTown_Text_SawSomeShadyPeopleInFrostbiteCave:
	.string "I saw some shady people hanging\n"
	.string "around in Frostbite Cave.\p"
	.string "I wonder what they're up to?$"
