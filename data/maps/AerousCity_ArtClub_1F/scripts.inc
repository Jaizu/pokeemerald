AerousCity_ArtClub_1F_MapScripts::
	.byte 0

AerousCity_ArtClub_1F_EventScript_Vincent::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EGG_FROM_VINCENT, AerousCity_ArtClub_1F_EventScript_VincentPostEgg
	goto_if_set FLAG_DEFEATED_VINCENT, AerousCity_ArtClub_1F_EventScript_TryGiveEgg
	msgbox AerousCity_ArtClub_1F_Text_GoodDayChallenger, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_VINCENT, AerousCity_ArtClub_1F_Text_VincentDefeat
	setflag FLAG_DEFEATED_VINCENT
	goto AerousCity_ArtClub_1F_EventScript_TryGiveEgg
	end

AerousCity_ArtClub_1F_EventScript_TryGiveEgg:
	msgbox AerousCity_ArtClub_1F_Text_ThatWasABeautifulDisplay, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne AerousCity_ArtClub_1F_EventScript_DeclinedEgg
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq AerousCity_ArtClub_1F_EventScript_NoRoomForEgg
	giveegg SPECIES_EEVEE
	setflag FLAG_RECEIVED_EGG_FROM_VINCENT
	playfanfare MUS_FANFA4
	message AerousCity_ArtClub_1F_Text_ReceivedTheEgg
	waitfanfare
	msgbox AerousCity_ArtClub_1F_Text_InAWayRaisingAPokemonEggIsLike, MSGBOX_DEFAULT
	release
	end

AerousCity_ArtClub_1F_EventScript_DeclinedEgg:
	msgbox AerousCity_ArtClub_1F_Text_VeryWell, MSGBOX_DEFAULT
	release
	end

AerousCity_ArtClub_1F_EventScript_NoRoomForEgg:
	msgbox AerousCity_ArtClub_1F_Text_ItAppearsYouHaveNoRoom, MSGBOX_DEFAULT
	release
	end

AerousCity_ArtClub_1F_EventScript_VincentPostEgg:
	msgbox AerousCity_ArtClub_1F_Text_IWillOneDayImmortalizeOurBattle, MSGBOX_DEFAULT
	release
	end

AerousCity_ArtClub_1F_Text_GoodDayChallenger:
	.string "{COLOR DARK_GREY}Vincent: {COLOR BLUE}Good day, challenger.\n"
	.string "They call me the Art Master.\p"
	.string "Art is a curious beast, is it not?\p"
	.string "Even the simplest paintings can\n"
	.string "evoke deeply personal reactions.\p"
	.string "That visceral, raw emotion is why\n"
	.string "I love art.\p"
	.string "I share that same passion for\n"
	.string "Pokémon battles.\p"
	.string "It is time to show me your true\n"
	.string "colors, challenger!{PLAY_BGM}{MUS_TEST}$"
	
AerousCity_ArtClub_1F_Text_VincentDefeat:
	.string "Art.\n"
	.string "Pure art.$"

AerousCity_ArtClub_1F_Text_ThatWasABeautifulDisplay:
	.string "{COLOR DARK_GREY}Vincent: {COLOR BLUE}That was beautiful!\n"
	.string "I must reward you with something.\p"
	.string "As you know, I only train\n"
	.string "Smeargle.\p"
	.string "The variety of the moves they can\n"
	.string "use is beautiful to me.\p"
	.string "Alas, I recently obtained this\n"
	.string "gift from a fan of mine.\p"
	.string "If I'm truthful, I have no use for\n"
	.string "it.\p"
	.string "I'm sure it will be far better in\n"
	.string "your capable hands, Trainer.\p"
	.string "Would you like this Pokémon Egg?$"

AerousCity_ArtClub_1F_Text_ReceivedTheEgg:
	.string "{COLOR DARK_GREY}{PLAYER} received the\n"
	.string "Pokémon Egg from Vincent!$"

AerousCity_ArtClub_1F_Text_InAWayRaisingAPokemonEggIsLike:
	.string "{COLOR DARK_GREY}Vincent: {COLOR BLUE}In a way, raising a\n"
	.string "Pokémon Egg is like painting.\p"
	.string "You must be delicate, careful and\n"
	.string "passionate to see results.\p"
	.string "I'm sure you are more than capable!$"

AerousCity_ArtClub_1F_Text_VeryWell:
	.string "{COLOR DARK_GREY}Vincent: {COLOR BLUE}Very well…\p"
	.string "I will hold onto it, but if you\n"
	.string "change your mind, come see me.$"

AerousCity_ArtClub_1F_Text_ItAppearsYouHaveNoRoom:
	.string "{COLOR DARK_GREY}Vincent: {COLOR BLUE}…It appears you have\n"
	.string "no room for this.\p"
	.string "Deposit a Pokémon from your party\n"
	.string "and return!$"

AerousCity_ArtClub_1F_Text_IWillOneDayImmortalizeOurBattle:
	.string "{COLOR DARK_GREY}Vincent: {COLOR BLUE}I will one day immortalize\n"
	.string "our battle in a painting!$"

AerousCity_ArtClub_1F_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, AerousCity_ArtClub_1F_Text_MelissaIntro, AerousCity_ArtClub_1F_Text_MelissaDefeated
	msgbox AerousCity_ArtClub_1F_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

AerousCity_ArtClub_1F_Text_MelissaIntro:
	.string "Hyah!\n"
	.string "Hyah!\p"
	.string "I strike twice, for double the\n"
	.string "effect!$"

AerousCity_ArtClub_1F_Text_MelissaDefeated:
	.string "Oh no, I lost…\n"
	.string "Oh no, I lost…$"

AerousCity_ArtClub_1F_Text_MelissaPostBattle:
	.string "You beat me…\n"
	.string "I lost!$"

AerousCity_ArtClub_1F_EventScript_Candice::
	trainerbattle_single TRAINER_CANDICE, AerousCity_ArtClub_1F_Text_CandiceIntro, AerousCity_ArtClub_1F_Text_CandiceDefeated
	msgbox AerousCity_ArtClub_1F_Text_CandicePostBattle, MSGBOX_AUTOCLOSE
	end

AerousCity_ArtClub_1F_Text_CandiceIntro:
	.string "Quick\n"
	.string "Let's battle!$"

AerousCity_ArtClub_1F_Text_CandiceDefeated:
	.string "Haste makes waste…$"

AerousCity_ArtClub_1F_Text_CandicePostBattle:
	.string "When you go at a thousand miles\n"
	.string "per hour, things become a blur.\p"
	.string "A beautiful, colorful blur… but\n"
	.string "still a blur.$"

AerousCity_ArtClub_1F_EventScript_Beverley::
	trainerbattle_single TRAINER_BEVERLEY, AerousCity_ArtClub_1F_Text_BeverleyIntro, AerousCity_ArtClub_1F_Text_BeverleyDefeated
	msgbox AerousCity_ArtClub_1F_Text_BeverleyPostBattle, MSGBOX_AUTOCLOSE
	end

AerousCity_ArtClub_1F_Text_BeverleyIntro:
	.string "Watch your step!$"

AerousCity_ArtClub_1F_Text_BeverleyDefeated:
	.string "That was hazardous…$"

AerousCity_ArtClub_1F_Text_BeverleyPostBattle:
	.string "Stealth Rocks are great!$"

AerousCity_ArtClub_1F_EventScript_Madelaine::
	trainerbattle_single TRAINER_MADELAINE, AerousCity_ArtClub_1F_Text_MadelaineIntro, AerousCity_ArtClub_1F_Text_MadelaineDefeated
	msgbox AerousCity_ArtClub_1F_Text_MadelainePostBattle, MSGBOX_AUTOCLOSE
	end

AerousCity_ArtClub_1F_Text_MadelaineIntro:
	.string "…\n"
	.string "I'm charging up…\p"
	.string "…\p"
	.string "Bring it on!$"

AerousCity_ArtClub_1F_Text_MadelaineDefeated:
	.string "I blew it…$"

AerousCity_ArtClub_1F_Text_MadelainePostBattle:
	.string "I prefer to wait…\n"
	.string "…and then strike!\p"
	.string "There's a certain beauty in\n"
	.string "patience, no?$"

AerousCity_ArtClub_1F_EventScript_Guard::
	lock
	faceplayer
	msgbox AerousCity_ArtClub_1F_Text_ImHereToGuardTheArtClub, MSGBOX_DEFAULT
	release
	end

AerousCity_ArtClub_1F_Text_ImHereToGuardTheArtClub:
	.string "I'm here to guard the Art Club.\p"
	.string "Some of these pieces can be sold\n"
	.string "for lots of money!\p"
	.string "So I make sure nothing gets stolen.$"

AerousCity_ArtClub_1F_EventScript_Painter::
	msgbox AerousCity_ArtClub_1F_Text_FinallyGotToShowVincentMyPainting, MSGBOX_NPC
	end

AerousCity_ArtClub_1F_Text_FinallyGotToShowVincentMyPainting:
	.string "I finally got to show Vincent my\n"
	.string "painting of Aerous Road.\p"
	.string "He didn't seem to like it…\n"
	.string "But that doesn't mean I'll give up!$"

AerousCity_ArtClub_1F_EventScript_Rocker::
	lock
	faceplayer
	msgbox AerousCity_ArtClub_1F_Text_YouDontUnderstandArtPunk, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousCity_ArtClub_1F_Text_YouDontUnderstandArtPunk:
	.string "You don't understand art, punk!$"

AerousCity_ArtClub_1F_EventScript_Lass::
	lock
	faceplayer
	msgbox AerousCity_ArtClub_1F_Text_ThisIsHisMasterpiece, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousCity_ArtClub_1F_Text_ThisIsHisMasterpiece:
	.string "…This is his masterpiece?\n"
	.string "I don't see the appeal.$"
