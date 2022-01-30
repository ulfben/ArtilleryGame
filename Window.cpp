#include "Window.h"
#include "SDLSystem.h"
#include <stdexcept>
Window::Window(std::string_view title, WindowSettings cfg)  :
	_ptr(SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cfg.width, cfg.height, cfg.flags)){
	if (!_ptr) {
		throw SDLError();
	}
}
void Window::setTitle(std::string_view title) const noexcept {
	SDL_SetWindowTitle(_ptr.get(), title.data());
}

SDL_Window* Window::getPtr() const noexcept {
	assert(_ptr != nullptr && "Window: invalid pointer. Use after delete?");
	return _ptr.get();
}
bool Window::getWindowGrab() const noexcept {
	return SDLex::toBool(SDL_GetWindowGrab(_ptr.get()));
}
void Window::setWindowGrab(bool on) const noexcept {
	SDL_SetWindowGrab(_ptr.get(), SDLex::fromBool(on));
}
void Window::hideCursor() const noexcept {
	SDL_ShowCursor(SDL_DISABLE);
}
void Window::showCursor() const noexcept {
	SDL_ShowCursor(SDL_ENABLE);
}