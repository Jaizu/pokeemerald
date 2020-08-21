.equ LOCALID_REDWOOD, 1
.equ LOCALID_TURTWIG_BALL, 2
.equ LOCALID_CHIMCHAR_BALL, 3
.equ LOCALID_PIPLUP_BALL, 4
.equ LOCALID_OPP_GENDER, 5
.equ LOCALID_COULTER, 6

CelantoTown_BackOfLibrary_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CelantoTown_BackOfLibrary_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CelantoTown_BackOfLibrary_OnFrame
	.byte 0

CelantoTown_BackOfLibrary_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	compare VAR_CELANTO_LIBRARY_STATE, 1
	call_if_eq CelantoTown_BackOfLibrary_EventScript_MoveRedwood
	end

CelantoTown_BackOfLibrary_OnFrame:
	map_script_2 VAR_CELANTO_LIBRARY_STATE, 0, CelantoTown_BackOfLibrary_EventScript_RedwoodWelcome
	.2byte 0

CelantoTown_BackOfLibrary_EventScript_RedwoodWelcome:
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp
	waitmovement 0
	special RemoveCameraObject
	playbgm MUS_RG_OHKIDO, 0
	msgbox CelantoTown_BackOfLibrary_Text_AtLastThirdPerson, MSGBOX_DEFAULT
	closemessage
	playse SE_BOO
	applymovement LOCALID_OPP_GENDER, CelantoTown_BackOfLibrary_Movement_X
	waitmovement 0
	applymovement LOCALID_OPP_GENDER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_OPP_GENDER, CelantoTown_BackOfLibrary_Movement_ExitOppGender
	waitmovement 0
	playse SE_KAIDAN
	waitse
	removeobject LOCALID_OPP_GENDER
	msgbox CelantoTown_BackOfLibrary_Text_WellThen, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, CelantoTown_BackOfLibrary_Movement_RedwoodMoveToTheSide
	waitmovement 0
	call CelantoTown_BackOfLibrary_EventScript_MoveRedwood
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown
	waitmovement 0
	special RemoveCameraObject
	fadedefaultbgm
	setvar VAR_CELANTO_LIBRARY_STATE, 1
	releaseall
	end

CelantoTown_BackOfLibrary_Text_AtLastThirdPerson:
	.string "Redwood: {COLOR BLUE}At last, a third person!\p"
	.string "I thought more people would be\n"
	.string "interested in free Pokémon…\p"
	.string "Obviously not!\p"
	.string "For those of you who don't know,\n"
	.string "my name is {COLOR GREEN}Prof. Redwood{COLOR BLUE}.\p"
	.string "I am the Pokémon Professor of the\n"
	.string "Orbtus region.\p"
	.string "I've come here to Celanto Town\n"
	.string "today to seek out talent.\p"
	.string "You see, I am getting quite old!\p"
	.string "I can't keep up with the fieldwork\n"
	.string "my research necessitates.\p"
	.string "For that reason, I need helpers!$"

CelantoTown_BackOfLibrary_Movement_X:
	emote_heart // TODO: Port the [X] emote from FireRed
	step_end

CelantoTown_BackOfLibrary_Movement_ExitOppGender:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

CelantoTown_BackOfLibrary_Text_WellThen:
	.string "Redwood: {COLOR BLUE}…Well then!\p"
	.string "I guess that prospect doesn't\n"
	.string "appeal to everyone, eheh…\p"
	.string "That leaves you two with the choice\n"
	.string "of these three, rare Pokémon!\p"
	.string "Please, go and choose!$"

CelantoTown_BackOfLibrary_Movement_RedwoodMoveToTheSide:
	walk_right
	walk_right
	walk_down
	walk_in_place_fastest_left
	step_end

CelantoTown_BackOfLibrary_EventScript_MoveRedwood:
	setobjectxyperm LOCALID_REDWOOD, 10, 4
	setobjectmovementtype LOCALID_REDWOOD, MOVEMENT_TYPE_FACE_LEFT
	return

CelantoTown_BackOfLibrary_EventScript_Coulter::
	lock
	faceplayer
	msgbox CelantoTown_BackOfLibrary_Text_YouCanChooseFirst, MSGBOX_DEFAULT
	applymovement LOCALID_COULTER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CelantoTown_BackOfLibrary_Text_YouCanChooseFirst:
	.string "{COLOR DARK_GREY}???: {COLOR BLUE}You can choose first!$"

CelantoTown_BackOfLibrary_EventScript_Redwood::
	lock
	faceplayer
	msgbox CelantoTown_BackOfLibrary_Text_GoAhead, MSGBOX_DEFAULT
	applymovement LOCALID_REDWOOD, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CelantoTown_BackOfLibrary_Text_GoAhead:
	.string "{COLOR DARK_GREY}Redwood: {COLOR BLUE}Go ahead, pick a {COLOR GREEN}Pokémon{COLOR BLUE}!$"

CelantoTown_BackOfLibrary_EventScript_TurtwigBall::
	lockall
	setvar VAR_0x8008, SPECIES_TURTWIG
	goto CelantoTown_BackOfLibrary_EventScript_PokemonSelection
	end

CelantoTown_BackOfLibrary_EventScript_ChimcharBall::
	lockall
	setvar VAR_0x8008, SPECIES_CHIMCHAR
	goto CelantoTown_BackOfLibrary_EventScript_PokemonSelection
	end

CelantoTown_BackOfLibrary_EventScript_PiplupBall::
	lockall
	setvar VAR_0x8008, SPECIES_PIPLUP
	goto CelantoTown_BackOfLibrary_EventScript_PokemonSelection
	end

CelantoTown_BackOfLibrary_EventScript_PokemonSelection:
	bufferspeciesname 0, VAR_0x8008
	playmoncry VAR_0x8008, 0
	showmonpic VAR_0x8008, 10, 3
	compare VAR_0x8008, SPECIES_TURTWIG
	call_if_eq CelantoTown_BackOfLibrary_EventScript_PrintTurtwig
	compare VAR_0x8008, SPECIES_CHIMCHAR
	call_if_eq CelantoTown_BackOfLibrary_EventScript_PrintChimchar
	compare VAR_0x8008, SPECIES_PIPLUP
	call_if_eq CelantoTown_BackOfLibrary_EventScript_PrintPiplup
	waitmoncry
	msgbox CelantoTown_BackOfLibrary_Text_ChooseThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq CelantoTown_BackOfLibrary_EventScript_HideMonPicEnd
	compare VAR_0x8008, SPECIES_TURTWIG
	call_if_eq CelantoTown_BackOfLibrary_EventScript_ChoseTurtwig
	compare VAR_0x8008, SPECIES_CHIMCHAR
	call_if_eq CelantoTown_BackOfLibrary_EventScript_ChoseChimchar
	compare VAR_0x8008, SPECIES_PIPLUP
	call_if_eq CelantoTown_BackOfLibrary_EventScript_ChosePiplup
	hidemonpic
	givemon VAR_0x8008, 5, ITEM_NONE
	setflag FLAG_SYS_POKEMON_GET
	playfanfare MUS_RG_FAN5
	message CelantoTown_BackOfLibrary_Text_ReceivedStarter
	waitmessage
	waitfanfare
	setvar 0x8004 0
	special BufferMonNatureName
	msgbox CelantoTown_BackOfLibrary_Text_ItsNatureAppearsToBe, MSGBOX_DEFAULT
	msgbox CelantoTown_BackOfLibrary_Text_WouldYouLikeToGiveANickname, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq CelantoTown_BackOfLibrary_EventScript_NicknameStarter
	closemessage
	compare VAR_0x8008, SPECIES_TURTWIG
	call_if_eq CelantoTown_BackOfLibrary_EventScript_CoulterChoosesChimchar
	compare VAR_0x8008, SPECIES_CHIMCHAR
	call_if_eq CelantoTown_BackOfLibrary_EventScript_CoulterChoosesPiplup
	compare VAR_0x8008, SPECIES_PIPLUP
	call_if_eq CelantoTown_BackOfLibrary_EventScript_CoulterChoosesTurtwig
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	compare VAR_0x8008, SPECIES_TURTWIG
	call_if_eq CelantoTown_BackOfLibrary_EventScript_RedwoodPicksUpPiplupBall
	compare VAR_0x8008, SPECIES_CHIMCHAR
	call_if_eq CelantoTown_BackOfLibrary_EventScript_RedwoodPicksUpTurtwigBall
	compare VAR_0x8008, SPECIES_PIPLUP
	call_if_eq CelantoTown_BackOfLibrary_EventScript_RedwoodPicksUpChimcharBall
	msgbox CelantoTown_BackOfLibrary_Text_CongratulationsMeetMeArchanTown, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_OHKIDO, 0
	applymovement LOCALID_REDWOOD, CelantoTown_BackOfLibrary_Movement_RedwoodExit
	waitmovement 0
	playse SE_KAIDAN
	waitse
	removeobject LOCALID_REDWOOD
	fadedefaultbgm
	delay 10
	compare VAR_0x8008, SPECIES_PIPLUP
	call_if_eq CelantoTown_BackOfLibrary_EventScript_CoulterFacesRight
	compare VAR_0x8008, SPECIES_PIPLUP
	call_if_ne CelantoTown_BackOfLibrary_EventScript_CoulterFacesLeft
	msgbox CelantoTown_BackOfLibrary_Text_ThisIsCoolIsntIt, MSGBOX_DEFAULT
	closemessage
	call CelantoTown_BackOfLibrary_EventScript_SetRivalName
	msgbox CelantoTown_BackOfLibrary_Text_TheNamesRival, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL2, 0
	compare VAR_0x8008, SPECIES_TURTWIG
	call_if_eq CelantoTown_BackOfLibrary_EventScript_CoulterExitFromChimcharBall
	compare VAR_0x8008, SPECIES_CHIMCHAR
	call_if_eq CelantoTown_BackOfLibrary_EventScript_CoulterExitFromPiplupBall
	compare VAR_0x8008, SPECIES_PIPLUP
	call_if_eq CelantoTown_BackOfLibrary_EventScript_CoulterExitFromTurtwigBall
	playse SE_KAIDAN
	waitse
	removeobject LOCALID_COULTER
	fadedefaultbgm
	delay 10
	setvar VAR_CELANTO_TOWN_GUARD, 1
	setvar VAR_CELANTO_LIBRARY_STATE, 2
	releaseall
	end

CelantoTown_BackOfLibrary_EventScript_NicknameStarter:
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	return

CelantoTown_BackOfLibrary_EventScript_PrintTurtwig:
	msgbox CelantoTown_BackOfLibrary_Text_TinyLeafPokemon, MSGBOX_DEFAULT
	return

CelantoTown_BackOfLibrary_EventScript_PrintChimchar:
	msgbox CelantoTown_BackOfLibrary_Text_ChimpPokemon, MSGBOX_DEFAULT
	return

CelantoTown_BackOfLibrary_EventScript_PrintPiplup:
	msgbox CelantoTown_BackOfLibrary_Text_PenguinPokemon, MSGBOX_DEFAULT
	return

CelantoTown_BackOfLibrary_EventScript_HideMonPicEnd:
	hidemonpic
	releaseall
	end

CelantoTown_BackOfLibrary_EventScript_ChoseTurtwig:
	removeobject LOCALID_TURTWIG_BALL
	setvar VAR_STARTER_MON, 0
	return

CelantoTown_BackOfLibrary_EventScript_ChoseChimchar:
	removeobject LOCALID_CHIMCHAR_BALL
	setvar VAR_STARTER_MON, 1
	return

CelantoTown_BackOfLibrary_EventScript_ChosePiplup:
	removeobject LOCALID_PIPLUP_BALL
	setvar VAR_STARTER_MON, 2
	return

CelantoTown_BackOfLibrary_EventScript_CoulterChoosesChimchar:
	applymovement LOCALID_COULTER, CelantoTown_BackOfLibrary_Movement_CoulterToChimcharBall
	waitmovement 0
	removeobject LOCALID_CHIMCHAR_BALL
	return

CelantoTown_BackOfLibrary_EventScript_CoulterChoosesPiplup:
	applymovement LOCALID_COULTER, CelantoTown_BackOfLibrary_Movement_CoulterToPiplupBall
	waitmovement 0
	removeobject LOCALID_PIPLUP_BALL
	return

CelantoTown_BackOfLibrary_EventScript_CoulterChoosesTurtwig:
	applymovement LOCALID_COULTER, CelantoTown_BackOfLibrary_Movement_CoulterToTurtwigBall
	waitmovement 0
	removeobject LOCALID_TURTWIG_BALL
	return

CelantoTown_BackOfLibrary_EventScript_RedwoodPicksUpPiplupBall:
	applymovement LOCALID_REDWOOD, CelantoTown_BackOfLibrary_Movement_RedwoodGoToPiplupBall
	waitmovement 0
	removeobject LOCALID_PIPLUP_BALL
	applymovement LOCALID_REDWOOD, CelantoTown_BackOfLibrary_Movement_RedwoodGoFromPiplupBall
	waitmovement 0
	return
	
CelantoTown_BackOfLibrary_EventScript_RedwoodPicksUpTurtwigBall:
	applymovement LOCALID_REDWOOD, CelantoTown_BackOfLibrary_Movement_RedwoodGoToTurtwigBall
	waitmovement 0
	removeobject LOCALID_TURTWIG_BALL
	applymovement LOCALID_REDWOOD, CelantoTown_BackOfLibrary_Movement_RedwoodGoFromTurtwigBall
	waitmovement 0
	return

CelantoTown_BackOfLibrary_EventScript_RedwoodPicksUpChimcharBall:
	applymovement LOCALID_REDWOOD, CelantoTown_BackOfLibrary_Movement_RedwoodGoToChimcharBall
	waitmovement 0
	removeobject LOCALID_CHIMCHAR_BALL
	applymovement LOCALID_REDWOOD, CelantoTown_BackOfLibrary_Movement_RedwoodGoFromChimcharBall
	waitmovement 0
	return

CelantoTown_BackOfLibrary_EventScript_CoulterFacesLeft:
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

CelantoTown_BackOfLibrary_EventScript_CoulterFacesRight:
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

CelantoTown_BackOfLibrary_EventScript_SetRivalName:
	closemessage
	fadescreen FADE_TO_BLACK
	// TODO: Implement SetRivalName special
	// special nullsub_37
	// waitstate
	fadescreen FADE_FROM_BLACK
	msgbox CelantoTown_BackOfLibrary_Text_IsHisNameRival, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq CelantoTown_BackOfLibrary_EventScript_SetRivalName
	return

CelantoTown_BackOfLibrary_EventScript_CoulterExitFromChimcharBall:
	applymovement LOCALID_COULTER, CelantoTown_BackOfLibrary_Movement_CoulterExitFromChimcharBall
	waitmovement 0
	return

CelantoTown_BackOfLibrary_EventScript_CoulterExitFromPiplupBall:
	applymovement LOCALID_COULTER, CelantoTown_BackOfLibrary_Movement_CoulterExitFromPiplupBall
	waitmovement 0
	return

CelantoTown_BackOfLibrary_EventScript_CoulterExitFromTurtwigBall:
	applymovement LOCALID_COULTER, CelantoTown_BackOfLibrary_Movement_CoulterExitFromTurtwigBall
	waitmovement 0
	return

CelantoTown_BackOfLibrary_Text_TinyLeafPokemon:
	.string "{STR_VAR_1}, the Tiny Leaf Pokémon.$"

CelantoTown_BackOfLibrary_Text_ChimpPokemon:
	.string "{STR_VAR_1}, the Chimp Pokémon.$"

CelantoTown_BackOfLibrary_Text_PenguinPokemon:
	.string "{STR_VAR_1}, the Penguin Pokémon.$"

CelantoTown_BackOfLibrary_Text_ChooseThisPokemon:
	.string "Choose {STR_VAR_1}?$"

CelantoTown_BackOfLibrary_Text_ReceivedStarter:
	.string "{PLAYER} received\n"
	.string "the {STR_VAR_1}!$"

CelantoTown_BackOfLibrary_Text_ItsNatureAppearsToBe:
	.string "Its nature appears to be\n"
	.string "{COLOR GREEN}{STR_VAR_2}{COLOR DARK_GREY}!$"

CelantoTown_BackOfLibrary_Text_WouldYouLikeToGiveANickname:
	.string "Would you like to give\n"
	.string "{STR_VAR_1} a nickname?$"

CelantoTown_BackOfLibrary_Text_CongratulationsMeetMeArchanTown:
	.string "Redwood: {COLOR BLUE}Congratulations!\p"
	.string "I'm sure you and your Pokémon will\n"
	.string "bond in no time!\p"
	.string "Anyway, I promised the librarian I\n"
	.string "wouldn't be here long…\p"
	.string "We should continue this chat at my\n"
	.string "house, in {COLOR GREEN}Archan Town{COLOR BLUE}!\p"
	.string "I have a gift for each of you\n"
	.string "waiting there, as well.\p"
	.string "{COLOR DARK_GREY}Redwood: {COLOR BLUE}I'll meet you there!$"

CelantoTown_BackOfLibrary_Text_ThisIsCoolIsntIt:
	.string "???: {COLOR BLUE}This is cool, isn't it?\n"
	.string "I've always wanted my own Pokémon.\p"
	.string "I wonder what the Professor's\n"
	.string "research is about…\p"
	.string "It will be fun to find out\n"
	.string "though, hey?\p"
	.string "Oh!\n"
	.string "I should introduce myself.\p"
	.string "My name is…$"

CelantoTown_BackOfLibrary_Text_IsHisNameRival:
	.string "Is his name {RIVAL}?$"

CelantoTown_BackOfLibrary_Text_TheNamesRival:
	.string "{RIVAL}: {COLOR BLUE}The name's {RIVAL}!\n"
	.string "And you?\p"
	.string "{COLOR DARK_GREY}{RIVAL}: {COLOR BLUE}I see!\n"
	.string "Nice to meet you, {PLAYER}!\p"
	.string "I'll race you to Archan Town!\n"
	.string "Last one there is a Slowpoke!$"

CelantoTown_BackOfLibrary_Movement_CoulterToChimcharBall:
	walk_up
	walk_right
	walk_up
	walk_in_place_fastest_up
	step_end

CelantoTown_BackOfLibrary_Movement_CoulterToTurtwigBall:
	walk_up
	walk_up
	walk_in_place_fastest_up
	step_end

CelantoTown_BackOfLibrary_Movement_CoulterToPiplupBall:
	walk_up
	walk_right
	walk_right
	walk_up
	walk_in_place_fastest_up
	step_end

CelantoTown_BackOfLibrary_Movement_RedwoodGoToPiplupBall:
	walk_left
	walk_up
	walk_in_place_fastest_up
	step_end

CelantoTown_BackOfLibrary_Movement_RedwoodGoFromPiplupBall:
	walk_down
	walk_left
	walk_in_place_fastest_up
	step_end

CelantoTown_BackOfLibrary_Movement_RedwoodGoToTurtwigBall:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_in_place_fastest_up
	step_end

CelantoTown_BackOfLibrary_Movement_RedwoodGoFromTurtwigBall:
	walk_down
	walk_right
	walk_in_place_fastest_up
	step_end

CelantoTown_BackOfLibrary_Movement_RedwoodGoToChimcharBall:
	walk_left
	walk_left
	walk_up
	walk_in_place_fastest_up
	step_end

CelantoTown_BackOfLibrary_Movement_RedwoodGoFromChimcharBall:
	walk_down
	walk_in_place_fastest_up
	step_end

CelantoTown_BackOfLibrary_Movement_RedwoodExit:
	walk_down
	walk_down
	walk_in_place_fastest_down
	step_end

CelantoTown_BackOfLibrary_Movement_CoulterExitFromChimcharBall:
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_down
	step_end

CelantoTown_BackOfLibrary_Movement_CoulterExitFromPiplupBall:
	walk_down
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_down
	step_end

CelantoTown_BackOfLibrary_Movement_CoulterExitFromTurtwigBall:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_in_place_fastest_down
	step_end
