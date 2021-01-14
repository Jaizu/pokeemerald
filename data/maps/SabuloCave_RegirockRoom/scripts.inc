.set LOCALID_COULTER, 3

SabuloCave_RegirockRoom_MapScripts::
	.byte 0

SabuloCave_RegirockRoom_EventScript_RaggedMap::
	textcolor 2 // Dark Grey
	finditem ITEM_RAGGED_MAP
	delay 10
	playse SE_EXIT
	addobject LOCALID_COULTER
	waitse
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	getplayerxy VAR_0x8008, VAR_0x8009
	compare VAR_0x8008, 7
	call_if_eq SabuloCave_RegirockRoom_EventScript_WalkCoulterToPlayer0
	compare VAR_0x8009, 6
	call_if_eq SabuloCave_RegirockRoom_EventScript_WalkCoulterToPlayer1
	compare VAR_0x8009, 8
	call_if_eq SabuloCave_RegirockRoom_EventScript_WalkCoulterToPlayer2
	compare VAR_0x8008, 9
	call_if_eq SabuloCave_RegirockRoom_EventScript_WalkCoulterToPlayer3
	msgbox SabuloCave_RegirockRoom_Text_PlayerAreYouAlright, MSGBOX_DEFAULT
	delay 10
	playse SE_PIN
	applymovement LOCALID_COULTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_COULTER, Common_Movement_Delay48
	waitmovement 0
	msgbox SabuloCave_RegirockRoom_Text_LookTheresACross, MSGBOX_DEFAULT
	giveitem ITEM_HM03
	msgbox SabuloCave_RegirockRoom_Text_TheRaceContinues, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	compare VAR_0x8009, 8
	call_if_ne SabuloCave_RegirockRoom_EventScript_ExitCoulter0
	compare VAR_0x8009, 8
	call_if_eq SabuloCave_RegirockRoom_EventScript_ExitCoulter1
	playse SE_EXIT
	removeobject LOCALID_COULTER
	waitse
	fadedefaultbgm
	setvar VAR_SABULO_ISLAND_STATE, 4
	end

SabuloCave_RegirockRoom_EventScript_WalkCoulterToPlayer0:
	applymovement LOCALID_COULTER, SabuloCave_RegirockRoom_Movement_WalkCoulterToPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

SabuloCave_RegirockRoom_EventScript_WalkCoulterToPlayer1:
	applymovement LOCALID_COULTER, SabuloCave_RegirockRoom_Movement_WalkCoulterToPlayer1
	waitmovement 0
	return

SabuloCave_RegirockRoom_EventScript_WalkCoulterToPlayer2:
	applymovement LOCALID_COULTER, SabuloCave_RegirockRoom_Movement_WalkCoulterToPlayer2
	waitmovement 0
	return

SabuloCave_RegirockRoom_EventScript_WalkCoulterToPlayer3:
	applymovement LOCALID_COULTER, SabuloCave_RegirockRoom_Movement_WalkCoulterToPlayer3
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

SabuloCave_RegirockRoom_EventScript_ExitCoulter0:
	applymovement LOCALID_COULTER, SabuloCave_RegirockRoom_Movement_ExitCoulter0
	waitmovement 0
	return

SabuloCave_RegirockRoom_EventScript_ExitCoulter1:
	applymovement LOCALID_COULTER, SabuloCave_RegirockRoom_Movement_ExitCoulter1
	waitmovement 0
	return

SabuloCave_RegirockRoom_Text_PlayerAreYouAlright:
	.string "{RIVAL}: {COLOR BLUE}{PLAYER}!\n"
	.string "Are you alright?!\p"
	.string "I saw everything!\p"
	.string "Err…\n"
	.string "I would have helped, but…\p"
	.string "Well, it's embarrassing, but I\n"
	.string "just got my butt kicked by Belle!\p"
	.string "Anyway, that's besides the point!\n"
	.string "You were amazing!\p"
	.string "Those New Elders really mean\n"
	.string "business, eh?\p"
	.string "…What is that, a map?\n"
	.string "Let me have a look at that…$"

SabuloCave_RegirockRoom_Text_LookTheresACross:
	.string "{RIVAL}: {COLOR BLUE}Look!\n"
	.string "There's a red cross on the map!\p"
	.string "That must be where they're\n"
	.string "headed next.\p"
	.string "I hate to say it, but I think we\n"
	.string "should follow them.\p"
	.string "I think they know something about\n"
	.string "the tremors that we don't!\p"
	.string "That must be why we keep bumping\n"
	.string "into them, right?\p"
	.string "They're headed southeast of here,\n"
	.string "so I guess we need to {COLOR GREEN}Surf{COLOR BLUE}!\p"
	.string "Well, today's your lucky day!$"

SabuloCave_RegirockRoom_Text_TheRaceContinues:
	.string "{RIVAL}: {COLOR BLUE}The race continues!\n"
	.string "The next Gym's in {COLOR GREEN}Valoon Town{COLOR BLUE}.\p"
	.string "I'm definitely going to get the\n"
	.string "Badge before you, Slowpoke!\p"
	.string "Peace!$"

SabuloCave_RegirockRoom_Movement_WalkCoulterToPlayer0:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_left
	step_end

SabuloCave_RegirockRoom_Movement_WalkCoulterToPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SabuloCave_RegirockRoom_Movement_WalkCoulterToPlayer2:
	walk_up
	walk_up
	walk_up
	step_end

SabuloCave_RegirockRoom_Movement_WalkCoulterToPlayer3:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_right
	step_end

SabuloCave_RegirockRoom_Movement_ExitCoulter0:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_down
	step_end

SabuloCave_RegirockRoom_Movement_ExitCoulter1:
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_down
	step_end
