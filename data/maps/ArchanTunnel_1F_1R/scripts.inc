.equ LOCALID_STINGA_BOY, 1

ArchanTunnel_1F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArchanTunnel_1F_1R_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ArchanTunnel_1F_1R_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, ArchanTunnel_1F_1R_OnWarp
	.byte 0

ArchanTunnel_1F_1R_OnWarp:
	map_script_2 VAR_STINGA_STATE, 1, ArchanTunnel_1F_1R_EventScript_TurnPlayerNorth
	.2byte 0

ArchanTunnel_1F_1R_OnFrame:
	map_script_2 VAR_STINGA_STATE, 1, ArchanTunnel_1F_1R_EventScript_ReturnStingaScene
	.2byte 0

ArchanTunnel_1F_1R_OnTransition:
	compare VAR_ARCHAN_TUNNEL_STATE, 1
	call_if_ge ArchanTunnel_1F_1R_EventScript_MoveStingaBoy
	end

ArchanTunnel_1F_1R_EventScript_TurnPlayerNorth:
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

ArchanTunnel_1F_1R_EventScript_ReturnStingaScene:
	lockall
	playfanfare MUS_LEVEL_UP
	message ArchanTunnel_1F_1R_Text_PlayerReturnedStinga
	waitfanfare
	waitmessage
	applymovement LOCALID_STINGA_BOY, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox ArchanTunnel_1F_1R_Text_ThankYouSoMuch, MSGBOX_DEFAULT
	giveitem ITEM_SOOTHE_BELL
	compare VAR_RESULT, FALSE
	goto_if_eq ArchanTunnel_1F_1R_EventScript_BagIsFull
	setflag FLAG_RECEIVED_STINGA_SOOTHE_BELL
	goto ArchanTunnel_1F_1R_EventScript_StingaBoyGoesHome
	end

ArchanTunnel_1F_1R_EventScript_BagIsFull:
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	msgbox ArchanTunnel_1F_1R_Text_ThatsTooBad, MSGBOX_DEFAULT
	goto ArchanTunnel_1F_1R_EventScript_StingaBoyGoesHome
	end

ArchanTunnel_1F_1R_EventScript_StingaBoyGoesHome:
	waitse
	playmoncry SPECIES_WEEDLE, 0
	msgbox Archan_Tunnel_1F_1R_Text_Stinga, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STINGA_BOY, ArchanTunnel_1F_1R_Movement_StingaBoyLeave
	waitmovement 0
	playse SE_EXIT
	waitse
	removeobject LOCALID_STINGA_BOY
	clearflag FLAG_HIDE_HOUSE_STINGA_BOY
	setflag FLAG_HIDE_ARCHAN_TUNNEL_STINGA
	clearflag FLAG_HIDE_HOUSE_STINGA
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_STINGA_STATE, 2
	releaseall
	end

ArchanTunnel_1F_1R_Text_PlayerReturnedStinga:
	.string "{PLAYER} returned Stinga\n"
	.string "to the boy!$"

ArchanTunnel_1F_1R_Text_ThankYouSoMuch:
	.string "{COLOR BLUE}Thank you so much!\p"
	.string "Sniff…\n"
	.string "I was so worried about Stinga!\p"
	.string "I know it's not much, but…\n"
	.string "I want you to have this!$"

ArchanTunnel_1F_1R_Text_ThatsTooBad:
	.string "{COLOR BLUE}That's too bad…\p"
	.string "Well, me and Stinga are going\n"
	.string "home now.\p"
	.string "It's been a very long day!\p"
	.string "Come visit us, okay?$"

Archan_Tunnel_1F_1R_Text_Stinga:
	.string "Stinga: {COLOR BLUE}Burrk!\p"
	.string "Come on Stinga, let's go home.$"

ArchanTunnel_1F_1R_Movement_StingaBoyLeave:
	walk_left
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
	
ArchanTunnel_1F_1R_EventScript_MoveStingaBoy:
	setobjectxyperm LOCALID_STINGA_BOY, 7, 2
	setobjectmovementtype LOCALID_STINGA_BOY, MOVEMENT_TYPE_FACE_DOWN
	return

ArchanTunnel_1F_1R_EventScript_StingaTrigger::
	lock
	applymovement LOCALID_STINGA_BOY, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_STINGA_BOY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STINGA_BOY, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto_if_set FLAG_ADVENTURE_STARTED, ArchanTunnel_1F_1R_EventScript_NoticesRedwoodCard
	msgbox ArchanTunnel_1F_1R_Text_NoOneIsGoingIn, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight
	waitmovement 0
	release
	end	

ArchanTunnel_1F_1R_EventScript_StingaBoy::
	lock
	faceplayer
	goto_if_set FLAG_PLEASE_FIND_STINGA, ArchanTunnel_1F_1R_EventScript_PleaseHelp
	goto_if_set FLAG_ADVENTURE_STARTED, ArchanTunnel_1F_1R_EventScript_NoticesRedwoodCard
	msgbox ArchanTunnel_1F_1R_Text_NoOneIsGoingIn, MSGBOX_DEFAULT
	release
	end
	
ArchanTunnel_1F_1R_EventScript_PleaseHelp:
	msgbox ArchanTunnel_1F_1R_Text_PleaseHelpMe, MSGBOX_DEFAULT
	release
	end

ArchanTunnel_1F_1R_EventScript_NoticesRedwoodCard:
	msgbox ArchanTunnel_1F_1R_Text_NoOneIsGoingIn, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_STINGA_BOY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STINGA_BOY, Common_Movement_Delay48
	waitmovement 0
	msgbox ArchanTunnel_1F_1R_Text_HeyThatRedwoodCard, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STINGA_BOY, ArchanTunnel_1F_1R_StingaBoyOutTheWay
	waitmovement 0
	call ArchanTunnel_1F_1R_EventScript_MoveStingaBoy
	setflag FLAG_PLEASE_FIND_STINGA
	setvar VAR_ARCHAN_TUNNEL_STATE, 1
	release
	end

ArchanTunnel_1F_1R_StingaBoyOutTheWay:
	walk_up
	walk_in_place_fastest_down
	step_end

ArchanTunnel_1F_1R_Text_PleaseHelpMe:
	.string "{COLOR BLUE}Please, help me find Stinga!$"

ArchanTunnel_1F_1R_Text_NoOneIsGoingIn:
	.string "{COLOR BLUE}I lost Stinga!\n"
	.string "He's my Weedle.\p"
	.string "We were playing in the Tunnel when\n"
	.string "the ground started shaking!\p"
	.string "When it stopped, I couldn't find\n"
	.string "him anywhere!\p"
	.string "Sniff…\n"
	.string "No-one's going in until I find him!$"

ArchanTunnel_1F_1R_Text_HeyThatRedwoodCard:
	.string "{COLOR BLUE}Hey!\n"
	.string "That Redwood Card!\p"
	.string "You're the Prof.'s aide?\n"
	.string "Then you must be a strong Trainer!\p"
	.string "Sniff…\n"
	.string "Please, find Stinga!$"
