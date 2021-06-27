.set LOCALID_GRUNT_1, 10
.set LOCALID_GRUNT_2, 11
.set LOCALID_GRUNT_3, 12
.set LOCALID_GRUNT_4, 13
.set LOCALID_MAXIE, 14
.set LOCALID_SCOTT, 16
.set LOCALID_RIVAL, 18

MossdeepCity_MapScripts:: @ 81E4A96
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_OnTransition: @ 81E4A9C
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

MossdeepCity_EventScript_PokefanF:: @ 81E4AB2
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM08, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone:: @ 81E4AC7
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor:: @ 81E4AD1
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM08, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone:: @ 81E4AE6
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy:: @ 81E4AF0
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM:: @ 81E4AF9
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl:: @ 81E4B02
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman:: @ 81E4B0B
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock:: @ 81E4B14
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign:: @ 81E4B1D
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign:: @ 81E4B26
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign:: @ 81E4B2F
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep:: @ 81E4B38
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_Rival:: @ 81E2DDE
	lock
	faceplayer
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq MossdeepCity_EventScript_May
	compare VAR_RESULT, FEMALE
	goto_if_eq MossdeepCity_EventScript_Brendan
	end

MossdeepCity_EventScript_May:: @ 81E2DF8
	playbgm MUS_ENCOUNTER_MAY, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_MOSSDEEP, MossdeepCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_MOSSDEEP, MossdeepCity_EventScript_MayAskToBattle
	compare VAR_RESULT, NO
	goto_if_eq MossdeepCity_EventScript_DeclineMayBattle
	msgbox MossdeepCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, MossdeepCity_EventScript_BattleMayTreecko
	case 1, MossdeepCity_EventScript_BattleMayTorchic
	case 2, MossdeepCity_EventScript_BattleMayMudkip
	end

MossdeepCity_EventScript_MayAskToBattleAgain:: @ 81E2E48
	msgbox MossdeepCity_Text_MayBattleMe, MSGBOX_YESNO
	return

MossdeepCity_EventScript_MayAskToBattle:: @ 81E2E51
	msgbox MossdeepCity_Text_MayLookHowFarWeveCome, MSGBOX_YESNO
	return

MossdeepCity_EventScript_DeclineMayBattle:: @ 81E2E5A
	setflag FLAG_DECLINED_RIVAL_BATTLE_MOSSDEEP
	msgbox MossdeepCity_Text_MayBattleDeclined, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

MossdeepCity_EventScript_Brendan:: @ 81E2E6B
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_MOSSDEEP, MossdeepCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_MOSSDEEP, MossdeepCity_EventScript_BrendanAskToBattle
	compare VAR_RESULT, NO
	goto_if_eq MossdeepCity_EventScript_DeclineBrendanBattle
	msgbox MossdeepCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, MossdeepCity_EventScript_BattleBrendanTreecko
	case 1, MossdeepCity_EventScript_BattleBrendanTorchic
	case 2, MossdeepCity_EventScript_BattleBrendanMudkip
	end

MossdeepCity_EventScript_BrendanAskToBattleAgain:: @ 81E2EBB
	msgbox MossdeepCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

MossdeepCity_EventScript_BrendanAskToBattle:: @ 81E2EC4
	msgbox MossdeepCity_Text_BrendanLookHowFarWeveCome, MSGBOX_YESNO
	return

MossdeepCity_EventScript_DeclineBrendanBattle:: @ 81E2ECD
	setflag FLAG_DECLINED_RIVAL_BATTLE_MOSSDEEP
	msgbox MossdeepCity_Text_BrendanBattleDeclined, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

MossdeepCity_EventScript_BattleMayTreecko:: @ 81E2EDE
	trainerbattle_no_intro TRAINER_MAY_MOSSDEEP_TREECKO, MossdeepCity_Text_MayDefeat
	goto MossdeepCity_EventScript_DefeatedMay
	end

MossdeepCity_EventScript_BattleMayTorchic:: @ 81E2EEE
	trainerbattle_no_intro TRAINER_MAY_MOSSDEEP_TORCHIC, MossdeepCity_Text_MayDefeat
	goto MossdeepCity_EventScript_DefeatedMay
	end

MossdeepCity_EventScript_BattleMayMudkip:: @ 81E2EFE
	trainerbattle_no_intro TRAINER_MAY_MOSSDEEP_MUDKIP, MossdeepCity_Text_MayDefeat
	goto MossdeepCity_EventScript_DefeatedMay
	end

MossdeepCity_EventScript_BattleBrendanTreecko:: @ 81E2F0E
	trainerbattle_no_intro TRAINER_BRENDAN_MOSSDEEP_TREECKO, MossdeepCity_Text_BrendanDefeat
	goto MossdeepCity_EventScript_DefeatedBrendan
	end

MossdeepCity_EventScript_BattleBrendanTorchic:: @ 81E2F1E
	trainerbattle_no_intro TRAINER_BRENDAN_MOSSDEEP_TORCHIC, MossdeepCity_Text_BrendanDefeat
	goto MossdeepCity_EventScript_DefeatedBrendan
	end

MossdeepCity_EventScript_BattleBrendanMudkip:: @ 81E2F2E
	trainerbattle_no_intro TRAINER_BRENDAN_MOSSDEEP_MUDKIP, MossdeepCity_Text_BrendanDefeat
	goto MossdeepCity_EventScript_DefeatedBrendan
	end

MossdeepCity_EventScript_DefeatedMay:: @ 81E2F3E
	msgbox MossdeepCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	goto MossdeepCity_EventScript_RivalFlyAway
	end

MossdeepCity_EventScript_DefeatedBrendan:: @ 81E2FAA
	msgbox MossdeepCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	goto MossdeepCity_EventScript_RivalFlyAway
	end

MossdeepCity_EventScript_RivalFlyAway:: @ 81E3006
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	compare VAR_FACING, DIR_EAST
	call_if_eq MossdeepCity_EventScript_RivalSetFieldEffectArgEast
	compare VAR_FACING, DIR_NORTH
	call_if_eq MossdeepCity_EventScript_RivalSetFieldEffectArgNorth
	compare VAR_FACING, DIR_WEST
	call_if_eq MossdeepCity_EventScript_RivalSetFieldEffectArgWest
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_MOSSDEEP
	release
	end

MossdeepCity_EventScript_RivalSetFieldEffectArgEast::
	setfieldeffectargument 1, 1 @ # tiles away from center on x axis, magnitude only
	setfieldeffectargument 2, 0 @ is x negative? 0=False, 1=True
	setfieldeffectargument 3, 0 @ # tiles away from center on y axis, magnitude only
	setfieldeffectargument 4, 0 @ is y negative? 0=False, 1=True
	return

MossdeepCity_EventScript_RivalSetFieldEffectArgNorth::
	setfieldeffectargument 1, 0 @ # tiles away from center on x axis, magnitude only
	setfieldeffectargument 2, 0 @ is x negative? 0=False, 1=True
	setfieldeffectargument 3, 1 @ # tiles away from center on y axis, magnitude only
	setfieldeffectargument 4, 1 @ is y negative? 0=False, 1=True
	return

MossdeepCity_EventScript_RivalSetFieldEffectArgWest::
	setfieldeffectargument 1, 1 @ # tiles away from center on x axis, magnitude only
	setfieldeffectargument 2, 1 @ is x negative? 0=False, 1=True
	setfieldeffectargument 3, 0 @ # tiles away from center on y axis, magnitude only
	setfieldeffectargument 4, 0 @ is y negative? 0=False, 1=True
	return


MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter:: @ 81E4B41
	lockall
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter: @ 81E4BAD
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter: @ 81E4BB7
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter: @ 81E4BBC
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter: @ 81E4BCA
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter: @ 81E4BDD
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter: @ 81E4BEF
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter: @ 81E4C00
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man:: @ 81E4C10
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy:: @ 81E4C26
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock:: @ 81E4C68
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock:: @ 81E4C72
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt:: @ 81E4C7C
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott:: @ 81E4C85
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq MossdeepCity_EventScript_ScottExitNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth:: @ 81E4CB0
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast:: @ 81E4CC2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit: @ 81E4CD4
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

MossdeepCity_Movement_ScottExitNorth: @ 81E4CD8
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast: @ 81E4CE2
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe: @ 81E4CED
	.string "I got this from Steven, but I don't\n"
	.string "know what it's good for.\p"
	.string "I think it's called King's Rock.\n"
	.string "Do you want it?$"

MossdeepCity_Text_YouCanKeepIt: @ 81E4D5B
	.string "Why would you want it?\n"
	.string "You're weird.\p"
	.string "You can keep it, but keep it a secret\n"
	.string "from Steven.$"

MossdeepCity_Text_StevensHouseOverThere: @ 81E4DB3
	.string "Steven's house is right over there!$"

MossdeepCity_Text_WhatToDoWithWeirdRock: @ 81E4DD7
	.string "Yeah, you think so, too! What are you\n"
	.string "supposed to do with some weird rock?$"

MossdeepCity_Text_WailmerWatching: @ 81E4E22
	.string "Around Mossdeep, you can see wild\n"
	.string "Wailmer.\p"
	.string "It's called, uh…\n"
	.string "What was it now…\p"
	.string "Wai, Wai, Wai…\p"
	.string "Wailmer watching!$"

MossdeepCity_Text_SpaceCenterReceivedLetter: @ 81E4E90
	.string "The island's Space Center has been\n"
	.string "launching huge rockets.\p"
	.string "There's been some kind of an uproar\n"
	.string "over a letter they received recently.$"

MossdeepCity_Text_SpaceCenterLaunchingRockets: @ 81E4F15
	.string "The island's Space Center has been\n"
	.string "launching huge rockets.$"

MossdeepCity_Text_MossdeepTargetedByMagma: @ 81E4F50
	.string "I heard from a Sailor buddy that\n"
	.string "Team Aqua set up shop in Lilycove.\p"
	.string "I also heard that someone came along\n"
	.string "and wiped the floor with them!\p"
	.string "But Mossdeep here's been targeted\n"
	.string "by that Team Magma.\p"
	.string "If you want to know what they're up to,\n"
	.string "go visit the Space Center.$"

MossdeepCity_Text_FeelReliefOnLand: @ 81E5051
	.string "I'm a Sailor, so the sea's obviously\n"
	.string "more important to me.\p"
	.string "But you know? When I get back on land\n"
	.string "after a long voyage, I do feel relief!$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers: @ 81E50D9
	.string "Wouldn't it be nice?\p"
	.string "If the whole world was covered in\n"
	.string "plants and flowers like this island?$"

MossdeepCity_Text_LifeNeedsSeaToLive: @ 81E5135
	.string "All life needs the sea to live, even\n"
	.string "though it makes its home on the land.\p"
	.string "Life, having run its course, becomes\n"
	.string "soil and returns to the land.\p"
	.string "And the sea is always connected to\n"
	.string "the land.\p"
	.string "Yes, like the very shoreline here.$"

MossdeepCity_Text_SurfExhilarating: @ 81E5213
	.string "A voyage on a ship is fine.\p"
	.string "But crossing the sea with Pokémon\n"
	.string "using Surf…\p"
	.string "Now that's an exhilarating trip!\n"
	.string "Wouldn't you agree, youngster?$"

MossdeepCity_Text_SpecialSpaceCenterRock: @ 81E529D
	.string "This rock has a special meaning to\n"
	.string "the people at the Space Center.\p"
	.string "They put it here as their wish for\n"
	.string "their rockets to fly safely.\p"
	.string "When you make a wish, what do you use?\n"
	.string "Do you wish upon a star?\p"
	.string "I use a wish tag to make it happen.\n"
	.string "That's what I do.$"

MossdeepCity_Text_ItsAWhiteRock: @ 81E5396
	.string "It's a white rock.$"

MossdeepCity_Text_GymSign: @ 81E53A9
	.string "Mossdeep City Pokémon Gym\n"
	.string "Leaders: Liza & Tate\p"
	.string "“The mystic combination!”$"

MossdeepCity_Text_CitySign: @ 81E53F2
	.string "Mossdeep City\n"
	.string "“Our slogan: Cherish Pokémon!”$"

MossdeepCity_Text_SpaceCenterSign: @ 81E541F
	.string "Mossdeep Space Center\n"
	.string "“The closest place to space.”$"

MossdeepCity_Text_ScottSomethingWrongWithTown: @ 81E5453
	.string "Scott: {PLAYER}{KUN}, feeling good?\n"
	.string "I'm doing great!\p"
	.string "I'd heard Mossdeep's Gym Leader is\n"
	.string "pretty strong, so I decided to come\l"
	.string "take a look-see for myself.\p"
	.string "But there's something wrong about\n"
	.string "this town.\p"
	.string "People are going on about a warning\n"
	.string "letter and the Space Center…\p"
	.string "I don't think it concerns me in any\n"
	.string "way, though.$"

MossdeepCity_Text_SootopolisNewGymLeader: @ 81E5581
	.string "Ahh… It feels great letting the waves\n"
	.string "wash over my feet…\p"
	.string "Speaking of the waves, you know that\n"
	.string "island city Sootopolis?\p"
	.string "I think the Gym there had a new\n"
	.string "Leader come in.\p"
	.string "People tell me the new Leader once\n"
	.string "mentored Wallace.$"

MossdeepCity_Text_MayLookHowFarWeveCome: @ 81E3061
	.string "{RIVAL}: Hey, {PLAYER}!\p"
	.string "I knew you'd show up here eventually.\n"
	.string "Look how far we've come.\p"
	.string "Did you ever think we'd find ourselves\n"
	.string "all the way out here, so far from home?\p"
	.string "It's been amazing travelling around\n"
	.string "Hoenn, finding and documenting all the\l"
	.string "Pokémon and their habitats.\p"
	.string "I think my father is going to be very\n"
	.string "surprised to see just how much data\l"
	.string "I've recorded once I get home.\p"
	.string "That's the reason I've been waiting\n"
	.string "for you, {PLAYER}.\p"
	.string "I think I'm going to take a break and\n"
	.string "head back home soon.\p"
	.string "But before I do, I'd like to battle you.\n"
	.string "One last time.\p"
	.string "I want to see just how much we've both\n"
	.string "grown since leaving home.\p"
	.string "So, what do you say?\n"
	.string "Are you up for a battle?$"

MossdeepCity_Text_MayBattleDeclined: @ 81E318D
	.string "{RIVAL}: Well, hurry and get ready.\p"
	.string "I don't want to head home before I get\n"
	.string "a chance to battle with you.$"

MossdeepCity_Text_MayBattleMe: @ 81E31F5
	.string "{RIVAL}: Are you ready for one last\n"
	.string "battle before I head home?$"

MossdeepCity_Text_MayWontBeBeaten: @ 81E3234
	.string "{RIVAL}: My Pokémon I raised…\p"
	.string "We're going to show you everything\n"
	.string "we've got! Bring it on!$"

MossdeepCity_Text_MayDefeat: @ 81E3275
	.string "… … … … … … … …\p"
	.string "I remember the battle I had with you,\n"
	.string "{PLAYER}{KUN}, on Route 103.\p"
	.string "That battle helped you become this\n"
	.string "strong, {PLAYER}{KUN}, didn't it?$"

MossdeepCity_Text_MayGoingBackToLittleroot: @ 81E32FB
	.string "{RIVAL}: Thanks, {PLAYER}.\n"
	.string "That was really fun, despite the loss.\p"
	.string "I'm going to head back to\n"
	.string "Littleroot now.\p"
	.string "You should pay your folks a visit from\n"
	.string "time to time, too.\p"
	.string "I'm sure they really miss you.\p"
	.string "Okay, I'm off! Good luck on the rest\n"
	.string "of you're journey!\p"
	.string "You're so close to challenging the\n"
	.string "the League!\p"
	.string "I have no doubt that you'll one day make\n"
	.string "it, and hopefully, become Champion!\p"
	.string "See you around, {PLAYER}!$"

MossdeepCity_Text_BrendanLookHowFarWeveCome: @ 81E3608
	.string "{RIVAL}: Hey, {PLAYER}!\p"
	.string "I knew you'd show up here eventually.\n"
	.string "Look how far we've come.\p"
	.string "Did you ever think we'd find ourselves\n"
	.string "all the way out here, so far from home?\p"
	.string "It's been amazing travelling around\n"
	.string "Hoenn, finding and documenting all the\l"
	.string "Pokémon and their habitats.\p"
	.string "I think my father is going to be very\n"
	.string "surprised to see just how much data\l"
	.string "I've recorded once I get home.\p"
	.string "That's the reason I've been waiting\n"
	.string "for you, {PLAYER}.\p"
	.string "I think I'm going to take a break and\n"
	.string "head back home soon.\p"
	.string "But before I do, I'd like to battle you.\n"
	.string "One last time.\p"
	.string "I want to see just how much we've both\n"
	.string "grown since leaving home.\p"
	.string "So, what do you say?\n"
	.string "Are you up for a battle?$"

MossdeepCity_Text_BrendanBattleDeclined: @ 81E36BF
	.string "{RIVAL}: Well, hurry and get ready.\p"
	.string "I don't want to head home before I get\n"
	.string "a chance to battle with you.$"

MossdeepCity_Text_BrendanBattleMe: @ 81E36FA
	.string "{RIVAL}: Are you ready for one last\n"
	.string "battle before I head home?$"

MossdeepCity_Text_BrendanWontBeBeaten: @ 81E373C
	.string "{RIVAL}: My Pokémon I raised…\p"
	.string "We're going to show you everything\n"
	.string "we've got! Bring it on!$"

MossdeepCity_Text_BrendanDefeat: @ 81E3777
	.string "Humph…\n"
	.string "You've done a lot of raising.\p"
	.string "That stings a bit--I had a head start\n"
	.string "on you as a Trainer…$"

MossdeepCity_Text_BrendanGoingBackToLittleroot: @ 81E37D7
	.string "{RIVAL}: Thanks, {PLAYER}.\n"
	.string "That was really fun, despite the loss.\p"
	.string "I'm going to head back to\n"
	.string "Littleroot now.\p"
	.string "You should pay your folks a visit from\n"
	.string "time to time, too.\p"
	.string "I'm sure they really miss you.\p"
	.string "Okay, I'm off! Good luck on the rest\n"
	.string "of you're journey!\p"
	.string "You're so close to challenging the\n"
	.string "the League!\p"
	.string "I have no doubt that you'll one day make\n"
	.string "it, and hopefully, become Champion!\p"
	.string "See you around, {PLAYER}!$"

