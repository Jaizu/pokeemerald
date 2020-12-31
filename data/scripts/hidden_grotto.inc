EventScript_HiddenGrottoTree::
	lock
	msgbox HiddenGrotto_Text_LookYouFoundANarrowPathWillYouFollowIt, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq EventScript_DoHiddenGrottoWarp
	release
	end

EventScript_DoHiddenGrottoWarp::
	special DoWarpAtPlayerPos
	waitstate
	release
	end

HiddenGrotto_Text_LookYouFoundANarrowPathWillYouFollowIt:
	.string "Look!\n"
	.string "You've found a narrow path!\p"
	.string "Will you follow it?$"

EventScript_EmptyChest::
	call EventScript_SetChestOpened
	msgbox HiddenGrotto_Text_ItsEmpty, MSGBOX_DEFAULT
	closemessage
	release
	end

HiddenGrotto_Text_ItsEmpty:
	.string "It's empty…$"

EventScript_OpenChest::
	msgbox HiddenGrotto_Text_PlayerOpenedUpTheChest, MSGBOX_DEFAULT
	closemessage
	playse SE_UNLOCK
	waitse
	call EventScript_SetChestOpened
	delay 10
	return

HiddenGrotto_Text_PlayerOpenedUpTheChest:
	.string "{PLAYER} opened up the chest…$"

EventScript_NoRoomChest::
	call EventScript_SetChestClosed
	goto Common_EventScript_ShowBagIsFull
	end

EventScript_SetChestOpened:
	applymovement VAR_LAST_TALKED, Common_Movement_FaceUp
	waitmovement 0
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_UP
	return

EventScript_SetChestClosed:
	applymovement VAR_LAST_TALKED, Common_Movement_FaceDown
	waitmovement 0
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_DOWN
	return
