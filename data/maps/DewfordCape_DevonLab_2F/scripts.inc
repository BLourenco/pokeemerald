DewfordCape_DevonLab_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordCape_DevonLab_2F_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, DewfordCape_DevonLab_2F_OnLoad
	.byte 0

DewfordCape_DevonLab_2F_OnTransition:
	setflag FLAG_LANDMARK_DEVON_LAB
	call DewfordCape_DevonLab_2F_EventScript_SetLights
	end

DewfordCape_DevonLab_2F_EventScript_SetLights::
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_2F_EventScript_SetLightsOn
	end

DewfordCape_DevonLab_2F_EventScript_SetLightsOn::
	setweather WEATHER_NONE
	doweather
	return

DewfordCape_DevonLab_2F_OnLoad::
	goto_if_set FLAG_UNLOCKED_DEVON_LAB_OFFICE, DewfordCape_DevonLab_2F_EventScript_SetOfficeUnlocked
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_2F_EventScript_SetOfficeLocked
	end

DewfordCape_DevonLab_2F_EventScript_SetOfficeUnlocked::	
	setmetatile 8, 8, METATILE_Lab_KeySwipe_Unlocked, 1
	setmetatile 6, 7, METATILE_Lab_LabTile_Clean, 0
	setmetatile 7, 7, METATILE_Lab_LabTile_Clean, 0
	setmetatile 6, 8, METATILE_Lab_LabTile_Clean, 0
	setmetatile 7, 8, METATILE_Lab_LabTile_Clean, 0
	setmetatile 6, 9, METATILE_Lab_LabTile_Clean, 0
	setmetatile 7, 9, METATILE_Lab_LabTile_Clean, 0
	return

DewfordCape_DevonLab_2F_EventScript_SetOfficeLocked::	
	setmetatile 8, 8, METATILE_Lab_KeySwipe_Locked, 1
	return

DewfordCape_DevonLab_2F_EventScript_CardKeyTerminal::
	goto_if_set FLAG_UNLOCKED_DEVON_LAB_OFFICE, DewfordCape_DevonLab_2F_EventScript_CardKeyTerminalUnlocked
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_2F_EventScript_CardKeyTerminalLocked
	goto DewfordCape_DevonLab_2F_EventScript_CardKeyTerminalUnpowered
	end 

DewfordCape_DevonLab_2F_EventScript_CardKeyTerminalUnpowered::
	lock
	msgbox DewfordCape_DevonLab_2F_Text_CardKeyTerminalUnpowered, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_2F_EventScript_CardKeyTerminalLocked::
	lock
	msgbox DewfordCape_DevonLab_2F_Text_CardKeyTerminalLocked, MSGBOX_DEFAULT
	checkitem ITEM_CARD_KEY, 1
	compare VAR_RESULT, TRUE
	goto_if_eq DewfordCape_DevonLab_2F_EventScript_CardKeyTerminalLockedHaveKey	
	release
	end

DewfordCape_DevonLab_2F_EventScript_CardKeyTerminalLockedHaveKey::
	msgbox DewfordCape_DevonLab_2F_Text_CardKeyTerminalYouSwipeTheKey, MSGBOX_DEFAULT
	playse SE_DOOR
	setflag FLAG_UNLOCKED_DEVON_LAB_OFFICE
	call DewfordCape_DevonLab_2F_EventScript_SetOfficeUnlocked
	special DrawWholeMapView
	msgbox DewfordCape_DevonLab_2F_Text_CardKeyTerminalTheDoorOpened, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_2F_EventScript_CardKeyTerminalUnlocked::
	lock
	msgbox DewfordCape_DevonLab_2F_Text_CardKeyTerminalUnlocked, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_2F_Text_LockedOfficeDoor:
	.string "It's an electronic door.\p"
	.string "It won't budge.$"

DewfordCape_DevonLab_2F_Text_CardKeyTerminalUnpowered:
	.string "It's a Card Key terminal.\p"
	.string "It doesn't seem to be powered.$"

DewfordCape_DevonLab_2F_Text_CardKeyTerminalLocked:
	.string "It's a Card Key terminal.\p"
	.string "The red light is on.$"

DewfordCape_DevonLab_2F_Text_CardKeyTerminalYouSwipeTheKey:
	.string "{PLAYER} swipes the Card Key…$"

DewfordCape_DevonLab_2F_Text_CardKeyTerminalTheDoorOpened:
	.string "The door opened!$"

DewfordCape_DevonLab_2F_Text_CardKeyTerminalUnlocked:
	.string "It's a Card Key terminal.\p"
	.string "The green light is on.$"
