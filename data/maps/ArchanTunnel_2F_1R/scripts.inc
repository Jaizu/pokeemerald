ArchanTunnel_2F_1R_MapScripts::
	.byte 0

ArchanTunnel_2F_1R_EventScript_Byron::
	trainerbattle_single TRAINER_BYRON, ArchanTunnel_2F_1R_Text_ByronIntro, ArchanTunnel_2F_1R_Text_ByronDefeated
	msgbox ArchanTunnel_2F_1R_Text_ByronPostBattle, MSGBOX_AUTOCLOSE
	end

ArchanTunnel_2F_1R_Text_ByronIntro:
	.string "I thought I had found somewhere to\n"
	.string "train in peace… Obviously not!$"

ArchanTunnel_2F_1R_Text_ByronDefeated:
	.string "I just want somewhere to train\n"
	.string "in peace!$"

ArchanTunnel_2F_1R_Text_ByronPostBattle:
	.string "This cave is far out of the way…\n"
	.string "Ideal for training, right?$"
