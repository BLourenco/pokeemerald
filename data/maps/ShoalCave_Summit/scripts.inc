ShoalCave_Summit_MapScripts::
	.byte 0

ShoalCave_Summit_EventScript_Girl::
	lock
	faceplayer
	msgbox ShoalCave_Summit_Text_SnowInHoenn, MSGBOX_DEFAULT
	release
	end

ShoalCave_Summit_EventScript_FrozenWaterfall::
	msgbox ShoalCave_Summit_Text_FrozenWaterfall, MSGBOX_SIGN
	end

ShoalCave_Summit_Text_SnowInHoenn:
	.string "Amazing! I never thought I'd ever get\n"
	.string "to see it snow in Hoenn!\p"
	.string "The weather in this area is caused by\n"
	.string "the Pokémon living here.\p"
	.string "There's no where in Hoenn that was a\n"
	.string "suitable place for them to live, so\l"
	.string "they came here and changed the\l"
	.string "environment to meet their needs.\p"
	.string "Never underestimate Pokémon!$"

ShoalCave_Summit_Text_FrozenWaterfall:
	.string "The waterfall is frozen solid!$"
