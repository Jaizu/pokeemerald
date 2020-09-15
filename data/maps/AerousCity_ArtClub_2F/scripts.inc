AerousCity_ArtClub_2F_MapScripts::
	.byte 0

AerousCity_ArtClub_2F_EventScript_AromaLady::
	lock
	msgbox AerousCity_ArtClub_2F_Text_ShesTooBusyEating, MSGBOX_DEFAULT
	release
	end

AerousCity_ArtClub_2F_Text_ShesTooBusyEating:
	.string "{COLOR DARK_GREY}She's too busy eating\n"
	.string "to notice you…$"

AerousCity_ArtClub_2F_EventScript_Cook1::
	msgbox AerousCity_ArtClub_2F_Text_BeingAChefIsTiringWork, MSGBOX_NPC
	end

AerousCity_ArtClub_2F_Text_BeingAChefIsTiringWork:
	.string "Being a chef is tiring work!$"

AerousCity_ArtClub_2F_EventScript_Cook2::
	lock
	faceplayer
	msgbox AerousCity_ArtClub_2F_Text_WhyDoIHaveToWashUp, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousCity_ArtClub_2F_Text_WhyDoIHaveToWashUp:
	.string "Why do I have to do all the\n"
	.string "washing up?$"

AerousCity_ArtClub_2F_EventScript_FatMan::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_AEROUS_CITY_NUGGET, AerousCity_ArtClub_2F_EventScript_ReceivedNugget
	msgbox AerousCity_ArtClub_2F_Text_TurnsOutThisIsntEdible, MSGBOX_DEFAULT
	giveitem ITEM_NUGGET
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_AEROUS_CITY_NUGGET
	goto AerousCity_ArtClub_2F_EventScript_ReceivedNugget
	end

AerousCity_ArtClub_2F_EventScript_ReceivedNugget:
	msgbox AerousCity_ArtClub_2F_Text_ThisFoodIsDelicious, MSGBOX_DEFAULT
	release
	end

AerousCity_ArtClub_2F_Text_TurnsOutThisIsntEdible:
	.string "Turns out this isn't the edible\n"
	.string "type of Nugget.\p"
	.string "You can take it!$"

AerousCity_ArtClub_2F_Text_ThisFoodIsDelicious:
	.string "This food is delicious!$"

AerousCity_ArtClub_2F_EventScript_Essa::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ESSA, AerousCity_ArtClub_2F_EventScript_EssaPostBattle
	msgbox AerousCity_ArtClub_2F_Text_ThisFoodIsSoSpicy, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq AerousCity_ArtClub_2F_EventScript_EssaBattle
	msgbox AerousCity_ArtClub_2F_Text_YikesSomeonesSalty, MSGBOX_DEFAULT
	release
	end

AerousCity_ArtClub_2F_EventScript_EssaBattle:
	msgbox AerousCity_ArtClub_2F_Text_EssaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ESSA, AerousCity_ArtClub_2F_Text_EssaDefeat
	setflag FLAG_DEFEATED_ESSA
	goto AerousCity_ArtClub_2F_EventScript_EssaPostBattle
	end

AerousCity_ArtClub_2F_EventScript_EssaPostBattle:
	msgbox AerousCity_ArtClub_2F_Text_PostBattle, MSGBOX_DEFAULT
	release
	end

AerousCity_ArtClub_2F_Text_ThisFoodIsSoSpicy:
	.string "This food is so spicy!\n"
	.string "It gives me the urge to fight!\p"
	.string "Do you want to have a Pokémon\n"
	.string "battle?$"

AerousCity_ArtClub_2F_Text_YikesSomeonesSalty:
	.string "Yikes…\n"
	.string "Someone's salty…$"

AerousCity_ArtClub_2F_Text_EssaIntro:
	.string "Sweet!\n"
	.string "Let's go!$"

AerousCity_ArtClub_2F_Text_EssaDefeat:
	.string "Roasted…$"

AerousCity_ArtClub_2F_Text_PostBattle:
	.string "I'm so bitter I lost!$"

AerousCity_ArtClub_2F_EventScript_Beauty::
	lock
	faceplayer
	msgbox AerousCity_ArtClub_2F_Text_ImNotGreatAtDating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousCity_ArtClub_2F_Text_ImNotGreatAtDating:
	.string "I'm not great at dating, but I\n"
	.string "love that I get all this free food!$"

AerousCity_ArtClub_2F_EventScript_Man::
	lock
	faceplayer
	msgbox AerousCity_ArtClub_2F_Text_DontRuinThisForMe, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousCity_ArtClub_2F_Text_DontRuinThisForMe:
	.string "Can't you see I'm on a date?\n"
	.string "Don't ruin this for me!$"

AerousCity_ArtClub_2F_EventScript_RichBoy::
	lock
	faceplayer
	msgbox AerousCity_ArtClub_2F_Text_ThisPaintingWasByVincent, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousCity_ArtClub_2F_Text_ThisPaintingWasByVincent:
	.string "This painting was actually made by\n"
	.string "Vincent!\p"
	.string "You can challenge him downstairs.$"

AerousCity_ArtClub_2F_EventScript_PaintingSign::
	msgbox AerousCity_ArtClub_2F_Text_PaintingOfThePokemonLeague, MSGBOX_SIGN
	end

AerousCity_ArtClub_2F_Text_PaintingOfThePokemonLeague:
	.string "It is a painting of the\n"
	.string "Pokémon League.$"
