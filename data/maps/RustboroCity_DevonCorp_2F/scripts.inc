.set LOCALID_FOSSIL_SCIENTIST, 5

RustboroCity_DevonCorp_2F_MapScripts:: @ 8211857
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_2F_OnTransition
	.byte 0

RustboroCity_DevonCorp_2F_OnTransition: @ 821185D
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RustboroCity_DevonCorp_2F_EventScript_SetFossilReady:: @ 8211869
	setvar VAR_FOSSIL_RESURRECTION_STATE, 2
	return

RustboroCity_DevonCorp_2F_EventScript_TalkToPokemonScientist:: @ 821186F
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_BallScientist:: @ 8211886
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls:: @ 82118A6
	msgbox RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokenavScientist:: @ 82118B0
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_DevonCorp_2F_EventScript_HasPokenav
	msgbox RustboroCity_DevonCorp_2F_Text_IMadePokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_HasPokenav:: @ 82118D0
	msgbox RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokemonDreamsScientist:: @ 82118DA
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilScientist::
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
	checkitem ITEM_HELIX_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_DOME_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_OLD_AMBER, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_ROOT_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_CLAW_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_SKULL_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_ARMOR_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_COVER_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_PLUME_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_JAW_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_SAIL_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	release
	end

RustboroCity_DevonCorp_2F_EventScript_NoticeFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto RustboroCity_DevonCorp_2F_EventScript_WhichFossilToRevive
	end

RustboroCity_DevonCorp_2F_EventScript_WhichFossilToRevive::
	message RustboroCity_DevonCorp_2F_Text_WhichFossilToRevive
	waitmessage
	goto RustboroCity_DevonCorp_2F_EventScript_ChooseFossilFromBag
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseFossilFromBag::
	fadescreen FADE_TO_BLACK
    setvar VAR_RESULT, 0
    special FossilScientistOpenBagMenu
    waitstate
    compare VAR_RESULT, 0
    goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
    compare VAR_RESULT, 1
    goto_if_eq RustboroCity_DevonCorp_2F_EventScript_VerifyItemIsFossil
    end

RustboroCity_DevonCorp_2F_EventScript_VerifyItemIsFossil::
	specialvar VAR_RESULT, IsItemFossil
    compare VAR_RESULT, FALSE
    goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ThatsNotAFossil
    compare VAR_RESULT, TRUE
    goto_if_eq RustboroCity_DevonCorp_2F_EventScript_BufferFossilAndMonNames
    end

RustboroCity_DevonCorp_2F_EventScript_ThatsNotAFossil::
	msgbox RustboroCity_DevonCorp_2F_Text_ThatsNotAFossil, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_BufferFossilAndMonNames::
	switch VAR_ITEM_ID
	case ITEM_HELIX_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChooseHelixFossil
	case ITEM_DOME_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChooseDomeFossil
	case ITEM_OLD_AMBER, RustboroCity_DevonCorp_2F_EventScript_ChooseOldAmber
	case ITEM_ROOT_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChooseRootFossil
	case ITEM_CLAW_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChooseClawFossil
	case ITEM_SKULL_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChooseSkullFossil
	case ITEM_ARMOR_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChooseArmorFossil
	case ITEM_COVER_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChooseCoverFossil
	case ITEM_PLUME_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChoosePlumeFossil
	case ITEM_JAW_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChooseJawFossil
	case ITEM_SAIL_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ChooseSailFossil

RustboroCity_DevonCorp_2F_EventScript_ChooseHelixFossil::
	setvar VAR_TEMP_2, ITEM_HELIX_FOSSIL
	setvar VAR_TEMP_1, SPECIES_OMANYTE
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseDomeFossil::
	setvar VAR_TEMP_2, ITEM_DOME_FOSSIL
	setvar VAR_TEMP_1, SPECIES_KABUTO
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseOldAmber::
	setvar VAR_TEMP_2, ITEM_OLD_AMBER
	setvar VAR_TEMP_1, SPECIES_AERODACTYL
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseRootFossil::
	setvar VAR_TEMP_2, ITEM_ROOT_FOSSIL
	setvar VAR_TEMP_1, SPECIES_LILEEP
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseClawFossil::
	setvar VAR_TEMP_2, ITEM_CLAW_FOSSIL
	setvar VAR_TEMP_1, SPECIES_ANORITH
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseSkullFossil::
	setvar VAR_TEMP_2, ITEM_SKULL_FOSSIL
	setvar VAR_TEMP_1, SPECIES_CRANIDOS
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseArmorFossil::
	setvar VAR_TEMP_2, ITEM_ARMOR_FOSSIL
	setvar VAR_TEMP_1, SPECIES_SHIELDON
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseCoverFossil::
	setvar VAR_TEMP_2, ITEM_COVER_FOSSIL
	setvar VAR_TEMP_1, SPECIES_TIRTOUGA
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChoosePlumeFossil::
	setvar VAR_TEMP_2, ITEM_PLUME_FOSSIL
	setvar VAR_TEMP_1, SPECIES_ARCHEN
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseJawFossil::
	setvar VAR_TEMP_2, ITEM_JAW_FOSSIL
	setvar VAR_TEMP_1, SPECIES_TYRUNT
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseSailFossil::
	setvar VAR_TEMP_2, ITEM_SAIL_FOSSIL
	setvar VAR_TEMP_1, SPECIES_AMAURA
	goto RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ConfirmFossil::
	bufferitemname 0, VAR_TEMP_2
	msgbox RustboroCity_DevonCorp_2F_Text_ConfirmFossil, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_WhichFossilToRevive
	checkitem VAR_TEMP_2, 1
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_YouDontHaveThatFossil
	givemon VAR_TEMP_1, 30, ITEM_NONE
	compare VAR_RESULT, 0
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilMonParty
	compare VAR_RESULT, 1
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilMonPC
	goto Common_EventScript_NoMoreRoomForPokemon
	return

RustboroCity_DevonCorp_2F_EventScript_YouDontHaveThatFossil::
	msgbox RustboroCity_DevonCorp_2F_Text_YouDontHaveThatFossil, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReviveFossil::
	msgbox RustboroCity_DevonCorp_2F_Text_PleaseWaitWhileIRevive, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOSSIL_SCIENTIST, RustboroCity_DevonCorp_2F_Movement_TurnToDesk
	fadescreen FADE_TO_BLACK
	playse SE_USE_ITEM
	delay 28
	fadescreen FADE_FROM_BLACK
	faceplayer
	bufferspeciesname 1, VAR_TEMP_1
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	return

RustboroCity_DevonCorp_2F_Movement_TurnToDesk:
	walk_in_place_fastest_up
	step_end

RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilMonParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReviveFossil
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFossilMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFossilMon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFossilMon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilMonPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReviveFossil
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFossilMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_TransferFossilMonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferFossilMonToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferFossilMonToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFossilMon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedFossilMonFanfare::
	bufferspeciesname 1, VAR_TEMP_1
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname 0, VAR_TEMP_1
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFossilMon::
	removeitem VAR_TEMP_2, 1
	msgbox RustboroCity_DevonCorp_2F_Text_ComeBackAgain, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil:: @ 82119EF
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_MatchCallScientist:: @ 8211BCF
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	compare VAR_RUSTBORO_CITY_STATE, 6
	goto_if_ge RustboroCity_DevonCorp_2F_EventScript_WorkOnNext
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_WorkOnNext:: @ 8211BF1
	msgbox RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon: @ 8211BFB
	.string "We're developing a device for talking\n"
	.string "with Pokémon.\p"
	.string "But we haven't had much success…$"

RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls: @ 8211C50
	.string "I'm developing new kinds of\n"
	.string "Poké Balls…\p"
	.string "But I haven't made much headway…$"

RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls: @ 8211C99
	.string "We finally made new kinds of\n"
	.string "Poké Balls!\p"
	.string "The Repeat Ball makes it easier to\n"
	.string "catch Pokémon you've caught before.\p"
	.string "The Timer Ball gets better at catching\n"
	.string "Pokémon the longer a battle runs.\p"
	.string "Both are proudly developed by\n"
	.string "the Devon Corporation.\p"
	.string "Please give them a try!$"

RustboroCity_DevonCorp_2F_Text_IMadePokenav: @ 8211D9F
	.string "I made the PokéNav!\p"
	.string "As an engineer, I feel blessed to have\n"
	.string "made something so great!$"

RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav: @ 8211DF3
	.string "Oh, wow!\n"
	.string "That's a PokéNav!\p"
	.string "It came about as a result of our\n"
	.string "President's desire to learn about\l"
	.string "the feelings of Pokémon.\p"
	.string "Would you like me to describe its\n"
	.string "features in detail?\p"
	.string "No, no. I think you'll find out just by\n"
	.string "trying the PokéNav out.$"

RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams: @ 8211EE0
	.string "I'm trying to develop a device that\n"
	.string "visually reproduces the dreams of\l"
	.string "Pokémon…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils: @ 8211F48
	.string "I've been trying to develop a device\n"
	.string "that resurrects Pokémon from fossils…\p"
	.string "And, it's working!$"

RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife: @ 8211FA6
	.string "Wait! That thing you have there…\n"
	.string "Is that a Pokémon fossil?\p"
	.string "Would you like to bring that Pokémon\n"
	.string "back to life?\p"
	.string "I can with my newly developed\n"
	.string "Fossil Regenerator.$"

RustboroCity_DevonCorp_2F_Text_OhIsThatSo: @ 8212046
	.string "Oh, is that so?\p"
	.string "Devon's technological expertise\n"
	.string "is outstanding, I tell you.$"

RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne: @ 8212092
	.string "Oh, now that's a surprise!\n"
	.string "You have not one, but two, fossils?\p"
	.string "Unfortunately, my machine can only\n"
	.string "regenerate one Pokémon at a time.\p"
	.string "Would you like to pick one of your\n"
	.string "fossils for regeneration?$"

RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher: @ 8212153
	.string "Excellent!\n"
	.string "Let's do this right away.\p"
	.string "{PLAYER} handed the {STR_VAR_1} to\n"
	.string "the Devon Researcher.$"

RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime: @ 82121A2
	.string "The Fossil Regenerator, which I made,\n"
	.string "is incredible.\p"
	.string "But it has one drawback--it takes\n"
	.string "a long time to work.\p"
	.string "So, uh… How about you go for a stroll\n"
	.string "and look around for a while?$"

RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife: @ 8212251
	.string "Thanks for waiting!\p"
	.string "Your fossilized Pokémon has been\n"
	.string "brought back to life!\p"
	.string "The fossil was an ancient Pokémon.\n"
	.string "{STR_VAR_2}, it was!$"

RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher: @ 82122CB
	.string "{PLAYER} received {STR_VAR_2} from\n"
	.string "the Devon Researcher.$"

RustboroCity_DevonCorp_2F_Text_TooManyPokemon: @ 82122F5
	.string "Uh-oh, you've got too many Pokémon.\n"
	.string "You have no room for this one.$"

RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature: @ 8212338
	.string "I'm trying to develop a new feature\n"
	.string "for the PokéNav…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext: @ 8212386
	.string "Well, now what shall I work on\n"
	.string "developing next?\p"
	.string "Our company allows us to make our\n"
	.string "inspirations into reality.\p"
	.string "One couldn't ask for a better\n"
	.string "environment as an engineer.$"

RustboroCity_DevonCorp_2F_Text_WhichFossilToRevive:
	.string "Which fossil have you brought me?$"

RustboroCity_DevonCorp_2F_Text_ConfirmFossil:
	.string "You wish to regenerate a Pokémon from\n"
	.string "the {STR_VAR_1}?$"

RustboroCity_DevonCorp_2F_Text_YouDontHaveThatFossil:
	.string "Hmm…\n"
	.string "You dont see to have a {STR_VAR_1}.$"

RustboroCity_DevonCorp_2F_Text_PleaseWaitWhileIRevive:
	.string "Great! Please wait just a moment…$"

RustboroCity_DevonCorp_2F_Text_ComeBackAgain:
	.string "If you find any more fossils, bring\n"
	.string "them to me!$"

RustboroCity_DevonCorp_2F_Text_ThatsNotAFossil:
	.string "Sorry…\n"
	.string "That doesn't seem to be a fossil.\p"
	.string "If you do find a fossil, please\n"
	.string "bring it to me!$"
