ArchanTunnel_3F_1R_MapScripts::
	.byte 0

ArchanTunnel_3F_1R_EventScript_Mako::
	trainerbattle_single TRAINER_MAKO, ArchanTunnel_3F_1R_Text_MakoIntro, ArchanTunnel_3F_1R_Text_MakoDefeated
	msgbox ArchanTunnel_3F_1R_Text_MakoPostBattle, MSGBOX_AUTOCLOSE
	end

ArchanTunnel_3F_1R_Text_MakoIntro:
	.string "Behold, the power of my Rock-type\n"
	.string "Pokémon!$"

ArchanTunnel_3F_1R_Text_MakoDefeated:
	.string "How'd you defeat them so fast?$"

ArchanTunnel_3F_1R_Text_MakoPostBattle:
	.string "Carry on through to reach\n"
	.string "Nestpine Climb!$"
