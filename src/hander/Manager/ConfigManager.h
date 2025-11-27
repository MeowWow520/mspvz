#pragma once

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cJSON.h>
#include <SDL.h>
#include "SingletonInstanceTemplate.h"
#include "../Map.h"
#include "../Wave.h"


class ConfigManager : public SITemplate<ConfigManager> {
	friend class SITemplate<ConfigManager>;

public:
    struct _BasicTemplate {
        std::string WindowTitle{u8"Default_Window_Title"};
        int WindowWidth{1280};
	    int WindowHeight{720};
    };
    struct _PlayerTemplate {
        double Speed{5.0};
        double NormalAttackSpeed{0.5};
        double NormalAttackDamage{0.0};
        double SkillInterval{10.0};
        double SkillDamage{1.0};
    };
    struct _TowerTemplate {
        double Interval[10] = { 1 };
        double Damage[10] = { 25 };
        double ViewRange[10] = { 5 };
        double Cost[10] = { 50 };
        double UpgradeCost[9] = { 75 };
    };
    struct _EnemyTemplate {
        double Speed{1.0};
        double Health{100.0};
        double Damage{1.0};
        double Reward{0.5};
        double RecoverInterval{10.0};
        double RecoverRange{0.0};
        double RecoverIntensity{25.0};
    };

    Map _Map;
    std::vector<Wave> WaveList;
    const double numInitialHealth{10.0};
    const double numInitialCoin{100.0};
    const double numCionPerProp{10.0};
    int LevelArcher{0};
    int LevelAxeman{0};
    int LevelGonner{0};
    bool IsGameWin{true};
    bool IsGameOver{false};
    SDL_Rect RectTileMap{0};

    _BasicTemplate BasicTemplate;
    _PlayerTemplate PlayerTemplate;

    _TowerTemplate ArcherTemplate;
    _TowerTemplate AxemanTemplate;
    _TowerTemplate GonnerTemplate;

    _EnemyTemplate SilmeTemplate;
    _EnemyTemplate SilmeKingTemplate;
    _EnemyTemplate GoblinTemplate;
    _EnemyTemplate GoblinPriestTemplate;

    bool LoadLevelConfig(const std::string& path) {};
    bool LoadGameConfig(const std::string& path) {};
protected:
    ConfigManager() = default;
    ~ConfigManager() = default;

private:

};

#endif // !CONFIGMANAGER_H