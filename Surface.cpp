#include "Surface.h"
#include "SDL_stbimage.h"
Surface::Surface(SDL_Surface* s){
	if (s == nullptr) {
		throw SDLError();
	}
	_ptr.reset(s);	
}

Surface::Surface(int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) :
	Surface(SDL_CreateRGBSurface(0, width, height, depth, Rmask, Gmask, Bmask, Amask))
{}
Surface::Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) :	
	Surface(SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask))
{}
Surface::Surface(const std::string& file):
	//Surface(SDL_LoadBMP_RW(SDL_RWFromFile(file.c_str(), "rb"), 1))
	Surface(STBIMG_Load(file.c_str()))	
{}
//Surface::Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 format) :  //TODO,  comes SDL with 2.0.5!
//	Surface(SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, format)) {}
//Surface::Surface(int width, int height, int depth, Uint32 format) :	Surface(SDL_CreateRGBSurfaceWithFormat(0, width, height, depth, format)){}
Surface::~Surface(){
}

SDL_Surface* Surface::getRawPtr() const noexcept {
	SDL_assert(_ptr != nullptr);
	return _ptr.get();
}

int Surface::width() const noexcept { return _ptr->w; }
int Surface::height() const noexcept { return _ptr->h; }
bool Surface::setClipRect(const SDL_Rect* rect) const noexcept {
	return SDLex::toBool(SDL_SetClipRect(_ptr.get(), rect));
}

void Surface::blit(const Surface& src, const SDL_Rect* srcrect, SDL_Rect* dstrect) const noexcept {
	int res = SDL_BlitSurface(src.getRawPtr(), srcrect, _ptr.get(), dstrect);
	SDL_assert(res == 0);
}
void Surface::blitScaled(const Surface& src, const SDL_Rect* srcrect, SDL_Rect* dstrect) const noexcept {
	int res = SDL_BlitScaled(src.getRawPtr(), srcrect, _ptr.get(), dstrect);
	SDL_assert(res == 0);
}
void Surface::setBlendMode(SDL_BlendMode blendMode) const noexcept {
	int res = SDL_SetSurfaceBlendMode(_ptr.get(), blendMode);
	SDL_assert(res == 0);
}
SDL_BlendMode Surface::getBlendMode() const noexcept {
	SDL_BlendMode blendMode;
	int res = SDL_GetSurfaceBlendMode(_ptr.get(), &blendMode);
	SDL_assert(res == 0);
	return blendMode;
}
void Surface::fillRect(const SDL_Rect* rect, Uint32 color) const noexcept {
	int res = SDL_FillRect(_ptr.get(), rect, color);
	SDL_assert(res == 0);
}
void Surface::fillRects(const SDL_Rect* rects, int count, Uint32 color) const noexcept {
	int res = SDL_FillRects(_ptr.get(), rects, count, color);
	SDL_assert(res == 0);
}
void Surface::getClipRect(SDL_Rect& rect) const noexcept {
	SDL_GetClipRect(_ptr.get(), &rect);	
}
void Surface::setColorKey(bool on, Uint32 key) const noexcept {
	int res = SDL_SetColorKey(_ptr.get(), SDLex::fromBool(on), key);
	SDL_assert(res == 0);
}
bool Surface::getColorKey(Uint32& key) const noexcept {	
	return SDL_GetColorKey(_ptr.get(), &key) == 0;
}
bool Surface::mustLock() const noexcept {
	return SDL_MUSTLOCK(_ptr.get());
}
bool Surface::lock() const noexcept {
	SDL_assert(mustLock() == true);
	return SDL_LockSurface(_ptr.get()) == 0;
}
void Surface::unlock() const noexcept {
	SDL_UnlockSurface(_ptr.get());
}
void Surface::convertSurface(Uint32 pixel_format) {
	SDL_Surface* newSurface = SDL_ConvertSurfaceFormat(_ptr.get(), pixel_format, 0);
	SDL_assert(newSurface != nullptr);
	if (newSurface) {
		_ptr.reset(newSurface);
	}
}
void Surface::convertSurface(const SDL_PixelFormat* fmt) {
	SDL_Surface* newSurface = SDL_ConvertSurface(_ptr.get(), fmt, 0);
	SDL_assert(newSurface != nullptr);
	if (newSurface) {
		_ptr.reset(newSurface);
	}
}
Surface Surface::clone() const noexcept {
	SDL_assert(_ptr != nullptr);
	SDL_Surface* original = _ptr.get();
	SDL_PixelFormat* fmt = original->format;
	return Surface(SDL_ConvertSurface(original, fmt, 0));
}