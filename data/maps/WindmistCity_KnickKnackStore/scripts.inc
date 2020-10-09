WindmistCity_KnickKnackStore_MapScripts::
	.byte 0

WindmistCity_KnickKnackStore_EventScript_ClerkLeft::
	lock
	faceplayer
	message WindmistCity_KnickKnackStore_Text_KnickKnackStoreYouBuy
	waitmessage
	pokemart WindmistCity_KnickKnackStore_Pokemart_Stock
	msgbox WindmistCity_KnickKnackStore_Text_PleaseReturn, MSGBOX_DEFAULT
	release
	end

WindmistCity_KnickKnackStore_Pokemart_Stock:
	.2byte ITEM_FRESH_WATER
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_NONE
	release
	end

WindmistCity_KnickKnackStore_Text_KnickKnackStoreYouBuy:
	.string "Hello. Knick-knack store!\n"
	.string "You buy, yes?$"

WindmistCity_KnickKnackStore_Text_PleaseReturn:
	.string "Please return, yes!$"

WindmistCity_KnickKnackStore_EventScript_ClerkRight::
	lock
	faceplayer
	message WindmistCity_KnickKnackStore_Text_WelcomeTraveler
	waitmessage
	pokemart WindmistCity_KnickKnackStore_Pokemart_MooMooMilk
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

WindmistCity_KnickKnackStore_Pokemart_MooMooMilk:
	.2byte ITEM_MOOMOO_MILK
	.2byte ITEM_NONE
	release
	end

WindmistCity_KnickKnackStore_Text_WelcomeTraveler:
	.string "Welcome, traveler!\n"
	.string "How can I help you?$"

WindmistCity_KnickKnackStore_EventScript_Explorer::
	lock
	faceplayer
	msgbox WindmistCity_KnickKnackStore_Text_YouNeverKnowWhatDangersAreOutThere, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_KnickKnackStore_Text_YouNeverKnowWhatDangersAreOutThere:
	.string "You never know what dangers are\n"
	.string "out there in the wild.\p"
	.string "Chansey here keeps my Pokémon and\n"
	.string "I safe!$"

WindmistCity_KnickKnackStore_EventScript_Chansey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHANSEY, 0
	msgbox WindmistCity_KnickKnackStore_Text_Chansey, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_KnickKnackStore_Text_Chansey:
	.string "Chansey: {COLOR RED}Buri-ee!$"

WindmistCity_KnickKnackStore_EventScript_SlowbroniteFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SLOWBRONITE, WindmistCity_KnickKnackStore_EventScript_ExplainSlowbronite
	msgbox WindmistCity_KnickKnackStore_Text_DoYouEverGetAnUrgeToSee, MSGBOX_DEFAULT
	setvar VAR_0x8004, SPECIES_SLOWPOKE
	specialvar VAR_RESULT, CheckPartyForMon
	compare VAR_RESULT, TRUE
	goto_if_eq WindmistCity_KnickKnackStore_EventScript_GiveSlowbronite
	release
	end

WindmistCity_KnickKnackStore_EventScript_GiveSlowbronite:
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox WindmistCity_KnickKnackStore_Text_ThatSlowpokeIsGreat, MSGBOX_DEFAULT
	giveitem ITEM_SLOWBRONITE
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SLOWBRONITE
	goto WindmistCity_KnickKnackStore_EventScript_ExplainSlowbronite
	end

WindmistCity_KnickKnackStore_EventScript_ExplainSlowbronite:
	msgbox WindmistCity_KnickKnackStore_Text_SlowbroCanMegaEvolve, MSGBOX_DEFAULT
	release
	end

WindmistCity_KnickKnackStore_Text_DoYouEverGetAnUrgeToSee:
	.string "Do you ever get an urge to see a\n"
	.string "certain type of Pokémon?\p"
	.string "Me?\n"
	.string "I've got that Slowpoke itch.\p"
	.string "If you show me one, I can give you\n"
	.string "a reward!$"

WindmistCity_KnickKnackStore_Text_ThatSlowpokeIsGreat:
	.string "That Slowpoke is great!\n"
	.string "Here's your prize!$"

WindmistCity_KnickKnackStore_Text_SlowbroCanMegaEvolve:
	.string "Slowbro can Mega Evolve with that\n"
	.string "Mega Stone!$"

WindmistCity_KnickKnackStore_EventScript_Rancher::
	msgbox WindmistCity_KnickKnackStore_Text_TheMooMooMilkTheyServeHere, MSGBOX_NPC
	end

WindmistCity_KnickKnackStore_Text_TheMooMooMilkTheyServeHere:
	.string "The Moomoo Milk they serve here is\n"
	.string "nutritious and delicious!$"

WindmistCity_KnickKnackStore_EventScript_Hiker::
	msgbox WindmistCity_KnickKnackStore_Text_WowTheSecretPotion, MSGBOX_NPC
	end

WindmistCity_KnickKnackStore_Text_WowTheSecretPotion:
	.string "Wow, the SecretPotion they sell\n"
	.string "here really packs a punch!\p"
	.string "It healed my chronically ill\n"
	.string "Pokémon right away!$"
