#pragma once
#include <cassert>
#include <memory>
#include <stdexcept>
#include <string_view>
#pragma warning(push, 0)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)
/*
SDLex: some utilities for wrapping SDL in Modern C++ convenience, like:
        1. unique and shared pointers for all SDL resource types
                        http://swarminglogic.com/jotting/2015_05_smartwrappers
        2. exception classes that wraps the SDL_GetError-message
        3. convenience functions for bool <--> SDL_BOOL translation
*/
namespace SDLex {
inline constexpr SDL_bool fromBool(bool b) noexcept {
  return b ? SDL_TRUE : SDL_FALSE;
}
inline constexpr bool toBool(SDL_bool b) noexcept { return b == SDL_TRUE; }
inline constexpr bool toBool(int b) noexcept { return b != 0; }

struct SDL_Deleter {
  void operator()(SDL_Surface *ptr) const noexcept {
    if (ptr)
      SDL_FreeSurface(ptr);
  }
  void operator()(SDL_Texture *ptr) const noexcept {
    if (ptr)
      SDL_DestroyTexture(ptr);
  }
  void operator()(SDL_Renderer *ptr) const noexcept {
    if (ptr)
      SDL_DestroyRenderer(ptr);
  }
  void operator()(SDL_Window *ptr) const noexcept {
    if (ptr)
      SDL_DestroyWindow(ptr);
  }
  void operator()(SDL_RWops *ptr) const noexcept {
    if (ptr)
      SDL_RWclose(ptr);
  }
  void operator()(char *ptr) const noexcept {
    if (ptr)
      SDL_free(ptr);
  } // for paths
  // void operator()(TTF_Font*	  ptr) const noexcept{ if (ptr)
  // TTF_CloseFont(ptr); }
};
// unique pointers
using SurfacePtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
using TexturePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
using RWopsPtr = std::unique_ptr<SDL_RWops, SDL_Deleter>;
using CharPtr = std::unique_ptr<char, SDL_Deleter>;
// using FontPtr		= std::unique_ptr<TTF_Font,
// SDL_Deleter>;

template <class T, class D = SDL_Deleter>
std::shared_ptr<T> make_shared(T *t = nullptr) {
  return std::shared_ptr<T>(t, D());
}

}; // namespace SDLex

class SDLError : public std::runtime_error {
public:
  SDLError() noexcept(false) : std::runtime_error(SDL_GetError()){};
};

class SDLInitError : public SDLError {};