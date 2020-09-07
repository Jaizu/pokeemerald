// TODO: Define these
.equ FLAG_DEFEATED_NEW_ELDERS, 0
.equ ITEM_RELIC_BALL, ITEM_POKE_BALL

AerousCity_Museum_1F_MapScripts::
	.byte 0

AerousCity_Museum_1F_EventScript_Teala::
	msgbox AerousCity_Museum_1F_Text_WelcomeUpstairsRentedToSomeOrganization, MSGBOX_NPC
	end

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
	message gText_HowMayIServeYou
	waitmessage
	pokemart AerousCity_Museum_1F_Pokemart_SouvenirShop
	goto EventScript_MartClerkPleaseComeAgain
	end

AerousCity_Museum_1F_Pokemart_SouvenirShop:
	.2byte ITEM_POKE_DOLL
	.2byte ITEM_NONE
	release
	end

AerousCity_Museum_1F_EventScript_RelicBallSwapper::
	lock
	faceplayer
	msgbox AerousCity_Museum_1F_Text_RelicBallsAreIncrediblyRare, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_NEW_ELDERS, AerousCity_Museum_1F_EventScript_CheckForRelicBall
	release
	end

AerousCity_Museum_1F_EventScript_CheckForRelicBall:
	bufferleadmonspeciesname 0
	setvar VAR_0x8004 0 // Party slot
	specialvar VAR_0x8005 GetPartyPokemonBall
	compare VAR_0x8005, ITEM_RELIC_BALL
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
	setvar VAR_0x8004 0 // Party slot
	setvar VAR_0x8005 ITEM_RELIC_BALL // Ball to change to
	special SetPartyPokemonBall
	fadescreen FADE_FROM_BLACK
	msgbox AerousCity_Museum_1F_Text_SpreadTheWord, MSGBOX_DEFAULT
	release
	end

AerousCity_Museum_1F_Text_RelicBallsAreIncrediblyRare:
	.string "Relic Balls are incredibly rare.$"

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
