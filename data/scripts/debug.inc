.ifdef DEBUG
    Debug_EventScript_SetUpFastForward::
		setflag FLAG_SYS_B_DASH
		setflag FLAG_SYS_POKEMON_GET
		setflag FLAG_BADGE01_GET
		setflag FLAG_BADGE02_GET
		givemon SPECIES_JOLTIK, 25, ITEM_NONE
		givemon SPECIES_CLEFAIRY, 25, ITEM_NONE
		givemon SPECIES_MARACTUS, 25, ITEM_NONE
		givemon SPECIES_MONFERNO, 25, ITEM_NONE
		additem ITEM_TOWN_MAP
		additem ITEM_POKE_BALL, 25
		additem ITEM_SUPER_POTION, 25
		additem ITEM_ESCAPE_ROPE, 3
		additem ITEM_HM01
		additem ITEM_HM06
        end
.endif
