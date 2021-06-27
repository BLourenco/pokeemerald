.set LOCALID_WALLY, 19

Route118_MapScripts:: @ 81F3DBC
	map_script MAP_SCRIPT_ON_TRANSITION, Route118_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route118_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route118_OnFrame
	.byte 0

Route118_OnTransition: @ 81F3DCC
	setflag FLAG_VISITED_ROUTE_118
	setvar VAR_0x8008, 1 @ Wally's position, 0=left, 1=middle, 2=right
	compare VAR_ROUTE118_STATE, 1
	call_if_eq Route118_EventScript_ResetWallyPosition 
	call GabbyAndTy_EventScript_UpdateLocation
	compare VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	call_if_eq AbnormalWeather_EventScript_HideMapNamePopup
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_EAST
	call_if_eq AbnormalWeather_StartGroudonWeather
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_WEST
	call_if_eq AbnormalWeather_StartGroudonWeather
	end

Route118_OnLoad: @ 81F3DF3
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_EAST
	call_if_eq AbnormalWeather_EventScript_PlaceTilesRoute118East
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_WEST
	call_if_eq AbnormalWeather_EventScript_PlaceTilesRoute118West
	end

Route118_OnFrame: @ 81F3E0A
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route118_EventScript_ResetWallyPosition::
	setobjectxyperm LOCALID_WALLY, 44, 10
	return

Route118_EventScript_SuperRodFisherman:: @ 82225C3
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, Route118_EventScript_ReceivedSuperRod
	msgbox Route118_Text_YouWantSuperRod, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route118_EventScript_DeclineSuperRod
	msgbox Route118_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox Route118_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_ReceivedSuperRod:: @ 8222602
	msgbox Route118_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_DeclineSuperRod:: @ 822260C
	msgbox Route118_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_Girl:: @ 81F3E73
	msgbox Route118_Text_CanCrossRiversWithSurf, MSGBOX_NPC
	end

Route118_EventScript_RouteSignMauville:: @ 81F3E7C
	msgbox Route118_Text_RouteSignMauville, MSGBOX_SIGN
	end

Route118_EventScript_RouteSign119:: @ 81F3E85
	msgbox Route118_Text_RouteSign119, MSGBOX_SIGN
	end

Route118_EventScript_WallyTrigger0:: @ 81F3E8E
	lockall
	setvar VAR_0x8008, 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_WALLY, Route118_Movement_WallyApproachLedge0
	waitmovement 0
	goto Route118_EventScript_WallyTrigger
	end

Route118_EventScript_WallyTrigger1:: @ 81F3EAE
	lockall
	setvar VAR_0x8008, 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	goto Route118_EventScript_WallyTrigger
	end

Route118_EventScript_WallyTrigger2:: @ 81F3EC4
	lockall
	setvar VAR_0x8008, 2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_WALLY, Route118_Movement_WallyApproachLedge2
	waitmovement 0
	goto Route118_EventScript_WallyTrigger
	end

Route118_EventScript_WallyTrigger3::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	switch VAR_0x8008
	case 0, Route118_EventScript_WallyFaceDown	
	case 1, Route118_EventScript_WallyOneStepLeft
	case 2, Route118_EventScript_WallyTwoStepsLeft
	end

Route118_EventScript_WallyTrigger4::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	switch VAR_0x8008
	case 0, Route118_EventScript_WallyOneStepRight	
	case 1, Route118_EventScript_WallyFaceDown
	case 2, Route118_EventScript_WallyOneStepLeft
	end

Route118_EventScript_WallyTrigger5::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	switch VAR_0x8008
	case 0, Route118_EventScript_WallyTwoStepsRight	
	case 1, Route118_EventScript_WallyOneStepRight
	case 2, Route118_EventScript_WallyFaceDown
	end

Route118_EventScript_WallyTrigger:: @ 81F3EE4
	playse SE_LEDGE
	applymovement LOCALID_WALLY, Route118_Movement_WallyJumpLedge
	waitmovement 0
	delay 30
	msgbox Route118_Text_Wally, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route118_EventScript_WallyBattleNotReady
	goto Route118_EventScript_WallyAcceptBattle
	end

Route118_EventScript_WallyBattleNotReady::
	msgbox Route118_Text_WallyPleaseComeBackWhenYoureReady, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	setvar VAR_ROUTE118_STATE, 1
	releaseall
	end

Route118_EventScript_WallyReturnForBattle::
	msgbox Route118_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route118_EventScript_WallyBattleNotReady
	goto Route118_EventScript_WallyAcceptBattle
	end

Route118_EventScript_WallyAcceptBattle::
	msgbox Route118_Text_WallyDontHoldBack, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_ROUTE118, Route118_Text_WallyDefeat
	msgbox Route118_Text_WallyThatWasExhilarating, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq Route118_EventScript_WallyExit0
	compare VAR_0x8008, 1
	call_if_eq Route118_EventScript_WallyExit1
	compare VAR_0x8008, 2
	call_if_eq Route118_EventScript_WallyExit2
	setvar VAR_ROUTE118_STATE, 2
	removeobject LOCALID_WALLY
	releaseall
	end

Route118_EventScript_WallyTwoStepsLeft::
	applymovement LOCALID_WALLY, Route118_Movement_WallyTwoStepsLeft
	waitmovement 0
	setvar VAR_0x8008, 0
	goto Route118_EventScript_WallyReturnForBattle
	return

Route118_EventScript_WallyOneStepLeft::
	applymovement LOCALID_WALLY, Route118_Movement_WallyOneStepLeft
	waitmovement 0
	addvar VAR_0x8008, -1
	goto Route118_EventScript_WallyReturnForBattle
	return

Route118_EventScript_WallyFaceDown::
	applymovement LOCALID_WALLY, Common_Movement_FaceDown
	waitmovement 0
	@ no update to position var
	goto Route118_EventScript_WallyReturnForBattle
	return

Route118_EventScript_WallyOneStepRight::
	applymovement LOCALID_WALLY, Route118_Movement_WallyOneStepRight
	waitmovement 0
	addvar VAR_0x8008, 1
	goto Route118_EventScript_WallyReturnForBattle
	return

Route118_EventScript_WallyTwoStepsRight::
	applymovement LOCALID_WALLY, Route118_Movement_WallyTwoStepsRight
	waitmovement 0
	setvar VAR_0x8008, 2
	goto Route118_EventScript_WallyReturnForBattle
	return


Route118_EventScript_WallyExit0:: @ 81F3F28
	applymovement OBJ_EVENT_ID_PLAYER, Route118_Movement_PlayerWatchWallyExit
	applymovement LOCALID_WALLY, Route118_Movement_WallyExit0
	waitmovement 0
	return

Route118_EventScript_WallyExit1:: @ 81F3F3A
	applymovement OBJ_EVENT_ID_PLAYER, Route118_Movement_PlayerWatchWallyExit
	applymovement LOCALID_WALLY, Route118_Movement_WallyExit1
	waitmovement 0
	return

Route118_EventScript_WallyExit2:: @ 81F3F4C
	applymovement OBJ_EVENT_ID_PLAYER, Route118_Movement_PlayerWatchWallyExit
	applymovement LOCALID_WALLY, Route118_Movement_WallyExit2
	waitmovement 0
	return

Route118_Movement_PlayerWatchWallyExit: @ 81F3F5E
	delay_16
	walk_in_place_fastest_right
	step_end

Route118_Movement_WallyApproachLedge0: @ 81F3F61
	walk_left
	step_end

Route118_Movement_WallyApproachLedge2: @ 81F3F63
	walk_right
	step_end

Route118_Movement_WallyJumpLedge: @ 81F3F65
	jump_2_down
	delay_16
	walk_down
	step_end

Route118_Movement_WallyTwoStepsLeft:
	walk_left
	walk_left
	face_down
	step_end

Route118_Movement_WallyOneStepLeft:
	walk_left
	face_down
	step_end

Route118_Movement_WallyOneStepRight:
	walk_right
	face_down
	step_end

Route118_Movement_WallyTwoStepsRight:
	walk_right
	walk_right
	face_down
	step_end

Route118_Movement_WallyExit0: @ 81F3F69
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route118_Movement_WallyExit1: @ 81F3F74
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route118_Movement_WallyExit2: @ 81F3F7E
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route118_EventScript_Rose:: @ 81F3F87
	trainerbattle_single TRAINER_ROSE_1, Route118_Text_RoseIntro, Route118_Text_RoseDefeat, Route118_EventScript_RegisterRose
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route118_EventScript_RematchRose
	msgbox Route118_Text_RosePostBattle, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_RegisterRose:: @ 81F3FB3
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route118_Text_RoseRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ROSE_1
	release
	end

Route118_EventScript_RematchRose:: @ 81F3FD2
	trainerbattle_rematch TRAINER_ROSE_1, Route118_Text_RoseRematchIntro, Route118_Text_RoseRematchDefeat
	msgbox Route118_Text_RosePostRematch, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Barny:: @ 81F3FE9
	trainerbattle_single TRAINER_BARNY, Route118_Text_BarnyIntro, Route118_Text_BarnyDefeat
	msgbox Route118_Text_BarnyPostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Wade:: @ 81F4000
	trainerbattle_single TRAINER_WADE, Route118_Text_WadeIntro, Route118_Text_WadeDefeat
	msgbox Route118_Text_WadePostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Dalton:: @ 81F4017
	trainerbattle_single TRAINER_DALTON_1, Route118_Text_DaltonIntro, Route118_Text_DaltonDefeat, Route118_EventScript_RegisterDalton
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route118_EventScript_RematchDalton
	msgbox Route118_Text_DaltonPostBattle, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_RegisterDalton:: @ 81F4043
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route118_Text_DaltonRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DALTON_1
	release
	end

Route118_EventScript_RematchDalton:: @ 81F4062
	trainerbattle_rematch TRAINER_DALTON_1, Route118_Text_DaltonRematchIntro, Route118_Text_DaltonRematchDefeat
	msgbox Route118_Text_DaltonPostRematch, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Perry:: @ 81F4079
	trainerbattle_single TRAINER_PERRY, Route118_Text_PerryIntro, Route118_Text_PerryDefeat
	msgbox Route118_Text_PerryPostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Chester:: @ 81F4090
	trainerbattle_single TRAINER_CHESTER, Route118_Text_ChesterIntro, Route118_Text_ChesterDefeat
	msgbox Route118_Text_ChesterPostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Deandre:: @ 81F40A7
	trainerbattle_single TRAINER_DEANDRE, Route118_Text_DeandreIntro, Route118_Text_DeandreDefeat
	msgbox Route118_Text_DeandrePostBattle, MSGBOX_AUTOCLOSE
	end

Route118_Text_Wally:
	.string "Wally: Hi, {PLAYER}{KUN}!\n"
	.string "It's me, Wally!\p"
	.string "A lot's happened since we last\n"
	.string "battled.\p"
	.string "I… I left my uncle's place in\n"
	.string "Verdanturf without telling anyone.\p"
	.string "My uncle is probably furious with me,\n"
	.string "but I had to!\p"
	.string "I know he was only trying to look out\n"
	.string "for me, but I couldn't let my health\l"
	.string "keep me at home.\p"
	.string "Ever since I met Ralts and started\n"
	.string "my Pokémon Journey, I've never felt\l"
	.string "better! I have so much energy!\p"
	.string "The excitement of seeing new places,\n"
	.string "meeting new people, and battling with\l"
	.string "my Pokémon at my side…\p"
	.string "It's all so much!\p"
	.string "That's why I have a favor to ask…\n"
	.string "Will you battle with me?\p"
	.string "I know I may not be as strong as you\n"
	.string "right now, but I can only improve by\l"
	.string "challenging stronger Trainers.\p"
	@ FALLTHROUGH
Route118_Text_WallyWillYouBattleMe:
	.string "Please, {PLAYER}.\n"
	.string "Are you ready to battle with me?$"

Route118_Text_WallyPleaseComeBackWhenYoureReady:
	.string "Oh, okay.\n"
	.string "When you're ready, please let me know.\p"
	.string "I'll be waiting here.$"

Route118_Text_WallyDontHoldBack:
	.string "Thank you, {PLAYER}!\n"
	.string "Please, don't hold anything back!$"

Route118_Text_WallyDefeat:
	.string "I tried my best,\n"
	.string "but it wasn't enough.$"

Route118_Text_WallyThatWasExhilarating:
	.string "That was… exhilarating!\p"
	.string "You've really become a lot\n"
	.string "stronger!\p"
	.string "I can tell you've seen so much\n"
	.string "and met so many people and Pokémon\l"
	.string "on your journey already.\p"
	.string "And thanks to our battle, I think I've\n"
	.string "also grown a little stronger myself.\p"
	.string "{PLAYER}, thank you.\n"
	.string "Really.\p"
	.string "I don't know what I'd be doing right\n"
	.string "now if you hadn't help me catch\l"
	.string "my first Pokémon.\p"
	.string "No reason to dwell on that, though.\n"
	.string "The world is waiting for me!\p"
	.string "Bye, {PLAYER}!$"

Route118_Text_YouWantSuperRod: @ 8222616
	.string "Hey there, Trainer!\n"
	.string "A Super Rod really is super!\p"
	.string "Say all you want, but this baby can\n"
	.string "catch Pokémon off the seafloor!\p"
	.string "What do you think?\n"
	.string "You want it, don't you?$"

Route118_Text_SuperRodIsSuper: @ 82226B6
	.string "You bet, you bet!\n"
	.string "After all, a Super Rod is really super!$"

Route118_Text_TryDroppingRodInWater: @ 82226F0
	.string "If there's any water, try dropping in\n"
	.string "your Rod and see what bites!$"

Route118_Text_DontYouLikeToFish: @ 8222733
	.string "Hunh?\n"
	.string "Don't you like to fish?$"

Route118_Text_GoAfterSeafloorPokemon: @ 8222751
	.string "Go after the seafloor Pokémon with\n"
	.string "your Super Rod.$"


Route118_Text_CanCrossRiversWithSurf: @ 81F4367
	.string "Even if there isn't a boat, you can\n"
	.string "cross rivers and the sea if you have\l"
	.string "a Pokémon that knows Surf.\p"
	.string "Pokémon can be counted on to do so\n"
	.string "much!$"

Route118_Text_RouteSignMauville: @ 81F43F4
	.string "Route 118\n"
	.string "{LEFT_ARROW} Mauville City$"

Route118_Text_RouteSign119: @ 81F440E
	.string "Route 118\n"
	.string "{UP_ARROW} Route 119$"

