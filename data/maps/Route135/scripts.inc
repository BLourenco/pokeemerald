Route135_MapScripts::
	.byte 0

Route135_EventScript_MarkAsVisitedTrigger::	
	setflag FLAG_VISITED_ROUTE_135
	setvar VAR_ROUTE135_STATE, 1
	end;

Route135_EventScript_RouteSign::
	msgbox Route135_Text_RouteSign, MSGBOX_SIGN
	end

Route135_EventScript_Tanya::
	trainerbattle_single TRAINER_TANYA, Route135_Text_TanyaIntro, Route135_Text_TanyaDefeat
	msgbox Route125_Text_TanyaPostBattle, MSGBOX_AUTOCLOSE
	end

Route135_EventScript_Henry::
	trainerbattle_single TRAINER_HENRY, Route135_Text_HenryIntro, Route135_Text_HenryDefeat
	msgbox Route135_Text_HenryPostBattle, MSGBOX_AUTOCLOSE
	end

Route135_EventScript_Aaron::
	trainerbattle_single TRAINER_AARON, Route135_Text_AaronIntro, Route135_Text_AaronDefeat
	msgbox Route135_Text_AaronPostBattle, MSGBOX_AUTOCLOSE
	end

Route135_EventScript_Marley::
	trainerbattle_single TRAINER_MARLEY, Route135_Text_MarleyIntro, Route135_Text_MarleyDefeat
	msgbox Route135_Text_MarleyPostBattle, MSGBOX_AUTOCLOSE
	end

Route135_EventScript_Alexa::
	trainerbattle_single TRAINER_ALEXA, Route135_Text_AlexaIntro, Route135_Text_AlexaDefeat
	msgbox Route135_Text_AlexaPostBattle, MSGBOX_AUTOCLOSE
	end

Route135_EventScript_Reed::
	trainerbattle_single TRAINER_REED, Route135_Text_ReedIntro, Route135_Text_ReedDefeat
	msgbox Route135_Text_ReedPostBattle, MSGBOX_AUTOCLOSE
	end

Route135_EventScript_Leonardo::
	trainerbattle_single TRAINER_LEONARDO, Route135_Text_LeonardoIntro, Route135_Text_LeonardoDefeat
	msgbox Route135_Text_LeonardoPostBattle, MSGBOX_AUTOCLOSE
	end

Route135_EventScript_Isobel::
	trainerbattle_single TRAINER_ISOBEL, Route135_Text_IsobelIntro, Route135_Text_IsobelDefeat
	msgbox Route135_Text_IsobelPostBattle, MSGBOX_AUTOCLOSE
	end

Route135_EventScript_TalkAboutMarsh::
	lock
	faceplayer
	msgbox Route135_Text_TalkAboutMarsh, MSGBOX_DEFAULT
	release
	end

Route135_Text_TalkAboutMarsh:
	.string "It constantly rains in this marsh.\n"
	.string "It makes it the perfect home for\l"
	.string "some pretty strong water Pokémon.$"

Route135_Text_RouteSign:
	.string "Route 135\n"
	.string "{UP_ARROW} Mt. Pyre\l"
	.string "{DOWN_ARROW} Pacifidlog Town$"
