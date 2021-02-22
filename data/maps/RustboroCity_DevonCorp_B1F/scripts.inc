RustboroCity_DevonCorp_B1F_MapScripts::
	.byte 0

RustboroCity_DevonCorp_B1F_EventScript_Employee::
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_B1F_Text_TakeWhatYouWant, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_B1F_Text_TakeWhatYouWant:
	.string "Thanks for helping us out!\p"
	.string "It's mostly junk down here, so\n"
	.string "feel free to take anything that\l"
	.string "catches you eye.\p"
	.string "Just be careful around the machinery,\n"
	.string "please.$"
