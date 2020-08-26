ArchanTown_House1_MapScripts::
	.byte 0
	
ArchanTown_House1_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_ARCHAN_HOUSE_POTION, ArchanTown_House1_EventScript_ReceivedPotion
	msgbox ArchanTown_House1_Text_YoureANewTrainerTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_POTION
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_ARCHAN_HOUSE_POTION
	goto ArchanTown_House1_EventScript_ReceivedPotion
	end

ArchanTown_House1_EventScript_ReceivedPotion:
	msgbox ArchanTown_House1_Text_ItsImportantToKeepPokemonHealthy, MSGBOX_DEFAULT
	release
	end

ArchanTown_House1_Text_YoureANewTrainerTakeThis:
	.string "You're a new Trainer?\n"
	.string "Take this!$"

ArchanTown_House1_Text_ItsImportantToKeepPokemonHealthy:
	.string "It's important to keep your\n"
	.string "Pokémon healthy at all times!$"
