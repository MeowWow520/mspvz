#pragma once

#ifndef ROUTE_H
#define ROUTE_H
#include <vector>
#include <SDL.h>
#include "StructTile.h"
#include "Map.h"



/** Route.h 
 * 
 */
class Route {

public:
    typedef std::vector<SDL_Point> _IndexList;
    Route() = default;
    Route(const TileMap& Map, const SDL_Point& Index_Origin) {
        size_t MapWidth = Map[0].size();
        size_t MapHeight = Map.size();
        SDL_Point Index_Next = Index_Origin;

        while (true) {
            // 判断是否超出地图边界
            if (Index_Next.x >= MapWidth || Index_Next.y >= MapHeight)
                break;
            // 判断是否闭合造成死循环
            if (ChackDuplicateIndex(Index_Next)) break;
            else IndexList.push_back(Index_Next);
            // 布尔值 -- 判断下一个位置是否存在
            bool Is_Next_Exist{true};
            const _Tile& Tile = Map[Index_Next.y][Index_Next.x];
            if (Tile.SpecialFlag == 0) break;
            switch (Tile.Direction) {
            case _Tile::EnumDirection::UP:
                Index_Next.y--;
                break;
            case _Tile::EnumDirection::DOWN:
                Index_Next.y++;
                break;
            case _Tile::EnumDirection::LEFT:
                Index_Next.x--;
                break;
            case _Tile::EnumDirection::RIGHT:
                Index_Next.x++;
                break;

            default:
                Is_Next_Exist = false;
                break;
            }
            if (!Is_Next_Exist) break;
        }
    };

    ~Route() = default;
    // 函数 -- 获取路径
    const _IndexList& GetIndexList() const { return IndexList; }

protected:


private:
    _IndexList IndexList;
    // 函数 -- 检查闭合路线
    bool ChackDuplicateIndex(const SDL_Point& Target_Index) {
        for (const SDL_Point& Index : IndexList) {
            if (Index.x == Target_Index.x && Index.y == Target_Index.y) 
                return true;
        }
        return false;
    }
};

#endif // !ROUTE_H