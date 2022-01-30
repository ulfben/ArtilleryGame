#pragma once
#include <string_view>
#include "SDLex.h"
struct SDL_Window1;
struct WindowSettings {
  unsigned width = 1280;
  unsigned height = 720;
  unsigned flags = SDL_WINDOW_OPENGL;
};
	
class Window {	
	SDLex::WindowPtr _ptr;	

public:
    Window(std::string_view title, WindowSettings cfg);
	void setTitle(std::string_view title) const noexcept;
	SDL_Window* getPtr() const noexcept;
	void setWindowGrab(bool on) const noexcept;
	bool getWindowGrab() const noexcept;
	void hideCursor() const noexcept;
	void showCursor() const noexcept;
};