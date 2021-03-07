.set LOCALID_BLENDER_WOMAN, 4
.set LOCALID_BLENDER_BOY, 5
.set LOCALID_BLENDER_GIRL, 7

LavaridgeTown_ContestLobby_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_ContestLobby_OnTransition
	.byte 0

LavaridgeTown_ContestLobby_OnTransition:
	call ContestLobby_EventScript_TryShowContestReporter
	end

LavaridgeTown_ContestLobby_EventScript_Man::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestLobby_Text_Man, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestLobby_EventScript_LittleGirl::
	lockall
	faceplayer
	goto_if_set FLAG_RECEIVED_POKEBLOCK_CASE, LavaridgeTown_ContestLobby_EventScript_LittleGirlHaveCase
	msgbox LavaridgeTown_ContestLobby_Text_LadyGaveMePokeblockCase, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestLobby_EventScript_LittleGirlHaveCase::
	msgbox LavaridgeTown_ContestLobby_Text_MakePokeblocksDifferentBerries, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_ContestLobby_EventScript_Girl::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestLobby_Text_Girl, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestLobby_EventScript_Expert::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestLobby_Text_Expert, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestLobby_EventScript_Boy::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestLobby_Text_Boy, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestLobby_EventScript_Woman::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestLobby_Text_Woman, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestLobby_EventScript_BerryBlender3::
	lockall
	setvar NUM_OPPONENTS, 3
	applymovement LOCALID_BLENDER_BOY, Common_Movement_FaceOriginalDirection
	applymovement LOCALID_BLENDER_GIRL, Common_Movement_FaceOriginalDirection
	applymovement LOCALID_BLENDER_WOMAN, BerryBlender_Movement_BlendLeaderWalkInPlace
	waitmovement 0
	msgbox BerryBlender_Text_WantToBlendPokeblocksWithUs, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BerryBlender_EventScript_TryUseBlender3
	goto BerryBlender_EventScript_DeclineBlender3
	end

LavaridgeTown_ContestLobby_EventScript_ContestReceptionist::
	setvar VAR_CONTEST_LOBBY_MAP, MAP_LAVARIDGE_TOWN_CONTEST_LOBBY
	goto ContestLobby_EventScript_ContestReceptionist
	end

LavaridgeTown_ContestLobby_Text_Man:
	.string "I want to raise a Pokémon that's\n"
	.string "the ultimate in “great” for both\l"
	.string "battles and Contests.\p"
	.string "It's vexing, trying to figure out\n"
	.string "which moves I should make it learn.$"

LavaridgeTown_ContestLobby_Text_LadyGaveMePokeblockCase:
	.string "Yippee!\p"
	.string "The lady at the reception counter\n"
	.string "gave me a case for {POKEBLOCK}s!$"

LavaridgeTown_ContestLobby_Text_MakePokeblocksDifferentBerries:
	.string "Make {POKEBLOCK}s and put them in there.\p"
	.string "When you make a {POKEBLOCK}, everyone\n"
	.string "has to put in a different Berry.$"

LavaridgeTown_ContestLobby_Text_Girl:
	.string "Do any of your friends have any\n"
	.string "Berries?\p"
	.string "You can use that Berry Blender and\n"
	.string "make {POKEBLOCK}s with your firends!\p"
	.string "You should try it - it's a lot of fun!$"

LavaridgeTown_ContestLobby_Text_Expert:
	.string "I love making {POKEBLOCK}s.\p"
	.string "I always have some Berries with me.\p"
	.string "If you'd like, we could make some\n"
	.string "{POKEBLOCK}s together using the\l"
	.string "Berry Blender.$"

LavaridgeTown_ContestLobby_Text_Boy:
	.string "Let's get blending already!$"

LavaridgeTown_ContestLobby_Text_Woman:
	.string "If you win a Contest, they put up a\n"
	.string "poster of your Pokémon on the wall.\p"
	.string "It will have a portrait of your\n"
	.string "Pokémon and both your names.$"
