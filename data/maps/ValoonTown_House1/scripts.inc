ValoonTown_House1_MapScripts::
	.byte 0

ValoonTown_House1_EventScript_Woman::
	msgbox ValoonTown_House1_Text_ImProudOfMySon, MSGBOX_NPC
	end

ValoonTown_House1_Text_ImProudOfMySon:
	.string "I'm so proud of my son for joining\n"
	.string "the Rangers.$"

ValoonTown_House1_EventScript_PkmnRangerM::
	msgbox ValoonTown_House1_Text_WhatDoYouThinkTheTabletIsAbout, MSGBOX_NPC
	end

ValoonTown_House1_Text_WhatDoYouThinkTheTabletIsAbout:
	.string "What do you think the tablet we\n"
	.string "found in Nemesis Cave is about?\p"
	.string "I think the Elders of Orbtus must\n"
	.string "have placed it there for a reason…$"
