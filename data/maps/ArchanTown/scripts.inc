ArchanTown_MapScripts::
	.byte 0

ArchanTown_EventScript_TownSign::
	msgbox ArchanTown_Text_TownSign, MSGBOX_SIGN
	end

ArchanTown_Text_TownSign:
	.string "Archan Town\n"
	.string "Famous for Archaeological Digs!$"

ArchanTown_EventScript_RedwoodSign::
	msgbox ArchanTown_Text_RedwoodSign, MSGBOX_SIGN
	end

ArchanTown_Text_RedwoodSign:
	.string "Redwood Residence$"

ArchanTown_EventScript_AncientTabletSign::
	msgbox ArchanTown_Text_AncientTabletSign, MSGBOX_SIGN
	end

ArchanTown_Text_AncientTabletSign:
	.string "This Ancient Tablet was\n"
	.string "constructed many years ago.\p"
	.string "It appears to portray the Pokémon\n"
	.string "Relicanth.$"
