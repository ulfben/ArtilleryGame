#pragma once
#include "SDLex.h"
#include "vector"
struct SDL_Renderer;
struct SDL_Color;
struct SDL_Rect;
class Window;
class Texture;
class Renderer {		
	SDLex::RendererPtr _ptr;
	Renderer(const Renderer&) = delete; //disable copy constructor
	Renderer& operator=(Renderer&) = delete; //disable copy assignment
public:
	Renderer(const Window& w);	
	void clear() const noexcept;
	inline SDL_Renderer* getRawPtr() const noexcept;
	void setLogicalSize(int w, int h) const noexcept;
	void setColor(const SDL_Color& c) const noexcept;
	void present() const noexcept;
	void drawLine(int x1, int y1, int x2, int y2) const noexcept;
	void drawPoint(int x, int y) const noexcept;
	void drawRect(const SDL_Rect& r) const noexcept;
	void drawFilledRect(const SDL_Rect& rect) const noexcept;
	bool isClipEnabled() const noexcept; 
	void drawTexture(Texture& texture, const SDL_Rect* srcrect = nullptr, const SDL_Rect* dstrect = nullptr) const noexcept;
	void drawTextureEx(Texture& texture, const SDL_Rect* srcrect = nullptr, const SDL_Rect* dstrect = nullptr, const float angle = 0.0f, const SDL_Point* center = nullptr, const SDL_RendererFlip flip = SDL_FLIP_NONE) const noexcept;
	
	void drawLines(const std::vector<SDL_Point>& points) const noexcept;
	void drawPoints(const std::vector<SDL_Point>& points) const noexcept;
	void drawRects(const std::vector<SDL_Rect>& rects) const noexcept;
	void drawFilledRects(const std::vector<SDL_Rect>& rects) const noexcept;
		
private:
	void drawLines(const SDL_Point* points, size_t count) const noexcept;
	void drawPoints(const SDL_Point* points, size_t count) const noexcept;
	void drawRects(const SDL_Rect* rects, size_t count) const noexcept;
	void drawFilledRects(const SDL_Rect* rects, size_t count) const noexcept;
};