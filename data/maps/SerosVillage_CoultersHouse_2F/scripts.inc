SerosVillage_CoultersHouse_2F_MapScripts::
	.byte 0

SerosVillage_CoultersHouse_2F_EventScript_CoultersPC::
	msgbox SerosVillage_CoultersHouse_2F_Text_CoultersPC, MSGBOX_SIGN
	end

SerosVillage_CoultersHouse_2F_Text_CoultersPC:
	.string "It's {RIVAL}'s item storage!\n"
	.string "Best not to touch anything…$"

SerosVillage_CoultersHouse_2F_EventScript_CoultersNES::
	msgbox SerosVillage_CoultersHouse_2F_Text_CoultersNES, MSGBOX_SIGN
	end

SerosVillage_CoultersHouse_2F_Text_CoultersNES:
	.string "Cool! {RIVAL} has a NES,\n"
	.string "just like the one at home!$"

SerosVillage_CoultersHouse_2F_EventScript_Doll::
	lock
	msgbox SerosVillage_CoultersHouse_2F_Text_Doll, MSGBOX_DEFAULT
	release
	end

SerosVillage_CoultersHouse_2F_Text_Doll:
	.string "This is a rare Pokémon!\n"
	.string "Huh? It's only a doll!$"
