.set LOCALID_ATTENDANT, 1

RustboroCity_BattleTentLobby_MapScripts:: @ 8208730
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_BattleTentLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RustboroCity_BattleTentLobby_OnWarp
	.byte 0

RustboroCity_BattleTentLobby_OnWarp: @ 820873B
	map_script_2 VAR_TEMP_1, 0, RustboroCity_BattleTentLobby_EventScript_TurnPlayerNorth
	.2byte 0

RustboroCity_BattleTentLobby_EventScript_TurnPlayerNorth:: @ 8208745
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

RustboroCity_BattleTentLobby_OnFrame: @ 820874F
	map_script_2 VAR_TEMP_0, 0, RustboroCity_BattleTentLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, RustboroCity_BattleTentLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, RustboroCity_BattleTentLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, RustboroCity_BattleTentLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, RustboroCity_BattleTentLobby_EventScript_LostChallenge
	.2byte 0

RustboroCity_BattleTentLobby_EventScript_GetChallengeStatus:: @ 8208779
	frontier_getstatus
	end

RustboroCity_BattleTentLobby_EventScript_QuitWithoutSaving:: @ 8208782
	lockall
	msgbox RustboroCity_BattleTentLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	releaseall
	end

RustboroCity_BattleTentLobby_EventScript_WonChallenge:: @ 82087B7
	lockall
	message RustboroCity_BattleTentLobby_Text_WonThreeMatchesReturnMons
	waitmessage
	slateporttent_setrandomprize
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	slateporttent_save 0
	playse SE_SAVE
	waitse
RustboroCity_BattleTentLobby_EventScript_GivePrize:: @ 82087E9
	msgbox RustboroCity_BattleTentLobby_Text_AwardYouThisPrize, MSGBOX_DEFAULT
	slateporttent_giveprize
	switch VAR_RESULT
	case FALSE, RustboroCity_BattleTentLobby_EventScript_NoRoomForPrize
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	message BattleFrontier_BattleTowerLobby_Text_ReceivedPrize  @ Odd that it uses Tower's instead of Factory's or its own
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	goto RustboroCity_BattleTentLobby_EventScript_EndGivePrize

RustboroCity_BattleTentLobby_EventScript_NoRoomForPrize:: @ 820882A
	msgbox RustboroCity_BattleTentLobby_Text_NoRoomInBagMakeRoom, MSGBOX_DEFAULT
	goto RustboroCity_BattleTentLobby_EventScript_EndGivePrize

RustboroCity_BattleTentLobby_EventScript_LostChallenge:: @ 8208837
	lockall
	message RustboroCity_BattleTentLobby_Text_ReturnRentalMonsSaveResults
	waitmessage
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	slateporttent_save 0
	playse SE_SAVE
	waitse

RustboroCity_BattleTentLobby_EventScript_EndGivePrize:: @ 8208861
	msgbox RustboroCity_BattleTentLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

RustboroCity_BattleTentLobby_EventScript_ResumeChallenge:: @ 8208871
	lockall
	message RustboroCity_BattleTentLobby_Text_BeenWaitingForYou
	waitmessage
	slateporttent_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_0, 255
	setvar VAR_0x8006, 2
	goto RustboroCity_BattleTentLobby_EventScript_EnterChallenge

RustboroCity_BattleTentLobby_EventScript_Attendant:: @ 82088AA
	lock
	faceplayer
	slateporttent_getprize
	compare VAR_RESULT, ITEM_NONE
	goto_if_ne RustboroCity_BattleTentLobby_EventScript_GivePrize
	special SavePlayerParty
	msgbox RustboroCity_BattleTentLobby_Text_WelcomeToBattleTent, MSGBOX_DEFAULT
RustboroCity_BattleTentLobby_EventScript_AskEnterChallenge:: @ 82088CA
	message RustboroCity_BattleTentLobby_Text_TakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, 0
	switch VAR_RESULT
	case 0, RustboroCity_BattleTentLobby_EventScript_TryEnterChallenge
	case 1, RustboroCity_BattleTentLobby_EventScript_ExplainChallenge
	case 2, RustboroCity_BattleTentLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, RustboroCity_BattleTentLobby_EventScript_CancelChallenge

RustboroCity_BattleTentLobby_EventScript_TryEnterChallenge:: @ 8208906
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_TENT
	msgbox RustboroCity_BattleTentLobby_Text_SaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, RustboroCity_BattleTentLobby_EventScript_LoadPartyCancelChallenge
	case YES, RustboroCity_BattleTentLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, RustboroCity_BattleTentLobby_EventScript_LoadPartyCancelChallenge

RustboroCity_BattleTentLobby_EventScript_SaveBeforeChallenge:: @ 8208950
	setvar VAR_TEMP_0, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	slateporttent_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	compare VAR_RESULT, 0
	goto_if_eq RustboroCity_BattleTentLobby_EventScript_CancelChallengeSaveFailed
	setvar VAR_0x8006, 0
RustboroCity_BattleTentLobby_EventScript_EnterChallenge:: @ 82089AC
	msgbox RustboroCity_BattleTentLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	call RustboroCity_BattleTentLobby_EventScript_WalkToDoor
	warp MAP_RUSTBORO_CITY_BATTLE_TENT_CORRIDOR, 255, 2, 7
	setvar VAR_TEMP_0, 0
	waitstate
	end

RustboroCity_BattleTentLobby_EventScript_WalkToDoor:: @ 82089C9
	applymovement LOCALID_ATTENDANT, RustboroCity_BattleTentLobby_Movement_AttendantWalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_BattleTentLobby_Movement_PlayerWalkToDoor
	waitmovement 0
	opendoor 6, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, RustboroCity_BattleTentLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_BattleTentLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 6, 1
	waitdooranim
	return

RustboroCity_BattleTentLobby_Movement_AttendantWalkToDoor: @ 82089F8
	walk_up
	walk_up
	walk_up
	step_end

RustboroCity_BattleTentLobby_Movement_AttendantEnterDoor: @ 82089FC
	walk_up
	set_invisible
	step_end

RustboroCity_BattleTentLobby_Movement_PlayerWalkToDoor: @ 82089FF
	walk_up
	walk_up
	walk_up
	step_end

RustboroCity_BattleTentLobby_Movement_PlayerEnterDoor: @ 8208A03
	walk_up
	walk_up
	set_invisible
	step_end

RustboroCity_BattleTentLobby_EventScript_ExplainChallenge:: @ 8208A07
	msgbox RustboroCity_BattleTentLobby_Text_ExplainSlateportTent, MSGBOX_DEFAULT
	goto RustboroCity_BattleTentLobby_EventScript_AskEnterChallenge

RustboroCity_BattleTentLobby_EventScript_CancelChallengeSaveFailed:: @ 8208A14
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto RustboroCity_BattleTentLobby_EventScript_CancelChallenge

RustboroCity_BattleTentLobby_EventScript_LoadPartyCancelChallenge:: @ 8208A2B
	special LoadPlayerParty
RustboroCity_BattleTentLobby_EventScript_CancelChallenge:: @ 8208A2E
	msgbox RustboroCity_BattleTentLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	release
	end

@ Unused
RustboroCity_BattleTentLobby_Movement_UnusedEnterDoor:: @ 8208A38
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

RustboroCity_BattleTentLobby_EventScript_TormentGiver:: @ 8208A3D
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM41, RustboroCity_BattleTentLobby_EventScript_ReceivedTorment
	msgbox RustboroCity_BattleTentLobby_Text_CouldntFindMonForMe, MSGBOX_DEFAULT
	giveitem ITEM_TM41
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM41
	msgbox RustboroCity_BattleTentLobby_Text_ExplainTorment, MSGBOX_DEFAULT
	release
	end

RustboroCity_BattleTentLobby_EventScript_ReceivedTorment:: @ 8208A74
	msgbox RustboroCity_BattleTentLobby_Text_ExplainTorment, MSGBOX_DEFAULT
	release
	end

RustboroCity_BattleTentLobby_EventScript_Man:: @ 8208A7E
	msgbox RustboroCity_BattleTentLobby_Text_IllTryUsingBugMons, MSGBOX_NPC
	end

RustboroCity_BattleTentLobby_EventScript_Girl:: @ 8208A87
	msgbox RustboroCity_BattleTentLobby_Text_BattleEvenWithoutToughMons, MSGBOX_NPC
	end

RustboroCity_BattleTentLobby_EventScript_Woman:: @ 8208A90
	msgbox RustboroCity_BattleTentLobby_Text_NiceIfMoreSelection, MSGBOX_NPC
	end

RustboroCity_BattleTentLobby_EventScript_RulesBoard:: @ 8208A99
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto RustboroCity_BattleTentLobby_EventScript_ReadRulesBoard
	end

RustboroCity_BattleTentLobby_EventScript_ReadRulesBoard:: @ 8208AA8
	message BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 0, MULTI_SLATEPORT_TENT_RULES, 0
	switch VAR_RESULT
	case 0, RustboroCity_BattleTentLobby_EventScript_RulesBasics
	case 1, RustboroCity_BattleTentLobby_EventScript_RulesSwapPartner
	case 2, RustboroCity_BattleTentLobby_EventScript_RulesSwapNumber
	case 3, RustboroCity_BattleTentLobby_EventScript_RulesSwapNotes
	case 4, RustboroCity_BattleTentLobby_EventScript_RulesMons
	case 5, RustboroCity_BattleTentLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, RustboroCity_BattleTentLobby_EventScript_ExitRules
	end

RustboroCity_BattleTentLobby_EventScript_RulesBasics:: @ 8208B06
	msgbox RustboroCity_BattleTentLobby_Text_ExplainBasicRules, MSGBOX_DEFAULT
	goto RustboroCity_BattleTentLobby_EventScript_ReadRulesBoard
	end

RustboroCity_BattleTentLobby_EventScript_RulesSwapPartner:: @ 8208B14
	msgbox RustboroCity_BattleTentLobby_Text_ExplainSwapPartnerRules, MSGBOX_DEFAULT
	goto RustboroCity_BattleTentLobby_EventScript_ReadRulesBoard
	end

RustboroCity_BattleTentLobby_EventScript_RulesSwapNumber:: @ 8208B22
	msgbox RustboroCity_BattleTentLobby_Text_ExplainSwapNumberRules, MSGBOX_DEFAULT
	goto RustboroCity_BattleTentLobby_EventScript_ReadRulesBoard
	end

RustboroCity_BattleTentLobby_EventScript_RulesSwapNotes:: @ 8208B30
	msgbox RustboroCity_BattleTentLobby_Text_ExplainSwapNotes, MSGBOX_DEFAULT
	goto RustboroCity_BattleTentLobby_EventScript_ReadRulesBoard
	end

RustboroCity_BattleTentLobby_EventScript_RulesMons:: @ 8208B3E
	msgbox RustboroCity_BattleTentLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
	goto RustboroCity_BattleTentLobby_EventScript_ReadRulesBoard
	end

RustboroCity_BattleTentLobby_EventScript_ExitRules:: @ 8208B4C
	releaseall
	end

RustboroCity_BattleTentLobby_Text_CouldntFindMonForMe: @ 8208B4E
	.string "So, like, I couldn't find myself any\n"
	.string "Pokémon that were, like, for me.\p"
	.string "So, I figured, like, hey, I should file\n"
	.string "a complaint to the guy there?\p"
	.string "And he wouldn't hear me out, like, hey!\n"
	.string "So, like, total bummer, man!\p"
	.string "Hey, like, you! Zip it, you know?\n"
	.string "Just, you know, take this!$"

RustboroCity_BattleTentLobby_Text_ExplainTorment: @ 8208C5C
	.string "That's, like, TM41, you know?\n"
	.string "Hey, it's Torment, you hearing me?\p"
	.string "Like, it won't let the other guy\n"
	.string "use the same move twice in a row, see?\p"
	.string "Hey, now, you listen here, like,\n"
	.string "I'm not laying a torment on you!$"

RustboroCity_BattleTentLobby_Text_IllTryUsingBugMons: @ 8208D27
	.string "I don't really like Bug Pokémon,\n"
	.string "but maybe I'll try using some for\l"
	.string "a change of pace.\p"
	.string "Who knows, I might even get to like\n"
	.string "them!$"

RustboroCity_BattleTentLobby_Text_BattleEvenWithoutToughMons: @ 8208DA6
	.string "You can battle all you want here even\n"
	.string "if you don't have any tough Pokémon.\p"
	.string "Students from the Pokémon Trainer's\n"
	.string "School come here often to practice.$"

RustboroCity_BattleTentLobby_Text_NiceIfMoreSelection: @ 8208DF1
	.string "Wouldn't it be nice if they had more of\n"
	.string "a selection?$"

