ArchanTunnel_B1F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArchanTunnel_B1F_1R_OnTransition
	.byte 0

ArchanTunnel_B1F_1R_OnTransition:
	call_if_unset FLAG_VISITED_OVARR_TOWN, ArchanTunnel_B1F_1R_EventScript_BlockOvarr
	end
	
ArchanTunnel_B1F_1R_EventScript_BlockOvarr:
	setmaplayoutindex LAYOUT_ARCHAN_TUNNEL_B1F_1R_OVARR_BLOCKED
	return

ArchanTunnel_B1F_1R_EventScript_Louise::
	trainerbattle_single TRAINER_LOUISE, ArchanTunnel_B1F_1R_Text_LouiseIntro, ArchanTunnel_B1F_1R_Text_LouiseDefeated
	msgbox ArchanTunnel_B1F_1R_Text_LouisePostBattle, MSGBOX_AUTOCLOSE
	end

ArchanTunnel_B1F_1R_Text_LouiseIntro:
	.string "I've been reading up on Pokémon\n"
	.string "battles all day. I can't lose!$"

ArchanTunnel_B1F_1R_Text_LouiseDefeated:
	.string "Wait, what?\n"
	.string "Did I misread you?$"

ArchanTunnel_B1F_1R_Text_LouisePostBattle:
	.string "Winning Pokémon battles comes down\n"
	.string "to reading your opponent.$"

ArchanTunnel_B1F_1R_EventScript_Quinn::
	trainerbattle_single TRAINER_QUINN, ArchanTunnel_B1F_1R_Text_QuinnIntro, ArchanTunnel_B1F_1R_Text_QuinnDefeated
	msgbox ArchanTunnel_B1F_1R_Text_QuinnPostBattle, MSGBOX_AUTOCLOSE
	end

ArchanTunnel_B1F_1R_Text_QuinnIntro:
	.string "Rumble rumble…\n"
	.string "I'm as unpredictable as the earth!$"

ArchanTunnel_B1F_1R_Text_QuinnDefeated:
	.string "Crushed…$"

ArchanTunnel_B1F_1R_Text_QuinnPostBattle:
	.string "Earthquakes are caused when tectonic\n"
    .string "plates scrape past one another.$"

ArchanTunnel_B1F_1R_EventScript_Cory::
	trainerbattle_single TRAINER_CORY, ArchanTunnel_B1F_1R_Text_CoryIntro, ArchanTunnel_B1F_1R_Text_CoryDefeated
	msgbox ArchanTunnel_B1F_1R_Text_CoryPostBattle, MSGBOX_AUTOCLOSE
	end

ArchanTunnel_B1F_1R_Text_CoryIntro:
	.string "You work for the Prof.?\n"
    .string "I'm gonna battle him one day!\p"
    .string "You'll be great practice!$"

ArchanTunnel_B1F_1R_Text_CoryDefeated:
	.string "Aw, it looks like I have some work\n"
    .string "to do…$"

ArchanTunnel_B1F_1R_Text_CoryPostBattle:
	.string "So, what is the Prof. researching?$"

ArchanTunnel_B1F_1R_EventScript_Worker::
	msgbox ArchanTunnel_B1F_1R_Text_WeveBeenForcedToHalt, MSGBOX_NPC
	end

ArchanTunnel_B1F_1R_Text_WeveBeenForcedToHalt:
	.string "We've been forced to halt\n"
	.string "construction on the tunnel to\l"
	.string "Ovarr Town.\p"
	.string "The tremors just make construction\n"
	.string "too dangerous!$"

ArchanTunnel_B1F_1R_EventScript_RuinManiac::
	msgbox ArchanTunnel_B1F_1R_Text_CarelessTrainersDropItems, MSGBOX_NPC
	end

ArchanTunnel_B1F_1R_Text_CarelessTrainersDropItems:
	.string "Careless Trainers often drop items\n"
	.string "when they walk through dark caves.\p"
	.string "That's great for observant\n"
	.string "explorers like myself!$"
