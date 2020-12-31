.set LOCALID_MOVE_DELETER, 1

NestpineTown_MoveDeletersHouse_MapScripts::
	.byte 0

NestpineTown_MoveDeletersHouse_EventScript_MoveDeleter::
	lockall
	applymovement LOCALID_MOVE_DELETER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox NestpineTown_MoveDeletersHouse_Text_ICanMakeMonForgetMove, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, NestpineTown_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	case NO, NestpineTown_MoveDeletersHouse_EventScript_ComeAgain
	releaseall
	end

NestpineTown_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget::
	msgbox NestpineTown_MoveDeletersHouse_Text_WhichMonShouldForget, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq NestpineTown_MoveDeletersHouse_EventScript_ComeAgain
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq NestpineTown_MoveDeletersHouse_EventScript_EggCantForgetMoves
	special GetNumMovesSelectedMonHas
	compare VAR_RESULT, 1
	goto_if_eq NestpineTown_MoveDeletersHouse_EventScript_MonOnlyKnowsOneMove
	msgbox NestpineTown_MoveDeletersHouse_Text_WhichMoveShouldBeForgotten, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	compare VAR_0x8005, MAX_MON_MOVES
	goto_if_eq NestpineTown_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	special BufferMoveDeleterNicknameAndMove
	msgbox NestpineTown_MoveDeletersHouse_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, NestpineTown_MoveDeletersHouse_EventScript_TryForgetMove
	case NO, NestpineTown_MoveDeletersHouse_EventScript_ComeAgain
	releaseall
	end

NestpineTown_MoveDeletersHouse_EventScript_TryForgetMove::
	special IsLastMonThatKnowsSurf
	compare VAR_RESULT, TRUE
	goto_if_eq NestpineTown_MoveDeletersHouse_EventScript_LastMonWithSurf
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox NestpineTown_MoveDeletersHouse_Text_MonHasForgottenMove, MSGBOX_DEFAULT
	releaseall
	end

NestpineTown_MoveDeletersHouse_EventScript_MonOnlyKnowsOneMove::
	special BufferMoveDeleterNicknameAndMove
	msgbox NestpineTown_MoveDeletersHouse_Text_MonOnlyKnowsOneMove, MSGBOX_DEFAULT
	releaseall
	end

NestpineTown_MoveDeletersHouse_EventScript_EggCantForgetMoves::
	msgbox NestpineTown_MoveDeletersHouse_Text_EggCantForgetMoves, MSGBOX_DEFAULT
	releaseall
	end

NestpineTown_MoveDeletersHouse_EventScript_ComeAgain::
	msgbox NestpineTown_MoveDeletersHouse_Text_ComeAgain, MSGBOX_DEFAULT
	releaseall
	end

NestpineTown_MoveDeletersHouse_EventScript_LastMonWithSurf::
	special BufferMoveDeleterNicknameAndMove
	msgbox NestpineTown_MoveDeletersHouse_Text_CantForgetSurf, MSGBOX_DEFAULT
	releaseall
	end

NestpineTown_MoveDeletersHouse_Text_ICanMakeMonForgetMove:
	.string "Uh…\n"
	.string "Oh, yes, I'm the Move Deleter.\p"
	.string "I can make Pokémon forget their moves.\p"
	.string "Would you like me to do that?$"

NestpineTown_MoveDeletersHouse_Text_WhichMonShouldForget:
	.string "Which Pokémon should forget a move?$"

NestpineTown_MoveDeletersHouse_Text_WhichMoveShouldBeForgotten:
	.string "Which move should be forgotten?$"

NestpineTown_MoveDeletersHouse_Text_MonOnlyKnowsOneMove:
	.string "{STR_VAR_1} knows only one move\n"
	.string "so it can't be forgotten…$"

NestpineTown_MoveDeletersHouse_Text_MonsMoveShouldBeForgotten:
	.string "Hm! {STR_VAR_1}'s {STR_VAR_2}?\n"
	.string "That move should be forgotten?$"

NestpineTown_MoveDeletersHouse_Text_MonHasForgottenMove:
	.string "It worked to perfection!\p"
	.string "{STR_VAR_1} has forgotten\n"
	.string "{STR_VAR_2} completely.$"

NestpineTown_MoveDeletersHouse_Text_ComeAgain:
	.string "Come again if there are moves that\n"
	.string "need to be forgotten.$"

NestpineTown_MoveDeletersHouse_Text_EggCantForgetMoves:
	.string "What?\n"
	.string "No Egg should know any moves.$"

NestpineTown_MoveDeletersHouse_Text_CantForgetSurf:
	.string "Hm!\p"
	.string "Your {STR_VAR_1} doesn't seem willing\n"
	.string "to forget Surf.$"
