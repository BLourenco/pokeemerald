.set LOCALID_MAGMA_GRUNT_1, 5
.set LOCALID_MAGMA_GRUNT_2, 6
.set LOCALID_ARCHIE, 7
.set LOCALID_AQUA_GRUNT_1, 8
.set LOCALID_AQUA_GRUNT_2, 9
.set LOCALID_PROF_COZMO, 10
.set LOCALID_COURTNEY, 11
.set LOCALID_RIVAL, 12

MeteorFalls_1F_1R_MapScripts:: @ 822BD2A
	map_script MAP_SCRIPT_ON_LOAD, MeteorFalls_1F_1R_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, MeteorFalls_1F_1R_OnTransition
	.byte 0

MeteorFalls_1F_1R_OnLoad: @ 822BD30
	call_if_set FLAG_SYS_GAME_CLEAR, MeteorFalls_1F_1R_EventScript_OpenStevensCave
	end

MeteorFalls_1F_1R_OnTransition:
	compare VAR_METEOR_FALLS_STATE, 1
	call_if_eq MeteorFalls_1F_1R_EventScript_MoveNPCsToBattleReadyPositions
	call Common_EventScript_SetupRivalGfxId
	end

MeteorFalls_1F_1R_EventScript_MoveNPCsToBattleReadyPositions::
	setobjectxyperm LOCALID_MAGMA_GRUNT_1, 9, 23
	setobjectxyperm LOCALID_MAGMA_GRUNT_2, 10, 24
	setobjectxyperm LOCALID_COURTNEY, 10, 22
	setobjectxyperm LOCALID_RIVAL, 12, 23
	return

MeteorFalls_1F_1R_EventScript_OpenStevensCave:: @ 822BD3A
	setmetatile 4, 1, METATILE_MeteorFalls_CaveEntrance_Top, 1
	setmetatile 3, 2, METATILE_MeteorFalls_CaveEntrance_Left, 1
	setmetatile 4, 2, METATILE_MeteorFalls_CaveEntrance_Bottom, 0
	setmetatile 5, 2, METATILE_MeteorFalls_CaveEntrance_Right, 1
	return

MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene2::
	lockall
	setvar VAR_METEOR_FALLS_STATE, 1
	playbgm MUS_ENCOUNTER_MAGMA, 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	delay 30
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGrunt1StepBack
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_MagmaGruntThisKidsTough, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_RivalLetCozmoGo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COURTNEY, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_CourtneyKidsGotSpunk, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COURTNEY, MeteorFalls_1F_1R_Movement_CourtneyAndGruntStepRight
	applymovement LOCALID_MAGMA_GRUNT_2, MeteorFalls_1F_1R_Movement_CourtneyAndGruntStepRight
	waitmovement 0
	applymovement LOCALID_RIVAL, MeteorFalls_1F_1R_Movement_RivalStepBack
	waitmovement 0	
	delay 45
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	msgbox MeteorFalls_1F_1R_Text_RivalICouldUseYourHelp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestLeft
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PlayerJoinsRival
	waitmovement 0
	applymovement LOCALID_COURTNEY, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_CourneyYouBroughtAFriend, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	applymovement LOCALID_RIVAL, Common_Movement_FaceUp
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_RivalLetMeHealOurPokemon, MSGBOX_DEFAULT
	playse SE_USE_ITEM
	special HealPlayerParty
	delay 30
	goto MeteorFalls_1F_1R_EventScript_ReadyForBattlePrompt
	end

MeteorFalls_1F_1R_EventScript_ReadyForBattlePrompt::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_RivalAreYouReady, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MeteorFalls_1F_1R_EventScript_ChoosePartyForMultiBattle
	msgbox MeteorFalls_1F_1R_Text_RivalHurryUpAndGetReady, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

MeteorFalls_1F_1R_EventScript_MagmaAdminCourtneyInteract::
	faceplayer
	msgbox MeteorFalls_1F_1R_Text_MagmaAdminCourtneyInteract, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COURTNEY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	end

MeteorFalls_1F_1R_EventScript_MagmaGrunt1Interact::
	faceplayer
	msgbox MeteorFalls_1F_1R_Text_MagmaGrunt1Interact, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	end

MeteorFalls_1F_1R_EventScript_MagmaGrunt2Interact::
	faceplayer
	msgbox MeteorFalls_1F_1R_Text_MagmaGrunt2Interact, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	end

MeteorFalls_1F_1R_EventScript_ChoosePartyForMultiBattle::
    choose_mons
    compare VAR_RESULT, 0
    goto_if_eq MeteorFalls_1F_1R_CancelBattle
    goto MeteorFalls_1F_1R_EventScript_DoMeteorFallsMultiBattle
    release
    end

MeteorFalls_1F_1R_EventScript_DoMeteorFallsMultiBattle::
	compare VAR_FACING, DIR_NORTH
	call_if_eq MeteorFalls_1F_1R_EventScript_GetIntoPositionFromSouth
	compare VAR_FACING, DIR_EAST
	call_if_eq MeteorFalls_1F_1R_EventScript_GetIntoPositionFromWest
	compare VAR_FACING, DIR_WEST
	call_if_eq MeteorFalls_1F_1R_EventScript_GetIntoPositionFromEast
	compare VAR_FACING, DIR_SOUTH
	call_if_eq MeteorFalls_1F_1R_EventScript_GetIntoPositionFromNorth
	compare VAR_FACING, DIR_NONE
	call_if_eq MeteorFalls_1F_1R_EventScript_GetIntoPositionFromNorth
	msgbox MeteorFalls_1F_1R_Text_CourtneyNothingCanStopTeamMagma, MSGBOX_DEFAULT
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq MeteorFalls_1F_1R_EventScript_MayPartner
	compare VAR_RESULT, FEMALE
	goto_if_eq MeteorFalls_1F_1R_EventScript_BrendanPartner
	release
    end

MeteorFalls_1F_1R_EventScript_GetIntoPositionFromSouth::
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestLeft
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PlayerWalksToNorthOfRivalFromSouth
	waitmovement 0
	return

MeteorFalls_1F_1R_EventScript_GetIntoPositionFromWest::
	@ applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestLeft
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PlayerWalksToNorthOfRivalFromWest
	waitmovement 0
	return

MeteorFalls_1F_1R_EventScript_GetIntoPositionFromEast::
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestLeft
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PlayerWalksToNorthOfRivalFromEast
	waitmovement 0
	return

MeteorFalls_1F_1R_EventScript_GetIntoPositionFromNorth::
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

MeteorFalls_1F_1R_EventScript_BrendanPartner::
	switch VAR_STARTER_MON
	case 0, MeteorFalls_1F_1R_EventScript_BrendanPartnerTreecko
	case 1, MeteorFalls_1F_1R_EventScript_BrendanPartnerTorchic
	case 2, MeteorFalls_1F_1R_EventScript_BrendanPartnerMudkip
	end

MeteorFalls_1F_1R_EventScript_MayPartner::
	switch VAR_STARTER_MON
	case 0, MeteorFalls_1F_1R_EventScript_MayPartnerTreecko
	case 1, MeteorFalls_1F_1R_EventScript_MayPartnerTorchic
	case 2, MeteorFalls_1F_1R_EventScript_MayPartnerMudkip
	end

MeteorFalls_1F_1R_EventScript_BrendanPartnerTreecko::
	multi_2_vs_2 TRAINER_MAGMA_ADMIN_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaAdminCourtneyDefeated, TRAINER_MAGMA_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaGruntDefeated, TRAINER_BRENDAN_METEOR_FALLS_TREECKO, TRAINER_BACK_PIC_BRENDAN
	specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_LOST
    goto_if_eq MeteorFalls_1F_1R_LostMultiBattle	
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq MeteorFalls_1F_1R_WonMultiBattle
	end

MeteorFalls_1F_1R_EventScript_BrendanPartnerTorchic::
	multi_2_vs_2 TRAINER_MAGMA_ADMIN_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaAdminCourtneyDefeated, TRAINER_MAGMA_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaGruntDefeated, TRAINER_BRENDAN_METEOR_FALLS_TORCHIC, TRAINER_BACK_PIC_BRENDAN
	specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_LOST
    goto_if_eq MeteorFalls_1F_1R_LostMultiBattle	
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq MeteorFalls_1F_1R_WonMultiBattle
	end
	
MeteorFalls_1F_1R_EventScript_BrendanPartnerMudkip::
	multi_2_vs_2 TRAINER_MAGMA_ADMIN_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaAdminCourtneyDefeated, TRAINER_MAGMA_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaGruntDefeated, TRAINER_BRENDAN_METEOR_FALLS_MUDKIP, TRAINER_BACK_PIC_BRENDAN
	specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_LOST
    goto_if_eq MeteorFalls_1F_1R_LostMultiBattle	
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq MeteorFalls_1F_1R_WonMultiBattle
	end
	
MeteorFalls_1F_1R_EventScript_MayPartnerTreecko::
	multi_2_vs_2 TRAINER_MAGMA_ADMIN_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaAdminCourtneyDefeated, TRAINER_MAGMA_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaGruntDefeated, TRAINER_MAY_METEOR_FALLS_TREECKO, TRAINER_BACK_PIC_MAY
	specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_LOST
    goto_if_eq MeteorFalls_1F_1R_LostMultiBattle	
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq MeteorFalls_1F_1R_WonMultiBattle
	end

MeteorFalls_1F_1R_EventScript_MayPartnerTorchic::
	multi_2_vs_2 TRAINER_MAGMA_ADMIN_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaAdminCourtneyDefeated, TRAINER_MAGMA_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaGruntDefeated, TRAINER_MAY_METEOR_FALLS_TORCHIC, TRAINER_BACK_PIC_MAY
	specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_LOST
    goto_if_eq MeteorFalls_1F_1R_LostMultiBattle	
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq MeteorFalls_1F_1R_WonMultiBattle
	end

MeteorFalls_1F_1R_EventScript_MayPartnerMudkip::
	multi_2_vs_2 TRAINER_MAGMA_ADMIN_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaAdminCourtneyDefeated, TRAINER_MAGMA_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_MagmaGruntDefeated, TRAINER_MAY_METEOR_FALLS_MUDKIP, TRAINER_BACK_PIC_MAY
	specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_LOST
    goto_if_eq MeteorFalls_1F_1R_LostMultiBattle	
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq MeteorFalls_1F_1R_WonMultiBattle
	end

MeteorFalls_1F_1R_CancelBattle::
    msgbox MeteorFalls_1F_1R_Text_RivalHurryUpAndGetReady, MSGBOX_DEFAULT
	closemessage	
	applymovement LOCALID_RIVAL, Common_Movement_FaceLeft
	waitmovement 0
    release
    end

MeteorFalls_1F_1R_LostMultiBattle::
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate
	end

MeteorFalls_1F_1R_WonMultiBattle::
	lockall
	setvar VAR_METEOR_FALLS_STATE, 2
	applymovement LOCALID_COURTNEY, MeteorFalls_1F_1R_Movement_MagmaGrunt1StepBack
	applymovement LOCALID_MAGMA_GRUNT_2, MeteorFalls_1F_1R_Movement_MagmaGrunt1StepBack
	waitmovement 0
	applymovement LOCALID_COURTNEY, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_CourtneyWhyMustYouGetInOurWay, MSGBOX_DEFAULT
	closemessage
	delay 30	
	fadeoutbgm 0
	msgbox MeteorFalls_1F_1R_Text_ArchieOffscreenHoldItRightThere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COURTNEY, Common_Movement_WalkInPlaceFastestLeft	
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_COURTNEY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFastestLeft	
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFastestLeft	
	waitmovement 0
	applymovement LOCALID_PROF_COZMO, Common_Movement_WalkInPlaceFastestLeft	
	waitmovement 0
	addobject LOCALID_ARCHIE
	addobject LOCALID_AQUA_GRUNT_1
	addobject LOCALID_AQUA_GRUNT_2
	playbgm MUS_ENCOUNTER_AQUA, 0
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_TeamAquaArrive
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_TeamAquaArrive
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_TeamAquaArrive
	waitmovement 0
	applymovement LOCALID_COURTNEY, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_CourtneyYouveGotToBeKiddingMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieYoureBadlyMistaken, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COURTNEY, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_CourtneyYoureOneToTalk, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COURTNEY, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_CourtneyGrabTheMeteorite, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement LOCALID_PROF_COZMO, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ProfCozmoNoMyMeteorite, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COURTNEY, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_CourtneySeeYaAqua, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PlayerWatchMagmaWalkBy
	applymovement LOCALID_RIVAL, MeteorFalls_1F_1R_Movement_PushRivalOutOfWay
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit
	applymovement LOCALID_MAGMA_GRUNT_2, MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit
	applymovement LOCALID_COURTNEY, MeteorFalls_1F_1R_Movement_CourtneyExit
	waitmovement 0
	removeobject LOCALID_COURTNEY
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_MAGMA_GRUNT_2
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PlayerFaceArchie
	applymovement LOCALID_RIVAL, MeteorFalls_1F_1R_Movement_RivalFaceArchie
	applymovement LOCALID_PROF_COZMO, MeteorFalls_1F_1R_Movement_PushCozmoOutOfWay
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieApproachPlayer
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachPlayer
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieSeenYouBefore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_AQUA_GRUNT_1, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceRight
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceRight
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieExit
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Exit
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Exit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_AQUA_GRUNT_1
	removeobject LOCALID_AQUA_GRUNT_2
	delay 30
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_RivalCozmoAreYouOkay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, MeteorFalls_1F_1R_Movement_RivalApproachCozmo
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PlayerApproachCozmo
	waitmovement 0
	applymovement LOCALID_PROF_COZMO, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ProfCozmoImOkay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_RivalTeamMagmaTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 30
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_RivalIllTakeCozmoHome, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceRight
	applymovement LOCALID_RIVAL, MeteorFalls_1F_1R_Movement_RivalExit
	applymovement LOCALID_PROF_COZMO, MeteorFalls_1F_1R_Movement_CozmoExit
	waitmovement 0
	removeobject LOCALID_RIVAL
	removeobject LOCALID_PROF_COZMO
	setflag FLAG_HIDE_ROUTE_112_TEAM_MAGMA
	setflag FLAG_MET_ARCHIE_METEOR_FALLS
	setflag FLAG_SAVED_PROF_COZMO
	setflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_RIVAL
	releaseall 
	end

MeteorFalls_1F_1R_Movement_MagmaGrunt1StepBack:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

MeteorFalls_1F_1R_Movement_CourtneyAndGruntStepRight:
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_RivalStepBack:
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

MeteorFalls_1F_1R_Movement_PlayerJoinsRival:
	walk_left
	walk_left
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt2JoinsCourtney:
	walk_up
	face_right
	step_end

MeteorFalls_1F_1R_Movement_PlayerWalksToNorthOfRivalFromSouth:
	walk_right
	walk_up
	walk_up
	walk_left
	step_end

MeteorFalls_1F_1R_Movement_PlayerWalksToNorthOfRivalFromWest:
	walk_up
	walk_right
	face_left
	step_end

MeteorFalls_1F_1R_Movement_PlayerWalksToNorthOfRivalFromEast:
	walk_up
	walk_left
	step_end

MeteorFalls_1F_1R_Movement_TeamAquaArrive:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_CourtneyExit:
	face_down
	delay_16
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit:
	face_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_PlayerWatchMagmaWalkBy:
	delay_16
	delay_16
	face_down
	delay_16
	delay_16
	face_right
	step_end
	
MeteorFalls_1F_1R_Movement_PushRivalOutOfWay:
	delay_16
	delay_16
	walk_in_place_fastest_up
	lock_facing_direction
	walk_down
	unlock_facing_direction
	face_up
	delay_16
	delay_16
	face_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieApproachPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachPlayer:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachPlayer:
	face_up
	delay_16
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_PushCozmoOutOfWay:
	delay_16
	walk_in_place_fastest_up
	lock_facing_direction
	walk_down
	unlock_facing_direction
	face_up
	step_end

MeteorFalls_1F_1R_Movement_PlayerFaceArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	step_end

MeteorFalls_1F_1R_Movement_RivalFaceArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_up
	step_end

MeteorFalls_1F_1R_Movement_ArchieExit:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Exit:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Exit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_RivalApproachCozmo:
	walk_left
	walk_left
	walk_left
	step_end

MeteorFalls_1F_1R_Movement_PlayerApproachCozmo:
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MeteorFalls_1F_1R_Movement_RivalExit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_CozmoExit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Text_MagmaGruntThisKidsTough:
	.string "Tch!\n"
	.string "This kid's tough!$"

MeteorFalls_1F_1R_Text_RivalLetCozmoGo:
	.string "{RIVAL}: There's more where that\n"
	.string "came from!\p"
	.string "Now let Prof. Cozmo go!$"

MeteorFalls_1F_1R_Text_CourtneyKidsGotSpunk:
	.string "Courtney: Aww… The kid's got some\n"
	.string "spunk!\p"
	.string "Listen here, all we're interested\n"
	.string "in is the Meteorite.\p"
	.string "Once pointdexter here decides to hand\n"
	.string "it over, we'll be on our way, and\l"
	.string "there's nothing you can do about it!$"

MeteorFalls_1F_1R_Text_RivalICouldUseYourHelp:
	.string "{RIVAL}: {PLAYER}!\p"
	.string "Am I glad to see you!\n"
	.string "Mind giving me a hand with these thugs?$"

MeteorFalls_1F_1R_Text_CourneyYouBroughtAFriend:
	.string "Courtney: Oh, you brought a friend!\n"
	.string "How sweet!$"

MeteorFalls_1F_1R_Text_RivalLetMeHealOurPokemon:
	.string "{RIVAL}: Here, let me heal our\n"
	.string "Pokémon first.$"

MeteorFalls_1F_1R_Text_RivalAreYouReady:
	.string "Are you ready for battle?$"

MeteorFalls_1F_1R_Text_RivalHurryUpAndGetReady:
	.string "{RIVAL}: Don't take too long!\n"
	.string "I can't take them on myself!$"

MeteorFalls_1F_1R_Text_MagmaAdminCourtneyInteract:
	.string "Courtney: All we want is the\n"
	.string "Meteorite.\p"
	.string "We'll be on our way once we have it.$"

MeteorFalls_1F_1R_Text_MagmaGrunt1Interact:
	.string "That kid wiped out my team like it was\n"
	.string "nothing.\p"
	.string "When did kids get so strong?$"

MeteorFalls_1F_1R_Text_MagmaGrunt2Interact:
	.string "You don't want to mess with\n"
	.string "Courtney, trust me.$"

MeteorFalls_1F_1R_Text_CourtneyNothingCanStopTeamMagma:
	.string "Courtney: It takes guts to oppose us.\p"
	.string "No matter. No one can stop the will\n"
	.string "of Team Magma!\p"
	.string "Not even you!$"

MeteorFalls_1F_1R_Text_MagmaGruntDefeated:
	.string "Not good…$"

MeteorFalls_1F_1R_Text_MagmaAdminCourtneyDefeated:
	.string "Grrr…\n"
	.string "How frustrating!$"

MeteorFalls_1F_1R_Text_CourtneyWhyMustYouGetInOurWay:
	.string "Courtney: Why must you get in our way?\p"
	.string "Do you not realize that we, Team Magma,\n"
	.string "strive for the betterment of all life\l"
	.string "in Hoenn?\p"
	.string "With the power of the Meteorite,\n"
	.string "we'll be able to control…$"

MeteorFalls_1F_1R_Text_ArchieOffscreenHoldItRightThere:
	.string "???: Hold it right there, Team Magma!$"

MeteorFalls_1F_1R_Text_CourtneyYouveGotToBeKiddingMe:
	.string "Courtney: You've got to be kidding me…\n"
	.string "First these brats, and now Team Aqua!$"

MeteorFalls_1F_1R_Text_ArchieYoureBadlyMistaken:
	.string "Archie: You're badly mistaken if you\n"
	.string "think you can have your way with Hoenn!$"

MeteorFalls_1F_1R_Text_CourtneyYoureOneToTalk:
	.string "Courtney: You're one to talk!\p"
	.string "We fight for the people and Pokémon of\n"
	.string "Hoenn, and all you do is try and get\l"
	.string "in our way!\p"
	.string "But it's too much trouble to deal with\n"
	.string "you all right now…$"

MeteorFalls_1F_1R_Text_CourtneyGrabTheMeteorite:
	.string "Courtney: We need to get back to\n"
	.string "Mt. Chimney, snatch that Meteorite\l"
	.string "from our friend here and let's scram!$"

MeteorFalls_1F_1R_Text_ProfCozmoNoMyMeteorite:
	.string "Prof. Cozmo: N-no! My Meteorite!$"

MeteorFalls_1F_1R_Text_CourtneySeeYaAqua:
	.string "Courtney: We have what we came for.\p"
	.string "Be seeing you, you Team Aqua dingbats!$"

MeteorFalls_1F_1R_Text_ArchieSeenYouBefore:
	.string "Archie: Hey, you!\p"
	.string "Haven't I seen you before?\n"
	.string "At Slateport's Museum?\p"
	.string "Ah, so your name is {PLAYER}.\p"
	.string "At the time, I thought you were one\n"
	.string "of Team Magma's goons.\p"
	.string "Humph…\n"
	.string "You're one odd kid.\p"
	.string "Team Magma is a dangerous group of\n"
	.string "total fanatics.\p"
	.string "They claim to be helping people and\n"
	.string "Pokémon by expanding Hoenn's\l"
	.string "landmass, but what they're really\l"
	.string "bringing is destruction!\p"
	.string "They stand in direct opposition to us,\n"
	.string "the sea-loving Team Aqua!$"

MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma: @ 822C268
	.string "Boss, we should give chase to\n"
	.string "Team Magma…$"

MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo: @ 822C292
	.string "Archie: Yes, yes, we must!\n"
	.string "We've got to hurry.\p"
	.string "There's no telling what Team Magma\n"
	.string "will do at Mt. Chimney!$"

MeteorFalls_1F_1R_Text_ArchieFarewell: @ 822C2FC
	.string "Archie: {PLAYER}, you should keep\n"
	.string "an eye out for Team Magma, too.\p"
	.string "Farewell!$"

MeteorFalls_1F_1R_Text_RivalCozmoAreYouOkay:
	.string "{RIVAL}: Prof. Cozmo!\n"
	.string "Are you okay?$"

MeteorFalls_1F_1R_Text_ProfCozmoImOkay:
	.string "Prof. Cozmo: I'm… I'm okay.\p"
	.string "… … … … … …\p"
	.string "Thank you for saving me.\p"
	.string "Team Magma asked me to guide them\n"
	.string "to Meteor Falls…\p"
	.string "But they tricked me,\n"
	.string "and stole my Meteorite…\p"
	.string "What are they going to do with my\n"
	.string "Meteorite at Mt. Chimney?$"

MeteorFalls_1F_1R_Text_RivalTeamMagmaTeamAqua:
	.string "{RIVAL}: Team Magma?\n"
	.string "Team Aqua?\p"
	.string "Who are these people?\p"
	.string "They claim they're saving Hoenn,\n"
	.string "but from what?\p"
	.string "I don't understand…$"

MeteorFalls_1F_1R_Text_RivalIllTakeCozmoHome:
	.string "{RIVAL}: I'm going to take\n"
	.string "Prof. Cozmo home.\p"
	.string "I think I'll stay with him for a bit\n"
	.string "in case any of those goons come back.\p"
	.string "You should head for Mt. Chimney,\n"
	.string "though.\p"
	.string "I don't know what Team Magma plans\n"
	.string "to do with that Meteorite, but they\l"
	.string "can't be ignored.\p"
	.string "Good luck, {PLAYER}.$"
