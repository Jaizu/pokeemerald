CelantoTown_Library_MapScripts::
	.byte 0

CelantoTown_Library_EventScript_Woman::
	msgbox CelantoTown_Library_Text_TheTotemPoles, MSGBOX_NPC
	end

CelantoTown_Library_Text_TheTotemPoles:
	.string "Have you seen the Totem Poles?\n"
	.string "They remind me of Xatu!$"

CelantoTown_Library_EventScript_Maniac::
	lock
	faceplayer
	msgbox CelantoTown_Library_Text_ImReadingThrillingNovel, MSGBOX_DEFAULT
	goto CelantoTown_Library_EventScript_FaceOriginalDirection
	end
	
CelantoTown_Library_EventScript_FaceOriginalDirection::
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CelantoTown_Library_Text_ImReadingThrillingNovel:
	.string "I'm reading a thrilling novel\n"
	.string "about a man and his Gardevoir!$"

CelantoTown_Library_EventScript_Clerk::
	lock
	faceplayer
	compare VAR_CELANTO_TOWN_STATE, 2
	goto_if_lt CelantoTown_Library_EventScript_ClerkCanalave
	compare VAR_CELANTO_LIBRARY_STATE, 1
	goto_if_ge CelantoTown_Library_EventScript_ClerkCanalave
	msgbox CelantoTown_Library_Text_DidYouHearProfRedwood, MSGBOX_DEFAULT
	release
	end

CelantoTown_Library_Text_DidYouHearProfRedwood:
	.string "Did you hear?\p"
	.string "The {COLOR GREEN}Orbtus Pokémon Professor{COLOR RED}\n"
	.string "is giving away Pokémon in the back.$"

CelantoTown_Library_EventScript_ClerkCanalave:
	msgbox CelantoTown_Library_Text_HaveYouHeardCanalave, MSGBOX_DEFAULT
	release
	end

CelantoTown_Library_Text_HaveYouHeardCanalave:
	.string "Have you heard of Canalave City,\n"
	.string "in the Sinnoh region?\p"
	.string "I've heard that they have a great\n"
	.string "library, one way bigger than ours!$"

CelantoTown_Library_EventScript_BattleGirl::
	msgbox CelantoTown_Library_Text_PreferBattling, MSGBOX_NPC
	end

CelantoTown_Library_Text_PreferBattling:
	.string "If I'm honest, I prefer battling\n"
	.string "with my Pokémon to studying.$"

CelantoTown_Library_EventScript_OldMan::
	lock
	faceplayer
	msgbox CelantoTown_Library_Text_BooksOlderThanMe, MSGBOX_DEFAULT
	goto CelantoTown_Library_EventScript_FaceOriginalDirection
	end

CelantoTown_Library_Text_BooksOlderThanMe:
	.string "Hoho, some of these books\n"
	.string "are even older than me!$"

CelantoTown_Library_EventScript_OldWoman::
	lock
	faceplayer
	msgbox CelantoTown_Library_Text_ReadingAboutMegaEvolution, MSGBOX_DEFAULT
	goto CelantoTown_Library_EventScript_FaceOriginalDirection
	end

CelantoTown_Library_Text_ReadingAboutMegaEvolution:
	.string "I'm reading a history of\n"
	.string "{COLOR GREEN}Mega Evolution{COLOR RED}.\p"
	.string "There seems to be a lot about\n"
	.string "meteorites, and outer-space…$"

CelantoTown_Library_EventScript_Camper::
	lock
	faceplayer
	msgbox CelantoTown_Library_Text_HaveYouReadAboutGreatDisaster, MSGBOX_DEFAULT
	goto CelantoTown_Library_EventScript_FaceOriginalDirection
	end

CelantoTown_Library_Text_HaveYouReadAboutGreatDisaster:
	.string "Have you read about the great\n"
	.string "disaster that destroyed Orbtus?\p"
	.string "The people who lived here long ago\n"
	.string "were wiped out by earthquakes!$"

CelantoTown_Library_EventScript_Youngster::
	msgbox CelantoTown_Library_Text_RelicanthPatterns, MSGBOX_NPC
	end

CelantoTown_Library_Text_RelicanthPatterns:
	.string "Relicanth patterns look like\n"
	.string "maps! Isn't that cool?$"

CelantoTown_Library_EventScript_Redwood::
	lock
	faceplayer
	msgbox CelantoTown_Library_Text_OhHelloImSettingUp, MSGBOX_DEFAULT
	goto CelantoTown_Library_EventScript_FaceOriginalDirection
	end

CelantoTown_Library_Text_OhHelloImSettingUp:
	.string "{COLOR DARK_GREY}Redwood: {COLOR BLUE}Oh, hello!\n"
	.string "I'm setting up right now.\p"
	.string "The library has let me use their\n"
	.string "back room for a while.\p"
	.string "Say, why don't you come back\n"
	.string "later? I shouldn't be too long.$"
