LavaridgeTown_ContestHall_MapScripts::
	.byte 0

LavaridgeTown_ContestHall_EventScript_NinjaBoy::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_MyPapaIsContestJudge, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_FatMan1::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_AdviceForContests, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_Boy1::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_BattleAndContestAlike, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_Maniac::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_MyMonBetterThanThatLot, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_Hiker::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_GetUrgeToMoveWithMon, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_Boy2::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_MonLooksOnTopOfGame, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_Girl::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_ItsAppealTime, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_Man::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_DidntPayAttentionToAppeal, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_Boy3::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_RewardWithSageAdvice, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_FatMan2::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_MoreFreakedOutThanMon, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_Woman::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_MCStepUpTakePartInContest, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_ContestJudge::
	lockall
	faceplayer
	msgbox LavaridgeTown_ContestHall_Text_JudgeWouldntDoToMissContest, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_ContestHall_EventScript_HyperRankStageSign::
	msgbox LavaridgeTown_ContestHall_Text_HyperRankStage, MSGBOX_SIGN
	end

LavaridgeTown_ContestHall_Text_AdviceForContests: @ 820906B
	.string "Want a tasty little bit of advice\n"
	.string "for Contests?\p"
	.string "Using a certain move after another\n"
	.string "certain kind of move sometimes gets\l"
	.string "you extra attention.\p"
	.string "If you know what you're doing,\n"
	.string "you can score big in appeal.\p"
	.string "Of course, your opponents might try\n"
	.string "disrupting your Pokémon's showing.$"

LavaridgeTown_ContestHall_Text_MyPapaIsContestJudge: @ 820917A
	.string "My papa, he's a Contest Judge.\p"
	.string "I wonder what I should be when I\n"
	.string "grow up, a Judge or a Gym Leader?$"

LavaridgeTown_ContestHall_Text_ImLikeMajorlyCheesed: @ 82091DC
	.string "Hey, man, I'm like majorly cheesed,\n"
	.string "you know. Like, you know, I just\l"
	.string "wanted to know why my Pokémon\l"
	.string "never won, you know, like, hey?\p"
	.string "So, like, I gave the Judge my two\n"
	.string "cents, you know, they're free.\p"
	.string "And he wouldn't hear me out, like, hey!\n"
	.string "So, like, total bummer, man!\p"
	.string "Hey, like, you! Zip it, you know?\n"
	.string "Just, you know, take this!$"

LavaridgeTown_ContestHall_Text_ExplainTorment: @ 8209322
	.string "That's, like, TM41, you know?\n"
	.string "Hey, it's Torment, you hearing me?\p"
	.string "Like, it won't let the other guy\n"
	.string "use the same move twice in a row, see?\p"
	.string "Hey, now, you listen here, like,\n"
	.string "I'm not laying a torment on you!$"

LavaridgeTown_ContestHall_Text_MCStepUpTakePartInContest: @ 82093ED
	.string "MC: Oh, my, my!\n"
	.string "Now isn't that a dandy of a Pokémon?\p"
	.string "Please! Do step right up and take\n"
	.string "part in our splendid Contests!\p"
	.string "You'll do well! I'm sure of it!\n"
	.string "My eyes have never failed me!$"

LavaridgeTown_ContestHall_Text_JudgeWouldntDoToMissContest: @ 82094A1
	.string "Judge: Well, hello there!\n"
	.string "I see that you're a Trainer!\p"
	.string "Then, it just wouldn't do for you\n"
	.string "to miss a Pokémon Contest!\p"
	.string "Speak with the Receptionist in\n"
	.string "the lobby and enter anytime!$"

LavaridgeTown_ContestHall_Text_ItsAppealTime: @ 820954E
	.string "It's appeal time!\n"
	.string "What should I lead with?$"

LavaridgeTown_ContestHall_Text_DidntPayAttentionToAppeal: @ 8209579
	.string "They didn't pay much attention to\n"
	.string "my Pokémon's appeal…\p"
	.string "Humph, that Judge, he doesn't know\n"
	.string "a good thing when he sees it.$"

LavaridgeTown_ContestHall_Text_RewardWithSageAdvice: @ 82095F1
	.string "Oh, hi! You must be a serious fan to get\n"
	.string "this close to the action.\p"
	.string "I'll reward your enthusiasm with\n"
	.string "this sage advice.\p"
	.string "If a move goes over really well,\n"
	.string "the audience will get excited.\p"
	.string "The Pokémon that makes its appeal\n"
	.string "right when everyone's excited…\p"
	.string "Well, you'd think something good has\n"
	.string "to happen!$"

LavaridgeTown_ContestHall_Text_MoreFreakedOutThanMon: @ 8209718
	.string "I can't do this! I'm more freaked out\n"
	.string "than my Pokémon.\p"
	.string "I'm shivering and my heart is racing!$"

LavaridgeTown_ContestHall_Text_BattleAndContestAlike: @ 8209775
	.string "A battle and a Contest aren't the\n"
	.string "same, but they are alike, too.\p"
	.string "You need to work hard and believe\n"
	.string "in the Pokémon you've raised.$"

LavaridgeTown_ContestHall_Text_MonLooksOnTopOfGame: @ 82097F6
	.string "That Pokémon looks like it's on top\n"
	.string "of its game, huh?\p"
	.string "A Pokémon that does good in the\n"
	.string "secondary judging seems to be more\l"
	.string "relaxed when it's doing appeals.$"

LavaridgeTown_ContestHall_Text_MyMonBetterThanThatLot: @ 8209890
	.string "Will you look at that sorry sight?\p"
	.string "Heh, my Pokémon's absolutely better\n"
	.string "than that lot!$"

LavaridgeTown_ContestHall_Text_GetUrgeToMoveWithMon: @ 82098E6
	.string "Don't you get the urge to move with\n"
	.string "Pokémon if they're putting on an\l"
	.string "energetic appeal?$"

LavaridgeTown_ContestHall_Text_HyperRankStage: @ 820993D
	.string "Pokémon Contests\n"
	.string "Hyper Rank Stage!$"
