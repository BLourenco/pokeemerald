SootopolisCity_House3_MapScripts:: @ 8226B71
	.byte 0

SootopolisCity_House3_EventScript_Woman:: @ 8226B72
	lock
	faceplayer
	call_if_unset FLAG_SYS_GAME_CLEAR, SootopolisCity_House3_EventScript_WallaceHasManyFansDoYou
	call_if_set FLAG_SYS_GAME_CLEAR, SootopolisCity_House3_EventScript_JuanHasManyFansDoYou
	end

SootopolisCity_House3_EventScript_WallaceHasManyFansDoYou::
	msgbox SootopolisCity_House3_Text_WallaceHasManyFansDoYou, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SootopolisCity_House3_EventScript_HaveFans
	goto SootopolisCity_House3_EventScript_ThatsLonesome
	end

SootopolisCity_House3_EventScript_JuanHasManyFansDoYou::
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SootopolisCity_House3_EventScript_HaveFans
	goto SootopolisCity_House3_EventScript_ThatsLonesome
	end

SootopolisCity_House3_EventScript_ThatsLonesome::	
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans:: @ 8226B91
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl:: @ 8226B9B
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_WallaceHasManyFansDoYou:
	.string "You're a Pokémon Trainer, aren't you?\p"
	.string "Sootopolis's Wallace has many fans.\n"
	.string "Do you have any?$"

SootopolisCity_House3_Text_JuanHasManyFansDoYou: @ 8226BA4
	.string "You're a Pokémon Trainer, aren't you?\p"
	.string "Sootopolis's Juan has many fans.\n"
	.string "Even more than his student Wallace!\p"
	.string "Do you have any?$"

SootopolisCity_House3_Text_YouMustBePrettyStrong: @ 8226C20
	.string "Oh, then you must be pretty strong.$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder: @ 8226C44
	.string "Oh, dear…\n"
	.string "That's a little lonesome.\p"
	.string "Try working a little harder to get\n"
	.string "a fan following.$"

SootopolisCity_House3_Text_TrainerFanClubWasWild: @ 8226C9C
	.string "Dedicated fans come over from even\n"
	.string "outside of Hoenn.\p"
	.string "It was really wild when I went to the\n"
	.string "Trainer Fan Club in Lilycove.$"

