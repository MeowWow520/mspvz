#pragma once

#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <SDL.h>
#include "StructTile.h"
#include "Route.h"



class Map {

public:
    Map() = default;
    ~Map() = default;
    // 宏定义 -- 把一条条怪物路线存入一个哈希表
    typedef std::unordered_map<int, Route> _SpawnerRoutePool;
    // 函数 -- 从文件中加载地图
    bool Load(const std::string& Map_Path) {
        // Map_Path 为地图文件路径

        // 打开文件
        std::ifstream Map_File(Map_Path);
        if (!Map_File.good()) return false;
        TileMap Tile_Map_Temp;

        int Index_X{0}, Index_Y{0};
        std::string String_Line;
        while (std::getline(Map_File, String_Line)) {
            String_Line = Trim_String(String_Line);
            // 判断 -- 如果是空行，则跳过
            if (String_Line.empty()) continue;
            Index_X = -1, Index_Y++;
            Tile_Map_Temp.emplace_back();
            std::stringstream String_Stream(String_Line);
            std::string String_Tile;
            while (std::getline(String_Stream, String_Tile, ',')) {
                Index_X++;
                Tile_Map_Temp[Index_Y].emplace_back();
                _Tile& Tile_Map = Tile_Map_Temp[Index_Y].back();
                LoadTileFromString(Tile_Map, String_Tile);
            }
        }
        // 关闭文件
        Map_File.close();
        if (Tile_Map_Temp.empty() || Tile_Map_Temp[0].empty()) return false;
        Tile_Map = Tile_Map_Temp;
        GenerateMapCache();
        return true;
    };
    // 函数 -- 获取地图的宽高
    size_t GetWidth() const { 
        if (Tile_Map.empty()) return 0;
        return Tile_Map[0].size();
    }
    // 函数 -- 获取地图的高度
    size_t GetHeight() const { return Tile_Map.size(); }
    // 函数 -- 获取地图
    const TileMap& GetTileMap() const { return Tile_Map; }
    // 函数 -- 获取守卫家的索引坐标
    const SDL_Point& GetHomeIndex() const { return Index_Home; }
    // 函数 -- 获取生成器路线池
    const _SpawnerRoutePool& GetSpawnerRoutePool() const
        { return SpawnerRoutePool; }
    // 函数 -- 放置塔，把瓦片的 HasPlants 属性设为 true
    void PlaceTower (const SDL_Point& Index_Tile) 
        { Tile_Map[Index_Tile.y][Index_Tile.x].HasPlants = true; }

protected:

private:
    TileMap Tile_Map;
    // 变量 -- 守卫家的索引坐标
    SDL_Point Index_Home{ 0 };
    // 变量 -- 生成器路线池
    _SpawnerRoutePool SpawnerRoutePool;
    // 字符串函数 -- 去除字符串两端的空格
    std::string Trim_String(const std::string& str) {
        size_t Begin_Index = str.find_first_not_of(" \t");
        // 如果字符串全是空格，则返回空字符串
        if (Begin_Index == std::string::npos) return "";
        size_t End_Index = str.find_last_not_of(" \t");
        return str.substr(Begin_Index, (End_Index - Begin_Index + 1));
    }
    // 函数 -- 从字符串中加载瓦片
    void LoadTileFromString(_Tile& Tile_Map, const std::string& String) {
        std::string String_Tidy = Trim_String(String);
        std::string String_Value;
        std::vector<int> Values;
        std::stringstream String_Stream(String_Tidy);
        while (std::getline(String_Stream, String_Value, '\\')) {
            int Value;
            try { Value = std::stoi(String_Value); }
            catch (const std::invalid_argument&) { Value = -1; }
            Values.push_back(Value);
        }
        Tile_Map.Terrian = (Values.size() < 1 || Values[0] < 0) ? 0 : Values[0];
        Tile_Map.Decoration = (Values.size() < 2) ? -1 : Values[1];
        Tile_Map.Direction = (_Tile::EnumDirection) ((Values.size() < 3 || Values[2] < 0) ? -1 : Values[2]);
        Tile_Map.SpecialFlag = (Values.size() <= 3) ? -1 : Values[3];
    }
    // 函数 -- 生成地图缓存
    void GenerateMapCache() {
        for (int y = 0; y < GetHeight(); y++) {
            for (int x = 0; x < GetWidth(); x++) {
                const _Tile& Tile = Tile_Map[y][x];
                if (Tile.SpecialFlag < 0) continue;
                if (Tile.SpecialFlag == 0) {
                    Index_Home.x = x;
                    Index_Home.y = y;
                }
                else SpawnerRoutePool[Tile.SpecialFlag] = Route(Tile_Map, { x, y });

            }
        }
    }
};
#endif // !MAP_H