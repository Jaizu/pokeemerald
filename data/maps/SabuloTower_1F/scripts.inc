SabuloTower_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SabuloTower_1F_OnLoad
	.byte 0

SabuloTower_1F_OnLoad:
	call_if_unset FLAG_RECEIVED_MEGA_RING, SabuloTower_1F_EventScript_DeactivateWarpPad
	end

SabuloTower_1F_EventScript_DeactivateWarpPad::
	setmetatile 12, 13, METATILE_SabuloTower_WarpPad_Deactivated, 0
	return

SabuloTower_1F_EventScript_JimGai::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MEGA_RING, SabuloTower_1F_EventScript_TryExplainMegaRing
	msgbox SabuloTower_1F_Text_HeyChampWelcome, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloTower_1F_EventScript_TryExplainMegaRing:
	msgbox SabuloTower_1F_Text_NiceGoingChampDoYouRemember, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SabuloTower_1F_EventScript_ExplainMegaRing
	msgbox SabuloTower_1F_Text_JustAskIfYouForget, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloTower_1F_EventScript_ExplainMegaRing:
	msgbox MegaEvolution_Text_ExplainMegaEvolution, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloTower_1F_Text_HeyChampWelcome:
	.string "Hey, champ!\n"
	.string "Welcome to Sabulo Tower.\p"
	.string "If you can climb to the top and\n"
	.string "defeat Successor Belle…\p"
	.string "You'll get a Mega Ring!\n"
	.string "Quite the prize, no?$"

SabuloTower_1F_Text_NiceGoingChampDoYouRemember:
	.string "Nice going, champ!\p"
	.string "Do you remember how to use that\n"
	.string "Mega Ring?$"

SabuloTower_1F_Text_JustAskIfYouForget:
	.string "Alright!\n"
	.string "Just ask if you forget.\p"
	.string "By the way, you can use that\n"
	.string "teleporter to go to the top floor.$"

SabuloTower_1F_EventScript_Nikolai::
	trainerbattle_single TRAINER_NIKOLAI, SabuloTower_1F_Text_NikolaiIntro, SabuloTower_1F_Text_NikolaiDefeated
	msgbox SabuloTower_1F_Text_NikolaiPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloTower_1F_Text_NikolaiIntro:
	.string "Welcome, young one. I shall be\n"
	.string "your first challenge. Let's begin!$"

SabuloTower_1F_Text_NikolaiDefeated:
	.string "You show promise!$"

SabuloTower_1F_Text_NikolaiPostBattle:
	.string "You've defeated me, but the\n"
	.string "challenge has just begun!$"
