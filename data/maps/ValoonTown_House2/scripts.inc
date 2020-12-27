ValoonTown_House2_MapScripts::
	.byte 0

ValoonTown_House2_EventScript_Woman::
	msgbox ValoonTown_House2_Text_WhenIWasALittleGirl, MSGBOX_NPC
	end

ValoonTown_House2_Text_WhenIWasALittleGirl:
	.string "When I was a little girl, there\n"
	.string "were stories about a mad scientist\l"
	.string "who built a lab by the river.\p"
	.string "I never saw him, but I remember\n"
	.string "hearing strange noises!\p"
	.string "Maybe it was just the Bug-type\n"
	.string "Pokémon in Nemesis Cave, though…$"

ValoonTown_House2_EventScript_Man::
	lock
	faceplayer
	msgbox ValoonTown_House2_Text_UghIFellOverInTheSwamp, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ValoonTown_House2_Text_UghIFellOverInTheSwamp:
	.string "Ugh, I fell over in the Swamp.\p"
	.string "Now I'm trying to get this gunk\n"
	.string "off of my hands, but it won't go!$"
