.equ LOCALID_PAINTER, 3
.equ LOCALID_BEAUTY, 4
.equ LOCALID_FAT_MAN, 5

AerousRoad_MapScripts::
	.byte 0

AerousRoad_EventScript_PainterRoadblock_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto AerousRoad_EventScript_PainterRoadblock
	end

AerousRoad_EventScript_PainterRoadblock_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto AerousRoad_EventScript_PainterRoadblock
	end

AerousRoad_EventScript_PainterRoadblock:
	applymovement LOCALID_PAINTER, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_PAINTER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PAINTER, Common_Movement_Delay48
	waitmovement 0
	msgbox AerousRoad_Text_DontTakeAnotherStep, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PAINTER, Common_Movement_FaceOriginalDirection
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
	end

AerousRoad_EventScript_Painter::
	lock
	faceplayer
	msgbox AerousRoad_Text_DontTakeAnotherStep, MSGBOX_DEFAULT
	applymovement LOCALID_PAINTER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousRoad_Text_DontTakeAnotherStep:
	.string "{COLOR RED}Don't take another step!\p"
	.string "You'll disturb the scene, and ruin\n"
	.string "my painting!$"

AerousRoad_EventScript_Harry::
	trainerbattle_single TRAINER_HARRY_1, AerousRoad_Text_HarryIntro, AerousRoad_Text_HarryDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_HarryRematch
	msgbox AerousRoad_Text_HarryPostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_HarryRematch::
	trainerbattle_rematch TRAINER_HARRY_1, AerousRoad_Text_HarryIntro, AerousRoad_Text_HarryDefeat
	msgbox AerousRoad_Text_HarryPostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_HarryIntro:
	.string "I love the fresh air out here!\n"
	.string "It makes me want to battle!$"

AerousRoad_Text_HarryDefeat:
	.string "Looks like I'm fresh out of luck.$"

AerousRoad_Text_HarryPostBattle:
	.string "It's important to get outside and\n"
	.string "breathe some fresh air!$"

AerousRoad_EventScript_Phoebe::
	trainerbattle_single TRAINER_PHOEBE_1, AerousRoad_Text_PhoebeIntro, AerousRoad_Text_PhoebeDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_PhoebeRematch
	msgbox AerousRoad_Text_PhoebePostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_PhoebeRematch::
	trainerbattle_rematch TRAINER_PHOEBE_1, AerousRoad_Text_PhoebeRematchIntro, AerousRoad_Text_PhoebeDefeat
	msgbox AerousRoad_Text_PhoebePostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_PhoebeIntro:
	.string "Ah!\n"
	.string "Did you spot it, too?$"

AerousRoad_Text_PhoebeDefeat:
	.string "Hmm…$"

AerousRoad_Text_PhoebePostBattle:
	.string "Do you see it yet?\n"
	.string "It's hidden!$"

AerousRoad_Text_PhoebeRematchIntro:
	.string "Ah!\n"
	.string "The mysterious Trainer returns…$"

AerousRoad_EventScript_Beauty::
	lock
	faceplayer
	msgbox AerousRoad_Text_ThisViewIsBeautiful, MSGBOX_DEFAULT
	applymovement LOCALID_BEAUTY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousRoad_Text_ThisViewIsBeautiful:
	.string "This view is beautiful!\p"
	.string "It's a shame about him…$"

AerousRoad_EventScript_FatMan::
	lock
	faceplayer
	msgbox AerousRoad_Text_IsntItBeautiful, MSGBOX_DEFAULT
	applymovement LOCALID_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

AerousRoad_Text_IsntItBeautiful:
	.string "Ah…\n"
	.string "Isn't it beautiful?\p"
	.string "The view looks nice, too!$"

AerousRoad_EventScript_Michael::
	trainerbattle_single TRAINER_MICHAEL_1, AerousRoad_Text_MichaelIntro, AerousRoad_Text_MichaelDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_MichaelRematch
	msgbox AerousRoad_Text_MichaelPostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_MichaelRematch::
	trainerbattle_rematch TRAINER_MICHAEL_1, AerousRoad_Text_MichaelRematchIntro, AerousRoad_Text_MichaelDefeat
	msgbox AerousRoad_Text_MichaelPostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_MichaelIntro:
	.string "“Bug-types are weak.”\n"
	.string "“Bug-types suck!”\p"
    .string "I'll show them!\n"
    .string "I'll show you, too!$"

AerousRoad_Text_MichaelDefeat:
	.string "This just proves I'm bad!\n"
    .string "Bug-types aren't weak!$"

AerousRoad_Text_MichaelPostBattle:
	.string "I won't have a bad word said about\n"
    .string "Bug-types! They're the best, okay?$"

AerousRoad_Text_MichaelRematchIntro:
	.string "Still think Bug-types are weak?\n"
    .string "I'll show you, punk!$"

AerousRoad_EventScript_Lisa::
	trainerbattle_double TRAINER_LISA_AND_LOIS_1, AerousRoad_Text_LisaIntro, AerousRoad_Text_LisaDefeat, AerousRoad_Text_LisaNotEnoughPokemon
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_LisaRematch
	msgbox AerousRoad_Text_LisaPostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_LisaRematch::
	trainerbattle_rematch_double TRAINER_LISA_AND_LOIS_1, AerousRoad_Text_LisaRematchIntro, AerousRoad_Text_LisaDefeat, AerousRoad_Text_LisaNotEnoughPokemon
	msgbox AerousRoad_Text_LisaPostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_LisaIntro:
	.string "My sister's a little… dramatic.\n"
    .string "We should battle, I guess.$"

AerousRoad_Text_LisaDefeat:
	.string "Oh well…$"

AerousRoad_Text_LisaPostBattle:
    .string "Maybe we'll get better one day…$"

AerousRoad_Text_LisaNotEnoughPokemon:
	.string "My sister insists on us battling\n"
    .string "together…$"

AerousRoad_Text_LisaRematchIntro:
	.string "My sister wants to battle again.$"

AerousRoad_EventScript_Lois::
	trainerbattle_double TRAINER_LISA_AND_LOIS_1, AerousRoad_Text_LoisIntro, AerousRoad_Text_LoisDefeat, AerousRoad_Text_LoisNotEnoughPokemon
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_LoisRematch
	msgbox AerousRoad_Text_LoisPostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_LoisRematch::
	trainerbattle_rematch_double TRAINER_LISA_AND_LOIS_1, AerousRoad_Text_LoisIntro, AerousRoad_Text_LoisDefeat, AerousRoad_Text_LoisNotEnoughPokemon
	msgbox AerousRoad_Text_LoisPostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_LoisIntro:
	.string "Behold, as my sister and I\n"
    .string "destroy this unassuming Trainer!$"

AerousRoad_Text_LoisDefeat:
	.string "Hehehe, oops!$"

AerousRoad_Text_LoisPostBattle:
    .string "No!\n"
    .string "I can't believe we lost!$"

AerousRoad_Text_LoisNotEnoughPokemon:
	.string "We don't battle alone, kid!\n"
    .string "Get a second Pokémon! Hmph!$"

AerousRoad_EventScript_Spencer::
	trainerbattle_single TRAINER_SPENCER_1, AerousRoad_Text_SpencerIntro, AerousRoad_Text_SpencerDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_SpencerRematch
	msgbox AerousRoad_Text_SpencerPostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_SpencerRematch::
	trainerbattle_rematch TRAINER_SPENCER_1, AerousRoad_Text_SpencerRematchIntro, AerousRoad_Text_SpencerDefeat
	msgbox AerousRoad_Text_SpencerPostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_SpencerIntro:
	.string "Hehehe!\n"
    .string "I emerge from the shadows!$"

AerousRoad_Text_SpencerDefeat:
	.string "I might have battled poorly, but\n"
    .string "the theatrics were great, right?$"

AerousRoad_Text_SpencerPostBattle:
	.string "Hey, maybe my vocation is\n"
    .string "entertainment, not battling…$"

AerousRoad_Text_SpencerRematchIntro:
	.string "Back for more shadowy theater?\n"
    .string "Then let the show begin!$"

AerousRoad_EventScript_Jon::
	trainerbattle_single TRAINER_JON_1, AerousRoad_Text_JonIntro, AerousRoad_Text_JonDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_JonRematch
	msgbox AerousRoad_Text_JonPostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_JonRematch::
	trainerbattle_rematch TRAINER_JON_1, AerousRoad_Text_JonIntro, AerousRoad_Text_JonDefeat
	msgbox AerousRoad_Text_JonPostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_JonIntro:
	.string "This bridge is pretty rickety, but\n"
    .string "I ain't scared!$"

AerousRoad_Text_JonDefeat:
	.string "I wanna jump in the pond to hide\n"
    .string "my embarrassment!$"

AerousRoad_Text_JonPostBattle:
	.string "I wonder if the bridge is weakened\n"
    .string "from Pokémon swimming by?$"

AerousRoad_EventScript_Arthur::
	trainerbattle_single TRAINER_ARTHUR_1, AerousRoad_Text_ArthurIntro, AerousRoad_Text_ArthurDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AerousRoad_EventScript_ArthurRematch
	msgbox AerousRoad_Text_ArthurPostBattle, MSGBOX_DEFAULT
	release
	end

AerousRoad_EventScript_ArthurRematch::
	trainerbattle_rematch TRAINER_ARTHUR_1, AerousRoad_Text_ArthurRematchIntro, AerousRoad_Text_ArthurDefeat
	msgbox AerousRoad_Text_ArthurPostBattle, MSGBOX_AUTOCLOSE
	end

AerousRoad_Text_ArthurIntro:
	.string "Good day, child! Would you indulge\n"
    .string "me in a Pokémon battle, perchance?$"

AerousRoad_Text_ArthurDefeat:
	.string "Drats!$"

AerousRoad_Text_ArthurPostBattle:
	.string "The move Chatter is only learned\n"
    .string "by Chatot.\p"
    .string "It makes those it hits\n"
    .string "confused!$"

AerousRoad_Text_ArthurRematchIntro:
	.string "Well met, child! Shall we engage\n"
    .string "in combat once again? Indeed!$"

AerousRoad_EventScript_Lass::
	msgbox AerousRoad_Text_HaveYouFoundAnyGoldPokeBalls, MSGBOX_NPC
	end

AerousRoad_Text_HaveYouFoundAnyGoldPokeBalls:
	.string "Have you found any gold\n"
    .string "Poké Balls?\p"
    .string "They contain Technical Machines!$"

AerousRoad_EventScript_OldMan::
	msgbox AerousRoad_Text_HaveYouHeardAboutVincent, MSGBOX_NPC
	end

AerousRoad_Text_HaveYouHeardAboutVincent:
	.string "Have you heard about Art Master\n"
    .string "Vincent, and his apprentices?\p"
    .string "They all train Smeargle which they\n"
    .string "raise to use different moves.$"

AerousRoad_EventScript_Youngster::
	msgbox AerousRoad_Text_TheYellowShardTutor, MSGBOX_NPC
	end

AerousRoad_Text_TheYellowShardTutor:
	.string "The Yellow Shard Tutor must be a\n"
    .string "Hiker. Or a weirdo…\p"
    .string "Why else would he Rock Climb to\n"
    .string "and from his home?$"

AerousRoad_EventScript_RouteSign::
	msgbox AerousRoad_Text_RouteSign, MSGBOX_SIGN
	end

AerousRoad_Text_RouteSign:
	.string "Aerous Road\n"
	.string "{LEFT_ARROW} Seros Village {RIGHT_ARROW} Aerous City$"

AerousRoad_EventScript_YellowShardTutorSign::
	msgbox AerousRoad_Text_YellowShardTutorSign, MSGBOX_SIGN
	end

AerousRoad_Text_YellowShardTutorSign:
	.string "Yellow Shard Meister's house\p"
	.string "“I will teach Pokémon moves for\n"
	.string "Yellow Shards!”$"
