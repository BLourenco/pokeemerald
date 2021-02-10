LavaridgeTown_Mart_MapScripts:: @ 81FF9CD
	.byte 0

LavaridgeTown_Mart_EventScript_Clerk:: @ 81FF9CE
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Mart_EventScript_Clerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LavaridgeTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_Mart_Pokemart:
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_CHARCOAL
	.2byte ITEM_FAB_MAIL
	.2byte ITEM_NONE
	release
	end

LavaridgeTown_Mart_EventScript_ExpertM:: @ 81FF9FE
	msgbox LavaridgeTown_Mart_Text_XSpeedFirstStrike, MSGBOX_NPC
	end

LavaridgeTown_Mart_EventScript_OldWoman:: @ 81FFA07
	msgbox LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney, MSGBOX_NPC
	end

LavaridgeTown_Mart_Text_XSpeedFirstStrike: @ 81FFA10
	.string "Use X Speed to add to a Pokémon's\n"
	.string "Speed in battle.\p"
	.string "That will help it get in the first\n"
	.string "strike--a decided advantage!$"

LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney: @ 81FFA83
	.string "On Mt. Chimney's peak, there's a local\n"
	.string "specialty that you can buy only there.\p"
	.string "Give it to a Pokémon--it will be elated.$"

