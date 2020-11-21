FrostbiteCave_1F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FrostbiteCave_1F_1R_OnLoad
	.byte 0

FrostbiteCave_1F_1R_OnLoad:
	call_if_set FLAG_CLEAR_ROCKS_FROSTBITE_CAVE_1F, FrostbiteCave_1F_1R_EventScript_ClearRocks
	end

FrostbiteCave_1F_1R_EventScript_ClearRocks::
	setmetatile 28, 14, METATILE_FrostbiteCave_CaveGround, 0
	setmetatile 28, 15, METATILE_FrostbiteCave_CaveGround, 0
	setmetatile 28, 16, METATILE_FrostbiteCave_CaveGround, 0
	return

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

FrostbiteCave_1F_1R_EventScript_GruntF::
	trainerbattle_single TRAINER_FROSTBITE_CAVE_GRUNT_1, FrostbiteCave_1F_1R_Text_GruntFIntro, FrostbiteCave_1F_1R_Text_GruntFDefeated
	msgbox FrostbiteCave_1F_1R_Text_GruntFPostBattle, MSGBOX_AUTOCLOSE
	end

FrostbiteCave_1F_1R_Text_GruntFIntro:
	.string "What are we looking for?\n"
	.string "None of your business!$"

FrostbiteCave_1F_1R_Text_GruntFDefeated:
	.string "I've said too much…$"

FrostbiteCave_1F_1R_Text_GruntFPostBattle:
	.string "That Herschel guy didn't help us…\p"
	.string "So we have to take matters into our\n"
	.string "own hands!$"

FrostbiteCave_1F_1R_EventScript_GruntM::
	trainerbattle_single TRAINER_FROSTBITE_CAVE_GRUNT_2, FrostbiteCave_1F_1R_Text_GruntMIntro, FrostbiteCave_1F_1R_Text_GruntMDefeated
	msgbox FrostbiteCave_1F_1R_Text_GruntMPostBattle, MSGBOX_AUTOCLOSE
	end

FrostbiteCave_1F_1R_Text_GruntMIntro:
	.string "You again?\n"
	.string "I lost to you at the Museum!$"

FrostbiteCave_1F_1R_Text_GruntMDefeated:
	.string "You have bested my Pokémon and I…$"

FrostbiteCave_1F_1R_Text_GruntMPostBattle:
	.string "Modern people destroy nature.\p"
	.string "We're in the business of\n"
	.string "preservation, kid!$"
