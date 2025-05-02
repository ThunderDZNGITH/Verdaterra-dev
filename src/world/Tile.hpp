#pragma once
enum class TileType {
    grass,
    snowy_grass,
    water,
    wood,
    leaves,
    selector
};
struct Tile {
    int x, y, z;
    TileType type;
};