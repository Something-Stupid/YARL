#pragma once

#include <SDL.h>

#include "action.h"

class InputManager {
public:
    [[nodiscard]] Action processInput();
};
