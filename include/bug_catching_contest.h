#ifndef GUARD_BUG_CATCHING_CONTEST_H
#define GUARD_BUG_CATCHING_CONTEST_H

#define BUG_CATCHING_CONTEST_TRAINER_NAME_LENGTH 8

// CONTESTANTS_COUNT is the number of contestants in a given, ongoing Contest
// Not to be confused with the total number of possible contestants, NUM_BUG_CATCHING_CONTEST_TRAINERS
#define CONTESTANTS_COUNT 4

struct BugCatchingContestTrainer {
    u16 trainerClass;
    u16 sprite;
    const u8 name[BUG_CATCHING_CONTEST_TRAINER_NAME_LENGTH + 1];
    struct {
        u16 species;
        u16 score;
    } pokemon[3];
};

extern u8 gNumParkBalls;

bool32 GetBugCatchingContestFlag(void);
void SetBugCatchingContestFlag(void);
void ResetBugCatchingContestFlag(void);
bool8 InValoonReserve(void);
void EnterBugCatchingContestMode(void);
void ExitBugCatchingContestMode(void);
bool8 PlayerHasCaughtBug(void);
void BugCatchingContestRetirePrompt(void);
void CB2_EndBugCatchingContestBattle(void);
void SetCaughtBug(struct Pokemon *mon);
void ViewCaughtBug(void);

#endif // GUARD_BUG_CATCHING_CONTEST_H
