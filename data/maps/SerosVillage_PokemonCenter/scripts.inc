SerosVillage_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SerosVillage_PokemonCenter_OnTransition
	.byte 0

SerosVillage_PokemonCenter_OnTransition:
	setrespawn HEAL_LOCATION_SEROS_VILLAGE
	end

SerosVillage_PokemonCenter_EventScript_Redwood::
	msgbox SerosVillage_PokemonCenter_Text_HiPlayer, MSGBOX_NPC
	end

SerosVillage_PokemonCenter_Text_HiPlayer:
	.string "{COLOR DARK_GREY}Redwood: {COLOR BLUE}Hi {PLAYER}!\p"
	.string "From what I can gather, there's\n"
	.string "definitely a second entrance.\p"
	.string "Nobody seems to know where, though.\n"
	.string "Let's keep searching!$"

SerosVillage_PokemonCenter_EventScript_Youngster::
	msgbox SerosVillage_PokemonCenter_Text_DontKnowAboutSecretTunnels, MSGBOX_NPC
	end

SerosVillage_PokemonCenter_Text_DontKnowAboutSecretTunnels:
	.string "I don't know about any secret\n"
	.string "tunnels.\p"
	.string "There are some suspiciously thin\n"
	.string "trees nearby, though!\p"
	.string "Makes me want to just chop them\n"
	.string "down and see what the big deal is.$"

SerosVillage_PokemonCenter_EventScript_Socialite::
	lock
	faceplayer
	msgbox SerosVillage_PokemonCenter_Text_DoYouWantToLearnAboutFernando, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SerosVillage_PokemonCenter_EventScript_ExplainFernandoBackstory
	msgbox SerosVillage_PokemonCenter_Text_OhFairEnough, MSGBOX_DEFAULT
	release
	end

SerosVillage_PokemonCenter_EventScript_ExplainFernandoBackstory:
	msgbox SerosVillage_PokemonCenter_Text_FernandosGrandpaTheDayCareMan, MSGBOX_DEFAULT
	release
	end

SerosVillage_PokemonCenter_Text_DoYouWantToLearnAboutFernando:
	.string "Do you want to learn about why\n"
	.string "such a young kid is the Gym Leader?$"

SerosVillage_PokemonCenter_Text_OhFairEnough:
	.string "Oh, fair enough.\n"
	.string "It's quite a sad story.$"

SerosVillage_PokemonCenter_Text_FernandosGrandpaTheDayCareMan:
	.string "Fernando's grandpa, the Day-Care\n"
	.string "Man, used to be the Gym Leader\l"
	.string "around here.\p"
	.string "Normally, Fernando's dad would\n"
	.string "have replaced him when he retired…\p"
	.string "But…\p"
	.string "Tragically, Fernando's parents both\n"
	.string "passed away when he was young.\p"
	.string "His grandparents think letting him\n"
	.string "run the Gym is a good outlet.\p"
	.string "Some kids have to grow up so fast!$"
