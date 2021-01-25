BattleMarsh_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleMarsh_1F_OnTransition
	.byte 0

BattleMarsh_1F_OnTransition:
	setrespawn HEAL_LOCATION_BATTLE_MARSH
	end

BattleMarsh_1F_EventScript_BPShopClerk::
	lock
	faceplayer
	msgbox BattleMarsh_1F_Text_WouldYouLikeToRedeemBP, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BattleMarsh_1F_EventScript_ShowBPShopStock
	goto BattleMarsh_1F_EventScript_PleaseComeAgain
	end

BattleMarsh_1F_EventScript_ShowBPShopStock:
	// TODO: Implement
	goto BattleMarsh_1F_EventScript_PleaseComeAgain
	end

BattleMarsh_1F_EventScript_PleaseComeAgain:
	msgbox BattleMarsh_1F_Text_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

BattleMarsh_1F_Text_WouldYouLikeToRedeemBP:
	.string "Hello! Would you like to redeem\n"
	.string "your Battle Points?$"

BattleMarsh_1F_Text_PleaseComeAgain:
	.string "Please come again!$"

BattleMarsh_1F_EventScript_BlackBelt::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BATTLE_MARSH_FOCUS_SASH, BattleMarsh_1F_EventScript_ReceivedFocusSash
	msgbox BattleMarsh_1F_Text_ImNeverGonnaWin, MSGBOX_DEFAULT
	giveitem ITEM_FOCUS_SASH
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_BATTLE_MARSH_FOCUS_SASH
	goto BattleMarsh_1F_EventScript_ReceivedFocusSash
	end

BattleMarsh_1F_EventScript_ReceivedFocusSash:
	msgbox BattleMarsh_1F_Text_ExplainFocusSash, MSGBOX_DEFAULT
	release
	end

BattleMarsh_1F_Text_ImNeverGonnaWin:
	.string "Sigh…\n"
	.string "I've lost it all!\p"
	.string "I'm never gonna win!\n"
	.string "I give up. Take this!$"

BattleMarsh_1F_Text_ExplainFocusSash:
	.string "Maybe you'll be able to use that\n"
	.string "Focus Sash better than I could!\p"
	.string "A Pokémon holding it will endure a\n"
	.string "hit, no matter how powerful.$"

BattleMarsh_1F_EventScript_AceTrainerM::
	msgbox BattleMarsh_1F_Text_ExplainAbilityPill, MSGBOX_NPC
	end

BattleMarsh_1F_Text_ExplainAbilityPill:
	.string "With an Ability Pill, Pokémon can\n"
	.string "change their Ability!$"

BattleMarsh_1F_EventScript_BattleGirl::
	msgbox BattleMarsh_1F_Text_IForgotToEat, MSGBOX_NPC
	end

BattleMarsh_1F_Text_IForgotToEat:
	.string "It's been such an intense day of\n"
	.string "battling…\p"
	.string "I completely forgot to eat!$"

BattleMarsh_1F_EventScript_AceTrainerF::
	lock
	faceplayer
	msgbox BattleMarsh_1F_Text_IFeedMyPidgeotLumBerries, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleMarsh_1F_Text_IFeedMyPidgeotLumBerries:
	.string "I feed my Pidgeot Lum Berries when\n"
	.string "she gets poisoned.$"

BattleMarsh_1F_EventScript_Pidgeot::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEOT, 0
	msgbox BattleMarsh_1F_Text_Pidgeot, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleMarsh_1F_Text_Pidgeot:
	.string "Pidgeot: {COLOR RED}Bi-bibii!$"
