#include "Texture.h"
#include "Surface.h"
#include "Renderer.h"
#include "SDL_stbimage.h"
Texture::Texture() : _ptr(nullptr)
{}
Texture::Texture(SDL_Texture* t) {
	if (t == nullptr) {
		throw SDLError();
	}
	_ptr.reset(t);	
}
Texture::Texture(const Renderer& r, Surface& s) :
	Texture(SDL_CreateTextureFromSurface(r.getRawPtr(), s.getRawPtr()))
{}
Texture::Texture(const Renderer& r, Surface& s, int access) :
	Texture(SDL_CreateTexture(r.getRawPtr(), s.getRawPtr()->format->format, access, s.getRawPtr()->w, s.getRawPtr()->h))
{}
Texture::Texture(const Renderer& r, SDL_Surface* s):
	Texture(SDL_CreateTextureFromSurface(r.getRawPtr(), s))
{}
Texture::Texture(const Renderer& r, const std::string_view imgFile) :
	Texture(STBIMG_LoadTexture(r.getRawPtr(), imgFile.data()))
{}
Texture::Texture(const Renderer& r, const unsigned char* buffer, int length) :
	Texture(STBIMG_LoadTextureFromMemory(r.getRawPtr(), buffer, length))
{}
Texture::Texture(const Renderer& r, Uint32 format, int access, int w, int h) :
	Texture(SDL_CreateTexture(r.getRawPtr(), format, access, w, h))
{}

SDL_Texture* Texture::getRawPtr() const noexcept {
	SDL_assert(_ptr != nullptr);
	return _ptr.get();
}

void Texture::setTextureAlphaMod(Uint8 alpha) const noexcept {
	int res = SDL_SetTextureAlphaMod(_ptr.get(), alpha);
	SDL_assert(res == 0);
}
void Texture::setTextureBlendMode(SDL_BlendMode blendMode) const noexcept {
	int res = SDL_SetTextureBlendMode(_ptr.get(), blendMode);
	SDL_assert(res == 0);
}
void Texture::setTextureColorMod(Uint8 r, Uint8 g, Uint8 b) const noexcept {
	int res = SDL_SetTextureColorMod(_ptr.get(), r, g, b);
	SDL_assert(res == 0);
}
void Texture::setTextureColorMod(const SDL_Color& c) const noexcept {
	setTextureColorMod(c.r, c.g, c.b);
}
SDL_BlendMode Texture::getTextureBlendMode() const noexcept {
	SDL_BlendMode blendMode;
	int res = SDL_GetTextureBlendMode(_ptr.get(), &blendMode);
	SDL_assert(res == 0);
	return blendMode;
}
void Texture::getTextureAlphaMod(Uint8& alpha) const noexcept {
	int res = SDL_GetTextureAlphaMod(_ptr.get(), &alpha);
	SDL_assert(res == 0);
}
void Texture::getTextureColorMod(Uint8& r, Uint8& g, Uint8& b) const noexcept {
	int res = SDL_GetTextureColorMod(_ptr.get(), &r, &g, &b);
	SDL_assert(res == 0);
}
void Texture::getTextureColorMod(SDL_Color& c) const noexcept {
	getTextureColorMod(c.r, c.g, c.b);
}

void Texture::unlock() const noexcept {
	SDL_UnlockTexture(_ptr.get());
}
void Texture::updateTexture(const SDL_Rect* rect, const void* pixels, int pitch)const noexcept {
	int res = SDL_UpdateTexture(_ptr.get(), rect, pixels, pitch);
	SDL_assert(res == 0);
}
void Texture::updateTexture(const SDL_Rect* rect, const Surface& surface) const noexcept {
	SDL_Surface* s = surface.getRawPtr();	
	int res = SDL_UpdateTexture(_ptr.get(), rect, s->pixels, s->pitch);
	SDL_assert(res == 0);
}
void Texture::updateTexture(const Surface& surface) const noexcept {
	SDL_Surface* s = surface.getRawPtr();
	int res = SDL_UpdateTexture(_ptr.get(), NULL, s->pixels, s->pitch);
	SDL_assert(res == 0);
}
void Texture::lockTexture(const SDL_Rect* rect, void** pixels, int* pitch) const noexcept {
	int res = SDL_LockTexture(_ptr.get(), rect, pixels, pitch);
	SDL_assert(res == 0);
}
void Texture::queryTexture(Uint32& format, int& access, int& w, int& h) const noexcept {
	int res = SDL_QueryTexture(_ptr.get(), &format, &access, &w, &h);
	SDL_assert(res == 0);
}