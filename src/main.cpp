#ifdef __EMSCRIPTEN__
#include <emscripten.h>  //Emscripten allows C/C++ code to be compiled to WebAssembly so that it can run in the web
#endif  // __EMSCRIPTEN__
#include <SDL.h>

#include <iostream>
#include <libtcod.hpp>

#if defined(_MSC_VER)
#pragma warning(disable : 4297)  // Allow "throw" in main().  Letting the compiler handle termination.
#endif

std::filesystem::path getDataDirectory() {
    static auto root = std::filesystem::path{"."};  // Begin at the working directory.
    while (!std::filesystem::exists(root / "data")) {
        // If the current working directory is missing the data dir then it will assume it exists in any parent
        // directory.
        root /= "..";
        if (!std::filesystem::exists(root)) {
            throw std::runtime_error("Could not find the data directory.");
        }
    }
    return root / "data";
};

// global console and context objects, they only exist inside this translation unit
static tcod::Console console;
static tcod::Context context;

void gameLoop() {
    console.clear();
    tcod::print(console, {0, 0}, "Hello World", std::nullopt, std::nullopt);
    context.present(console);

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
        }
    }
}

int main(int argc, char** argv) {
    try {
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

#ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(gameLoop, 0, 0);
#else
        while (true) {
            gameLoop();
        }
#endif

    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        throw;
    }
}
