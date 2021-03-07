.set LOCALID_EXPERT_M, 2

SlateportCity_ContestLobby_MapScripts::
	.byte 0

SlateportCity_ContestLobby_EventScript_LittleGirl::
	lockall
	faceplayer
	goto_if_set FLAG_RECEIVED_POKEBLOCK_CASE, SlateportCity_ContestLobby_EventScript_LittleGirlHaveCase
	msgbox SlateportCity_ContestLobby_Text_LadyGaveMePokeblockCase, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_ContestLobby_EventScript_LittleGirlHaveCase::
	msgbox SlateportCity_ContestLobby_Text_MakePokeblocksDifferentBerries, MSGBOX_DEFAULT
	release
	end

SlateportCity_ContestLobby_EventScript_BerryBlender1::
	lockall
	setvar NUM_OPPONENTS, 1
	applymovement LOCALID_EXPERT_M, BerryBlender_Movement_BlendLeaderWalkInPlace
	waitmovement 0
	msgbox BerryBlender_Text_WantToMakePokeblocks, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BerryBlender_EventScript_TryUseBerryBlender1
	goto BerryBlender_EventScript_DeclineBlender1
	end

SlateportCity_ContestLobby_EventScript_Expert_M::
	lockall
	faceplayer
	msgbox SlateportCity_ContestLobby_Text_Expert_M, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_ContestLobby_EventScript_Boy1::
	lockall
	faceplayer
	msgbox SlateportCity_ContestLobby_Text_Boy1, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_ContestLobby_EventScript_Boy2::
	lockall
	faceplayer
	msgbox SlateportCity_ContestLobby_Text_Boy2, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_ContestLobby_EventScript_ContestReceptionist::
	call LilycoveCity_ContestLobby_EventScript_SpeakToContestReceptionist
	call LilycoveCity_ContestLobby_EventScript_LeadToContestHall
	special SetContestTrainerGfxIds
	call LilycoveCity_ContestLobby_EventScript_SetPlayerGfx
	call LilycoveCity_ContestLobby_EventScript_SetContestType
	call LilycoveCity_ContestLobby_EventScript_WarpToContestHall
	waitstate
	end

SlateportCity_ContestLobby_EventScript_SpeakToContestReceptionist::
	lock
	faceplayer
	compare VAR_CONTEST_PRIZE_PICKUP, 0
	goto_if_ne LilycoveCity_ContestLobby_EventScript_PickUpPrize
	call_if_set FLAG_RECEIVED_POKEBLOCK_CASE, LilycoveCity_ContestLobby_EventScript_ReceptionWelcome
	call_if_unset FLAG_RECEIVED_POKEBLOCK_CASE, LilycoveCity_ContestLobby_EventScript_GivePokeblockCase
	goto LilycoveCity_ContestLobby_EventScript_AskEnterContest
	end

SlateportCity_ContestLobby_Text_LadyGaveMePokeblockCase:
	.string "Yippee!\p"
	.string "The lady at the reception counter\n"
	.string "gave me a case for {POKEBLOCK}s!$"

SlateportCity_ContestLobby_Text_MakePokeblocksDifferentBerries:
	.string "Make {POKEBLOCK}s and put them in there.\p"
	.string "When you make a {POKEBLOCK}, everyone\n"
	.string "has to put in a different Berry.$"

SlateportCity_ContestLobby_Text_Expert_M:
	.string "I love making {POKEBLOCK}s.\p"
	.string "I always have some Berries with me.\p"
	.string "If you'd like, we could make some\n"
	.string "{POKEBLOCK}s together using the\l"
	.string "Berry Blender.$"

SlateportCity_ContestLobby_Text_Boy1:
	.string "Which Contest are you planning on\n"
	.string "entering?\p"
	.string "If you're entering a Cool Contest,\n"
	.string "a cool Pokémon has to be the one!\p"
	.string "Pick a Pokémon worthy of the Contest\n"
	.string "theme, and make sure it has the\l"
	.string "right set of moves to match.\p"
	.string "That's fundamental!$"

SlateportCity_ContestLobby_Text_Boy2:
	.string "I went in through the entrance and\n"
	.string "took a look around the Contest hall.\p"
	.string "Getting up on that big stage…\n"
	.string "It's going to be tense!$"
