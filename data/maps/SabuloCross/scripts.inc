.set TRAINER_FELIX_1, 0
.set TRAINER_ESTEBAN_1, 0
.set TRAINER_KRISTOFF_1, 0
.set TRAINER_STEPHAN_1, 0
.set TRAINER_CELESTE_1, 0

SabuloCross_MapScripts::
	.byte 0

SabuloCross_EventScript_RouteSign::
	msgbox SabuloCross_Text_RouteSign, MSGBOX_SIGN
	end

SabuloCross_Text_RouteSign::
	.string "Sabulo Cross\n"
	.string "{LEFT_ARROW} Aerous City {UP_ARROW} Reliquia Ruins\l"
	.string "{RIGHT_ARROW} Sabulo Island$"

SabuloCross_EventScript_PokeManiac::
	msgbox SabuloCross_Text_ImTryingToCatchSwablu, MSGBOX_NPC
	end

SabuloCross_Text_ImTryingToCatchSwablu:
	.string "I'm trying to catch as many\n"
	.string "Swablu as I can find.\p"
	.string "Right now I've got seventeen!$"

SabuloCross_EventScript_Joanna::
	trainerbattle_single TRAINER_JOANNA_1, SabuloCross_Text_JoannaIntro, SabuloCross_Text_JoannaDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SabuloCross_EventScript_JoannaRematch
	msgbox SabuloCross_Text_JoannaPostBattle, MSGBOX_DEFAULT
	release
	end

SabuloCross_EventScript_JoannaRematch::
	trainerbattle_rematch TRAINER_JOANNA_1, SabuloCross_Text_JoannaRematchIntro, SabuloCross_Text_JoannaDefeat
	msgbox SabuloCross_Text_JoannaPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloCross_Text_JoannaIntro:
	.string "Welcome to Sabulo Island!\n"
	.string "Prepare to get destroyed!$"

SabuloCross_Text_JoannaDefeat:
	.string "Aw, I got destroyed…$"

SabuloCross_Text_JoannaPostBattle:
	.string "A lot of the wild Pokémon you'll\n"
	.string "find here love living by the water!$"

SabuloCross_Text_JoannaRematchIntro:
	.string "Back for more?\n"
	.string "This time I will destroy you!$"

SabuloCross_EventScript_Felix::
	trainerbattle_single TRAINER_FELIX_1, SabuloCross_Text_FelixIntro, SabuloCross_Text_FelixDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SabuloCross_EventScript_FelixRematch
	msgbox SabuloCross_Text_FelixPostBattle, MSGBOX_DEFAULT
	release
	end

SabuloCross_EventScript_FelixRematch::
	trainerbattle_rematch TRAINER_FELIX_1, SabuloCross_Text_FelixRematchIntro, SabuloCross_Text_FelixDefeat
	msgbox SabuloCross_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloCross_Text_FelixIntro:
	.string "Are you trying to nab my perfect\n"
	.string "fishing spot?$"

SabuloCross_Text_FelixDefeat:
	.string "No! My fishies!$"

SabuloCross_Text_FelixPostBattle:
	.string "This here is the perfect fishing\n"
	.string "spot!\p"
	.string "It's midway between Aerous\n"
	.string "and Sabulo, see!$"

SabuloCross_Text_FelixRematchIntro:
	.string "You're not back to try and nab my\n"
	.string "fishing spot, are you?$"

SabuloCross_EventScript_Esteban::
	trainerbattle_single TRAINER_ESTEBAN_1, SabuloCross_Text_EstebanIntro, SabuloCross_Text_EstebanDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SabuloCross_EventScript_EstebanRematch
	msgbox SabuloCross_Text_EstebanPostBattle, MSGBOX_DEFAULT
	release
	end

SabuloCross_EventScript_EstebanRematch::
	trainerbattle_rematch TRAINER_ESTEBAN_1, SabuloCross_Text_EstebanRematchIntro, SabuloCross_Text_EstebanDefeat
	msgbox SabuloCross_Text_EstebanPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloCross_Text_EstebanIntro:
	.string "Kid, you distracted me!\n"
	.string "I lost a big one that was biting!$"

SabuloCross_Text_EstebanDefeat:
	.string "I shouldn't have bit the bait…$"

SabuloCross_Text_EstebanPostBattle:
	.string "When fishing, timing is everything.$"

SabuloCross_Text_EstebanRematchIntro:
	.string "Argh!\n"
	.string "I lost another one!\p"
	.string "I'm gonna take my frustration out\n"
	.string "on you!$"

SabuloCross_EventScript_Kristoff::
	trainerbattle_single TRAINER_KRISTOFF_1, SabuloCross_Text_KristoffIntro, SabuloCross_Text_KristoffDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SabuloCross_EventScript_KristoffRematch
	msgbox SabuloCross_Text_KristoffPostBattle, MSGBOX_DEFAULT
	release
	end

SabuloCross_EventScript_KristoffRematch::
	trainerbattle_rematch TRAINER_KRISTOFF_1, SabuloCross_Text_KristoffIntro, SabuloCross_Text_KristoffDefeat
	msgbox SabuloCross_Text_KristoffPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloCross_Text_KristoffIntro:
	.string "Eek! Don't look at me while I'm\n"
	.string "swimming!$"

SabuloCross_Text_KristoffDefeat:
	.string "Eek!\n"
	.string "I lost!$"

SabuloCross_Text_KristoffPostBattle:
	.string "What?\n"
	.string "I'm not insecure of my body!$"

SabuloCross_EventScript_Stephan::
	trainerbattle_single TRAINER_STEPHAN_1, SabuloCross_Text_StephanIntro, SabuloCross_Text_StephanDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SabuloCross_EventScript_StephanRematch
	msgbox SabuloCross_Text_StephanPostBattle, MSGBOX_DEFAULT
	release
	end

SabuloCross_EventScript_StephanRematch::
	trainerbattle_rematch TRAINER_STEPHAN_1, SabuloCross_Text_StephanIntro, SabuloCross_Text_StephanDefeat
	msgbox SabuloCross_Text_StephanPostBattle, MSGBOX_AUTOCLOSE
	end

SabuloCross_Text_StephanIntro:
	.string "I can swim, battle, and never lose\n"
	.string "my breath!$"

SabuloCross_Text_StephanDefeat:
	.string "Whoa…\n"
	.string "I'm out of breath…$"

SabuloCross_Text_StephanPostBattle:
	.string "Sometimes I like to submerge my\n"
	.string "body in the warm ocean currents…\p"
	.string "Then I remember I need to breathe\n"
	.string "and I scurry to the surface.$"

SabuloCross_EventScript_Celeste::
	trainerbattle_single TRAINER_CELESTE_1, SabuloCross_Text_CelesteIntro, SabuloCross_Text_CelesteDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq SabuloCross_EventScript_CelesteRematch
	msgbox SabuloCross_Text_CelestePostBattle, MSGBOX_DEFAULT
	release
	end

SabuloCross_EventScript_CelesteRematch::
	trainerbattle_rematch TRAINER_CELESTE_1, SabuloCross_Text_CelesteIntro, SabuloCross_Text_CelesteDefeat
	msgbox SabuloCross_Text_CelestePostBattle, MSGBOX_AUTOCLOSE
	end

SabuloCross_Text_CelesteIntro:
	.string "The ocean is unforgiving!\p"
	.string "My Pokémon and I are also\n"
	.string "relentless!$"

SabuloCross_Text_CelesteDefeat:
	.string "You didn't hold back!$"

SabuloCross_Text_CelestePostBattle:
	.string "I believe that Water-type Pokémon\n"
	.string "are the strongest.\p"
	.string "That's why there's so many of them!$"

SabuloCross_EventScript_Rocker::
	msgbox SabuloCross_Text_ThatCaveOverThereIsASecretTemple, MSGBOX_NPC
	end

SabuloCross_Text_ThatCaveOverThereIsASecretTemple:
	.string "That cave over there is a\n"
	.string "Secret Temple.\p"
	.string "I got chased out by a Marowak\n"
	.string "before I could check it out though.$"
