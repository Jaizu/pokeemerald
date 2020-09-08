.equ LOCALID_MUSEUM_CLERK, 3

AerousCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AerousCity_OnTransition
	.byte 0

AerousCity_OnTransition::
	setflag FLAG_VISITED_AEROUS_CITY
	end

AerousCity_EventScript_CitySign::
	msgbox AerousCity_Text_CitySign, MSGBOX_SIGN
	end

AerousCity_Text_CitySign:
	.string "Aerous City\n"
	.string "The Cultural Capital City.$"

AerousCity_EventScript_MuseumSign::
	msgbox AerousCity_Text_MuseumSign, MSGBOX_SIGN
	end

AerousCity_Text_MuseumSign:
	.string "Aerous City Museum$"

AerousCity_EventScript_ArtClubSign::
	msgbox AerousCity_Text_ArtClubSign, MSGBOX_SIGN
	end

AerousCity_Text_ArtClubSign:
	.string "Aerous Art Club\n"
    .string "“Check out the upstairs café!”$"

AerousCity_EventScript_PortSign::
	msgbox AerousCity_Text_PortSign, MSGBOX_SIGN
	end

AerousCity_Text_PortSign:
	.string "{DOWN_ARROW} Aerous City port$"

AerousCity_EventScript_BikeShopSign::
	msgbox AerousCity_Text_BikeShopSign, MSGBOX_SIGN
	end

AerousCity_Text_BikeShopSign:
	.string "Bicycle shop$"

AerousCity_EventScript_NameRaterSign::
	msgbox AerousCity_Text_NameRaterSign, MSGBOX_SIGN
	end

AerousCity_Text_NameRaterSign:
	.string "The Name Rater's house$"

AerousCity_EventScript_MuseumClerk::
	lock
	faceplayer
	msgbox AerousCity_Text_TheAerousMuseumIsHavingAnExhibit, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MUSEUM_CLERK, AerousCity_Text_MuseumClerkDefeat
	msgbox AerousCity_Text_IGottaTellTheBoss, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MUSEUM_CLERK, Common_Movement_WalkUp
	waitmovement 0
	playse SE_KAIDAN
	waitse
	removeobject LOCALID_MUSEUM_CLERK
	release
	end

AerousCity_Text_TheAerousMuseumIsHavingAnExhibit:
	.string "{COLOR DARK_GREY}???: {COLOR BLUE}The Aerous Museum is… er…\p"
	.string "Having an exhibit!\n"
	.string "Yeah…\p"
	.string "…You don't believe me?\n"
	.string "Argh, you're a belligerent child!{PLAY_BGM}{MUS_MGM0}\p"
	.string "I'll make you pay!$"

AerousCity_Text_MuseumClerkDefeat:
	.string "Oh man…\n"
	.string "This isn't good!$"

AerousCity_Text_IGottaTellTheBoss:
	.string "{COLOR DARK_GREY}???: {COLOR BLUE}This is bad…\n"
	.string "I gotta tell the boss!$"

AerousCity_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_AEROUS_CITY_REVIVAL_HERB, AerousCity_EventScript_ReceivedRevivalHerb
	msgbox AerousCity_Text_IThoughtThisHerbWouldBePerfect, MSGBOX_DEFAULT
	giveitem ITEM_REVIVAL_HERB
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_AEROUS_CITY_REVIVAL_HERB
	goto AerousCity_EventScript_ReceivedRevivalHerb
	end

AerousCity_EventScript_ReceivedRevivalHerb:
	msgbox AerousCity_Text_IdBeCautiousAboutFeedingThat, MSGBOX_DEFAULT
	release
	end

AerousCity_Text_IThoughtThisHerbWouldBePerfect:
	.string "When I found this herb, I thought\n"
	.string "it would be perfect for my stew.\p"
	.string "Turns out it tastes horribly\n"
	.string "bitter. Not very nice indeed!\p"
	.string "You can take it, if you'd like.$"

AerousCity_Text_IdBeCautiousAboutFeedingThat:
	.string "I'd be cautious about feeding that\n"
	.string "herb to a Pokémon.\p"
	.string "They might resent you feeding them\n"
	.string "something so bitter!$"

AerousCity_EventScript_Man::
	msgbox AerousCity_Text_IFoughtThatOpposGuy, MSGBOX_NPC
	end

AerousCity_Text_IFoughtThatOpposGuy:
	.string "I fought that Oppos guy, but my\n"
	.string "moves didn't work normally!$"

AerousCity_EventScript_Lass::
	msgbox AerousCity_Text_DidYouHearTheRumors, MSGBOX_NPC
	end

AerousCity_Text_DidYouHearTheRumors:
	.string "Did you hear the rumors about\n"
	.string "Telmurk City?\p"
	.string "Apparently, a gang has taken it\n"
	.string "over!\p"
	.string "That's so scary.\n"
	.string "I'm glad I live in a safe city.$"

AerousCity_EventScript_Sailor1::
	msgbox AerousCity_Text_ICanSeeSabuloFromHere, MSGBOX_NPC
	end

AerousCity_Text_ICanSeeSabuloFromHere:
	.string "Hey, I can see Sabulo Island from\n"
	.string "here!\p"
	.string "You can get there by Surfing east\n"
	.string "from here, or taking the S.S. Wake.$"

AerousCity_EventScript_Sailor2::
	lock
	faceplayer
	msgbox AerousCity_Text_DoYouSeeThatLighthouse, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_ne AerousCity_EventScript_ShowLighthouse
	msgbox AerousCity_Text_ItLooksAbandoned, MSGBOX_DEFAULT
	release
	end

AerousCity_EventScript_ShowLighthouse:
	msgbox AerousCity_Text_LookCloselyOverThere, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_0x8000, VAR_0x8001
	compare VAR_0x8001, 14
	call_if_eq AerousCity_EventScript_PlayerFaceEast
	fadescreen FADE_TO_BLACK
	// TODO: Implement
	// setvar VAR_0x8004, 67
	// setvar VAR_0x8005, 8
	// special TeleportCamera
	fadescreen FADE_FROM_BLACK
	waitbuttonpress
	fadescreen FADE_TO_BLACK
	// TODO: Implement
	// special ReturnCameraToPlayer
	fadescreen FADE_FROM_BLACK
	compare VAR_0x8001, 14
	call_if_eq AerousCity_EventScript_PlayerFaceNorth
	return

AerousCity_EventScript_PlayerFaceEast:
	delay 10
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 10
	return

AerousCity_EventScript_PlayerFaceNorth:
	delay 10
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 10
	return

AerousCity_Text_DoYouSeeThatLighthouse:
	.string "Do you see that lighthouse?$"

AerousCity_Text_LookCloselyOverThere:
	.string "Look closely, over there!$"

AerousCity_Text_ItLooksAbandoned:
	.string "It looks abandoned, doesn't it?\p"
	.string "I've never figured out how to get\n"
	.string "to it, either…$"

AerousCity_EventScript_Herschel::
	lock
	faceplayer
	msgbox AerousCity_Text_AreYouReady, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq AerousCity_EventScript_LeaveForArchanTunnel
	msgbox AerousCity_Text_HmphComeBack, MSGBOX_DEFAULT
	release
	end

AerousCity_EventScript_LeaveForArchanTunnel:
	msgbox AerousCity_Text_LetsGo, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_TANGROWTH_TABLET_ROOM_HERSCHEL
	setflag FLAG_HIDE_AEROUS_CITY_HERSCHEL
	setvar VAR_ARCHAN_TUNNEL_STATE, 4
	warp MAP_ARCHAN_TUNNEL_TANGROWTH_TABLET_ROOM, -1, 6, 5
	waitstate
	release
	end

AerousCity_Text_AreYouReady:
	.string "{COLOR DARK_GREY}Herschel: {COLOR BLUE}Are you ready?$"

AerousCity_Text_HmphComeBack:
	.string "{COLOR DARK_GREY}Herschel: {COLOR BLUE}Hmph…\n"
	.string "Come back when you are ready.$"

AerousCity_Text_LetsGo:
	.string "{COLOR DARK_GREY}Herschel: {COLOR BLUE}Let's go!$"
