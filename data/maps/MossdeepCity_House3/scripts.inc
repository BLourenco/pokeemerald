MossdeepCity_House3_MapScripts:: @ 82225C2
	.byte 0

MossdeepCity_House3_EventScript_NetBallFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DIVE_BALLS, MossdeepCity_House3_EventScript_ReceivedDiveBalls
	msgbox MossdeepCity_House3_Text_TakeDiveBalls, MSGBOX_DEFAULT
	giveitem ITEM_DIVE_BALL, 5
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_DIVE_BALLS
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_ReceivedDiveBalls::
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_Text_TakeDiveBalls:
	.string "Hey there, Trainer!\p"
	.string "Some really rare Pokémon live all\n"
	.string "the way down on the seafloor.\p"
	.string "That's why you should make sure to\n"
	.string "bring some Dive Balls if you ever dive\l"
	.string "down there. Here, take a few!$"

MossdeepCity_House3_Text_GoAfterSeafloorPokemon:
	.string "Go after the seafloor Pokémon with\n"
	.string "your Dive Balls.$"

