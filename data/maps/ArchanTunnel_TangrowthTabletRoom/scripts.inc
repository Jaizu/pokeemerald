.equ LOCALID_REDWOOD, 3
.equ LOCALID_COULTER, 4
.equ LOCALID_HERSCHEL, 5
.equ LOCALID_TOP_ROCK, 1
.equ LOCALID_BOTTOM_ROCK, 2

ArchanTunnel_TangrowthTabletRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArchanTunnel_TangrowthTabletRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ArchanTunnel_TangrowthTabletRoom_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, ArchanTunnel_TangrowthTabletRoom_OnWarp
	.byte 0

ArchanTunnel_TangrowthTabletRoom_OnTransition:
	compare VAR_ARCHAN_TUNNEL_STATE, 2
	call_if_eq ArchanTunnel_TangrowthTabletRoom_MoveRedwoodToSouthWall
	end

ArchanTunnel_TangrowthTabletRoom_MoveRedwoodToSouthWall:
	setobjectxyperm LOCALID_REDWOOD, 6, 10
	return

ArchanTunnel_TangrowthTabletRoom_OnWarp:
	map_script_2 VAR_ARCHAN_TUNNEL_STATE, 4, ArchanTunnel_TangrowthTabletRoom_EventScript_PlayerTurnNorthRedwoodTurnWest
	.2byte 0

ArchanTunnel_TangrowthTabletRoom_EventScript_PlayerTurnNorthRedwoodTurnWest::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	turnobject LOCALID_REDWOOD, DIR_WEST
	end

ArchanTunnel_TangrowthTabletRoom_OnFrame:
	map_script_2 VAR_ARCHAN_TUNNEL_STATE, 2, ArchanTunnel_TangrowthTabletRoom_EventScript_TabletDiscoveryScene
	map_script_2 VAR_ARCHAN_TUNNEL_STATE, 4, ArchanTunnel_TangrowthTabletRoom_EventScript_HerschelTranslationScene
	.2byte 0

ArchanTunnel_TangrowthTabletRoom_EventScript_TabletDiscoveryScene:
	lockall
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_WhoaHowHaveINeverFoundThisBefore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, ArchanTunnel_TangrowthTabletRoom_Movement_RedwoodWalkToTablet
	applymovement LOCALID_COULTER, ArchanTunnel_TangrowthTabletRoom_Movement_CoulterWalkToTablet
	applymovement OBJ_EVENT_ID_PLAYER, ArchanTunnel_TangrowthTabletRoom_Movement_PlayerWalkToTablet
	waitmovement 0
	delay 32
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 5
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_Fascinating, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 32
	playse SE_PIN
	applymovement LOCALID_REDWOOD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_REDWOOD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_TheseGlyphsAtTheBase, MSGBOX_DEFAULT
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 5
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_AlrightPlayer, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL2, 0
	applymovement LOCALID_COULTER, ArchanTunnel_TangrowthTabletRoom_Movement_ExitCoulter
	waitmovement 0
	playse SE_KAIDAN
	waitse
	removeobject LOCALID_COULTER
	setflag FLAG_HIDE_COULTERS_HOUSE_COULTER
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	fadedefaultbgm
	setobjectxyperm LOCALID_REDWOOD, 6, 4
	setflag FLAG_HIDE_SEROS_POKEMON_CENTER_REDWOOD
	setflag FLAG_HIDE_SEROS_VILLAGE_CUT_TREE_LEFT
	setflag FLAG_HIDE_SEROS_VILLAGE_CUT_TREE_RIGHT
	setflag FLAG_HIDE_AEROUS_ROAD_PAINTER
	setvar VAR_AEROUS_ROAD_STATE, 1
	setvar VAR_ARCHAN_TUNNEL_STATE, 3
	releaseall
	end

ArchanTunnel_TangrowthTabletRoom_Text_WhoaHowHaveINeverFoundThisBefore:
	.string "{RIVAL}: {COLOR BLUE}Whoa…\n"
	.string "How have I never found this before?$"

ArchanTunnel_TangrowthTabletRoom_Text_Fascinating:
	.string "Redwood: {COLOR BLUE}Fascinating!\n"
	.string "My hypothesis may yet be proven!\p"
	.string "Oh…?$"

ArchanTunnel_TangrowthTabletRoom_Text_TheseGlyphsAtTheBase:
	.string "Redwood: {COLOR BLUE}These glyphs at\n"
	.string "the base seem familiar…\p"
	.string "Ah!\n"
	.string "I remember now!\p"
	.string "An old friend of mine used to\n"
	.string "study this language.\p"
	.string "His name is {COLOR GREEN}Herschel{COLOR BLUE}.\n"
	.string "He's a Pokémon Trainer, too!\p"
	.string "If we're going to translate this\n"
	.string "tablet, we'll certainly need him.\p"
	.string "Last I heard, he was headed to\n"
	.string "{COLOR GREEN}Aerous City's Museum{COLOR BLUE}.\p"
	.string "The two of you should go and find\n"
	.string "him!$"

ArchanTunnel_TangrowthTabletRoom_Text_AlrightPlayer:
	.string "{RIVAL}: {COLOR BLUE}Alright, {PLAYER}!\n"
	.string "I guess you won this race, huh?\p"
	.string "Well, I'll get to Aerous City\n"
	.string "first, for sure!$"

ArchanTunnel_TangrowthTabletRoom_Movement_RedwoodWalkToTablet:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

ArchanTunnel_TangrowthTabletRoom_Movement_CoulterWalkToTablet:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

ArchanTunnel_TangrowthTabletRoom_Movement_PlayerWalkToTablet:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

ArchanTunnel_TangrowthTabletRoom_Movement_ExitCoulter:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_down
	set_invisible
	step_end

ArchanTunnel_TangrowthTabletRoom_EventScript_HerschelTranslationScene::
	lockall
	setescapewarp MAP_SEROS_VILLAGE, -1, 15, 6
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_CharlesItsGreatToSeeYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HERSCHEL, Common_Movement_WalkUp
	waitmovement 0
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_HmmThisIsQuiteCryptic, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_HERSCHEL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_HERSCHEL, Common_Movement_Delay48
	waitmovement 0
	delay 10
	applymovement LOCALID_HERSCHEL, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	fadenewbgm MUS_MABOROSI
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_AhThisCertainlyAlludesToApexTemple, MSGBOX_DEFAULT
	closemessage
	delay 10
	playse SE_PIN
	applymovement LOCALID_REDWOOD, Common_Movement_ExclamationMark
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement LOCALID_REDWOOD, Common_Movement_Delay48
	waitmovement 0
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_TheTempleAtThePeakOfMtIgnis, MSGBOX_DEFAULT
	fadedefaultbgm
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_PlayerTheMysteryUnfolds, MSGBOX_DEFAULT
	giveitem ITEM_HM06
	closemessage
	delay 10
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_HerschelItHasBeenAPleasure, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HERSCHEL, ArchanTunnel_TangrowthTabletRoom_Movement_ExitHerschel
	waitmovement 0
	playse SE_KAIDAN
	waitse
	removeobject LOCALID_HERSCHEL
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_LetMeShowYouHowToUseRockSmash, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, ArchanTunnel_TangrowthTabletRoom_Movement_RedwoodWalkToBreakableRocks
	applymovement OBJ_EVENT_ID_PLAYER, ArchanTunnel_TangrowthTabletRoom_Movement_PlayerFollowRedwoodToBreakableRocks
	waitmovement 0
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 10
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceRight
	waitmovement 0
	playse SE_W088
	applymovement LOCALID_TOP_ROCK, Movement_SmashRock
	waitmovement 0
	removeobject LOCALID_TOP_ROCK
	waitse
	delay 10
	applymovement LOCALID_REDWOOD, Common_Movement_WalkDown
	waitmovement 0
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 10
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceRight
	waitmovement 0
	playse SE_W088
	applymovement LOCALID_BOTTOM_ROCK, Movement_SmashRock
	waitmovement 0
	removeobject LOCALID_BOTTOM_ROCK
	waitse
	delay 10
	applymovement LOCALID_REDWOOD, ArchanTunnel_TangrowthTabletRoom_Movement_RedwoodWalkBackToPlayer
	waitmovement 0
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_SimpleRight, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, ArchanTunnel_TangrowthTabletRoom_Movement_ExitRedwood
	waitmovement 0
	playse SE_KAIDAN
	waitse
	removeobject LOCALID_REDWOOD
	setvar VAR_ARCHAN_TUNNEL_STATE, 5
	releaseall
	end

ArchanTunnel_TangrowthTabletRoom_Text_CharlesItsGreatToSeeYou:
	.string "Herschel: {COLOR BLUE}Charles!\n"
	.string "It is great to see you.\p"
	.string "I see you have discovered another\n"
	.string "tablet!$"

ArchanTunnel_TangrowthTabletRoom_Text_HmmThisIsQuiteCryptic:
	.string "Herschel: {COLOR BLUE}Hmm…\n"
	.string "This is quite cryptic.\p"
	.string "The glyphs don't seem to translate\n"
	.string "directly, but.{PAUSE 0x30}.{PAUSE 0x30}.{PAUSE 0x30}$"

ArchanTunnel_TangrowthTabletRoom_Text_AhThisCertainlyAlludesToApexTemple:
	.string "Herschel: {COLOR BLUE}Ah! This certainly\n"
	.string "alludes to {COLOR GREEN}Apex Temple{COLOR BLUE}.$"

ArchanTunnel_TangrowthTabletRoom_Text_TheTempleAtThePeakOfMtIgnis:
	.string "Redwood: {COLOR BLUE}The temple at the\n"
	.string "peak of Mt. Ignis?\p"
	.string "{COLOR DARK_GREY}Herschel: {COLOR BLUE}Yes.\p"
	.string "As you know, I've studied the\n"
	.string "Elders of Orbtus quite closely.\p"
	.string "Apex Temple was built by the\n"
	.string "Elders of Orbtus as a shrine.\p"
	.string "It was a place where they stored\n"
	.string "their knowledge of the land.\p"
	.string "Its location, {COLOR GREEN}Ignis Roost{COLOR BLUE}, is\n"
	.string "the highest peak of the region.\p"
	.string "The Temple was built to symbolize\n"
	.string "their love and reverence of nature.\p"
	.string "{COLOR DARK_GREY}Prof. Redwood: {COLOR BLUE}Hmm…\p"
	.string "The Elders of Orbtus were wiped\n"
	.string "out by earthquakes not unlike\l"
	.string "the tremors we're seeing today…\p"
	.string "Maybe the Temple will have some\n"
	.string "info that could help us!$"

ArchanTunnel_TangrowthTabletRoom_Text_PlayerTheMysteryUnfolds:
	.string "Redwood: {COLOR BLUE}{PLAYER}!\p"
	.string "The mystery unfolds!\n"
	.string "How exciting.\p"
	.string "You should head to {COLOR GREEN}Apex Temple{COLOR BLUE}.\n"
	.string "This means climbing Mt. Ignis!\p"
	.string "This HM may help you in your\n"
	.string "travels.\p"
	.string "It's {COLOR GREEN}HM06 Rock Smash{COLOR BLUE}.$"

ArchanTunnel_TangrowthTabletRoom_Text_HerschelItHasBeenAPleasure:
	.string "Redwood: {COLOR BLUE}Herschel, it has\n"
	.string "been a pleasure, like always.\p"
	.string "Thanks for your help!\p"
	.string "{COLOR DARK_GREY}Herschel: {COLOR BLUE}Any time, my dear\n"
	.string "friend.\p"
	.string "I'm afraid I must leave now,\n"
	.string "though.\p"
	.string "Farewell Charles, and… er…\n"
	.string "Trainer!$"

ArchanTunnel_TangrowthTabletRoom_Text_LetMeShowYouHowToUseRockSmash:
	.string "Redwood: {COLOR BLUE}Let me show you\n"
	.string "how to use Rock Smash.\p"
	.string "Follow me, {PLAYER}!$"

ArchanTunnel_TangrowthTabletRoom_Text_SimpleRight:
	.string "Redwood: {COLOR BLUE}Simple, right?\p"
	.string "That path should continue on to\n"
	.string "{COLOR GREEN}Nestpine Climb{COLOR BLUE}.\p"
	.string "I'll go tell {RIVAL}\n"
	.string "where to head next.\p"
	.string "Good luck, {PLAYER}!$"

ArchanTunnel_TangrowthTabletRoom_Movement_ExitHerschel:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

ArchanTunnel_TangrowthTabletRoom_Movement_RedwoodWalkToBreakableRocks:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	step_end

ArchanTunnel_TangrowthTabletRoom_Movement_PlayerFollowRedwoodToBreakableRocks:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_right
	step_end

ArchanTunnel_TangrowthTabletRoom_Movement_RedwoodWalkBackToPlayer:
	walk_up
	walk_left
	step_end

ArchanTunnel_TangrowthTabletRoom_Movement_ExitRedwood:
	walk_down
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end

ArchanTunnel_TangrowthTabletRoom_EventScript_Redwood::
	lock
	faceplayer
	msgbox ArchanTunnel_TangrowthTabletRoom_Text_HerschelShouldBeAtAerousMuseum, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ArchanTunnel_TangrowthTabletRoom_Text_HerschelShouldBeAtAerousMuseum:
	.string "{COLOR DARK_GREY}Redwood: {COLOR BLUE}Herschel should be at the\n"
	.string "Aerous Museum.\p"
	.string "Hopefully, with his assistance, we\n"
	.string "can translate this tablet!$"
