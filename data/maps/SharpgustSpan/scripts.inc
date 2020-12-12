SharpgustSpan_MapScripts::
	.byte 0

SharpgustSpan_EventScript_AceTrainerF::
	msgbox SharpgustSpan_Text_OnceIGotTheSurfHM, MSGBOX_NPC
	end

SharpgustSpan_Text_OnceIGotTheSurfHM:
	.string "Once I got the Surf HM, I could\n"
	.string "explore so much more of the world!$"

SharpgustSpan_EventScript_RockWithAncientGlyphs::
	msgbox SharpgustSpan_Text_RockWithAncientGlyphs, MSGBOX_SIGN
	end

SharpgustSpan_Text_RockWithAncientGlyphs:
	.string "The rock is inscribed with\n"
	.string "ancient glyphs.$"

SharpgustSpan_EventScript_Maya::
	trainerbattle_double TRAINER_MAYA_AND_DAVE_1, SharpgustSpan_Text_MayaIntro, SharpgustSpan_Text_MayaDefeat, SharpgustSpan_Text_MayaNotEnoughPokemon
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SharpgustSpan_EventScript_MayaRematch
	msgbox SharpgustSpan_Text_MayaPostBattle, MSGBOX_DEFAULT
	release
	end

SharpgustSpan_EventScript_MayaRematch::
	trainerbattle_rematch_double TRAINER_MAYA_AND_DAVE_1, SharpgustSpan_Text_MayaIntro, SharpgustSpan_Text_MayaDefeat, SharpgustSpan_Text_MayaNotEnoughPokemon
	msgbox SharpgustSpan_Text_MayaPostBattle, MSGBOX_AUTOCLOSE
	end

SharpgustSpan_Text_MayaIntro:
	.string "My bro always battles with me!\n"
	.string "We'll take you down!$"

SharpgustSpan_Text_MayaDefeat:
	.string "Aw snap, I'm sorry bro!$"

SharpgustSpan_Text_MayaPostBattle:
	.string "My bro and I are tag-team Trainers.\p"
	.string "I think we need more practice,\n"
	.string "though…$"

SharpgustSpan_Text_MayaNotEnoughPokemon:
	.string "My bro always feels left out if I\n"
	.string "battle without him.$"

SharpgustSpan_EventScript_Dave::
	trainerbattle_double TRAINER_MAYA_AND_DAVE_1, SharpgustSpan_Text_DaveIntro, SharpgustSpan_Text_DaveDefeat, SharpgustSpan_Text_DaveNotEnoughPokemon
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SharpgustSpan_EventScript_DaveRematch
	msgbox SharpgustSpan_Text_DavePostBattle, MSGBOX_DEFAULT
	release
	end

SharpgustSpan_EventScript_DaveRematch::
	trainerbattle_rematch_double TRAINER_MAYA_AND_DAVE_1, SharpgustSpan_Text_DaveIntro, SharpgustSpan_Text_DaveDefeat, SharpgustSpan_Text_DaveNotEnoughPokemon
	msgbox SharpgustSpan_Text_DavePostBattle, MSGBOX_AUTOCLOSE
	end

SharpgustSpan_Text_DaveIntro:
	.string "Sis and me will take you down!\n"
	.string "Yeah!$"

SharpgustSpan_Text_DaveDefeat:
	.string "Aw man!$"

SharpgustSpan_Text_DavePostBattle:
	.string "I'm a great Trainer, but my sister\n"
	.string "always messes things up!$"

SharpgustSpan_Text_DaveNotEnoughPokemon:
	.string "We'll only battle you if we can\n"
	.string "battle together, y'hear?$"

SharpgustSpan_EventScript_Peggy::
	trainerbattle_single TRAINER_PEGGY_1, SharpgustSpan_Text_PeggyIntro, SharpgustSpan_Text_PeggyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SharpgustSpan_EventScript_PeggyRematch
	msgbox SharpgustSpan_Text_PeggyPostBattle, MSGBOX_DEFAULT
	release
	end

SharpgustSpan_EventScript_PeggyRematch::
	trainerbattle_rematch TRAINER_PEGGY_1, SharpgustSpan_Text_PeggyIntro, SharpgustSpan_Text_PeggyDefeat
	msgbox SharpgustSpan_Text_PeggyPostBattle, MSGBOX_AUTOCLOSE
	end

SharpgustSpan_Text_PeggyIntro:
	.string "You never know what you'll find\n"
	.string "when you're out at sea!$"

SharpgustSpan_Text_PeggyDefeat:
	.string "I didn't see that coming!$"

SharpgustSpan_Text_PeggyPostBattle:
	.string "The waves of the sea are so\n"
	.string "relaxing!\p"
	.string "Whenever I get too stressed, I\n"
	.string "love to go for long swims.$"
