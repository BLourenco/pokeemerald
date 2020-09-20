SlateportCity_PokemonFanClub_EventScript_SwaggerTM:: @ 82C7F16
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM87, SlateportCity_PokemonFanClub_EventScript_SwaggerReceived
	msgbox MoveTutor_Text_SwaggerGift, MSGBOX_DEFAULT
	giveitem ITEM_TM87
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM87
	release
	end
	
SlateportCity_PokemonFanClub_EventScript_SwaggerReceived:: @ 82C7F74
	msgbox MoveTutor_Text_SwaggerReceived, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_SmackDownTM:: @ 82C7F7E
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM69, MoveTutor_EventScript_SmackDownReceived
	msgbox MoveTutor_Text_SmackDownGift, MSGBOX_DEFAULT
	giveitem ITEM_TM69
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM69
	release
	end

MoveTutor_EventScript_SmackDownReceived:: @ 82C7FDC
	msgbox MoveTutor_Text_SmackDownReceived, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_EchoedVoiceTM:: @ 82C7FE6
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM100, MoveTutor_EventScript_EchoedVoiceReceived
	msgbox MoveTutor_Text_EchoedVoiceGift, MSGBOX_DEFAULT
	giveitem ITEM_TM100
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM100
	release
	end

MoveTutor_EventScript_EchoedVoiceReceived:: @ 82C8044
	msgbox MoveTutor_Text_EchoedVoiceReceived, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_House_EventScript_NaturePowerTM:: @ 82C804E
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM96, MoveTutor_EventScript_NaturePowerReceived
	msgbox MoveTutor_NaturePowerGift, MSGBOX_DEFAULT
	giveitem ITEM_TM96
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM96
	release
	end

MoveTutor_EventScript_NaturePowerReceived:: @ 82C80AC
	msgbox MoveTutor_Text_NaturePowerReceived, MSGBOX_DEFAULT
	release
	end

FallarborTown_Mart_EventScript_SmartStrikeTM:: @ 82C80B6
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM67, MoveTutor_EventScript_SmartStrikeReceived
	msgbox MoveTutor_Text_SmartStrikeGift, MSGBOX_DEFAULT
	giveitem ITEM_TM67
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM67
	release
	end

MoveTutor_EventScript_SmartStrikeReceived:: @ 82C8114
	msgbox MoveTutor_Text_SmartStrikeReceived, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_SleepTalkTM:: @ 82C811E
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM88, MoveTutor_EventScript_SleepTalkReceived
	msgbox MoveTutor_Text_SleepTalkGift, MSGBOX_DEFAULT
	giveitem ITEM_TM88
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM88
	release
	end

MoveTutor_EventScript_SleepTalkReceived:: @ 82C817C
	msgbox MoveTutor_Text_SleepTalkReceived, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_SubstituteTM:: @ 82C8186
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM90, MoveTutor_EventScript_SubstituteReceived
	msgbox MoveTutor_Text_SubstituteGift, MSGBOX_DEFAULT
	giveitem ITEM_TM90
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM90
	release
	end

MoveTutor_EventScript_SubstituteReceived:: @ 82C81E4
	msgbox MoveTutor_Text_SubstituteReceived, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PowerUpPunchTM:: @ 82C81EE
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM98, MoveTutor_EventScript_PowerUpPunchReceived
	msgbox MoveTutor_Text_PowerUpPunchGift, MSGBOX_DEFAULT
	giveitem ITEM_TM98
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM98
	release
	end

MoveTutor_EventScript_PowerUpPunchReceived:: @ 82C824C
	msgbox MoveTutor_Text_PowerUpPunchReceived, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_SwordsDanceTM:: @ 82C8256
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM75, MoveTutor_EventScript_SwordsDanceReceived
	msgbox MoveTutor_Text_SwordsDanceGift, MSGBOX_DEFAULT
	giveitem ITEM_TM75
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM75
	release
	end

MoveTutor_EventScript_SwordsDanceReceived:: @ 82C82B4
	msgbox MoveTutor_Text_SwordsDanceReceived, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_PokemonCenter_1F_EventScript_ExplosionTM:: @ 82C82BE
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM64, MoveTutor_EventScript_ExplosionReceived
	msgbox MoveTutor_Text_ExplosionGift, MSGBOX_DEFAULT
	giveitem ITEM_TM64
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM64
	release
	end

MoveTutor_EventScript_ExplosionReceived:: @ 82C831C
	msgbox MoveTutor_Text_ExplosionReceived, MSGBOX_DEFAULT
	release
	end