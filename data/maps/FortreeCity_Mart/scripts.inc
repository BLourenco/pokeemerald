FortreeCity_Mart_MapScripts:: @ 8217665
	.byte 0

FortreeCity_Mart_EventScript_Clerk:: @ 8217666
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

FortreeCity_Mart_EventScript_Clerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FortreeCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_Mart_Pokemart:
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_SHARP_BEAK
	.2byte ITEM_TM40_AERIAL_ACE
	.2byte ITEM_TM51_LOW_SWEEP
	.2byte ITEM_TM110_HEX
	.2byte ITEM_WOOD_MAIL
	.2byte ITEM_NONE
	release
	end

FortreeCity_Mart_EventScript_Woman:: @ 8217698
	msgbox FortreeCity_Mart_Text_SuperRepelBetter, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Girl:: @ 82176A1
	msgbox FortreeCity_Mart_Text_StockUpOnItems, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Boy:: @ 82176AA
	msgbox FortreeCity_Mart_Text_RareCandyMakesMonGrow, MSGBOX_NPC
	end

FortreeCity_Mart_Text_SuperRepelBetter: @ 82176B3
	.string "Super Repel lasts a long time,\n"
	.string "and it gets the job done.\p"
	.string "It's much better than an ordinary\n"
	.string "Repel.$"

FortreeCity_Mart_Text_StockUpOnItems: @ 8217715
	.string "I always stock up on more items than\n"
	.string "I'm sure I'll need.\p"
	.string "You never know what might happen.\n"
	.string "Better to be safe than sorry!$"

FortreeCity_Mart_Text_RareCandyMakesMonGrow: @ 821778E
	.string "A Rare Candy makes a Pokémon grow\n"
	.string "immediately by one level.$"

