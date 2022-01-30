#pragma once
#include "SDLex.h"
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	#define _rmask 0xff000000;
	#define _gmask 0x00ff0000;
	#define _bmask 0x0000ff00;
	#define _amask 0x000000ff;
#else
	#define _rmask 0x000000ff
	#define _gmask 0x0000ff00
	#define _bmask 0x00ff0000
	#define _amask 0xff000000
#endif
class Surface
{
	std::shared_ptr<SDL_Surface> _ptr;
public:
	Surface(SDL_Surface* ptr);
	Surface(std::string_view file);
	Surface(int width, int height, int depth=32, Uint32 Rmask= _rmask, Uint32 Gmask= _gmask, Uint32 Bmask= _bmask, Uint32 Amask= _amask);
	Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask = _rmask, Uint32 Gmask = _gmask, Uint32 Bmask = _bmask, Uint32 Amask = _amask);
	//Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 format=SDL_PIXELFORMAT_RGBA32); //TODO,  comes SDL with 2.0.5!
	//Surface(int width, int height, int depth=32, Uint32 format=SDL_PIXELFORMAT_RGBA32); //TODO,  comes SDL with 2.0.5!	
	
	
	bool mustLock() const noexcept;
	bool lock() const noexcept;
	void unlock() const noexcept;
	void blit(const Surface& src, const SDL_Rect* srcrect = NULL, SDL_Rect* dstrect = NULL) const noexcept;
	void blitScaled(const Surface& src, const SDL_Rect* srcrect = NULL, SDL_Rect* dstrect = NULL) const noexcept;
	void setBlendMode(SDL_BlendMode blendMode) const noexcept;
	SDL_BlendMode getBlendMode() const noexcept;
	void setColorKey(bool on, Uint32 key) const noexcept;
	bool getColorKey(Uint32& key) const noexcept;
	bool setClipRect(const SDL_Rect* rect) const noexcept;
	void fillRect(const SDL_Rect* rect, Uint32 color) const noexcept;
	void fillRects(const SDL_Rect* rects, int count, Uint32 color) const noexcept;
	void getClipRect(SDL_Rect& rect) const noexcept;
	Surface convertSurface(Uint32 pixel_format) const;
	Surface convertSurface(const SDL_PixelFormat* fmt) const;
	Surface clone() const;
	inline SDL_Surface* getPtr() const noexcept;
	int width() const noexcept;
	int height() const noexcept;
    void* pixels() const noexcept { return getPtr()->pixels; }
	int pitch() const noexcept { return getPtr()->pitch; }
};

