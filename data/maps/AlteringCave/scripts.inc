.set LOCALID_RUIN_MANIAC, 1
.set LOCALID_AZURILL, 2

AlteringCave_MapScripts:: @ 823B177
	map_script MAP_SCRIPT_ON_TRANSITION, AlteringCave_OnTransition
	.byte 0

AlteringCave_OnTransition: @ 823B17D
	setflag FLAG_LANDMARK_ALTERING_CAVE
	end

AlteringCave_EventScript_StartTrigger::
	lock
	applymovement LOCALID_RUIN_MANIAC, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RUIN_MANIAC, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RUIN_MANIAC, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_RUIN_MANIAC, AlteringCave_Movement_RuinManiacApproach
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox AlteringCave_Text_RuinManiacIntro, MSGBOX_AUTOCLOSE
	playse SE_EXIT
	addobject LOCALID_AZURILL
	applymovement LOCALID_AZURILL, AlteringCave_Movement_AzurillAppearsAndFlees1
	waitmovement 0
	delay 30
	applymovement LOCALID_RUIN_MANIAC, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RUIN_MANIAC, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 30
	applymovement LOCALID_AZURILL, AlteringCave_Movement_AzurillAppearsAndFlees2
	waitmovement 0
	delay 30
	applymovement LOCALID_AZURILL, AlteringCave_Movement_AzurillAppearsAndFlees3
	waitmovement 0
	delay 30
	applymovement LOCALID_AZURILL, AlteringCave_Movement_AzurillAppearsAndFlees4
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_AZURILL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_AZURILL, Common_Movement_Delay48
	waitmovement 0
	delay 30
	playmoncry SPECIES_AZURILL, 0
	delay 30
	waitmoncry
	applymovement LOCALID_AZURILL, AlteringCave_Movement_AzurillAppearsAndFlees5
	waitmovement 0
	removeobject LOCALID_AZURILL
	playse SE_EXIT
	delay 30
	msgbox AlteringCave_Text_RuinManiacThatWasAPokemon, MSGBOX_DEFAULT
	applymovement LOCALID_RUIN_MANIAC, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0	
	msgbox AlteringCave_Text_RuinManiacIsItPossible, MSGBOX_DEFAULT
	applymovement LOCALID_RUIN_MANIAC, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox AlteringCave_Text_RuinManiacFameAndFortune, MSGBOX_AUTOCLOSE
	applymovement LOCALID_RUIN_MANIAC, AlteringCave_Movement_RuinManiac_ChaseAzurill
	waitmovement 0
	removeobject LOCALID_RUIN_MANIAC
	playse SE_EXIT
	setvar VAR_ALTERING_CAVE_STATE, 1
	releaseall
	end

AlteringCave_Movement_RuinManiacApproach:
	walk_left
	walk_left
	face_down
	step_end

AlteringCave_Movement_RuinManiac_ChaseAzurill:
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

AlteringCave_Movement_AzurillAppearsAndFlees1:
	walk_down
	face_right
	step_end

AlteringCave_Movement_AzurillAppearsAndFlees2:
	walk_down
	walk_down
	face_down
	face_right
	step_end

AlteringCave_Movement_AzurillAppearsAndFlees3:
	face_left
	step_end

AlteringCave_Movement_AzurillAppearsAndFlees4:
	face_down
	delay_16
	face_left
	step_end

AlteringCave_Movement_AzurillAppearsAndFlees5:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

AlteringCave_Text_RuinManiacIntro:
	.string "You, there!\p"
	.string "You're here because of the legends,\n"
	.string "correct?\p"
	.string "It's been said that deep within this\n"
	.string "cave is a beautiful, lush grotto that is\l"
	.string "home to many rare Pokémon!\p"
	.string "Very few have actually set eyes on it.\n"
	.string "Supposedly it's quite a sight to behold!\p"
	.string "I am going to be the first one to reveal\n"
	.string "it to the world! It'll be the discovery\l"
	.string "of the century! I'll be famous!\p"
	.string "Unfortunately… so far it seems that it's\n"
	.string "just a legend…\p"
	.string "After spending days in the deepest\n"
	.string "part of the cave, I have not seen\l"
	.string "anything to suggest such a place\l"
	.string "even exists!\p"
	.string "No crystal-clear waters, not a single\n"
	.string "blade of grass, and not one Pokémon!$"

AlteringCave_Text_RuinManiacThatWasAPokemon:
	.string "That…\p"
	.string "That was a Pokémon!$"

AlteringCave_Text_RuinManiacIsItPossible:
	.string "Is it possible?\n"
	.string "Has the grotto appeared?\p"
	.string "There's no time to waste!\n"
	.string "I must see it!$"

AlteringCave_Text_RuinManiacFameAndFortune:
	.string "Fame and fortune, here I come!$"
