DewfordCape_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, DewfordCape_OnLoad
	.byte 0

DewfordCape_OnLoad:
	call_if_unset FLAG_UNLOCKED_DEVON_LAB, DewfordCape_EventScript_LockDoor
	call_if_set FLAG_UNLOCKED_DEVON_LAB, DewfordCape_EventScript_UnlockDoor
	end

DewfordCape_EventScript_LockDoor::
	setmetatile 12, 6, METATILE_Dewford_LabDoorLocked, 1
	return

DewfordCape_EventScript_UnlockDoor::
	setmetatile 12, 6, METATILE_Dewford_LabDoor, 1
	return

DewfordCape_EventScript_DevonLabDoor::
	lockall
	goto_if_set FLAG_UNLOCKED_DEVON_LAB, DewfordCape_EventScript_TheDoorIsOpen
	checkitem ITEM_SECRET_KEY, 1
	compare VAR_RESULT, FALSE
	goto_if_eq DewfordCape_EventScript_TheDoorIsLocked
	msgbox DewfordCape_Text_InsertedKey, MSGBOX_DEFAULT
	playse SE_PIN
	setflag FLAG_UNLOCKED_DEVON_LAB
	call DewfordCape_EventScript_UnlockDoor
	special DrawWholeMapView
	releaseall
	end

DewfordCape_EventScript_TheDoorIsOpen::
	msgbox DewfordCape_Text_TheDoorIsOpen, MSGBOX_DEFAULT
	releaseall
	end

DewfordCape_EventScript_TheDoorIsLocked::
	msgbox DewfordCape_Text_TheDoorIsLocked, MSGBOX_DEFAULT
	releaseall
	end

DewfordCape_EventScript_DewfordCapeSign::
	msgbox DewfordCape_Text_DewfordCapeSign, MSGBOX_DEFAULT
	releaseall
	end

DewfordCape_EventScript_DevonLabSign::
	msgbox DewfordCape_Text_DevonLabSign, MSGBOX_DEFAULT
	releaseall
	end

DewfordCape_EventScript_Anton::
	trainerbattle_single TRAINER_ANTON, DewfordCape_Text_AntonIntro, DewfordCape_Text_AntonDefeat
	msgbox DewfordCape_Text_AntonPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordCape_EventScript_Curtis::
	trainerbattle_single TRAINER_CURTIS, DewfordCape_Text_CurtisIntro, DewfordCape_Text_CurtisDefeat
	msgbox DewfordCape_Text_CurtisPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordCape_EventScript_Ralph::
	trainerbattle_single TRAINER_RALPH, DewfordCape_Text_RalphIntro, DewfordCape_Text_RalphDefeat
	msgbox DewfordCape_Text_RalphPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordCape_EventScript_Otto::
	trainerbattle_single TRAINER_OTTO, DewfordCape_Text_OttoIntro, DewfordCape_Text_OttoDefeat
	msgbox DewfordCape_Text_OttoPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordCape_EventScript_Reid::
	trainerbattle_single TRAINER_REID, DewfordCape_Text_ReidIntro, DewfordCape_Text_ReidDefeat
	msgbox DewfordCape_Text_ReidPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordCape_EventScript_Dina::
	trainerbattle_double TRAINER_DINA_AND_JIM, DewfordCape_Text_DinaIntro, DewfordCape_Text_DinaDefeat, DewfordCape_Text_DinaNotEnoughMons
	msgbox DewfordCape_Text_DinaPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordCape_EventScript_Jim::
	trainerbattle_double TRAINER_DINA_AND_JIM, DewfordCape_Text_JimIntro, DewfordCape_Text_JimDefeat, DewfordCape_Text_JimNotEnoughMons
	msgbox DewfordCape_Text_JimPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordCape_Text_InsertedKey:
	.string "{PLAYER} inserted and turned the\n"
	.string "Key.\p"
	.string "The inserted Key stuck fast,\n"
	.string "but the door opened.$"

DewfordCape_Text_TheDoorIsOpen:
	.string "The door is open.$"

DewfordCape_Text_TheDoorIsLocked:
	.string "The door is locked.\p"
	.string "There's a sign on the door:\n"
	.string "“Shut down until further notice.”$"

DewfordCape_Text_DewfordCapeSign:
	.string "Dewford Cape$"

DewfordCape_Text_DevonLabSign:
	.string "Devon Laboratory$"
