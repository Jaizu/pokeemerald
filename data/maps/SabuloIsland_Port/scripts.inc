SabuloIsland_Port_MapScripts::
	.byte 0

SabuloIsland_Port_EventScript_Sailor::
	lock
	faceplayer
	msgbox SabuloIsland_Port_Text_SetSailForAerous, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SabuloIsland_Port_EventScript_LeaveForAerousCity
	closemessage
	release
	end

SabuloIsland_Port_EventScript_LeaveForAerousCity:
	msgbox SabuloIsland_Port_Text_AllAboard, MSGBOX_DEFAULT
	closemessage
	delay 20
	warp MAP_AEROUS_CITY_PORT, -1, 8, 5
	waitstate
	release
	end

SabuloIsland_Port_Text_SetSailForAerous:
	.string "Would you like to set sail\n"
	.string "for {COLOR GREEN}Aerous City{COLOR BLUE}?$"

SabuloIsland_Port_Text_AllAboard:
	.string "All right!\n"
	.string "All aboard the S.S. Wake!$"
