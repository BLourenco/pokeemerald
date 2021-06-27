.set LOCALID_CHAMPION, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3
.set LOCALID_NORMAN, 4

EverGrandeCity_ChampionsRoom_MapScripts:: @ 82289EF
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition: @ 82289FF
	call Common_EventScript_SetupRivalGfxId
	call EverGrandeCity_ChampionsRoom_SetupChampionGfxId
	goto_if_unset FLAG_SYS_GAME_CLEAR, EverGrandeCity_ChampionsRoom_EventScript_LoadStevensRoom
	end

EverGrandeCity_ChampionsRoom_EventScript_LoadStevensRoom::
	setmaplayoutindex LAYOUT_EVER_GRANDE_CITY_CHAMPIONS_ROOM_STEVEN
	end

EverGrandeCity_ChampionsRoom_SetupChampionGfxId::
	goto_if_unset FLAG_SYS_GAME_CLEAR, EverGrandeCity_ChampionsRoom_EventScript_SetupChampionGfxIdSteven
	goto_if_set FLAG_SYS_GAME_CLEAR, EverGrandeCity_ChampionsRoom_EventScript_SetupChampionGfxIdWallace
	return

EverGrandeCity_ChampionsRoom_EventScript_SetupChampionGfxIdSteven::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_STEVEN
	return

EverGrandeCity_ChampionsRoom_EventScript_SetupChampionGfxIdWallace::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_WALLACE
	return

EverGrandeCity_ChampionsRoom_OnWarp: @ 8228A05
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth:: @ 8228A0F
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame: @ 8228A14
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom:: @ 8228A1E
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachChampion
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto_if_unset FLAG_SYS_GAME_CLEAR, EverGrandeCity_ChampionsRoom_EventScript_Steven
	goto_if_set FLAG_SYS_GAME_CLEAR, EverGrandeCity_ChampionsRoom_EventScript_Wallace
    releaseall
    end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachChampion: @ 8228A42
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Steven:: @ 8228A45
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenIntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN_CHAMPION, EverGrandeCity_ChampionsRoom_Text_StevenDefeat
	goto EverGrandeCity_ChampionsRoom_EventScript_StevenDefeated
	end

EverGrandeCity_ChampionsRoom_EventScript_Wallace:: @ 8228A45
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceIntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE_CHAMPION, EverGrandeCity_ChampionsRoom_Text_WallaceDefeat
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceDefeated
	end

EverGrandeCity_ChampionsRoom_EventScript_StevenDefeated:: @ 8228A61
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, 0
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, 0
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenPostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	compare VAR_RESULT, FEMALE
	goto_if_eq EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_WallaceDefeated:: @ 8228A61
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, 0
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, 0
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_WallacePostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CHAMPION, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 255, 7, 16	
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic:: @ 8228ABC
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic:: @ 8228AC1
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice:: @ 8228AC6
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice:: @ 8228AFB
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF:: @ 8228B30
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	closemessage
	addobject LOCALID_NORMAN
	applymovement LOCALID_NORMAN, EverGrandeCity_ChampionsRoom_Movement_NormanArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_DadArrives, MSGBOX_DEFAULT
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_DadMySon
	compare VAR_RESULT, FEMALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_DadMyDaughter
	msgbox EverGrandeCity_ChampionsRoom_Text_DadCongratulations, MSGBOX_DEFAULT	
	applymovement LOCALID_CHAMPION, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 20
	applymovement LOCALID_CHAMPION, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_CHAMPION, EverGrandeCity_ChampionsRoom_Movement_StevenExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFastestUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	compare VAR_RESULT, FEMALE
	call_if_eq EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_CHAMPION, EverGrandeCity_ChampionsRoom_Movement_StevenExitFinish
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitFinish
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 255, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_DadMySon::
	msgbox EverGrandeCity_ChampionsRoom_Text_DadArrivesMySon, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_DadMyDaughter::
	msgbox EverGrandeCity_ChampionsRoom_Text_DadArrivesMyDaughter, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations:: @ 8228BEB
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations:: @ 8228BF4
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer:: @ 8228BFD
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth:: @ 8228C12
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart: @ 8228C1D
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExitFinish: @ 8228C20
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer: @ 8228C26
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_fastest_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth: @ 8228C2F
	walk_in_place_fastest_up
	delay_16
	walk_in_place_fastest_right
	delay_16
	walk_in_place_fastest_up
	delay_8
	walk_in_place_fastest_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows: @ 8228C38
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_StevenExitStart: @ 8228C3B
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_StevenExitFinish:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end
	
EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	walk_up
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives: @ 8228C43
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_fastest_left
	step_end

EverGrandeCity_ChampionsRoom_Movement_NormanArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Text_StevenIntroSpeech:
	.string "Steven: Welcome, {PLAYER}{KUN}.\p"
	.string "I was looking forward to seeing you\n"
	.string "here one day.\p"
	.string "You… What did you see on your\n"
	.string "journey with Pokémon?\p"
	.string "What did you feel, meeting so many\n"
	.string "other Trainers like you?\p"
	.string "That incident in Sootopolis City…\n"
	.string "That was superb work, putting an end\l"
	.string "to that crisis all by yourself.\p"
	.string "Oh, pardon me!\p"
	.string "It wouldn't be fair to say that you\n"
	.string "alone ended the crisis.\p"
	.string "You overcame that difficult situation\n"
	.string "by working as one with your Pokémon.\p"
	.string "We Trainers raise Pokémon by giving\n"
	.string "them items and by teaching them new\l"
	.string "techniques for battle.\p"
	.string "But we ourselves also learn many\n"
	.string "things from Pokémon.\p"
	.string "And this is where your achievements\n"
	.string "are put to the test against what\l"
	.string "others like you have achieved.\p"
	.string "Now!\p"
	.string "After traveling all over this rich\n"
	.string "land of Hoenn with your Pokémon…\p"
	.string "Has it awoken something inside you?\n"
	.string "I want you to come at me with all that\l"
	.string "you've learned.\p"
	.string "Let it begin!$"

EverGrandeCity_ChampionsRoom_Text_StevenDefeat:
	.string "So I, the Champion, fall in defeat…\p"
	.string "Kudos to you, {PLAYER}{KUN}!\p"
	.string "You are a truly noble Pokémon\n"
	.string "Trainer!$"

EverGrandeCity_ChampionsRoom_Text_StevenPostBattleSpeech:
	.string "Just as I have come to expect.\p"
	.string "{PLAYER}, you are truly an excellent\n"
	.string "Pokémon Trainer.\p"
	.string "Congratulations to you and\n"
	.string "your Pokémon!\p"
	.string "And thank you…\p"
	.string "I had wanted to learn how you feel\n"
	.string "about this world, what kinds of\l"
	.string "ideals you have developed with\l"
	.string "your Pokémon…\p"
	.string "I feel I was able to find the\n"
	.string "answer in our battle.\p"
	.string "The feelings you have for your\n"
	.string "Pokémon…\p"
	.string "And the way that your Pokémon gave\n"
	.string "their all in battle in response\l"
	.string "to those feelings…\p"
	.string "Those two together created a great\n"
	.string "power.\p"
	.string "That is how you seized victory today.\p"
	.string "I felt a thrill of excitement in my\n"
	.string "breast when we first met, and now I\l"
	.string "know for sure that feeling was not\l"
	.string "misplaced!\p"
	.string "You are rightfully the Hoenn region's\n"
	.string "new…$"

EverGrandeCity_ChampionsRoom_Text_StevenComeWithMe:
	.string "Steven: {PLAYER}{KUN}…\p"
	.string "No, let me rephrase that properly.\p"
	.string "Champion {PLAYER}{KUN}!\p"
	.string "Come with me.$"

EverGrandeCity_ChampionsRoom_Text_StevenWaitOutside: @ 82293EB
	.string "Steven: I'm very sorry…\p"
	.string "But only a Trainer who has successfully\n"
	.string "become the Champion may enter.\p"
	.string "You'll need to wait outside.$"

EverGrandeCity_ChampionsRoom_Text_WallaceIntroSpeech: @ 8228C4C
	.string "Wallace: Welcome, Champion {PLAYER}.\p"
	.string "Surprised to see me?\p"
	.string "Something came up that required\n"
	.string "Steven's extended attention.\p"
	.string "In the meantime, he's asked me\n"
	.string "to take his place in the League.\p"
	.string "It's been a long while since I\n"
	.string "last challenged the League myself.\p"
	.string "But now here I stand, ready to put\n"
	.string "any challenger to the test!\p"
	.string "Now!\p"
	.string "Who can most elegantly dance with\n"
	.string "their Pokémon in Hoenn?\p"
	.string "Show me right here and now!$"

EverGrandeCity_ChampionsRoom_Text_WallaceDefeat: @ 8228EAC
	.string "You truly are a Champion!\n"
	.string "That was wonderful work.\p"
	.string "You were elegant, infuriatingly so.\n"
	.string "And yet it was utterly glorious!$"

EverGrandeCity_ChampionsRoom_Text_WallacePostBattleSpeech: @ 8228F66
	.string "Wallace: The Pokémon you sent into\n"
	.string "battle…\p"
	.string "At times they danced like a spring\n"
	.string "breeze, and at times they struck\l"
	.string "like lightning.\p"
	.string "It was with light, yet surefooted,\n"
	.string "elegance that you led your Pokémon.\p"
	.string "Even I felt bedazzled by your\n"
	.string "masterful performance!\p"
	.string "You once again stand at the glorious\n"
	.string "peak of the Pokémon League.\p"
	.string "Champion {PLAYER}…\n"
	.string "Please follow me.$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice: @ 82290CA
	.string "{RIVAL}: {PLAYER}{KUN}!\p"
	.string "Here's some advice before you challenge\n"
	.string "the Champion…$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver: @ 822910B
	.string "{RIVAL}: Huh?\n"
	.string "What, what, what?\p"
	.string "{PLAYER}{KUN}…\n"
	.string "Could it be that…\l"
	.string "It's already over?$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice: @ 8229152
	.string "{RIVAL}: {PLAYER}!\p"
	.string "How would you like some advice before\n"
	.string "you challenge the Champion?…$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon: @ 82291A2
	.string "{RIVAL}: {PLAYER}…\p"
	.string "Are you trying to tell me…\n"
	.string "You've beaten the Champion?$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex: @ 82291E6
	.string "Prof. Birch: See?\n"
	.string "What did I tell you, {RIVAL}?\p"
	.string "Didn't I tell you that you don't need\n"
	.string "to worry about {PLAYER}{KUN}?\p"
	.string "… … … … … … … …\n"
	.string "{PLAYER}{KUN}, you've finally done it.\p"
	.string "When I heard that you defeated your\n"
	.string "own father at the Petalburg Gym,\l"
	.string "I thought perhaps you had a chance…\p"
	.string "But to think you've actually become\n"
	.string "the Champion!$"

EverGrandeCity_ChampionsRoom_Text_DadArrives:
	.string "Dad: {PLAYER}!\n"
	.string "I'm so proud of you!\p"
	.string "Nothing makes me happier than\n"
	.string "seeing you succeed as a Pokémon\l"
	.string "Trainer.\p"
	.string "I remember when you showed me your\n"
	.string "very first Pokémon…\p"
	.string "I remember the day you challenged your\n"
	.string "own father to a Gym battle, and won…\p"
	.string "And now, here you are!$"

EverGrandeCity_ChampionsRoom_Text_DadArrivesMySon:
	.string "My own son,\n"
	.string "the Hoenn region Champion!$"

EverGrandeCity_ChampionsRoom_Text_DadArrivesMyDaughter:
	.string "My own daughter,\n"
	.string "the Hoenn region Champion!$"

EverGrandeCity_ChampionsRoom_Text_DadCongratulations:
	.string "Congratulations, {PLAYER}!\p"
	.string "Now, go proudly into the final room!$"

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe: @ 8229399
	.string "Wallace: {PLAYER}{KUN}…\p"
	.string "No, let me rephrase that properly.\p"
	.string "The new Champion!\p"
	.string "Come with me.$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside: @ 82293EB
	.string "Wallace: I'm sorry, but…\p"
	.string "From here on, only those Trainers who\n"
	.string "have become Champions may enter.\p"
	.string "You'll have to wait outside with\n"
	.string "Prof. Birch.$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations: @ 8229479
	.string "{RIVAL}: Groan…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "I'm just joking! That's okay!\n"
	.string "That's the rule!\p"
	.string "{PLAYER}{KUN}!\n"
	.string "Honestly, congratulations!$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations: @ 82294F5
	.string "{RIVAL}: Whaaaat?! … … … … …\n"
	.string "… … … … … … … …\p"
	.string "It can't be helped if that's the rule.\p"
	.string "{PLAYER}, way to go!\n"
	.string "Congratulations!$"

