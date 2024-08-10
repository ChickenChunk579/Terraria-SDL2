#pragma once

#define XY(x, y) (WORLD_WIDTH * y) + x

struct AutoTileData
{
    char v11;
    char v12;
    char v13;

    char v21;
    char v22;
    char v23;

    char v31;
    char v32;
    char v33;
};

struct Vector2i
{
    int x, y;
};

bool comparev2i(const Vector2i &left, const Vector2i &right)
{
    return left.x == right.x && left.y == right.y;
}

bool compare(AutoTileData &left, AutoTileData &right)
{
    return (left.v11 == right.v11 || left.v11 == '/' || right.v11 == '/') &&
           (left.v12 == right.v12 || left.v12 == '/' || right.v12 == '/') &&
           (left.v13 == right.v13 || left.v13 == '/' || right.v13 == '/') &&

           (left.v21 == right.v21 || left.v21 == '/' || right.v21 == '/') &&
           (left.v22 == right.v22 || left.v22 == '/' || right.v22 == '/') &&
           (left.v23 == right.v23 || left.v23 == '/' || right.v23 == '/') &&

           (left.v31 == right.v31 || left.v31 == '/' || right.v31 == '/') &&
           (left.v32 == right.v32 || left.v32 == '/' || right.v32 == '/') &&
           (left.v33 == right.v33 || left.v33 == '/' || right.v33 == '/');
}

static Vector2i v2(int x, int y) {
    return {x, y};
}

Vector2i add(Vector2i left, Vector2i right)
{
    return {left.x + right.x, left.y + right.y};
}