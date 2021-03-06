.set LOCALID_WALLY, 6
.set LOCALID_WALLYS_UNCLE, 7
.set LOCALID_WATTSON, 8
.set LOCALID_SCOTT, 11

MauvilleCity_MapScripts:: @ 81DF385
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition: @ 81DF38B
	setflag FLAG_VISITED_MAUVILLE_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM24_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym:: @ 81DF3A9
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy:: @ 81DF3B3
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac:: @ 81DF3BC
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman:: @ 81DF3C5
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy:: @ 81DF3CE
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign:: @ 81DF3D7
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign:: @ 81DF3E0
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign:: @ 81DF3E9
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign:: @ 81DF3F2
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end
	
MauvilleCity_EventScript_BattleTentSign::
	msgbox MauvilleCity_Text_BattleTentSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM:: @ 81DF3FB
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained:: @ 81DF413
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle:: @ 81DF41D
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally:: @ 81DF43D
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally:: @ 81DF452
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt:: @ 81DF4AD
	compare VAR_RESULT, YES
	call_if_eq MauvilleCity_EventScript_BattleWally
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_EventScript_DeclineWallyBattle
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth:: @ 81DF4E0
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_WATTSON, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExit
	waitmovement 0

	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_WATTSON, Common_Movement_FaceDown
	waitmovement 0

	msgbox MauvilleCity_Text_WattsonYouHoweverAreReady, MSGBOX_DEFAULT
	closemessage

	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 5
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim		
	applymovement LOCALID_WATTSON, MauvilleCity_Movement_WattsonEnterGym
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	removeobject LOCALID_WATTSON

	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast:: @ 81DF53D
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_WATTSON, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExit
	waitmovement 0

	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	applymovement LOCALID_WATTSON, Common_Movement_FaceLeft
	waitmovement 0

	msgbox MauvilleCity_Text_WattsonYouHoweverAreReady, MSGBOX_DEFAULT
	closemessage

	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 5
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim		
	applymovement LOCALID_WATTSON, MauvilleCity_Movement_WattsonEnterGym
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	removeobject LOCALID_WATTSON


	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally:: @ 81DF593
	removeobject LOCALID_WALLY
	removeobject LOCALID_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	compare VAR_FACING, DIR_NORTH
	call_if_eq MauvilleCity_EventScript_ScottApproachPlayerNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	compare VAR_FACING, DIR_NORTH
	call_if_eq MauvilleCity_EventScript_ScottExitNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_SCOTT
	setflag FLAG_HIDE_MAUVILLE_BATTLE_TENT_SCOTT
	clearflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth:: @ 81DF5F3
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast:: @ 81DF601
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth:: @ 81DF616
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast:: @ 81DF628
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally:: @ 81DF63A
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT	
	closemessage
	delay 15
	msgbox MauvilleCity_Text_WattsonYourUnclesRight, MSGBOX_DEFAULT
	closemessage
	
	applymovement LOCALID_WALLY, Common_Movement_FaceUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_Delay48
	waitmovement 0

	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 5
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	setobjectxyperm LOCALID_WATTSON, 8, 5
	addobject LOCALID_WATTSON

	compare VAR_FACING, DIR_NORTH
	call_if_eq MauvilleCity_EventScript_WallyMakeWayForWattsonNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MauvilleCity_EventScript_WallyMakeWayForWattsonEast

	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim

	msgbox MauvilleCity_Text_WattsonWatchingFromInside, MSGBOX_DEFAULT
	closemessage

	compare VAR_FACING, DIR_NORTH
	call_if_eq MauvilleCity_EventScript_UncleApproachesPlayerNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MauvilleCity_EventScript_UncleApproachesPlayerEast

	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage

	compare VAR_FACING, DIR_NORTH
	call_if_eq MauvilleCity_EventScript_PlayerAndUncleFaceWallyNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MauvilleCity_EventScript_PlayerAndUncleFaceWallyEast

	msgbox MauvilleCity_Text_WattsonDontGiveUp, MSGBOX_DEFAULT
	closemessage
	msgbox MauvilleCity_Text_WallyThankYouWattson, MSGBOX_DEFAULT
	closemessage

	compare VAR_FACING, DIR_NORTH
	call_if_eq MauvilleCity_EventScript_UncleApproachWallyNorth
	compare VAR_FACING, DIR_EAST
	call_if_eq MauvilleCity_EventScript_UncleApproachWallyEast

	msgbox MauvilleCity_Text_UncleLetsGoHome, MSGBOX_DEFAULT
	closemessage

	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	return

MauvilleCity_EventScript_DeclineWallyBattle:: @ 81DF683
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain:: @ 81DF690
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_WallyMakeWayForWattsonEast::
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyMakeWayForWattsonEast
	waitmovement 0
	applymovement LOCALID_WATTSON, Common_Movement_WalkDown
	waitmovement 0
	return

MauvilleCity_EventScript_WallyMakeWayForWattsonNorth::
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyMakeWayForWattsonNorth
	waitmovement 0
	applymovement LOCALID_WATTSON, Common_Movement_WalkDown
	waitmovement 0
	applymovement LOCALID_WATTSON, Common_Movement_FaceLeft
	waitmovement 0
	return

MauvilleCity_EventScript_UncleApproachesPlayerEast::
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_UncleApproachesPlayerEast
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	return

MauvilleCity_EventScript_UncleApproachesPlayerNorth::
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_UncleApproachesPlayerNorth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	return

MauvilleCity_EventScript_PlayerAndUncleFaceWallyEast::
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	return

MauvilleCity_EventScript_PlayerAndUncleFaceWallyNorth::
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	return

MauvilleCity_EventScript_UncleApproachWallyEast::
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_UncleApproachWallyEast
	waitmovement 0
	return

MauvilleCity_EventScript_UncleApproachWallyNorth::
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_UncleApproachWallyNorth
	waitmovement 0
	return


MauvilleCity_Movement_UncleApproachesPlayerEast:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_UncleApproachesPlayerNorth:
	walk_down
	face_left
	step_end

MauvilleCity_Movement_WallyMakeWayForWattsonEast:
	walk_down
	face_up
	step_end

MauvilleCity_Movement_WallyMakeWayForWattsonNorth:
	walk_left
	face_right
	step_end

MauvilleCity_Movement_UncleApproachWallyNorth:
	walk_down
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_UncleApproachWallyEast:
	face_right
	step_end

MauvilleCity_Movement_WallyExitNorth:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast:
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WattsonEnterGym:
	walk_up
	set_invisible
	step_end

MauvilleCity_Movement_WallyExitNorth1: @ 81DF6A8
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1: @ 81DF6AE
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2: @ 81DF6B4
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2: @ 81DF6C0
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2: @ 81DF6CC
	delay_16
	delay_8
	walk_in_place_fastest_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2: @ 81DF6D0
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth: @ 81DF6D5
	delay_16
	walk_in_place_fastest_right
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast: @ 81DF6D8
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1: @ 81DF6DC
	delay_16
	walk_in_place_fastest_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1: @ 81DF6DF
	delay_16
	walk_in_place_fastest_left
	step_end

MauvilleCity_Movement_WallysUncleExit:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth: @ 81DF6EE
	delay_16
	delay_8
	delay_4
	walk_in_place_fastest_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth: @ 81DF6F3
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast: @ 81DF6F7
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2: @ 81DF6FA
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2: @ 81DF703
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth: @ 81DF70D
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast: @ 81DF719
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_ScottExitNorth: @ 81DF725
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MauvilleCity_Movement_ScottExitEast: @ 81DF72F
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MauvilleCity_EventScript_Wattson:: @ 81DF73A
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM24_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	compare VAR_NEW_MAUVILLE_STATE, 3
	goto_if_eq MauvilleCity_EventScript_CompletedNewMauville
	compare VAR_NEW_MAUVILLE_STATE, 2
	goto_if_eq MauvilleCity_EventScript_PushedRedButton
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville:: @ 81DF77A
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville:: @ 81DF784
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM24
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM24_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_PushedRedButton::
	msgbox MauvilleCity_Text_WattsonPressedRedButton, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt:: @ 81DF7B0
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall:: @ 81DF7BA
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy: @ 81DF7DC
	.string "Uncle: It's because of Pokémon that\n"
	.string "this boy's got more pep, I suppose…\l"
	.string "But he's become a bit too peppy…$"

MauvilleCity_Text_WallyWantToChallengeGym: @ 81DF845
	.string "Wally: Aww, Uncle, please?\p"
	.string "I want to challenge this Gym and see\n"
	.string "how much better I've become.\p"
	.string "Please? May I, please?$"

MauvilleCity_Text_UncleYourePushingIt: @ 81DF8B9
	.string "Uncle: Now hold on, Wally.\p"
	.string "Since you started living with Pokémon,\n"
	.string "you have grown quite a lot stronger.\p"
	.string "But don't you think you're pushing it\n"
	.string "to suddenly challenge a Gym?$"

MauvilleCity_Text_WallyWeCanBeatAnyone: @ 81DF963
	.string "Wally: I'm not pushing it.\p"
	.string "If I combine forces with Ralts,\n"
	.string "we can beat anyone!$"

MauvilleCity_Text_WallyWillYouBattleMe: @ 81DF9B2
	.string "Wally: Oh! Hi, {PLAYER}!\p"
	.string "I've gotten a lot stronger since\n"
	.string "we met.\p"
	.string "I want you and my Uncle to\n"
	.string "understand that.\p"
	.string "{PLAYER}, please, will you have\n"
	.string "a battle with me?$"

MauvilleCity_Text_WallyMyUncleWontKnowImStrong: @ 81DFA4A
	.string "Wally: Oh… If you won't battle me,\n"
	.string "{PLAYER}, my Uncle won't know that I've\l"
	.string "become really strong.$"

MauvilleCity_Text_UncleCanYouBattleWally: @ 81DFAA5
	.string "Uncle: {PLAYER}{KUN}, was it?\n"
	.string "On Wally's behalf, can I ask you to\l"
	.string "battle with him just this once?\p"
	.string "I don't think he's going to listen to\n"
	.string "any reason the way he is now.$"

MauvilleCity_Text_WallyPleaseBattleMe: @ 81DFB42
	.string "Wally: {PLAYER}, please!\n"
	.string "Battle with me, please.$"

MauvilleCity_Text_WallyHereICome: @ 81DFB6D
	.string "Wally: {PLAYER}, thank you.\p"
	.string "Okay… Here I come!$"

MauvilleCity_Text_WallyDefeat: @ 81DFB96
	.string "Wally: … … … … … … …\p"
	.string "… … … … … … … …\p"
	.string "I lost…$"

MauvilleCity_Text_WallyIllGoBackToVerdanturf: @ 81DFBC3
	.string "Wally: Uncle…\n"
	.string "I'll go back to Verdanturf…$"

MauvilleCity_Text_ThankYouNotEnoughToBattle: @ 81DFBED
	.string "{PLAYER}, thank you.\n"
	.string "Being a Trainer is tough, isn't it?\p"
	.string "It's not enough just to have Pokémon\n"
	.string "and make them battle. That isn't what\l"
	.string "being a real Trainer is about.$"

MauvilleCity_Text_UncleNoNeedToBeDown: @ 81DFC8A
	.string "Uncle: Wally, there's no need to be so\n"
	.string "down on yourself.\p"
	.string "Why, what's keeping you from becoming\n"
	.string "stronger and stronger?$"

MauvilleCity_Text_WattsonYourUnclesRight:
	.string "???: Your uncle's right!$"

MauvilleCity_Text_WattsonWatchingFromInside:
	.string "Wattson: I was watching your battle\n"
	.string "from inside the Gym.\p"
	.string "Don't let this one loss get you down!\p"
	.string "I can see the spark in your eyes!\n"
	.string "Keep training and you'll become a\l"
	.string "fine trainer! Wahahahaha!\p"
	.string "Here, let me share some advice:\n"
	.string "… … … … … …$"

MauvilleCity_Text_UncleVisitUsSometime: @ 81DFD34
	.string "Uncle: {PLAYER}{KUN}, it just dawned on me\n"
	.string "that you must be the Trainer who kept\l"
	.string "an eye out for Wally when he caught\l"
	.string "his Pokémon.\p"
	.string "Why don't you visit us in Verdanturf\n"
	.string "sometime?\l"
	.string "I'm sure Wally would enjoy it.$"

MauvilleCity_Text_WattsonDontGiveUp:
	.string "Wattson: … … … … … …\n"
	.string "…and that's everything I've got!\p"
	.string "Keep your head up, and don't give up!\p"
	.string "You'll be shocked when you see just\n"
	.string "how far you'll go!\p"
	.string "Wahahahaha!$"

MauvilleCity_Text_WallyThankYouWattson:
	.string "Wally: W-wow! Thank you!\n"
	.string "I won't give up! You can count on it!$"

MauvilleCity_Text_UncleLetsGoHome:
	.string "Uncle: Come on, let's go home.\n"
	.string "Everyone's waiting for you.$"

MauvilleCity_Text_WattsonYouHoweverAreReady:
	.string "Wattson: You, however…\n"
	.string "You're ready to challenge the Gym.\p"
	.string "That was quite the electrifying\n"
	.string "display you put on! Wahahahaha!\p"
	.string "Please! Once you've recharged,\n"
	.string "visit me in my Gym!$"

MauvilleCity_Text_WallyPokenavCall: @ 81DFDFB
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "Wally: Oh, hello, {PLAYER}!\p"
	.string "I just wanted to tell you that\n"
	.string "my uncle bought me a PokéNav!\p"
	.string "Now I can get in touch with you\n"
	.string "anytime, {PLAYER}!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"

MauvilleCity_Text_RegisteredWally: @ 81DFEB4
	.string "Registered Wally\n"
	.string "in the PokéNav.$"

MauvilleCity_Text_ScottYouDidntHoldBack: @ 81DFED5
	.string "Scott: Hehe…\n"
	.string "I was also watching that match!\p"
	.string "You're friends with that boy Wally,\n"
	.string "aren't you?\p"
	.string "But you didn't hold anything back\n"
	.string "and beat him impressively.\p"
	.string "Yeah! That's what a real Pokémon\n"
	.string "battle is all about!\p"
	.string "I idolize Trainers like that!\p"
	.string "… … … … … …\n"
	.string "I'll be cheering for you!$"

MauvilleCity_Text_WattsonNeedFavorTakeKey: @ 81DFFE4
	.string "Wattson: Oh, {PLAYER}{KUN}!\n"
	.string "You look like you have a lot of zip!\l"
	.string "That's a good thing, wahahahaha!\p"
	.string "Fine! I've decided!\n"
	.string "I need a favor, {PLAYER}{KUN}!\p"
	.string "Mauville City has an underground\n"
	.string "sector called New Mauville.\p"
	.string "{PLAYER}{KUN}, I'd like you to go there and\n"
	.string "switch off the Generator.\p"
	.string "The Generator has been running a bit\n"
	.string "haywire. It's getting unsafe.\p"
	.string "Here, this is the Key to get into\n"
	.string "New Mauville.$"

MauvilleCity_Text_WattsonWontBeChallenge: @ 81E0154
	.string "Wattson: Don't you worry about it.\n"
	.string "It won't be a challenge to you.\p"
	.string "The entrance to New Mauville is just\n"
	.string "a short Surf away from Route 110.\p"
	.string "That's it, then, you have my trust!\n"
	.string "Wahahahaha!$"

MauvilleCity_Text_WattsonThanksTakeTM: @ 81E020E
	.string "Wattson: Wahahahaha!\p"
	.string "I knew it, {PLAYER}{KUN}! I knew I'd made\n"
	.string "the right choice asking you!\p"
	.string "This is my thanks--a TM containing\n"
	.string "Thunderbolt!\p"
	.string "Go on, you've earned it!$"

MauvilleCity_Text_WattsonYoungTakeCharge: @ 81E02AA
	.string "Wattson: Wahahahaha!\p"
	.string "It pleases me to no end to see\n"
	.string "the young step up and take charge!$"

MauvilleCity_Text_WattsonPressedRedButton:
	.string "Wattson: You're back! Did you\n"
	.string "switch off the generator?\p"
	.string "… … … … … …\n"
	.string "Hmm?\p"
	.string "You pressed the switch but the\n"
	.string "generator is still running?\p"
	.string "That's concerning… I suggest you\n"
	.string "go back and take a second look at\l"
	.string "the generator.\p"
	.string "Maybe there's something wrong with\n"
	.string "the generator itself.$"

MauvilleCity_Text_NurseHurtMonBackToHealth: @ 81E0301
	.string "You know, it's cool to have Pokémon\n"
	.string "battles and stuff…\p"
	.string "But if your Pokémon gets hurt,\n"
	.string "you have to nurse it back to health.$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough: @ 81E037C
	.string "The roads of this town stretch north\n"
	.string "and south, and east and west.\p"
	.string "Because of that, we get all sorts of\n"
	.string "people coming through.$"

MauvilleCity_Text_RydelVeryGenerous: @ 81E03FB
	.string "Have you been to Rydel's Cycles yet?\p"
	.string "Rydel, the owner, is a very generous\n"
	.string "man.$"

MauvilleCity_Text_PokemonCanJumpYouOnBike: @ 81E044A
	.string "Even if you're riding a Bike,\n"
	.string "wild Pokémon could jump you.$"

MauvilleCity_Text_CitySign: @ 81E0485
	.string "Mauville City\n"
	.string "“The bright and shiny city of fun!”$"

MauvilleCity_Text_GymSign: @ 81E04B7
	.string "Mauville City Pokémon Gym\n"
	.string "Leader: Wattson\l"
	.string "“The cheerfully electrifying man!”$"

MauvilleCity_Text_BikeShopSign: @ 81E0504
	.string "“Ride in gravel and shake up your\n"
	.string "soul!”\l"
	.string "Rydel's Cycles$"

MauvilleCity_Text_GameCornerSign: @ 81E053C
	.string "“The play spot for all!”\n"
	.string "Mauville Game Corner$"

MauvilleCity_Text_BattleTentSign:
	.string "Battle Tent Mauville Site\n"
	.string "“Feast your eyes on battles!”$"

MauvilleCity_Text_ExplainTV: @ 81E056A
	.string "Hi, do you check out TV at all?\p"
	.string "They've added a bunch of cool new\n"
	.string "shows recently.\p"
	.string "TV is so cool. I've seen my friends on\n"
	.string "TV just out of the blue.\p"
	.string "And, sometimes, they even put you on TV\n"
	.string "without telling you.\p"
	.string "I wish I would be on TV sometime.\p"
	.string "That's why I think you should check\n"
	.string "out TVs whenever you can.$"

MauvilleCity_Text_BeenCheckingOutTV: @ 81E0699
	.string "Hi, have you been checking out TVs?$"
