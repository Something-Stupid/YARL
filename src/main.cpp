#ifdef __EMSCRIPTEN__
#include <emscripten.h>  //Emscripten allows C/C++ code to be compiled to WebAssembly so that it can run in the web
#endif                   // __EMSCRIPTEN__
#include <SDL.h>

#include <iostream>
#include <libtcod.hpp>

#include "engine.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4297)  // Allow "throw" in main().  Letting the
                                 // compiler handle termination.
#endif

int main(int argc, char** argv) {
    try {
        Engine engine(argc, argv);

#ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(engine.gameLoop(), 0, 0);
#else
        while (true) {
            engine.getInput();
            engine.render();
        }
#endif

    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        throw;
    }
}
