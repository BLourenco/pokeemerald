.set LOCALID_WOMAN_1, 19
.set LOCALID_MAN_1, 20

LilycoveCity_MapScripts:: @ 81E2B3C
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	.byte 0

LilycoveCity_OnTransition: @ 81E2B47
	setflag FLAG_VISITED_LILYCOVE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_CONTEST_HALL_REPORTER
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad: @ 81E2B61
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles:: @ 81E2B6B
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, 1
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, 1
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, 1
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, 1
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, 1
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, 1
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, 1
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, 1
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, 1
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, 1
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, 1
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, 1
	return

LilycoveCity_EventScript_BerryGentleman:: @ 81E2BD8
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	random 10
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry:: @ 81E2C18
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3:: @ 81E2C22
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl:: @ 81E2C2B
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone:: @ 81E2C40
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy:: @ 81E2C4A
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2:: @ 81E2C53
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone:: @ 81E2C68
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2:: @ 81E2C72
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone:: @ 81E2C87
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2:: @ 81E2C91
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1:: @ 81E2C9A
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF:: @ 81E2CA3
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2:: @ 81E2CAC
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone:: @ 81E2CC1
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1:: @ 81E2CCB
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan:: @ 81E2CD4
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1:: @ 81E2CDD
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1:: @ 81E2CEE
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign:: @ 81E2CFF
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ContestHallSign:: @ 81E2D08
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign:: @ 81E2D11
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign:: @ 81E2D1A
	lockall
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings:: @ 81E2D3A
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign:: @ 81E2D44
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady:: @ 81E2D58
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign:: @ 81E2D62
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign:: @ 81E2D6B
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign:: @ 81E2D74
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt:: @ 81E2D7D
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer:: @ 81E2DB0
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1:: @ 81E2DBA
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2:: @ 81E2DC3
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3:: @ 81E2DCC
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4:: @ 81E2DD5
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_SchoolKidM:: @ 81E302D
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq LilycoveCity_EventScript_KnowAboutBerryBlender
	compare VAR_RESULT, NO
	call_if_eq LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender:: @ 81E304F
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender:: @ 81E3058
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MovedLootIntoHideoutToday: @ 81E3B2C
	.string "Fufufu…\p"
	.string "We moved more loot into our secret\n"
	.string "Hideout today…\p"
	.string "Wh-who are you?!\n"
	.string "I was just talking to myself!$"

LilycoveCity_Text_ChanceToDoBigThings: @ 81E3B95
	.string "I'm just a Grunt, so I don't know what\n"
	.string "the Boss is thinking…\p"
	.string "But being on Team Aqua, I know I'll get\n"
	.string "the chance to do big things!\p"
	.string "Wh-who are you?!\n"
	.string "I was just talking to myself!$"

LilycoveCity_Text_DontGoNearCaveInCove: @ 81E3C46
	.string "Hey, you!\p"
	.string "Don't go near the cave in the cove!\p"
	.string "Why? You don't need a reason why!\n"
	.string "I'm an adult, so you just listen to me!$"

LilycoveCity_Text_IfWorldBecomesOurs: @ 81E3CBE
	.string "If this whole wide world becomes ours,\n"
	.string "Team Aqua's, it will be a happier\l"
	.string "place for Pokémon, too.$"

LilycoveCity_Text_WailmerLeapOutOfWater: @ 81E3D1F
	.string "There! Wailmer!\n"
	.string "Leap out of the water now!$"

LilycoveCity_Text_GetLostMessingUpTraining: @ 81E3D4A
	.string "Hunh? What do you want?\p"
	.string "You're messing up our training,\n"
	.string "so can you, like, get lost?$"

LilycoveCity_Text_ContestHallInTown: @ 81E3D9E
	.string "There's a Pokémon Contest Hall\n"
	.string "right in this here town. \p"
	.string "That means well-raised Pokémon will\n"
	.string "come from all over the country.\p"
	.string "My heart swells with excitement!$"

LilycoveCity_Text_StrangeCaveInCove: @ 81E3E3C
	.string "Have you seen that strange cave in\n"
	.string "the cove at the edge of town?$"

LilycoveCity_Text_GoingToMoveDeleterForHMs: @ 81E3E7D
	.string "I'm going to teach my Pokémon some new\n"
	.string "moves for entering a Contest.\p"
	.string "So, I'm going to see the Move Deleter\n"
	.string "and make it forget HM moves.$"

LilycoveCity_Text_ImFromKanto: @ 81E3F05
	.string "I came from Kanto.\p"
	.string "The Hoenn region is beautiful with\n"
	.string "all its water and verdant nature.\p"
	.string "Hunh? Wait a second…\p"
	.string "Could there be rare Pokémon that live\n"
	.string "only in this area?$"

LilycoveCity_Text_TeamAquaBeenTrainingWailmer: @ 81E3FAB
	.string "Team Aqua's been training their\n"
	.string "Wailmer in the cove.\p"
	.string "We Sailors can't get our boats out\n"
	.string "to sea with them in the way!$"

LilycoveCity_Text_SomeonePuntedTeamAquaOut: @ 81E4020
	.string "Ahoy, did you know?\p"
	.string "Someone punted Team Aqua out of\n"
	.string "the way for us!\p"
	.string "That got the Wailmer out of the cove,\n"
	.string "so we can get our boats out again.$"

LilycoveCity_Text_SomeoneStoleMyPokemon: @ 81E40AD
	.string "I was taking a relaxing snooze at the\n"
	.string "seaside inn to the sound of waves…\p"
	.string "When someone stole my Pokémon!\p"
	.string "Who's the abductor?\n"
	.string "Team Aqua? Is it Team Aqua?$"

LilycoveCity_Text_MissingPokemonCameBack: @ 81E4145
	.string "My missing Pokémon…\n"
	.string "It came back without me noticing!$"

LilycoveCity_Text_ImArtDealer: @ 81E417B
	.string "I'm an Art Dealer.\p"
	.string "I am a buyer and seller of fine art,\n"
	.string "especially paintings.\p"
	.string "I've heard that the Museum here has\n"
	.string "magnificent works on exhibit…$"

LilycoveCity_Text_SeaRemainsForeverYoung: @ 81E420B
	.string "Even as we grow old and wrinkled,\n"
	.string "the sea remains forever young with\l"
	.string "the vivid brilliance of life…\p"
	.string "Fwohoho fwohohohoho…$"

LilycoveCity_Text_SixtyYearsAgoHusbandProposed: @ 81E4283
	.string "It was sixty years ago that my husband\n"
	.string "proposed to me here.\l"
	.string "The sea remains as beautiful as ever.\p"
	.string "Mufufufu mufufufufufu…$"

LilycoveCity_Text_TeamAquaRenovatedCavern: @ 81E42FC
	.string "Hm, you know of the peculiar cavern\n"
	.string "in this cove?\p"
	.string "That had been a natural formation,\n"
	.string "but then that Team Aqua lot came\l"
	.string "along and made their renovations.\p"
	.string "They call themselves\n"
	.string "the “nature-loving Team Aqua”!\p"
	.string "But what they do and what they say\n"
	.string "don't match at all!$"

LilycoveCity_Text_TeamAquaLotGoneForGood: @ 81E43FF
	.string "That cave in the cove…\p"
	.string "I didn't notice it right away,\n"
	.string "but it's completely empty now.\p"
	.string "That Team Aqua lot, they must\n"
	.string "have gone away for good.$"

LilycoveCity_Text_CitySign: @ 81E448B
	.string "Lilycove City\p"
	.string "“Where the land ends and the\n"
	.string "sea begins.”$"

LilycoveCity_Text_ContestHallSign: @ 81E44C3
	.string "Pokémon Contest Hall\n"
	.string "“The gathering place for Trainers!”$"

LilycoveCity_Text_MotelSign: @ 81E44FC
	.string "Cove Lily Motel\p"
	.string "“Remember us as Cove Lily of\n"
	.string "Lilycove.”$"

LilycoveCity_Text_MuseumSign: @ 81E4534
	.string "Lilycove Museum\p"
	.string "“Pokémon Masterpiece Collection\n"
	.string "on exhibit!”$"

LilycoveCity_Text_MuseumSignPlayersExhibit: @ 81E4571
	.string "Lilycove Museum\p"
	.string "“{PLAYER}'s Pokémon Collection\n"
	.string "on exhibit!”$"

LilycoveCity_Text_HarborSignUnderConstruction: @ 81E45A7
	.string "Lilycove City Harbor\p"
	.string "“The ferry S.S. Tidal is under\n"
	.string "construction in Slateport City.\p"
	.string "“Service is scheduled to begin\n"
	.string "shortly.”$"

LilycoveCity_Text_HarborSign: @ 81E4624
	.string "Lilycove City Harbor\p"
	.string "“Enjoy a delightful cruise on\n"
	.string "the ferry S.S. Tidal.”$"

LilycoveCity_Text_TrainerFanClubSign: @ 81E466E
	.string "Pokémon Trainer Fan Club\p"
	.string "The names of Trainers are scribbled\n"
	.string "all over the sign…$"

LilycoveCity_Text_DepartmentStoreSign: @ 81E46BE
	.string "Lilycove Department Store\p"
	.string "“Overflowing with great merchandise\n"
	.string "and excitement!\p"
	.string "“A great place to find that something\n"
	.string "you need!”$"

LilycoveCity_Text_MoveDeletersHouseSign: @ 81E473D
	.string "Move Deleter's House\p"
	.string "“Unwanted Pokémon moves deleted.”$"

LilycoveCity_Text_DoYouKnowAboutBerryBlender: @ 81E4774
	.string "Do you know about the machine\n"
	.string "Berry Blender?$"

LilycoveCity_Text_FasterSpinBetterPokeblocks: @ 81E47A1
	.string "People have to work together to get it\n"
	.string "to spin faster.\p"
	.string "The faster you can make it spin, the\n"
	.string "better {POKEBLOCK}s you can get, I've heard.$"

LilycoveCity_Text_ExplainBerryBlender: @ 81E4824
	.string "It's used for making a kind of candy\n"
	.string "called a {POKEBLOCK}.\p"
	.string "If you give a good {POKEBLOCK} to a Pokémon,\n"
	.string "its condition will improve by a lot.$"

LilycoveCity_Text_HeardTowerCalledSkyPillar: @ 81E48A5
	.string "I heard there's a tower somewhere out\n"
	.string "on the sea routes.\p"
	.string "It's called the Sky Pillar, I hear.$"

LilycoveCity_Text_SawTallTowerOnRoute131: @ 81E4902
	.string "I saw this tall tower somewhere\n"
	.string "around Route 131.\p"
	.string "Could that possibly be…?$"

LilycoveCity_Text_JustArrivedAndSawRarePokemon: @ 81E494D
	.string "We just arrived here on our\n"
	.string "honeymoon vacation.\p"
	.string "We happened to see a Dragon-type\n"
	.string "Pokémon flying way up in the sky.\p"
	.string "Do cool Pokémon like that live in\n"
	.string "the Hoenn region?$"

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon: @ 81E49F4
	.string "On our honeymoon, we vowed to see as\n"
	.string "many rare Pokémon as we can.\p"
	.string "So we were delighted to see a rare\n"
	.string "Pokémon as soon as we arrived.\p"
	.string "I mean, we are totally happy!$"

