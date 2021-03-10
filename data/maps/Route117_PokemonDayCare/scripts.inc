Route117_PokemonDayCare_MapScripts:: @ 822BBB1
	map_script MAP_SCRIPT_ON_TRANSITION, Route117_PokemonDayCare_OnTransition
	.byte 0

Route117_PokemonDayCare_OnTransition: @ 822BBB7
	setflag FLAG_LANDMARK_POKEMON_DAYCARE
	end

Route117_PokemonDayCare_EventScript_EggMan::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DAYCARE_GIFT_EGG, Route117_PokemonDayCare_EventScript_ReceivedEgg
	msgbox Route117_PokemonDayCare_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route117_PokemonDayCare_EventScript_DeclineEgg
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq Route117_PokemonDayCare_EventScript_NoRoomForEgg
	msgbox Route117_PokemonDayCare_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_DAYCARE_GIFT_EGG
	playfanfare MUS_OBTAIN_ITEM
	message Route117_PokemonDayCare_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_TOGEPI
	release
	end

Route117_PokemonDayCare_EventScript_ReceivedEgg::
	msgbox Route117_PokemonDayCare_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_NoRoomForEgg::
	msgbox Route117_PokemonDayCare_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_DeclineEgg::
	msgbox Route117_PokemonDayCare_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_Text_HaveEggWillYouTakeIt:
	.string "I left my Pokémon at the Day Care,\n"
	.string "and when I came back, there was an Egg!\p"
	.string "Problem is, I don't think I can take\n"
	.string "care of it. I'm just too busy!\p"
	.string "I've heard Eggs hatch when carried by\n"
	.string "Trainers and their Pokémon.\p"
	.string "You're a Trainer, right?\n"
	.string "Do you want to take this Egg?$"

Route117_PokemonDayCare_Text_HopeYoullWalkPlentyWithEgg:
	.string "Good! I hope you'll take good care of\n"
	.string "this Egg!$"

Route117_PokemonDayCare_Text_ReceivedTheEgg:
	.string "{PLAYER} received the Egg.$"

Route117_PokemonDayCare_Text_NoRoomForThisEgg:
	.string "Oops! You're carrying too many Pokémon.\n"
	.string "There's no room for this Egg…$"

Route117_PokemonDayCare_Text_AsYouWishThen:
	.string "All right, then…\p"
	.string "If you ever change your mind about\n"
	.string "hatching this Egg, come see me again.$"

Route117_PokemonDayCare_Text_EverySoOftenEggFoundAtDayCare:
	.string "Every so often, an Egg will be found at\n"
	.string "the Pokémon Day Care.\p"
	.string "I learned that firsthand.$"



