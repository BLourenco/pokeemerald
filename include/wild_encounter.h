#ifndef GUARD_WILD_ENCOUNTER_H
#define GUARD_WILD_ENCOUNTER_H

#define LAND_WILD_COUNT     12
#define WATER_WILD_COUNT    5
#define ROCK_WILD_COUNT     5
#define FISH_WILD_COUNT     10
#define HIDDEN_WILD_COUNT   3

struct WildPokemon
{
    u8 minLevel;
    u8 maxLevel;
    u16 species;
};

struct WildPokemonInfo
{
    u8 encounterRate;
    const struct WildPokemon *wildPokemon;
};

struct WildPokemonHeader
{
    u8 mapGroup;
    u8 mapNum;
    const struct WildPokemonInfo *landMonsInfo;
    const struct WildPokemonInfo *waterMonsInfo;
    const struct WildPokemonInfo *rockSmashMonsInfo;
    const struct WildPokemonInfo *fishingMonsInfo;
    const struct WildPokemonInfo *headbuttMonsInfo;
    const struct WildPokemonInfo *hiddenMonsInfo;
};

extern bool8 gIsFishingEncounter;

extern const struct WildPokemonHeader gWildMonHeaders[];

void DisableWildEncounters(bool8 disabled);
bool8 StandardWildEncounter(u16 currMetaTileBehavior, u16 previousMetaTileBehavior);
void ScrSpecial_RockSmashWildEncounter(void);
bool8 SweetScentWildEncounter(void);
bool8 DoesCurrentMapHaveFishingMons(void);
void FishingWildEncounter(u8 rod);
u16 GetLocalWildMon(bool8 *isWaterMon);
u16 GetLocalWaterMon(void);
bool8 UpdateRepelCounter(void);
void CreateWildMon(u16 species, u8 level);
u16 GetCurrentMapWildMonHeaderId(void);
u8 ChooseWildMonIndex_Land(void);
u8 ChooseWildMonIndex_WaterRock(void);
u8 ChooseHiddenMonIndex(void);
bool8 TryDoDoubleWildBattle(void);

#endif // GUARD_WILD_ENCOUNTER_H
