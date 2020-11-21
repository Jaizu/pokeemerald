.set LOCALID_BELLE, 1

SabuloTower_6F_BellesStudy_MapScripts::
	.byte 0

SabuloTower_6F_BellesStudy_EventScript_Belle::
	lock
	faceplayer
	msgbox SabuloTower_6F_BellesStudy_Text_DoYouRememberHowMegaEvolutionWorks, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SabuloTower_6F_BellesStudy_EventScript_ExplainMegaEvolution
	msgbox SabuloTower_6F_BellesStudy_Text_RememberMegaEvolutionIsAMightyPower, MSGBOX_DEFAULT
	closemessage
	goto SabuloTower_6F_BellesStudy_EventScript_FaceOriginalDirection
	end

SabuloTower_6F_BellesStudy_EventScript_ExplainMegaEvolution:
	msgbox MegaEvolution_Text_ExplainMegaEvolution, MSGBOX_DEFAULT
	closemessage
	goto SabuloTower_6F_BellesStudy_EventScript_FaceOriginalDirection
	end

SabuloTower_6F_BellesStudy_EventScript_FaceOriginalDirection:
	applymovement LOCALID_BELLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SabuloTower_6F_BellesStudy_Text_DoYouRememberHowMegaEvolutionWorks:
	.string "{COLOR DARK_GREY}Belle: {COLOR RED}Ah, {PLAYER}.\n"
	.string "How do you fare?\p"
	.string "Have you wielded the power of\n"
	.string "Mega Evolution, yet?\p"
	.string "Do you remember how it works?$"

SabuloTower_6F_BellesStudy_Text_RememberMegaEvolutionIsAMightyPower:
	.string "Fine. Remember, Mega Evolution is\n"
	.string "a mighty power.\p"
	.string "You must use it responsibly, and\n"
	.string "for the forces of good!$"

SabuloTower_6F_BellesStudy_EventScript_Book::
	lock
	msgbox SabuloTower_6F_BellesStudy_Text_ItsBellesBook, MSGBOX_DEFAULT
	release
	end

SabuloTower_6F_BellesStudy_Text_ItsBellesBook:
	.string "It is one of Belle's books.\p"
	.string "It describes an island that\n"
	.string "sparkles at night.$"
