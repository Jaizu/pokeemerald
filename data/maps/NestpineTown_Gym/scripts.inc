NestpineTown_Gym_MapScripts::
	.byte 0

NestpineTown_Gym_EventScript_GymSign::
	msgbox NestpineTown_Gym_Text_GymSign, MSGBOX_SIGN
	end

NestpineTown_Gym_Text_GymSign:
	.string "Nestpine Town Pokémon Gym\p"
	.string "Leader: Aria\n"
	.string "“The Circling Songbird.”$"

NestpineTown_Gym_EventScript_JimGai::
	lock
	faceplayer
	goto_if_set FLAG_BADGE02_GET, NestpineTown_EventScript_CongratulatePlayer
	msgbox NestpineTown_Text_WelcomeChamp, MSGBOX_DEFAULT
	release
	end

NestpineTown_EventScript_CongratulatePlayer:
	msgbox NestpineTown_Text_NiceGoingChamp, MSGBOX_DEFAULT
	release
	end

NestpineTown_Text_WelcomeChamp:
	.string "Welcome, champ!\n"
	.string "This Gym is musical!\p"
	.string "That's right, you've gotta listen\n"
	.string "to the Chatot sing, and then\l"
	.string "repeat it back to them!\p"
	.string "That will clear the branches in\n"
	.string "your way.\p"
	.string "Oh, and this is a Flying-type Gym.\n"
	.string "Good luck out there, champ!$"

NestpineTown_Text_NiceGoingChamp:
	.string "Nice going, champ!\p"
	.string "That Plume Badge…\n"
	.string "It looks real good on you, kid!$"
