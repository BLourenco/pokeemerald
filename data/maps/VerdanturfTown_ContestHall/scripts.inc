VerdanturfTown_ContestHall_MapScripts::
	.byte 0

VerdanturfTown_ContestHall_EventScript_Youngster::
	lockall
	faceplayer
	msgbox VerdanturfTown_ContestHall_Text_CantWinEverywhere, MSGBOX_DEFAULT
	releaseall
	end

VerdanturfTown_ContestHall_EventScript_Woman::
	lockall
	faceplayer
	msgbox VerdanturfTown_ContestHall_Text_MonAllTheseRibbons, MSGBOX_DEFAULT
	releaseall
	end

VerdanturfTown_ContestHall_EventScript_Man::
	lockall
	faceplayer
	msgbox VerdanturfTown_ContestHall_Text_DoAllRightInPreliminary, MSGBOX_DEFAULT
	releaseall
	end

VerdanturfTown_ContestHall_EventScript_SuperRankStageSign::
	msgbox VerdanturfTown_ContestHall_Text_SuperRankStage, MSGBOX_SIGN
	end

VerdanturfTown_ContestHall_Text_DoAllRightInPreliminary:
	.string "We do all right in the preliminary round,\n"
	.string "but we can never win the appeals…\p"
	.string "Maybe it means I have to watch what\n"
	.string "other contestants are doing…$"

VerdanturfTown_ContestHall_Text_MonAllTheseRibbons:
	.string "See!\n"
	.string "My Pokémon won all these Ribbons!\p"
	.string "Have your Pokémon earned any Ribbons?\n"
	.string "You can check them on your PokéNav.$"

VerdanturfTown_ContestHall_Text_CantWinEverywhere:
	.string "I can't beat Gym Leaders…\p"
	.string "I can't win any Contests…\p"
	.string "I've been here, there, and everywhere,\n"
	.string "and it's all for naught…$"

VerdanturfTown_ContestHall_Text_SuperRankStage:
	.string "Pokémon Contests\n"
	.string "Super Rank Stage!$"

