SabuloTower_2F_MapScripts::
	.byte 0

SabuloTower_2F_EventScript_Maya::
	trainerbattle_single TRAINER_MAYA, SabuloTower_2F_Text_MayaIntro, SabuloTower_2F_Text_MayaDefeated
	msgbox SabuloTower_2F_Text_MayaPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloTower_2F_Text_MayaIntro:
	.string "Your effort has been valiant, but\n"
	.string "it ends here!$"

SabuloTower_2F_Text_MayaDefeated:
	.string "I underestimated you.$"

SabuloTower_2F_Text_MayaPostBattle:
	.string "Heed my warning, Successor Belle\n"
	.string "will not go easily on you!$"
