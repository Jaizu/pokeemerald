.equ LOCALID_FERNANDO, 6

SerosVillage_Gym_MapScripts::
	.byte 0

SerosVillage_Gym_EventScript_GymSign::
	msgbox SerosVillage_Gym_Text_GymSign, MSGBOX_SIGN
	end

SerosVillage_Gym_Text_GymSign:
	.string "Seros Village Pokémon Gym\p"
	.string "Leader: Fernando\n"
	.string "“The Young Fairy-type Trainer!”$"

SerosVillage_Gym_EventScript_JimGai::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SEROS_GYM, SerosVillage_Gym_EventScript_YouSavedFernando
	goto_if_set FLAG_FERNANDO_STORMED_OFF, SerosVillage_Gym_EventScript_WhoaWhatDidYouSay
	msgbox SerosVillage_Gym_Text_HeyThere, MSGBOX_DEFAULT
	release
	end

SerosVillage_Gym_EventScript_WhoaWhatDidYouSay:
	msgbox SerosVillage_Gym_Text_WhoaWhatDidYouSay, MSGBOX_DEFAULT
	release
	end

SerosVillage_Gym_EventScript_YouSavedFernando:
	msgbox SerosVillage_Gym_Text_YouSavedFernando, MSGBOX_DEFAULT
	release
	end

SerosVillage_Gym_Text_HeyThere:
	.string "Hey there!\n"
	.string "You're new to the Gym, right?\p"
	.string "Well, Fernando's the Gym Leader.\n"
	.string "He uses Fairy-types!\p"
	.string "{COLOR GREEN}Poison-type{COLOR BLUE} moves are great here.$"

SerosVillage_Gym_Text_WhoaWhatDidYouSay:
	.string "Whoa…\n"
	.string "What did you say to Fernando?\p"
	.string "He stormed out of here, and threw\n"
	.string "his Poké Balls at me!$"

SerosVillage_Gym_Text_YouSavedFernando:
	.string "You saved Fernando from\n"
	.string "the Wisp Forest?\p"
	.string "Wow! You really do deserve that\n"
	.string "Mystic Badge!$"

SerosVillage_Gym_EventScript_Rose::
	trainerbattle_single TRAINER_ROSE, SerosVillage_Gym_Text_RoseIntro, SerosVillage_Gym_Text_RoseDefeat
	msgbox SerosVillage_Gym_Text_RosePostBattle, MSGBOX_AUTOCLOSE
	end

SerosVillage_Gym_Text_RoseIntro:
	.string "Don't be fooled by the trees!\n"
	.string "We use Fairy-type Pokémon here!$"

SerosVillage_Gym_Text_RoseDefeat:
	.string "That was mystifying!$"

SerosVillage_Gym_Text_RosePostBattle:
	.string "You beat me!\p"
	.string "Good luck not getting lost!$"

SerosVillage_Gym_EventScript_Courtney::
	trainerbattle_single TRAINER_COURTNEY, SerosVillage_Gym_Text_CourtneyIntro, SerosVillage_Gym_Text_CourtneyDefeat
	msgbox SerosVillage_Gym_Text_CourtneyPostBattle, MSGBOX_AUTOCLOSE
	end

SerosVillage_Gym_Text_CourtneyIntro:
	.string "This Gym confuses me, but I won't\n"
	.string "let that faze me!$"

SerosVillage_Gym_Text_CourtneyDefeat:
	.string "How perplexing…$"

SerosVillage_Gym_Text_CourtneyPostBattle:
	.string "I don't think I've ever found the\n"
	.string "room where Fernando is…$"

SerosVillage_Gym_EventScript_Daz::
	trainerbattle_single TRAINER_DAZ, SerosVillage_Gym_Text_DazIntro, SerosVillage_Gym_Text_DazDefeat
	msgbox SerosVillage_Gym_Text_DazPostBattle, MSGBOX_AUTOCLOSE
	end

SerosVillage_Gym_Text_DazIntro:
	.string "Some say Fairy-type Pokémon get\n"
	.string "their power from the moon!$"

SerosVillage_Gym_Text_DazDefeat:
	.string "Total eclipse of my heart…$"

SerosVillage_Gym_Text_DazPostBattle:
	.string "Moves like Moonblast and Moonlight\n"
	.string "are Fairy-type!$"

SerosVillage_Gym_EventScript_Hana::
	trainerbattle_single TRAINER_HANA, SerosVillage_Gym_Text_HanaIntro, SerosVillage_Gym_Text_HanaDefeat
	msgbox SerosVillage_Gym_Text_HanaPostBattle, MSGBOX_AUTOCLOSE
	end

SerosVillage_Gym_Text_HanaIntro:
	.string "I've got the strongest bond with\n"
	.string "my Pokémon!$"

SerosVillage_Gym_Text_HanaDefeat:
	.string "Whoa, you must have a great bond\n"
	.string "with your Pokémon!$"

SerosVillage_Gym_Text_HanaPostBattle:
	.string "The love you show your Pokémon\n"
	.string "affects their ability to battle!$"

SerosVillage_Gym_EventScript_Fernando::
	trainerbattle_single TRAINER_FERNANDO_1, SerosVillage_Gym_Text_FernandoIntro, SerosVillage_Gym_Text_FernandoDefeat, SerosVillage_Gym_EventScript_FernandoDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_TM03, SerosVillage_Gym_EventScript_GiveDisarmingVoice
	msgbox SerosVillage_Gym_Text_FernandoPostBattle, MSGBOX_DEFAULT
	release
	end

SerosVillage_Gym_EventScript_FernandoDefeated:
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	msgbox SerosVillage_Gym_Text_FernandoRefuses, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_1, 31
	call_if_eq SerosVillage_Gym_EventScript_FernandoWalkRight
	applymovement LOCALID_FERNANDO, SerosVillage_Gym_Movement_ExitFernando
	waitmovement 0
	playse SE_EXIT
	waitse
	removeobject LOCALID_FERNANDO
	setflag FLAG_FERNANDO_STORMED_OFF
	setvar VAR_SEROS_VILLAGE_STATE, 2
	release
	end

SerosVillage_Gym_EventScript_FernandoWalkRight:
	applymovement LOCALID_FERNANDO, Common_Movement_WalkRight
	waitmovement 0
	return

SerosVillage_Gym_EventScript_GiveDisarmingVoice:
	msgbox SerosVillage_Gym_Text_ThankYouAgain, MSGBOX_DEFAULT
	giveitem ITEM_TM03
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_TM03
	msgbox SerosVillage_Gym_Text_ThatsDisarmingVoice, MSGBOX_DEFAULT
	release
	end

SerosVillage_Gym_Text_FernandoIntro:
	.string "{COLOR DARK_GREY}Fernando: {COLOR BLUE}Ahem…\p"
	.string "H-hello.\n"
	.string "My name is Fernando.\p"
	.string "I am the Gym Leader of\n"
	.string "Seros Village.\p"
	.string "U-um…\n"
	.string "I'm sort of new at this…\p"
	.string "Go easy on me, okay?\n"
	.string "Alright…\p"
	.string "Bring it on!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

SerosVillage_Gym_Text_FernandoDefeat:
	.string "Waaah!\n"
	.string "This doesn't count!\p"
	.string "I'm not giving you my Badge!$"

SerosVillage_Gym_Text_FernandoRefuses:
	.string "{COLOR DARK_GREY}Fernando: {COLOR BLUE}No!\n"
	.string "No no no!\p"
	.string "I don't want to give you my Badge!\n"
	.string "You can't make me!$"

SerosVillage_Gym_Text_FernandoPostBattle:
	.string "{COLOR DARK_GREY}Fernando: {COLOR BLUE}I bet you want to get the\n"
	.string "next Gym Badge now, right?\p"
	.string "I think the next Gym is in\n"
	.string "{COLOR GREEN}Nestpine Town{COLOR BLUE}.\p"
	.string "Aria is the Gym Leader!\n"
	.string "She uses Flying-types.\p"
	.string "But, don't worry, she isn't a\n"
	.string "crybaby like I am!$"

SerosVillage_Gym_Text_ThankYouAgain:
	.string "{COLOR DARK_GREY}Fernando: {COLOR BLUE}{PLAYER}!\p"
	.string "Thanks again for saving me from\n"
	.string "Wisp Forest…\p"
	.string "I'm sorry for not being nice when\n"
	.string "you beat me, so…\p"
	.string "I want you to take this.\n"
	.string "It's TM03!$"

SerosVillage_Gym_Text_ThatsDisarmingVoice:
	.string "{COLOR DARK_GREY}Fernando: {COLOR BLUE}TM03 contains\n"
	.string "{COLOR GREEN}Disarming Voice{COLOR BLUE}.\p"
	.string "Pokémon who use it let out a cry.\n"
	.string "Fitting for me, right?$"

SerosVillage_Gym_Movement_ExitFernando:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
