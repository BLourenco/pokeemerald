PacifidlogTown_MapScripts:: @ 81EBAB1
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	map_script MAP_SCRIPT_ON_LOAD, PacifidlogTown_OnLoad
	.byte 0

PacifidlogTown_OnTransition: @ 81EBABC
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume: @ 81EBAC0
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_OnLoad:
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, PacifidlogTown_EventScript_SetWailmerMetatiles
	end

PacifidlogTown_EventScript_SetWailmerMetatiles:: @ 81E2B6B
	setmetatile 27, 17, METATILE_Pacifidlog_Wailmer0_Alt, 1
	setmetatile 28, 17, METATILE_Pacifidlog_Wailmer1_Alt, 1
	setmetatile 27, 18, METATILE_Pacifidlog_Wailmer2, 1
	setmetatile 28, 18, METATILE_Pacifidlog_Wailmer3, 1
	
	setmetatile 28, 19, METATILE_Pacifidlog_Wailmer0_Alt, 1
	setmetatile 29, 19, METATILE_Pacifidlog_Wailmer1_Alt, 1
	setmetatile 28, 20, METATILE_Pacifidlog_Wailmer2, 1
	setmetatile 29, 20, METATILE_Pacifidlog_Wailmer3, 1
	
	setmetatile 26, 20, METATILE_Pacifidlog_Wailmer0_Alt, 1
	setmetatile 27, 20, METATILE_Pacifidlog_Wailmer1_Alt, 1
	setmetatile 26, 21, METATILE_Pacifidlog_Wailmer2, 1
	setmetatile 27, 21, METATILE_Pacifidlog_Wailmer3, 1
	
	setmetatile 28, 22, METATILE_Pacifidlog_Wailmer0_Alt, 1
	setmetatile 29, 22, METATILE_Pacifidlog_Wailmer1_Alt, 1
	setmetatile 28, 23, METATILE_Pacifidlog_Wailmer2, 1
	setmetatile 29, 23, METATILE_Pacifidlog_Wailmer3, 1
	return

PacifidlogTown_EventScript_NinjaBoy:: @ 81EBAC3
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl:: @ 81EBACC
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Fisherman:: @ 81EBAD5
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	end

PacifidlogTown_EventScript_TownSign:: @ 81EBADE
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_EventScript_WailmerTrainerGrunt:: @ 81E2D7D
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, PacifidlogTown_EventScript_MetWailmerTrainer
	msgbox PacifidlogTown_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox PacifidlogTown_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

PacifidlogTown_EventScript_MetWailmerTrainer:: @ 81E2DB0
	msgbox PacifidlogTown_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

PacifidlogTown_Text_FastRunningCurrent: @ 81EBAE7
	.string "The sea between Pacifidlog and\n"
	.string "Slateport has a fast-running tide.\p"
	.string "If you decide to Surf, you could end\n"
	.string "up swept away somewhere else.$"

PacifidlogTown_Text_NeatHousesOnWater: @ 81EBB6C
	.string "See, isn't it neat?\n"
	.string "These houses are on water!\p"
	.string "I was born here!$"

PacifidlogTown_Text_SkyPillarTooScary: @ 81EBBAC
	.string "The Sky Pillar?\p"
	.string "…Oh, you must mean that tall, tall\n"
	.string "tower a little further out.\p"
	.string "If you asked me, I wouldn't climb it.\n"
	.string "It's too scary to get up that high.\p"
	.string "Life at sea level in Pacifidlog,\n"
	.string "that suits me fine.$"

PacifidlogTown_Text_TownSign: @ 81EBC7A
	.string "Pacifidlog Town\p"
	.string "“Where the morning sun smiles upon\n"
	.string "the waters.”$"

PacifidlogTown_Text_WailmerLeapOutOfWater: @ 81E3D1F
	.string "There! Wailmer!\n"
	.string "Leap out of the water now!$"

PacifidlogTown_Text_GetLostMessingUpTraining: @ 81E3D4A
	.string "Hunh? What do you want?\p"
	.string "You're messing up our training,\n"
	.string "so can you, like, get lost?$"

