FortreeCity_House1_MapScripts:: @ 82162BA
	.byte 0

FortreeCity_House1_EventScript_Man:: @ 81FC3CE
	msgbox FortreeCity_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Woman:: @ 81FC3D7
	msgbox FortreeCity_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon:: @ 81FC3E0
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, 0
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_LotToBeSaidForLivingOnIsland: @ 81FC3F3
	.string "There's a lot to be said for living in\n"
	.string "the trees like this in harmony with\l"
	.string "Pokémon and the family.$"

FortreeCity_House1_Text_LifeGoesSlowlyOnIsland: @ 81FC45B
	.string "I left the major city of Lilycove\n"
	.string "when I married my husband here.\p"
	.string "Life goes by slowly up here in the\n"
	.string "trees. But being surrounded by\l"
	.string "nature--that's happiness, too.$"

FortreeCity_House1_Text_Zigzagoon: @ 81FC510
	.string "Zigzagoon: Guguuh!$"

