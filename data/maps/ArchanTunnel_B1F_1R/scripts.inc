ArchanTunnel_B1F_1R_MapScripts::
	.byte 0

Archan_Tunnel_B1F_1R_Louise::
	trainerbattle_single TRAINER_LOUISE, Archan_Tunnel_B1F_1R_Text_LouiseIntro, Archan_Tunnel_B1F_1R_Text_LouiseDefeated
	msgbox Archan_Tunnel_B1F_1R_Text_LouisePostBattle, MSGBOX_AUTOCLOSE
	end

Archan_Tunnel_B1F_1R_Text_LouiseIntro:
	.string "I've been reading up on Pokémon\n"
	.string "battles all day. I can't lose!$"

Archan_Tunnel_B1F_1R_Text_LouiseDefeated:
	.string "Wait, what?\n"
	.string "Did I misread you?$"

Archan_Tunnel_B1F_1R_Text_LouisePostBattle:
	.string "Winning Pokémon battles comes down\n"
	.string "to reading your opponent.$"

Archan_Tunnel_B1F_1R_Quinn::
	trainerbattle_single TRAINER_QUINN, Archan_Tunnel_B1F_1R_Text_QuinnIntro, Archan_Tunnel_B1F_1R_Text_QuinnDefeated
	msgbox Archan_Tunnel_B1F_1R_Text_QuinnPostBattle, MSGBOX_AUTOCLOSE
	end

Archan_Tunnel_B1F_1R_Text_QuinnIntro:
	.string "Rumble rumble…\n"
	.string "I'm as unpredictable as the earth!$"

Archan_Tunnel_B1F_1R_Text_QuinnDefeated:
	.string "Crushed…$"

Archan_Tunnel_B1F_1R_Text_QuinnPostBattle:
	.string "Earthquakes are caused when tectonic\n"
    .string "plates scrape past one another.$"

Archan_Tunnel_B1F_1R_Cory::
	trainerbattle_single TRAINER_CORY, Archan_Tunnel_B1F_1R_Text_CoryIntro, Archan_Tunnel_B1F_1R_Text_CoryDefeated
	msgbox Archan_Tunnel_B1F_1R_Text_CoryPostBattle, MSGBOX_AUTOCLOSE
	end

Archan_Tunnel_B1F_1R_Text_CoryIntro:
	.string "You work for the Prof.?\n"
    .string "I'm gonna battle him one day!\p"
    .string "You'll be great practice!$"

Archan_Tunnel_B1F_1R_Text_CoryDefeated:
	.string "Aw, it looks like I have some work\n"
    .string "to do…$"

Archan_Tunnel_B1F_1R_Text_CoryPostBattle:
	.string "So, what is the Prof. researching?$"
