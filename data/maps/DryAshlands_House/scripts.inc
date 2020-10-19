DryAshlands_House_MapScripts::
	.byte 0

DryAshlands_House_EventScript_GoodRodFisherman:: @ 81F3E14
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_GOOD_ROD, DryAshlands_House_EventScript_ReceivedGoodRod
	msgbox DryAshlands_House_Text_YouAgreeGoodRodIsGood, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DryAshlands_House_EventScript_ReceiveGoodRod
	compare VAR_RESULT, NO
	goto_if_eq DryAshlands_House_EventScript_DeclineGoodRod
	end

DryAshlands_House_EventScript_ReceiveGoodRod:: @ 81F3E3E
	msgbox DryAshlands_House_Text_IdenticalMindsTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	setflag FLAG_RECEIVED_GOOD_ROD
	msgbox DryAshlands_House_Text_TryYourLuckFishing, MSGBOX_DEFAULT
	release
	end

DryAshlands_House_EventScript_DeclineGoodRod:: @ 81F3E5F
	msgbox DryAshlands_House_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

DryAshlands_House_EventScript_ReceivedGoodRod:: @ 81F3E69
	msgbox DryAshlands_House_Text_TryCatchingMonWithGoodRod, MSGBOX_DEFAULT
	release
	end

DryAshlands_House_Text_YouAgreeGoodRodIsGood: @ 81F427B
	.string "Hmm!\n"
	.string "A Good Rod is really good!\p"
	.string "Wouldn't you agree?$"

DryAshlands_House_Text_IdenticalMindsTakeThis: @ 81F42AF
	.string "Hmm!\n"
	.string "We're of identical minds!\p"
	.string "Hmm!\n"
	.string "Take this Good Rod!$"

DryAshlands_House_Text_TryYourLuckFishing: @ 81F42E7
	.string "Wherever there's water, try your luck\n"
	.string "at fishing.$"

DryAshlands_House_Text_DontYouLikeToFish: @ 81F4319
	.string "Don't you like to fish?$"

DryAshlands_House_Text_TryCatchingMonWithGoodRod: @ 81F4331
	.string "Try catching all sorts of Pokémon\n"
	.string "with your Good Rod.$"
