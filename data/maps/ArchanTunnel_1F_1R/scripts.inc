.equ LOCALID_STINGA_BOY, 1

ArchanTunnel_1F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArchanTunnel_1F_1R_OnTransition
	.byte 0

ArchanTunnel_1F_1R_OnTransition::
	compare VAR_ARCHAN_TUNNEL_STATE, 1
	call_if_eq ArchanTunnel_1F_1R_EventScript_MoveStingaBoy
	end

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
