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
