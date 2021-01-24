BattleMarsh_MapScripts::
	.byte 0

BattleMarsh_EventScript_RouteSign::
	msgbox BattleMarsh_Text_RouteSign, MSGBOX_SIGN
	end

BattleMarsh_Text_RouteSign:
	.string "{LEFT_ARROW} Telmurk Swamp {RIGHT_ARROW} Telmurk City$"

BattleMarsh_EventScript_BattleMarshSign::
	msgbox BattleMarsh_Text_BattleMarshSign, MSGBOX_SIGN
	end

BattleMarsh_Text_BattleMarshSign:
	.string "Battle Marsh\n"
	.string "Where Trainers are put to the test!$"
