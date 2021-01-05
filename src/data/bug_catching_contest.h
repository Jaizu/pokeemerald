enum
{
    BUG_CATCHING_CONTEST_TRAINER_BEASLY,
    BUG_CATCHING_CONTEST_TRAINER_CALUM,
    BUG_CATCHING_CONTEST_TRAINER_JESS,
    BUG_CATCHING_CONTEST_TRAINER_DOMINIK,
    BUG_CATCHING_CONTEST_TRAINER_SANDRA,
    BUG_CATCHING_CONTEST_TRAINER_HILA,
    BUG_CATCHING_CONTEST_TRAINER_MARIANNE,
    BUG_CATCHING_CONTEST_TRAINER_MICKEY,
    BUG_CATCHING_CONTEST_TRAINER_SIMON,
    BUG_CATCHING_CONTEST_TRAINER_SESSEL,
    BUG_CATCHING_CONTEST_TRAINER_VERNON,
    BUG_CATCHING_CONTEST_PLAYER
};

#define NUM_BUG_CATCHING_CONTEST_TRAINERS BUG_CATCHING_CONTEST_TRAINER_VERNON

static const struct BugCatchingContestTrainer sBugCatchingContestTrainers[] =
{
    [BUG_CATCHING_CONTEST_TRAINER_BEASLY] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .sprite = OBJ_EVENT_GFX_BUG_CATCHER,
        .name = _("Beasly"),
        .pokemon = {
            {SPECIES_NINCADA, 263},
            {SPECIES_NINCADA, 245},
            {SPECIES_NINCADA, 214},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_CALUM] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .sprite = OBJ_EVENT_GFX_YOUNGSTER,
        .name = _("Calum"),
        .pokemon = {
            {SPECIES_BEAUTIFLY, 246},
            {SPECIES_BEAUTIFLY, 222},
            {SPECIES_CATERPIE,  189},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_JESS] =
    {
        .trainerClass = TRAINER_CLASS_ACE_TRAINER,
        .sprite = OBJ_EVENT_GFX_ACE_TRAINER_F,
        .name = _("Jess"),
        .pokemon = {
            {SPECIES_COMBEE,   287},
            {SPECIES_SURSKIT,  254},
            {SPECIES_CATERPIE, 183},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_DOMINIK] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .sprite = OBJ_EVENT_GFX_CAMPER,
        .name = _("Dominik"),
        .pokemon = {
            {SPECIES_CASCOON,  301},
            {SPECIES_CATERPIE, 264},
            {SPECIES_COMBEE,   241},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_SANDRA] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        .sprite = OBJ_EVENT_GFX_LASS,
        .name = _("Sandra"),
        .pokemon = {
            {SPECIES_SURSKIT,  261},
            {SPECIES_NINCADA,  253},
            {SPECIES_CATERPIE, 243},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_HILA] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .sprite = OBJ_EVENT_GFX_BEAUTY,
        .name = _("Hila"),
        .pokemon = {
            {SPECIES_SCYTHER,  321},
            {SPECIES_BEEDRILL, 316},
            {SPECIES_CATERPIE, 277},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_MARIANNE] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .sprite = OBJ_EVENT_GFX_PKMN_RANGER_F,
        .name = _("Marianne"),
        .pokemon = {
            {SPECIES_BEAUTIFLY, 312},
            {SPECIES_BEAUTIFLY, 304},
            {SPECIES_SURSKIT,   214},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_MICKEY] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .sprite = OBJ_EVENT_GFX_PKMN_RANGER_M,
        .name = _("Mickey"),
        .pokemon = {
            {SPECIES_NINCADA,  279},
            {SPECIES_CATERPIE, 223},
            {SPECIES_COMBEE,   214},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_SIMON] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .sprite = OBJ_EVENT_GFX_BUG_CATCHER,
        .name = _("Simon"),
        .pokemon = {
            {SPECIES_PINSIR,  320},
            {SPECIES_KAKUNA,  294},
            {SPECIES_CASCOON, 226},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_SESSEL] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        .sprite = OBJ_EVENT_GFX_SCHOOL_KID_M,
        .name = _("Sessel"),
        .pokemon = {
            {SPECIES_LARVESTA,  358},
            {SPECIES_HERACROSS, 344},
            {SPECIES_CATERPIE,  226},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_VERNON] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        .sprite = OBJ_EVENT_GFX_VERNON,
        .name = _("Vernon"),
        .pokemon = {
            {SPECIES_BEEDRILL, 380},
            {SPECIES_BEEDRILL, 377},
            {SPECIES_BEEDRILL, 366},
        }
    }
};

static const u16 sCommonSpecies[] =
{
    SPECIES_CATERPIE, SPECIES_CASCOON, SPECIES_COMBEE, SPECIES_NINCADA, SPECIES_SURSKIT
};

#define NUM_COMMON_SPECIES (sizeof(sCommonSpecies) / sizeof(u16))

static const u16 sRareSpecies[] =
{
    SPECIES_PINSIR, SPECIES_SCYTHER, SPECIES_HERACROSS, SPECIES_LARVESTA
};

#define NUM_RARE_SPECIES (sizeof(sRareSpecies) / sizeof(u16))

static const struct MegaStonePrize sMegaStonePrizes[] =
{
    {SPECIES_PINSIR,    ITEM_PINSIRITE,   FLAG_OBTAINED_PINSIRITE},
    {SPECIES_SCYTHER,   ITEM_SCIZORITE,   FLAG_OBTAINED_SCIZORITE},
    {SPECIES_SCIZOR,    ITEM_SCIZORITE,   FLAG_OBTAINED_SCIZORITE},
    {SPECIES_HERACROSS, ITEM_HERACRONITE, FLAG_OBTAINED_HERACRONITE},
    {SPECIES_BEEDRILL,  ITEM_BEEDRILLITE, FLAG_OBTAINED_BEEDRILLITE},
};

#define NUM_MEGA_STONE_PRIZES (sizeof(sMegaStonePrizes) / sizeof(struct MegaStonePrize))

static const u16 sBugCatchingContestPrizes[] =
{
    ITEM_SUN_STONE, ITEM_MOON_STONE, ITEM_FIRE_STONE, ITEM_THUNDER_STONE,
    ITEM_WATER_STONE, ITEM_LEAF_STONE, ITEM_DAWN_STONE, ITEM_DUSK_STONE,
    ITEM_SHINY_STONE, ITEM_ICE_STONE, /*ITEM_REGAL_STONE,*/ ITEM_EVIOLITE
};

#define NUM_BUG_CATCHING_CONTEST_PRIZES (sizeof(sBugCatchingContestPrizes) / sizeof(u16))
