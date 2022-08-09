#include "engine.h"

#include <iostream>

// TODO: figure out input system
void Engine::processInput() {
    auto action = inputManager.processInput();
    switch (action.type) {
        case ActionType::MOVEMENT: {
            player->position.x +=
        }
    }
}

void Engine::render() {
    console.clear();
    tcod::print(console, {0, 0}, "Hello World", std::nullopt, std::nullopt);
    context.present(console);
}

void Engine::gameLoop() {
    render();
    processInput();
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
