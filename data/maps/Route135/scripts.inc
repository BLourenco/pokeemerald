Route135_MapScripts::
	.byte 0

Route135_EventScript_MarkAsVisitedTrigger::	
	setflag FLAG_VISITED_ROUTE_135
	setvar VAR_ROUTE135_STATE, 1
	end;

Route135_EventScript_RouteSign::
	msgbox Route135_Text_RouteSign, MSGBOX_SIGN
	end

Route135_Text_RouteSign:
	.string "Route 135\n"
	.string "{UP_ARROW} Mt. Pyre\l"
	.string "{DOWN_ARROW} Pacifidlog Town$"
