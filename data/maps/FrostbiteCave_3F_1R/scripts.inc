FrostbiteCave_3F_1R_MapScripts::
	.byte 0

FrostbiteCave_3F_1R_EventScript_GruntM::
	trainerbattle_single TRAINER_FROSTBITE_CAVE_GRUNT_3, FrostbiteCave_3F_1R_Text_GruntMIntro, FrostbiteCave_3F_1R_Text_GruntMDefeated
	msgbox FrostbiteCave_3F_1R_Text_GruntMPostBattle, MSGBOX_AUTOCLOSE
	end

FrostbiteCave_3F_1R_Text_GruntMIntro:
	.string "Didn't you feel the tremors?\n"
	.string "You should turn around and go back!$"

FrostbiteCave_3F_1R_Text_GruntMDefeated:
	.string "You are surprisingly strong.\n"
	.string "But you should really leave!$"

FrostbiteCave_3F_1R_Text_GruntMPostBattle:
	.string "I-it's freezing in here…\n"
	.string "Why don't you turn back?$"

FrostbiteCave_3F_1R_EventScript_GruntF::
	trainerbattle_single TRAINER_FROSTBITE_CAVE_GRUNT_4, FrostbiteCave_3F_1R_Text_GruntFIntro, FrostbiteCave_3F_1R_Text_GruntFDefeated
	msgbox FrostbiteCave_3F_1R_Text_GruntFPostBattle, MSGBOX_AUTOCLOSE
	end

FrostbiteCave_3F_1R_Text_GruntFIntro:
	.string "Kids like you have no respect for\n"
	.string "our traditions. We'll teach you!$"

FrostbiteCave_3F_1R_Text_GruntFDefeated:
	.string "You can hold your own…\n"
	.string "Maybe you should join us!$"

FrostbiteCave_3F_1R_Text_GruntFPostBattle:
	.string "I'm warning you, kid, you'll\n"
	.string "regret sticking around.$"
