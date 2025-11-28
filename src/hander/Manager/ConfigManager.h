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



/** ConfigManager.h 定义了配置管理器
 * 
 *  该类负责读取配置文件，为实现玩家自定义地图。
 *  该类为单例模式
 */
class ConfigManager : public SITemplate<ConfigManager> {
	friend class SITemplate<ConfigManager>;

public:
    /** 结构体 -- 定义josn文件中的各个部分数据
     * 
     ** _BasicTemplate: 存储基础配置信息
     *      | WindowTitle: 窗口标题
     *      | WindowWidth: 窗口宽度
     *      | WindowHeight: 窗口高度
     * 
     ** _PlayerTemplate: 存储玩家配置信息
     *      | Speed: 移动速度
     *      | NormalAttackSpeed: 普通攻击速度
     *      | NormalAttackDamage: 普通攻击伤害
     *      | SkillInterval: 技能冷却时间
     *      | SkillDamage: 技能伤害
     * 
     ** _TowerTemplate: 存储塔配置信息
     *      | Interval: 攻击间隔
     *      | Damage: 攻击伤害
     *      | ViewRange: 攻击范围
     *      | Cost: 建造费用
     *      | UpgradeCost: 升级费用
     * 
     ** _EnemyTemplate: 存储敌人配置信息
     *      | Speed: 移动速度
     *      | Health: 生命值
     *      | Damage: 伤害
     *      | Reward: 奖励
     *      | RecoverInterval: 恢复间隔
     *      | RecoverRange: 恢复范围
     *      | RecoverIntensity: 恢复强度
     */
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
    // 向量 -- 每一波次被存储到一个向量 WaveList[int] 中
    std::vector<Wave> WaveList;
    /** 常量 -- 存储游戏初始信息
     *  numInitialHealth: 初始生命值
     *  numInitialCoin: 初始金币
     *  numCionPerProp: 每个道具增加的金币数
     */
    const double numInitialHealth{10.0};
    const double numInitialCoin{100.0};
    const double numCionPerProp{10.0};
    /** 变量 -- 存储游戏运行时玩家等级变化
     *  该值随玩家自行升级而变化
     */
    int LevelArcher{0};
    int LevelAxeman{0};
    int LevelGonner{0};
    /** 布尔值 -- 存储游戏运行状态
     * 
     *  IsGameWin: 游戏是否胜利
     *      | true: 默认认为玩家胜利，当玩家Health <= 0时，该值变为 false
     *      | false: 游戏失败
     *  IsGameOver: 游戏是否结束。用于控制主循环开关
     */
    bool IsGameWin{true};
    bool IsGameOver{false};
    SDL_Rect RectTileMap{0};
    // 上文结构体的实例化
    _BasicTemplate BasicTemplate;
    _PlayerTemplate PlayerTemplate;
    // 防御塔的实例化
    _TowerTemplate ArcherTemplate;
    _TowerTemplate AxemanTemplate;
    _TowerTemplate GonnerTemplate;
    // 敌人的实例化
    _EnemyTemplate SilmeTemplate;
    _EnemyTemplate SilmeKingTemplate;
    _EnemyTemplate GoblinTemplate;
    _EnemyTemplate GoblinPriestTemplate;
    // 函数 -- 加载关卡配置文件：加载波次、敌人信息etc.
    bool LoadLevelConfig(const std::string& FilePath) {
        // 打开文件
        std::ifstream File(FilePath);
        if (!File.is_open()) return false;
        std::stringstream StringStream;
        StringStream << File.rdbuf();
        File.close();

        cJSON* cJSONRoot = cJSON_Parse(StringStream.str().c_str());
        if (!cJSONRoot) return false;
        if (cJSONRoot->type != cJSON_Array) {
            cJSON_Delete(cJSONRoot);
            return false;
        }
        // 解析关卡配置
        cJSON* cJSONWave = nullptr;
        cJSON_ArrayForEach(cJSONWave, cJSONRoot) {
            if (cJSONWave->type != cJSON_Object) continue;
            WaveList.emplace_back();
            Wave& Wave = WaveList.back();
            cJSON* cJSONWaveRewards = cJSON_GetObjectItem(cJSONWave, "Rewards");
            if (cJSONWaveRewards && cJSONWaveRewards->type == cJSON_Array) {
                
            }
        }

    }
    // 函数 -- 加载游戏配置文件
    bool LoadGameConfig(const std::string& FilePath) {};

protected:
    ConfigManager() = default;
    ~ConfigManager() = default;

private:

};

#endif // !CONFIGMANAGER_H