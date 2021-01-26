TelmurkCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TelmurkCity_OnTransition
	.byte 0

TelmurkCity_OnTransition::
	setflag FLAG_VISITED_TELMURK_CITY
	end

TelmurkCity_EventScript_CitySign::
	msgbox TelmurkCity_Text_CitySign, MSGBOX_SIGN
	end

TelmurkCity_Text_CitySign:
	.string "Telmurk City\n"
	.string "The Mighty Marsh Metropolis.$"

TelmurkCity_EventScript_GymSign::
	msgbox TelmurkCity_Text_GymSign, MSGBOX_SIGN
	end

TelmurkCity_Text_GymSign:
	.string "Telmurk City Pokémon Gym\p"
	.string "Leader: Sid\n"
	.string "“Still water is the most dangerous…”$"

TelmurkCity_EventScript_UndergroudPathSign::
	msgbox TelmurkCity_Text_UndergroudPathSign, MSGBOX_SIGN
	end

TelmurkCity_Text_UndergroudPathSign:
	.string "Underground Path\n"
	.string "Now leaving Telmurk!$"

TelmurkCity_EventScript_MsMurkrowSign::
	msgbox TelmurkCity_Text_MsMurkrowSign, MSGBOX_SIGN
	end

TelmurkCity_Text_MsMurkrowSign:
	.string "Ms. Murkrow's Special Poké Balls$"
