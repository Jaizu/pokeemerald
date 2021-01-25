CelantoTown_Condominiums_2F_MapScripts::
	.byte 0

CelantoTown_Condominiums_2F_EventScript_PremierBallSwapper::
	lock
	faceplayer
	msgbox CelantoTown_Condominiums_2F_Text_ImObsessedWithPremierBalls, MSGBOX_DEFAULT
	goto_if_set FLAG_SYS_POKEMON_GET, CelantoTown_Condominiums_2F_EventScript_CheckForPremierBall
	release
	end

CelantoTown_Condominiums_2F_EventScript_CheckForPremierBall:
	bufferleadmonspeciesname 0
	specialvar VAR_RESULT GetLeadMonBall
	compare VAR_RESULT, ITEM_PREMIER_BALL
	goto_if_ne CelantoTown_Condominiums_2F_EventScript_OfferToSwap
	msgbox CelantoTown_Condominiums_2F_Text_OhGoodTaste, MSGBOX_DEFAULT
	release
	end

CelantoTown_Condominiums_2F_EventScript_OfferToSwap:
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_Condominiums_2F_Text_OhDearYourPokemon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq CelantoTown_Condominiums_2F_EventScript_SwapBallForPremier
	msgbox CelantoTown_Condominiums_2F_Text_HowCouldYouDoThisToMe, MSGBOX_DEFAULT
	release
	end

CelantoTown_Condominiums_2F_EventScript_SwapBallForPremier:
	msgbox CelantoTown_Condominiums_2F_Text_ThankGoodness, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004 ITEM_PREMIER_BALL
	special SetLeadMonBall
	fadescreen FADE_FROM_BLACK
	msgbox CelantoTown_Condominiums_2F_Text_AhMuchBetter, MSGBOX_DEFAULT
	release
	end

CelantoTown_Condominiums_2F_Text_ImObsessedWithPremierBalls:
	.string "I'm obsessed with Premier Balls.$"

CelantoTown_Condominiums_2F_Text_OhGoodTaste:
	.string "Oh, good taste! I see that your\n"
	.string "{STR_VAR_1} is in one!$"

CelantoTown_Condominiums_2F_Text_OhDearYourPokemon:
	.string "Oh dear!\n"
	.string "Your {STR_VAR_1}!\p"
	.string "Please, for my sake, swap its\n"
	.string "Ball with a Premier Ball?$"
	
CelantoTown_Condominiums_2F_Text_HowCouldYouDoThisToMe:
	.string "How could you do this to me?\n"
	.string "Ugh!$"

CelantoTown_Condominiums_2F_Text_ThankGoodness:
	.string "Thank goodness!\n"
	.string "One Premier Ball, coming up!$"

CelantoTown_Condominiums_2F_Text_AhMuchBetter:
	.string "Ahh… Much better!\n"
	.string "Doesn't that feel better?$"

CelantoTown_Condominiums_2F_EventScript_Fisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_OLD_ROD, CelantoTown_Condominiums_2F_EventScript_ExplainOldRod
	msgbox CelantoTown_Condominiums_2F_Text_WeFishermenRespectSkill, MSGBOX_DEFAULT
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq CelantoTown_Condominiums_2F_EventScript_GiveOldRod
	release
	end

CelantoTown_Condominiums_2F_EventScript_GiveOldRod:
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_Condominiums_2F_Text_GreatYouveGotAFullTeam, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	setflag FLAG_RECEIVED_OLD_ROD
	goto CelantoTown_Condominiums_2F_EventScript_ExplainOldRod
	end

CelantoTown_Condominiums_2F_EventScript_ExplainOldRod:
	msgbox CelantoTown_Condominiums_2F_Text_YouCanUseThatOldRod, MSGBOX_DEFAULT
	release
	end

CelantoTown_Condominiums_2F_Text_WeFishermenRespectSkill:
	.string "We Fishermen respect skill!\n"
	.string "Yessir, we do!\p"
	.string "Say, are you good enough to get\n"
	.string "{COLOR GREEN}six Pokémon{COLOR BLUE}?$"

CelantoTown_Condominiums_2F_Text_YouCanUseThatOldRod:
	.string "You can use that Old Rod to fish\n"
	.string "for Pokémon living in the water!$"

CelantoTown_Condominiums_2F_Text_GreatYouveGotAFullTeam:
	.string "Great!\n"
	.string "You've got a full team of six.\p"
	.string "That's impressive, for a newbie.\n"
	.string "Talent needs rewarding. Take this!$"

CelantoTown_Condominiums_2F_EventScript_SuperNerd::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CELANTO_DUSK_STONE, CelantoTown_Condominiums_2F_EventScript_ExplainDuskStone
	msgbox CelantoTown_Condominiums_2F_Text_AlwaysWantedToSeeShuppet, MSGBOX_DEFAULT
	setvar VAR_0x8004, SPECIES_SHUPPET
	specialvar VAR_RESULT, CheckPartyForMon
	compare VAR_RESULT, TRUE
	goto_if_eq CelantoTown_Condominiums_2F_EventScript_GiveDuskStone
	release
	end

CelantoTown_Condominiums_2F_EventScript_GiveDuskStone:
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox CelantoTown_Condominiums_2F_Text_WowYourShuppet, MSGBOX_DEFAULT
	giveitem ITEM_DUSK_STONE
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CELANTO_DUSK_STONE
	goto CelantoTown_Condominiums_2F_EventScript_ExplainDuskStone
	end

CelantoTown_Condominiums_2F_EventScript_ExplainDuskStone:
	msgbox CelantoTown_Condominiums_2F_Text_ThatDuskStone, MSGBOX_DEFAULT
	release
	end

CelantoTown_Condominiums_2F_Text_AlwaysWantedToSeeShuppet:
	.string "I've always wanted to see a\n"
	.string "Shuppet. I'd even pay to see one!$"

CelantoTown_Condominiums_2F_Text_WowYourShuppet:
	.string "Wow!\n"
	.string "You have a Shuppet!\p"
	.string "May I see it?\p"
	.string "…\p"
	.string "Wow, incredible!\n"
	.string "You must be proud.\p"
	.string "Thank you for sharing with me!\n"
	.string "Accept this gift!$"

CelantoTown_Condominiums_2F_Text_ThatDuskStone:
	.string "That Dusk Stone can make certain\n"
	.string "Pokémon evolve!$"
