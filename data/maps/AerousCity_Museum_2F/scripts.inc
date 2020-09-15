.equ LOCALID_HERSCHEL, 3
.equ LOCALID_EUNICE, 4
.equ LOCALID_GRUNT_1, 1
.equ LOCALID_GRUNT_2, 2
.equ LOCALID_GRUNT_3, 5

AerousCity_Museum_2F_MapScripts::
	.byte 0

AerousCity_Museum_2F_EventScript_Grunt1::
	trainerbattle_single TRAINER_MUSEUM_GRUNT_2, AerousCity_Museum_2F_Text_Grunt1Intro, AerousCity_Museum_2F_Text_Grunt1Defeated
	msgbox AerousCity_Museum_2F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

AerousCity_Museum_2F_Text_Grunt1Intro:
	.string "How did you get up here?$"

AerousCity_Museum_2F_Text_Grunt1Defeated:
	.string "I only asked…$"

AerousCity_Museum_2F_Text_Grunt1PostBattle:
	.string "We're conducting important\n"
	.string "business.\p"
	.string "It's rude to just barge in!$"

AerousCity_Museum_2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_MUSEUM_GRUNT_3, AerousCity_Museum_2F_Text_Grunt2Intro, AerousCity_Museum_2F_Text_Grunt2Defeated
	msgbox AerousCity_Museum_2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

AerousCity_Museum_2F_Text_Grunt2Intro:
	.string "Do you know who you're dealing\n"
	.string "with?\p"
	.string "We're the {COLOR GREEN}New Elders{COLOR BLUE}!$"

AerousCity_Museum_2F_Text_Grunt2Defeated:
	.string "I only lost because this is a\n"
	.string "cramped space…$"

AerousCity_Museum_2F_Text_Grunt2PostBattle:
	.string "You've got us all wrong, kid.\n"
	.string "We New Elders are a force for good!$"

AerousCity_Museum_2F_EventScript_EuniceHerschelTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto AerousCity_Museum_2F_EventScript_EuniceHerschelScene
	end

AerousCity_Museum_2F_EventScript_EuniceHerschelTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto AerousCity_Museum_2F_EventScript_EuniceHerschelScene
	end

AerousCity_Museum_2F_EventScript_EuniceHerschelTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto AerousCity_Museum_2F_EventScript_EuniceHerschelScene
	end

AerousCity_Museum_2F_EventScript_EuniceHerschelScene::
	compare VAR_0x8008, 0
	call_if_eq AerousCity_Museum_2F_EventScript_PanCameraToEunice0
	compare VAR_0x8008, 1
	call_if_eq AerousCity_Museum_2F_EventScript_PanCameraToEunice1
	compare VAR_0x8008, 2
	call_if_eq AerousCity_Museum_2F_EventScript_PanCameraToEunice2
	delay 10
	msgbox AerousCity_Museum_2F_Text_AndThatIsOurMainPriority, MSGBOX_DEFAULT
	applymovement LOCALID_HERSCHEL, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox AerousCity_Museum_2F_Text_IveAlreadyGivenYouMyAnswer, MSGBOX_DEFAULT
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox AerousCity_Museum_2F_Text_HerschelIFeelIHaveNotExplained, MSGBOX_DEFAULT
	applymovement LOCALID_GRUNT_3, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 10
	playse SE_PIN
	applymovement LOCALID_GRUNT_3, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GRUNT_3, Common_Movement_Delay48
	waitmovement 0
	delay 10
	applymovement LOCALID_GRUNT_3, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox AerousCity_Museum_2F_Text_MaamTheChildIWasTalkingAboutIsHere, MSGBOX_DEFAULT
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox AerousCity_Museum_2F_Text_DontInterrupt, MSGBOX_DEFAULT
	applymovement LOCALID_EUNICE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox AerousCity_Museum_2F_Text_ItsClearIWontBePersuadingYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EUNICE, AerousCity_Museum_2F_Movement_ExitEunice
	applymovement LOCALID_GRUNT_3, AerousCity_Museum_2F_Movement_ExitGrunt3
	delay 15
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_EUNICE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight
	waitmovement 0
	special RemoveCameraObject
	fadescreen FADE_FROM_BLACK
	delay 10
	compare VAR_0x8008, 0
	call_if_eq AerousCity_Museum_2F_EventScript_PanCameraWalkHerschelToPlayer0
	compare VAR_0x8008, 1
	call_if_eq AerousCity_Museum_2F_EventScript_PanCameraWalkHerschelToPlayer1
	compare VAR_0x8008, 2
	call_if_eq AerousCity_Museum_2F_EventScript_PanCameraWalkHerschelToPlayer2
	msgbox AerousCity_Museum_2F_Text_OhGoodDayChild, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_HERSCHEL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_HERSCHEL, Common_Movement_Delay48
	waitmovement 0
	msgbox AerousCity_Museum_2F_Text_IsThatARedwoodCard, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq AerousCity_Museum_2F_EventScript_ExitHerschel0
	compare VAR_0x8008, 1
	call_if_eq AerousCity_Museum_2F_EventScript_ExitHerschel1
	compare VAR_0x8008, 2
	call_if_eq AerousCity_Museum_2F_EventScript_ExitHerschel2
	removeobject LOCALID_HERSCHEL
	clearflag FLAG_HIDE_AEROUS_CITY_HERSCHEL
	setvar VAR_AEROUS_MUSEUM_STATE, 1
	releaseall
	end

AerousCity_Museum_2F_EventScript_PanCameraToEunice0:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, AerousCity_Museum_2F_Movement_PanCameraToEunice0
	waitmovement 0
	special RemoveCameraObject
	return

AerousCity_Museum_2F_EventScript_PanCameraToEunice1:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, AerousCity_Museum_2F_Movement_PanCameraToEunice1
	waitmovement 0
	special RemoveCameraObject
	return

AerousCity_Museum_2F_EventScript_PanCameraToEunice2:
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, AerousCity_Museum_2F_Movement_PanCameraToEunice2
	waitmovement 0
	special RemoveCameraObject
	return

AerousCity_Museum_2F_EventScript_PanCameraWalkHerschelToPlayer0:
	special SpawnCameraObject
	applymovement LOCALID_HERSCHEL, AerousCity_Museum_2F_Movement_WalkHerschelToPlayer0
	applymovement OBJ_EVENT_ID_CAMERA, AerousCity_Museum_2F_Movement_PanCameraToPlayer0
	waitmovement 0
	special RemoveCameraObject
	return

AerousCity_Museum_2F_EventScript_PanCameraWalkHerschelToPlayer1:
	special SpawnCameraObject
	applymovement LOCALID_HERSCHEL, AerousCity_Museum_2F_Movement_WalkHerschelToPlayer1
	applymovement OBJ_EVENT_ID_CAMERA, AerousCity_Museum_2F_Movement_PanCameraToPlayer1
	waitmovement 0
	special RemoveCameraObject
	return

AerousCity_Museum_2F_EventScript_PanCameraWalkHerschelToPlayer2:
	special SpawnCameraObject
	applymovement LOCALID_HERSCHEL, AerousCity_Museum_2F_Movement_WalkHerschelToPlayer2
	applymovement OBJ_EVENT_ID_CAMERA, AerousCity_Museum_2F_Movement_PanCameraToPlayer2
	waitmovement 0
	special RemoveCameraObject
	return

AerousCity_Museum_2F_EventScript_ExitHerschel0:
	applymovement LOCALID_HERSCHEL, AerousCity_Museum_2F_Movement_ExitHerschel0
	waitmovement 0
	return

AerousCity_Museum_2F_EventScript_ExitHerschel1:
	applymovement LOCALID_HERSCHEL, AerousCity_Museum_2F_Movement_ExitHerschel1
	waitmovement 0
	return

AerousCity_Museum_2F_EventScript_ExitHerschel2:
	applymovement LOCALID_HERSCHEL, AerousCity_Museum_2F_Movement_ExitHerschel2
	waitmovement 0
	return

AerousCity_Museum_2F_Text_AndThatIsOurMainPriority:
	.string "???: {COLOR RED}…and that is our main\n"
	.string "priority.\p"
	.string "Your help would be invaluable.$"

AerousCity_Museum_2F_Text_IveAlreadyGivenYouMyAnswer:
	.string "???: {COLOR BLUE}I've already given you my\n"
	.string "answer.\p"
	.string "It would not be prudent to ask\n"
	.string "again.$"

AerousCity_Museum_2F_Text_HerschelIFeelIHaveNotExplained:
	.string "???: {COLOR GREEN}Herschel{COLOR RED}, I feel I have\n"
	.string "not explained myself properly…$"

AerousCity_Museum_2F_Text_MaamTheChildIWasTalkingAboutIsHere:
	.string "Grunt: {COLOR BLUE}Ma'am, the child I was\n"
	.string "talking about is here.$"

AerousCity_Museum_2F_Text_DontInterrupt:
	.string "???: {COLOR RED}Don't interrupt!$"

AerousCity_Museum_2F_Text_ItsClearIWontBePersuadingYou:
	.string "???: {COLOR RED}It's clear I won't be\n"
	.string "persuading you any time soon.\p"
	.string "Thank you for your time.\n"
	.string "We're finished here.$"

AerousCity_Museum_2F_Text_OhGoodDayChild:
	.string "Herschel: {COLOR BLUE}Oh, good day, child.\n"
	.string "I presume you saw that.\p"
	.string "If you are curious, those people\n"
	.string "were ridiculous fanatics.\p"
	.string "I want no involvement with them.$"

AerousCity_Museum_2F_Text_IsThatARedwoodCard:
	.string "{COLOR BLUE}I hope you don't mind my asking,\n"
	.string "but is that a Redwood Card?\p"
	.string "…\p"
	.string "{COLOR DARK_GREY}Herschel: {COLOR BLUE}It is?\n"
	.string "Oh, how extraordinary!\p"
	.string "Charles… err, Prof. Redwood is a\n"
	.string "great friend of mine.\p"
	.string "…\p"
	.string "{COLOR DARK_GREY}Herschel: {COLOR BLUE}What's that?\n"
	.string "He sent you here to find me?\p"
	.string "Archan Tunnel? The old language?\n"
	.string "How intriguing!\p"
	.string "I would love to help.\n"
	.string "Very well.\p"
	.string "I'll wait for you by {COLOR GREEN}the exit to\n"
	.string "Aerous Road{COLOR BLUE}. We can go together.\p"
	.string "I shall see you there!$"

AerousCity_Museum_2F_Movement_PanCameraToEunice0:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

AerousCity_Museum_2F_Movement_PanCameraToEunice1:
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

AerousCity_Museum_2F_Movement_PanCameraToEunice2:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

AerousCity_Museum_2F_Movement_ExitEunice:
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_ExitGrunt3:
	delay_16
	walk_up
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_PanCameraToPlayer0:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_WalkHerschelToPlayer0:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_PanCameraToPlayer1:
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_WalkHerschelToPlayer1:
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_PanCameraToPlayer2:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_WalkHerschelToPlayer2:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_ExitHerschel0:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_ExitHerschel1:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_Movement_ExitHerschel2:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

AerousCity_Museum_2F_EventScript_Fossil::
	msgbox AerousCity_Museum_2F_Text_Fossil, MSGBOX_SIGN
	end

AerousCity_Museum_2F_Text_Fossil:
	.string "It is a Fossil of some sort.\n"
	.string "Prof. Redwood would love this!$"
