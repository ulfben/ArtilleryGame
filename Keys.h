#pragma once
#include "SDLex.h"
#include <algorithm>
template<size_t N = 3>
class Keys { //map multiple keys to single action. (eg. w + up + 8 for "walk forward")
  SDL_Scancode _keys[N]{};
	using const_iter = SDL_Scancode const* const;
public:
	constexpr Keys(const std::initializer_list<SDL_Scancode> list) {
		assert(list.size() <= N && "Mapping too many keys to an action.");
	//	std::copy(list.begin(), list.end(), std::begin(_keys), std::end(_keys));						
	}
	inline constexpr const_iter end() const noexcept {
		return &_keys[N];
	}
	inline constexpr const_iter begin() const noexcept {
		return &_keys[0];
	}
};