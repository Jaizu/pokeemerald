NestpineClimb_NetasHouse_MapScripts::
	.byte 0

NestpineClimb_NetasHouse_EventScript_Neta::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_NETAS_METAL_COAT, NestpineClimb_NetasHouse_EventScript_NetaDiscussStackOfDrives
	msgbox NestpineClimb_NetasHouse_Text_OhThatRedwoodCard, MSGBOX_DEFAULT
	setflag FLAG_SYS_PC_NETA
	giveitem ITEM_METAL_COAT
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_NETAS_METAL_COAT
	msgbox NestpineClimb_NetasHouse_Text_ExplainMetalCoat, MSGBOX_DEFAULT
	release
	end

NestpineClimb_NetasHouse_EventScript_NetaDiscussStackOfDrives:
	msgbox NestpineClimb_NetasHouse_Text_DiscussStackOfDrives, MSGBOX_DEFAULT
	release
	end

NestpineClimb_NetasHouse_Text_OhThatRedwoodCard:
	.string "Oh, hey there!\n"
	.string "That Redwood Card…\p"
	.string "You must be a Pokémon Trainer!\p"
	.string "Sorry, I should introduce myself.\n"
	.string "The name's Neta!\p"
	.string "I maintain the Storage System for\n"
	.string "the Orbtus region.\p"
	.string "I'm sorry about the mess.\p"
	.string "…Actually, when I was cleaning\n"
	.string "up, I found this!\p"
	.string "I have no use for it, so…\n"
	.string "Here you go!$"

NestpineClimb_NetasHouse_Text_ExplainMetalCoat:
	.string "That Metal Coat boosts Steel-type\n"
	.string "moves!\p"
	.string "I hope you make good use of the\n"
	.string "Pokémon Boxes.$"

NestpineClimb_NetasHouse_Text_DiscussStackOfDrives:
	.string "When tidying up I found this\n"
	.string "{COLOR GREEN}stack of Drives{COLOR RED}, too…\p"
	.string "I guess it must be old versions of\n"
	.string "my software?\p"
	.string "Best to keep hold of them, right?$"
