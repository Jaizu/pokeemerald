ValoonTown_BlueShardMeistersHouse_MapScripts::
	.byte 0

ValoonTown_BlueShardMeistersHouse_EventScript_BlueShardMeister::
	lock
	faceplayer
	msgbox ValoonTown_BlueShardMeistersHouse_Text_Intro, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ValoonTown_BlueShardMeistersHouse_EventScript_ExitTutorMoveSelect
	// TODO: Implement
	release
	end

ValoonTown_BlueShardMeistersHouse_EventScript_ExitTutorMoveSelect:
	msgbox ValoonTown_BlueShardMeistersHouse_Text_WoeIsMe, MSGBOX_DEFAULT
	release
	end

ValoonTown_BlueShardMeistersHouse_Text_Intro:
	.string "Oh blue! Blue blue blue!\n"
	.string "My favorite color!\p"
	.string "Tell me, do you have any\n"
	.string "{COLOR GREEN}Blue Shards{COLOR BLUE} for me?$"

ValoonTown_BlueShardMeistersHouse_Text_WoeIsMe:
	.string "You changed your mind?\n"
	.string "Oh, woe is me! I am blue!$"

ValoonTown_BlueShardMeistersHouse_EventScript_StoneShardExchange::
	lock
	faceplayer
	msgbox ValoonTown_BlueShardMeistersHouse_Text_SighHowMayIHelpYou, MSGBOX_DEFAULT
	// TODO: Implement
	release
	end

ValoonTown_BlueShardMeistersHouse_Text_SighHowMayIHelpYou:
	.string "Sigh…\n"
	.string "How may I help you?$"

ValoonTown_BlueShardMeistersHouse_EventScript_LittleGirl::
	msgbox ValoonTown_BlueShardMeistersHouse_Text_MyDaddyIsTheBlueShardMeister, MSGBOX_NPC
	end

ValoonTown_BlueShardMeistersHouse_Text_MyDaddyIsTheBlueShardMeister:
	.string "My daddy is the\n"
	.string "Blue Shard Meister.\p"
	.string "He makes my sister help out, too.\p"
	.string "She lets customers trade their\n"
	.string "Water Stones for Blue Shards.\p"
	.string "She finds it boring, though…\n"
	.string "It looks like fun to me!\p"
	.string "Maybe when I'm older, I can take\n"
	.string "over her job!$"
