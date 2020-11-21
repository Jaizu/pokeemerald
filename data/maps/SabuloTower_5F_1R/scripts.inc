SabuloTower_5F_1R_MapScripts::
	.byte 0

SabuloTower_5F_1R_EventScript_Agem::
	trainerbattle_single TRAINER_AGEM, SabuloTower_5F_1R_Text_AgemIntro, SabuloTower_5F_1R_Text_AgemDefeated
	msgbox SabuloTower_5F_1R_Text_AgemPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloTower_5F_1R_Text_AgemIntro:
	.string "I am the last challenge you must\n"
	.string "face before Successor Belle.\p"
	.string "Do not hold back!$"

SabuloTower_5F_1R_Text_AgemDefeated:
	.string "Extraordinary…$"

SabuloTower_5F_1R_Text_AgemPostBattle:
	.string "Go on, Trainer.\n"
	.string "Successor Belle awaits you.$"
