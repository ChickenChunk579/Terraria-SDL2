#pragma once

#include <math.hpp>
#include <consts.hpp>

#include <SDL.h>

#define RELATIVE_TILE(bp, o) tiles[XY(add(bp, o).x, add(bp, o).y)]
#define DEFINE_TILE_SRCRECT_CALCULATOR(name) SDL_Rect name(int id, Vector2i position)

struct Tile
{
    int id;
    Vector2i position;
};

const Vector2i tile_size = {16, 16};
const Vector2i tile_seperation = {2, 2};

const Vector2i tile_center = {1, 1};
const Vector2i tile_left = {0, 0};
const Vector2i tile_right = {4, 0};
const Vector2i tile_top = {1, 0};
const Vector2i tile_bottom = {1, 2};
const Vector2i tile_top_left = {4, 3};
const Vector2i tile_top_right = {5, 3};
const Vector2i tile_bottom_left = {4, 4};
const Vector2i tile_bottom_right = {5, 4};
const Vector2i tile_strip_side_end_left = {9, 1};
const Vector2i tile_strip_side_end_right = {12, 1};
const Vector2i tile_strip_side = {6, 4};
const Vector2i tile_strip_vertical = {5, 0};
const Vector2i tile_strip_vertical_end_top = {6, 0};
const Vector2i tile_strip_vertical_end_bottom = {6, 3};
const Vector2i tile_single = {9, 3};

static Tile *tiles;

static AutoTileData tile_top_left_autotile = {
    '/', 'N', '/',
    'N', 'Y', 'Y',
    '/', 'Y', '/'};
    
static AutoTileData tile_top_right_autotile = {
    '/', 'N', 'N',
    'Y', 'Y', 'N',
    '/', 'Y', '/'};

static AutoTileData tile_bottom_left_autotile = {
    '/', 'Y', '/',
    'N', 'Y', 'Y',
    'N', 'N', 'N'};
static AutoTileData tile_bottom_right_autotile = {
    '/', 'Y', '/',
    'Y', 'Y', 'N',
    'N', 'N', 'N'};

static AutoTileData tile_top_autotile = {
    '/', 'N', '/',
    'Y', 'Y', 'Y',
    '/', 'Y', '/'};

static AutoTileData tile_bottom_autotile = {
    '/', 'Y', '/',
    'Y', 'Y', 'Y',
    '/', 'N', '/'};

static AutoTileData tile_left_autotile = {
    '/', 'Y', 'Y',
    'N', 'Y', 'Y',
    '/', 'Y', 'Y'};


static AutoTileData tile_right_autotile = {
    'Y', 'Y', '/',
    'Y', 'Y', 'N',
    'Y', 'Y', '/'};

static AutoTileData tile_strip_side_end_left_autotile = {
    'N', 'N', '/',
    'N', 'Y', 'Y',
    'N', 'N', '/'};

static AutoTileData tile_strip_side_end_right_autotile = {
    '/', 'N', 'N',
    'Y', 'Y', 'N',
    '/', 'N', 'N'};

static AutoTileData tile_strip_side_autotile = {
    '/', 'N', '/',
    'Y', 'Y', 'Y',
    '/', 'N', '/'};
static AutoTileData tile_strip_vertical_autotile = {
    '/', 'Y', '/',
    'N', 'Y', 'N',
    '/', 'Y', '/'};
static AutoTileData tile_strip_vertical_end_top_autotile = {
    '/', 'N', '/',
    'N', 'Y', 'N',
    '/', 'Y', '/'};
static AutoTileData tile_strip_vertical_end_bottom_autotile = {
    '/', 'Y', '/',
    'N', 'Y', 'N',
    '/', 'N', '/'};

static AutoTileData tile_single_autotile = {
    '/', 'N', '/',
    'N', 'Y', 'N',
    '/', 'N', '/'};

Vector2i getTileOrientationByPosition(Vector2i position)
{
    AutoTileData data = {
        'N',
        'N',
        'N',
        'N',
        'N',
        'N',
        'N',
        'N',
        'N',
    };

    if (RELATIVE_TILE(position, v2(-1, -1)).id != -1)
    {
        data.v11 = 'Y';
    }
    if (RELATIVE_TILE(position, v2(0, -1)).id != -1)
    {
        data.v12 = 'Y';
    }
    if (RELATIVE_TILE(position, v2(1, -1)).id != -1)
    {
        data.v13 = 'Y';
    }

    if (RELATIVE_TILE(position, v2(-1, 0)).id != -1)
    {
        data.v21 = 'Y';
    }
    if (RELATIVE_TILE(position, v2(0, 0)).id != -1)
    {
        data.v22 = 'Y';
    }
    if (RELATIVE_TILE(position, v2(1, 0)).id != -1)
    {
        data.v23 = 'Y';
    }

    if (RELATIVE_TILE(position, v2(-1, 1)).id != -1)
    {
        data.v31 = 'Y';
    }
    if (RELATIVE_TILE(position, v2(0, 1)).id != -1)
    {
        data.v32 = 'Y';
    }
    if (RELATIVE_TILE(position, v2(1, 1)).id != -1)
    {
        data.v33 = 'Y';
    }

    if (compare(data, tile_single_autotile))
    {
        return tile_single;
    }
    else if (compare(data, tile_top_left_autotile))
    {
        return tile_top_left;
    }
    else if (compare(data, tile_top_right_autotile))
    {
        return tile_top_right;
    }
    else if (compare(data, tile_bottom_left_autotile))
    {
        return tile_bottom_left;
    }
    else if (compare(data, tile_bottom_right_autotile))
    {
        return tile_bottom_right;
    }
    else if (compare(data, tile_strip_vertical_end_top_autotile))
    {
        return tile_strip_vertical_end_top;
    }
    else if (compare(data, tile_strip_vertical_end_bottom_autotile))
    {
        return tile_strip_vertical_end_bottom;
    }
    else if (compare(data, tile_top_autotile))
    {
        return tile_top;
    }
    else if (compare(data, tile_bottom_autotile))
    {
        return tile_bottom;
    }
    else if (compare(data, tile_left_autotile))
    {
        return tile_left;
    }
    else if (compare(data, tile_right_autotile))
    {
        return tile_right;
    }
    else if (compare(data, tile_strip_side_end_left_autotile))
    {
        return tile_strip_side_end_left;
    }
    else if (compare(data, tile_strip_side_end_right_autotile))
    {
        return tile_strip_side_end_right;
    }
    else if (compare(data, tile_strip_side_autotile))
    {
        return tile_strip_side;
    }
    else if (compare(data, tile_strip_vertical_autotile))
    {
        return tile_strip_vertical;
    }
    else
    {
        return tile_center;
    }
}

DEFINE_TILE_SRCRECT_CALCULATOR(defaultSrcrectCalculator) {
    Vector2i orientation = getTileOrientationByPosition(position);
    SDL_Rect srcRect = {
        ((tile_size.x + 2) * orientation.x),
        ((tile_size.y + 2) * orientation.y),
        (tile_size.x),
        (tile_size.y),
    };

    return srcRect;
}

DEFINE_TILE_SRCRECT_CALCULATOR(lifeCrystalSrcrectCalculator) {
    Vector2i orientation = v2(0, 1);

    if (RELATIVE_TILE(position, v2(-1, 0)).id == id) {
        orientation = v2(1, 1);
    }
    if (RELATIVE_TILE(position, v2(0, 1)).id == id && RELATIVE_TILE(position, v2(-1, 0)).id == id) {
        orientation = v2(1, 0);
    }
    if (RELATIVE_TILE(position, v2(0, 1)).id == id && RELATIVE_TILE(position, v2(1, 0)).id == id) {
        orientation = v2(0, 0);
    }

    SDL_Rect srcRect = {
        ((tile_size.x + 2) * orientation.x),
        ((tile_size.y + 2) * orientation.y),
        (tile_size.x),
        (tile_size.y),
    };

    return srcRect;
}

DEFINE_TILE_SRCRECT_CALCULATOR(platformSrcrectCalculator) {
    Vector2i orientation = v2(0, 0);

    if (RELATIVE_TILE(position, v2(-1, 0)).id != id && RELATIVE_TILE(position, v2(-1, 0)).id != -1) {
        orientation.x = 3;
    }
    else if (RELATIVE_TILE(position, v2(1, 0)).id != id && RELATIVE_TILE(position, v2(1, 0)).id != -1) {
        orientation.x = 4;
    }

    SDL_Rect srcRect = {
        ((tile_size.x + 2) * orientation.x),
        ((tile_size.y + 2) * orientation.y),
        (tile_size.x),
        (tile_size.y),
    };

    return srcRect;
}


void drawTile(SDL_Renderer *renderer, Vector2i cameraPos, SDL_Texture *tile, Vector2i tilePos, int id)
{
    SDL_Rect (*calculator)(int, Vector2i);

    if (id == 12 || id == 21) {
        calculator = lifeCrystalSrcrectCalculator;
    } else if (id == 19) {
        calculator = platformSrcrectCalculator;
    } else {
        calculator = defaultSrcrectCalculator;
    }

    SDL_Rect srcRect = calculator(id, tilePos);
    

    SDL_Rect destRect = {
        ((tilePos.x * 16) + cameraPos.x),
        ((tilePos.y * 16) + cameraPos.y),
        (tile_size.x),
        (tile_size.y),
    };
    // SDL_BlitSurface(tile, &srcRect, screen, &destRect);

    SDL_RenderCopy(renderer, tile, &srcRect, &destRect);
}