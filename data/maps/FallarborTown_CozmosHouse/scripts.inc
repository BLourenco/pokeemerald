FallarborTown_CozmosHouse_MapScripts:: @ 8200F12
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_CozmosHouse_OnTransition
	.byte 0

FallarborTown_CozmosHouse_OnTransition::
	call Common_EventScript_SetupRivalGfxId
	end

FallarborTown_CozmosHouse_EventScript_ProfCozmo:: @ 8200F13
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM69, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite:: @ 8200F38
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	compare VAR_RESULT, NO
	goto_if_eq FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM69_ROCK_POLISH
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM69
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite:: @ 8200F8B
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite:: @ 8200F9C
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite:: @ 8200FA5
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite:: @ 8200FB2
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmosWife:: @ 8200FBC
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM69, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_set FLAG_SAVED_PROF_COZMO, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad:: @ 8200FDA
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy:: @ 8200FE4
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_Rival::
	lock
	faceplayer
	msgbox FallarborTown_CozmosHouse_Text_Rival, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow: @ 8200FEE
	.string "Prof. Cozmo: Oh…\n"
	.string "I never should have let myself be\l"
	.string "conned into telling Team Magma where\l"
	.string "you can find Meteorites…\p"
	.string "That Meteorite from Meteor Falls…\n"
	.string "It's never going to be mine now…$"

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt: @ 82010A2
	.string "Oh!\n"
	.string "Hah?\p"
	.string "That item…\p"
	.string "Could it be?\p"
	.string "Is it the Meteorite that Team Magma\n"
	.string "took from Meteor Falls?\p"
	.string "Please, may I have it?\p"
	.string "I'm not asking for it for free.\n"
	.string "How about in exchange for this TM?$"

FallarborTown_CozmosHouse_Text_PleaseUseThisTM: @ 8201159
	.string "Prof. Cozmo: This TM, take it\n"
	.string "as a token of my gratitude.\l"
	.string "Please use it!$"

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch: @ 82011A5
	.string "Prof. Cozmo: Oh, I can't believe it.\n"
	.string "This is really, really great!\p"
	.string "This is really going to help my research!$"

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment: @ 8201212
	.string "Prof. Cozmo: Oh, but…\n"
	.string "I'm crushed with disappointment…$"

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite: @ 8201249
	.string "Prof. Cozmo: Please, may I have that\n"
	.string "Meteorite?\p"
	.string "I'm not asking for it for free.\n"
	.string "How about in exchange for this TM?$"

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls: @ 82012BC
	.string "Are you here to see Prof. Cozmo?\p"
	.string "Sorry, but you just missed him.\n"
	.string "Someone came by asking to join him on\l"
	.string "his next outing to Meteor Falls.\p"
	.string "They'll be out there for a while if\n"
	.string "you want to go find them.$"

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo: @ 8201310
	.string "Poor Prof. Cozmo…\n"
	.string "He's so depressed… I feel sorry for him.$"

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy: @ 820134B
	.string "Look at Prof. Cozmo…\n"
	.string "He's so happy! I think it's cute.$"

FallarborTown_CozmosHouse_Text_Rival:
	.string "{RIVAL}: Hey, {PLAYER}.\p"
	.string "No sign of Team Magma or Team Aqua\n"
	.string "coming back to cause trouble.\p"
	.string "I finally got a chance to talk to\n"
	.string "Prof. Cozmo about the Pokémon living in\l"
	.string "Meteor Falls, but he seems distracted.\p"
	.string "Prof. Cozmo is really upset about losing\n"
	.string "the Meteorite…\p"
	.string "What does Team Magma plan to do with it\n"
	.string "at Mt. Chimney?$"

