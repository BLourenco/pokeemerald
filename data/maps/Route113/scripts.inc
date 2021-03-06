.set LOCALID_GLASS_WORKER, 18

Route113_MapScripts:: @ 81F2153
	map_script MAP_SCRIPT_ON_RESUME, Route113_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route113_OnTransition
	.byte 0

Route113_OnResume: @ 81F215E
	setstepcallback STEP_CB_ASH
	end

Route113_OnTransition: @ 81F2161
	setflag FLAG_VISITED_ROUTE_113
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	call Route113_EventScript_CheckSetAshWeather
	end

Route113_EventScript_CheckSetAshWeather:: @ 81F216A
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_0, 19
	goto_if_lt Route113_EventScript_DontSetAshWeather
	compare VAR_TEMP_0, 84
	goto_if_gt Route113_EventScript_DontSetAshWeather
	setweather WEATHER_VOLCANIC_ASH
	return

Route113_EventScript_DontSetAshWeather:: @ 81F2189
	return

Route113_EventScript_GlassWorkerTrigger1:: @ 81EF74D
	setvar VAR_0x8008, 1
	goto Route113_EventScript_GlassWorkerScene
	end

Route113_EventScript_GlassWorkerTrigger2:: @ 81EF758
	setvar VAR_0x8008, 2
	goto Route113_EventScript_GlassWorkerScene
	end

Route113_EventScript_GlassWorkerTrigger3:: @ 81EF763
	setvar VAR_0x8008, 3
	goto Route113_EventScript_GlassWorkerScene
	end

Route113_EventScript_GlassWorkerScene::
	lockall
	faceplayer
	applymovement LOCALID_GLASS_WORKER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_GLASS_WORKER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GLASS_WORKER, Common_Movement_Delay48
	waitmovement 0
	delay 30
	compare VAR_0x8008, 1
	call_if_eq Route113_EventScript_GlassWorkerApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq Route113_EventScript_GlassWorkerApproachPlayer2
	compare VAR_0x8008, 3
	call_if_eq Route113_EventScript_GlassWorkerApproachPlayer3
	msgbox Route113_Text_GoCollectAshWithThis, MSGBOX_DEFAULT
	giveitem ITEM_SOOT_SACK
	setvar VAR_GLASS_WORKSHOP_STATE, 1
	msgbox Route113_Text_ExplainSootSack, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 1
	call_if_eq Route113_EventScript_GlassWorkerExit1
	compare VAR_0x8008, 2
	call_if_eq Route113_EventScript_GlassWorkerExit2
	compare VAR_0x8008, 3
	call_if_eq Route113_EventScript_GlassWorkerExit3
	removeobject LOCALID_GLASS_WORKER
	setvar VAR_ROUTE113_STATE, 1
	releaseall
	end

Route113_EventScript_GlassWorkerApproachPlayer1:: @ 81EF94E
	applymovement LOCALID_GLASS_WORKER, Route113_Movement_GlassWorkerApproachPlayer1
	waitmovement 0
	return

Route113_EventScript_GlassWorkerApproachPlayer2:: @ 81EF959
	applymovement LOCALID_GLASS_WORKER, Route113_Movement_GlassWorkerApproachPlayer2
	waitmovement 0
	return

Route113_EventScript_GlassWorkerApproachPlayer3:: @ 81EF964
	applymovement LOCALID_GLASS_WORKER, Route113_Movement_GlassWorkerApproachPlayer3
	waitmovement 0
	return

Route113_EventScript_GlassWorkerExit1:: @ 81EF96F
	applymovement LOCALID_GLASS_WORKER, Route113_Movement_GlassWorkerExit1
	waitmovement 0
	return

Route113_EventScript_GlassWorkerExit2:: @ 81EF96F
	applymovement LOCALID_GLASS_WORKER, Route113_Movement_GlassWorkerExit2
	waitmovement 0
	return

Route113_EventScript_GlassWorkerExit3:: @ 81EF96F
	applymovement LOCALID_GLASS_WORKER, Route113_Movement_GlassWorkerExit3
	waitmovement 0
	return

Route113_Movement_GlassWorkerApproachPlayer1: @ 81EF9A8
	walk_up
	walk_right
	walk_in_place_fastest_right
	step_end

Route113_Movement_GlassWorkerApproachPlayer2: @ 81EF9AC
	walk_right
	step_end

Route113_Movement_GlassWorkerApproachPlayer3: @ 81EF9AE
	walk_down
	walk_right
	walk_in_place_fastest_right
	step_end

Route113_Movement_GlassWorkerExit1: @ 81EF9BA
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

Route113_Movement_GlassWorkerExit2: @ 81EF9BA
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

Route113_Movement_GlassWorkerExit3: @ 81EF9BA
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

Route113_EventScript_Gentleman:: @ 81F218A
	msgbox Route113_Text_AshCanBeFashionedIntoGlass, MSGBOX_NPC
	end

Route113_EventScript_NinjaBoy:: @ 81F2193
	msgbox Route113_Text_FunWalkingThroughAsh, MSGBOX_NPC
	end

Route113_EventScript_RouteSign111:: @ 81F219C
	msgbox Route113_Text_RouteSign111, MSGBOX_SIGN
	end

Route113_EventScript_RouteSignFallarbor:: @ 81F21A5
	msgbox Route113_Text_RouteSignFallarbor, MSGBOX_SIGN
	end

Route113_EventScript_GlassWorkshopSign:: @ 81F21AE
	msgbox Route113_Text_GlassWorkshopSign, MSGBOX_SIGN
	end

Route113_EventScript_TrainerTipsRegisterKeyItems:: @ 81F21B7
	msgbox Route113_Text_TrainerTipsRegisterKeyItems, MSGBOX_SIGN
	end

Route113_EventScript_Jaylen:: @ 81F21C0
	trainerbattle_single TRAINER_JAYLEN, Route113_Text_JaylenIntro, Route113_Text_JaylenDefeat
	msgbox Route113_Text_JaylenPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Dillon:: @ 81F21D7
	trainerbattle_single TRAINER_DILLON, Route113_Text_DillonIntro, Route113_Text_DillonDefeat
	msgbox Route113_Text_DillonPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Madeline:: @ 81F21EE
	trainerbattle_single TRAINER_MADELINE_1, Route113_Text_MadelineIntro, Route113_Text_MadelineDefeat, Route113_EventScript_RegisterMadeline
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route113_EventScript_RematchMadeline
	msgbox Route113_Text_MadelinePostBattle, MSGBOX_DEFAULT
	release
	end

Route113_EventScript_RegisterMadeline:: @ 81F221A
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route113_Text_MadelineRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MADELINE_1
	release
	end

Route113_EventScript_RematchMadeline:: @ 81F2239
	trainerbattle_rematch TRAINER_MADELINE_1, Route113_Text_MadelineRematchIntro, Route113_Text_MadelineRematchDefeat
	msgbox Route113_Text_MadelinePostRematch, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Lao:: @ 81F2250
	trainerbattle_single TRAINER_LAO_1, Route113_Text_LaoIntro, Route113_Text_LaoDefeat, Route113_EventScript_RegisterLao
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route113_EventScript_RematchLao
	msgbox Route113_Text_LaoPostBattle, MSGBOX_DEFAULT
	release
	end

Route113_EventScript_RegisterLao:: @ 81F227C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route113_Text_LaoRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_LAO_1
	release
	end

Route113_EventScript_RematchLao:: @ 81F229B
	trainerbattle_rematch TRAINER_LAO_1, Route113_Text_LaoRematchIntro, Route113_Text_LaoRematchDefeat
	msgbox Route113_Text_LaoPostRematch, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Lung:: @ 81F22B2
	trainerbattle_single TRAINER_LUNG, Route113_Text_LungIntro, Route113_Text_LungDefeat
	msgbox Route113_Text_LungPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Tori:: @ 81F22C9
	trainerbattle_double TRAINER_TORI_AND_TIA, Route113_Text_ToriIntro, Route113_Text_ToriDefeat, Route113_Text_ToriNotEnoughMons
	msgbox Route113_Text_ToriPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Tia:: @ 81F22E4
	trainerbattle_double TRAINER_TORI_AND_TIA, Route113_Text_TiaIntro, Route113_Text_TiaDefeat, Route113_Text_TiaNotEnoughMons
	msgbox Route113_Text_TiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Sophie:: @ 81F22FF
	trainerbattle_single TRAINER_SOPHIE, Route113_Text_SophieIntro, Route113_Text_SophieDefeat
	msgbox Route113_Text_SophiePostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Coby:: @ 81F2316
	trainerbattle_single TRAINER_COBY, Route113_Text_CobyIntro, Route113_Text_CobyDefeat
	msgbox Route113_Text_CobyPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Lawrence:: @ 81F232D
	trainerbattle_single TRAINER_LAWRENCE, Route113_Text_LawrenceIntro, Route113_Text_LawrenceDefeat
	msgbox Route113_Text_LawrencePostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Wyatt:: @ 81F2344
	trainerbattle_single TRAINER_WYATT, Route113_Text_WyattIntro, Route113_Text_WyattDefeat
	msgbox Route113_Text_WyattPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_Text_GoCollectAshWithThis: @ 826F19D
	.string "This area is covered in volcanic ash,\n"
	.string "huff-puff!\p"
	.string "I'm specially gifted, huff-puff.\p"
	.string "I make glass out of volcanic ash\n"
	.string "and make items, huff-puff.\p"
	.string "Go collect ashes with this, huff-puff.$"

Route113_Text_ExplainSootSack: @ 826F252
	.string "Just take that Soot Sack and walk\n"
	.string "through the grass, huff-puff.\p"
	.string "And it will fill up with 1-3 grams of\n"
	.string "volcanic ash per step, huff-puff.\p"
	.string "Once you think you've collected a good\n"
	.string "amount, come see me, huff-puff.\p"
	.string "My workshop is at the other end of this\n"
	.string "route, huff-puff.$"

Route113_Text_AshCanBeFashionedIntoGlass: @ 81F235B
	.string "Wahahaha! Today's technology is a\n"
	.string "wondrous thing!\p"
	.string "Take this volcanic ash here.\n"
	.string "It can be fashioned into glass.$"

Route113_Text_FunWalkingThroughAsh: @ 81F23CA
	.string "It's fun walking through the volcano's\n"
	.string "ashes on the ground and grass.\p"
	.string "You can see where you walked--it's\n"
	.string "really neat!$"

Route113_Text_RouteSign111: @ 81F2440
	.string "Route 113\n"
	.string "{RIGHT_ARROW} Route 111$"

Route113_Text_RouteSignFallarbor: @ 81F2456
	.string "Route 113\n"
	.string "{LEFT_ARROW} Fallarbor Town$"

Route113_Text_TrainerTipsRegisterKeyItems: @ 81F2471
	.string "Trainer Tips\p"
	.string "You may register one of the Key Items\n"
	.string "in your Bag as Select.\p"
	.string "Simply press Select to use\n"
	.string "the registered item conveniently.$"

Route113_Text_GlassWorkshopSign: @ 81F24F8
	.string "Glass Workshop\n"
	.string "“Turning Volcanic Ash into Glass Items”$"

