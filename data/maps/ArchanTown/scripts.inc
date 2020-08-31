.equ LOCALID_OLD_MAN, 9
.equ LOCALID_REDWOOD, 10
.equ LOCALID_COULTER, 11

ArchanTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArchanTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ArchanTown_OnFrame
	.byte 0

ArchanTown_OnTransition::
	setflag FLAG_VISITED_ARCHAN_TOWN
	compare VAR_ARCHAN_TOWN_STATE, 1
	call_if_eq ArchanTown_EventScript_MoveOldMan
	end

ArchanTown_OnFrame:
	map_script_2 VAR_ARCHAN_TOWN_STATE, 1, ArchanTown_EventScript_TabletScene
	.2byte 0

ArchanTown_EventScript_MoveOldMan:
	setobjectxyperm LOCALID_OLD_MAN, 21, 17
	setobjectmovementtype LOCALID_OLD_MAN, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	return

ArchanTown_EventScript_TabletScene:
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox ArchanTown_Text_RedwoodThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_REDWOOD, ArchanTown_Movement_RedwoodToTablet
	applymovement LOCALID_COULTER, ArchanTown_Movement_CoulterPlayerToTablet
	applymovement OBJ_EVENT_ID_PLAYER, ArchanTown_Movement_CoulterPlayerToTablet
	waitmovement 0
	delay 20
	fadedefaultbgm
	msgbox ArchanTown_Text_AncientTabletExplanation, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_OHKIDO, 0
	applymovement LOCALID_REDWOOD, ArchanTown_Movement_RedwoodExit
	waitmovement 0
	removeobject LOCALID_REDWOOD
	fadedefaultbgm
	delay 10
	applymovement LOCALID_COULTER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0	
	msgbox ArchanTown_Text_RaceToFindTheSecondTablet, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RG_RIVAL2, 0
	applymovement LOCALID_COULTER, ArchanTown_Movement_CoulterExit
	waitmovement 0
	removeobject LOCALID_COULTER
	fadedefaultbgm
	delay 10
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	clearflag FLAG_DONT_TRANSITION_MUSIC
	clearflag FLAG_DONT_CLEAR_SAVED_MUSIC
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_ARCHAN_TOWN_STATE, 2
	releaseall
	end

ArchanTown_Text_RedwoodThisWay:
	.string "Redwood: {COLOR BLUE}This way!$"

ArchanTown_Text_AncientTabletExplanation:
	.string "Redwood: {COLOR BLUE}Have you felt the tremors?\n"
	.string "They've started off small, but…\p"
	.string "They are getting stronger.\n"
	.string "I fear they will only get worse.\p"
	.string "Data suggests the {COLOR GREEN}Ancient Tablet{COLOR BLUE}\n"
	.string "here is linked to the quakes!\p"
	.string "I've received similar data from\n"
	.string "within the {COLOR GREEN}Archan Tunnel{COLOR BLUE}.\p"
	.string "I theorize there's a {COLOR GREEN}second Tablet{COLOR BLUE}\n"
	.string "buried somewhere close by.\p"
	.string "It would account for the converging\n"
	.string "seismic epicenters of…\p"
	.string "…Ah, I see your eyes glazing over.\n"
	.string	"Sorry, I tend to ramble.\p"
	.string "{COLOR GREEN}Find this second Tablet{COLOR BLUE}!\n"
	.string "That's what's important.\p"
	.string "The Tunnel leads to {COLOR GREEN}Seros Village{COLOR BLUE}.\n"
	.string "Let's meet there! Good luck!$"

ArchanTown_Text_RaceToFindTheSecondTablet:
	.string "{RIVAL}: {COLOR BLUE}I'm sorry about earlier,\n"
	.string "{PLAYER}… You really beat me!\p"
	.string "Water under the bridge, yeah?\n"
	.string "But, I was thinking…\p"
	.string "Let's race to find the second\n"
	.string "Tablet! What do you say?\p"
	.string "A rivalry between us, to raise the\n"
	.string "stakes sky-high! Do you accept?\p"
	.string "…Of course you do! I'll catch you\n"
	.string "at the finish line, Slowpoke!$"

ArchanTown_Movement_RedwoodToTablet:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

ArchanTown_Movement_CoulterPlayerToTablet:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

ArchanTown_Movement_RedwoodExit:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

ArchanTown_Movement_CoulterExit:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

ArchanTown_EventScript_TownSign::
	msgbox ArchanTown_Text_TownSign, MSGBOX_SIGN
	end

ArchanTown_Text_TownSign:
	.string "Archan Town\n"
	.string "Famous for Archaeological Digs!$"

ArchanTown_EventScript_RedwoodSign::
	msgbox ArchanTown_Text_RedwoodSign, MSGBOX_SIGN
	end

ArchanTown_Text_RedwoodSign:
	.string "Redwood Residence$"

ArchanTown_EventScript_AncientTabletSign::
	msgbox ArchanTown_Text_AncientTabletSign, MSGBOX_SIGN
	end

ArchanTown_Text_AncientTabletSign:
	.string "This Ancient Tablet was\n"
	.string "constructed many years ago.\p"
	.string "It appears to portray the Pokémon\n"
	.string "Relicanth.$"

ArchanTown_EventScript_OldWoman::
	msgbox ArchanTown_Text_ProfRedwoodsHouse, MSGBOX_NPC
	end

ArchanTown_Text_ProfRedwoodsHouse:
	.string "Prof. Redwood's house is right next\n"
	.string "to the Pokémon Center.\p"
	.string "Talk about prime real estate!$"

ArchanTown_EventScript_BattleGirl::
	msgbox ArchanTown_Text_RedwoodsFossilMachine, MSGBOX_NPC
	end

ArchanTown_Text_RedwoodsFossilMachine:
	.string "Prof. Redwood has a machine that\n"
	.string "can revive Pokémon from Fossils.\p"
	.string "When does it stop being science,\n"
	.string "and start being magic?$"

ArchanTown_EventScript_FatMan::
	lock
	faceplayer
	msgbox ArchanTown_Text_ZigzagoonInCelantoPath, MSGBOX_NPC
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ArchanTown_Text_ZigzagoonInCelantoPath:
	.string "My Zigzagoon jumped out at me from\n"
	.string "the tall grass in Celanto Path.\p"
	.string "I was scared then, but we're life-\n"
	.string "long friends now! Isn't that great?$"

ArchanTown_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, 0
	msgbox ArchanTown_Text_Zigzagoon, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ArchanTown_Text_Zigzagoon:
	.string "Zigzagoon: {COLOR BLUE}Guguu!$"

ArchanTown_EventScript_Hiker::
	msgbox ArchanTown_Text_WhatsYourTheory, MSGBOX_NPC
	end

ArchanTown_Text_WhatsYourTheory:
	.string "I can't resist a good mystery!\p"
	.string "What's your theory on why the\n"
	.string "tremors are happening?$"

ArchanTown_EventScript_OldMan::
	lock
	faceplayer
	msgbox ArchanTown_Text_LotsOfDifferentFolkTales, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ArchanTown_Text_LotsOfDifferentFolkTales:
	.string "There are lots of different folk\n"
	.string "tales about why the Elders built\l"
	.string "the Ancient Tablet.\p"
	.string "I wonder if any of them are true?$"
