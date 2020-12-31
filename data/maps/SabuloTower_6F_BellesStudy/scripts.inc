.set LOCALID_BELLE, 1

SabuloTower_6F_BellesStudy_MapScripts::
	.byte 0

SabuloTower_6F_BellesStudy_EventScript_Belle::
	lock
	faceplayer
	goto_if_set FLAG_DIDNT_RECEIVE_KANTO_STARTER, SabuloTower_6F_BellesStudy_EventScript_TryGiveKantoStarter
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

SabuloTower_6F_BellesStudy_EventScript_TryGiveKantoStarter:
	compare VAR_STARTER_MON, 0 // Player chose Turtwig
	call_if_eq SabuloTower_6F_BellesStudy_EventScript_SetWartortle
	compare VAR_STARTER_MON, 1 // Player chose Chimchar
	call_if_eq SabuloTower_6F_BellesStudy_EventScript_SetIvysaur
	compare VAR_STARTER_MON, 2 // Player chose Piplup
	call_if_eq SabuloTower_6F_BellesStudy_EventScript_SetCharmeleon
	givemon VAR_TEMP_1, 25, VAR_TEMP_2
	copyvar VAR_0x8009, VAR_RESULT
	compare VAR_0x8009, 0
	call_if_eq SabuloTower_6F_BellesStudy_EventScript_ReceiveMonParty
	compare VAR_0x8009, 1
	call_if_eq SabuloTower_6F_BellesStudy_EventScript_ReceiveMonPC
	compare VAR_0x8009, 1
	call_if_gt SabuloTower_6F_BellesStudy_EventScript_NoMoreRoomForPokemon
	goto SabuloTower_6F_BellesStudy_EventScript_FaceOriginalDirection
	end

SabuloTower_6F_BellesStudy_EventScript_SetWartortle:
	setvar VAR_TEMP_1, SPECIES_WARTORTLE
	setvar VAR_TEMP_2, ITEM_BLASTOISINITE
	return

SabuloTower_6F_BellesStudy_EventScript_SetIvysaur:
	setvar VAR_TEMP_1, SPECIES_IVYSAUR
	setvar VAR_TEMP_2, ITEM_VENUSAURITE
	return

SabuloTower_6F_BellesStudy_EventScript_SetCharmeleon:
	setvar VAR_TEMP_1, SPECIES_CHARMELEON
	setvar VAR_TEMP_2, ITEM_CHARIZARDITE_Y
	return

SabuloTower_6F_BellesStudy_EventScript_ReceiveMonParty::
	call SabuloTower_6F_BellesStudy_EventScript_ReceivedMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SabuloTower_6F_BellesStudy_EventScript_FinishReceivingMon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto SabuloTower_6F_BellesStudy_EventScript_FinishReceivingMon
	end

SabuloTower_6F_BellesStudy_EventScript_ReceiveMonPC::
	call SabuloTower_6F_BellesStudy_EventScript_ReceivedMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SabuloTower_6F_BellesStudy_EventScript_TransferMonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto SabuloTower_6F_BellesStudy_EventScript_TransferMonToPC
	end

SabuloTower_6F_BellesStudy_EventScript_TransferMonToPC::
	call Common_EventScript_TransferredToPC
	goto SabuloTower_6F_BellesStudy_EventScript_FinishReceivingMon
	end

SabuloTower_6F_BellesStudy_EventScript_ReceivedMonFanfare::
	bufferspeciesname 1, VAR_TEMP_1
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message SabuloTower_6F_BellesStudy_Text_ReceivedMonFromBelle
	waitmessage
	waitfanfare
	bufferspeciesname 0, VAR_TEMP_1
	return

SabuloTower_6F_BellesStudy_EventScript_NoMoreRoomForPokemon:
	msgbox gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
	msgbox SabuloTower_6F_BellesStudy_Text_WhenYouMakeRoom, MSGBOX_DEFAULT
	closemessage
	return

SabuloTower_6F_BellesStudy_EventScript_FinishReceivingMon:
	setflag FLAG_RECEIVED_KANTO_STARTER
	clearflag FLAG_DIDNT_RECEIVE_KANTO_STARTER
	msgbox SabuloTower_6F_BellesStudy_Text_IfYouTrainThatPokemon, MSGBOX_DEFAULT
	closemessage
	return

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

SabuloTower_6F_BellesStudy_Text_ReceivedMonFromBelle:
	.string "{COLOR DARK_GREY}{PLAYER} received {STR_VAR_2}\n"
	.string "from Belle!$"

SabuloTower_6F_BellesStudy_Text_IfYouTrainThatPokemon:
	.string "Belle: {COLOR RED}If you train that Pokémon\n"
	.string "enough, it will evolve and be able\l"
	.string "to use its Mega Stone!\p"
	.string "You have potential for greatness\n"
	.string "{PLAYER}.\p"
	.string "I'm glad my judgment was correct!\n"
	.string "Good luck out there.$"

SabuloTower_6F_BellesStudy_Text_WhenYouMakeRoom:
	.string "Belle: {COLOR RED}When you make room, come and\n"
	.string "see me, okay?\p"
	.string "I will hold onto this Pokémon, in\n"
	.string "the mean time.\p"
	.string "Thanks once more for your help,\n"
	.string "{PLAYER}!$"

SabuloTower_6F_BellesStudy_EventScript_Book::
	lock
	msgbox SabuloTower_6F_BellesStudy_Text_ItsBellesBook, MSGBOX_DEFAULT
	release
	end

SabuloTower_6F_BellesStudy_Text_ItsBellesBook:
	.string "It is one of Belle's books.\p"
	.string "It describes an island that\n"
	.string "sparkles at night.$"
