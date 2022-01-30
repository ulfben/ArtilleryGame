#pragma once
#include "SDLex.h"
#include "Utils.h"
#include "Keys.h"
#include <string_view>
namespace Cfg {	
	using KeyMap = Keys<3>;
	using namespace std::literals::string_view_literals;	
	static constexpr std::string_view TITLE = "ArtilleryGame"sv;	
	static constexpr int WIN_WIDTH = 800;
	static constexpr int WIN_HEIGHT = 600;			
	static const KeyMap moveForward{SDL_SCANCODE_KP_8, SDL_SCANCODE_UP, SDL_SCANCODE_W};
    static const KeyMap rotateLeft{SDL_SCANCODE_KP_4, SDL_SCANCODE_LEFT, SDL_SCANCODE_A};
    static const KeyMap moveBackward{SDL_SCANCODE_KP_2, SDL_SCANCODE_DOWN, SDL_SCANCODE_S};	
	static const KeyMap rotateRight{ SDL_SCANCODE_KP_6, SDL_SCANCODE_RIGHT, SDL_SCANCODE_D };

	namespace img {
		static constexpr std::string_view background("./images/background.jpg");
		static constexpr std::string_view landscape("./images/landscape.png");
		static constexpr std::string_view bullet("./images/bullet.jpg");
		static constexpr std::string_view gunbody1("./images/gunbody1.png");
		static constexpr std::string_view gunbarrel1("./images/gunbarrel1.png");
		static constexpr std::string_view gunbody2("./images/gunbody2.png");
		static constexpr std::string_view gunbarrel2("./images/gunbarrel2.png");
		static constexpr std::string_view expl1("./images/expl1.png");
	}
};

