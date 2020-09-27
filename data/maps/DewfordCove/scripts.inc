DewfordCove_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordCove_OnTransition
	.byte 0

DewfordCove_OnTransition:
	setflag FLAG_LANDMARK_DEWFORD_COVE
	end

DewfordCove_EventScript_TrainerTipsSign::
	msgbox DewfordCove_Text_TrainerTips, MSGBOX_SIGN
	end

DewfordCove_Text_TrainerTips:
	.string "TRAINER TIPS\p"
	.string "Some Pokémon live under rocks.\n"
	.string "Smash those rocks to uncover them!$"
