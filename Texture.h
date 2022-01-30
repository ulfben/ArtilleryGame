#pragma once
#include "SDLex.h"
class Renderer;
class Surface;
class Texture
{
	SDLex::TexturePtr _ptr = nullptr;
public:		
	explicit Texture(SDL_Texture* t) ;
	Texture(const Renderer& r, Surface& s);
	Texture(const Renderer& r, Surface& s, int access); //= SDL_TEXTUREACCESS_STATIC, SDL_TEXTUREACCESS_STREAMING
	Texture(const Renderer& r, SDL_Surface* s);
	Texture(const Renderer& r, std::string_view imgFile);
	//Texture(const Renderer& r, const std::string& imgFile);
	Texture(const Renderer& r, const unsigned char* buffer, int length);
	Texture(const Renderer& r, Uint32 format, int access, int w, int h);		
	
	SDL_Texture* getPtr() const noexcept;
		
	void setTextureAlphaMod(Uint8 alpha) const noexcept;
	void setTextureBlendMode(SDL_BlendMode blendMode) const noexcept;
	void setTextureColorMod(const SDL_Color& c) const noexcept;
	void setTextureColorMod(Uint8 r, Uint8 g, Uint8 b) const noexcept;
	SDL_BlendMode getTextureBlendMode() const noexcept;
	void getTextureAlphaMod(Uint8& alpha) const noexcept;	
	void getTextureColorMod(SDL_Color& c) const noexcept;
	void getTextureColorMod(Uint8& r, Uint8& g, Uint8& b) const noexcept;

	void unlock() const noexcept;
	void updateTexture(const SDL_Rect* rect, const void* pixels, int pitch) const noexcept;
	void updateTexture(const SDL_Rect* rect, const Surface& surface) const noexcept;
	void updateTexture(const Surface& surface) const noexcept;
	void lockTexture(const SDL_Rect* rect, void** pixels, int* pitch) const noexcept;
	void queryTexture(Uint32& format, int& access, int& w, int& h) const noexcept;
};

