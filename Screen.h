#pragma once
#include "Surface.h"
class Screen {
  Surface _surface;
	//surface
public:
  void clear() const noexcept {
	  //_surface.clear
  }
    void fill(/*(red, green, blue)*/) const noexcept {}
  void blit(/*image, (left, top)*/) const noexcept {}

  void draw_line(/*start, end, (r, g, b)*/) const noexcept {}
  void draw_circle(/*pos, radius, (r, g, b)*/) const noexcept {}
  void draw_filled_circle(/*pos, radius, (r, g, b)*/) const noexcept {}
  void draw_rect(/*rect, (r, g, b)*/) const noexcept {}
  void draw_filled_rect(/*rect, (r, g, b)*/) const noexcept {}
  void draw_text(/*text, [pos, ]**kwargs*/) const noexcept {}
  void draw_textbox(/*text, rect, **kwargs*/) const noexcept {}

};