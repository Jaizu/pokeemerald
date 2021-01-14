.ifdef DEBUG
    Debug_EventScript_SetUpFastForward::
		// PLAYER'S HOUSE 2F:
		// Obtain Dusty Tome
		setflag FLAG_HIDE_DUSTY_TOME
		// PLAYER'S HOUSE 1F:
		// Obtain Letter
		// Obtain Running Shoes
		setflag FLAG_SYS_B_DASH
		setvar VAR_PLAYERS_HOUSE_STATE, 4
		// CELANTO TOWN:
		// Set visited flag
		setflag FLAG_VISITED_CELANTO_TOWN
		// RELIQUIA RUINS:
		// Talk to Morgana, remove Letter & Dusty Tome
		setflag FLAG_HIDE_RELIQUIA_RUINS_MORGANA
		setvar VAR_RELIQUIA_RUINS_STATE, 1
		// CELANTO LIBRARY:
		// Mom tells you to visit library, access to Back of Library granted
		setflag FLAG_HIDE_CELANTO_LIBRARY_REDWOOD
		setvar VAR_CELANTO_TOWN_STATE, 2
		// BACK OF CELANTO LIBRARY:
		// Opp Gender character leaves
		setflag FLAG_HIDE_LIBRARY_BACK_ROOM_OPP_GENDER
		// Starter selection
		setflag FLAG_HIDE_TURTWIG_BALL
		setflag FLAG_HIDE_CHIMCHAR_BALL
		setflag FLAG_HIDE_PIPLUP_BALL
		setflag FLAG_SYS_POKEMON_GET
		setvar VAR_STARTER_MON, 2 // Chose Piplup
		// Redwood leaves
		setflag FLAG_HIDE_LIBRARY_BACK_ROOM_REDWOOD
		// Coulter leaves
		setflag FLAG_HIDE_LIBRARY_BACK_ROOM_COULTER
		setvar VAR_CELANTO_LIBRARY_STATE, 2
		// Access to Celanto Path granted
		setvar VAR_CELANTO_TOWN_GUARD, 1
		// CELANTO CONDIMINIUMS 2F:
        // Obtain Old Rod
		additem ITEM_OLD_ROD
		setflag FLAG_RECEIVED_OLD_ROD
		// CELANTO PATH:
		// Fight Coulter
		settrainerflag TRAINER_COULTER_CELANTO_PATH_PIPLUP
		setflag FLAG_HIDE_CELANTO_PATH_COULTER
		setvar VAR_CELANTO_PATH_STATE, 1
		// ARCHAN TOWN:
		// Set visited flag
		setflag FLAG_VISITED_ARCHAN_TOWN
		// REDWOOD RESIDENCE 1F:
		// Obtain Pokédex
		setflag FLAG_SYS_POKEDEX_GET
		special SetUnlockedPokedexFlags
		// Obtain Care Package items
		additem ITEM_REDWOOD_CARD
		additem ITEM_TOWN_MAP
		// Coulter leaves
		setflag FLAG_HIDE_REDWOOD_RESIDENCE_COULTER
		// Redwood leads you to Ancient Tablet
		setvar VAR_REDWOOD_RESIDENCE_STATE, 1
		// ARCHAN TOWN:
		// Redwood leads you to Ancient Tablet
		setflag FLAG_ADVENTURE_STARTED
		setvar VAR_ARCHAN_TOWN_STATE, 2
		// ARCHAN TUNNEL 1F 1R:
		// Please find Stinga
		setflag FLAG_PLEASE_FIND_STINGA
		// ARCHAN TUNNEL B1F 1R:
		// Fight Trainers
		settrainerflag TRAINER_LOUISE
		settrainerflag TRAINER_QUINN
		settrainerflag TRAINER_CORY
		// ARCHAN TUNNEL B2F 1R:
		// Tremor
		setvar VAR_ARCHAN_TUNNEL_STATE, 2
		// Fight Trainers
		settrainerflag TRAINER_GEORG
		settrainerflag TRAINER_BOB
		settrainerflag TRAINER_IGGY
		// Find Stinga
		setflag FLAG_HIDE_ARCHAN_TUNNEL_STINGA
		// ARCHAN TUNNEL 1F 1R:
		// Return Stinga
		setflag FLAG_HIDE_ARCHAN_TUNNEL_STINGA_BOY
		clearflag FLAG_HIDE_HOUSE_STINGA_BOY
		clearflag FLAG_HIDE_HOUSE_STINGA
		setvar VAR_STINGA_STATE, 2
		// SEROS VILLAGE:
		// Set visited flag
		setflag FLAG_VISITED_SEROS_VILLAGE
		// Meet with Redwood and Coulter
		setflag FLAG_HIDE_SEROS_VILLAGE_REDWOOD
		setflag FLAG_HIDE_SEROS_VILLAGE_COULTER
		// SEROS PATH:
		// Fight Trainers
		settrainerflag TRAINER_JENSON_1
		settrainerflag TRAINER_LANESSA_1
		// SEROS GYM:
		// Fight Trainers
		settrainerflag TRAINER_ROSE
		settrainerflag TRAINER_COURTNEY
		settrainerflag TRAINER_DAZ
		settrainerflag TRAINER_HANA
		// Fight Fernando
		settrainerflag TRAINER_FERNANDO_1
		setflag FLAG_FERNANDO_STORMED_OFF
		// SEROS VILLAGE:
		// Day-Care Man asks you to save Fernando & access granted to Wisp Forest
		setflag FLAG_HIDE_SEROS_PATH_BATTLING_TRAINERS
		// WISP FOREST:
		// Fight Trainers
		settrainerflag TRAINER_DMITRI
		settrainerflag TRAINER_SHIRO
		settrainerflag TRAINER_CADENCE
		// Rescue Fernando
		setflag FLAG_BADGE01_GET
		setflag FLAG_DEFEATED_SEROS_GYM
		setflag FLAG_HIDE_WISP_FOREST_FERNANDO
		setvar VAR_WISP_FOREST_STATE, 1
		// DAYCARE CENTER:
		// Fernando is rescued
		setflag FLAG_FERNANDO_RESCUED
		// Obtain HM01 Cut
		additem ITEM_HM01
		setflag FLAG_RECEIVED_HM01
		setvar VAR_DAY_CARE_CENTER_STATE, 2
		// SEROS VILLAGE
		// Discover entrance to Tangrowth Tablet room
		setflag FLAG_HIDE_SEROS_VILLAGE_CUT_TREE_LEFT
		setflag FLAG_HIDE_SEROS_VILLAGE_CUT_TREE_RIGHT
		setvar VAR_SEROS_VILLAGE_STATE, 4
		// TANGROWTH TABLET ROOM
		// Coulter leaves
		setflag FLAG_HIDE_COULTERS_HOUSE_COULTER
		setflag FLAG_HIDE_TANGROWTH_TABLET_ROOM_COULTER
		// Redwood leaves Seros PC
		setflag FLAG_HIDE_SEROS_POKEMON_CENTER_REDWOOD
		// Access granted to Aerous Road
		setflag FLAG_HIDE_AEROUS_ROAD_PAINTER
		setvar VAR_AEROUS_ROAD_STATE, 1
		// AEROUS ROAD
		// Fight Trainers
		settrainerflag TRAINER_HARRY_1
		settrainerflag TRAINER_PHOEBE_1
		settrainerflag TRAINER_MICHAEL_1
		settrainerflag TRAINER_LISA_AND_LOIS_1
		settrainerflag TRAINER_SPENCER_1
		settrainerflag TRAINER_JON_1
		settrainerflag TRAINER_ARTHUR_1
		// AEROUS CITY
		// Set visited flag
		setflag FLAG_VISITED_AEROUS_CITY
		// Fight Museum Clerk
		settrainerflag TRAINER_MUSEUM_CLERK
		setflag FLAG_HIDE_AEROUS_CITY_MUSEUM_CLERK
		// MUSEUM 1F
		// Fight Grunt
		settrainerflag TRAINER_MUSEUM_GRUNT_1
		// MUSEUM 2F
		// Fight Trainers
		settrainerflag TRAINER_MUSEUM_GRUNT_2
		settrainerflag TRAINER_MUSEUM_GRUNT_3
		// New Elders leave
		setflag FLAG_HIDE_AEROUS_MUSEUM_NEW_ELDERS
		// Herschel leaves
		setflag FLAG_HIDE_AEROUS_MUSEUM_HERSCHEL
		setvar VAR_AEROUS_MUSEUM_STATE, 1
		// AEROUS CITY
		// Leave with Herschel
		setflag FLAG_HIDE_AEROUS_CITY_HERSCHEL
		// TANGROWTH TABLET ROOM
		// Herschel leaves
		setflag FLAG_HIDE_TANGROWTH_TABLET_ROOM_HERSCHEL
		// Obtain HM06 Rock Smash
		additem ITEM_HM06
		// Redwood shows how to use it
		setflag FLAG_HIDE_TANGROWTH_TABLET_ROOM_BREAKABLE_ROCK_TOP
		setflag FLAG_HIDE_TANGROWTH_TABLET_ROOM_BREAKABLE_ROCK_BOTTOM
		// Redwood leaves
		setflag FLAG_HIDE_TANGROWTH_TABLET_ROOM_REDWOOD
		setvar VAR_ARCHAN_TUNNEL_STATE, 5
		// ARCHAN TUNNEL 1F 4R
		// Fight Haskel
		settrainerflag TRAINER_HASKEL
		// ARCHAN TUNNEL 2F 1R
		// Fight Byron
		settrainerflag TRAINER_BYRON
		// ARCHAN TUNNEL 3F 1R
		// Fight Byron
		settrainerflag TRAINER_MAKO
		// CELANTO PATH
		// Clear the Rock Smash rocks
		setflag FLAG_HIDE_CELANTO_PATH_BREAKABLE_ROCK_LEFT
		setflag FLAG_HIDE_CELANTO_PATH_BREAKABLE_ROCK_RIGHT
		// NESTPINE CLIMB
		// Fight Trainers
		settrainerflag TRAINER_MARTHA_1
		settrainerflag TRAINER_LUCY_1
		settrainerflag TRAINER_YOSHIRO
		settrainerflag TRAINER_RALPH_1
		settrainerflag TRAINER_BRETT_1
		settrainerflag TRAINER_JULY_1
		settrainerflag TRAINER_LUDWIG
		// NETAS HOUSE
		// Meet Neta
		setflag FLAG_SYS_PC_NETA
		// NESTPINE TOWN
		// Set visited flag
		setflag FLAG_VISITED_NESTPINE_TOWN
		// Fight Coulter
		settrainerflag TRAINER_COULTER_NESTPINE_TOWN_PRINPLUP
		// Obtain Exp Share
		additem ITEM_EXP_SHARE
		setflag FLAG_RECEIVED_EXP_SHARE
		// Coulter leaves
		setflag FLAG_HIDE_NESTPINE_TOWN_COULTER
		// Obtain SecretPotion
		setflag FLAG_RECEIVED_SECRET_POTION
		// ARCHAN HILLS
		// Clear the ill Psyduck
		setflag FLAG_HIDE_ARCHAN_HILLS_PSYDUCK
		// Fight Becca
		settrainerflag TRAINER_BECCA_1
		// NESTPINE GYM
		// Fight Trainers
		settrainerflag TRAINER_WILHELM
		settrainerflag TRAINER_GORDON
		settrainerflag TRAINER_PETER
		settrainerflag TRAINER_JANE
		settrainerflag TRAINER_CEDRIC
		// Fight Aria
		settrainerflag TRAINER_ARIA_1
		setflag FLAG_BADGE02_GET
		setflag FLAG_DEFEATED_NESTPINE_GYM
		// Access granted to second half of Frostbite Cave 1F 1R
		setflag FLAG_HIDE_NEW_ELDERS_GRUNT_FROSTBITE_CAVE_1F
		setflag FLAG_CLEAR_ROCKS_FROSTBITE_CAVE_1F
		// FROSTBITE CAVE 1F 1R
		// Fight Trainers
		settrainerflag TRAINER_MORTON
		settrainerflag TRAINER_FINLEY
		settrainerflag TRAINER_FROSTBITE_CAVE_GRUNT_1
		settrainerflag TRAINER_FROSTBITE_CAVE_GRUNT_2
		// FROSTBITE CAVE 2F 1R
		// Eunice cutscene
		setflag FLAG_HIDE_FROSTBITE_CAVE_2F_1R_EUNICE
		setflag FLAG_HIDE_FROSTBITE_CAVE_2F_1R_GRUNT
		// FROSTBITE CAVE 3F 1R
		// Fight Trainers
		settrainerflag TRAINER_FROSTBITE_CAVE_GRUNT_3
		settrainerflag TRAINER_FROSTBITE_CAVE_GRUNT_4
		// Obtain Itemfinder
		additem ITEM_ITEMFINDER
		setflag FLAG_ITEM_FROSTBITE_CAVE_ITEMFINDER
		// FROSTBITE CAVE 4F 1R
		// Fight Grunt
		settrainerflag TRAINER_FROSTBITE_CAVE_GRUNT_5
		// Fight Eunice
		settrainerflag TRAINER_FROSTBITE_CAVE_EUNICE
		// New Elders leave
		setflag FLAG_HIDE_ALL_FROSTBITE_CAVE_NEW_ELDERS
		setvar VAR_FROSTBITE_CAVE_STATE, 3
		// WINDMIST CITY
		// Set visited flag
		setflag FLAG_VISITED_WINDMIST_CITY
		// WINDMIST SUMMIT
		// Fight Trainers
		settrainerflag TRAINER_BRODY_1
		settrainerflag TRAINER_MARCAS_1
		settrainerflag TRAINER_HARLEIGH_1
		settrainerflag TRAINER_DAVINA_1
		settrainerflag TRAINER_BRANDON_1
		settrainerflag TRAINER_OLYMPIA_1
		// Meet with Coulter
		setvar VAR_WINDMIST_SUMMIT_STATE, 1
		// IGNIS ROOST
		// Fight Trainers
		settrainerflag TRAINER_IGNIS_ROOST_GRUNT_1
		settrainerflag TRAINER_IGNIS_ROOST_GRUNT_2
		settrainerflag TRAINER_IGNIS_ROOST_GRUNT_3
		// Meet with Coulter
		setvar VAR_IGNIS_ROOST_STATE, 1
		// APEX TEMPLE
		// Fight Trainers
		settrainerflag TRAINER_APEX_TEMPLE_GRUNT_1
		settrainerflag TRAINER_APEX_TEMPLE_GRUNT_2
		settrainerflag TRAINER_APEX_TEMPLE_GRUNTS
		// The New Elders leave
		setflag FLAG_HIDE_APEX_TEMPLE_ENOCH_AND_GRUNTS
		setflag FLAG_HIDE_IGNIS_ROOST_GRUNTS
		// Leave with Coulter & the book
		setflag FLAG_HIDE_IGNIS_ROOST_COULTER
		setflag FLAG_HIDE_APEX_TEMPLE_COULTER
		setflag FLAG_HIDE_APEX_TEMPLE_BOOK
		setvar VAR_APEX_TEMPLE_STATE, 1
		// WINDMIST CITY POKEMON CENTER
		// Meet with Coulter & Redwood
		setvar VAR_WINDMIST_CITY_POKEMON_CENTER_STATE, 2
		// Unlock the Windmist Gym
		setflag FLAG_UNLOCK_WINDMIST_GYM_DOOR
		// WINDMIST GYM
		// Fight Trainers
		settrainerflag TRAINER_HECTOR
		settrainerflag TRAINER_ANGELICA
		settrainerflag TRAINER_JUNIOR
		// Complete the puzzle
		setvar VAR_WINDMIST_GYM_STATE, 3
		// Fight Nina
		settrainerflag TRAINER_NINA_1
		setflag FLAG_BADGE03_GET
		setflag FLAG_DEFEATED_WINDMIST_GYM
		// WINDMIST CITY
		// Obtain the Bike Voucher from Redwood
		setvar VAR_WINDMIST_CITY_STATE, 2
		// AEROUS CITY
		// Say goodbye to Redwood
		setvar VAR_AEROUS_CITY_STATE, 2
		// Exchange Bike Voucher for Bicycle
		setflag FLAG_RECEIVED_BIKE
		additem ITEM_BICYCLE
		// AEROUS PORT
		// Fight Braveton
		settrainerflag TRAINER_BRAVETON
		// The SS Wake arrives
		clearflag FLAG_HIDE_AEROUS_CITY_PORT_SS_WAKE
		// SABULO ISLAND
		// Set visited flag
		setflag FLAG_VISITED_SABULO_ISLAND
		// SABULO CROSS
		// Fight Joanna
		settrainerflag TRAINER_JOANNA_1
		// SABULO TOWER
		// Fight Trainers
		settrainerflag TRAINER_NIKOLAI
		settrainerflag TRAINER_MAYA
		settrainerflag TRAINER_JAIME
		settrainerflag TRAINER_MIKEL
		settrainerflag TRAINER_AGEM
		// Fight Belle
		settrainerflag TRAINER_BELLE_1
		// Obtain Mega Ring
		additem ITEM_MEGA_RING
		setflag FLAG_RECEIVED_MEGA_RING
		// Belle leaves
		setflag FLAG_HIDE_SABULO_TOWER_6F_2R_BELLE
		// SABULO ISLAND
		// Regirock cutscene, Sabulo Cave guard flees
		setflag FLAG_HIDE_SABULO_ISLAND_SABULO_CAVE_GUARD
		// Fight the New Elders
		settrainerflag TRAINER_SABULO_ISLAND_GRUNT_1
		settrainerflag TRAINER_SABULO_ISLAND_GRUNT_2
		settrainerflag TRAINER_SABULO_ISLAND_ENOCH
		// SABULO CAVE
		// Obtain Ragged Map item
		// TODO: Add Ragged Map item
		// additem ITEM_RAGGED_MAP
		setflag FLAG_ITEM_SABULO_CAVE_RAGGED_MAP
		// Obtain HM03 from Coulter
		additem ITEM_HM03
		// SABULO ISLAND
		// Receive Kanto starter from Belle
		setflag FLAG_DIDNT_RECEIVE_KANTO_STARTER
		setvar VAR_SABULO_TOWER_STATE, 3
		setvar VAR_SABULO_ISLAND_STATE, 5
		// SABULO CROSS
		// Fight Trainers
		settrainerflag TRAINER_FELIX_1
		settrainerflag TRAINER_ESTEBAN_1
		settrainerflag TRAINER_KRISTOFF_1
		settrainerflag TRAINER_STEPHAN_1
		settrainerflag TRAINER_CELESTE_1
		// SHARPGUST SPAN
		// Fight Trainers
		settrainerflag TRAINER_MAYA_AND_DAVE_1
		settrainerflag TRAINER_PEGGY_1
		// VALOON WAY
		// Fight Trainers
		settrainerflag TRAINER_NATASHA_1
		settrainerflag TRAINER_HANS_1
		settrainerflag TRAINER_OLIVIA
		// Tremor scene
		setvar VAR_VALOON_WAY_STATE, 1
		// Fight Trainers
		settrainerflag TRAINER_ERIC_1
		settrainerflag TRAINER_DOUG_1
		settrainerflag TRAINER_SAMMY_1
		settrainerflag TRAINER_COLTON_1
		// VALOON TOWN
		// Set visited flag
		setflag FLAG_VISITED_VALOON_TOWN
		// Rangers leaving for Nemesis Cave scene
		setflag FLAG_HIDE_VALOON_TOWN_PKMN_RANGERS
		setflag FLAG_HIDE_VALOON_TOWN_PKMN_RANGER_1
		setvar VAR_VALOON_TOWN_STATE, 1
		// NEMESIS RIVER
		// Fight Trainers
		settrainerflag TRAINER_WENDY_1
		// NEMESIS CAVE
		// Fight Trainers
		settrainerflag TRAINER_AMALIA
		settrainerflag TRAINER_KOICHI
		settrainerflag TRAINER_MARLON
		settrainerflag TRAINER_INGRID
		settrainerflag TRAINER_HIDEKI
		// Discover the Lileep Tablet
		setflag FLAG_HIDE_NEMESIS_CAVE_PKMN_RANGER_M
		setflag FLAG_HIDE_NEMESIS_CAVE_PKMN_RANGERS
		setflag FLAG_NEMESIS_CAVE_RANGERS_RETURNED
		clearflag FLAG_HIDE_VALOON_TOWN_PKMN_RANGER_1
		clearflag FLAG_HIDE_VALOON_TOWN_HOUSE_1_PKMN_RANGER_M
		// NEMESIS RIVER
		// Ezekiel scene
		setvar VAR_NEMESIS_RIVER_STATE, 2
		// VALOON RESERVE
		// Player enters the compulsory Bug-Catching Contest
		// setflag FLAG_UNLOCK_VALOON_GYM_DOOR
		end
	
	Debug_EventScript_GetParty::
		givemon SPECIES_GALVANTULA, 36, ITEM_NONE
		givemon SPECIES_EXCADRILL, 36, ITEM_NONE
		givemon SPECIES_CHARIZARD, 36, ITEM_CHARIZARDITE_Y
		givemon SPECIES_EMPOLEON, 36, ITEM_NONE
		end
	
	Debug_EventScript_GetItems::
		additem ITEM_FULL_RESTORE, 99
		additem ITEM_MAX_REVIVE, 99
		additem ITEM_MAX_REPEL, 99
		additem ITEM_MASTER_BALL, 99
		end
.endif
