Route122_MapScripts:: @ 81F6146
	map_script MAP_SCRIPT_ON_TRANSITION, Route122_OnTransition
	.byte 0

Route122_OnTransition:
	setflag FLAG_VISITED_ROUTE_122
	end

Route122_EventScript_RouteSign::
	msgbox Route122_Text_RouteSign, MSGBOX_SIGN
	end

Route122_Text_RouteSign:
	.string "Mt. Pyre$"
