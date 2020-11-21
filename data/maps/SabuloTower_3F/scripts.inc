SabuloTower_3F_MapScripts::
	.byte 0

SabuloTower_3F_EventScript_Jaime::
	trainerbattle_single TRAINER_JAIME, SabuloTower_3F_Text_JaimeIntro, SabuloTower_3F_Text_JaimeDefeated
	msgbox SabuloTower_3F_Text_JaimePostBattle, MSGBOX_AUTOCLOSE
	end

SabuloTower_3F_Text_JaimeIntro:
	.string "I'm not going to let some scrub\n"
	.string "get in my way!$"

SabuloTower_3F_Text_JaimeDefeated:
	.string "You cheated!$"

SabuloTower_3F_Text_JaimePostBattle:
	.string "I don't care if I lost to some\n"
	.string "kid, I'm still going to beat Belle!$"
