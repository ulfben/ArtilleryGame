#pragma once
#include <cassert>
#include <cstdint>
#include <cmath>
#include <numeric>
using Real = float;
using Coordinate = Real;
using ColorChannel = uint8_t;
static constexpr auto FULL = std::numeric_limits<ColorChannel>::max();
static constexpr auto EMPTY = std::numeric_limits<ColorChannel>::min();
static constexpr auto ALPHA_OPAQUE = FULL;
static constexpr auto ALPHA_TRANSPARENT = EMPTY;

namespace internal {

template <typename T> constexpr Real normalize(T value) noexcept {
  return value < 0 ? -static_cast<Real>(value) / std::numeric_limits<T>::min()
                   : static_cast<Real>(value) / std::numeric_limits<T>::max();
}

constexpr ColorChannel toChannel(Real value) noexcept {  
  return (value < 0) ? EMPTY : (value > 1) ? FULL : value * FULL;
}
static_assert(toChannel(0.0f) == EMPTY, "");
static_assert(toChannel(1.0f) == FULL, "");
static_assert(toChannel(0.495f) == 126, "");
static_assert(toChannel(0.5f) == 127, "");
static_assert(toChannel(0.505f) == 128, "");

} // namespace internal

struct Position {
  Coordinate x = 0.0f;
  Coordinate y = 0.0f;
};
struct Rect {
  Coordinate x = 0.0f;
  Coordinate y = 0.0f;
  Real width = 0.0f;
  Real height = 0.0f;
};
struct Color {
  ColorChannel r = EMPTY;
  ColorChannel g = EMPTY;
  ColorChannel b = EMPTY;
  ColorChannel a = ALPHA_OPAQUE;

  constexpr void update(ColorChannel r_, ColorChannel g_,
                        ColorChannel b_) noexcept {
    r = r_;
    g = g_;
    b = b_;
  }

  constexpr void update(ColorChannel r_, ColorChannel g_, ColorChannel b_,
                        ColorChannel a_) noexcept {
    r = r_;
    g = g_;
    b = b_;
    a = a_;
  }

  constexpr Color correct_gamma(Real g) const noexcept {
    using internal::normalize;
    const auto rf = std::pow(normalize(r), g);
    const auto gf = std::pow(normalize(g), g);
    const auto bf = std::pow(normalize(b), g);
    const auto af = std::pow(normalize(a), g);   
    //pygame rounds with +.5, whereas I don't
    // pygame: rf * 255+0.5f    
    //todo: test the observable(?) difference
    return fromFloats(rf, gf, bf, af);
  }

  static constexpr Real lerp(Real from, Real target, Real amount) noexcept {
    return from * (1 - amount) + target * amount;
  }

  #define pg_round(d) (((d < 0) ? (ceil((d)-0.5)) : (floor((d) + 0.5))))
  constexpr Color lerp(Color target, Real amount) const noexcept {
    assert(amount >= 0.0f && amount <= 1.0f && "Argument 2 must be in the range [0, 1]");
    const ColorChannel rn = pg_round(lerp(r, target.r, amount));
    const ColorChannel gn = pg_round(lerp(g, target.g, amount));
    const ColorChannel bn = pg_round(lerp(b, target.b, amount));
    const ColorChannel an = pg_round(lerp(a, target.a, amount));
    return Color{rn, gn, bn, an};
    //TODO: use fromFloats, and test that lerp is rounding correctly. 
  }

  constexpr Color normalize() const noexcept {
    const Real sum = r + g + b + a;
    const auto rf = internal::normalize(r);
    const auto gf = internal::normalize(g);
    const auto bf = internal::normalize(b);
    const auto af = internal::normalize(a);
    return Color::fromFloats(rf / sum, gf / sum, bf / sum, af / sum);
  }
  static_assert(internal::normalize(ColorChannel(ALPHA_OPAQUE)) == 1.0f, "");
  static_assert(internal::normalize(ColorChannel(0)) == 0.0f, "");
  static_assert(internal::normalize(ColorChannel(127)) > 0.49f && internal::normalize(ColorChannel(128)) < 0.51f, "");

  constexpr Color premul_alpha() const noexcept {
    // https://github.com/pygame/pygame/blob/ca61671459d2acbba3b5e24deb15f84852d414de/src_c/color.c#L863
    constexpr auto premul =
        [](ColorChannel value,
           ColorChannel multiplier) noexcept -> ColorChannel {
      // return (value * multiplier) / FULL; //safe, but slow.
      return ((value + 1) * multiplier) >> 8; //assumes ColorChannel::max() == 255, but is faster.
        //I should add compile time selection of the algo.
    };
    return Color{premul(r, a), premul(g, a), premul(b, a), a};
  }
  static constexpr ColorChannel red = FULL;
  static constexpr ColorChannel alpha = FULL;
  static constexpr ColorChannel pygame_blend = (((red + 1) * alpha) >> 8);
  static constexpr ColorChannel my_blend = (red * alpha) / FULL;
  static_assert(pygame_blend == my_blend, "You're mathing wrong.");

  static constexpr Color fromFloats(Real r, Real g, Real b, Real a) noexcept {
    using internal::toChannel;
    return Color{toChannel(r), toChannel(g), toChannel(b), toChannel(a)};
  };
};
