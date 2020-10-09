RedClayTunnels_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RedClayTunnels_OnTransition
	.byte 0

RedClayTunnels_OnTransition:
	setflag FLAG_LANDMARK_RED_CLAY_TUNNELS
	end
