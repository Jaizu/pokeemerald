NestpineTown_Mart_MapScripts::
	.byte 0

NestpineTown_Mart_EventScript_Worker::
	msgbox NestpineTown_Mart_Text_IveGotToWorkLate, MSGBOX_NPC
	end

NestpineTown_Mart_Text_IveGotToWorkLate:
	.string "I've got to stay up late every\n"
	.string "night to help restock the Mart.\p"
	.string "I guess the couriers have trouble\n"
	.string "climbing the mountain…$"

NestpineTown_Mart_EventScript_Rocker::
	msgbox NestpineTown_Mart_Text_BusinessIsSlowAroundHere, MSGBOX_NPC
	end

NestpineTown_Mart_Text_BusinessIsSlowAroundHere:
	.string "Business is slow around here, but\n"
	.string "the prices are still the same…\p"
	.string "You've got to admire the"
	.string "Poké Mart's consistency!$"
