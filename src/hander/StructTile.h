#pragma once 

#ifndef STRUCTTILE_H
#define STRUCTTILE_H
#include <vector>


// This is the pixel size of each tile
#define TILE_SIZE 48;
struct Tile {
    /*  Every tile has a position
     *  Which mark the direction of the enemy
     */
    enum class EnumDirection {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE = 0
    };
    /*  Terrian has 4 value 1, 2, 3, 4
     *  Every value is different type.
     *  For two is data leyer, and the other is texture layer
     */
    int Terrian{0};
    /*  Decoration mark is this tile has a decoration
     *  Such as home, flover, etc. ------- DOUBLE CHECK
     *  Each name has a different int value
     */
    int Decoration{-1};
    int SpecialFlag{-1};
    /*  Has_Plants mark is this tile has a plant
     *  If it has, then it will be true
     */
    bool Has_Plants{false};
    EnumDirection Direction{EnumDirection::NONE};
};

/*  Define the tile map 
 *  It is a 2D vector
 *  I typedef it TileMap
 */ 
typedef std::vector<std::vector<Tile>> TileMap;
#endif // !STRUCTTILE_H