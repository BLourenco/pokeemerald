VerdanturfTown_Mart_MapScripts:: @ 8202586
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk:: @ 8202587
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_Mart_EventScript_Clerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart:
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_MIRACLE_SEED
	.2byte ITEM_TM03_WATER_PULSE
	.2byte ITEM_TM112_GRASSY_TERRAIN
	.2byte ITEM_TROPIC_MAIL
	.2byte ITEM_NONE
	release
	end

VerdanturfTown_Mart_EventScript_Boy:: @ 82025BA
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF:: @ 82025C3
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForContests, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass:: @ 82025CC
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_XSpecialIsCrucial: @ 82025D5
	.string "For any Pokémon match, X Special\n"
	.string "is crucial.\p"
	.string "It jacks up the power of some moves\n"
	.string "even though it's only for one battle.$"

VerdanturfTown_Mart_Text_NoStrategyGuidesForContests: @ 820264C
	.string "They don't seem to sell any winning\n"
	.string "strategy guides for Contests…\p"
	.string "It seems one must rely on one's\n"
	.string "own creativity after all…$"

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon: @ 82026C9
	.string "The Nest Ball works better on\n"
	.string "weakened Pokémon.\p"
	.string "Verdanturf is the only place you can\n"
	.string "buy it.$"

