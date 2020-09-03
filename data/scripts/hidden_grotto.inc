EventScript_HiddenGrottoTree::
	lock
	msgbox HiddenGrotto_Text_LookYouFoundANarrowPathWillYouFollowIt, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq EventScript_DoHiddenGrottoWarp
	release
	end

EventScript_DoHiddenGrottoWarp::
	special DoWarpAtPlayerPos
	waitstate
	release
	end

HiddenGrotto_Text_LookYouFoundANarrowPathWillYouFollowIt:
	.string "Look!\n"
	.string "You've found a narrow path!\p"
	.string "Will you follow it?$"
