.set LOCALID_GUARD, 1

ValoonTown_Gatehouse_1F_MapScripts::
	.byte 0

ValoonTown_Gatehouse_1F_EventScript_Guard::
	lock
	faceplayer
	msgbox ValoonTown_Gatehouse_1F_Text_TheNoxiousGases, MSGBOX_DEFAULT
	release
	end

ValoonTown_Gatehouse_1F_Text_TheNoxiousGases:
	.string "The noxious gases in Telmurk\n"
	.string "Swamp are at record levels!\p"
	.string "It's not safe to go there without\n"
	.string "a Gas Mask.$"

ValoonTown_Gatehouse_1F_EventScript_Roadblock::
	lockall
	textcolor 0 // Blue
	applymovement LOCALID_GUARD, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox ValoonTown_Gatehouse_1F_Text_HeyYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	getplayerxy VAR_0x8008, VAR_0x8009
	compare VAR_0x8009, 6
	call_if_gt ValoonTown_Gatehouse_1F_EventScript_CutToGuard
	msgbox ValoonTown_Gatehouse_1F_Text_TheNoxiousGases, MSGBOX_DEFAULT
	msgbox ValoonTown_Gatehouse_1F_Text_SorryKid, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8009, 6
	call_if_gt ValoonTown_Gatehouse_1F_EventScript_ReturnToPlayer
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft
	waitmovement 0
	release
	end

ValoonTown_Gatehouse_1F_EventScript_CutToGuard:
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004,  6 @ x
	setvar VAR_0x8005,  2 @ y
	special TeleportCamera
	fadescreen FADE_FROM_BLACK
	return

ValoonTown_Gatehouse_1F_EventScript_ReturnToPlayer:
	fadescreen FADE_TO_BLACK
	special ReturnCameraToPlayer
	fadescreen FADE_FROM_BLACK
	return

ValoonTown_Gatehouse_1F_Text_HeyYou:
	.string "Hey, you!$"

ValoonTown_Gatehouse_1F_Text_SorryKid:
	.string "Sorry, kid, I can't let you pass.$"
