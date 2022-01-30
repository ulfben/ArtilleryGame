#include "Texture.h"
#include "Surface.h"
#include "Renderer.h"
#include "SDL_stbimage.h"

Texture::Texture(SDL_Texture* t) {
	if (t == nullptr) {
		throw SDLError();
	}
	_ptr.reset(t);	
}
Texture::Texture(const Renderer& r, Surface& s) :
	Texture(SDL_CreateTextureFromSurface(r.getPtr(), s.getPtr()))
{}
Texture::Texture(const Renderer& r, Surface& s, int access) :
	Texture(SDL_CreateTexture(r.getPtr(), s.getPtr()->format->format, access, s.getPtr()->w, s.getPtr()->h))
{}
Texture::Texture(const Renderer& r, SDL_Surface* s):
	Texture(SDL_CreateTextureFromSurface(r.getPtr(), s))
{}
Texture::Texture(const Renderer& r, const std::string_view imgFile) :
	Texture(STBIMG_LoadTexture(r.getPtr(), imgFile.data()))
{}
Texture::Texture(const Renderer& r, const unsigned char* buffer, int length) :
	Texture(STBIMG_LoadTextureFromMemory(r.getPtr(), buffer, length))
{}
Texture::Texture(const Renderer& r, Uint32 format, int access, int w, int h) :
	Texture(SDL_CreateTexture(r.getPtr(), format, access, w, h))
{}

SDL_Texture* Texture::getPtr() const noexcept {
	assert(_ptr != nullptr);
	return _ptr.get();
}

void Texture::setTextureAlphaMod(Uint8 alpha) const noexcept {
	const int res = SDL_SetTextureAlphaMod(_ptr.get(), alpha);
	assert(res == 0);
}
void Texture::setTextureBlendMode(SDL_BlendMode blendMode) const noexcept {
	const int res = SDL_SetTextureBlendMode(_ptr.get(), blendMode);
	assert(res == 0);
}
void Texture::setTextureColorMod(Uint8 r, Uint8 g, Uint8 b) const noexcept {
	const int res = SDL_SetTextureColorMod(_ptr.get(), r, g, b);
	assert(res == 0);
}
void Texture::setTextureColorMod(const SDL_Color& c) const noexcept {
	setTextureColorMod(c.r, c.g, c.b);
}
SDL_BlendMode Texture::getTextureBlendMode() const noexcept {
	SDL_BlendMode blendMode;
	const int res = SDL_GetTextureBlendMode(_ptr.get(), &blendMode);
	assert(res == 0);
	return blendMode;
}
void Texture::getTextureAlphaMod(Uint8& alpha) const noexcept {
	const int res = SDL_GetTextureAlphaMod(_ptr.get(), &alpha);
	assert(res == 0);
}
void Texture::getTextureColorMod(Uint8& r, Uint8& g, Uint8& b) const noexcept {
	const int res = SDL_GetTextureColorMod(_ptr.get(), &r, &g, &b);
	assert(res == 0);
}
void Texture::getTextureColorMod(SDL_Color& c) const noexcept {
	getTextureColorMod(c.r, c.g, c.b);
}

void Texture::unlock() const noexcept {
	SDL_UnlockTexture(_ptr.get());
}
void Texture::updateTexture(const SDL_Rect* rect, const void* pixels, int pitch)const noexcept {
	const int res = SDL_UpdateTexture(_ptr.get(), rect, pixels, pitch);
	assert(res == 0);
}
void Texture::updateTexture(const SDL_Rect* rect, const Surface& surface) const noexcept {	
	const int res = SDL_UpdateTexture(_ptr.get(), rect, surface.pixels(), surface.pitch());
	assert(res == 0);
}
void Texture::updateTexture(const Surface& surface) const noexcept {	
	const int res = SDL_UpdateTexture(_ptr.get(), nullptr, surface.pixels(), surface.pitch());
	assert(res == 0);
}
void Texture::lockTexture(const SDL_Rect* rect, void** pixels, int* pitch) const noexcept {
	const int res = SDL_LockTexture(_ptr.get(), rect, pixels, pitch);
	assert(res == 0);
}
void Texture::queryTexture(Uint32& format, int& access, int& w, int& h) const noexcept {
	const int res = SDL_QueryTexture(_ptr.get(), &format, &access, &w, &h);
	assert(res == 0);
}