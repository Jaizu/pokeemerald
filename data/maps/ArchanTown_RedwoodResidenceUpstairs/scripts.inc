ArchanTown_RedwoodResidenceUpstairs_MapScripts::
	.byte 0

ArchanTown_RedwoodResidenceUpstairs_EventScript_FossilRevivalMachine::
	msgbox ArchanTown_RedwoodResidenceUpstairs_Text_FossilRevivalMachine, MSGBOX_SIGN
	end

ArchanTown_RedwoodResidenceUpstairs_Text_FossilRevivalMachine:
	.string "The computer displays a program:\n"
	.string "“FOSSIL REVIVAL SYSTEM v2.0”\p"
	.string "There's an error message, too:\n"
	.string "“VITAL COMPONENT MISSING!”\p"
	.string "Looks like it's out of service…$"

ArchanTown_RedwoodResidenceUpstairs_EventScript_RedwoodsJournal::
	msgbox ArchanTown_RedwoodResidenceUpstairs_Text_RedwoodsJournal, MSGBOX_SIGN
	end

ArchanTown_RedwoodResidenceUpstairs_Text_RedwoodsJournal:
	.string "It's a scientific journal of some\n"
	.string "sort.\p"
	.string "There are annotations all over the\n"
	.string "page!$"
