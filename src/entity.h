#pragma once

#include <libtcod.hpp>

#include "vector.h"

struct Entity {
    int character;
    TCOD_ColorRGBA foreground;
    Vector2 position;
};
