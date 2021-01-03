#ifndef GUARD_BUG_CATCHING_CONTEST_H
#define GUARD_BUG_CATCHING_CONTEST_H

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
