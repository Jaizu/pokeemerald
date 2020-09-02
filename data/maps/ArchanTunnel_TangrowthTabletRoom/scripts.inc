.equ LOCALID_REDWOOD, 3
.equ LOCALID_COULTER, 4

ArchanTunnel_TangrowthTabletRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArchanTunnel_TangrowthTabletRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ArchanTunnel_TangrowthTabletRoom_OnFrame
	.byte 0

ArchanTunnel_TangrowthTabletRoom_OnTransition:
	compare VAR_ARCHAN_TUNNEL_STATE, 2
	call_if_eq ArchanTunnel_TangrowthTabletRoom_MoveRedwoodToSouthWall
	end

ArchanTunnel_TangrowthTabletRoom_MoveRedwoodToSouthWall:
	setobjectxyperm LOCALID_REDWOOD, 6, 10
	return

ArchanTunnel_TangrowthTabletRoom_OnFrame:
	map_script_2 VAR_ARCHAN_TUNNEL_STATE, 2, ArchanTunnel_TangrowthTabletRoom_EventScript_TabletDiscoveryScene
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
	applymovement LOCALID_REDWOOD, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	fadedefaultbgm
	setobjectxyperm LOCALID_REDWOOD, 6, 4
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
