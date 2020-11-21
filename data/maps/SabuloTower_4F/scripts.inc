SabuloTower_4F_MapScripts::
	.byte 0

SabuloTower_4F_EventScript_Mikel::
	trainerbattle_single TRAINER_MIKEL, SabuloTower_4F_Text_MikelIntro, SabuloTower_4F_Text_MikelDefeated
	msgbox SabuloTower_4F_Text_MikelPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloTower_4F_Text_MikelIntro:
	.string "How high does this tower go?\n"
	.string "Am I even near the top?$"

SabuloTower_4F_Text_MikelDefeated:
	.string "I feel like I'm falling all the\n"
	.string "way down…$"

SabuloTower_4F_Text_MikelPostBattle:
	.string "I can't let one loss keep me down!$"
