#ifndef GUARD_POKEDEX_H
#define GUARD_POKEDEX_H

extern u8 gUnusedPokedexU8;
extern void (*gPokedexVBlankCB)(void);

enum
{
    DEX_MODE_NATIONAL,
    DEX_MODE_KANTO,
    DEX_MODE_JOHTO,
    DEX_MODE_HOENN,
    DEX_MODE_SINNOH,
    DEX_MODE_UNOVA,
    DEX_MODE_KALOS,
    DEX_MODE_ALOLA,
    DEX_MODE_GALAR
};

enum
{
    FLAG_GET_SEEN,
    FLAG_GET_CAUGHT,
    FLAG_SET_SEEN,
    FLAG_SET_CAUGHT
};

struct PokedexEntry
{
    /*0x00*/ u8 categoryName[13];
    /*0x0C*/ u16 height; //in decimeters
    /*0x0E*/ u16 weight; //in hectograms
    /*0x10*/ const u8 *description;
    /*0x14*/ u16 unused;
    /*0x16*/ u16 pokemonScale;
    /*0x18*/ u16 pokemonOffset;
    /*0x1A*/ u16 trainerScale;
    /*0x1C*/ u16 trainerOffset;
};  /*size = 0x20*/

void ResetPokedex(void);
u16 GetPokedexHeightWeight(u16 dexNum, u8 data);
u16 GetNationalPokedexCount(u8);
u16 GetHoennPokedexCount(u8);
u16 GetRegionPokedexCount(u8, u8);
u16 GetRegionPokedexTotal(u8, bool8);
u8 DisplayCaughtMonDexPage(u16 dexNum, u32 otId, u32 personality);
s8 GetSetPokedexFlag(u16 nationalNum, u8 caseId);
u16 CreateMonSpriteFromNationalDexNumber(u16, s16, s16, u16);
bool16 HasAllHoennMons(void);
void ResetPokedexScrollPositions(void);
bool16 HasAllMons(void);
void CB2_OpenPokedex(void);

#endif // GUARD_POKEDEX_H
