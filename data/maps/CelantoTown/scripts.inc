.equ LOCALID_OLD_MAN, 6
.equ LOCALID_CELANTO_PATH_GUARD, 7

// TODO: Remove temporary defines:
.equ SPECIES_SHAYMIN, 0x221 // TODO: Actually add Shaymin Pokémon
.equ ITEM_GRACIDEA, 0x181   // TODO: Actually add Gracidea item

CelantoTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CelantoTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CelantoTown_OnFrame
	.byte 0

CelantoTown_OnTransition::
	setflag FLAG_VISITED_PETALBURG_CITY
	end

CelantoTown_OnFrame::
	map_script_2 VAR_POST_GAME_STATE, 2, CelantoTown_EventScript_RedwoodValorTicket
	.2byte 0

CelantoTown_EventScript_RedwoodValorTicket::
    lockall
    setvar VAR_POST_GAME_STATE, 3
	releaseall
	end

CelantoTown_EventScript_OldMan::
    lock
    faceplayer
    goto_if_set FLAG_GOT_GRACIDEA, CelantoTown_EventScript_OldManDiscussGracidea
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
	setflag FLAG_GOT_GRACIDEA
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
    goto_if_set FLAG_SYS_POKEMON_GET, CelantoTown_EventScript_CelantoPathGuardSisterStory
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
