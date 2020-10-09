WindmistCity_LumberjackRestStop_MapScripts::
	.byte 0

WindmistCity_LumberjackRestStop_EventScript_Clerk::
	lock
	faceplayer
	message WindmistCity_LumberjackRestStop_Text_WeSellTMs
	waitmessage
	pokemart WindmistCity_LumberjackRestStop_Pokemart_TMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

WindmistCity_LumberjackRestStop_Pokemart_TMs:
	.2byte ITEM_NONE
	release
	end

WindmistCity_LumberjackRestStop_Text_WeSellTMs:
	.string "We're selling TMs to raise funds!\n"
	.string "How can I help you?$"

WindmistCity_LumberjackRestStop_EventScript_Kindler::
	msgbox WindmistCity_LumberjackRestStop_Text_ThisFirewoodIsPerfect, MSGBOX_NPC
	end

WindmistCity_LumberjackRestStop_Text_ThisFirewoodIsPerfect:
	.string "This firewood is perfect for\n"
	.string "kindling!$"

WindmistCity_LumberjackRestStop_EventScript_BlackBelt::
	lock
	faceplayer
	msgbox WindmistCity_LumberjackRestStop_Text_MachopAndI, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_LumberjackRestStop_Text_MachopAndI:
	.string "My Machop and I run a roof-\n"
	.string "cleaning service!\p"
	.string "We'll shovel snow off your roof\n"
	.string "for a low, low price!\p"
	.string "What?\n"
	.string "You're not a home-owner?\p"
	.string "…Oh.$"

WindmistCity_LumberjackRestStop_EventScript_Machop::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOP, 0
	msgbox WindmistCity_LumberjackRestStop_Text_Machop, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_LumberjackRestStop_Text_Machop:
	.string "Machop: {COLOR BLUE}Guoh! Gogogoh!$"

WindmistCity_LumberjackRestStop_EventScript_BattleGirl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXPERT_BELT, WindmistCity_LumberjackRestStop_EventScript_ExplainWhereToFindPorygon
	goto_if_set FLAG_BADGE03_GET, WindmistCity_LumberjackRestStop_EventScript_TryGiveExpertBelt
	msgbox WindmistCity_LumberjackRestStop_Text_YouSeemTough, MSGBOX_DEFAULT
	release
	end

WindmistCity_LumberjackRestStop_EventScript_TryGiveExpertBelt:
	msgbox WindmistCity_LumberjackRestStop_Text_YouWonTheEmberBadge, MSGBOX_DEFAULT
	giveitem ITEM_EXPERT_BELT, 1
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXPERT_BELT
	goto WindmistCity_LumberjackRestStop_EventScript_ExplainWhereToFindPorygon
	end

WindmistCity_LumberjackRestStop_EventScript_ExplainWhereToFindPorygon:
	msgbox WindmistCity_LumberjackRestStop_Text_AnExpertTrainerLikeYou, MSGBOX_DEFAULT
	release
	end

WindmistCity_LumberjackRestStop_Text_YouSeemTough:
	.string "You seem tough… I've got something\n"
	.string "for you, if you can beat Nina.$"

WindmistCity_LumberjackRestStop_Text_YouWonTheEmberBadge:
	.string "You won the Ember Badge?\n"
	.string "I insist you take this Expert Belt!$"

WindmistCity_LumberjackRestStop_Text_AnExpertTrainerLikeYou:
	.string "An expert Trainer like you should\n"
	.string "know what that Expert Belt does.$"

WindmistCity_LumberjackRestStop_EventScript_Hiker::
	lock
	faceplayer
	msgbox WindmistCity_LumberjackRestStop_Text_ThereIsNoMonster, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_LumberjackRestStop_Text_ThereIsNoMonster:
	.string "There is no {COLOR GREEN}monster{COLOR BLUE}…\n"
	.string "You guys are just hearing things!$"

WindmistCity_LumberjackRestStop_EventScript_Explorer::
	lock
	faceplayer
	msgbox WindmistCity_LumberjackRestStop_Text_IHeardTheMonster, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_LumberjackRestStop_Text_IHeardTheMonster:
	.string "I heard the {COLOR GREEN}monster{COLOR RED}!\n"
	.string "It lives in Rimewood Forest.$"
