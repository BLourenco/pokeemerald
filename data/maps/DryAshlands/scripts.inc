.set LOCALID_RIVAL, 7
.set LOCALID_RIVAL_ON_BIKE, 8

DryAshlands_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, DryAshlands_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, DryAshlands_OnTransition
	.byte 0

DryAshlands_OnResume:
	setstepcallback STEP_CB_ASH
	end
    
DryAshlands_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	end
    
DryAshlands_EventScript_RivalTrigger::
	goto DryAshlands_EventScript_RivalScene
	end
    
@ Redo the following events

DryAshlands_EventScript_RivalScene:: @ 81EF76E
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq DryAshlands_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	call_if_eq DryAshlands_EventScript_PlayBrendanMusic
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 30
	call DryAshlands_EventScript_RivalApproachPlayer
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq DryAshlands_EventScript_MayBattle
	compare VAR_RESULT, FEMALE
	goto_if_eq DryAshlands_EventScript_BrendanBattle
	releaseall
	end
    
DryAshlands_EventScript_PlayMayMusic:: @ 81EF7E1
	playbgm MUS_ENCOUNTER_MAY, 1
	return

DryAshlands_EventScript_PlayBrendanMusic:: @ 81EF7E6
	playbgm MUS_ENCOUNTER_BRENDAN, 1
	return

DryAshlands_EventScript_MayBattle:: @ 81EF7EB
	msgbox DryAshlands_Text_MayLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, DryAshlands_EventScript_MayBattleTreecko
	case 1, DryAshlands_EventScript_MayBattleTorchic
	case 2, DryAshlands_EventScript_MayBattleMudkip
	end

DryAshlands_EventScript_MayBattleTreecko:: @ 81EF81A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TREECKO, DryAshlands_Text_MayDefeated
	goto DryAshlands_EventScript_MayDefeated
	end

DryAshlands_EventScript_MayBattleTorchic:: @ 81EF82A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TORCHIC, DryAshlands_Text_MayDefeated
	goto DryAshlands_EventScript_MayDefeated
	end

DryAshlands_EventScript_MayBattleMudkip:: @ 81EF83A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_MUDKIP, DryAshlands_Text_MayDefeated
	goto DryAshlands_EventScript_MayDefeated
	end

DryAshlands_EventScript_MayDefeated:: @ 81EF84A
	@ msgbox DryAshlands_Text_MayTakeThis, MSGBOX_DEFAULT
	@ call DryAshlands_EventScript_GiveItemfinder
	@ msgbox DryAshlands_Text_MayExplainItemfinder, MSGBOX_DEFAULT
	goto DryAshlands_EventScript_RivalExit
	end

DryAshlands_EventScript_BrendanBattle:: @ 81EF865
	msgbox DryAshlands_Text_BrendanLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, DryAshlands_EventScript_BrendanBattleTreecko
	case 1, DryAshlands_EventScript_BrendanBattleTorchic
	case 2, DryAshlands_EventScript_BrendanBattleMudkip
	end

DryAshlands_EventScript_BrendanBattleTreecko:: @ 81EF894
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TREECKO, DryAshlands_Text_BrendanDefeated
	goto DryAshlands_EventScript_BrendanDefeated
	end

DryAshlands_EventScript_BrendanBattleTorchic:: @ 81EF8A4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TORCHIC, DryAshlands_Text_BrendanDefeated
	goto DryAshlands_EventScript_BrendanDefeated
	end

DryAshlands_EventScript_BrendanBattleMudkip:: @ 81EF8B4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_MUDKIP, DryAshlands_Text_BrendanDefeated
	goto DryAshlands_EventScript_BrendanDefeated
	end

DryAshlands_EventScript_BrendanDefeated:: @ 81EF8C4
	@ msgbox DryAshlands_Text_BrendanTakeThis, MSGBOX_DEFAULT
	@ call DryAshlands_EventScript_GiveItemfinder
	@ msgbox DryAshlands_Text_BrendanExplainItemfinder, MSGBOX_DEFAULT
	goto DryAshlands_EventScript_RivalExit
	end

DryAshlands_EventScript_GiveItemfinder:: @ 81EF8DF
	giveitem ITEM_ITEMFINDER
	return

DryAshlands_EventScript_RivalExit:: @ 81EF8EC
	closemessage
	call DryAshlands_EventScript_MoveRival
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_FACE_LEFT
	setobjectmovementtype LOCALID_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_LEFT
	removeobject LOCALID_RIVAL
	addobject LOCALID_RIVAL_ON_BIKE
	delay 45
	applymovement LOCALID_RIVAL_ON_BIKE, DryAshlands_Movement_RivalExit
	waitmovement 0
	removeobject LOCALID_RIVAL_ON_BIKE
	setvar VAR_DRY_ASHLANDS_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

DryAshlands_EventScript_RivalApproachPlayer:: @ 81EF94E
	applymovement LOCALID_RIVAL, DryAshlands_Movement_RivalApproachPlayer
	waitmovement 0
	return

DryAshlands_EventScript_MoveRival:: @ 81EF990
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 43, 18
	return

DryAshlands_Movement_RivalApproachPlayer: @ 81EF9A8
	walk_up
	walk_right
	step_end

DryAshlands_Movement_RivalExit: @ 81EF9B2
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

DryAshlands_Text_MayLetsBattle: @ 81EFC48
	.string "May: Hi, {PLAYER}{KUN}, long time no see!\p"
	.string "While I was searching for other\n"
	.string "Pokémon, my Pokémon grew stronger.\p"
	.string "So…\n"
	.string "How about a little battle?$"

DryAshlands_Text_MayDefeated: @ 81EFCCB
	.string "Yikes!\n"
	.string "You're better than I expected!$"

DryAshlands_Text_MayTakeThis: @ 81EFCF1
	.string "May: {PLAYER}{KUN}, you've been busy\n"
	.string "training, too, haven't you?\p"
	.string "I think you deserve a reward!\n"
	.string "This is from me!$"

DryAshlands_Text_MayExplainItemfinder: @ 81EFD58
	.string "May: That's an Itemfinder.\p"
	.string "Try it out. If there is an item that's\n"
	.string "not visible, it emits a sound.\p"
	.string "Okay, {PLAYER}{KUN}, let's meet again!\p"
	.string "I know it's a little silly coming from\n"
	.string "me, but I think you should train a lot\l"
	.string "harder for the next time.$"

DryAshlands_Text_BrendanLetsBattle: @ 81EFE3F
	.string "Brendan: Hey, {PLAYER}.\n"
	.string "So this is where you were.\l"
	.string "How's it going?\p"
	.string "Have you been raising your Pokémon?\n"
	.string "I'll check for you.$"

DryAshlands_Text_BrendanDefeated: @ 81EFEB4
	.string "Hmm…\n"
	.string "You're pretty good.$"

DryAshlands_Text_BrendanTakeThis: @ 81EFECD
	.string "Brendan: {PLAYER}, you've trained\n"
	.string "without me noticing…\p"
	.string "Good enough!\n"
	.string "Here, take this.$"

DryAshlands_Text_BrendanExplainItemfinder: @ 81EFF1C
	.string "Brendan: That's an Itemfinder.\p"
	.string "Use it to root around for items that\n"
	.string "aren't visible.\p"
	.string "If it senses something, it emits\n"
	.string "a sound.\p"
	.string "Anyway, I'm off to look for new\n"
	.string "Pokémon.$"

