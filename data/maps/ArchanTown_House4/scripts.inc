ArchanTown_House4_MapScripts::
	.byte 0

ArchanTown_House4_EventScript_Woman::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_HOUSE_STINGA_BOY, ArchanTown_House4_EventScript_TryGiveBerries
	msgbox ArchanTown_House4_Text_MySonsWeedle, MSGBOX_DEFAULT
	release
	end

ArchanTown_House4_EventScript_TryGiveBerries:
	goto_if_set FLAG_RECEIVED_STINGA_BERRIES, ArchanTown_House4_EventScript_WomanThankYou
	msgbox ArchanTown_House4_Text_YouHelpedTakeThese, MSGBOX_DEFAULT
	giveitem ITEM_ORAN_BERRY, 3
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_STINGA_BERRIES
	release
	end

ArchanTown_House4_EventScript_WomanThankYou:
	msgbox ArchanTown_House4_Text_MySonIsRelieved, MSGBOX_DEFAULT
	release
	end

ArchanTown_House4_Text_MySonsWeedle:
	.string "My son's Weedle went missing in\n"
	.string "the Archan Tunnel after a tremor.\p"
	.string "He's very upset, but it's just too\n"
	.string "dangerous to go searching for it!$"

ArchanTown_House4_Text_YouHelpedTakeThese:
	.string "You helped my son find his Weedle?\n"
	.string "Thank you! Please, take these.$"

ArchanTown_House4_Text_MySonIsRelieved:
	.string "My son is relieved now that\n"
	.string "he knows his Pokémon is safe.\p"
	.string "Thank you so much for helping!$"

ArchanTown_House4_EventScript_StingaBoy::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_STINGA_SOOTHE_BELL, ArchanTown_House4_EventScript_TryGiveSootheBell
	msgbox ArchanTown_House4_Text_ThanksAgain, MSGBOX_DEFAULT
	release
	end

ArchanTown_House4_EventScript_TryGiveSootheBell:
	msgbox ArchanTown_House4_Text_HeyThankYou, MSGBOX_DEFAULT
	giveitem ITEM_SOOTHE_BELL
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_STINGA_SOOTHE_BELL
	release
	end

ArchanTown_House4_Text_ThanksAgain:
	.string "Thanks again for rescuing Stinga!$"

ArchanTown_House4_Text_HeyThankYou:
	.string "Hey, thank you for saving Stinga!\n"
	.string "I want you to have this.$"

ArchanTown_House4_EventScript_Stinga::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WEEDLE, 0
	msgbox ArchanTown_House4_Text_Stinga, MSGBOX_DEFAULT
	closemessage
	release
	end

ArchanTown_House4_Text_Stinga:
	.string "Stinga: {COLOR BLUE}Burrk!$"
