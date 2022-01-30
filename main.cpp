#define SDL_MAIN_HANDLED
#define SDL_STBIMAGE_IMPLEMENTATION 
#include "SDL_stbimage.h"
#include <iostream>
#include "Config.h"
#include "SDLSystem.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Window.h"
#include "Texture.h"
#include "Artillery.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){    
    try {        
        SDLSystem _sdl(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        Window _window{Cfg::TITLE, WindowSettings{}};
        Renderer _r { _window };        
        InputManager _input {};

        Texture bg(_r, Cfg::img::background);
        Texture landscape(_r, Cfg::img::landscape);
              
        Artillery a;

        while (!_input.quitRequested()) {
            _input.update();                       
            _r.clear();
            _r.drawTexture(bg);
            _r.drawTexture(landscape);
            _r.present();
        }
        return 0;
    } catch (const SDLInitError& e) {
        std::cerr << "SDL initialization error: " << e.what() << std::endl;
    } catch (const SDLError& e) {
        std::cerr << "SDL error: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown failure occurred. Exiting." << std::endl;
    }
    return EXIT_SUCCESS;
}
