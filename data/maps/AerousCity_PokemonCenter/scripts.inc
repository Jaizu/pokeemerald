.equ LOCALID_NURSE, 1

AerousCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AerousCity_PokemonCenter_OnTransition
	.byte 0

AerousCity_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_AEROUS_CITY
	end

AerousCity_PokemonCenter_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
