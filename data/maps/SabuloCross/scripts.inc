SabuloCross_MapScripts::
	.byte 0

SabuloCross_EventScript_RouteSign::
	msgbox SabuloCross_Text_RouteSign, MSGBOX_SIGN
	end

SabuloCross_Text_RouteSign::
	.string "Sabulo Cross\n"
	.string "{LEFT_ARROW} Aerous City {UP_ARROW} Reliquia Ruins\l"
	.string "{RIGHT_ARROW} Sabulo Island$"

SabuloCross_EventScript_PokeManiac::
	msgbox SabuloCross_Text_ImTryingToCatchSwablu, MSGBOX_NPC
	end

SabuloCross_Text_ImTryingToCatchSwablu:
	.string "I'm trying to catch as many\n"
	.string "Swablu as I can find.\p"
	.string "Right now I've got seventeen!$"

SabuloCross_EventScript_Joanna::
	trainerbattle_single TRAINER_JOANNA_1, SabuloCross_Text_JoannaIntro, SabuloCross_Text_JoannaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SabuloCross_EventScript_JoannaRematch
	msgbox SabuloCross_Text_JoannaPostBattle, MSGBOX_DEFAULT
	release
	end

SabuloCross_EventScript_JoannaRematch::
	trainerbattle_rematch TRAINER_JOANNA_1, SabuloCross_Text_JoannaRematchIntro, SabuloCross_Text_JoannaDefeat
	msgbox SabuloCross_Text_JoannaPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloCross_Text_JoannaIntro:
	.string "Welcome to Sabulo Island!\n"
	.string "Prepare to get destroyed!$"

SabuloCross_Text_JoannaDefeat:
	.string "Aw, I got destroyed…$"

SabuloCross_Text_JoannaPostBattle:
	.string "A lot of the wild Pokémon you'll\n"
	.string "find here love living by the water!$"

SabuloCross_Text_JoannaRematchIntro:
	.string "Back for more?\n"
	.string "This time I will destroy you!$"
