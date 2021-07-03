VerdanturfTown_House_MapScripts:: @ 820335E
	.byte 0

VerdanturfTown_House_EventScript_Woman1:: @ 820335F
	msgbox VerdanturfTown_House_Text_TrainersGatherAtPokemonLeague, MSGBOX_NPC
	end

VerdanturfTown_House_EventScript_Woman2:: @ 8203368
	msgbox VerdanturfTown_House_Text_DefeatEliteFourInARow, MSGBOX_NPC
	end

VerdanturfTown_House_EventScript_Trader:: @ 8264FED
	lock
	faceplayer
	goto_if_set FLAG_VERDANTURF_TRADE_DONE, VerdanturfTown_House_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_WOOLOO
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox VerdanturfTown_House_Text_WouldYouLikeToTrade, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq VerdanturfTown_House_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	compare VAR_0x8004, 255
	goto_if_eq VerdanturfTown_House_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne VerdanturfTown_House_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox VerdanturfTown_House_Text_PromiseIllBeGoodToIt, MSGBOX_DEFAULT
	setflag FLAG_VERDANTURF_TRADE_DONE
	release
	end

VerdanturfTown_House_EventScript_DeclineTrade:: @ 826506B
	msgbox VerdanturfTown_House_Text_WellThatsFineToo, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_House_EventScript_NotRequestedMon:: @ 8265075
	bufferspeciesname 0, VAR_0x8009
	msgbox VerdanturfTown_House_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_House_EventScript_TradeCompleted:: @ 8265083
	msgbox VerdanturfTown_House_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_House_Text_TrainersGatherAtPokemonLeague: @ 8203371
	.string "Far away, deep in Ever Grande City,\n"
	.string "is the Pokémon League.\p"
	.string "The Trainers who gather there are\n"
	.string "all frighteningly well skilled.$"

VerdanturfTown_House_Text_DefeatEliteFourInARow: @ 82033EE
	.string "In the Pokémon League, I think the\n"
	.string "rules say that you have to battle the\l"
	.string "Elite Four all in a row.\p"
	.string "If you lose to any of them, you have\n"
	.string "to begin your challenge again from the\l"
	.string "first one.$"

VerdanturfTown_House_Text_WouldYouLikeToTrade: @ 826508D
	.string "My Pokémon is a {STR_VAR_2}.\n"
	.string "Do you know it?\l"
	.string "It's quite cute and rather nice.\p"
	.string "This little one, I could trade with\n"
	.string "pride!\p"
	.string "Would you like to trade me a {STR_VAR_1}\n"
	.string "for my {STR_VAR_2}?$"

VerdanturfTown_House_Text_PromiseIllBeGoodToIt: @ 8265128
	.string "Oh, it's adorable!\n"
	.string "Thank you!\l"
	.string "I promise I'll be good to it!\p"
	.string "Oh! I hope you'll be good to\n"
	.string "my {STR_VAR_2}, too!$"

VerdanturfTown_House_Text_DontTradeForAnythingButMon: @ 826518D
	.string "Oh, I'm sorry!\n"
	.string "I don't intend to trade for anything\l"
	.string "but a {STR_VAR_1}.$"

VerdanturfTown_House_Text_WellThatsFineToo: @ 82651CB
	.string "Oh, you won't?\n"
	.string "Well, that's fine, too.\l"
	.string "Please come visit us again.$"

VerdanturfTown_House_Text_SkittySoMuchCuterThanImagined: @ 826520E
	.string "Giggle!\n"
	.string "A Mareep is so much cuter than I had\l"
	.string "imagined. I'm delighted!$"
