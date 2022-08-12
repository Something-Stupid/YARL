#pragma once

#include <libtcod.hpp>
#include <string>

#include "vectors.h"

struct Entity {
    std::string character;
    TCOD_ColorRGB foreground;
    Vector2 position;
};
