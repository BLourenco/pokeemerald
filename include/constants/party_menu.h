#ifndef GUARD_CONSTANTS_PARTY_MENU_H
#define GUARD_CONSTANTS_PARTY_MENU_H

#define AILMENT_NONE  0
#define AILMENT_PSN   1
#define AILMENT_PRZ   2
#define AILMENT_SLP   3
#define AILMENT_FRZ   4
#define AILMENT_BRN   5
#define AILMENT_PKRS  6
#define AILMENT_FNT   7

//
// TUTOR MOVES
//

#define MOVE_TUTOR_FREE         0   // Man NPC
#define MOVE_TUTOR_SPECIAL      1   // Female Elder NPC
#define MOVE_TUTOR_OFFENSE_1    2   // Black Belt NPC
#define MOVE_TUTOR_OFFENSE_2    3   // Black Belt NPC
#define MOVE_TUTOR_STATUS       4   // Maniac NPC
#define MOVE_TUTOR_SUPPORT      5   // Woman NPC
#define MOVE_TUTOR_SWSH_IOA     6   // ???

#define MOVE_TUTOR_COUNT        7

// Emerald Frontier Tutor Moves (that haven't become TMs in Gen. 7)
#define TUTOR_MOVE_DEFENSE_CURL	    0
#define TUTOR_MOVE_SOFT_BOILED	    1
#define TUTOR_MOVE_MUD_SLAP	        2
#define TUTOR_MOVE_SWIFT	        3
#define TUTOR_MOVE_SEISMIC_TOSS	    4
#define TUTOR_MOVE_MEGA_PUNCH	    5
#define TUTOR_MOVE_MEGA_KICK	    6
#define TUTOR_MOVE_ENDURE	        7
#define TUTOR_MOVE_PSYCH_UP	        8
#define TUTOR_MOVE_BODY_SLAM	    9
#define TUTOR_MOVE_COUNTER	        10
#define TUTOR_MOVE_DYNAMIC_PUNCH	11
#define TUTOR_MOVE_DOUBLE_EDGE	    12
#define TUTOR_MOVE_ROLLOUT	        13
#define TUTOR_MOVE_FURY_CUTTER	    14
#define TUTOR_MOVE_METRONOME	    15
#define TUTOR_MOVE_MIMIC	        16

// Special Tutor Moves
#define TUTOR_MOVE_GRASS_PLEDGE	    17
#define TUTOR_MOVE_FIRE_PLEDGE	    18
#define TUTOR_MOVE_WATER_PLEDGE	    19
#define TUTOR_MOVE_FRENZY_PLANT	    20
#define TUTOR_MOVE_BLAST_BURN	    21
#define TUTOR_MOVE_HYDRO_CANNON	    22
#define TUTOR_MOVE_DRACO_METEOR	    23
#define TUTOR_MOVE_RELIC_SONG	    24
#define TUTOR_MOVE_SECRET_SWORD	    25
#define TUTOR_MOVE_DRAGON_ASCENT	26

// Offensive 1/2 Tutor Moves
#define TUTOR_MOVE_UPROAR	        27
#define TUTOR_MOVE_SNORE	        28
#define TUTOR_MOVE_BOUNCE	        29
#define TUTOR_MOVE_LOW_KICK	        30
#define TUTOR_MOVE_THUNDER_PUNCH	31
#define TUTOR_MOVE_FIRE_PUNCH	    32
#define TUTOR_MOVE_ICE_PUNCH	    33
#define TUTOR_MOVE_DRAIN_PUNCH	    34
#define TUTOR_MOVE_HEAT_WAVE	    35
#define TUTOR_MOVE_EARTH_POWER	    36
#define TUTOR_MOVE_KNOCK_OFF	    37
#define TUTOR_MOVE_SUPER_FANG	    38
#define TUTOR_MOVE_DUAL_CHOP	    39
#define TUTOR_MOVE_THROAT_CHOP	    40
#define TUTOR_MOVE_SKY_DROP	        41
#define TUTOR_MOVE_ENDEAVOR	        42
#define TUTOR_MOVE_LIQUIDATION	    43
#define TUTOR_MOVE_SLUDGE_WAVE	    44

// Offensive 2/2 Tutor Moves
#define TUTOR_MOVE_BUG_BITE	        45
#define TUTOR_MOVE_FLING	        46
#define TUTOR_MOVE_DRILL_RUN	    47
#define TUTOR_MOVE_IRON_HEAD	    48
#define TUTOR_MOVE_ZEN_HEADBUTT	    49
#define TUTOR_MOVE_SIGNAL_BEAM	    50
#define TUTOR_MOVE_BRUTAL_SWING	    51
#define TUTOR_MOVE_HYPER_VOICE	    52
#define TUTOR_MOVE_AQUA_TAIL	    53
#define TUTOR_MOVE_DRAGON_PULSE	    54
#define TUTOR_MOVE_SEED_BOMB	    55
#define TUTOR_MOVE_LAST_RESORT	    56
#define TUTOR_MOVE_FOUL_PLAY	    57
#define TUTOR_MOVE_STOMPING_TANTRUM	58
#define TUTOR_MOVE_OUTRAGE	        59
#define TUTOR_MOVE_SUPERPOWER	    60
#define TUTOR_MOVE_GUNK_SHOT	    61
#define TUTOR_MOVE_SKY_ATTACK	    62

// Status Tutor Moves
#define TUTOR_MOVE_BIND	            63
#define TUTOR_MOVE_INFESTATION	    64
#define TUTOR_MOVE_COVET	        65
#define TUTOR_MOVE_BLOCK	        66
#define TUTOR_MOVE_QUASH	        67
#define TUTOR_MOVE_ROLE_PLAY	    68
#define TUTOR_MOVE_PAIN_SPLIT	    69
#define TUTOR_MOVE_GASTRO_ACID	    70
#define TUTOR_MOVE_WORRY_SEED	    71
#define TUTOR_MOVE_SPITE	        72
#define TUTOR_MOVE_TRICK	        73
#define TUTOR_MOVE_EMBARGO	        74
#define TUTOR_MOVE_MAGIC_COAT	    75
#define TUTOR_MOVE_TELEKINESIS	    76
#define TUTOR_MOVE_ELECTROWEB	    77
#define TUTOR_MOVE_ICY_WIND	        78

// Support Tutor Moves
#define TUTOR_MOVE_HONE_CLAWS	    79
#define TUTOR_MOVE_IRON_DEFENSE	    80
#define TUTOR_MOVE_LASER_FOCUS	    81
#define TUTOR_MOVE_HEAL_BELL	    82
#define TUTOR_MOVE_MAGIC_ROOM	    83
#define TUTOR_MOVE_WONDER_ROOM	    84
#define TUTOR_MOVE_GRAVITY	        85
#define TUTOR_MOVE_MAGNET_RISE	    86
#define TUTOR_MOVE_RECYCLE	        87
#define TUTOR_MOVE_AFTER_YOU	    88
#define TUTOR_MOVE_HELPING_HAND	    89
#define TUTOR_MOVE_SYNTHESIS	    90
#define TUTOR_MOVE_DEFOG	        91
#define TUTOR_MOVE_ALLY_SWITCH	    92
#define TUTOR_MOVE_TAILWIND	        93
#define TUTOR_MOVE_STEALTH_ROCK	    94

// Isle of Armor Moves
// #define TUTOR_MOVE_TERRAIN_PULSE	95
// #define TUTOR_MOVE_BURNING_JEALOUSY	96
// #define TUTOR_MOVE_FLIP_TURN	    97
// #define TUTOR_MOVE_GRASSY_GLIDE	    98
// #define TUTOR_MOVE_RISING_VOLTAGE	99
// #define TUTOR_MOVE_COACHING	        100
// #define TUTOR_MOVE_SCORCHING_SANDS	101
// #define TUTOR_MOVE_DUAL_WINGBEAT	102
// #define TUTOR_MOVE_METEOR_BEAM	    103
// #define TUTOR_MOVE_SKITTER_SMACK	104
// #define TUTOR_MOVE_TRIPLE_AXEL	    105
// #define TUTOR_MOVE_CORROSIVE_GAS	106
// #define TUTOR_MOVE_EXPANDING_FORCE	107
// #define TUTOR_MOVE_POLTERGEIST	    108
// #define TUTOR_MOVE_SCALE_SHOT	    109
// #define TUTOR_MOVE_LASH_OUT	        110
// #define TUTOR_MOVE_STEEL_ROLLER	    111
// #define TUTOR_MOVE_MISTY_EXPLOSION	112

#define TUTOR_MOVE_COUNT            95

#define PARTY_LAYOUT_SINGLE          0
#define PARTY_LAYOUT_DOUBLE          1
#define PARTY_LAYOUT_MULTI           2
#define PARTY_LAYOUT_MULTI_SHOWCASE  3  // The layout during the screen that appears just before a multi battle
#define PARTY_LAYOUT_COUNT           4
#define KEEP_PARTY_LAYOUT            0xFF

#define PARTY_MENU_TYPE_FIELD                     0 
#define PARTY_MENU_TYPE_IN_BATTLE                 1 
#define PARTY_MENU_TYPE_CONTEST                   2 
#define PARTY_MENU_TYPE_CHOOSE_MON                3 
#define PARTY_MENU_TYPE_CHOOSE_HALF               4  // multi battles, eReader battles, and some battle facilities
#define PARTY_MENU_TYPE_MULTI_SHOWCASE            5
#define PARTY_MENU_TYPE_DAYCARE                   6 
#define PARTY_MENU_TYPE_MOVE_RELEARNER            7 
#define PARTY_MENU_TYPE_UNION_ROOM_REGISTER       8  // trading board
#define PARTY_MENU_TYPE_UNION_ROOM_TRADE          9  // trading board
#define PARTY_MENU_TYPE_SPIN_TRADE                10 // Unused beta for Gen IV's Spin Trade
#define PARTY_MENU_TYPE_MINIGAME                  11
#define PARTY_MENU_TYPE_STORE_PYRAMID_HELD_ITEMS  12

#define PARTY_ACTION_CHOOSE_MON         0
#define PARTY_ACTION_SEND_OUT           1
#define PARTY_ACTION_CANT_SWITCH        2
#define PARTY_ACTION_USE_ITEM           3
#define PARTY_ACTION_ABILITY_PREVENTS   4
#define PARTY_ACTION_GIVE_ITEM          5  
#define PARTY_ACTION_GIVE_PC_ITEM       6   // Unused. Not possible to give non-mail items directly from PC
#define PARTY_ACTION_GIVE_MAILBOX_MAIL  7
#define PARTY_ACTION_SWITCH             8
#define PARTY_ACTION_SWITCHING          9
#define PARTY_ACTION_SOFTBOILED         10
#define PARTY_ACTION_CHOOSE_AND_CLOSE   11
#define PARTY_ACTION_MOVE_TUTOR         12
#define PARTY_ACTION_MINIGAME           13
#define PARTY_ACTION_REUSABLE_ITEM      14  // Unused. The only reusable items are handled separately

// IDs for DisplayPartyMenuStdMessage, to display the message at the bottom of the party menu
#define PARTY_MSG_CHOOSE_MON                0
#define PARTY_MSG_CHOOSE_MON_OR_CANCEL      1
#define PARTY_MSG_CHOOSE_MON_AND_CONFIRM    2
#define PARTY_MSG_MOVE_TO_WHERE             3 
#define PARTY_MSG_TEACH_WHICH_MON           4
#define PARTY_MSG_USE_ON_WHICH_MON          5
#define PARTY_MSG_GIVE_TO_WHICH_MON         6
#define PARTY_MSG_NOTHING_TO_CUT            7
#define PARTY_MSG_CANT_SURF_HERE            8
#define PARTY_MSG_ALREADY_SURFING           9
#define PARTY_MSG_CURRENT_TOO_FAST          10
#define PARTY_MSG_ENJOY_CYCLING             11
#define PARTY_MSG_ALREADY_IN_USE            12
#define PARTY_MSG_CANT_USE_HERE             13
#define PARTY_MSG_NO_MON_FOR_BATTLE         14
#define PARTY_MSG_CHOOSE_MON_2              15
#define PARTY_MSG_NOT_ENOUGH_HP             16
#define PARTY_MSG_X_MONS_ARE_NEEDED         17
#define PARTY_MSG_MONS_CANT_BE_SAME         18
#define PARTY_MSG_NO_SAME_HOLD_ITEMS        19
#define PARTY_MSG_UNUSED                    20
#define PARTY_MSG_DO_WHAT_WITH_MON          21
#define PARTY_MSG_RESTORE_WHICH_MOVE        22
#define PARTY_MSG_BOOST_PP_WHICH_MOVE       23
#define PARTY_MSG_DO_WHAT_WITH_ITEM         24
#define PARTY_MSG_DO_WHAT_WITH_MAIL         25
#define PARTY_MSG_ALREADY_HOLDING_ONE       26
#define PARTY_MSG_NONE                      127

// IDs for DisplayPartyPokemonDescriptionText, to display a message in the party pokemon's box
#define PARTYBOX_DESC_NO_USE      0
#define PARTYBOX_DESC_ABLE_3      1
#define PARTYBOX_DESC_FIRST       2
#define PARTYBOX_DESC_SECOND      3
#define PARTYBOX_DESC_THIRD       4
#define PARTYBOX_DESC_FOURTH      5
#define PARTYBOX_DESC_ABLE        6
#define PARTYBOX_DESC_NOT_ABLE    7
#define PARTYBOX_DESC_ABLE_2      8
#define PARTYBOX_DESC_NOT_ABLE_2  9
#define PARTYBOX_DESC_LEARNED     10
#define PARTYBOX_DESC_HAVE        11
#define PARTYBOX_DESC_DONT_HAVE   12

#define SELECTWINDOW_ACTIONS  0
#define SELECTWINDOW_ITEM     1
#define SELECTWINDOW_MAIL     2
#define SELECTWINDOW_MOVES    3

#endif // GUARD_CONSTANTS_PARTY_MENU_H
