.set LOCALID_RANGER_1, 12
.set LOCALID_RANGER_2, 13
.set LOCALID_RANGER_3, 14

NemesisCave_1F_1R_MapScripts::
	.byte 0

NemesisCave_1F_1R_EventScript_LileepTablet::
	lockall
	msgbox NemesisCave_1F_1R_Text_ItIsAnotherTablet, MSGBOX_DEFAULT
	call_if_unset FLAG_NEMESIS_CAVE_RANGERS_RETURNED, NemesisCave_1F_1R_EventScript_RangerScene
	releaseall
	end

NemesisCave_1F_1R_EventScript_RangerScene::
	msgbox NemesisCave_1F_1R_Text_YouOverThere, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	addobject LOCALID_RANGER_1
	applymovement LOCALID_RANGER_1, NemesisCave_1F_1R_Movement_RangerWalkToPlayer
	waitmovement 0
	msgbox NemesisCave_1F_1R_Text_ISeeYouHaveFoundTheTablet, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RANGER_1, NemesisCave_1F_1R_Movement_ExitRanger
	waitmovement 0
	removeobject LOCALID_RANGER_1
	removeobject LOCALID_RANGER_2
	removeobject LOCALID_RANGER_3
	setflag FLAG_HIDE_NEMESIS_CAVE_PKMN_RANGERS
	setflag FLAG_NEMESIS_CAVE_RANGERS_RETURNED
	clearflag FLAG_HIDE_VALOON_TOWN_PKMN_RANGER_1
	clearflag FLAG_HIDE_VALOON_TOWN_HOUSE_1_PKMN_RANGER_M
	clearflag FLAG_HIDE_NEMESIS_RIVER_NEW_ELDERS
	setvar VAR_NEMESIS_RIVER_STATE, 1
	return

NemesisCave_1F_1R_Text_ItIsAnotherTablet:
	.string "It is another Tablet.\n"
	.string "It appears to depict Lileep.$"

NemesisCave_1F_1R_Text_YouOverThere:
	.string "???: {COLOR BLUE}You, over there!$"

NemesisCave_1F_1R_Text_ISeeYouHaveFoundTheTablet:
	.string "{COLOR BLUE}I see you have found the\n"
	.string "Nemesis Cave Tablet!\p"
	.string "We Rangers found it recently!\n"
	.string "It's pretty mysterious, right?\p"
	.string "It's strange, but it seems to have\n"
	.string "some link to the earthquakes.\p"
	.string "Oh?\n"
	.string "You're investigating the tremors?\p"
	.string "Hmm…\p"
	.string "Well, we tried bringing a Lileep\n"
	.string "here, and nothing happened…\p"
	.string "I wonder what the Elders of Orbtus\n"
	.string "built it for?\p"
	.string "Well, it's fun to speculate,\n"
	.string "don't you agree?\p"
	.string "Oh, and you should come by the\n"
	.string "Rangers HQ later!\p"
	.string "We're going to be hosting a\n"
	.string "Bug-Catching Contest.\p"
	.string "I'll see you there, Trainer!$"

NemesisCave_1F_1R_Movement_RangerWalkToPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NemesisCave_1F_1R_Movement_ExitRanger:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

NemesisCave_1F_1R_EventScript_MossyRock::
	msgbox NemesisCave_1F_1R_Text_TheSurfaceIsCoveredInMoss, MSGBOX_SIGN
	end

NemesisCave_1F_1R_Text_TheSurfaceIsCoveredInMoss:
	.string "The surface is covered with moss.\n"
	.string "It feels soft to the touch.$"

NemesisCave_1F_1R_EventScript_Amalia::
	trainerbattle_single TRAINER_AMALIA, NemesisCave_1F_1R_Text_AmaliaIntro, NemesisCave_1F_1R_Text_AmaliaDefeated
	msgbox NemesisCave_1F_1R_Text_AmaliaPostBattle, MSGBOX_AUTOCLOSE
	end

NemesisCave_1F_1R_Text_AmaliaIntro:
	.string "Oh dear, I don't believe you'll be\n"
	.string "getting any further, friend.$"

NemesisCave_1F_1R_Text_AmaliaDefeated:
	.string "Oh, what a shock!$"

NemesisCave_1F_1R_Text_AmaliaPostBattle:
	.string "It appears I was wrong to assume\n"
	.string "you were weaker than me.$"

NemesisCave_1F_1R_EventScript_Koichi::
	trainerbattle_single TRAINER_KOICHI, NemesisCave_1F_1R_Text_KoichiIntro, NemesisCave_1F_1R_Text_KoichiDefeated
	msgbox NemesisCave_1F_1R_Text_KoichiPostBattle, MSGBOX_AUTOCLOSE
	end

NemesisCave_1F_1R_Text_KoichiIntro:
	.string "Gwa-hah! You're about to be\n"
	.string "ensnared by my vicious trap!$"

NemesisCave_1F_1R_Text_KoichiDefeated:
	.string "Well!\n"
	.string "That backfired fabulously.$"

NemesisCave_1F_1R_Text_KoichiPostBattle:
	.string "I should refine my battling skills\n"
	.string "before making such bold claims…$"

NemesisCave_1F_1R_EventScript_Marlon::
	trainerbattle_single TRAINER_MARLON, NemesisCave_1F_1R_Text_MarlonIntro, NemesisCave_1F_1R_Text_MarlonDefeated
	msgbox NemesisCave_1F_1R_Text_MarlonPostBattle, MSGBOX_AUTOCLOSE
	end

NemesisCave_1F_1R_Text_MarlonIntro:
	.string "Scr-chow! Sick riff, isn't it?$"

NemesisCave_1F_1R_Text_MarlonDefeated:
	.string "Chikka-boom…$"

NemesisCave_1F_1R_Text_MarlonPostBattle:
	.string "Scr-chow!\n"
	.string "You beat me!$"

NemesisCave_1F_1R_EventScript_Ingrid::
	trainerbattle_single TRAINER_INGRID, NemesisCave_1F_1R_Text_IngridIntro, NemesisCave_1F_1R_Text_IngridDefeated
	msgbox NemesisCave_1F_1R_Text_IngridPostBattle, MSGBOX_AUTOCLOSE
	end

NemesisCave_1F_1R_Text_IngridIntro:
	.string "I'm tougher than tough…\n"
	.string "I'm super tough!$"

NemesisCave_1F_1R_Text_IngridDefeated:
	.string "That loss will be tough to explain…$"

NemesisCave_1F_1R_Text_IngridPostBattle:
	.string "I've gotta toughen up.\n"
	.string "I need to be extra-super tough!$"

NemesisCave_1F_1R_EventScript_Hideki::
	trainerbattle_single TRAINER_HIDEKI, NemesisCave_1F_1R_Text_HidekiIntro, NemesisCave_1F_1R_Text_HidekiDefeated
	msgbox NemesisCave_1F_1R_Text_HidekiPostBattle, MSGBOX_AUTOCLOSE
	end

NemesisCave_1F_1R_Text_HidekiIntro:
	.string "Are you hunting for the Mossy Rock,\n"
	.string "too?$"

NemesisCave_1F_1R_Text_HidekiDefeated:
	.string "I give up! I give up!\n"
	.string "It was only a question!$"

NemesisCave_1F_1R_Text_HidekiPostBattle:
	.string "The Mossy Rock is way past cool!\n"
	.string "It's how my Eevee evolved!$"

NemesisCave_1F_1R_EventScript_PkmnRangerM::
	msgbox NemesisCave_1F_1R_Text_ItsWeirdHowGrassGrowsHere, MSGBOX_NPC
	end

NemesisCave_1F_1R_Text_ItsWeirdHowGrassGrowsHere:
	.string "It's weird how grass can still\n"
	.string "grow in here…$"

NemesisCave_1F_1R_EventScript_PkmnRangerF::
	msgbox NemesisCave_1F_1R_Text_ItSeemsNobodyGotHarmed, MSGBOX_NPC
	end

NemesisCave_1F_1R_Text_ItSeemsNobodyGotHarmed:
	.string "It seems nobody got hurt in the\n"
	.string "earthquake, then…$"
