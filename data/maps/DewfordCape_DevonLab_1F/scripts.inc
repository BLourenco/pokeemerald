DewfordCape_DevonLab_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordCape_DevonLab_1F_OnTransition
	.byte 0

DewfordCape_DevonLab_1F_OnTransition:
	setflag FLAG_LANDMARK_DEVON_LAB
	call DewfordCape_DevonLab_1F_EventScript_SetLights
	end

DewfordCape_DevonLab_1F_EventScript_SetLights::
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_1F_EventScript_SetLightsOn
	end

DewfordCape_DevonLab_1F_EventScript_SetLightsOn::
	setweather WEATHER_NONE
	doweather
	return

DewfordCape_DevonLab_1F_EventScript_RareRocksStonesDisplay::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_RareRocksStonesDisplay, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_RocksMetalDisplay::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_RocksMetalDisplay, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_PrototypesProductsDisplay::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_PrototypesProductsDisplay, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_MachineCylindrical::
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_1F_EventScript_MachineCylindricalOn
	goto DewfordCape_DevonLab_1F_EventScript_MachineCylindricalOff
	end

DewfordCape_DevonLab_1F_EventScript_MachineCylindricalOn::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_MachineCylindricalOn, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_MachineCylindricalOff::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_MachineCylindricalOff, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_MaintainenceBox::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_MaintainenceBox, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_Intercom::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_Intercom, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_Computer::
	goto_if_set FLAG_POWERED_ON_DEVON_LAB, DewfordCape_DevonLab_1F_EventScript_ComputerOn
	goto DewfordCape_DevonLab_1F_EventScript_ComputerOff
	end

DewfordCape_DevonLab_1F_EventScript_ComputerOn::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_ComputerOn, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_ComputerOff::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_ComputerOff, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_Bookshelf::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_Bookshelf, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_NoFoodNotice::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_NoFoodNotice, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_BulletinBoardFireDrill::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_BulletinBoardFireDrill, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_EventScript_BulletinBoardSellingSofa::
	lock
	msgbox DewfordCape_DevonLab_1F_Text_BulletinBoardSellingSofa, MSGBOX_DEFAULT
	release
	end

DewfordCape_DevonLab_1F_Text_RareRocksStonesDisplay:
	.string "It's a collection of rare rocks\n"
	.string "and stones.$"

DewfordCape_DevonLab_1F_Text_RocksMetalDisplay:
	.string "Samples of rocks and metal are\n"
	.string "displayed in the glass case.$"

DewfordCape_DevonLab_1F_Text_PrototypesProductsDisplay:
	.string "Prototypes and test products fill\n"
	.string "the glass display case.$"

DewfordCape_DevonLab_1F_Text_MachineCylindricalOff:
	.string "It's a machine with some sort of\n"
	.string "chamber in the center.\p"
	.string "The meters on the front aren't moving.$"

DewfordCape_DevonLab_1F_Text_MachineCylindricalOn:
	.string "It's a machine with some sort of\n"
	.string "chamber in the center.\p"
	.string "It's making a low humming sound.$"

DewfordCape_DevonLab_1F_Text_MaintainenceBox:
	.string "It's a maintainence box.\p"
	.string "It's locked tight.$"

DewfordCape_DevonLab_1F_Text_Intercom:
	.string "It's an intercom.\p"
	.string "{PLAYER} presses the button and\n"
	.string "speaks into the intercom…\p"
	.string "… … … … … …\p"
	.string "No response.$"

DewfordCape_DevonLab_1F_Text_ComputerOff:
	.string "It's a computer, but it's shut off.$"

DewfordCape_DevonLab_1F_Text_ComputerOn:
	.string "It's a computer.\p"
	.string "The monitor is displaying the\n"
	.string "login screen.\p"
	.string "Good luck guessing the password,\n"
	.string "though.$"

DewfordCape_DevonLab_1F_Text_Bookshelf:
	.string "It's a bookshelf lined with various\n"
	.string "scientific books and research notes.$"

DewfordCape_DevonLab_1F_Text_NoFoodNotice:
	.string "It's a notice:\p"
	.string "“No food or drinks allowed near\n"
	.string "any electronics. Thank you!”$"

DewfordCape_DevonLab_1F_Text_BulletinBoardFireDrill:
	.string "There's a large notice pinned to\n"
	.string "the bulletin board:\p"
	.string "“A reminder for all staff that there\n"
	.string "will be a fire drill this Friday.\p"
	.string "Participation is mandatory.”$"

DewfordCape_DevonLab_1F_Text_BulletinBoardSellingSofa:
	.string "There's a post pinned to the\n"
	.string "bulletin board:\p"
	.string "“Sofa for sale. If interested, please\n"
	.string "contact me on my PokéNav.”$"
