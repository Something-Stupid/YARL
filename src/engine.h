#pragma once

#include <filesystem>
#include <libtcod.hpp>
#include <set>

#include "entity.h"
#include "inputManager.h"

struct World {};  // TODO: replace with actual implementation

class Engine {
private:
    InputManager inputManager;
    World world;  // the currently active world, not sure if there will be more than one, but nice to have incase
    std::set<Entity> entities;  // all active entities in world
    tcod::Console console;
    tcod::Context context;

    std::filesystem::path getDataDirectory();

public:
    Entity* player;  // non-owning pointer to player entity

    void processInput();
    void render();
    void gameLoop();

    Engine(int argc, char** argv) {
        inputManager = InputManager();
        world = World();
        entities = std::set<Entity>();
        console = tcod::Console{80, 40};

        auto params = TCOD_ContextParams{};
        params.tcod_version = TCOD_COMPILEDVERSION;
        params.console = console.get();
        params.window_title = "Yet another roguelike";
        params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
        params.vsync = true;
        params.argc = argc;
        params.argv = argv;

        auto tileset = tcod::load_tilesheet(getDataDirectory() / "dejavu16x16_gs_tc.png", {32, 8}, tcod::CHARMAP_TCOD);

        params.tileset = tileset.get();

        context = tcod::Context(params);
    }
};
