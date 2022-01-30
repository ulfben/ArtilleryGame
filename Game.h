#pragma once

class Game {
public:
  void update() noexcept {
    read_inputs();
    do_update();
  }
  void draw() const noexcept { do_draw(); }
  virtual ~Game() noexcept {}

private:
  void read_inputs() noexcept {

  };
  virtual void do_update() noexcept = 0;
  virtual void do_draw() const noexcept = 0;
};