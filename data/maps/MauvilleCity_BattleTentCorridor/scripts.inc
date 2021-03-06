.set LOCALID_ATTENDANT, 1

MauvilleCity_BattleTentCorridor_MapScripts:: @ 820208A
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MauvilleCity_BattleTentCorridor_OnFrame
	.byte 0

MauvilleCity_BattleTentCorridor_OnFrame: @ 8202090
	map_script_2 VAR_TEMP_0, 0, MauvilleCity_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

MauvilleCity_BattleTentCorridor_EventScript_EnterCorridor:: @ 820209A
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, MauvilleCity_BattleTentCorridor_Movement_WalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, MauvilleCity_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_MAUVILLE_CITY_BATTLE_TENT_BATTLE_ROOM, 255, 6, 5
	waitstate
	releaseall
	end

MauvilleCity_BattleTentCorridor_Movement_WalkToDoor: @ 82020DE
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

MauvilleCity_BattleTentCorridor_Movement_PlayerEnterDoor: @ 82020E3
	walk_up
MauvilleCity_BattleTentCorridor_Movement_AttendantEnterDoor: @ 82020E4
	walk_up
	set_invisible
	step_end
