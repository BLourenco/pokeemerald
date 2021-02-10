SootopolisCity_House1_MapScripts:: @ 822694C
	.byte 0

SootopolisCity_House1_EventScript_PowerUpPunchBlackBelt:: @ 822694D
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM98, SootopolisCity_House1_EventScript_ReceivedPowerUpPunch
	msgbox SootopolisCity_House1_Text_DevelopedThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM98_POWER_UP_PUNCH
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM98
	msgbox SootopolisCity_House1_Text_ExplainPowerUpPunch, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House1_EventScript_ReceivedPowerUpPunch:: @ 8226984
	msgbox SootopolisCity_House1_Text_ExplainPowerUpPunch, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House1_EventScript_Kecleon:: @ 822698E
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KECLEON, 0
	msgbox SootopolisCity_House1_Text_Kecleon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House1_Text_DevelopedThisTM: @ 82269A1
	.string "For thirty years I've remained in\n"
	.string "Sootopolis honing my skills.\p"
	.string "I developed an empowering TM.\n"
	.string "I bequeath it to you!$"

SootopolisCity_House1_Text_ExplainPowerUpPunch: @ 8226A13
	.string "TM98 contains PowerUpPunch! It's a move\n"
	.string "so horrible that I can't describe it.$"

SootopolisCity_House1_Text_Kecleon: @ 8226A60
	.string "Kecleon: Puu puhyaah.$"

