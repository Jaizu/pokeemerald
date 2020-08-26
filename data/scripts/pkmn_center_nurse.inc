Common_EventScript_PkmnCenterNurse::
    lock
    faceplayer
    msgbox gText_WouldYouLikeToRestYourPkmn, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq EventScript_PkmnCenterNurse_HealPkmn
    compare VAR_RESULT, NO
    msgbox gText_WeHopeToSeeYouAgain, MSGBOX_DEFAULT
	release
    end

EventScript_PkmnCenterNurse_HealPkmn::
    incrementgamestat GAME_STAT_USED_POKECENTER
    message gText_IllTakeYourPkmn
	delay 5
    call EventScript_PkmnCenterNurse_TakeAndHealPkmn
    goto_if_unset FLAG_POKERUS_EXPLAINED, EventScript_PkmnCenterNurse_CheckPokerus
    goto EventScript_PkmnCenterNurse_ReturnPkmn
    end

EventScript_PkmnCenterNurse_CheckPokerus::
    specialvar VAR_RESULT, IsPokerusInParty
    compare VAR_RESULT, TRUE
    goto_if_eq EventScript_PkmnCenterNurse_ExplainPokerus
    compare VAR_RESULT, FALSE
    goto_if_eq EventScript_PkmnCenterNurse_ReturnPkmn
    end

EventScript_PkmnCenterNurse_ExplainPokerus::
    message gText_PokerusExplanation
    setflag FLAG_POKERUS_EXPLAINED
    return

EventScript_PkmnCenterNurse_TakeAndHealPkmn::
    applymovement VAR_0x800B, Common_Movement_WalkInPlaceFastestLeft
    waitmovement 0
    dofieldeffect FLDEFF_POKECENTER_HEAL
    waitfieldeffect FLDEFF_POKECENTER_HEAL
    applymovement VAR_0x800B, Common_Movement_WalkInPlaceFastestDown
    waitmovement 0
    special HealPlayerParty
    return

EventScript_PkmnCenterNurse_ReturnPkmn::
    message gText_RestoredPkmnToFullHealth
    applymovement VAR_0x800B, EventScript_PkmnCenterNurse_Bow
    waitmovement 0
    waitmessage
    return

EventScript_PkmnCenterNurse_Bow:
    nurse_joy_bow
    delay_4
    step_end

Common_EventScript_PokeMartClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, EventScript_PokeBallsStock
	pokemart Pokemart_NoPokeBallsStock
	goto EventScript_MartClerkPleaseComeAgain
	end

EventScript_PokeBallsStock:
	goto_if_set FLAG_BADGE01_GET, EventScript_Badge01Stock
	pokemart Pokemart_NoBadgesStock
	goto EventScript_MartClerkPleaseComeAgain
	end

EventScript_Badge01Stock:
	goto_if_set FLAG_BADGE02_GET, EventScript_Badge02Stock
	pokemart Pokemart_Badge01Stock
	goto EventScript_MartClerkPleaseComeAgain
	end

EventScript_Badge02Stock:
	goto_if_set FLAG_BADGE03_GET, EventScript_Badge03Stock
	pokemart Pokemart_Badge02Stock
	goto EventScript_MartClerkPleaseComeAgain
	end

EventScript_Badge03Stock:
	goto_if_set FLAG_BADGE04_GET, EventScript_Badge04Stock
	pokemart Pokemart_Badge03Stock
	goto EventScript_MartClerkPleaseComeAgain
	end

EventScript_Badge04Stock:
	goto_if_set FLAG_BADGE05_GET, EventScript_FullStock
	pokemart Pokemart_Badge04Stock
	goto EventScript_MartClerkPleaseComeAgain
	end

EventScript_FullStock:
	pokemart Pokemart_FullStock
	goto EventScript_MartClerkPleaseComeAgain
	end

EventScript_MartClerkPleaseComeAgain:
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Pokemart_NoPokeBallsStock:
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

Pokemart_NoBadgesStock:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

Pokemart_Badge01Stock:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

Pokemart_Badge02Stock:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_NONE
	release
	end

Pokemart_Badge03Stock:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

Pokemart_Badge04Stock:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

Pokemart_FullStock:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end
