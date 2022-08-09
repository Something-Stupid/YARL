#pragma once

#include "vector.h"

enum class ActionType {
    BASE,  // should never be used
    MOVEMENT,
};

struct Action {
    ActionType type = ActionType::BASE;
    virtual ~Action() = default;
};

struct MovementAction : Action {
    Vector2 direction;

    MovementAction(Vector2 direction) : direction(direction) { type = ActionType::MOVEMENT; }
};
