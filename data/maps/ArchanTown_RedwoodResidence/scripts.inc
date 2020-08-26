ArchanTown_RedwoodResidence_MapScripts::
	.byte 0

ArchanTown_RedwoodResidence_Redwood::
	lock
	faceplayer
	clearflag FLAG_HIDE_ARCHAN_TOWN_REDWOOD
	clearflag FLAG_HIDE_ARCHAN_TOWN_COULTER
	setvar VAR_ARCHAN_TOWN_STATE, 1
	warp MAP_ARCHAN_TOWN, 2, 0, 0
	waitstate
	release
	end
