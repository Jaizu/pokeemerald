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

NestpineTown_Gym_EventScript_Wilhelm::
	trainerbattle_single TRAINER_WILHELM, NestpineTown_Gym_Text_WilhelmIntro, NestpineTown_Gym_Text_WilhelmDefeat
	msgbox NestpineTown_Gym_Text_WilhelmPostBattle, MSGBOX_AUTOCLOSE
	end

NestpineTown_Gym_Text_WilhelmIntro:
	.string "Behold! The might and variety of\n"
	.string "the Flying-type!$"

NestpineTown_Gym_Text_WilhelmDefeat:
	.string "How…\n"
	.string "How is this possible?$"

NestpineTown_Gym_Text_WilhelmPostBattle:
	.string "You clawed me down…$"

NestpineTown_Gym_EventScript_Gordon::
	trainerbattle_single TRAINER_GORDON, NestpineTown_Gym_Text_GordonIntro, NestpineTown_Gym_Text_GordonDefeat
	msgbox NestpineTown_Gym_Text_GordonPostBattle, MSGBOX_AUTOCLOSE
	end

NestpineTown_Gym_Text_GordonIntro:
	.string "The strongest Flying-type Pokémon are\n"
	.string "also Bug-type!$"

NestpineTown_Gym_Text_GordonDefeat:
	.string "Was I wrong…?$"

NestpineTown_Gym_Text_GordonPostBattle:
	.string "Why do my Pokémon always lose so\n"
	.string "quickly?$"

NestpineTown_Gym_EventScript_Peter::
	trainerbattle_single TRAINER_PETER, NestpineTown_Gym_Text_PeterIntro, NestpineTown_Gym_Text_PeterDefeat
	msgbox NestpineTown_Gym_Text_PeterPostBattle, MSGBOX_AUTOCLOSE
	end

NestpineTown_Gym_Text_PeterIntro:
	.string "I'm the hot dude who protects Aria\n"
	.string "from danger!$"

NestpineTown_Gym_Text_PeterDefeat:
	.string "That was dangerously fast…$"

NestpineTown_Gym_Text_PeterPostBattle:
	.string "No!\n"
	.string "I have failed Aria!$"

NestpineTown_Gym_EventScript_Jane::
	trainerbattle_single TRAINER_JANE, NestpineTown_Gym_Text_JaneIntro, NestpineTown_Gym_Text_JaneDefeat
	msgbox NestpineTown_Gym_Text_JanePostBattle, MSGBOX_AUTOCLOSE
	end

NestpineTown_Gym_Text_JaneIntro:
	.string "You thought I was gonna be the\n"
	.string "Leader, didn't you?$"

NestpineTown_Gym_Text_JaneDefeat:
	.string "I thought that would be easier…$"

NestpineTown_Gym_Text_JanePostBattle:
	.string "When it evolves, Swablu loses its\n"
	.string "Normal-type.\p"
	.string "Altaria is Dragon-type, instead!$"

NestpineTown_Gym_EventScript_Cedric::
	trainerbattle_single TRAINER_CEDRIC, NestpineTown_Gym_Text_CedricIntro, NestpineTown_Gym_Text_CedricDefeat
	msgbox NestpineTown_Gym_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

NestpineTown_Gym_Text_CedricIntro:
	.string "Hey, dude! I'm no Gym Leader, but\n"
	.string "fight me, bro!$"

NestpineTown_Gym_Text_CedricDefeat:
	.string "Totally off-key…$"

NestpineTown_Gym_Text_CedricPostBattle:
	.string "Sorry bro, the Gym Leader's"
	.string "not over here."
	.string "But my tunes were rocking, right?$"

NestpineTown_Gym_EventScript_Aria::
	trainerbattle_single TRAINER_LEADER_ARIA_1, NestpineTown_Gym_Text_AriaIntro, NestpineTown_Gym_Text_AriaDefeat, NestpineTown_Gym_EventScript_AriaDefeated, NO_MUSIC
	call_if_unset FLAG_RECEIVED_TM19, NestpineTown_Gym_EventScript_GiveRoost
	msgbox NestpineTown_Gym_Text_AriaPostBattle, MSGBOX_DEFAULT
	release
	end

NestpineTown_Gym_EventScript_AriaDefeated:
	setflag FLAG_BADGE02_GET
	call NestpineTown_Gym_EventScript_GiveRoost
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	setflag FLAG_DEFEATED_NESTPINE_GYM
	setflag FLAG_HIDE_NEW_ELDERS_GRUNT_FROSTBITE_CAVE_1F
	setflag FLAG_CLEAR_ROCKS_FROSTBITE_CAVE_1F
	release
	end

NestpineTown_Gym_EventScript_GiveRoost:
	msgbox NestpineTown_Gym_Text_HereTakeThisCommemorativeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM19
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_TM19
	msgbox NestpineTown_Gym_Text_ExplainTM19, MSGBOX_DEFAULT
	return
	
NestpineTown_Gym_Text_AriaIntro:
	.string "My name is Aria.\p"
	.string "I have soared high and swooped low\n"
	.string "with my Flying-type Pokémon.\p"
	.string "Will this battle be a peak, or\n"
	.string "will you fall?\p"
	.string "What tune do you play to?\n"
	.string "It's time to find out!{PLAY_BGM}{MUS_RG_EXEYE}$"

NestpineTown_Gym_Text_AriaDefeat:
	.string "Simply stunning!\p"
	.string "This battle was truly\n"
	.string "breathtaking.\p"
	.string "It is my honor to bestow upon you\n"
	.string "the official Plume Badge.\p"
	.string "{PLAYER} received the Plume Badge\n"
	.string "from Aria!{PAUSE_MUSIC}{PLAY_BGM}{MUS_ME_BACHI}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}$"

NestpineTown_Gym_Text_HereTakeThisCommemorativeTM:
	.string "I'm stunned at your battling\n"
	.string "prowess.\p"
	.string "Here, take this commemorative\n"
	.string "TM19 Roost.$"

NestpineTown_Gym_Text_ExplainTM19:
	.string "Roost heals your Pokémon, but they\n"
	.string "temporarily lose their Flying-type.\p"
	.string "It can be a tricky trade-off, so\n"
	.string "timing is everything!$"

NestpineTown_Gym_Text_AriaPostBattle:
	.string "Your battling style is truly\n"
	.string "unique.\p"
	.string "I can't wait for the next time we\n"
	.string "battle!$"
