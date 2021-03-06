SlateportCity_ContestHall_MapScripts::
	.byte 0

SlateportCity_ContestHall_EventScript_Rich_Boy::
	lockall
	faceplayer
	msgbox SlateportCity_ContestHall_Text_MyMonRules, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_ContestHall_EventScript_LittleGirl::
	lockall
	faceplayer
	msgbox SlateportCity_ContestHall_Text_RaisedMonToBeCute, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_ContestHall_EventScript_Boy::
	lockall
	faceplayer
	msgbox SlateportCity_ContestHall_Text_WhichContestYouEntering, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_ContestHall_EventScript_NormalRankStageSign::
	msgbox SlateportCity_ContestHall_Text_NormalRankStage, MSGBOX_SIGN
	end

SlateportCity_ContestHall_Text_WhichContestYouEntering:
	.string "Which Contest are you entering?\n"
	.string "Want a piece of advice?\p"
	.string "In any Contest, for example, a Cute\n"
	.string "Contest, I don't think they judge you\l"
	.string "only on cuteness in the first round.\p"
	.string "You need to work out ways for raising\n"
	.string "Pokémon better.$"

SlateportCity_ContestHall_Text_RaisedMonToBeCute:
	.string "I raised my Pokémon to be cute.\p"
	.string "I found out you can put Pokémon in\n"
	.string "a Contest for cuteness!\p"
	.string "I'm so glad I raised my Pokémon with\n"
	.string "loving care…$"

SlateportCity_ContestHall_Text_MyMonRules:
	.string "My Pokémon rules!\p"
	.string "It's cool, tough yet beautiful, cute,\n"
	.string "and smart. It's complete!\p"
	.string "I may as well go for wins in every\n"
	.string "single Contest.$"

SlateportCity_ContestHall_Text_NormalRankStage:
	.string "Pokémon Contests\n"
	.string "Normal Rank Stage!$"
