.set LOCALID_APRICORN_WORKER, 1

OldaleTown_ApricornWorkshop_MapScripts::
	.byte 0

OldaleTown_ApricornWorkshop_EventScript_ApricornWorker::
	lock
	faceplayer
	goto_if_unset FLAG_MET_OLDALE_TOWN_APRICORN_WORKER, OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerIntroduction
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerDoYouHaveAnApricorn, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	call OldaleTown_ApricornWorkshop_EventScript_CraftMenu
	release
	end

OldaleTown_ApricornWorkshop_EventScript_CraftMenu::
	message OldaleTown_ApricornWorkshop_Text_CraftWhichBall
	waitmessage
	setvar VAR_0x8009, 0
	setvar VAR_0x8004, SCROLL_MULTI_APRICORN_WORKSHOP_VENDOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, OldaleTown_ApricornWorkshop_EventScript_CraftRedApricorns
	case 1, OldaleTown_ApricornWorkshop_EventScript_CraftBlueApricorns
	case 2, OldaleTown_ApricornWorkshop_EventScript_CraftYellowApricorns
	case 3, OldaleTown_ApricornWorkshop_EventScript_CraftGreenApricorns
	case 4, OldaleTown_ApricornWorkshop_EventScript_CraftPinkApricorns
	case 5, OldaleTown_ApricornWorkshop_EventScript_CraftWhiteApricorns
	case 6, OldaleTown_ApricornWorkshop_EventScript_CraftBlackApricorns
	case 7, OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	case MULTI_B_PRESSED, OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	release
	end

OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerIntroduction::
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerIntroduction, MSGBOX_DEFAULT
	giveitem ITEM_RAZZ_BERRY
	compare VAR_RESULT, FALSE
	call_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBerries @ Probably won't ever get called during regular gameplay
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerComeBackAgain, MSGBOX_DEFAULT
	setflag FLAG_MET_OLDALE_TOWN_APRICORN_WORKER
	release
	end

OldaleTown_ApricornWorkshop_EventScript_NoRoomForBerries::
	msgbox OldaleTown_ApricornWorkshop_Text_NoRoomForBerries, MSGBOX_DEFAULT
	release
	end

OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain::
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerComeBackAgain, MSGBOX_DEFAULT
	release
	end

OldaleTown_ApricornWorkshop_EventScript_CraftRedApricorns::
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmLevelBall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_CraftMenu
	checkitem ITEM_RED_APRICORN, 1
	compare VAR_RESULT, FALSE
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoApricorns
	checkitemspace ITEM_LEVEL_BALL, 1
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	call OldaleTown_ApricornWorkshop_EventScript_FadeToBlack
	giveitem ITEM_LEVEL_BALL
	removeitem ITEM_RED_APRICORN, 1
	call OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	return

OldaleTown_ApricornWorkshop_EventScript_CraftBlueApricorns::
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmLureBall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_CraftMenu
	checkitem ITEM_BLUE_APRICORN, 1
	compare VAR_RESULT, FALSE
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoApricorns
	checkitemspace ITEM_LURE_BALL, 1
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	call OldaleTown_ApricornWorkshop_EventScript_FadeToBlack
	giveitem ITEM_LURE_BALL
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	removeitem ITEM_BLUE_APRICORN, 1
	call OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	return

OldaleTown_ApricornWorkshop_EventScript_CraftPinkApricorns::
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmLoveBall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_CraftMenu
	checkitem ITEM_PINK_APRICORN, 1
	compare VAR_RESULT, FALSE
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoApricorns
	checkitemspace ITEM_LOVE_BALL, 1
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	call OldaleTown_ApricornWorkshop_EventScript_FadeToBlack
	giveitem ITEM_LOVE_BALL
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	removeitem ITEM_PINK_APRICORN, 1
	call OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	return

OldaleTown_ApricornWorkshop_EventScript_CraftGreenApricorns::
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmFriendBall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_CraftMenu
	checkitem ITEM_GREEN_APRICORN, 1
	compare VAR_RESULT, FALSE
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoApricorns
	checkitemspace ITEM_FRIEND_BALL, 1
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	call OldaleTown_ApricornWorkshop_EventScript_FadeToBlack
	giveitem ITEM_FRIEND_BALL
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	removeitem ITEM_GREEN_APRICORN, 1
	call OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	return

OldaleTown_ApricornWorkshop_EventScript_CraftYellowApricorns::
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmMoonBall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_CraftMenu
	checkitem ITEM_YELLOW_APRICORN, 1
	compare VAR_RESULT, FALSE
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoApricorns
	checkitemspace ITEM_MOON_BALL, 1
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	call OldaleTown_ApricornWorkshop_EventScript_FadeToBlack
	giveitem ITEM_MOON_BALL
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	removeitem ITEM_YELLOW_APRICORN, 1
	call OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	return

OldaleTown_ApricornWorkshop_EventScript_CraftBlackApricorns::
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmHeavyBall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_CraftMenu
	checkitem ITEM_BLACK_APRICORN, 1
	compare VAR_RESULT, FALSE
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoApricorns
	checkitemspace ITEM_HEAVY_BALL, 1
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	call OldaleTown_ApricornWorkshop_EventScript_FadeToBlack
	giveitem ITEM_HEAVY_BALL
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	removeitem ITEM_BLACK_APRICORN, 1
	call OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	return

OldaleTown_ApricornWorkshop_EventScript_CraftWhiteApricorns::
	msgbox OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmFastBall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_CraftMenu
	checkitem ITEM_WHITE_APRICORN, 1
	compare VAR_RESULT, FALSE
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoApricorns
	checkitemspace ITEM_FAST_BALL, 1
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	call OldaleTown_ApricornWorkshop_EventScript_FadeToBlack
	giveitem ITEM_FAST_BALL
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls
	removeitem ITEM_WHITE_APRICORN, 1
	call OldaleTown_ApricornWorkshop_EventScript_ApricornWorkerComeBackAgain
	return

OldaleTown_ApricornWorkshop_EventScript_NoApricorns::
	msgbox OldaleTown_ApricornWorkshop_Text_YouHaveNoApricorns, MSGBOX_DEFAULT
	release
	end

OldaleTown_ApricornWorkshop_EventScript_NoRoomForBalls::
	msgbox OldaleTown_ApricornWorkshop_Text_NoRoomForBalls, MSGBOX_DEFAULT
	release
	end

OldaleTown_ApricornWorkshop_EventScript_FadeToBlack::
	msgbox OldaleTown_ApricornWorkshop_Text_WaitWhileCrafting, MSGBOX_DEFAULT
	applymovement LOCALID_APRICORN_WORKER, OldaleTown_ApricornWorkshop_Movement_ApricornWorkerTurnToDesk
	fadescreen FADE_TO_BLACK
	playse SE_BRIDGE_WALK
	delay 28
	playse SE_BRIDGE_WALK
	delay 28
	playse SE_BRIDGE_WALK
	delay 28
	fadescreen FADE_FROM_BLACK
	faceplayer
	msgbox OldaleTown_ApricornWorkshop_Text_HereYouAre, MSGBOX_DEFAULT
	return

OldaleTown_ApricornWorkshop_EventScript_Sign::
	lockall
	msgbox OldaleTown_ApricornWorkshop_Text_SignListApricornBalls, MSGBOX_DEFAULT
	goto OldaleTown_ApricornWorkshop_EventScript_ChooseApricornBallTopic
	end

OldaleTown_ApricornWorkshop_EventScript_ChooseApricornBallTopic::
	message OldaleTown_ApricornWorkshop_Text_ReadWhichTopic
	waitmessage
	setvar VAR_0x8009, 0
	setvar VAR_0x8004, SCROLL_MULTI_APRICORN_WORKSHOP_VENDOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, OldaleTown_ApricornWorkshop_EventScript_LevelBall
	case 1, OldaleTown_ApricornWorkshop_EventScript_LureBall
	case 2, OldaleTown_ApricornWorkshop_EventScript_MoonBall
	case 3, OldaleTown_ApricornWorkshop_EventScript_FriendBall
	case 4, OldaleTown_ApricornWorkshop_EventScript_LoveBall
	case 5, OldaleTown_ApricornWorkshop_EventScript_FastBall
	case 6, OldaleTown_ApricornWorkshop_EventScript_HeavyBall
	case 7, OldaleTown_ApricornWorkshop_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, OldaleTown_ApricornWorkshop_EventScript_ExitTopicSelect
	end

OldaleTown_ApricornWorkshop_EventScript_LevelBall::
	msgbox OldaleTown_ApricornWorkshop_Text_ExplainLevelBall, MSGBOX_DEFAULT
	goto OldaleTown_ApricornWorkshop_EventScript_ChooseApricornBallTopic
	end

OldaleTown_ApricornWorkshop_EventScript_LureBall::
	msgbox OldaleTown_ApricornWorkshop_Text_ExplainLureBall, MSGBOX_DEFAULT
	goto OldaleTown_ApricornWorkshop_EventScript_ChooseApricornBallTopic
	end

OldaleTown_ApricornWorkshop_EventScript_LoveBall::
	msgbox OldaleTown_ApricornWorkshop_Text_ExplainLoveBall, MSGBOX_DEFAULT
	goto OldaleTown_ApricornWorkshop_EventScript_ChooseApricornBallTopic
	end

OldaleTown_ApricornWorkshop_EventScript_FriendBall::
	msgbox OldaleTown_ApricornWorkshop_Text_ExplainFriendBall, MSGBOX_DEFAULT
	goto OldaleTown_ApricornWorkshop_EventScript_ChooseApricornBallTopic
	end

OldaleTown_ApricornWorkshop_EventScript_MoonBall::
	msgbox OldaleTown_ApricornWorkshop_Text_ExplainMoonBall, MSGBOX_DEFAULT
	goto OldaleTown_ApricornWorkshop_EventScript_ChooseApricornBallTopic
	end

OldaleTown_ApricornWorkshop_EventScript_HeavyBall::
	msgbox OldaleTown_ApricornWorkshop_Text_ExplainHeavyBall, MSGBOX_DEFAULT
	goto OldaleTown_ApricornWorkshop_EventScript_ChooseApricornBallTopic
	end

OldaleTown_ApricornWorkshop_EventScript_FastBall::
	msgbox OldaleTown_ApricornWorkshop_Text_ExplainFastBall, MSGBOX_DEFAULT
	goto OldaleTown_ApricornWorkshop_EventScript_ChooseApricornBallTopic
	end

OldaleTown_ApricornWorkshop_EventScript_ExitTopicSelect:: @ 8213F5D
	releaseall
	end

OldaleTown_ApricornWorkshop_Movement_ApricornWorkerTurnToDesk:
	walk_in_place_fastest_right
	step_end

OldaleTown_ApricornWorkshop_Text_ApricornWorkerIntroduction:
	@.string "Hm? Well look who it is! I thought I\n"
	@.string "recognized that face I saw running\l"
	@.string "back and forth through town.\p"
	.string "Hm? Well look who it is!\p"
	.string "You're Norman's kid, {PLAYER}! My,\n"
	.string "you've grown a lot since I last saw\l"
	.string "you back when I still lived in Johto.\p"
	.string "You probably don't remember me, but I\n"
	.string "was a friend of your father's. I moved\l"
	.string "to Hoenn a few years ago to start up\l"
	.string "my own Apricorn Workshop.\p"
	.string "I take Apricorns and use them to craft\n"
	.string "special Poké Balls that even Devon\l"
	.string "Corp. would be jealous of!\p"
	.string "But where might one aquire Apricorns?\n"
	.string "Well, in Hoenn, Apricorns grow off of\l"
	.string "certain Berry trees. If you plant more\l"
	.string "of that Berry, you'll grow more of that\l"
	.string "same type of Apricorn.\p"
	.string "Here, take this and try for yourself.$"

OldaleTown_ApricornWorkshop_Text_NoRoomForBerries:
	.string "Hm? Your Bag's Berries Pocket is full.$"

OldaleTown_ApricornWorkshop_Text_NoRoomForBalls:
	.string "Hm? Your Bag's Poké Balls Pocket is full.$"

OldaleTown_ApricornWorkshop_Text_CraftWhichBall: @ 82140F9
	.string "Which Poké Ball would you like me to\n"
	.string "craft for you?$"

OldaleTown_ApricornWorkshop_Text_WaitWhileCrafting:
	.string "Sure, I'll take that Apricorn, then.\n"
	.string "Just give me a moment.$"

OldaleTown_ApricornWorkshop_Text_HereYouAre:
	.string "All done! Here you go!$"

OldaleTown_ApricornWorkshop_Text_YouHaveNoApricorns:
	.string "Hm? You don't seem to have the correct\n"
	.string "Apricorn for that Ball.$"

OldaleTown_ApricornWorkshop_Text_ApricornWorkerDoYouHaveAnApricorn:
	.string "Good to see you again, {PLAYER}.\n"
	.string "Want me to craft some Poké Balls?$"

OldaleTown_ApricornWorkshop_Text_ApricornWorkerComeBackAgain:
	.string "Come back when you have some Apricorns\n"
	.string "and I'll craft some special Poké Balls!$"

OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmLevelBall:
	.string "You want me to craft a Level Ball?\n"
	.string "That'll require a Red Apricorn, okay?$"

OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmLureBall:
	.string "You want me to craft a Lure Ball?\n"
	.string "That'll require a Blu Apricorn, okay?$"

OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmLoveBall:
	.string "You want me to craft a Love Ball?\n"
	.string "That'll require a Pik Apricorn, okay?$"

OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmFriendBall:
	.string "You want me to craft a Friend Ball?\n"
	.string "That'll require a Grn Apricorn, okay?$"

OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmMoonBall:
	.string "You want me to craft a Moon Ball?\n"
	.string "That'll require a Ylw Apricorn, okay?$"

OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmHeavyBall:
	.string "You want me to craft a Heavy Ball?\n"
	.string "That'll require a Blk Apricorn, okay?$"

OldaleTown_ApricornWorkshop_Text_ApricornWorkerConfirmFastBall:
	.string "You want me to craft a Fast Ball?\n"
	.string "That'll require a Wht Apricorn, okay?$"

OldaleTown_ApricornWorkshop_Text_SignListApricornBalls: @ 82140B2
	.string "The sign lists the various Poké Balls\n"
	.string "that can be crafted.$"

OldaleTown_ApricornWorkshop_Text_ReadWhichTopic: @ 82140F9
	.string "Which Poké Ball do you want to read\n"
	.string "about?$"

OldaleTown_ApricornWorkshop_Text_ExplainLevelBall:
	.string "Red Apricorn {RIGHT_ARROW} Level Ball\p"
	.string "Better chance to catch when your\n"
	.string "Pokémon is a higher level than the\l"
	.string "wild Pokémon:\p"
	.string "x2 if higher but not double in level.\n"
	.string "x4 if double but not quadruple in level.\l"
	.string "x8 if quadruple in level.$"

OldaleTown_ApricornWorkshop_Text_ExplainLureBall:
	.string "Blu Apricorn {RIGHT_ARROW} Lure Ball\p"
	.string "x3 chance for catching Pokémon reeled\n"
	.string "in with a fishing rod.$"

OldaleTown_ApricornWorkshop_Text_ExplainLoveBall:
	.string "Pnk Apricorn {RIGHT_ARROW} Love Ball\p"
	.string "x8 chance for catching if the wild\n"
	.string "Pokémon is the same species as your\l"
	.string "active Pokémon, but is the opposite\l"
	.string "gender.$"

OldaleTown_ApricornWorkshop_Text_ExplainFriendBall:
	.string "Grn Apricorn {RIGHT_ARROW} Friend Ball\p"
	.string "Makes the caught Pokémon instantly\n"
	.string "very friendly. (200 Friendship)$"

OldaleTown_ApricornWorkshop_Text_ExplainMoonBall:
	.string "Ylw Apricorn {RIGHT_ARROW} Moon Ball\p"
	.string "x4 chance to catch Pokémon that can\n"
	.string "evolve by using a Moon Stone.$"

OldaleTown_ApricornWorkshop_Text_ExplainHeavyBall:
	.string "Blk Apricorn {RIGHT_ARROW} Heavy Ball\p"
	.string "Good for catching heavier Pokémon:\p"
	.string "x0.5 if less than 225.8 lbs.\n" @ or 102.4 kg
	.string "x2 if weighs less than 677.3 lbs.\l" @ or 307.2 kg
	.string "x3 if weighs less than 903.0 lbs.\l" @ or 409.6 kg
	.string "x4 if weighs greater than 903.0 lbs.$" @ or 409.6 kg

OldaleTown_ApricornWorkshop_Text_ExplainFastBall:
	.string "Wht Apricorn {RIGHT_ARROW} Fast Ball\p"
	.string "x4 chance for catching Pokémon with a\n"
	.string "base Speed greater than 100.$"
