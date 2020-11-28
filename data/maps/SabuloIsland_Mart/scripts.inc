SabuloIsland_Mart_MapScripts::
	.byte 0

SabuloIsland_Mart_EventScript_Maniac::
	lock
	faceplayer
	compare VAR_SABULO_ISLAND_STATE, 2
	goto_if_eq SabuloIsland_Mart_EventScript_IsSabuloTowerSafe
	msgbox SabuloIsland_Mart_Text_MegaStonesAreTrickyToFind, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloIsland_Mart_Text_MegaStonesAreTrickyToFind:
	.string "Mega Stones are tricky to find.\p"
	.string "But, there's something thrilling\n"
	.string "about when you finally do!\p"
	.string "Ooh! I get chills just thinking\n"
	.string "about it!$"

SabuloIsland_Mart_EventScript_IsSabuloTowerSafe:
	msgbox SabuloIsland_Mart_Text_IsSabuloTowerSafe, MSGBOX_DEFAULT
	closemessage
	release
	end

SabuloIsland_Mart_Text_IsSabuloTowerSafe:
	.string "Is Sabulo Tower safe?$"
