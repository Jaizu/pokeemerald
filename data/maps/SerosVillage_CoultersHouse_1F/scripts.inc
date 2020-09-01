.equ LOCALID_COULTERS_DAD, 2

SerosVillage_CoultersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SerosVillage_CoultersHouse_1F_OnTransition
	.byte 0

SerosVillage_CoultersHouse_1F_OnTransition:
	call_if_unset FLAG_HIDE_COULTERS_HOUSE_COULTER, SerosVillage_CoultersHouse_1F_EventScript_TurnCoultersDadSouth
	end

SerosVillage_CoultersHouse_1F_EventScript_TurnCoultersDadSouth:
	setobjectmovementtype LOCALID_COULTERS_DAD, MOVEMENT_TYPE_FACE_DOWN
	return

SerosVillage_CoultersHouse_1F_EventScript_Coulter::
	msgbox SerosVillage_CoultersHouse_1F_Text_TurnsOutMyDadHasntBeenTooUseful, MSGBOX_NPC
	end

SerosVillage_CoultersHouse_1F_Text_TurnsOutMyDadHasntBeenTooUseful:
	.string "Turns out my dad hasn't been too\n"
	.string "useful…\p"
	.string "Well, we should keep searching, eh\n"
	.string "{PLAYER}?$"

SerosVillage_CoultersHouse_1F_EventScript_CoultersMom::
	msgbox SerosVillage_CoultersHouse_1F_Text_YoureGoingOnAnAdventureWithMySon, MSGBOX_NPC
	end

SerosVillage_CoultersHouse_1F_Text_YoureGoingOnAnAdventureWithMySon:
	.string "You're on an adventure with my son?\n"
	.string "That sounds exciting!\p"
	.string "But, please look after him.$"

SerosVillage_CoultersHouse_1F_EventScript_CoultersDad::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_COULTERS_HOUSE_COULTER, SerosVillage_CoultersHouse_1F_EventScript_CoultersDadExplainCoulter
	msgbox SerosVillage_CoultersHouse_1F_Text_SecretTunnel, MSGBOX_DEFAULT
	release
	end

SerosVillage_CoultersHouse_1F_EventScript_CoultersDadExplainCoulter:
	msgbox SerosVillage_CoultersHouse_1F_Text_OurSonHasBeenPassionate, MSGBOX_DEFAULT
	release
	end

SerosVillage_CoultersHouse_1F_Text_SecretTunnel:
	.string "Secret tunnel?\n"
	.string "Never heard of anything like that…$"

SerosVillage_CoultersHouse_1F_Text_OurSonHasBeenPassionate:
	.string "Our son has been passionate about\n"
	.string "Pokémon from since he was a kid.\p"
	.string "He even keeps his old Pokémon\n"
	.string "dolls in his room!$"
