.set LOCALID_COULTER, 4
.set LOCALID_REDWOOD, 5

WindmistCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, WindmistCity_PokemonCenter_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, WindmistCity_PokemonCenter_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, WindmistCity_PokemonCenter_OnWarp
	.byte 0

WindmistCity_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_WINDMIST_CITY
	end

WindmistCity_PokemonCenter_OnFrame:
	map_script_2 VAR_WINDMIST_CITY_POKEMON_CENTER_STATE, 1, WindmistCity_PokemonCenter_EventScript_RedwoodMeetingScene
	.2byte 0

WindmistCity_PokemonCenter_EventScript_RedwoodMeetingScene::
	lockall
	msgbox WindmistCity_PokemonCenter_Text_TheProfessorsJustBoarded, MSGBOX_DEFAULT
	fadenewbgm MUS_SEALED_CHAMBER
	msgbox WindmistCity_PokemonCenter_Text_ICantShakeABadFeeling, MSGBOX_DEFAULT
	closemessage
	delay 64
	playse SE_EXIT
	addobject LOCALID_REDWOOD
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 10
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 10
	playse SE_PIN
	applymovement LOCALID_COULTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_Delay48
	waitmovement 0
	msgbox WindmistCity_PokemonCenter_Text_ProfessorYouMadeIt, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, WindmistCity_PokemonCenter_Movement_RedwoodWalkToPlayer
	waitmovement 0
	msgbox WindmistCity_PokemonCenter_Text_ItWasLuckyYouCaughtMe, MSGBOX_DEFAULT
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox WindmistCity_PokemonCenter_Text_YesAndTheresThisBook, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_REDWOOD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_REDWOOD, Common_Movement_Delay48
	waitmovement 0
	msgbox WindmistCity_PokemonCenter_Text_ItsQuiteAnOldPainting, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	applymovement LOCALID_COULTER, WindmistCity_PokemonCenter_Movement_ExitCoulter
	waitmovement 0
	playse SE_EXIT
	waitse
	removeobject LOCALID_COULTER
	fadedefaultbgm
	msgbox WindmistCity_PokemonCenter_Text_ISeeYouHaveAHealthyRivalry, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, WindmistCity_PokemonCenter_Movement_ExitRedwood
	waitmovement 0
	playse SE_EXIT
	waitse
	removeobject LOCALID_REDWOOD
	clearflag FLAG_HIDE_KNICK_KNACK_STORE_REDWOOD
	setflag FLAG_UNLOCK_WINDMIST_GYM_DOOR
	setvar VAR_WINDMIST_CITY_POKEMON_CENTER_STATE, 2
	releaseall
	end

WindmistCity_PokemonCenter_Text_TheProfessorsJustBoarded:
	.string "{RIVAL}: {COLOR BLUE}The Professor said\n"
	.string "he's just boarded the Cable Car.\p"
	.string "He shouldn't be too long.$"

WindmistCity_PokemonCenter_Text_ICantShakeABadFeeling:
	.string "{RIVAL}: {COLOR BLUE}Man, I can't shake a bad\n"
	.string "feeling about those guys.\p"
	.string "Why would they be at Apex Temple?\p"
	.string "It can't be a coincidence that its\n"
	.string "where the Tablet pointed us, right?$"

WindmistCity_PokemonCenter_Text_ProfessorYouMadeIt:
	.string "{RIVAL}: {COLOR BLUE}Professor, you made it!$"

WindmistCity_PokemonCenter_Text_ItWasLuckyYouCaughtMe:
	.string "Redwood: {COLOR BLUE}It was rather lucky\n"
	.string "you caught me!\p"
	.string "What's going on?\p"
	.string "{COLOR DARK_GREY}…\p"
	.string "{COLOR BLUE}I see…\p"
	.string "They're called the New Elders?$"

WindmistCity_PokemonCenter_Text_YesAndTheresThisBook:
	.string "{RIVAL}: {COLOR BLUE}Yes, and there's\n"
	.string "this book, too!\p"
	.string "Do you know where that island is,\n"
	.string "Professor?\p"
	.string "{COLOR DARK_GREY}Redwood: {COLOR BLUE}Hmm.{PAUSE 0x30}.{PAUSE 0x30}.{PAUSE 0x30}$"

WindmistCity_PokemonCenter_Text_ItsQuiteAnOldPainting:
	.string "Redwood: {COLOR BLUE}It's quite an old\n"
	.string "painting, but…\p"
	.string "That spire unmistakably belongs to\n"
	.string "{COLOR GREEN}Sabulo Tower{COLOR BLUE}.\p"
	.string "Perhaps there's something at\n"
	.string "{COLOR GREEN}Sabulo Island{COLOR BLUE}?\p"
	.string "Hmm…\p"
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}And the Pokémon\n"
	.string "they're chasing, Regirock…\p"
	.string "Do you think it could have\n"
	.string "something to do with the tremors?\p"
	.string "{COLOR DARK_GREY}Redwood: {COLOR BLUE}It's hard to say…\p"
	.string "The few stories I have heard about\n"
	.string "Regirock aren't exactly pleasant…\p"
	.string "If this organization is hunting\n"
	.string "down powerful Pokémon, they must\l"
	.string "be dangerous.\p"
	.string "I'm not sure pursuing them is the\n"
	.string "right move, at least for now.\p"
	.string "You're both still new Trainers.\p"
	.string "I would feel much safer if you\n"
	.string "trained more.\p"
	.string "I just saw {COLOR GREEN}Nina{COLOR BLUE}, the Gym Leader,\n"
	.string "unlocking the city's Gym.\p"
	.string "She's a real tough lady.\n"
	.string "You should both win her Badge.\p"
	.string "If you can defeat her, I'd\n"
	.string "certainly sleep much better.\p"
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}Say no more, Prof!\p"
	.string "I'm definitely getting that Badge\n"
	.string "before {PLAYER} does!$"

WindmistCity_PokemonCenter_Text_ISeeYouHaveAHealthyRivalry:
	.string "Redwood: {COLOR BLUE}Oho! I see the two of you\n"
	.string "have a healthy rivalry!\p"
	.string "Anyway, I've got some business to\n"
	.string "attend to, here in the city.\p"
	.string "Good luck with your Gym challenge,\n"
	.string "{PLAYER}!$"

WindmistCity_PokemonCenter_Movement_RedwoodWalkToPlayer:
	walk_up
	walk_up
	step_end

WindmistCity_PokemonCenter_Movement_ExitCoulter:
	walk_down
	walk_down
	walk_left
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end

WindmistCity_PokemonCenter_Movement_ExitRedwood:
	walk_down
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end

WindmistCity_PokemonCenter_OnWarp:
	map_script_2 VAR_WINDMIST_CITY_POKEMON_CENTER_STATE, 1, WindmistCity_PokemonCenter_EventScript_TurnPlayerEast
	.2byte 0

WindmistCity_PokemonCenter_EventScript_TurnPlayerEast:
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	end

WindmistCity_PokemonCenter_EventScript_Picnicker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WINDMIST_CITY_CHOICE_SCARF, WindmistCity_PokemonCenter_EventScript_ReceivedChoiceScarf
	msgbox WindmistCity_PokemonCenter_Text_IBoughtThisScarf, MSGBOX_DEFAULT
	giveitem ITEM_CHOICE_SCARF
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WINDMIST_CITY_CHOICE_SCARF
	goto WindmistCity_PokemonCenter_EventScript_ReceivedChoiceScarf
	end

WindmistCity_PokemonCenter_EventScript_ReceivedChoiceScarf:
	msgbox WindmistCity_PokemonCenter_Text_IWonderIfPokemonCouldWearThatScarf, MSGBOX_DEFAULT
	release
	end

WindmistCity_PokemonCenter_Text_IBoughtThisScarf:
	.string "I bought this scarf a while back,\n"
	.string "but it doesn't keep me warm.\p"
	.string "I guess you can take it instead.$"

WindmistCity_PokemonCenter_Text_IWonderIfPokemonCouldWearThatScarf:
	.string "I wonder if Pokémon could wear\n"
	.string "that scarf?$"

WindmistCity_PokemonCenter_EventScript_Explorer::
	msgbox WindmistCity_PokemonCenter_Text_ExplainSnowWarning, MSGBOX_NPC
	end

WindmistCity_PokemonCenter_Text_ExplainSnowWarning:
	.string "When my Snover is sent out in\n"
	.string "battle it summons a hailstorm!\p"
	.string "Impressive, right?$"
