.set LOCALID_RIVAL, 6
.set LOCALID_RIVAL_ON_BIKE, 7
.set LOCALID_SUDOWOODO, 10

DryAshlands_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, DryAshlands_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, DryAshlands_OnTransition
	.byte 0

DryAshlands_OnResume:
	setstepcallback STEP_CB_ASH
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, DryAshlands_EventScript_TryRemoveSudowoodo
	end
    
DryAshlands_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	setflag FLAG_LANDMARK_DRY_ASHLANDS
	call_if_unset FLAG_DEFEATED_SUDOWOODO_DRY_ASHLANDS, DryAshlands_EventScript_ShowSudowoodo
	end

DryAshlands_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

DryAshlands_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_DRY_ASHLANDS_SUDOWOODO
	return

DryAshlands_EventScript_RouteSign::
	msgbox DryAshlands_Text_RouteSign, MSGBOX_SIGN
	end

DryAshlands_EventScript_Fisherman:: @ 81F218A
	msgbox DryAshlands_Text_ToughWaterPokemon, MSGBOX_NPC
	end

DryAshlands_EventScript_NorthPointSign::
	msgbox DryAshlands_Text_NorthPointSign, MSGBOX_SIGN
	end
  
DryAshlands_EventScript_RivalTrigger::
	goto DryAshlands_EventScript_RivalScene
	end

DryAshlands_EventScript_Liam::
	trainerbattle_single TRAINER_LIAM, DryAshlands_Text_LiamIntro, DryAshlands_Text_LiamDefeat
	msgbox DryAshlands_Text_LiamPostBattle, MSGBOX_AUTOCLOSE
	end

DryAshlands_EventScript_Ingrid::
	trainerbattle_single TRAINER_INGRID, DryAshlands_Text_IngridIntro, DryAshlands_Text_IngridDefeat
	msgbox DryAshlands_Text_IngridPostBattle, MSGBOX_AUTOCLOSE
	end

DryAshlands_EventScript_Cormac::
	trainerbattle_single TRAINER_CORMAC, DryAshlands_Text_CormacIntro, DryAshlands_Text_CormacDefeat
	msgbox DryAshlands_Text_CormacPostBattle, MSGBOX_AUTOCLOSE
	end
DryAshlands_EventScript_Sudowoodo:: @ 8242CEA
	lock
	@faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, DryAshlands_Movement_SudowoodoShake
	waitmovement 0
	release
	end

DryAshlands_EventScript_WaterSudowoodo:: @ 8242CFC
	lock
	@faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, DryAshlands_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, 2
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 20, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DryAshlands_EventScript_DefeatedSudowoodo
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq DryAshlands_EventScript_DefeatedSudowoodo
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq DryAshlands_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO_DRY_ASHLANDS
	release
	end

DryAshlands_EventScript_DefeatedSudowoodo:: @ 8242D60
	setflag FLAG_DEFEATED_SUDOWOODO_DRY_ASHLANDS
	goto Common_EventScript_RemoveStaticPokemon
	end

DryAshlands_Movement_SudowoodoShake: @ 8242D69
	face_up
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_up
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

    
@ Redo the following events

DryAshlands_EventScript_RivalScene::
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
	applymovement LOCALID_RIVAL, DryAshlands_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
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
	trainerbattle_no_intro TRAINER_MAY_DRY_ASHLANDS_TREECKO, DryAshlands_Text_MayDefeated
	goto DryAshlands_EventScript_MayDefeated
	end

DryAshlands_EventScript_MayBattleTorchic:: @ 81EF82A
	trainerbattle_no_intro TRAINER_MAY_DRY_ASHLANDS_TORCHIC, DryAshlands_Text_MayDefeated
	goto DryAshlands_EventScript_MayDefeated
	end

DryAshlands_EventScript_MayBattleMudkip:: @ 81EF83A
	trainerbattle_no_intro TRAINER_MAY_DRY_ASHLANDS_MUDKIP, DryAshlands_Text_MayDefeated
	goto DryAshlands_EventScript_MayDefeated
	end

DryAshlands_EventScript_MayDefeated:: @ 81EF84A
	@ msgbox DryAshlands_Text_MayTakeThis, MSGBOX_DEFAULT
	@ call DryAshlands_EventScript_GiveItemfinder
	@ msgbox DryAshlands_Text_MayExplainItemfinder, MSGBOX_DEFAULT
	msgbox DryAshlands_Text_MayGoingToSeeProfCozmo, MSGBOX_DEFAULT
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
	trainerbattle_no_intro TRAINER_BRENDAN_DRY_ASHLANDS_TREECKO, DryAshlands_Text_BrendanDefeated
	goto DryAshlands_EventScript_BrendanDefeated
	end

DryAshlands_EventScript_BrendanBattleTorchic:: @ 81EF8A4
	trainerbattle_no_intro TRAINER_BRENDAN_DRY_ASHLANDS_TORCHIC, DryAshlands_Text_BrendanDefeated
	goto DryAshlands_EventScript_BrendanDefeated
	end

DryAshlands_EventScript_BrendanBattleMudkip:: @ 81EF8B4
	trainerbattle_no_intro TRAINER_BRENDAN_DRY_ASHLANDS_MUDKIP, DryAshlands_Text_BrendanDefeated
	goto DryAshlands_EventScript_BrendanDefeated
	end

DryAshlands_EventScript_BrendanDefeated:: @ 81EF8C4
	@ msgbox DryAshlands_Text_BrendanTakeThis, MSGBOX_DEFAULT
	@ call DryAshlands_EventScript_GiveItemfinder
	@ msgbox DryAshlands_Text_BrendanExplainItemfinder, MSGBOX_DEFAULT
	msgbox DryAshlands_Text_BrendanGoingToSeeProfCozmo, MSGBOX_DEFAULT
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

DryAshlands_Text_RouteSign:
	.string "The Dry Ashlands\n"
	.string "{DOWN_ARROW} Route 113$"

DryAshlands_Text_NorthPointSign:
	.string "If you walk up to the edge of\n"
	.string "this cliff, you'll have reached the\l"
	.string "northernmost point in Hoenn!$"

DryAshlands_Text_ToughWaterPokemon:
	.string "The falling ash from Mt. Chimney\n"
	.string "makes these waters inhabitable to\l"
	.string "many of the usual water-dwelling\l"
	.string "Pokémon you find elsewhere in Hoenn.$"

DryAshlands_Text_MayLetsBattle:
	.string "{RIVAL}: Oh! Hi, {PLAYER}{KUN}!\p"
	.string "I'm not surprised to see you here.\p"
	.string "There's some hardy Pokémon here\n"
	.string "that'd really bolster your team.\p"
	.string "Speaking of which, are they up for a\n"
	.string "battle? My Pokémon are raring to go!\p"
	.string "All right!\n"
	.string "Here we come!$"

DryAshlands_Text_MayDefeated:
	.string "Wow!\n"
	.string "Very impressive!$"

DryAshlands_Text_MayGoingToSeeProfCozmo:
	.string "You've really become a lot stronger\n"
	.string "since last time we battled, {PLAYER}{KUN}.\p"
	.string "I think your dad is going to be very\n"
	.string "proud to see how far you've come.\p"
	.string "Anyways, I'm actually headed for\n"
	.string "Fallarbor Town to meet Prof. Cozmo.\p"
	.string "He's an expert on Meteorites. He\n"
	.string "spends a lot of time in Meteor Falls\l"
	.string "searching for them.\p"
	.string "I'm hoping to learn what he knows about\n"
	.string "the Pokémon that live there.\p"
	.string "I've heard there are Pokémon that came\n"
	.string "here from space! Can you believe it?\p"
	.string "Well, it was nice seeing you again,\n"
	.string "{PLAYER}{KUN}.\p"
	.string "Bye!$"

DryAshlands_Text_MayTakeThis: 
	.string "{RIVAL}: {PLAYER}{KUN}, take this.$"

DryAshlands_Text_MayExplainItem:
	.string "{RIVAL}: That's an item.$"

DryAshlands_Text_BrendanLetsBattle:
	.string "{RIVAL}: Oh! Hey, {PLAYER}!\p"
	.string "I'm not surprised to see you here.\p"
	.string "There's some hardy Pokémon here\n"
	.string "that'd really bolster your team.\p"
	.string "Speaking of which, are they up for a\n"
	.string "battle? My Pokémon are raring to go!\p"
	.string "All right!\n"
	.string "Here we come!$"

DryAshlands_Text_BrendanDefeated:
	.string "Wow!\n"
	.string "Very impressive!$"

DryAshlands_Text_BrendanGoingToSeeProfCozmo:
	.string "You've really become a lot tougher\n"
	.string "since last time we battled, {PLAYER}.\p"
	.string "I think your dad is going to be very\n"
	.string "proud to see how far you've come.\p"
	.string "Anyways, I'm actually headed for\n"
	.string "Fallarbor Town to meet Prof. Cozmo.\p"
	.string "He's an expert on Meteorites. He\n"
	.string "spends a lot of time in Meteor Falls\l"
	.string "searching for them.\p"
	.string "I'm hoping to learn what he knows about\n"
	.string "the Pokémon that live there.\p"
	.string "I've heard there are Pokémon that came\n"
	.string "here from space! Can you believe it?\p"
	.string "Well, it was nice seeing you again,\n"
	.string "{PLAYER}.\p"
	.string "See ya!$"

DryAshlands_Text_BrendanTakeThis:
	.string "{RIVAL}: {PLAYER}, take this.$"

DryAshlands_Text_BrendanExplainItem:
	.string "{RIVAL}: That's an item.$"

