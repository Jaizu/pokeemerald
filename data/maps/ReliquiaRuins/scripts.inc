.equ LOCALID_MORGANA, 1

ReliquiaRuins_MapScripts::
	.byte 0

ReliquiaRuins_EventScript_OldMan::
	msgbox ReliquiaRuins_Text_MyGrandfatherToldMe, MSGBOX_NPC
	end

ReliquiaRuins_Text_MyGrandfatherToldMe:
	.string "My grandfather told me that each\n"
	.string "totem pole has its own story.\p"
	.string "I wonder if that's true?$"

ReliquiaRuins_EventScript_HexManiac::
	msgbox ReliquiaRuins_Text_CanYouSense, MSGBOX_NPC
	end

ReliquiaRuins_Text_CanYouSense:
	.string "Can you sense the spiritual energy\n"
	.string "here? It's overwhelming!$"

ReliquiaRuins_EventScript_Fisherman::
	msgbox ReliquiaRuins_Text_QuietSeaLife, MSGBOX_NPC
	end

ReliquiaRuins_Text_QuietSeaLife:
	.string "Not a bite!\p"
	.string "I wonder why the sea life is so\n"
	.string "quiet around here?$"

ReliquiaRuins_EventScript_RouteSign::
	msgbox ReliquiaRuins_Text_RouteSign, MSGBOX_SIGN
	end

ReliquiaRuins_Text_RouteSign:
	.string "Reliquia Ruins\n"
	.string "{UP_ARROW} Celanto Town {DOWN_ARROW} Totem Poles\l"
	.string "{DOWN_ARROW} Sabulo Cross$"

ReliquiaRuins_EventScript_RockWithAncientGlyphs::
	msgbox ReliquiaRuins_Text_RockWithAncientGlyphs, MSGBOX_SIGN
	end

ReliquiaRuins_Text_RockWithAncientGlyphs:
	.string "The rock is inscribed with\n"
	.string "ancient glyphs.$"

ReliquiaRuins_EventScript_MorganaTrigger::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox ReliquiaRuins_Text_TheseTotemPolesAreFascinating
	closemessage
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_MORGANA, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox ReliquiaRuins_Text_HistoriansCantSeemToAgree, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq ReliquiaRuins_EventScript_PlayerChoseToGiveBook
	compare VAR_RESULT, YES
	call_if_ne ReliquiaRuins_EventScript_PlayerChoseToNotGiveBook
	msgbox ReliquiaRuins_Text_ExcuseMe, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, ReliquiaRuins_Movement_PlayerMoveOutTheWay
	waitmovement 0
	delay 30	
	applymovement LOCALID_MORGANA, ReliquiaRuins_Movement_MorganaExit
	waitmovement 0
	removeobject LOCALID_MORGANA
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_CELANTO_TOWN_STATE, 1
	setvar VAR_RELIQUIA_RUINS_STATE, 1
	releaseall
	end

ReliquiaRuins_Text_TheseTotemPolesAreFascinating:
	.string "???: {COLOR RED}These totem poles are\n"
	.string "fascinating, are they not?$"

ReliquiaRuins_Text_HistoriansCantSeemToAgree:
	.string "???: {COLOR RED}Historians can't seem to agree\n"
	.string "on why they were built…\p"
	.string "But the {COLOR GREEN}Elders of Orbtus{COLOR RED} were wise.\n"
	.string "That's something I know for sure.\p"
	.string "The book you have is ancient, and\n"
	.string "was once a family heirloom of mine.\p"
	.string "It does not belong here, in a\n"
	.string "library far from home.\p"
	.string "Would you be kind enough to return\n"
	.string "it to its rightful owner?$"

ReliquiaRuins_Text_ExcuseMe:
	.string "???: {COLOR RED}Excuse me, child.$"

ReliquiaRuins_Movement_PlayerMoveOutTheWay:
	walk_down
	walk_right
	walk_in_place_fastest_left
	step_end

ReliquiaRuins_Movement_MorganaExit:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
	
ReliquiaRuins_EventScript_PlayerChoseToGiveBook:
	call ReliquiaRuins_EventScript_HandOverTheBook
	msgbox ReliquiaRuins_Text_ThankYouVeryMuch
	return

ReliquiaRuins_Text_ThankYouVeryMuch:
	.string "???: {COLOR RED}Thank you very much, child.\p"
	.string "You strike me as very wise, for\n"
	.string "your age.\p"
	.string "Perhaps our paths will cross again?$"

ReliquiaRuins_EventScript_PlayerChoseToNotGiveBook:
	playse SE_PIN
	applymovement LOCALID_MORGANA, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MORGANA, Common_Movement_Delay48
	waitmovement 0
	msgbox ReliquiaRuins_Text_InThatCaseIChallengeYou, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox ReliquiaRuins_Text_YouHaveNoPokemon, MSGBOX_DEFAULT
	closemessage
	goto ReliquiaRuins_EventScript_HandOverTheBook
	end

ReliquiaRuins_Text_InThatCaseIChallengeYou:
	.string "???: {COLOR RED}What?!\p"
	.string "In that case, I challenge you to a\n"
	.string "Pokémon battle!$"

ReliquiaRuins_Text_YouHaveNoPokemon:
	.string "???: {COLOR RED}You have no Pokémon?\n"
	.string "Then you have no choice!$"

ReliquiaRuins_EventScript_HandOverTheBook:
	applymovement LOCALID_MORGANA, Common_Movement_WalkDown
	waitmovement 0
	removeitem ITEM_DUSTY_TOME
	removeitem ITEM_LETTER
	msgbox ReliquiaRuins_Text_HandedOverTheDustyTome
	delay 30
	return

ReliquiaRuins_Text_HandedOverTheDustyTome:
	.string "{PLAYER} handed over the\n"
	.string "Dusty Tome to the old lady.$"
