#pragma once 

#ifndef STRUCTTILE_H
#define STRUCTTILE_H
#include <vector>


// This is the pixel size of each tile
#define TILE_SIZE 48;
struct Tile {

    enum class EnumDirection {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE = 0
    };
    int Terrian{0};
    int Decoration{-1};
    int SpecialFlag{-1};
    bool Has_Plants{false};
    EnumDirection Direction = EnumDirection::NONE;
};

typedef std::vector<std::vector<Tile>> TileMap;
#endif // !STRUCTTILE_H