SabuloIsland_House2_MapScripts::
	.byte 0

SabuloIsland_House2_EventScript_AceTrainerM::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM23, SabuloIsland_House2_EventScript_ExplainGrassKnot
	msgbox SabuloIsland_House2_Text_ItsImportantToKeepYourPokemonHealthy, MSGBOX_DEFAULT
	giveitem ITEM_TM23
	setflag FLAG_RECEIVED_TM23
	goto SabuloIsland_House2_EventScript_ExplainGrassKnot
	end

SabuloIsland_House2_EventScript_ExplainGrassKnot:
	msgbox SabuloIsland_House2_Text_YupGrassKnotIsARealThreat, MSGBOX_DEFAULT
	release
	end

SabuloIsland_House2_Text_ItsImportantToKeepYourPokemonHealthy:
	.string "It's important to keep your\n"
	.string "Pokémon healthy.\p"
	.string "If you let them get too heavy,\n"
	.string "Grass Knot will hurt them a bunch!\p"
	.string "Here, I'll give you the TM so you\n"
	.string "don't forget!$"

SabuloIsland_House2_Text_YupGrassKnotIsARealThreat:
	.string "Yup, Grass Knot is a real threat\n"
	.string "against heavier Pokémon.$"
