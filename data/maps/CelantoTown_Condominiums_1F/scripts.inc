CelantoTown_Condominiums_1F_MapScripts::
	.byte 0

CelantoTown_Condominiums_1F_EventScript_Lass::
	msgbox CelantoTown_Condominiums_1F_Text_HaveYouFeltTremors, MSGBOX_NPC
	end

CelantoTown_Condominiums_1F_Text_HaveYouFeltTremors:
	.string "Have you felt the tremors lately?\n"
	.string "They are frightening me…$"

CelantoTown_Condominiums_1F_EventScript_Hiker::
	msgbox CelantoTown_Condominiums_1F_Text_DidYouKnow, MSGBOX_NPC
	end

CelantoTown_Condominiums_1F_Text_DidYouKnow:
	.string "Did you know?\n"
	.string "Some moves are Physical.\p"
	.string "Others deal Special damage,\n"
	.string "and some are Status moves!$"
