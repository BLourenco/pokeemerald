OldaleTown_Mart_MapScripts:: @ 81FC23F
	.byte 0

OldaleTown_Mart_EventScript_Clerk:: @ 81FC240
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_ExpandedItems
	pokemart OldaleTown_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_Pokemart_Basic: @ 81FC260
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_AWAKENING
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_NONE
	release
	end

OldaleTown_Mart_EventScript_Clerk2:: @ 8267ACC
	lock
	faceplayer
	goto_if_unset FLAG_ADVENTURE_STARTED, OldaleTown_Mart_Clerk2_CurrentlyRestocking
	message gText_HowMayIServeYou
	waitmessage
	pokemart OldaleTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart:
	.2byte ITEM_SILVER_POWDER
	.2byte ITEM_TM54_FALSE_SWIPE
	.2byte ITEM_RETRO_MAIL
	.2byte ITEM_NONE
	release
	end

OldaleTown_Mart_ExpandedItems:: @ 81FC26C
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_Clerk2_CurrentlyRestocking::
	msgbox OldaleTown_Mart_Text_CurrentlyRestocking, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_Woman:: @ 81FC28A
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_EventScript_PokeBallsInStock
	msgbox OldaleTown_Mart_Text_PokeBallsAreSoldOut, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_PokeBallsInStock:: @ 81FC29F
	msgbox OldaleTown_Mart_Text_ImGoingToBuyPokeBalls, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_Boy:: @ 81FC2A9
	msgbox OldaleTown_Mart_Text_RestoreHPWithPotion, MSGBOX_NPC
	end

OldaleTown_Mart_Text_PokeBallsAreSoldOut: @ 81FC2B2
	.string "The clerk says they're all sold out.\n"
	.string "I can't buy any Poké Balls.$"

OldaleTown_Mart_Text_ImGoingToBuyPokeBalls: @ 81FC2F3
	.string "I'm going to buy a bunch of Poké Balls\n"
	.string "and catch a bunch of Pokémon!$"

OldaleTown_Mart_Text_RestoreHPWithPotion: @ 81FC338
	.string "If a Pokémon gets hurt and loses its HP\n"
	.string "and faints, it won't be able to battle.\p"
	.string "To prevent your Pokémon from fainting,\n"
	.string "restore its HP with a Potion.$"

OldaleTown_Mart_Text_CurrentlyRestocking:
	.string "Sorry! We're currently restocking our\n"
	.string "inventory. Come back in a little bit!$"
