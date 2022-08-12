#include "engine.h"

#include <iostream>

void Engine::getInput() {
    SDL_Event event;
#ifndef __EMSCRIPTEN__
    SDL_WaitEvent(nullptr);
#endif
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                std::exit(EXIT_SUCCESS);
                break;
            }
            case SDL_KEYDOWN: {
                processInput(event.type, event);
                break;
            }
                // Can expand to handle mouse input and KeyUp events
        }
    }
}

void Engine::processInput(uint32_t eventType, SDL_Event event) {
    switch (eventType) {
        case SDL_KEYDOWN:

            auto& p = entities[0];

            switch (event.key.keysym.sym) {
                case SDLK_UP: {
                    p.position.y -= 1;
                    std::cout << "UP" << std::endl;
                    break;
                }
                case SDLK_DOWN: {
                    p.position.y += 1;
                    std::cout << "DOWN" << std::endl;
                    break;
                }
                case SDLK_LEFT: {
                    p.position.x -= 1;
                    std::cout << "LEFT" << std::endl;
                    break;
                }
                case SDLK_RIGHT: {
                    p.position.x += 1;
                    std::cout << "RIGHT" << std::endl;
                    break;
                }
            }
            break;
    }
}

void Engine::render() {
    console.clear();

    for (auto& entity : entities) {
        tcod::print(console, {entity.position.x, entity.position.y}, entity.character, entity.foreground, std::nullopt);
    }

    context.present(console);
}

void Engine::gameLoop() {
    render();
    getInput();
}

Engine::Engine(int argc, char** argv) {
    world = World();
    entities = std::vector<Entity>();
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

    Entity playerEntity = {"@", {255, 255, 255}, {40, 20}};
    entities.push_back(playerEntity);
}

std::filesystem::path Engine::getDataDirectory() {
    static auto root = std::filesystem::path{"."};  // Begin at the working directory.
    while (!std::filesystem::exists(root / "data")) {
        // If the current working directory is missing the data dir then it will
        // assume it exists in any parent directory.
        root /= "..";
        if (!std::filesystem::exists(root)) {
            throw std::runtime_error("Could not find the data directory.");
        }
    }
    return root / "data";
};
