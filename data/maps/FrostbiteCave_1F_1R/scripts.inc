FrostbiteCave_1F_1R_MapScripts::
	.byte 0

FrostbiteCave_1F_1R_EventScript_Morton::
	trainerbattle_single TRAINER_MORTON, FrostbiteCave_1F_1R_Text_MortonIntro, FrostbiteCave_1F_1R_Text_MortonDefeated
	msgbox FrostbiteCave_1F_1R_Text_MortonPostBattle, MSGBOX_AUTOCLOSE
	end

FrostbiteCave_1F_1R_Text_MortonIntro:
	.string "The stronger the Trainers, the\n"
	.string "more experience your Pokémon earn!$"

FrostbiteCave_1F_1R_Text_MortonDefeated:
	.string "That was a painful experience.$"

FrostbiteCave_1F_1R_Text_MortonPostBattle:
	.string "You know how the Exp. Share\n"
	.string "works, right?\p"
	.string "It splits up the Exp. Points\n"
	.string "earned between Pokémon that\l"
	.string "battled and the holder.\p"
	.string "It has great utility if you want\n"
	.string "to raise weak Pokémon quickly!$"

FrostbiteCave_1F_1R_EventScript_Finley::
	trainerbattle_single TRAINER_FINLEY, FrostbiteCave_1F_1R_Text_FinleyIntro, FrostbiteCave_1F_1R_Text_FinleyDefeated
	msgbox FrostbiteCave_1F_1R_Text_FinleyPostBattle, MSGBOX_AUTOCLOSE
	end

FrostbiteCave_1F_1R_Text_FinleyIntro:
	.string "Energy flows through this cave,\n"
	.string "and indeed the entire mountain!$"

FrostbiteCave_1F_1R_Text_FinleyDefeated:
	.string "You are…\n"
	.string "Overwhelming!$"

FrostbiteCave_1F_1R_Text_FinleyPostBattle:
	.string "Minerals often contain unknown\n"
	.string "powers.\p"
	.string "Some unlock Evolution, others\n"
	.string "prevent it.\p"
	.string "Some even enable Mega Evolution!$"

FrostbiteCave_1F_1R_EventScript_Grunt::
	msgbox FrostbiteCave_1F_1R_Text_ScramKid, MSGBOX_NPC
	end

FrostbiteCave_1F_1R_Text_ScramKid:
	.string "Scram kid!\p"
	.string "I've got to clear these rocks\n"
	.string "before my boss gets here.$"
