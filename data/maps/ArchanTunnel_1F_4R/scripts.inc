ArchanTunnel_1F_4R_MapScripts::
	.byte 0

ArchanTunnel_1F_4R_EventScript_Haskel::
	trainerbattle_single TRAINER_HASKEL, ArchanTunnel_1F_4R_Text_HaskelIntro, ArchanTunnel_1F_4R_Text_HaskelDefeated
	msgbox ArchanTunnel_1F_4R_Text_HaskelPostBattle, MSGBOX_AUTOCLOSE
	end

ArchanTunnel_1F_4R_Text_HaskelIntro:
	.string "Aha! You've walked into my line of\n"
	.string "sight, and now we must spar!$"

ArchanTunnel_1F_4R_Text_HaskelDefeated:
	.string "My best efforts weren't enough!$"

ArchanTunnel_1F_4R_Text_HaskelPostBattle:
	.string "Dwebble are native to the Unova\n"
	.string "region, but they're quite common\l"
	.string "in Orbtus too!$"

ArchanTunnel_1F_4R_EventScript_Hiker::
	msgbox ArchanTunnel_1F_4R_Text_CraterFormByAWildPokemon, MSGBOX_NPC
	end

ArchanTunnel_1F_4R_Text_CraterFormByAWildPokemon:
	.string "This kind of crater was probably\n"
	.string "formed by a wild Pokémon.$"
