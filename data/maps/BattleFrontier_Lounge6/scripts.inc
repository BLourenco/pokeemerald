BattleFrontier_Lounge6_MapScripts:: @ 8264FEC
	.byte 0

BattleFrontier_Lounge6_EventScript_Beauty:: @ 8264FED
	lock
	faceplayer
	msgbox BattleFrontier_Lounge6_Text_ILoveSkitty, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_Skitty1:: @ 8267931
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, 0
	msgbox BattleFrontier_Lounge6_Text_Skitty1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_Lounge6_EventScript_Skitty2:: @ 8267931
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, 0
	msgbox BattleFrontier_Lounge6_Text_Skitty2, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_Lounge6_EventScript_Skitty3:: @ 8267931
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, 0
	msgbox BattleFrontier_Lounge6_Text_Skitty3, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_Lounge6_EventScript_Skitty4:: @ 8267931
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, 0
	msgbox BattleFrontier_Lounge6_Text_Skitty4, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_Lounge6_EventScript_Skitty5:: @ 8267931
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, 0
	msgbox BattleFrontier_Lounge6_Text_Skitty5, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_Lounge6_EventScript_Skitty6:: @ 8267931
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, 0
	msgbox BattleFrontier_Lounge6_Text_Skitty6, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_Lounge6_Text_ILoveSkitty: @ 826508D
	.string "I love Skitty!\n"
	.string "They're so cute!\p"
	.string "I've colected all these through\n"
	.string "trading with others.\p"
	.string "Oh, sorry! I'm not looking to trade\n"
	.string "for more Skitty.\p"
	.string "I'm all out of Pokemon to trade!$"

BattleFrontier_Lounge6_Text_Skitty1:
	.string "Skitty: Fffnyaaaah…$"

BattleFrontier_Lounge6_Text_Skitty2:
	.string "Skitty: Gyaaaah!$"

BattleFrontier_Lounge6_Text_Skitty3:
	.string "Skitty: Miyaan?$"

BattleFrontier_Lounge6_Text_Skitty4:
	.string "Skitty: Miyao?$"

BattleFrontier_Lounge6_Text_Skitty5:
	.string "Skitty: Mya myaaah!$"

BattleFrontier_Lounge6_Text_Skitty6:
	.string "Skitty: Miyaoo…$"
