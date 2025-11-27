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

    typedef std::unordered_map<int, Route> SpawnerRoutePool;

    bool Load(const std::string& Map_Path) {
        std::ifstream Map_File(Map_Path);
        if (!Map_File.good()) return false;
        TileMap Tile_Map_Temp;

        int Index_X{0}, Index_Y{0};
        std::string String_Line;
        while (std::getline(Map_File, String_Line)) {
            String_Line = Trim_String(String_Line);
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

        Map_File.close();
        if (Tile_Map_Temp.empty() || Tile_Map_Temp[0].empty()) return false;
        Tile_Map = Tile_Map_Temp;
        GenerateMapCache();
        return true;
    };
    size_t GetWidth() const { 
        if (Tile_Map.empty()) return 0;
        return Tile_Map[0].size();
    }
    size_t GetHeight() const { return Tile_Map.size(); }
    const TileMap& GetTileMap() const { return Tile_Map; }
    const SDL_Point& GetHomeIndex() const { return Index_Home; }
    const SpawnerRoutePool& GetSpawnerRoutePool() const
        { return Spawner_Route_Pool; }
    void PlaceTower (const SDL_Point& Index_Tile) 
        { Tile_Map[Index_Tile.y][Index_Tile.x].HasPlants = true; }

protected:

private:
    TileMap Tile_Map;
    SDL_Point Index_Home{ 0 };
    SpawnerRoutePool Spawner_Route_Pool;
    std::string Trim_String(const std::string& str) {
        size_t Begin_Index = str.find_first_not_of(" \t");
        if (Begin_Index == std::string::npos) return "";
        size_t End_Index = str.find_last_not_of(" \t");
        return str.substr(Begin_Index, (End_Index - Begin_Index + 1));
    }
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
    void GenerateMapCache() {
        for (int y = 0; y < GetHeight(); y++) {
            for (int x = 0; x < GetWidth(); x++) {
                const _Tile& Tile = Tile_Map[y][x];
                if (Tile.SpecialFlag < 0) continue;
                if (Tile.SpecialFlag == 0) {
                    Index_Home.x = x;
                    Index_Home.y = y;
                }
                else Spawner_Route_Pool[Tile.SpecialFlag] = Route(Tile_Map, { x, y });

            }
        }
    }
};
#endif // !MAP_H