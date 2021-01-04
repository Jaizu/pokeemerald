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
    BUG_CATCHING_CONTEST_TRAINERS_COUNT
};

static const struct BugCatchingContestTrainer contestants[] =
{
    [BUG_CATCHING_CONTEST_TRAINER_BEASLY] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .sprite = OBJ_EVENT_GFX_BUG_CATCHER,
        .name = _("Beasly"),
        .pokemon = {
            {SPECIES_NINCADA, 270},
            {SPECIES_NINCADA, 265},
            {SPECIES_NINCADA, 234},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_CALUM] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .sprite = OBJ_EVENT_GFX_YOUNGSTER,
        .name = _("Calum"),
        .pokemon = {
            {SPECIES_BEAUTIFLY, 286},
            {SPECIES_BEAUTIFLY, 251},
            {SPECIES_CATERPIE,  237},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_JESS] =
    {
        .trainerClass = TRAINER_CLASS_ACE_TRAINER,
        .sprite = OBJ_EVENT_GFX_ACE_TRAINER_F,
        .name = _("Jess"),
        .pokemon = {
            {SPECIES_COMBEE,   301},
            {SPECIES_SURSKIT,  341},
            {SPECIES_CATERPIE, 264},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_DOMINIK] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .sprite = OBJ_EVENT_GFX_CAMPER,
        .name = _("Dominik"),
        .pokemon = {
            {SPECIES_CASCOON,  301},
            {SPECIES_COMBEE,   341},
            {SPECIES_CATERPIE, 264},
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
            {SPECIES_CATERPIE, 264},
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
            {SPECIES_NINCADA,  277},
            {SPECIES_CATERPIE, 226},
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
            {SPECIES_LARVESTA,  379},
            {SPECIES_HERACROSS, 344},
            {SPECIES_CATERPIE,  226},
        }
    },
    [BUG_CATCHING_CONTEST_TRAINER_VERNON] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .sprite = OBJ_EVENT_GFX_VERNON,
        .name = _("Vernon"),
        .pokemon = {
            {SPECIES_BEEDRILL, 393},
            {SPECIES_BEEDRILL, 391},
            {SPECIES_BEEDRILL, 387},
        }
    }
};
