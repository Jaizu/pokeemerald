.equ LOCALID_MOM, 1
.equ LOCALID_OLD_MAN, 6
.equ LOCALID_CELANTO_PATH_GUARD, 7

CelantoTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CelantoTown_OnTransition
	.byte 0

CelantoTown_OnTransition::
	setflag FLAG_VISITED_PETALBURG_CITY
	end

CelantoTown_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_GRACIDEA, CelantoTown_EventScript_OldManDiscussGracidea
	msgbox CelantoTown_Text_ThisFlowerIsStriking
	setvar VAR_0x8004, SPECIES_SHAYMIN
	specialvar VAR_RESULT, IsPokemonJumpSpeciesInParty // TODO: Port DoesPlayerPartyContainSpecies
	compare VAR_RESULT, TRUE
	goto_if_eq CelantoTown_EventScript_OldManTryGiveGracidea
	msgbox CelantoTown_Text_LongAdmiredInterestingFlowers
	goto CelantoTown_EventScript_OldManFaceFlower

CelantoTown_EventScript_OldManTryGiveGracidea::
	playse SE_PIN
	applymovement LOCALID_OLD_MAN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_OLD_MAN, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_Text_YourShayminIsBeautiful
	giveitem ITEM_GRACIDEA
	setflag FLAG_RECEIVED_GRACIDEA
	additem ITEM_GRACIDEA
	goto CelantoTown_EventScript_OldManDiscussGracidea

CelantoTown_EventScript_OldManDiscussGracidea::
	msgbox CelantoTown_Text_ThatGracideaYourPokemonWillLoveIt
	goto CelantoTown_EventScript_OldManFaceFlower

CelantoTown_EventScript_OldManFaceFlower::
	applymovement LOCALID_OLD_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CelantoTown_Text_ThisFlowerIsStriking::
	.string "My… This flower…\n"
	.string "It's so striking!\p"
	.string "There's something to be said about\n"
	.string "unique flowers, wouldn't you say?$"

CelantoTown_Text_LongAdmiredInterestingFlowers::
	.string "Yes, yes… I've long admired\n"
	.string "interesting flowers…$"

CelantoTown_Text_YourShayminIsBeautiful::
	.string "Oh, your Pokémon!\n"
	.string "It's beautiful!\p"
	.string "It reminds me of this incredibly\n"
	.string "beautiful flower I found.\p"
	.string "I always keep it with me!\n"
	.string "Please, I insist, take it.$"

CelantoTown_Text_ThatGracideaYourPokemonWillLoveIt::
	.string "That Gracidea… I just know your\n"
	.string "Pokémon will love it!$"

CelantoTown_EventScript_CelantoPathGuard::
	lock
	faceplayer
	compare VAR_CELANTO_TOWN_GUARD, 1
	goto_if_ge CelantoTown_EventScript_CelantoPathGuardSisterStory
	msgbox CelantoTown_Text_WildPokemonPastHereAreDangerous
	release
	end

CelantoTown_EventScript_CelantoPathGuardSisterStory::
	msgbox CelantoTown_Text_MySisterWentOutWithoutAPokemon
	release
	end

CelantoTown_Text_WildPokemonPastHereAreDangerous::
	.string "The wild Pokémon past here are\n"
	.string "incredibly dangerous!\p"
	.string "You shouldn't go out alone!$"

CelantoTown_Text_MySisterWentOutWithoutAPokemon::
	.string "My sister once went out to Celanto\n"
	.string "Path without a Pokémon.\p"
	.string "When she came back, she had a\n"
	.string "scratch on her leg!\p"
	.string "How crazy is that?\p"
	.string "Now I've dedicated my life to\n"
	.string "safeguarding the town from Pokémon.$"

CelantoTown_EventScript_CelantoPathGuardTrigger::
	lock
	applymovement LOCALID_CELANTO_PATH_GUARD, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_CELANTO_PATH_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CELANTO_PATH_GUARD, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_Text_YouCantGoOutThere, MSGBOX_AUTOCLOSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight
	waitmovement 0
	release
	end

CelantoTown_Text_YouCantGoOutThere:
	.string "{COLOR BLUE}Hey! You can't go out there\n"
	.string "without a Pokémon!\p"
	.string "It's way too dangerous!$"

CelantoTown_EventScript_RuinManiac::
	msgbox CelantoTown_Text_MyLifesDream, MSGBOX_NPC
	end

CelantoTown_Text_MyLifesDream::
	.string "My life's dream is to become an\n"
	.string "archaeologist, like Prof. Redwood!$"

CelantoTown_EventScript_Youngster::
	msgbox CelantoTown_Text_CelantoLibraryIsAwesome, MSGBOX_NPC
	end

CelantoTown_Text_CelantoLibraryIsAwesome::
	.string "The Celanto Library is awesome!\n"
	.string "I spend most my time there.$"

CelantoTown_EventScript_Rocker::
	msgbox CelantoTown_Text_TheCableCarGoesToWindmist, MSGBOX_NPC
	end

CelantoTown_Text_TheCableCarGoesToWindmist::
	.string "The Cable Car goes all the way up\n"
	.string "to Windmist City!$"

CelantoTown_EventScript_TownSign::
	msgbox CelantoTown_Text_TownSign, MSGBOX_SIGN
	end

CelantoTown_Text_TownSign::
	.string "Celanto Town\n"
	.string "Enigmas of the Past Prevail.$"

CelantoTown_EventScript_PlayersHouseSign::
	msgbox CelantoTown_Text_PlayersHouse, MSGBOX_SIGN
	end

CelantoTown_Text_PlayersHouse::
	.string "{PLAYER}'s house$"

CelantoTown_EventScript_CondominiumsSign::
	msgbox CelantoTown_Text_CondominiumsSign, MSGBOX_SIGN
	end

CelantoTown_Text_CondominiumsSign::
	.string "Celanto Condominiums$"

CelantoTown_EventScript_LibrarySign::
	msgbox CelantoTown_Text_LibrarySign, MSGBOX_SIGN
	end

CelantoTown_Text_LibrarySign::
	.string "Celanto Library\p"
	.string "Knowledge is learned,\n"
	.string "wisdom is earned.$"

CelantoTown_EventScript_MomLibrary_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto CelantoTown_EventScript_MomLibraryScene
	end

CelantoTown_EventScript_MomLibrary_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto CelantoTown_EventScript_MomLibraryScene
	end

CelantoTown_EventScript_MomLibrary_Trigger2::
	lockall
	setvar VAR_0x8008, 2
	goto CelantoTown_EventScript_MomLibraryScene
	end

CelantoTown_EventScript_MomLibraryScene:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	addobject LOCALID_MOM
	applymovement LOCALID_MOM, Common_Movement_WalkDown
	waitmovement 0
	delay 30
	playse SE_PIN
	applymovement LOCALID_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOM, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_Text_MomPlayer
	closemessage
	compare VAR_0x8008, 0
	call_if_eq CelantoTown_EventScript_MomWalkToPlayer0
	compare VAR_0x8008, 1
	call_if_eq CelantoTown_EventScript_MomWalkToPlayer1
	compare VAR_0x8008, 2
	call_if_eq CelantoTown_EventScript_MomWalkToPlayer2
	msgbox CelantoTown_Text_DidYouMeetUp
	closemessage
	applymovement LOCALID_MOM, CelantoTown_Movement_MomExit
	waitmovement 0
	removeobject LOCALID_MOM
	setflag FLAG_HIDE_CELANTO_LIBRARY_REDWOOD
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_CELANTO_TOWN_STATE, 2
	releaseall
	end
	
CelantoTown_Text_MomPlayer:
	.string "Mom: {COLOR RED}{PLAYER}!$"

CelantoTown_Text_DidYouMeetUp:
	.string "Mom: {COLOR RED}How did it go?\p"
	.string "…She said it was hers?\n"
	.string "Hm, that's strange…\p"
	.string "I realized you could have been\n"
	.string "attacked by wild Pokémon just now.\p"
	.string "Well, I've got good news.\n"
	.string "I was just in the library!\p"
	.string "The Pokémon Professor, Redwood, is\n"
	.string "giving out Pokémon to Trainers!\p"
	.string "You should go talk to him.\p"
	.string "It's about time you got your own\n"
	.string "Pokémon, wouldn't you say?\p"
	.string "{COLOR DARK_GREY}Mom: {COLOR RED}Stay safe, {PLAYER}!\n"
	.string "I love you!$"

CelantoTown_Movement_MomExit:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

CelantoTown_EventScript_MomWalkToPlayer0:
	applymovement LOCALID_MOM, CelantoTown_Movement_MomWalkToPlayer0
	waitmovement 0
	return

CelantoTown_EventScript_MomWalkToPlayer1:
	applymovement LOCALID_MOM, CelantoTown_Movement_MomWalkToPlayer1
	waitmovement 0
	return

CelantoTown_EventScript_MomWalkToPlayer2:
	applymovement LOCALID_MOM, CelantoTown_Movement_MomWalkToPlayer2
	waitmovement 0
	return

CelantoTown_Movement_MomWalkToPlayer0:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

CelantoTown_Movement_MomWalkToPlayer1:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

CelantoTown_Movement_MomWalkToPlayer2:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	step_end
