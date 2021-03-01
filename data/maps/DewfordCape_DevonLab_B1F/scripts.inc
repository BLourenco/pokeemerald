DewfordCape_DevonLab_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordCape_DevonLab_B1F_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, DewfordCape_DevonLab_B1F_OnLoad
	.byte 0

DewfordCape_DevonLab_B1F_OnTransition:
	call DewfordCape_DevonLab_B1F_EventScript_SetLights
	end

DewfordCape_DevonLab_B1F_EventScript_SetLights::
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_B1F_EventScript_SetLightsOn
	end

DewfordCape_DevonLab_B1F_EventScript_SetLightsOn::
	setflashradius 0
	setweather WEATHER_NONE
	doweather
	return

DewfordCape_DevonLab_B1F_OnLoad::
	call_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_B1F_SetSwitchOn
	end

DewfordCape_DevonLab_B1F_SetSwitchOn::	
	setmetatile 23, 20, METATILE_Lab_WallSwitchTop_On, 1
	setmetatile 23, 21, METATILE_Lab_WallSwitchBottom_On, 1
	return

DewfordCape_DevonLab_B1F_EventScript_PowerSwitch::
	lock
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_B1F_EventScript_PowerSwitchAlreadyOn
	msgbox DewfordCape_DevonLab_B1F_Text_PowerSwitch, MSGBOX_YESNO
	compare VAR_RESULT, 1
	call_if_eq DewfordCape_DevonLab_B1F_EventScript_PowerSwitchTurnedOn
	release
	end

DewfordCape_DevonLab_B1F_EventScript_PowerSwitchTurnedOn::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_PowerSwitchTurnedOn, MSGBOX_DEFAULT
	closemessage
	call DewfordCape_DevonLab_B1F_SetSwitchOn
	special DrawWholeMapView
	playse SE_SWITCH
	setweather WEATHER_NONE
	doweather
	animateflash 0
	setflashradius 0
	msgbox DewfordCape_DevonLab_B1F_Text_ThePowerIsBackUp, MSGBOX_DEFAULT
	setflag FLAG_POWERED_ON_DEVON_LAB
	release
	end

DewfordCape_DevonLab_B1F_EventScript_PowerSwitchAlreadyOn::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_PowerSwitchAlreadyOn, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_MachineGauges::
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_B1F_EventScript_MachineGaugesOn
	goto DewfordCape_DevonLab_B1F_EventScript_MachineGaugesOff
	end

DewfordCape_DevonLab_B1F_EventScript_MachineGaugesOn::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_MachineGaugesOn, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_MachineGaugesOff::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_MachineGaugesOff, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_MachineButtons::
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_B1F_EventScript_MachineButtonsOn
	goto DewfordCape_DevonLab_B1F_EventScript_MachineButtonsOff
	end

DewfordCape_DevonLab_B1F_EventScript_MachineButtonsOn::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_MachineButtonsOn, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_MachineButtonsOff::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_MachineButtonsOff, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_MachineDisplay::
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_B1F_EventScript_MachineDisplayOn
	goto DewfordCape_DevonLab_B1F_EventScript_MachineDisplayOff
	end

DewfordCape_DevonLab_B1F_EventScript_MachineDisplayOn::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_MachineDisplayOn, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_MachineDisplayOff::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_MachineDisplayOff, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_MachineBarMeter::
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_B1F_EventScript_MachineBarMeterOn
	goto DewfordCape_DevonLab_B1F_EventScript_MachineBarMeterOff
	end

DewfordCape_DevonLab_B1F_EventScript_MachineBarMeterOn::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_MachineBarMeterOn, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_MachineBarMeterOff::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_MachineBarMeterOff, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_Laptop::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_Laptop, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_BulletinBoardPPE::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_BulletinBoardPPE, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_EventScript_BulletinBoardLostStapler::
	lock
	msgbox DewfordCape_DevonLab_B1F_Text_BulletinBoardLostStapler, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_B1F_Text_PowerSwitch:
	.string "It's a large red switch.\p"
	.string "Flip the switch?$"

DewfordCape_DevonLab_B1F_Text_PowerSwitchTurnedOn:
	.string "Who wouldn't?$"

DewfordCape_DevonLab_B1F_Text_ThePowerIsBackUp:
	.string "The power came back on!$"

DewfordCape_DevonLab_B1F_Text_PowerSwitchAlreadyOn:
	.string "The power switch has already\n"
	.string "been flipped.$"

DewfordCape_DevonLab_B1F_Text_MachineGaugesOff:
	.string "It's a machine with gauges.\p"
	.string "The needles aren't moving.$"

DewfordCape_DevonLab_B1F_Text_MachineGaugesOn:
	.string "It's a machine with gauges.\p"
	.string "The needles are moving slightly\n"
	.string "in place.$"

DewfordCape_DevonLab_B1F_Text_MachineButtonsOff:
	.string "It's a machine with many buttons.\p"
	.string "Who knows what its purpose is.$"

DewfordCape_DevonLab_B1F_Text_MachineButtonsOn:
	.string "It's a machine with many buttons.\p"
	.string "They're lit up in an assorment\n"
	.string "of colors.$"

DewfordCape_DevonLab_B1F_Text_MachineDisplayOff:
	.string "There's a display on this machine.\p"
	.string "It's turned off, though.$"

DewfordCape_DevonLab_B1F_Text_MachineDisplayOn:
	.string "There's a display on this machine.\p"
	.string "It shows a bunch of numbers.\n"
	.string "Not sure what they could mean.$"

DewfordCape_DevonLab_B1F_Text_MachineBarMeterOff:
	.string "There's a large bar meter on the\n"
	.string "front of this machine.\p"
	.string "It's not filled at all.$"

DewfordCape_DevonLab_B1F_Text_MachineBarMeterOn:
	.string "There's a large bar meter on the\n"
	.string "front of this machine.\p"
	.string "It's filled up to a green marking.\n"
	.string "Hopefully that's a good thing.$"

DewfordCape_DevonLab_B1F_Text_Laptop:
	.string "It's a laptop.\p"
	.string "The battery is dead.$"

DewfordCape_DevonLab_B1F_Text_BulletinBoardPPE:
	.string "There's a large notice pinned to\n"
	.string "the bulletin board:\p"
	.string "“Remember to wear the proper protective\n"
	.string "equipment when operating any heavy\l"
	.string "machinery.\p"
	.string "Failure to do so can result in serious\n"
	.string "and permanent injury.”$"

DewfordCape_DevonLab_B1F_Text_BulletinBoardLostStapler:
	.string "There's a post pinned to the\n"
	.string "bulletin board:\p"
	.string "“LOST: Red stapler. If you see it or know\n"
	.string "who has it, please let me know! Thanks!”$"
