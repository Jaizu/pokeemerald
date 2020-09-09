NestpineClimb_MapScripts::
	.byte 0

NestpineClimb_EventScript_RouteSign::
	msgbox NestpineClimb_Text_RouteSign, MSGBOX_SIGN
	end

NestpineClimb_Text_RouteSign:
	.string "Nestpine Climb\n"
	.string "{UP_ARROW} Nestpine Town {DOWN_ARROW} Celanto Path$"

NestpineClimb_EventScript_NetasHouseSign::
	msgbox NestpineClimb_Text_NetasHouseSign, MSGBOX_SIGN
	end

NestpineClimb_Text_NetasHouseSign:
	.string "Neta's house$"
