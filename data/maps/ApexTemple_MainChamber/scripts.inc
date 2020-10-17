.set LOCALID_GRUNT_1, 1
.set LOCALID_GRUNT_2, 2
.set LOCALID_GRUNT_3, 3
.set LOCALID_GRUNT_4, 4
.set LOCALID_BOOK, 5
.set LOCALID_ENOCH, 6
.set LOCALID_COULTER, 7

ApexTemple_MainChamber_MapScripts::
	.byte 0

ApexTemple_MainChamber_EventScript_EnochMeeting_Trigger0::
	lockall
	setvar VAR_0x8008, 0
	goto ApexTemple_MainChamber_EventScript_EnochMeetingScene
	end

ApexTemple_MainChamber_EventScript_EnochMeeting_Trigger1::
	lockall
	setvar VAR_0x8008, 1
	goto ApexTemple_MainChamber_EventScript_EnochMeetingScene
	end

ApexTemple_MainChamber_EventScript_EnochMeetingScene::
	applymovement LOCALID_ENOCH, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 32
	playse SE_PIN
	applymovement LOCALID_ENOCH, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ENOCH, Common_Movement_Delay48
	waitmovement 0
	compare VAR_0x8008, 0
	call_if_eq ApexTemple_MainChamber_EventScript_EnochWalkToPlayer0
	compare VAR_0x8008, 1
	call_if_eq ApexTemple_MainChamber_EventScript_EnochWalkToPlayer1
	msgbox ApexTemple_MainChamber_Text_EnochSpeech, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ENOCH
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	fadescreen FADE_FROM_BLACK
	addobject LOCALID_COULTER
	compare VAR_0x8008, 0
	call_if_eq ApexTemple_MainChamber_EventScript_AlignCoulterWithPlayer0
	compare VAR_0x8008, 1
	call_if_eq ApexTemple_MainChamber_EventScript_AlignCoulterWithPlayer1
	playbgm MUS_RG_RIVAL1, 0
	applymovement OBJ_EVENT_ID_PLAYER, ApexTemple_MainChamber_Movement_PlayerFaceCoulter
	applymovement LOCALID_COULTER, ApexTemple_MainChamber_Movement_CoulterWalkToPlayer
	waitmovement 0
	msgbox ApexTemple_MainChamber_Text_WhoaThatWasInsane, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	compare VAR_0x8008, 0
	call_if_eq ApexTemple_MainChamber_EventScript_CoulterWalkToBook0
	compare VAR_0x8008, 1
	call_if_eq ApexTemple_MainChamber_EventScript_CoulterWalkToBook1
	msgbox ApexTemple_MainChamber_Text_ComeCheckThisOut, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq ApexTemple_MainChamber_EventScript_PlayerWalkToBook0
	compare VAR_0x8008, 1
	call_if_eq ApexTemple_MainChamber_EventScript_PlayerWalkToBook1
	msgbox ApexTemple_MainChamber_Text_ThisBookHasTheSameGlyphs, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 32
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox ApexTemple_MainChamber_Text_LookTheresSomeSortOfIsland, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 10
	removeobject LOCALID_BOOK
	delay 10
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 10
	msgbox ApexTemple_MainChamber_Text_AlrightsLetsGo, MSGBOX_DEFAULT
	closemessage
	delay 10
	setflag FLAG_HIDE_IGNIS_ROOST_COULTER
	setflag FLAG_HIDE_IGNIS_ROOST_GRUNTS
	setflag FLAG_HIDE_APEX_TEMPLE_COULTER
	clearflag FLAG_HIDE_WINDMIST_CITY_POKEMON_CENTER_COULTER
	setvar VAR_APEX_TEMPLE_STATE, 1
	setvar VAR_WINDMIST_CITY_POKEMON_CENTER_STATE, 1
	warp MAP_WINDMIST_CITY_POKEMON_CENTER, -1, 7, 5
	waitstate
	releaseall
	end

ApexTemple_MainChamber_EventScript_EnochWalkToPlayer0:
	applymovement LOCALID_ENOCH, ApexTemple_MainChamber_Movement_EnochWalkToPlayer0
	waitmovement 0
	return

ApexTemple_MainChamber_EventScript_EnochWalkToPlayer1:
	applymovement LOCALID_ENOCH, ApexTemple_MainChamber_Movement_EnochWalkToPlayer1
	waitmovement 0
	return

ApexTemple_MainChamber_EventScript_AlignCoulterWithPlayer0:
	setobjectxy LOCALID_COULTER, 7, 12
	return

ApexTemple_MainChamber_EventScript_AlignCoulterWithPlayer1:
	setobjectxy LOCALID_COULTER, 8, 12
	return

ApexTemple_MainChamber_EventScript_CoulterWalkToBook0:
	applymovement OBJ_EVENT_ID_PLAYER, ApexTemple_MainChamber_Movement_PlayerWatchCoulterWalkToBook0
	applymovement LOCALID_COULTER, ApexTemple_MainChamber_Movement_CoulterWalkToBook0
	waitmovement 0
	return

ApexTemple_MainChamber_EventScript_CoulterWalkToBook1:
	applymovement OBJ_EVENT_ID_PLAYER, ApexTemple_MainChamber_Movement_PlayerWatchCoulterWalkToBook1
	applymovement LOCALID_COULTER, ApexTemple_MainChamber_Movement_CoulterWalkToBook1
	waitmovement 0
	return

ApexTemple_MainChamber_EventScript_PlayerWalkToBook0:
	applymovement OBJ_EVENT_ID_PLAYER, ApexTemple_MainChamber_Movement_PlayerWalkToBook0
	waitmovement 0
	return

ApexTemple_MainChamber_EventScript_PlayerWalkToBook1:
	applymovement OBJ_EVENT_ID_PLAYER, ApexTemple_MainChamber_Movement_PlayerWalkToBook1
	waitmovement 0
	return

ApexTemple_MainChamber_Text_EnochSpeech:
	.string "Enoch: {COLOR BLUE}Child, I do not appreciate\n"
	.string "this disturbance.\p"
	.string "Nevertheless, our work here is\n"
	.string "done.\p"
	.string "I now know the whereabouts of the\n"
	.string "legendary {COLOR GREEN}Regirock{COLOR BLUE}!\p"
	.string "The Elders of Orbtus left us all\n"
	.string "the information we needed.\p"
	.string "I wish only that the modern world\n"
	.string "knew of the Elders' greatness…\p"
	.string "We have strayed too from our\n"
	.string "roots, and a correction is due.\p"
	.string "All will be revealed, in time!\n"
	.string "For now, I bid you farewell, child.$"

ApexTemple_MainChamber_Text_WhoaThatWasInsane:
	.string "{RIVAL}: {COLOR BLUE}Whoa…\n"
	.string "That was insane!\p"
	.string "Who were those guys?\p"
	.string "{COLOR DARK_GREY}…\p"
	.string "{COLOR BLUE}You saw others like them at\n"
	.string "the Aerous Museum?\p"
	.string "Huh… And they captured a Pokémon\n"
	.string "called Regice in that icy cave?\p"
	.string "That Enoch dude mentioned\n"
	.string "Regirock, too…\p"
	.string "I've never even heard of those\n"
	.string "Pokémon!\p"
	.string "…Hey, what's that book?$"

ApexTemple_MainChamber_Text_ComeCheckThisOut:
	.string "{RIVAL}: {COLOR BLUE}{PLAYER}!\n"
	.string "Come check this out!$"

ApexTemple_MainChamber_Text_ThisBookHasTheSameGlyphs:
	.string "{RIVAL}: {COLOR BLUE}This book has the same\n"
	.string "glyphs as the Tablets!$"

ApexTemple_MainChamber_Text_LookTheresSomeSortOfIsland:
	.string "{RIVAL}: {COLOR BLUE}And look, there's some\n"
	.string "sort of island!\p"
	.string "We should bring this to the Prof!\n"
	.string "It might have some useful info!\p"
	.string "There's a phone at the Pokémon\n"
	.string "Center in Windmist City.\p"
	.string "Let's grab the book and head there.$"

ApexTemple_MainChamber_Text_AlrightsLetsGo:
	.string "{RIVAL}: {COLOR BLUE}Alright, let's go!$"

ApexTemple_MainChamber_Movement_EnochWalkToPlayer0:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

ApexTemple_MainChamber_Movement_EnochWalkToPlayer1:
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

ApexTemple_MainChamber_Movement_CoulterWalkToPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

ApexTemple_MainChamber_Movement_PlayerFaceCoulter:
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_down
	step_end

ApexTemple_MainChamber_Movement_PlayerWatchCoulterWalkToBook0:
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

ApexTemple_MainChamber_Movement_PlayerWatchCoulterWalkToBook1:
	delay_16
	delay_16
	walk_in_place_fastest_left
	delay_16
	delay_16
	walk_in_place_fastest_up
	step_end

ApexTemple_MainChamber_Movement_CoulterWalkToBook0:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

ApexTemple_MainChamber_Movement_CoulterWalkToBook1:
	walk_left
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

ApexTemple_MainChamber_Movement_PlayerWalkToBook0:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

ApexTemple_MainChamber_Movement_PlayerWalkToBook1:
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

ApexTemple_MainChamber_EventScript_GruntM1::
	trainerbattle_single TRAINER_APEX_TEMPLE_GRUNT_1, ApexTemple_MainChamber_Text_GruntM1Intro, ApexTemple_MainChamber_Text_GruntM1Defeated
	msgbox ApexTemple_MainChamber_Text_GruntM1PostBattle, MSGBOX_AUTOCLOSE
	end

ApexTemple_MainChamber_Text_GruntM1Intro:
	.string "Enoch won't be happy to see some\n"
	.string "kid snooping around our business.\p"
	.string "I'll have to take care of you!$"

ApexTemple_MainChamber_Text_GruntM1Defeated:
	.string "Argh, you'll regret crossing me.$"

ApexTemple_MainChamber_Text_GruntM1PostBattle:
	.string "I think I bought us enough time.$"

ApexTemple_MainChamber_EventScript_GruntM2::
	trainerbattle_single TRAINER_APEX_TEMPLE_GRUNT_2, ApexTemple_MainChamber_Text_GruntM2Intro, ApexTemple_MainChamber_Text_GruntM2Defeated
	msgbox ApexTemple_MainChamber_Text_GruntM2PostBattle, MSGBOX_AUTOCLOSE
	end

ApexTemple_MainChamber_Text_GruntM2Intro:
	.string "We're making the mother of all\n"
	.string "omelets here, kid.\p"
	.string "We can't fret over every egg!$"

ApexTemple_MainChamber_Text_GruntM2Defeated:
	.string "I'm scrambled…$"

ApexTemple_MainChamber_Text_GruntM2PostBattle:
	.string "Our leader is hardboiled.\n"
	.string "You'll never fry him!$"

ApexTemple_MainChamber_EventScript_DoubleBattleGruntM::
	trainerbattle_double TRAINER_APEX_TEMPLE_GRUNTS, ApexTemple_MainChamber_Text_DoubleBattleGruntMIntro, ApexTemple_MainChamber_Text_DoubleBattleGruntMDefeated, ApexTemple_MainChamber_Text_DoubleBattleGruntMNotEnoughPokemon
	msgbox ApexTemple_MainChamber_Text_DoubleBattleGruntMPostBattle, MSGBOX_AUTOCLOSE
	end

ApexTemple_MainChamber_Text_DoubleBattleGruntMIntro:
	.string "You won't pass us!\n"
	.string "We fight together!$"

ApexTemple_MainChamber_Text_DoubleBattleGruntMDefeated:
	.string "No!\n"
	.string "We've failed!$"

ApexTemple_MainChamber_Text_DoubleBattleGruntMNotEnoughPokemon:
	.string "Ha! You can't fight both of us\n"
	.string "with just one Pokémon!$"

ApexTemple_MainChamber_Text_DoubleBattleGruntMPostBattle:
	.string "We won't budge until our business\n"
	.string "here is finished!$"

ApexTemple_MainChamber_EventScript_DoubleBattleGruntF::
	trainerbattle_double TRAINER_APEX_TEMPLE_GRUNTS, ApexTemple_MainChamber_Text_DoubleBattleGruntFIntro, ApexTemple_MainChamber_Text_DoubleBattleGruntFDefeated, ApexTemple_MainChamber_Text_DoubleBattleGruntFNotEnoughPokemon
	msgbox ApexTemple_MainChamber_Text_DoubleBattleGruntFPostBattle, MSGBOX_AUTOCLOSE
	end

ApexTemple_MainChamber_Text_DoubleBattleGruntFIntro:
	.string "Some kid isn't getting past us,\n"
	.string "not on my watch!$"

ApexTemple_MainChamber_Text_DoubleBattleGruntFDefeated:
	.string "Our time is ticking out…$"

ApexTemple_MainChamber_Text_DoubleBattleGruntFNotEnoughPokemon:
	.string "We have principles.\n"
	.string "Two on one just isn't fair.$"

ApexTemple_MainChamber_Text_DoubleBattleGruntFPostBattle:
	.string "We're not moving until Enoch\n"
	.string "says so.$"

ApexTemple_MainChamber_EventScript_DomeFossilPainting::
	msgbox ApexTemple_MainChamber_Text_DomeFossilPainting, MSGBOX_SIGN
	end

ApexTemple_MainChamber_Text_DomeFossilPainting:
	.string "It is a painting of an ancient\n"
	.string "Pokémon.\p"
	.string "Its pattern resembles a\n"
	.string "Dome Fossil!$"

ApexTemple_MainChamber_EventScript_HelixFossilPainting::
	msgbox ApexTemple_MainChamber_Text_HelixFossilPainting, MSGBOX_SIGN
	end

ApexTemple_MainChamber_Text_HelixFossilPainting:
	.string "It is a painting of an ancient\n"
	.string "Pokémon.\p"
	.string "Its pattern resembles a\n"
	.string "Helix Fossil!$"
