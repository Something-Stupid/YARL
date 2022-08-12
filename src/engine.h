#pragma once

#include <SDL.h>

#include <filesystem>
#include <libtcod.hpp>
#include <vector>

#include "entity.h"

struct World {};  // TODO: replace with actual implementation

class Engine {
private:
    World world;  // the currently active world, not sure if there will be more than one, but nice to have incase

    // The entity ID needs to be unique, either through a UUID or by just using sequential numbers
    std::vector<Entity> entities;
    tcod::Console console;
    tcod::Context context;

    std::filesystem::path getDataDirectory();
    void processInput(uint32_t eventType, SDL_Event event);

public:
    uint64_t player;  // ID of player

    void getInput();
    void render();
    void gameLoop();

    Engine(int argc, char** argv);
};
