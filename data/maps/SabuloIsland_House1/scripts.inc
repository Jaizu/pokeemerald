SabuloIsland_House1_MapScripts::
	.byte 0

SabuloIsland_House1_EventScript_UltraBallSwapper::
	lock
	faceplayer
	msgbox SabuloIsland_House1_Text_YouveGotToBeUltraTough, MSGBOX_DEFAULT
	bufferleadmonspeciesname 0
	specialvar VAR_RESULT GetLeadMonBall
	compare VAR_RESULT, ITEM_ULTRA_BALL
	goto_if_ne SabuloIsland_House1_EventScript_OfferToSwap
	msgbox SabuloIsland_House1_Text_ISeeYouUnderstandThat, MSGBOX_DEFAULT
	release
	end

SabuloIsland_House1_EventScript_OfferToSwap:
	msgbox SabuloIsland_House1_Text_YouDoWantToBeatBelleRight, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SabuloIsland_House1_EventScript_SwapBallForUltra
	msgbox SabuloIsland_House1_Text_MaybeYouJustWantAChallenge, MSGBOX_DEFAULT
	release
	end

SabuloIsland_House1_EventScript_SwapBallForUltra:
	msgbox SabuloIsland_House1_Text_YouveGotTheRightAttitude, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004 ITEM_ULTRA_BALL
	special SetLeadMonBall
	fadescreen FADE_FROM_BLACK
	msgbox SabuloIsland_House1_Text_RightOn, MSGBOX_DEFAULT
	release
	end

SabuloIsland_House1_Text_YouveGotToBeUltraTough:
	.string "You've got to be ultra tough to\n"
	.string "get by on this island.\p"
	.string "Like my Machop there. He's in an\n"
	.string "Ultra Ball, just to prove it.$"

SabuloIsland_House1_Text_ISeeYouUnderstandThat:
	.string "I see you understand that, though.\p"
	.string "Your {STR_VAR_1} is already\n"
	.string "in an Ultra Ball!$"

SabuloIsland_House1_Text_YouDoWantToBeatBelleRight:
	.string "Your {STR_VAR_1}…\n"
	.string "You do want to beat Belle, right?\p"
	.string "It will struggle being ultra tough\n"
	.string "in that Ball.\p"
	.string "Let me switch its Ball?$"
	
SabuloIsland_House1_Text_MaybeYouJustWantAChallenge:
	.string "Hm, maybe you just want a\n"
	.string "challenge.$"

SabuloIsland_House1_Text_YouveGotTheRightAttitude:
	.string "You've got the right attitude!$"

SabuloIsland_House1_Text_RightOn:
	.string "Right on!\n"
	.string "Ultra tough, as nature intended!$"

SabuloIsland_House1_EventScript_Machop::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOP, 0
	msgbox SabuloIsland_House1_Text_Machop, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SabuloIsland_House1_Text_Machop:
	.string "Machop: {COLOR BLUE}Guoh! Gogogoh!$"
