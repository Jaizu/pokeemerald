AerousCity_Museum_1F_MapScripts::
	.byte 0

AerousCity_Museum_1F_EventScript_Teala::
	lock
	faceplayer
	compare VAR_AEROUS_MUSEUM_STATE, 1
	goto_if_lt AerousCity_Museum_1F_EventScript_TealaExplainNewEldersPresence
	msgbox AerousCity_Museum_1F_Text_EnjoyPerusingOurSubjects, MSGBOX_DEFAULT
	release
	end

AerousCity_Museum_1F_EventScript_TealaExplainNewEldersPresence:
	msgbox AerousCity_Museum_1F_Text_WelcomeUpstairsRentedToSomeOrganization, MSGBOX_DEFAULT
	release
	end

AerousCity_Museum_1F_Text_EnjoyPerusingOurSubjects:
	.string "Hello!\n"
	.string "Enjoy perusing our subjects!$"

AerousCity_Museum_1F_Text_WelcomeUpstairsRentedToSomeOrganization:
	.string "Hello, welcome to the\n"
	.string "Aerous Museum!\p"
	.string "It seems the top floor has been\n"
	.string "rented to…\p"
	.string "Well, some kind of organization…\p"
	.string "Enjoy perusing our subjects!$"

AerousCity_Museum_1F_EventScript_SouvenirShopClerk::
	lock
	faceplayer
	message AerousCity_Museum_1F_Text_WouldYouLikeToBuySouvenir
	waitmessage
	pokemart AerousCity_Museum_1F_Pokemart_SouvenirShop
	goto EventScript_MartClerkPleaseComeAgain
	end

AerousCity_Museum_1F_Pokemart_SouvenirShop:
	.2byte ITEM_POKE_DOLL
	.2byte ITEM_NONE
	release
	end

AerousCity_Museum_1F_Text_WouldYouLikeToBuySouvenir:
	.string "Hi, there!\n"
	.string "Would you like to buy a souvenir?$"

AerousCity_Museum_1F_EventScript_RelicBallSwapper::
	lock
	faceplayer
	msgbox AerousCity_Museum_1F_Text_RelicBallsAreIncrediblyRare, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_NEW_ELDERS, AerousCity_Museum_1F_EventScript_CheckForRelicBall
	msgbox AerousCity_Museum_1F_Text_ImWorkingOnFindingASource, MSGBOX_DEFAULT
	release
	end

AerousCity_Museum_1F_EventScript_CheckForRelicBall:
	bufferleadmonspeciesname 0
	specialvar VAR_RESULT GetLeadMonBall
	compare VAR_RESULT, ITEM_RELIC_BALL
	goto_if_ne AerousCity_Museum_1F_EventScript_OfferToSwap
	msgbox AerousCity_Museum_1F_Text_WhoaWhereDidYouFindOne, MSGBOX_DEFAULT
	release
	end

AerousCity_Museum_1F_EventScript_OfferToSwap:
	msgbox AerousCity_Museum_1F_Text_WantMeToSwapYourPokemonsBall, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq AerousCity_Museum_1F_EventScript_SwapBallForRelic
	msgbox AerousCity_Museum_1F_Text_GoodLuckFindingThemSomewhereElse, MSGBOX_DEFAULT
	release
	end

AerousCity_Museum_1F_EventScript_SwapBallForRelic:
	msgbox AerousCity_Museum_1F_Text_GoodChoiceKid, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004 ITEM_RELIC_BALL
	special SetLeadMonBall
	fadescreen FADE_FROM_BLACK
	msgbox AerousCity_Museum_1F_Text_SpreadTheWord, MSGBOX_DEFAULT
	release
	end

AerousCity_Museum_1F_Text_RelicBallsAreIncrediblyRare:
	.string "Relic Balls are incredibly rare.$"

AerousCity_Museum_1F_Text_ImWorkingOnFindingASource:
	.string "I'm working on finding a source\n"
	.string "who says he can get me some…\p"
	.string "Come back to me in a while, yeah?\p"
	.string "I might be able to hook you up…$"

AerousCity_Museum_1F_Text_WhoaWhereDidYouFindOne:
	.string "Whoa! Where did you find\n"
	.string "one for your {STR_VAR_1}?$"

AerousCity_Museum_1F_Text_WantMeToSwapYourPokemonsBall:
	.string "I have a source who can get me\n"
	.string "loads of them on the cheap.\p"
	.string "Want me to swap your {STR_VAR_1}'s\n"
	.string "Ball to a Relic Ball?$"
	
AerousCity_Museum_1F_Text_GoodLuckFindingThemSomewhereElse:
	.string "Psh, good luck finding them\n"
	.string "somewhere else…$"

AerousCity_Museum_1F_Text_GoodChoiceKid:
	.string "Good choice, kid!$"

AerousCity_Museum_1F_Text_SpreadTheWord:
	.string "Spread the word, yeah?$"

AerousCity_Museum_1F_EventScript_OldMan::
	msgbox AerousCity_Museum_1F_Text_SomeOfTheseFossils, MSGBOX_NPC
	end

AerousCity_Museum_1F_Text_SomeOfTheseFossils:
	.string "Some of these Fossils have been\n"
	.string "donated by faraway regions!$"

AerousCity_Museum_1F_EventScript_Grunt::
	trainerbattle_single TRAINER_MUSEUM_GRUNT_1, AerousCity_Museum_1F_Text_GruntIntro, AerousCity_Museum_1F_Text_GruntDefeated
	msgbox AerousCity_Museum_1F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
	end

AerousCity_Museum_1F_Text_GruntIntro:
	.string "Nobody can go upstairs.\n"
	.string "Important business is going on.\p"
	.string "Don't look at me like that!$"

AerousCity_Museum_1F_Text_GruntDefeated:
	.string "Fine, go upstairs.$"

AerousCity_Museum_1F_Text_GruntPostBattle:
	.string "You can go upstairs, but you won't\n"
	.string "be welcomed!$"

AerousCity_Museum_1F_EventScript_Fossil::
	msgbox AerousCity_Museum_1F_Text_Fossil, MSGBOX_SIGN
	end

AerousCity_Museum_1F_Text_Fossil:
	.string "It is a Fossil of some sort.\n"
	.string "Prof. Redwood would love this!$"

AerousCity_Museum_1F_EventScript_RelicBall::
	msgbox AerousCity_Museum_1F_Text_RelicBall, MSGBOX_SIGN
	end

AerousCity_Museum_1F_Text_RelicBall:
	.string "It's a rare Relic Ball!$"
