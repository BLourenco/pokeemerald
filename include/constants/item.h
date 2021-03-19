#ifndef GUARD_ITEM_CONSTANTS_H
#define GUARD_ITEM_CONSTANTS_H

// These constants are used in gItems
#define POCKET_NONE         0
#define POCKET_MEDICINE     1
#define POCKET_POKE_BALLS   2
#define POCKET_ITEMS        3
#define POCKET_TM_HM        4
#define POCKET_BERRIES      5
#define POCKET_COMPETITIVE  6
#define POCKET_TRAINING     7
#define POCKET_KEY_ITEMS    8

#define MEDICINE_POCKET     0
#define BALLS_POCKET        1
#define ITEMS_POCKET        2
#define TMHM_POCKET         3
#define BERRIES_POCKET      4
#define COMPETITIVE_POCKET  5
#define TRAINING_POCKET     6
#define KEYITEMS_POCKET     7
#define POCKETS_COUNT       8

// The Competitive pocket is the largest pocket, so the maximum amount of items
// in a pocket is its count + 1 for the cancel option
#define MAX_POCKET_ITEMS   (BAG_COMPETITIVE_COUNT + 1)


#endif // GUARD_ITEM_CONSTANTS_H
