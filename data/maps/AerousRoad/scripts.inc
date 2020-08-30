.equ LOCALID_PAINTER, 3
.equ LOCALID_BEAUTY, 4
.equ LOCALID_FAT_MAN, 5

AerousRoad_MapScripts::
	.byte 0

AerousRoad_EventScript_PainterRoadblock_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto AerousRoad_EventScript_PainterRoadblock
	end

AerousRoad_EventScript_PainterRoadblock_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto AerousRoad_EventScript_PainterRoadblock
	end

AerousRoad_EventScript_PainterRoadblock:
	applymovement LOCALID_PAINTER, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_PAINTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PAINTER, Common_Movement_Delay48
	waitmovement 0
	msgbox AerousRoad_Text_DontTakeAnotherStep, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PAINTER, Common_Movement_FaceOriginalDirection
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
	end

AerousRoad_EventScript_Painter::
	lock
	faceplayer
	msgbox AerousRoad_Text_DontTakeAnotherStep, MSGBOX_DEFAULT
	applymovement LOCALID_PAINTER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousRoad_Text_DontTakeAnotherStep:
	.string "{COLOR RED}Don't take another step!\p"
	.string "You'll disturb the scene, and ruin\n"
	.string "my painting!$"

AerousRoad_EventScript_Harry::
	trainerbattle_single TRAINER_HARRY_1, AerousRoad_Text_HarryIntro, AerousRoad_Text_HarryDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_HarryRematch
	msgbox AerousRoad_Text_HarryPostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_HarryRematch::
	trainerbattle_rematch TRAINER_HARRY_1, AerousRoad_Text_HarryIntro, AerousRoad_Text_HarryDefeat
	msgbox AerousRoad_Text_HarryPostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_HarryIntro:
	.string "I love the fresh air out here!\n"
	.string "It makes me want to battle!$"

AerousRoad_Text_HarryDefeat:
	.string "Looks like I'm fresh out of luck.$"

AerousRoad_Text_HarryPostBattle:
	.string "It's important to get outside and\n"
	.string "breathe some fresh air!$"

AerousRoad_EventScript_Phoebe::
	trainerbattle_single TRAINER_PHOEBE_1, AerousRoad_Text_PhoebeIntro, AerousRoad_Text_PhoebeDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_PhoebeRematch
	msgbox AerousRoad_Text_PhoebePostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_PhoebeRematch::
	trainerbattle_rematch TRAINER_PHOEBE_1, AerousRoad_Text_PhoebeRematchIntro, AerousRoad_Text_PhoebeDefeat
	msgbox AerousRoad_Text_PhoebePostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_PhoebeIntro:
	.string "Ah!\n"
	.string "Did you spot it, too?$"

AerousRoad_Text_PhoebeDefeat:
	.string "Hmm…$"

AerousRoad_Text_PhoebePostBattle:
	.string "Do you see it yet?\n"
	.string "It's hidden!$"

AerousRoad_Text_PhoebeRematchIntro:
	.string "Ah!\n"
	.string "The mysterious Trainer returns…$"

AerousRoad_EventScript_Beauty::
	lock
	faceplayer
	msgbox AerousRoad_Text_ThisViewIsBeautiful, MSGBOX_DEFAULT
	applymovement LOCALID_BEAUTY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousRoad_Text_ThisViewIsBeautiful:
	.string "This view is beautiful!\p"
	.string "It's a shame about him…$"

AerousRoad_EventScript_FatMan::
	lock
	faceplayer
	msgbox AerousRoad_Text_IsntItBeautiful, MSGBOX_DEFAULT
	applymovement LOCALID_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousRoad_Text_IsntItBeautiful:
	.string "Ah…\n"
	.string "Isn't it beautiful?\p"
	.string "The view looks nice, too!$"
