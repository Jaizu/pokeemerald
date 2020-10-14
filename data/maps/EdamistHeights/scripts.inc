EdamistHeights_MapScripts::
	.byte 0

EdamistHeights_EventScript_RouteSign::
	msgbox EdamistHeights_Text_RouteSign, MSGBOX_SIGN
	end

EdamistHeights_Text_RouteSign:
	.string "Edamist Heights\n"
	.string "{LEFT_ARROW} Windmist City {RIGHT_ARROW} Edashore Town$"

EdamistHeights_EventScript_Explorer::
	msgbox EdamistHeights_Text_DontYouThink, MSGBOX_NPC
	end

EdamistHeights_Text_DontYouThink:
	.string "Don't you think the name of this\n"
	.string "place is cute?\p"
	.string "It's like a little word romance\n"
	.string "between Edashore and Windmist!$"
