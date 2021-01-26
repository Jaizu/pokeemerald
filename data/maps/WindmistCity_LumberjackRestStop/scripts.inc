WindmistCity_LumberjackRestStop_MapScripts::
	.byte 0

WindmistCity_LumberjackRestStop_EventScript_Clerk::
	lock
	faceplayer
	message WindmistCity_LumberjackRestStop_Text_WeSellTMs
	waitmessage
	pokemart WindmistCity_LumberjackRestStop_Pokemart_TMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

WindmistCity_LumberjackRestStop_Pokemart_TMs:
	.2byte ITEM_MOOMOO_MILK
	.2byte ITEM_NONE
	release
	end

WindmistCity_LumberjackRestStop_Text_WeSellTMs:
	.string "We're selling TMs to raise funds!\n"
	.string "How can I help you?$"

WindmistCity_LumberjackRestStop_EventScript_Kindler::
	msgbox WindmistCity_LumberjackRestStop_Text_ThisFirewoodIsPerfect, MSGBOX_NPC
	end

WindmistCity_LumberjackRestStop_Text_ThisFirewoodIsPerfect:
	.string "This firewood is perfect for\n"
	.string "kindling!$"

WindmistCity_LumberjackRestStop_EventScript_BlackBelt::
	lock
	faceplayer
	msgbox WindmistCity_LumberjackRestStop_Text_MachopAndI, MSGBOX_DEFAULT
WindmistCity_LumberjackRestStop_EventScript_FaceOriginalDirection:
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

WindmistCity_LumberjackRestStop_Text_MachopAndI:
	.string "My Machop and I run a roof-\n"
	.string "cleaning service!\p"
	.string "We'll shovel snow off your roof\n"
	.string "for a low, low price!\p"
	.string "What?\n"
	.string "You're not a home-owner?\p"
	.string "…Oh.$"

WindmistCity_LumberjackRestStop_EventScript_Machop::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOP, 0
	msgbox WindmistCity_LumberjackRestStop_Text_Machop, MSGBOX_DEFAULT
	goto WindmistCity_LumberjackRestStop_EventScript_FaceOriginalDirection
	end

WindmistCity_LumberjackRestStop_Text_Machop:
	.string "Machop: {COLOR BLUE}Guoh! Gogogoh!$"

WindmistCity_LumberjackRestStop_EventScript_BattleGirl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXPERT_BELT, WindmistCity_LumberjackRestStop_EventScript_ExplainWhereToFindPorygon
	goto_if_set FLAG_BADGE03_GET, WindmistCity_LumberjackRestStop_EventScript_TryGiveExpertBelt
	msgbox WindmistCity_LumberjackRestStop_Text_YouSeemTough, MSGBOX_DEFAULT
	release
	end

WindmistCity_LumberjackRestStop_EventScript_TryGiveExpertBelt:
	msgbox WindmistCity_LumberjackRestStop_Text_YouWonTheEmberBadge, MSGBOX_DEFAULT
	giveitem ITEM_EXPERT_BELT, 1
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXPERT_BELT
	goto WindmistCity_LumberjackRestStop_EventScript_ExplainWhereToFindPorygon
	end

WindmistCity_LumberjackRestStop_EventScript_ExplainWhereToFindPorygon:
	msgbox WindmistCity_LumberjackRestStop_Text_AnExpertTrainerLikeYou, MSGBOX_DEFAULT
	release
	end

WindmistCity_LumberjackRestStop_Text_YouSeemTough:
	.string "You seem tough… I've got something\n"
	.string "for you, if you can beat Nina.$"

WindmistCity_LumberjackRestStop_Text_YouWonTheEmberBadge:
	.string "You won the Ember Badge?\n"
	.string "I insist you take this Expert Belt!$"

WindmistCity_LumberjackRestStop_Text_AnExpertTrainerLikeYou:
	.string "An expert Trainer like you should\n"
	.string "know what that Expert Belt does.$"

WindmistCity_LumberjackRestStop_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_CAUGHT_RIMEWOOD_FOREST_ABOMASNOW, WindmistCity_LumberjackRestStop_EventScript_CaughtRimewoodAbomasnowHiker
	goto_if_set FLAG_DEFEATED_RIMEWOOD_FOREST_ABOMASNOW, WindmistCity_LumberjackRestStop_EventScript_DefeatedRimewoodAbomasnowHiker
	msgbox WindmistCity_LumberjackRestStop_Text_ThereIsNoMonster, MSGBOX_DEFAULT
	goto WindmistCity_LumberjackRestStop_EventScript_FaceOriginalDirection
	end

WindmistCity_LumberjackRestStop_EventScript_CaughtRimewoodAbomasnowHiker:
	goto_if_set FLAG_RECEIVED_WINDMIST_CITY_ICY_ROCK, WindmistCity_LumberjackRestStop_EventScript_ExplainIcyRockHiker
	msgbox WindmistCity_LumberjackRestStop_Text_IShouldApologize, MSGBOX_DEFAULT
	giveitem ITEM_ICY_ROCK
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WINDMIST_CITY_ICY_ROCK
	goto WindmistCity_LumberjackRestStop_EventScript_ExplainIcyRockHiker
	end

WindmistCity_LumberjackRestStop_EventScript_ExplainIcyRockHiker:
	msgbox WindmistCity_LumberjackRestStop_Text_ExplainIcyRock, MSGBOX_DEFAULT
	goto WindmistCity_LumberjackRestStop_EventScript_FaceOriginalDirection
	end

WindmistCity_LumberjackRestStop_EventScript_DefeatedRimewoodAbomasnowHiker:
	msgbox WindmistCity_LumberjackRestStop_Text_YouSayYouSawItToo, MSGBOX_DEFAULT
	goto WindmistCity_LumberjackRestStop_EventScript_FaceOriginalDirection
	end

WindmistCity_LumberjackRestStop_Text_ThereIsNoMonster:
	.string "There is no {COLOR GREEN}monster{COLOR BLUE}…\n"
	.string "You guys are just hearing things!$"

WindmistCity_LumberjackRestStop_Text_IShouldApologize:
	.string "There is no {COLOR GREEN}monster{COLOR BLUE}…\n"
	.string "You guys are just hearing things…\p"
	.string "…\p"
	.string "Wait, you say you captured it?\n"
	.string "It's an Abomasnow…?\p"
	.string "…That explains a lot.\n"
	.string "I guess I should apologize.\p"
	.string "Take this, I'm sure you will use it.$"

WindmistCity_LumberjackRestStop_Text_ExplainIcyRock:
	.string "That Icy Rock broke my axe!\p"
	.string "It was embedded deep in a tree I\n"
	.string "was chopping down.\p"
	.string "I don't understand how it even\n"
	.string "got there…$"

WindmistCity_LumberjackRestStop_Text_YouSayYouSawItToo:
	.string "You say you saw the {COLOR GREEN}monster{COLOR BLUE}, too?\n"
	.string "Pff, I don't believe you at all!$"

WindmistCity_LumberjackRestStop_EventScript_Explorer::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WINDMIST_CITY_ICY_ROCK, WindmistCity_LumberjackRestStop_EventScript_ExplainIcyRockExplorer
	goto_if_set FLAG_CAUGHT_RIMEWOOD_FOREST_ABOMASNOW, WindmistCity_LumberjackRestStop_EventScript_CaughtRimewoodAbomasnowExplorer
	msgbox WindmistCity_LumberjackRestStop_Text_IHeardTheMonster, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_RIMEWOOD_FOREST_ABOMASNOW, WindmistCity_LumberjackRestStop_EventScript_DefeatedRimewoodAbomasnowExplorer
	goto WindmistCity_LumberjackRestStop_EventScript_FaceOriginalDirection
	end

WindmistCity_LumberjackRestStop_EventScript_ExplainIcyRockExplorer:
	msgbox WindmistCity_LumberjackRestStop_Text_GuessIcyRockUsage, MSGBOX_DEFAULT
	goto WindmistCity_LumberjackRestStop_EventScript_FaceOriginalDirection
	end

WindmistCity_LumberjackRestStop_EventScript_CaughtRimewoodAbomasnowExplorer:
	msgbox WindmistCity_LumberjackRestStop_Text_WaitYouCaughtIt, MSGBOX_DEFAULT
	goto WindmistCity_LumberjackRestStop_EventScript_FaceOriginalDirection
	end

WindmistCity_LumberjackRestStop_EventScript_DefeatedRimewoodAbomasnowExplorer:
	msgbox WindmistCity_LumberjackRestStop_Text_YouFoughtIt, MSGBOX_DEFAULT
	goto WindmistCity_LumberjackRestStop_EventScript_FaceOriginalDirection
	end

WindmistCity_LumberjackRestStop_Text_GuessIcyRockUsage:
	.string "If I had to guess, I would say that\n"
	.string "Icy Rock affects the weather!\p"
	.string "I know it's superstitious, but when\n"
	.string "my buddy here brought it back…\p"
	.string "Well, it seemed like the blizzards\n"
	.string "lasted a lot longer than usual!$"

WindmistCity_LumberjackRestStop_Text_WaitYouCaughtIt:
	.string "You say you caught the {COLOR GREEN}monster{COLOR RED}?\n"
	.string "No way! I knew it was real!\p"
	.string "Here, tell my friend!\n"
	.string "He's gonna have to eat his words!$"

WindmistCity_LumberjackRestStop_Text_IHeardTheMonster:
	.string "I heard the {COLOR GREEN}monster{COLOR RED}!\n"
	.string "It lives in Rimewood Forest.$"

WindmistCity_LumberjackRestStop_Text_YouFoughtIt:
	.string "You say you saw the {COLOR GREEN}monster{COLOR RED} too?\n"
	.string "In the Rimewood Forest, right?\p"
	.string "…You fought it?\p"
	.string "Hmm… I have a feeling it will be\n"
	.string "back sometime soon…$"
