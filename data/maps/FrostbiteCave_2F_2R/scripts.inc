FrostbiteCave_2F_2R_MapScripts::
	.byte 0

FrostbiteCave_2F_2R_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, FrostbiteCave_2F_2R_Text_NateIntro, FrostbiteCave_2F_2R_Text_NateDefeated
	msgbox FrostbiteCave_2F_2R_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

FrostbiteCave_2F_2R_Text_NateIntro:
	.string "I'm a straightforward fella.\n"
	.string "Winner gets the Fossil, okay?$"

FrostbiteCave_2F_2R_Text_NateDefeated:
	.string "It's all yours, buddy!$"

FrostbiteCave_2F_2R_Text_NatePostBattle:
	.string "Prof. Redwood is the guy to see\n"
	.string "for reviving Fossils.$"

FrostbiteCave_2F_2R_EventScript_Hiker::
	msgbox FrostbiteCave_2F_2R_Text_HeSeemsTooDistracted, MSGBOX_DEFAULT
	closemessage
	release
	end

FrostbiteCave_2F_2R_Text_HeSeemsTooDistracted:
	.string "{COLOR DARK_GREY}He seems too distracted to\n"
	.string "notice you…\p"
	.string "{COLOR BLUE}Don't panic… Remember your\n"
	.string "orientation lessons!\p"
	.string "You don't want to miss the\n"
	.string "Meteor Festival…$"
