.set LOCALID_RUIN_MANIAC, 1
.set LOCALID_AZURILL, 2
.set LOCALID_SHINY_STONE, 13

AlteringCave_Hidden_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AlteringCave_Hidden_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, AlteringCave_Hidden_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AlteringCave_Hidden_OnFrame
	.byte 0

AlteringCave_Hidden_OnTransition:
	goto_if_set FLAG_ALTERING_CAVE_REVEALED, AlteringCave_Hidden_EventScript_SetRevealed
	goto AlteringCave_Hidden_EventScript_SetHidden

AlteringCave_Hidden_EventScript_SetRevealed::
	setmaplayoutindex LAYOUT_ALTERING_CAVE_REVEALED
	end

AlteringCave_Hidden_EventScript_SetHidden::
	setmaplayoutindex LAYOUT_ALTERING_CAVE_HIDDEN
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	setflag FLAG_TEMP_17
	setflag FLAG_TEMP_18
	setflag FLAG_TEMP_19
	setflag FLAG_TEMP_1A
	end

AlteringCave_Hidden_OnWarp:
	map_script_2 VAR_ALTERING_CAVE_STATE, 1, AlteringCave_Hidden_EventScript_SetAzurillBehindRock
	map_script_2 VAR_ALTERING_CAVE_STATE, 6, AlteringCave_Hidden_EventScript_PlayerFacesUp
	.2byte 0

AlteringCave_Hidden_EventScript_SetAzurillBehindRock::	
	setobjectxyperm LOCALID_AZURILL, 18, 18
	turnobject LOCALID_AZURILL, DIR_WEST
	removeobject LOCALID_AZURILL
	end

AlteringCave_Hidden_EventScript_PlayerFacesUp::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

AlteringCave_Hidden_OnFrame:
	map_script_2 VAR_ALTERING_CAVE_STATE, 6, AlteringCave_Hidden_EventScriptAzurillLeaves
	.2byte 0

AlteringCave_Hidden_EventScript_SenseUnusualPresence::
	lock
	msgbox AlteringCave_Hidden_Text_SenseUnusualPresense, MSGBOX_DEFAULT
	setvar VAR_ALTERING_CAVE_STATE, 2
	release
	end

AlteringCave_Hidden_EventScript_SenseMist::
	lock
	msgbox AlteringCave_Hidden_Text_SenseMist, MSGBOX_DEFAULT
	setvar VAR_ALTERING_CAVE_STATE, 3
	release
	end

AlteringCave_Hidden_EventScript_SenseWaves::
	lock
	msgbox AlteringCave_Hidden_Text_SenseWaves, MSGBOX_DEFAULT
	setvar VAR_ALTERING_CAVE_STATE, 4
	release
	end

AlteringCave_Hidden_EventScript_SenseWetFeet::
	lock
	msgbox AlteringCave_Hidden_Text_SenseWetFeet, MSGBOX_DEFAULT
	setvar VAR_ALTERING_CAVE_STATE, 5
	release
	end

AlteringCave_Hidden_EventScript_ApproachRuinManiac1::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, AlteringCave_Hidden_Movement_PlayerApproachRuinManiac1
	waitmovement 0
	goto AlteringCave_Hidden_EventScript_RuinManiac

AlteringCave_Hidden_EventScript_ApproachRuinManiac2::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, AlteringCave_Hidden_Movement_PlayerApproachRuinManiac2
	waitmovement 0
	goto AlteringCave_Hidden_EventScript_RuinManiac

AlteringCave_Hidden_EventScript_RuinManiac::
	lock
	applymovement LOCALID_RUIN_MANIAC, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox AlteringCave_Hidden_Text_RuinManiacImNotLeaving, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_OMAR, AlteringCave_Hidden_Text_OmarDefeated
	setvar VAR_ALTERING_CAVE_STATE, 6
	setflag FLAG_ALTERING_CAVE_REVEALED
	msgbox AlteringCave_Hidden_Text_RuinManiacFineIllGo, MSGBOX_AUTOCLOSE	
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement LOCALID_RUIN_MANIAC, AlteringCave_Hidden_Movement_RuinManiacDeparts
	waitmovement 0
	removeobject LOCALID_RUIN_MANIAC
	addobject LOCALID_AZURILL
	delay 30
	applymovement LOCALID_AZURILL, AlteringCave_Hidden_Movement_AzurillStepsOutOfHiding
	waitmovement 0
	playmoncry SPECIES_AZURILL, 0
	delay 30
	waitmoncry
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_AZURILL, AlteringCave_Hidden_Movement_AzurillApproachesPlayer
	waitmovement 0
	playmoncry SPECIES_AZURILL, 0
	delay 30
	waitmoncry
	msgbox AlteringCave_Hidden_Text_AzurillLooksAtYou, MSGBOX_DEFAULT
	delay 30
	@msgbox AlteringCave_Hidden_Text_FlashOfLight, MSGBOX_AUTOCLOSE
	fadescreenspeed FADE_TO_WHITE, 1
	setflag FLAG_HIDE_MAP_NAME_POPUP
	warpsilent MAP_ALTERING_CAVE_HIDDEN, 255, 18, 21
	release
	end

AlteringCave_Hidden_Movement_PlayerApproachRuinManiac1:
	walk_right
	walk_right
	walk_right
	face_up
	step_end

AlteringCave_Hidden_Movement_PlayerApproachRuinManiac2:
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

AlteringCave_Hidden_Movement_RuinManiacDeparts:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

AlteringCave_Hidden_Movement_AzurillStepsOutOfHiding:
	walk_left
	face_down
	step_end

AlteringCave_Hidden_Movement_AzurillApproachesPlayer:
	walk_down
	walk_down
	walk_right
	face_down
	step_end

AlteringCave_Hidden_EventScriptAzurillLeaves:
	lock
	delay 60
	playmoncry SPECIES_AZURILL, 0
	delay 30
	waitmoncry
	applymovement LOCALID_AZURILL, AlteringCave_Hidden_Movement_AzurillJumps
	waitmovement 0
	msgbox AlteringCave_Hidden_Text_TheIllusionWasBroken, MSGBOX_AUTOCLOSE
	addobject LOCALID_SHINY_STONE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	applymovement LOCALID_AZURILL, AlteringCave_Hidden_Movement_AzurillJumpsIntoWater
	waitmovement 0
	setvar VAR_ALTERING_CAVE_STATE, 7	
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	removeobject LOCALID_AZURILL
	clearflag FLAG_HIDDEN_ITEM_ALTERING_CAVE_LUMINOUS_MOSS
	clearflag FLAG_ITEM_ALTERING_CAVE_TM_120
	release
	end

AlteringCave_Hidden_Movement_AzurillJumps:
	jump_in_place_left_right
	jump_in_place_left_right
	face_down
	step_end

AlteringCave_Hidden_Movement_AzurillJumpsIntoWater:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	jump_right
	jump_right
	set_invisible
	step_end

AlteringCave_Hidden_Text_SenseUnusualPresense:
	.string "You sense an unusual presense here…$"

AlteringCave_Hidden_Text_SenseMist:
	.string "You feel… a cool, refreshing mist…$"

AlteringCave_Hidden_Text_SenseWaves:
	.string "You hear… waves, crawling up on shore…$"
	
AlteringCave_Hidden_Text_SenseWetFeet:
	.string "Your shoes… they're…\n"
	.string "completely soaked?$"

AlteringCave_Hidden_Text_RuinManiacImNotLeaving:
	.string "Where did it go?\n"
	.string "I don't understand…\p"
	.string "The grotto's here, I know it's here!\n"
	.string "I'm so close! I can feel it!\p"
	.string "The world must know about this\n"
	.string "mysterious wonder!\p"
	.string "I can't leave now!\p"
	.string "I won't leave now!\p"
	.string "No one will get in the way of my\n"
	.string "fame and fortune!\p"
	.string "Not even you!$"

AlteringCave_Hidden_Text_OmarDefeated:
	.string "But… my fame…$"

AlteringCave_Hidden_Text_RuinManiacFineIllGo:
	.string "…I give up.\p"
	.string "I guess it wasn't meant to be.\n"
	.string "It probably doesn't even exist.\p"
	.string "The legendary grotto is exactly that.\n"
	.string "A legend.\p"
	.string "I wouldn't waste anymore of my time\n"
	.string "here if I were you.\p"
	.string "So long! There's plenty of other\n"
	.string "discoveries to be made and shared\l"
	.string "with the world. They're waiting for me!$"

AlteringCave_Hidden_Text_AzurillLooksAtYou:
	.string "Azurill looks at you happily.\n"
	.string "It seems to trust you.$"

AlteringCave_Hidden_Text_FlashOfLight:
	.string "Suddenly…\n"
	.string "There's a flash of light!$"

AlteringCave_Hidden_Text_TheIllusionWasBroken:
	.string "The illusion was broken!$"
