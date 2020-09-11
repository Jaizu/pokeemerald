.equ LOCALID_COULTER, 5

.equ WEST_OF_COULTER, 23
.equ SOUTH_OF_COULTER, 24
.equ EAST_OF_COULTER, 25

NestpineTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NestpineTown_OnTransition
	.byte 0

NestpineTown_OnTransition::
	setflag FLAG_VISITED_NESTPINE_TOWN
	end

NestpineTown_EventScript_Coulter::
	lock
	faceplayer
	msgbox NestpineTown_Text_YouMadeItPlayer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq NestpineTown_EventScript_CoulterBattle
	msgbox NestpineTown_Text_ComeBackWhenYoureReady, MSGBOX_DEFAULT
	release
	end

NestpineTown_EventScript_CoulterBattle:
	msgbox NestpineTown_Text_IllWinThisTimeForSure, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0 // Player chose Turtwig
	call_if_eq NestpineTown_EventScript_StartCoulterBattleMonferno
	compare VAR_STARTER_MON, 1 // Player chose Chimchar
	call_if_eq NestpineTown_EventScript_StartCoulterBattlePrinplup
	compare VAR_STARTER_MON, 2 // Player chose Piplup
	call_if_eq NestpineTown_EventScript_StartCoulterBattleGrotle
	msgbox NestpineTown_Text_BreatheInBreatheOut, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE
	compare VAR_RESULT, FALSE
	call_if_ne NestpineTown_EventScript_SetReceivedExpShareFlag
	compare VAR_RESULT, FALSE
	call_if_eq NestpineTown_EventScript_NoRoomForExpShare
	msgbox NestpineTown_Text_ImGoingToForgetThisBattleHappened, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL2, 0
	getplayerxy VAR_0x8000, VAR_0x8001
	compare VAR_0x8000, SOUTH_OF_COULTER
	call_if_eq NestpineTown_EventScript_ExitCoulter0
	compare VAR_0x8000, SOUTH_OF_COULTER
	call_if_ne NestpineTown_EventScript_ExitCoulter1
	removeobject LOCALID_COULTER
	fadedefaultbgm
	delay 10
	release
	end

NestpineTown_EventScript_StartCoulterBattleMonferno:
	trainerbattle_no_intro TRAINER_COULTER_NESTPINE_TOWN_MONFERNO, NestpineTown_Text_CoulterDefeat
	return

NestpineTown_EventScript_StartCoulterBattlePrinplup:
	trainerbattle_no_intro TRAINER_COULTER_NESTPINE_TOWN_PRINPLUP, NestpineTown_Text_CoulterDefeat
	return

NestpineTown_EventScript_StartCoulterBattleGrotle:
	trainerbattle_no_intro TRAINER_COULTER_NESTPINE_TOWN_GROTLE, NestpineTown_Text_CoulterDefeat
	return

NestpineTown_EventScript_NoRoomForExpShare:
	call Common_EventScript_BagIsFull
	msgbox NestpineTown_Text_OhYouDontHaveRoom, MSGBOX_DEFAULT
	setflag FLAG_DIDNT_RECEIVE_EXP_SHARE
	return

NestpineTown_EventScript_SetReceivedExpShareFlag:
	setflag FLAG_RECEIVED_EXP_SHARE
	return

NestpineTown_EventScript_ExitCoulter0:
	applymovement LOCALID_COULTER, NestpineTown_Movement_ExitCoulter0
	waitmovement 0
	return

NestpineTown_EventScript_ExitCoulter1:
	applymovement LOCALID_COULTER, NestpineTown_Movement_ExitCoulter1
	waitmovement 0
	return

NestpineTown_Text_YouMadeItPlayer:
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}You made it, {PLAYER}!\n"
	.string "It's been a while, no?\p"
	.string "Well, the Prof. told me all about\n"
	.string "Apex Temple.\p"
	.string "On the way up, I fought this Gym,\n"
	.string "and got the Badge!\p"
	.string "Say… It's been a while since we\n"
	.string "last battled.\p"
	.string "What do you say?\n"
	.string "Are you up to it?$"

NestpineTown_Text_ComeBackWhenYoureReady:
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}Come back when\n"
	.string "you're ready!$"

NestpineTown_Text_IllWinThisTimeForSure:
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}I'll win this time,\n"
	.string "for sure!{PLAY_BGM}{MUS_RG_RIVAL2}$"

NestpineTown_Text_CoulterDefeat:
	.string "No…\n"
	.string "Again? No way!$"

NestpineTown_Text_BreatheInBreatheOut:
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}… … …\n"
	.string "Breathe in, breathe out…\p"
	.string "I've got to control my anger…\p"
	.string "…\p"
	.string "Okay!\p"
	.string "Maybe my Pokémon aren't strong like\n"
	.string "yours because of this {COLOR GREEN}Exp. Share{COLOR BLUE}.\p"
	.string "I guess you could find a better\n"
	.string "use for it.$"

NestpineTown_Text_OhYouDontHaveRoom:
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}Oh, you don't have\n"
	.string "room for it?\p"
	.string "Well, I'll leave it with\n"
	.string "Prof. Redwood.\p"
	.string "Anyway…$"

NestpineTown_Text_ImGoingToForgetThisBattleHappened:
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}I'm going to forget\n"
	.string "that this battle happened.\p"
	.string "I'll meet you near Apex Temple,\n"
	.string "alright?\p"
	.string "Don't take too long, Slowpoke!$"

NestpineTown_Movement_ExitCoulter0:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

NestpineTown_Movement_ExitCoulter1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

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
