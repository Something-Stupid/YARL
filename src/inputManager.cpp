#include "inputManager.h"

#include <cstdlib>

[[nodiscard]] Action InputManager::processInput() {
    // handle input
    SDL_Event event;
#ifndef __EMSCRIPTEN__
    // block until an event happens, not compatible with Emscripten
    SDL_WaitEvent(nullptr);
#endif

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                std::exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_UP: {
                        return MovementAction({0, -1});
                        break;
                    }
                    case SDLK_DOWN: {
                        return MovementAction({0, 1});
                        break;
                    }
                    case SDLK_LEFT: {
                        return MovementAction({-1, 0});
                        break;
                    }
                    case SDLK_RIGHT: {
                        return MovementAction({1, 0});
                    }
                }
            }
        }
    }
}
