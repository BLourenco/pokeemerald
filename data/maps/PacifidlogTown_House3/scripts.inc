PacifidlogTown_House3_MapScripts:: @ 8203C10
	.byte 0

PacifidlogTown_House3_EventScript_Man:: @ 8203C11
	msgbox PacifidlogTown_House3_Text_ThisTownIsGreatForFishing, MSGBOX_NPC	
	end

PacifidlogTown_House3_EventScript_Girl:: @ 8203CB5
	msgbox PacifidlogTown_House3_Text_IsThatAPokedex, MSGBOX_NPC
	end

PacifidlogTown_House3_Text_ThisTownIsGreatForFishing: @ 8203EF1
	.string "This town is great for fishing!\p"
	.string "Just step outside and let your\n"
	.string "fishing line fly!$"

PacifidlogTown_House3_Text_IsThatAPokedex: @ 8203EF1
	.string "Is that a Pokédex?\p"
	.string "Did you get to meet a lot of different\n"
	.string "Pokémon?\p"
	.string "I wish I was like you.$"

