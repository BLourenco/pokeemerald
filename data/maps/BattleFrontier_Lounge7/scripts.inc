BattleFrontier_Lounge7_MapScripts:: @ 8265254
	.byte 0

@ FREE TUTOR SCRIPTS

BattleFrontier_Lounge7_EventScript_MoveTutor_Free:: @ 8265255
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_FREE
	goto_if_set FLAG_MET_FRONTIER_MOVE_TUTOR_FREE, BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Free
	msgbox BattleFrontier_Lounge7_Text_TutorIntro_Free, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_MOVE_TUTOR_FREE
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Free
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Free:: @ 8265276
	msgbox BattleFrontier_Lounge7_Text_TutorWelcomeBack_Free, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Free
	end

BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Free:: @ 8265284
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_FREE
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Softboiled
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 5, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 6, BattleFrontier_Lounge7_EventScript_MegaKick
	case 7, BattleFrontier_Lounge7_EventScript_Endure
	case 8, BattleFrontier_Lounge7_EventScript_PsychUp
	case 9, BattleFrontier_Lounge7_EventScript_BodySlam
	case 10, BattleFrontier_Lounge7_EventScript_Counter
	case 11, BattleFrontier_Lounge7_EventScript_DynamicPunch
	case 12, BattleFrontier_Lounge7_EventScript_DoubleEdge
	case 13, BattleFrontier_Lounge7_EventScript_Rollout
	case 14, BattleFrontier_Lounge7_EventScript_FuryCutter
	case 15, BattleFrontier_Lounge7_EventScript_Metronome
	case 16, BattleFrontier_Lounge7_EventScript_Mimic
	case 17, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Free:: @ 826532F
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_FREE
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Softboiled
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 5, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 6, BattleFrontier_Lounge7_EventScript_MegaKick
	case 7, BattleFrontier_Lounge7_EventScript_Endure
	case 8, BattleFrontier_Lounge7_EventScript_PsychUp
	case 9, BattleFrontier_Lounge7_EventScript_BodySlam
	case 10, BattleFrontier_Lounge7_EventScript_Counter
	case 11, BattleFrontier_Lounge7_EventScript_DynamicPunch
	case 12, BattleFrontier_Lounge7_EventScript_DoubleEdge
	case 13, BattleFrontier_Lounge7_EventScript_Rollout
	case 14, BattleFrontier_Lounge7_EventScript_FuryCutter
	case 15, BattleFrontier_Lounge7_EventScript_Metronome
	case 16, BattleFrontier_Lounge7_EventScript_Mimic
	case 17, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

@ SPECIAL TUTOR SCRIPTS

BattleFrontier_Lounge7_EventScript_MoveTutor_Special:: @ 8265445
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_SPECIAL
	goto_if_set FLAG_MET_FRONTIER_MOVE_TUTOR_SPECIAL, BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Special
	msgbox BattleFrontier_Lounge7_Text_TutorIntro_Special, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_MOVE_TUTOR_SPECIAL
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Special
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Special:: @ 8265466
	msgbox BattleFrontier_Lounge7_Text_TutorWelcomeBack_Special, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Special
	end

BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Special:: @ 8265474
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_SPECIAL
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_GrassPledge
	case 1, BattleFrontier_Lounge7_EventScript_FirePledge
	case 2, BattleFrontier_Lounge7_EventScript_WaterPledge
	case 3, BattleFrontier_Lounge7_EventScript_FrenzyPlant
	case 4, BattleFrontier_Lounge7_EventScript_BlastBurn
	case 5, BattleFrontier_Lounge7_EventScript_HydroCannon
	case 6, BattleFrontier_Lounge7_EventScript_DracoMeteor
	case 7, BattleFrontier_Lounge7_EventScript_RelicSong
	case 8, BattleFrontier_Lounge7_EventScript_SecretSword
	case 9, BattleFrontier_Lounge7_EventScript_DragonAscent
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Special:: @ 826551F
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_SPECIAL
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_GrassPledge
	case 1, BattleFrontier_Lounge7_EventScript_FirePledge
	case 2, BattleFrontier_Lounge7_EventScript_WaterPledge
	case 3, BattleFrontier_Lounge7_EventScript_FrenzyPlant
	case 4, BattleFrontier_Lounge7_EventScript_BlastBurn
	case 5, BattleFrontier_Lounge7_EventScript_HydroCannon
	case 6, BattleFrontier_Lounge7_EventScript_DracoMeteor
	case 7, BattleFrontier_Lounge7_EventScript_RelicSong
	case 8, BattleFrontier_Lounge7_EventScript_SecretSword
	case 9, BattleFrontier_Lounge7_EventScript_DragonAscent
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

@ OFFENSE 1/2 TUTOR SCRIPTS

BattleFrontier_Lounge7_EventScript_MoveTutor_Offense1:: @ 8265445
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_OFFENSE_1
	goto_if_set FLAG_MET_FRONTIER_MOVE_TUTOR_OFFENSE_1, BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Offense1
	msgbox BattleFrontier_Lounge7_Text_TutorIntro_Offense1, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_MOVE_TUTOR_OFFENSE_1
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Offense1
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Offense1:: @ 8265466
	msgbox BattleFrontier_Lounge7_Text_TutorWelcomeBack_Offense1, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Offense1
	end

BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Offense1:: @ 8265474
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 2
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_OFFENSE_1
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Uproar
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_Bounce
	case 3, BattleFrontier_Lounge7_EventScript_LowKick
	case 4, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 5, BattleFrontier_Lounge7_EventScript_FirePunch
	case 6, BattleFrontier_Lounge7_EventScript_IcePunch
	case 7, BattleFrontier_Lounge7_EventScript_DrainPunch
	case 8, BattleFrontier_Lounge7_EventScript_HeatWave
	case 9, BattleFrontier_Lounge7_EventScript_EarthPower
	case 10, BattleFrontier_Lounge7_EventScript_KnockOff
	case 11, BattleFrontier_Lounge7_EventScript_SuperFang
	case 12, BattleFrontier_Lounge7_EventScript_DualChop
	case 13, BattleFrontier_Lounge7_EventScript_ThroatChop
	case 14, BattleFrontier_Lounge7_EventScript_SkyDrop
	case 15, BattleFrontier_Lounge7_EventScript_Endeavor
	case 16, BattleFrontier_Lounge7_EventScript_Liquidation
	case 17, BattleFrontier_Lounge7_EventScript_SludgeWave
	case 18, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Offense1:: @ 826551F
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 2
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_OFFENSE_1
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Uproar
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_Bounce
	case 3, BattleFrontier_Lounge7_EventScript_LowKick
	case 4, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 5, BattleFrontier_Lounge7_EventScript_FirePunch
	case 6, BattleFrontier_Lounge7_EventScript_IcePunch
	case 7, BattleFrontier_Lounge7_EventScript_DrainPunch
	case 8, BattleFrontier_Lounge7_EventScript_HeatWave
	case 9, BattleFrontier_Lounge7_EventScript_EarthPower
	case 10, BattleFrontier_Lounge7_EventScript_KnockOff
	case 11, BattleFrontier_Lounge7_EventScript_SuperFang
	case 12, BattleFrontier_Lounge7_EventScript_DualChop
	case 13, BattleFrontier_Lounge7_EventScript_ThroatChop
	case 14, BattleFrontier_Lounge7_EventScript_SkyDrop
	case 15, BattleFrontier_Lounge7_EventScript_Endeavor
	case 16, BattleFrontier_Lounge7_EventScript_Liquidation
	case 17, BattleFrontier_Lounge7_EventScript_SludgeWave
	case 18, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

@  OFFENSE 2/2 TUTOR SCRIPTS

BattleFrontier_Lounge7_EventScript_MoveTutor_Offense2:: @ 8265445
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_OFFENSE_2
	goto_if_set FLAG_MET_FRONTIER_MOVE_TUTOR_OFFENSE_2, BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Offense2
	msgbox BattleFrontier_Lounge7_Text_TutorIntro_Offense2, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_MOVE_TUTOR_OFFENSE_2
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Offense2
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Offense2:: @ 8265466
	msgbox BattleFrontier_Lounge7_Text_TutorWelcomeBack_Offense2, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Offense2
	end

BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Offense2:: @ 8265474
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 3
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_OFFENSE_2
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_BugBite
	case 1, BattleFrontier_Lounge7_EventScript_Fling
	case 2, BattleFrontier_Lounge7_EventScript_DrillRun
	case 3, BattleFrontier_Lounge7_EventScript_IronHead
	case 4, BattleFrontier_Lounge7_EventScript_ZenHeadbutt
	case 5, BattleFrontier_Lounge7_EventScript_SignalBeam
	case 6, BattleFrontier_Lounge7_EventScript_BrutalSwing
	case 7, BattleFrontier_Lounge7_EventScript_HyperVoice
	case 8, BattleFrontier_Lounge7_EventScript_AquaTail
	case 9, BattleFrontier_Lounge7_EventScript_DragonPulse
	case 10, BattleFrontier_Lounge7_EventScript_SeedBomb
	case 11, BattleFrontier_Lounge7_EventScript_LastResort
	case 12, BattleFrontier_Lounge7_EventScript_FoulPlay
	case 13, BattleFrontier_Lounge7_EventScript_StompingTantrum
	case 14, BattleFrontier_Lounge7_EventScript_Outrage
	case 15, BattleFrontier_Lounge7_EventScript_Superpower
	case 16, BattleFrontier_Lounge7_EventScript_GunkShot
	case 17, BattleFrontier_Lounge7_EventScript_SkyAttack
	case 18, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Offense2:: @ 826551F
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 3
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_OFFENSE_2
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_BugBite
	case 1, BattleFrontier_Lounge7_EventScript_Fling
	case 2, BattleFrontier_Lounge7_EventScript_DrillRun
	case 3, BattleFrontier_Lounge7_EventScript_IronHead
	case 4, BattleFrontier_Lounge7_EventScript_ZenHeadbutt
	case 5, BattleFrontier_Lounge7_EventScript_SignalBeam
	case 6, BattleFrontier_Lounge7_EventScript_BrutalSwing
	case 7, BattleFrontier_Lounge7_EventScript_HyperVoice
	case 8, BattleFrontier_Lounge7_EventScript_AquaTail
	case 9, BattleFrontier_Lounge7_EventScript_DragonPulse
	case 10, BattleFrontier_Lounge7_EventScript_SeedBomb
	case 11, BattleFrontier_Lounge7_EventScript_LastResort
	case 12, BattleFrontier_Lounge7_EventScript_FoulPlay
	case 13, BattleFrontier_Lounge7_EventScript_StompingTantrum
	case 14, BattleFrontier_Lounge7_EventScript_Outrage
	case 15, BattleFrontier_Lounge7_EventScript_Superpower
	case 16, BattleFrontier_Lounge7_EventScript_GunkShot
	case 17, BattleFrontier_Lounge7_EventScript_SkyAttack
	case 18, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

@ STATUS TUTOR SCRIPTS

BattleFrontier_Lounge7_EventScript_MoveTutor_Status:: @ 8265445
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_STATUS
	goto_if_set FLAG_MET_FRONTIER_MOVE_TUTOR_STATUS, BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Status
	msgbox BattleFrontier_Lounge7_Text_TutorIntro_Status, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_MOVE_TUTOR_STATUS
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Status
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Status:: @ 8265466
	msgbox BattleFrontier_Lounge7_Text_TutorWelcomeBack_Status, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Status
	end

BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Status:: @ 8265474
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 4
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_STATUS
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Bind
	case 1, BattleFrontier_Lounge7_EventScript_Infestation
	case 2, BattleFrontier_Lounge7_EventScript_Covet
	case 3, BattleFrontier_Lounge7_EventScript_Block
	case 4, BattleFrontier_Lounge7_EventScript_Quash
	case 5, BattleFrontier_Lounge7_EventScript_RolePlay
	case 6, BattleFrontier_Lounge7_EventScript_PainSplit
	case 7, BattleFrontier_Lounge7_EventScript_GastroAcid
	case 8, BattleFrontier_Lounge7_EventScript_WorrySeed
	case 9, BattleFrontier_Lounge7_EventScript_Spite
	case 10, BattleFrontier_Lounge7_EventScript_Trick
	case 11, BattleFrontier_Lounge7_EventScript_Embargo
	case 12, BattleFrontier_Lounge7_EventScript_MagicCoat
	case 13, BattleFrontier_Lounge7_EventScript_Telekinesis
	case 14, BattleFrontier_Lounge7_EventScript_Electroweb
	case 15, BattleFrontier_Lounge7_EventScript_IcyWind
	case 16, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Status:: @ 826551F
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 4
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_STATUS
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Bind
	case 1, BattleFrontier_Lounge7_EventScript_Infestation
	case 2, BattleFrontier_Lounge7_EventScript_Covet
	case 3, BattleFrontier_Lounge7_EventScript_Block
	case 4, BattleFrontier_Lounge7_EventScript_Quash
	case 5, BattleFrontier_Lounge7_EventScript_RolePlay
	case 6, BattleFrontier_Lounge7_EventScript_PainSplit
	case 7, BattleFrontier_Lounge7_EventScript_GastroAcid
	case 8, BattleFrontier_Lounge7_EventScript_WorrySeed
	case 9, BattleFrontier_Lounge7_EventScript_Spite
	case 10, BattleFrontier_Lounge7_EventScript_Trick
	case 11, BattleFrontier_Lounge7_EventScript_Embargo
	case 12, BattleFrontier_Lounge7_EventScript_MagicCoat
	case 13, BattleFrontier_Lounge7_EventScript_Telekinesis
	case 14, BattleFrontier_Lounge7_EventScript_Electroweb
	case 15, BattleFrontier_Lounge7_EventScript_IcyWind
	case 16, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

@ SUPPORT TUTOR SCRIPTS

BattleFrontier_Lounge7_EventScript_MoveTutor_Support:: @ 8265445
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_SUPPORT
	goto_if_set FLAG_MET_FRONTIER_MOVE_TUTOR_SUPPORT, BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Support
	msgbox BattleFrontier_Lounge7_Text_TutorIntro_Support, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_MOVE_TUTOR_SUPPORT
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Support
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetTutor_Support:: @ 8265466
	msgbox BattleFrontier_Lounge7_Text_TutorWelcomeBack_Support, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Support
	end

BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Support:: @ 8265474
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 5
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_SUPPORT
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_HoneClaws
	case 1, BattleFrontier_Lounge7_EventScript_IronDefense
	case 2, BattleFrontier_Lounge7_EventScript_LaserFocus
	case 3, BattleFrontier_Lounge7_EventScript_HealBell
	case 4, BattleFrontier_Lounge7_EventScript_MagicRoom
	case 5, BattleFrontier_Lounge7_EventScript_WonderRoom
	case 6, BattleFrontier_Lounge7_EventScript_Gravity
	case 7, BattleFrontier_Lounge7_EventScript_MagnetRise
	case 8, BattleFrontier_Lounge7_EventScript_Recycle
	case 9, BattleFrontier_Lounge7_EventScript_AfterYou
	case 10, BattleFrontier_Lounge7_EventScript_HelpingHand
	case 11, BattleFrontier_Lounge7_EventScript_Synthesis
	case 12, BattleFrontier_Lounge7_EventScript_Defog
	case 13, BattleFrontier_Lounge7_EventScript_AllySwitch
	case 14, BattleFrontier_Lounge7_EventScript_Tailwind
	case 15, BattleFrontier_Lounge7_EventScript_StealthRock
	case 16, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Support:: @ 826551F
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 5
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_SUPPORT
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_HoneClaws
	case 1, BattleFrontier_Lounge7_EventScript_IronDefense
	case 2, BattleFrontier_Lounge7_EventScript_LaserFocus
	case 3, BattleFrontier_Lounge7_EventScript_HealBell
	case 4, BattleFrontier_Lounge7_EventScript_MagicRoom
	case 5, BattleFrontier_Lounge7_EventScript_WonderRoom
	case 6, BattleFrontier_Lounge7_EventScript_Gravity
	case 7, BattleFrontier_Lounge7_EventScript_MagnetRise
	case 8, BattleFrontier_Lounge7_EventScript_Recycle
	case 9, BattleFrontier_Lounge7_EventScript_AfterYou
	case 10, BattleFrontier_Lounge7_EventScript_HelpingHand
	case 11, BattleFrontier_Lounge7_EventScript_Synthesis
	case 12, BattleFrontier_Lounge7_EventScript_Defog
	case 13, BattleFrontier_Lounge7_EventScript_AllySwitch
	case 14, BattleFrontier_Lounge7_EventScript_Tailwind
	case 15, BattleFrontier_Lounge7_EventScript_StealthRock
	case 16, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end


@ SHARED TUTOR SCRIPTS

BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect:: @ 8265635
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_CancelChooseMon:: @ 8265645
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8008 is the price
@ VAR_TEMP_C is the scroll multichoice ID
@ VAR_TEMP_D is the move selection
@ VAR_TEMP_E is which move tutor was spoken to
BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection:: @ 826564F
	copyvar VAR_0x8004, VAR_TEMP_D
	copyvar VAR_0x8005, VAR_TEMP_E
	special BufferBattleFrontierTutorMoveName
	buffernumberstring 1, VAR_0x8008
	copyvar VAR_0x8004, VAR_TEMP_C
	msgbox BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseNewMove
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	compare VAR_TEMP_1, VAR_0x8008
	goto_if_ge BattleFrontier_Lounge7_EventScript_TeachTutorMove
	msgbox BattleFrontier_Lounge7_Text_HaventGotEnoughPoints, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseNewMove
	end

BattleFrontier_Lounge7_EventScript_TeachTutorMove:: @ 8265696
	msgbox BattleFrontier_Lounge7_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	special GetBattleFrontierTutorMoveIndex
	fadescreen FADE_TO_BLACK
	special CloseBattlePointsWindow
	special CloseBattleFrontierTutorWindow
	special ChooseMonForMoveTutor
	waitstate
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseMove
	msgbox BattleFrontier_Lounge7_Text_IllTakeBattlePoints, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

BattleFrontier_Lounge7_EventScript_ChooseNewMove:: @ 82656CA
	compare VAR_TEMP_E, 0
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Free
	compare VAR_TEMP_E, 1
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Special
	compare VAR_TEMP_E, 2
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Offense1
	compare VAR_TEMP_E, 3
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Offense2
	compare VAR_TEMP_E, 4
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Status
	goto BattleFrontier_Lounge7_EventScript_ChooseNewTutorMove_Support
	end

BattleFrontier_Lounge7_EventScript_ChooseMove:: @ 82656CA
	compare VAR_TEMP_E, 0
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Free
	compare VAR_TEMP_E, 1
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Special
	compare VAR_TEMP_E, 2
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Offense1
	compare VAR_TEMP_E, 3
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Offense2
	compare VAR_TEMP_E, 4
	goto_if_eq BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Status
	goto BattleFrontier_Lounge7_EventScript_ChooseTutorMove_Support
	end

@ SHARED TUTOR DIALOG

BattleFrontier_Lounge7_Text_TeachWhichMove: @ 82658EF
	.string "Which move should I teach?$"

BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints: @ 8265921
	.string "The move {STR_VAR_1}, is it?\n"
	.string "That will be {STR_VAR_2} Battle Points, okay?$"

BattleFrontier_Lounge7_Text_MoveWillBeFree: @ 8265921
	.string "The move {STR_VAR_1}, is it?\n"
	.string "This is free of charge, okay?$"

BattleFrontier_Lounge7_Text_TeachMoveToWhichMon: @ 826595A
	.string "Okay, tell me which Pokémon\n"
	.string "I should teach the move to.$"

BattleFrontier_Lounge7_Text_HaventGotEnoughPoints: @ 8265997
	.string "Oh, sorry…\n"
	.string "You haven't got enough Battle Points!$"

BattleFrontier_Lounge7_Text_IllTakeBattlePoints: @ 82659C7
	.string "There you go!\n"
	.string "Good luck with your new move!$"

BattleFrontier_Lounge7_Text_YouDontWantTo: @ 8265A0E
	.string "If you want to learn some new moves,\n"
	.string "you can come see me anytime!$"

@ SPECIFIC TUTOR DIALOG

BattleFrontier_Lounge7_Text_TutorIntro_Free: @ 82656ED
	.string "Hey there!\p"
	.string "I can teach your Pokémon some\n"
	.string "decent new moves. Unlike the others\l"
	.string "though, I do it for free!\p"
	.string "Want to learn some moves?$"

BattleFrontier_Lounge7_Text_TutorWelcomeBack_Free: @ 82658AB
	.string "Want to teach your Pokémon\n"
	.string "some free moves?$"

BattleFrontier_Lounge7_Text_TutorIntro_Special: @ 8265A6C
	.string "Ihihihi!\p"
	.string "Welcome, child! I can teach your\n"
	.string "Pokémon some rare and special moves.\p"
	.string "These moves can only be taught to\n"
	.string "specific Pokémon!\p"
	.string "But my lessons don't come free.\n"
	.string "How about paying for the moves I teach\l"
	.string "with a wee bit of Battle Points?$"

BattleFrontier_Lounge7_Text_TutorWelcomeBack_Special: @ 8265C2C
	.string "Have you come to learn rare and\n"
	.string "special moves?$"

BattleFrontier_Lounge7_Text_TutorIntro_Offense1:
	.string "Hoo-haa!\p"
	.string "If your moves don't deal a lot\n"
	.string "of damage, then why use them?\p"
	.string "I can teach your Pokémon some\n"
	.string "powerful moves in exchange for\l"
	.string "some Battle Points. Interested?$"

BattleFrontier_Lounge7_Text_TutorWelcomeBack_Offense1:
	.string "Have you come to teach your Pokémon\n"
	.string "some powerful moves? Hoo-haa!$"

BattleFrontier_Lounge7_Text_TutorIntro_Offense2:
	.string "Hi-yah!\p"
	.string "The best offense is... well,\n"
	.string "a good offense!\p"
	.string "I can teach your Pokémon some\n"
	.string "mighty moves in exchange for\l"
	.string "some Battle Points. Interested?$"

BattleFrontier_Lounge7_Text_TutorWelcomeBack_Offense2:
	.string "Have you come to teach your Pokémon\n"
	.string "some mighty moves? Hi-yah!$"

BattleFrontier_Lounge7_Text_TutorIntro_Status:
	.string "Hehehe…\p"
	.string "Don't let those Black Belts\n"
	.string "intimidate you into going with a\l"
	.string "pure offensive strategy.\p"
	.string "Brains over brawn is what I say.\p"
	.string "Interested in learning some more\n"
	.string "intelligent moves in exchange for\l"
	.string "some Battle points?$"

BattleFrontier_Lounge7_Text_TutorWelcomeBack_Status:
	.string "Interested in learning some more\n"
	.string "intelligent moves?$"

BattleFrontier_Lounge7_Text_TutorIntro_Support:
	.string "Hello, dear!\p"
	.string "Sometimes the best way to get ahead\n"
	.string "isn't to attack your foes, but to\l"
	.string "instead focus on improving yourself\l"
	.string "and your surroundings.\p"
	.string "Do you wish to teach your Pokémon\n"
	.string "some supportive moves in exchange\l"
	.string "for some Battle Points?$"

BattleFrontier_Lounge7_Text_TutorWelcomeBack_Support:
	.string "Do you wish to teach your Pokémon\n"
	.string "some supportive moves?$"

@ MOVE PRICES AND SCRIPTS

BattleFrontier_Lounge7_EventScript_DefenseCurl::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Softboiled::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_MudSlap::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Swift::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_SeismicToss::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_MegaPunch::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_MegaKick::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Endure::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_PsychUp::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_BodySlam::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Counter::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_DynamicPunch::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_DoubleEdge::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Rollout::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_FuryCutter::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Metronome::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Mimic::
    setvar VAR_0x8008, 0
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_GrassPledge::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_FirePledge::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_WaterPledge::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_FrenzyPlant::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_BlastBurn::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_HydroCannon::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_DracoMeteor::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_RelicSong::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_SecretSword::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_DragonAscent::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Uproar::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Snore::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Bounce::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_LowKick::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_ThunderPunch::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_FirePunch::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_IcePunch::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_DrainPunch::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_HeatWave::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_EarthPower::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_KnockOff::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_SuperFang::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_DualChop::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_ThroatChop::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_SkyDrop::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Endeavor::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Liquidation::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_SludgeWave::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_BugBite::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Fling::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_DrillRun::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_IronHead::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_ZenHeadbutt::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_SignalBeam::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_BrutalSwing::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_HyperVoice::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_AquaTail::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_DragonPulse::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_SeedBomb::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_LastResort::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_FoulPlay::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_StompingTantrum::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Outrage::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Superpower::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_GunkShot::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_SkyAttack::
    setvar VAR_0x8008, 16
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Bind::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Infestation::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Covet::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Block::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Quash::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_RolePlay::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_PainSplit::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_GastroAcid::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_WorrySeed::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Spite::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Trick::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Embargo::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_MagicCoat::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Telekinesis::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Electroweb::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_IcyWind::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_HoneClaws::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_IronDefense::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_LaserFocus::
    setvar VAR_0x8008, 4
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_HealBell::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_MagicRoom::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_WonderRoom::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Gravity::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_MagnetRise::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Recycle::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_AfterYou::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_HelpingHand::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Synthesis::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Defog::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_AllySwitch::
    setvar VAR_0x8008, 8
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_Tailwind::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

BattleFrontier_Lounge7_EventScript_StealthRock::
    setvar VAR_0x8008, 12
    goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
    end

@ MOVE DESCRIPTIONS

BattleFrontier_Lounge7_Text_DefenseCurlDesc::
	.string "Curls up to con-\n"
	.string "ceal weak spots\n"
	.string "and raise DEFENSE.$"

BattleFrontier_Lounge7_Text_SoftboiledDesc:: @ 8265E30
	.string "Recovers up to\n"
	.string "half the user's\n"
	.string "maximum HP.$"

BattleFrontier_Lounge7_Text_MudSlapDesc:: @ 8266070
	.string "Hurls mud in the\n"
	.string "foe's face to re-\n"
	.string "duce its accuracy.$"

BattleFrontier_Lounge7_Text_SwiftDesc:: @ 82660A6
	.string "Sprays star-\n"
	.string "shaped rays\n"
	.string "that never miss.$"

BattleFrontier_Lounge7_Text_SeismicTossDesc:: @ 8265E5B
	.string "Inflicts damage\n"
	.string "identical to the\n"
	.string "user's level.$"

BattleFrontier_Lounge7_Text_MegaPunchDesc:: @ 8265EC0
	.string "A strong punch\n"
	.string "thrown with\n"
	.string "incredible power.$"

BattleFrontier_Lounge7_Text_MegaKickDesc:: @ 8265EED
	.string "An extremely\n"
	.string "powerful kick with\n"
	.string "intense force.$"

BattleFrontier_Lounge7_Text_EndureDesc:: @ 82660FF
	.string "Endures any at-\n"
	.string "tack for 1 turn,\n"
	.string "leaving 1HP.$"

BattleFrontier_Lounge7_Text_PsychUpDesc:: @ 826612D
	.string "Copies the foe's\n"
	.string "effect(s) and\n"
	.string "gives to the user.$"

BattleFrontier_Lounge7_Text_BodySlamDesc:: @ 8265F1C
	.string "A full-body slam\n"
	.string "that may cause\n"
	.string "paralysis.$"

BattleFrontier_Lounge7_Text_CounterDesc:: @ 8265F77
	.string "Retaliates any\n"
	.string "physical hit with\n"
	.string "double the power.$"

BattleFrontier_Lounge7_Text_DynamicPunchDesc::
	.string "The foe is punched\n"
	.string "with full power.\n"
	.string "Always confuses.$"

BattleFrontier_Lounge7_Text_DoubleEdgeDesc::
	.string "A life-risking\n"
	.string "tackle that also\n"
	.string "hurts the user.$"

BattleFrontier_Lounge7_Text_RolloutDesc::
	.string "A 5-turn rolling\n"
	.string "attack that gets\n"
	.string "stronger each hit.$"

BattleFrontier_Lounge7_Text_FuryCutterDesc::
	.string "An attack where\n"
	.string "successive hits\n"
	.string "raise power.$"

BattleFrontier_Lounge7_Text_MetronomeDesc::
	.string "Waggles a finger\n"
	.string "to use any move\n"
	.string "at random.$"

BattleFrontier_Lounge7_Text_MimicDesc::
	.string "Copies a move last\n"
	.string "used by the foe\n"
	.string "for the battle.$"

BattleFrontier_Lounge7_Text_GrassPledgeDesc::
	.string "Combos with other\n"
	.string "Pledges for extra\n"
	.string "power and effects.$"

BattleFrontier_Lounge7_Text_FirePledgeDesc::
	.string "Combos with other\n"
	.string "Pledges for extra\n"
	.string "power and effects.$"

BattleFrontier_Lounge7_Text_WaterPledgeDesc::
	.string "Combos with other\n"
	.string "Pledges for extra\n"
	.string "power and effects.$"

BattleFrontier_Lounge7_Text_FrenzyPlantDesc::
	.string "Hits the foe with\n"
	.string "enormous roots.\n"
	.string "Must recharge.$"

BattleFrontier_Lounge7_Text_BlastBurnDesc::
	.string "Hits the foe with\n"
	.string "a fiery explosion.\n"
	.string "Must recharge.$"

BattleFrontier_Lounge7_Text_HydroCannonDesc::
	.string "Hits the foe with\n"
	.string "a watery blast.\n"
	.string "Must recharge.$"

BattleFrontier_Lounge7_Text_RelicSongDesc::
	.string "The user sings an\n"
	.string "ancient song. May\n"
	.string "also induce sleep.$"

BattleFrontier_Lounge7_Text_SecretSwordDesc::
	.string "The user cuts with\n"
	.string "its horn. Deals\n"
	.string "Physical damage.$"

BattleFrontier_Lounge7_Text_DracoMeteorDesc::
	.string "Casts comets onto\n"
	.string "the foe. Harshly\n"
	.string "drops Sp. Atk.$"

BattleFrontier_Lounge7_Text_DragonAscentDesc::
	.string "Soars upward, then\n"
	.string "hits at high speed.\n"
	.string "Lowers defenses.$"

BattleFrontier_Lounge7_Text_BindDesc::
	.string "Squeezes the foe\n"
	.string "for 2 to 5 turns,\n"
	.string "trapping them.$"

BattleFrontier_Lounge7_Text_SnoreDesc:: @ 826603E
	.string "A loud attack\n"
	.string "that can be used\n"
	.string "only while asleep.$"

BattleFrontier_Lounge7_Text_HoneClawsDesc::
	.string "Hones your claws\n"
	.string "to raise Attack\n"
	.string "and Accuracy.$"

BattleFrontier_Lounge7_Text_InfestationDesc::
	.string "Swarms the foe\n"
	.string "for 2 to 5 turns,\n"
	.string "trapping them.$"

BattleFrontier_Lounge7_Text_BugBiteDesc::
	.string "Eats the foe's\n"
	.string "held Berry to\n"
	.string "gain its effect.$"

BattleFrontier_Lounge7_Text_CovetDesc::
	.string "Cutely begs the\n"
	.string "foe to obtain\n"
	.string "their held item.$"

BattleFrontier_Lounge7_Text_LowKickDesc::
	.string "Inflicts more\n"
	.string "damage on\n"
	.string "heavier foes.$"

BattleFrontier_Lounge7_Text_SignalBeamDesc::
	.string "A strange beam\n"
	.string "that may confuse\n"
	.string "the foe.$"

BattleFrontier_Lounge7_Text_FlingDesc::
	.string "Throws your item.\n"
	.string "Power and effect\n"
	.string "varies per item.$"

BattleFrontier_Lounge7_Text_ThunderPunchDesc:: @ 8266185
	.string "An electrified\n"
	.string "punch that may\n"
	.string "paralyze the foe.$"

BattleFrontier_Lounge7_Text_FirePunchDesc:: @ 82661B5
	.string "A fiery punch\n"
	.string "that may burn\n"
	.string "the foe.$"

BattleFrontier_Lounge7_Text_IcePunchDesc:: @ 826615F
	.string "An icy punch\n"
	.string "that may\n"
	.string "freeze the foe.$"

BattleFrontier_Lounge7_Text_DrainPunchDesc::
	.string "A punch that\n"
	.string "absorbs half the\n"
	.string "damage as HP.$"

BattleFrontier_Lounge7_Text_KnockOffDesc::
	.string "Knocks the foe's\n"
	.string "held item away to\n"	
	.string "prevent its use.$"

BattleFrontier_Lounge7_Text_SuperFangDesc::
	.string "Bites the foe,\n"
	.string "cutting their HP\n"
	.string "in half.$"

BattleFrontier_Lounge7_Text_DualChopDesc::
	.string "Attacks with\n"
	.string "brutal hits that\n"
	.string "strike twice.$"

BattleFrontier_Lounge7_Text_SkyDropDesc::
	.string "Takes the foe\n"
	.string "into the sky, then\n"
	.string "drops them.$"

BattleFrontier_Lounge7_Text_EndeavorDesc::
	.string "Brings the foe's\n"
	.string "HP down to match\n"
	.string "the user's HP.$"

BattleFrontier_Lounge7_Text_LiquidationDesc::
	.string "Slams the foe\n"
	.string "with water. May\n"
	.string "lower Defense.$"

BattleFrontier_Lounge7_Text_ThroatChopDesc::
	.string "Chops the throat\n"
	.string "to disable sound\n"
	.string "moves for a while.$"

BattleFrontier_Lounge7_Text_UproarDesc::
	.string "Causes an uproar\n"
	.string "for 2 to 5 turns.\n"
	.string "Prevents sleeping.$"

BattleFrontier_Lounge7_Text_BrutalSwingDesc::
	.string "Violently swings\n"
	.string "around to hurt all\n"
	.string "adjacent Pokémon.$"

BattleFrontier_Lounge7_Text_BounceDesc::
	.string "Bounces up, then\n"
	.string "down next turn.\n"
	.string "May paralyze.$"

BattleFrontier_Lounge7_Text_DrillRunDesc::
	.string "Spins its body\n"
	.string "like a drill.\n"
	.string "High crit ratio.$"

BattleFrontier_Lounge7_Text_IronHeadDesc::
	.string "Slams the foe\n"
	.string "with a hard head.\n"
	.string "May flinch.$"

BattleFrontier_Lounge7_Text_ZenHeadbuttDesc::
	.string "Hits with a strong\n"
	.string "headbutt.\n"
	.string "May flinch.$"

BattleFrontier_Lounge7_Text_AquaTailDesc::
	.string "The user swings\n"
	.string "its tail like a\n"
	.string "wave to attack.$"

BattleFrontier_Lounge7_Text_DragonPulseDesc::
	.string "Generates a\n"
	.string "shock wave to\n"
	.string "attack the foe.$"

BattleFrontier_Lounge7_Text_SeedBombDesc::
	.string "Fires a barrage\n"
	.string "of volatile seeds\n"
	.string "at the foe.$"

BattleFrontier_Lounge7_Text_HeatWaveDesc::
	.string "Exhales a hot\n"
	.string "breath on all\n"
	.string "foes. May burn.$"

BattleFrontier_Lounge7_Text_LastResortDesc::
	.string "Must use every\n"
	.string "other known move\n"
	.string "first.$"

BattleFrontier_Lounge7_Text_HyperVoiceDesc::
	.string "A loud attack\n"
	.string "that uses sound\n"
	.string "waves to attack.$"

BattleFrontier_Lounge7_Text_FoulPlayDesc::
	.string "Uses the foe's\n"
	.string "Attack stat\n"
	.string "against them.$"

BattleFrontier_Lounge7_Text_EarthPowerDesc::
	.string "Makes the ground\n"
	.string "erupt with power.\n"
	.string "May lower Sp. Def.$"

BattleFrontier_Lounge7_Text_StompingTantrumDesc::
	.string "Stomps around\n"
	.string "angrily. Stronger\n"
	.string "after missing.$"

BattleFrontier_Lounge7_Text_OutrageDesc::
	.string "Rampage for 2 to 3\n"
	.string "turns. The user is\n"
	.string "confused after.$"

BattleFrontier_Lounge7_Text_SuperpowerDesc::
	.string "A strong attack.\n"
	.string "The user's Attack\n"
	.string "and Defense drop.$"

BattleFrontier_Lounge7_Text_GunkShotDesc::
	.string "Shoots garbage\n"
	.string "at the foe.\n"
	.string "May poison.$"

BattleFrontier_Lounge7_Text_SkyAttackDesc::
	.string "Searches out\n"
	.string "weakspots, then\n"
	.string "attacks next turn.$"

BattleFrontier_Lounge7_Text_SludgeWaveDesc::
	.string "Swamps adjacent\n"
	.string "Pokémon with\n"
	.string "sludge. May poison.$"

BattleFrontier_Lounge7_Text_BlockDesc::
	.string "Blocks the foe's\n"
	.string "way to prevent\n"
	.string "escape.$"

BattleFrontier_Lounge7_Text_QuashDesc::
	.string "Suppresses the\n"
	.string "foe, making it\n"
	.string "move last.$"

BattleFrontier_Lounge7_Text_SynthesisDesc::
	.string "Restores HP.\n"
	.string "The amount varies\n"
	.string "with the weather.$"

BattleFrontier_Lounge7_Text_RolePlayDesc::
	.string "Mimics the target\n"
	.string "and copies their\n"
	.string "Ability.$"

BattleFrontier_Lounge7_Text_PainSplitDesc::
	.string "Sums the user and\n"
	.string "foe's HP, then\n"
	.string "shares it equally.$"

BattleFrontier_Lounge7_Text_GastroAcidDesc::
	.string "Stomach acid\n"
	.string "supresses the\n"
	.string "foe's Ability.$"

BattleFrontier_Lounge7_Text_WorrySeedDesc::
	.string "Plants a seed on\n"
	.string "the foe, giving\n"
	.string "them Insomnia.$"

BattleFrontier_Lounge7_Text_SpiteDesc::
	.string "Spitefully cuts\n"
	.string "the PP of the\n"
	.string "foe's last move.$"

BattleFrontier_Lounge7_Text_AfterYouDesc::
	.string "Helps out the\n"
	.string "target, letting\n"
	.string "them move next.$"

BattleFrontier_Lounge7_Text_HelpingHandDesc::
	.string "Boosts the power\n"
	.string "of the ally's\n"
	.string "next move.$"

BattleFrontier_Lounge7_Text_TrickDesc::
	.string "Tricks the target\n"
	.string "into trading\n"
	.string "held items.$"

BattleFrontier_Lounge7_Text_RecycleDesc::
	.string "Recycles a used\n"
	.string "held item for\n"
	.string "another use.$"

BattleFrontier_Lounge7_Text_EmbargoDesc::
	.string "Prevents the foe\n"
	.string "from using any\n"
	.string "items for a while.$"

BattleFrontier_Lounge7_Text_MagicCoatDesc::
	.string "Reflects special\n"
	.string "effects back to\n"
	.string "the attacker.$"

BattleFrontier_Lounge7_Text_MagnetRiseDesc::
	.string "The user levitates\n"
	.string "in the air with\n"
	.string "electromagnetism.$"

BattleFrontier_Lounge7_Text_IronDefenseDesc::
	.string "Hardens the outer\n"
	.string "shell to sharply\n"
	.string "raise Defense.$"

BattleFrontier_Lounge7_Text_TelekinesisDesc::
	.string "Makes the foe\n"
	.string "float. They are\n"
	.string "easier to hit.$"

BattleFrontier_Lounge7_Text_HealBellDesc::
	.string "Chimes soothingly\n"
	.string "to heal your party\n"
	.string "of all status.$"

BattleFrontier_Lounge7_Text_TailwindDesc::
	.string "Doubles the Speed\n"
	.string "of your Pokémon\n"
	.string "for 3 turns.$"

BattleFrontier_Lounge7_Text_MagicRoomDesc::
	.string "Hold items lose\n"
	.string "their effects for\n"
	.string "5 turns.$"

BattleFrontier_Lounge7_Text_WonderRoomDesc::
	.string "Defenses are\n"
	.string "swapped for\n"
	.string "5 turns.$"

BattleFrontier_Lounge7_Text_StealthRockDesc::
	.string "Sets floating\n"
	.string "stones that hurt\n"
	.string "foes switching in.$"

BattleFrontier_Lounge7_Text_GravityDesc::
	.string "Gravity is\n"
	.string "intensified,\n"
	.string "grounding all.$"

BattleFrontier_Lounge7_Text_DefogDesc::
	.string "Clears hazards\n"
	.string "and screens. Also\n"
	.string "lowers evasion.$"

BattleFrontier_Lounge7_Text_AllySwitchDesc::
	.string "The user switches\n"
	.string "places with its\n"
	.string "partner.$"

BattleFrontier_Lounge7_Text_ElectrowebDesc::
	.string "Snares all foes\n"
	.string "with an electric\n"
	.string "net. Lowers Speed.$"

BattleFrontier_Lounge7_Text_IcyWindDesc:: @ 82660D0
	.string "A chilling attack\n"
	.string "that lowers all\n"
	.string "foe's speed.$"

BattleFrontier_Lounge7_Text_LaserFocusDesc::
	.string "Guarentees the\n"
	.string "next move will be\n"
	.string "a critical hit.$"
