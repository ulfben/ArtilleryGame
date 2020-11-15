#include "Renderer.h"
#include "SDLSystem.h"
#include "Window.h"
#include "Texture.h"
#include <stdexcept>
#include <vector>
Renderer::Renderer(const Window& w): 
	_ptr{ SDL_CreateRenderer(w.getRawPtr(), -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC)}{
	if (!_ptr) {		
		throw SDLError();
	}
}
SDL_Renderer* Renderer::getRawPtr() const noexcept {
	SDL_assert(_ptr != nullptr && "Renderer: invalid pointer. Use after delete?");
	return _ptr.get();
}
void Renderer::setLogicalSize(int w, int h) const noexcept {
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(getRawPtr(), w, h);
}

void Renderer::clear() const noexcept {
	int res = SDL_RenderClear(_ptr.get());
	SDL_assert(res == 0);
}
void Renderer::setColor(const SDL_Color& c) const noexcept {
	int res = SDL_SetRenderDrawColor(_ptr.get(), c.r, c.g, c.b, c.a);
	SDL_assert(res == 0);
}
void Renderer::present() const noexcept {
	SDL_RenderPresent(_ptr.get());
}
void Renderer::drawLine(int x1, int y1, int x2, int y2) const noexcept {
	int res = SDL_RenderDrawLine(_ptr.get(), x1, y1, x2, y2);
	SDL_assert(res == 0);
}
void Renderer::drawPoint(int x, int y) const  noexcept {
	int res = SDL_RenderDrawPoint(_ptr.get(), x, y);
	SDL_assert(res == 0);
}
void Renderer::drawRect(const SDL_Rect& rect) const noexcept {
	int res = SDL_RenderDrawRect(_ptr.get(), &rect);
	SDL_assert(res == 0);
}
void Renderer::drawFilledRect(const SDL_Rect& rect) const noexcept {
	int res = SDL_RenderFillRect(_ptr.get(), &rect);
	SDL_assert(res == 0);
}
bool Renderer::isClipEnabled() const noexcept {
	return SDL_RenderIsClipEnabled(_ptr.get()) == SDL_TRUE;
}

void Renderer::drawTexture(Texture& texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) const noexcept {
	int res = SDL_RenderCopy(_ptr.get(), texture.getRawPtr(), srcrect, dstrect);
	SDL_assert(res == 0);
}
void Renderer::drawTextureEx(Texture& texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const float angle, const SDL_Point* center, const SDL_RendererFlip flip) const noexcept {
	int res = SDL_RenderCopyEx(_ptr.get(), texture.getRawPtr(), srcrect, dstrect, angle, center, flip);
	SDL_assert(res == 0);
}

void Renderer::drawLines(const std::vector<SDL_Point>& points) const noexcept {
	SDL_assert(!points.empty());
	drawLines(&points[0], points.size());
}
void Renderer::drawPoints(const std::vector<SDL_Point>& points) const noexcept {
	SDL_assert(!points.empty());
	drawLines(&points[0], points.size());
}
void Renderer::drawRects(const std::vector<SDL_Rect>& rects) const noexcept {
	SDL_assert(!rects.empty());
	drawRects(&rects[0], rects.size());
}
void Renderer::drawFilledRects(const std::vector<SDL_Rect>& rects) const noexcept{
	SDL_assert(!rects.empty());
	drawRects(&rects[0], rects.size());
}
void Renderer::drawLines(const SDL_Point* points, size_t count) const noexcept {
	int res = SDL_RenderDrawLines(_ptr.get(), points, static_cast<int>(count));
	SDL_assert(res == 0);
}
void Renderer::drawPoints(const SDL_Point* points, size_t count) const noexcept {
	int res = SDL_RenderDrawPoints(_ptr.get(), points, static_cast<int>(count));
	SDL_assert(res == 0);
}
void Renderer::drawRects(const SDL_Rect* rects, size_t count) const noexcept {
	int res = SDL_RenderDrawRects(_ptr.get(), rects, static_cast<int>(count));
	SDL_assert(res == 0);
}
void Renderer::drawFilledRects(const SDL_Rect* rects, size_t count) const noexcept {
	int res = SDL_RenderFillRects(_ptr.get(), rects, static_cast<int>(count));
	SDL_assert(res == 0);
}