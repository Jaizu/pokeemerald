ArchanTunnel_B1F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArchanTunnel_B1F_1R_OnTransition
	.byte 0

ArchanTunnel_B1F_1R_OnTransition:
	call_if_unset FLAG_VISITED_OVARR_TOWN, ArchanTunnel_B1F_1R_EventScript_BlockOvarr
	end
	
ArchanTunnel_B1F_1R_EventScript_BlockOvarr:
	setmaplayoutindex LAYOUT_ARCHAN_TUNNEL_B1F_1R_OVARR_BLOCKED
	return

Archan_Tunnel_B1F_1R_EventScript_Louise::
	trainerbattle_single TRAINER_LOUISE, Archan_Tunnel_B1F_1R_Text_LouiseIntro, Archan_Tunnel_B1F_1R_Text_LouiseDefeated
	msgbox Archan_Tunnel_B1F_1R_Text_LouisePostBattle, MSGBOX_AUTOCLOSE
	end

Archan_Tunnel_B1F_1R_Text_LouiseIntro:
	.string "I've been reading up on Pokémon\n"
	.string "battles all day. I can't lose!$"

Archan_Tunnel_B1F_1R_Text_LouiseDefeated:
	.string "Wait, what?\n"
	.string "Did I misread you?$"

Archan_Tunnel_B1F_1R_Text_LouisePostBattle:
	.string "Winning Pokémon battles comes down\n"
	.string "to reading your opponent.$"

Archan_Tunnel_B1F_1R_EventScript_Quinn::
	trainerbattle_single TRAINER_QUINN, Archan_Tunnel_B1F_1R_Text_QuinnIntro, Archan_Tunnel_B1F_1R_Text_QuinnDefeated
	msgbox Archan_Tunnel_B1F_1R_Text_QuinnPostBattle, MSGBOX_AUTOCLOSE
	end

Archan_Tunnel_B1F_1R_Text_QuinnIntro:
	.string "Rumble rumble…\n"
	.string "I'm as unpredictable as the earth!$"

Archan_Tunnel_B1F_1R_Text_QuinnDefeated:
	.string "Crushed…$"

Archan_Tunnel_B1F_1R_Text_QuinnPostBattle:
	.string "Earthquakes are caused when tectonic\n"
    .string "plates scrape past one another.$"

Archan_Tunnel_B1F_1R_EventScript_Cory::
	trainerbattle_single TRAINER_CORY, Archan_Tunnel_B1F_1R_Text_CoryIntro, Archan_Tunnel_B1F_1R_Text_CoryDefeated
	msgbox Archan_Tunnel_B1F_1R_Text_CoryPostBattle, MSGBOX_AUTOCLOSE
	end

Archan_Tunnel_B1F_1R_Text_CoryIntro:
	.string "You work for the Prof.?\n"
    .string "I'm gonna battle him one day!\p"
    .string "You'll be great practice!$"

Archan_Tunnel_B1F_1R_Text_CoryDefeated:
	.string "Aw, it looks like I have some work\n"
    .string "to do…$"

Archan_Tunnel_B1F_1R_Text_CoryPostBattle:
	.string "So, what is the Prof. researching?$"

Archan_Tunnel_B1F_1R_EventScript_Worker::
	msgbox Archan_Tunnel_B1F_1R_Text_WeveBeenForcedToHalt, MSGBOX_NPC
	end

Archan_Tunnel_B1F_1R_Text_WeveBeenForcedToHalt:
	.string "We've been forced to halt\n"
	.string "construction on the tunnel to\l"
	.string "Ovarr Town.\p"
	.string "The tremors just make construction\n"
	.string "too dangerous!$"

Archan_Tunnel_B1F_1R_EventScript_Hiker::
	msgbox Archan_Tunnel_B1F_1R_Text_CarelessTrainersDropItems, MSGBOX_NPC
	end

Archan_Tunnel_B1F_1R_Text_CarelessTrainersDropItems:
	.string "Careless Trainers often drop items\n"
	.string "when they walk through dark caves.\p"
	.string "That's great for observant\n"
	.string "explorers like myself!$"
