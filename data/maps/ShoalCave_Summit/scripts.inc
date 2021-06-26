ShoalCave_Summit_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ShoalCave_Summit_OnTransition
	.byte 0

ShoalCave_Summit_OnTransition: @ 823434B
	setflag FLAG_LANDMARK_SHOAL_SUMMIT
	end

ShoalCave_Summit_EventScript_Glacia::
	lock
	faceplayer
	msgbox ShoalCave_Summit_Text_SnowInHoenn, MSGBOX_DEFAULT
	release
	end

ShoalCave_Summit_EventScript_FrozenWaterfall::
	msgbox ShoalCave_Summit_Text_FrozenWaterfall, MSGBOX_SIGN
	end

ShoalCave_Summit_Text_SnowInHoenn:
	.string "Glacia: Beautiful, is it not?\n"
	.string "Snowfall in Hoenn…\p"
	.string "The weather in this area is caused by\n"
	.string "the Pokémon living here.\p"
	.string "There's no where in Hoenn that was a\n"
	.string "suitable place for them to live, so\l"
	.string "they came here and changed the\l"
	.string "environment to meet their needs.\p"
	.string "Never underestimate the power\n"
	.string "of Pokémon…$"

ShoalCave_Summit_Text_FrozenWaterfall:
	.string "The waterfall is frozen solid!$"
