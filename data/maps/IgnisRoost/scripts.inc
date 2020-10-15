IgnisRoost_MapScripts::
	.byte 0

IgnisRoost_EventScript_GruntM1::
	trainerbattle_single TRAINER_IGNIS_ROOST_GRUNT_1, IgnisRoost_Text_GruntM1Intro, IgnisRoost_Text_GruntM1Defeated
	msgbox IgnisRoost_Text_GruntM1PostBattle, MSGBOX_AUTOCLOSE
	end

IgnisRoost_Text_GruntM1Intro:
	.string "This is the highest point in\n"
	.string "Orbtus.\p"
	.string "We're literally reaching for the\n"
	.string "skies to achieve our goal.$"

IgnisRoost_Text_GruntM1Defeated:
	.string "That's a long way to fall…$"

IgnisRoost_Text_GruntM1PostBattle:
	.string "I have let down the boss…$"

IgnisRoost_EventScript_GruntF::
	trainerbattle_single TRAINER_IGNIS_ROOST_GRUNT_2, IgnisRoost_Text_GruntFIntro, IgnisRoost_Text_GruntFDefeated
	msgbox IgnisRoost_Text_GruntFPostBattle, MSGBOX_AUTOCLOSE
	end

IgnisRoost_Text_GruntFIntro:
	.string "We're here to find some important\n"
	.string "information!$"

IgnisRoost_Text_GruntFDefeated:
	.string "Stop trying to foil our plans!$"

IgnisRoost_Text_GruntFPostBattle:
	.string "The Elders of Orbtus knew how to\n"
	.string "live. Modernity is evil!$"

IgnisRoost_EventScript_GruntM2::
	trainerbattle_single TRAINER_IGNIS_ROOST_GRUNT_3, IgnisRoost_Text_GruntM2Intro, IgnisRoost_Text_GruntM2Defeated
	msgbox IgnisRoost_Text_GruntM2PostBattle, MSGBOX_AUTOCLOSE
	end

IgnisRoost_Text_GruntM2Intro:
	.string "What's a couple of kids like you\n"
	.string "doing up here, anyway?$"

IgnisRoost_Text_GruntM2Defeated:
	.string "This was supposed to be a brief\n"
	.string "knowledge-gathering mission!$"

IgnisRoost_Text_GruntM2PostBattle:
	.string "I don't think Enoch expected\n"
	.string "antagonism up here…\p"
	.string "What do you guys what with the\n"
	.string "Temple, anyway?$"

IgnisRoost_EventScript_Grunt::
	lock
	faceplayer
	msgbox IgnisRoost_Text_YikesThatsALongWayDown, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

IgnisRoost_Text_YikesThatsALongWayDown:
	.string "Yikes…\n"
	.string "That's a long way down.\p"
	.string "…Hey, where is your uniform?$"
