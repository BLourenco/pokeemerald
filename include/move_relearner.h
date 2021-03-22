#ifndef GUARD_MOVE_RELEARNER_H
#define GUARD_MOVE_RELEARNER_H

// Which learnset to use
#define LEARNSET_TYPE_LEVEL_UP  0
#define LEARNSET_TYPE_EGG       1

void TeachMoveRelearnerMove(void);
void MoveRelearnerShowHideHearts(s32);
void MoveRelearnerShowHideTypeAndCategory(s32);
void CB2_InitLearnMove(void);

#endif //GUARD_MOVE_RELEARNER_H
