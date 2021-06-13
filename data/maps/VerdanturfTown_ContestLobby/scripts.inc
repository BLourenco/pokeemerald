.set LOCALID_BLENDER_MAN, 4
.set LOCALID_BLENDER_TWIN, 6

VerdanturfTown_ContestLobby_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_ContestLobby_OnTransition
	.byte 0

VerdanturfTown_ContestLobby_OnTransition:
	call ContestLobby_EventScript_TryShowContestReporter
	end

VerdanturfTown_ContestLobby_EventScript_Lass::
	lockall
	faceplayer
	msgbox VerdanturfTown_ContestLobby_Text_Lass, MSGBOX_DEFAULT
	releaseall
	end

VerdanturfTown_ContestLobby_EventScript_LittleBoy::
	lockall
	faceplayer
	msgbox VerdanturfTown_ContestLobby_Text_LittleBoy, MSGBOX_DEFAULT
	releaseall
	end

VerdanturfTown_ContestLobby_EventScript_Expert_M::
	lockall
	faceplayer
	msgbox VerdanturfTown_ContestLobby_Text_Expert_M, MSGBOX_DEFAULT
	releaseall
	end

VerdanturfTown_ContestLobby_EventScript_ArtistSmeargleGift::
	lockall
	faceplayer
	goto_if_set FLAG_RECEIVED_SMEARGLE, VerdanturfTown_ContestLobby_EventScript_TakeCareOfSmeargle
	msgbox VerdanturfTown_ContestLobby_Text_ArtistSmeargleGift, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq VerdanturfTown_ContestLobby_EventScript_ArtistSmeargleGiftDecline
	msgbox VerdanturfTown_ContestLobby_Text_ArtistSmeargleGiftAccept, MSGBOX_DEFAULT
	givemon SPECIES_SMEARGLE, 10, ITEM_NONE
	compare VAR_RESULT, 0
	goto_if_eq VerdanturfTown_ContestLobby_EventScript_ReceiveSmeargleParty
	compare VAR_RESULT, 1
	goto_if_eq VerdanturfTown_ContestLobby_EventScript_ReceiveSmearglePC
	goto Common_EventScript_NoMoreRoomForPokemon
	releaseall
	end

VerdanturfTown_ContestLobby_EventScript_ReceiveSmeargleParty::
	call VerdanturfTown_ContestLobby_EventScript_ReceivedSmeargleFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq VerdanturfTown_ContestLobby_EventScript_NicknameSmeargle
	setflag FLAG_RECEIVED_SMEARGLE
	end

VerdanturfTown_ContestLobby_EventScript_NicknameSmeargle::	
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	return

VerdanturfTown_ContestLobby_EventScript_ReceiveSmearglePC::
	call VerdanturfTown_ContestLobby_EventScript_ReceivedSmeargleFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq VerdanturfTown_ContestLobby_EventScript_TransferSmeargleToPC
	call Common_EventScript_NameReceivedBoxMon
	goto VerdanturfTown_ContestLobby_EventScript_TransferSmeargleToPC
	end

VerdanturfTown_ContestLobby_EventScript_TransferSmeargleToPC::
	call Common_EventScript_TransferredToPC
	setflag FLAG_RECEIVED_SMEARGLE
	end

VerdanturfTown_ContestLobby_EventScript_ReceivedSmeargleFanfare::
	bufferspeciesname 1, SPECIES_SMEARGLE
	playfanfare MUS_OBTAIN_ITEM
	message VerdanturfTown_ContestLobby_Text_PlayerReceivedSmeargle
	waitmessage
	waitfanfare
	bufferspeciesname 0, SPECIES_SMEARGLE
	return

VerdanturfTown_ContestLobby_EventScript_ArtistSmeargleGiftDecline::
	msgbox VerdanturfTown_ContestLobby_Text_ArtistSmeargleGiftDecline, MSGBOX_DEFAULT
	releaseall
	end

VerdanturfTown_ContestLobby_EventScript_TakeCareOfSmeargle::
	msgbox VerdanturfTown_ContestLobby_Text_TakeCareOfSmeargle, MSGBOX_DEFAULT
	releaseall
	end

VerdanturfTown_ContestLobby_EventScript_BerryBlender2::
	lockall
	setvar NUM_OPPONENTS, 2
	applymovement LOCALID_BLENDER_TWIN, Common_Movement_FaceOriginalDirection
	applymovement LOCALID_BLENDER_MAN, BerryBlender_Movement_BlendLeaderWalkInPlace
	waitmovement 0
	msgbox BerryBlender_Text_WantToBlendPokeblocksWithUs, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BerryBlender_EventScript_TryUseBerryBlender2
	goto BerryBlender_EventScript_DeclineBlender2
	end

VerdanturfTown_ContestLobby_EventScript_ContestReceptionist::
	setvar VAR_CONTEST_LOBBY_MAP, MAP_VERDANTURF_TOWN_CONTEST_LOBBY
	goto ContestLobby_EventScript_ContestReceptionist
	end

VerdanturfTown_ContestLobby_EventScript_ContestWinner::
	lockall
	fadescreen FADE_TO_BLACK
	showcontestpainting CONTEST_WINNER_VERDANTURF_HALL
	releaseall
	end

VerdanturfTown_ContestLobby_Text_Lass:
	.string "Hi, are you making any {POKEBLOCK}s?\p"
	.string "You should come by with a bunch of\n"
	.string "Berries sometime.$"

VerdanturfTown_ContestLobby_Text_LittleBoy:
	.string "They had a sketch of my Pokémon up\n"
	.string "on the wall over there, but they,\l"
	.string "changed it with a new one already.\p"
	.string "I'm going to enter my Hana in Contests\n"
	.string "so we can get her sketch up again!$"

VerdanturfTown_ContestLobby_Text_Expert_M:
	.string "I love making {POKEBLOCK}s.\p"
	.string "I always have some Berries with me.\p"
	.string "If you'd like, we could make some\n"
	.string "{POKEBLOCK}s together using the\l"
	.string "Berry Blender.$"

VerdanturfTown_ContestLobby_Text_Artist:
	.string "You see how they display a sketch of\n"
	.string "a Contest winner here?\p"
	.string "I sketch them!\p"
	.string "If any of your Pokémon wins a Contest,\n"
	.string "I'd gladly make a sketch of it!$"

VerdanturfTown_ContestLobby_Text_ArtistSmeargleGift:
	.string "My Smeargle just completed it's\n"
	.string "1000th Contest sketch!\p"
	.string "It's been creating sketches of\n"
	.string "Contest winners in this Hall for\l"
	.string "many years.\p"
	.string "I think it's ready to move on from\n"
	.string "sketching Contest winners.\p"
	.string "…Hey! You're a Trainer, aren't you?\p"
	.string "Will you let my Smeargle join you\n"
	.string "on your adventure?\p"
	.string "It wants to find new sources of\n"
	.string "inspiration, and travelling the world\l"
	.string "will help achieve that.\p"
	.string "What do you say?$"

VerdanturfTown_ContestLobby_Text_ArtistSmeargleGiftDecline:
	.string "That's a shame…\p"
	.string "If you ever change your mind, come\n"
	.string "back and see me.$"

VerdanturfTown_ContestLobby_Text_ArtistSmeargleGiftAccept:
	.string "That's great news!\p"
	.string "Smeargle, thanks for all your work!\n"
	.string "Now go out and see the world!$"

VerdanturfTown_ContestLobby_Text_PlayerReceivedSmeargle:
	.string "{PLAYER} received Smeargle!$"

VerdanturfTown_ContestLobby_Text_TakeCareOfSmeargle:
	.string "Don't worry, I can handle the sketches\n"
	.string "from now on.\p"
	.string "Have fun travelling the world with\n"
	.string "Smeargle!$"
