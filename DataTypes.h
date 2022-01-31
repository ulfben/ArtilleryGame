#pragma once
#include <cassert>
#include <cmath>
#include <cstdint>
#include <numeric>
using Real = float;
using Coordinate = Real;
using ColorChannel = uint8_t;

static constexpr auto FULL = std::numeric_limits<ColorChannel>::max();
static constexpr auto EMPTY = std::numeric_limits<ColorChannel>::min();
static constexpr auto ALPHA_OPAQUE = FULL;
static constexpr auto ALPHA_TRANSPARENT = EMPTY;

struct NormalizedColor {
  Real r = 0;
  Real g = 0;
  Real b = 0;
  Real a = 0;
};

struct Position {
  Coordinate x = 0.0f;
  Coordinate y = 0.0f;
};
struct Rect {
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
  int left() const noexcept { return x; }
  int top() const noexcept { return y; }
  int right() const noexcept { return x + width; }
  int bottom() const noexcept { return y + height; }
};

template <class T, class U> constexpr T narrow_cast(U &&u) noexcept {
  return static_cast<T>(std::forward<U>(u));
}

static constexpr bool isBetween(auto in, auto min, auto max) noexcept {
  return min <= in && max >= in;
}
static constexpr bool isInside(Position pos, Rect bounds) noexcept {
  return isBetween(pos.x, bounds.left(), bounds.right()) &&
         isBetween(pos.y, bounds.top(), bounds.bottom());
}

static constexpr Real lerp(Real from, Real target, Real amount) noexcept {
  return from * (1.0f - amount) + target * amount;
}

namespace internal {

template <typename T> constexpr Real normalize(T value) noexcept {
  return value < 0 ? -static_cast<Real>(value) / std::numeric_limits<T>::min()
                   : static_cast<Real>(value) / std::numeric_limits<T>::max();
}
static_assert(internal::normalize(ColorChannel(ALPHA_OPAQUE)) == 1.0f, "");
static_assert(internal::normalize(ColorChannel(0)) == 0.0f, "");
static_assert(internal::normalize(ColorChannel(127)) > 0.49f &&
                  internal::normalize(ColorChannel(128)) < 0.51f,
              "");

constexpr ColorChannel normalizedToChannel(Real value) noexcept {
  return (value < 0)   ? EMPTY
         : (value > 1) ? FULL
                       : narrow_cast<ColorChannel>(value * FULL);
}
static_assert(normalizedToChannel(0.0f) == EMPTY, "");
static_assert(normalizedToChannel(1.0f) == FULL, "");
static_assert(normalizedToChannel(0.495f) == 126, "");
static_assert(normalizedToChannel(0.5f) == 127, "");
static_assert(normalizedToChannel(0.505f) == 128, "");

constexpr ColorChannel denormalizedToChannel(Real value) noexcept {
  const auto MIN = static_cast<Real>(EMPTY);
  const auto MAX = static_cast<Real>(FULL);
  return narrow_cast<ColorChannel>(std::clamp(value, MIN, MAX));
}
static_assert(denormalizedToChannel(0.0f) == EMPTY, "");
static_assert(denormalizedToChannel(0.8f) == EMPTY, "");
static_assert(denormalizedToChannel(-10.0f) == EMPTY, "");
static_assert(denormalizedToChannel(FULL + 10) == FULL, "");
static_assert(denormalizedToChannel(100.0f) == 100, "");
static_assert(denormalizedToChannel(127.0f) == 127, "");

} // namespace internal



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

  constexpr void update(Color that) noexcept {
    *this = that;    
  }

  Color correct_gamma(Real g) const noexcept { // TODO: needs constexpr pow
    using internal::normalize;
    // rounding like pygame    
    // https://github.com/pygame/pygame/blob/ca61671459d2acbba3b5e24deb15f84852d414de/src_c/color.c#L808
    static constexpr auto round = [](Real value) noexcept -> ColorChannel {
      return (value > 1)   ? FULL
             : (value < 0) ? EMPTY
                           : narrow_cast<ColorChannel>(value * FULL + .5f);
    };
    const auto rf = std::pow(normalize(r), g);
    const auto gf = std::pow(normalize(g), g);
    const auto bf = std::pow(normalize(b), g);
    const auto af = std::pow(normalize(a), g);
    return Color{round(rf), round(gf), round(bf), round(af)};
  }

  constexpr Color lerp(Color target, Real amount) const noexcept {
    assert(amount >= 0.0f && amount <= 1.0f &&
           "Argument 2 must be in the range [0, 1]");
    // pg_round:
    // https://github.com/pygame/pygame/blob/ca61671459d2acbba3b5e24deb15f84852d414de/src_c/color.c#L50
    constexpr auto pg_round = [](Real value) noexcept {
      return (value < 0.0f) ? std::ceil(value - 0.5f)
                            : std::floor(value + 0.5f);
    };
    const auto rn = pg_round(::lerp(r, target.r, amount));
    const auto gn = pg_round(::lerp(g, target.g, amount));
    const auto bn = pg_round(::lerp(b, target.b, amount));
    const auto an = pg_round(::lerp(a, target.a, amount));
    return fromDenormalized(rn, gn, bn, an);
  }

  constexpr NormalizedColor normalize() const noexcept {    
    const auto rf = internal::normalize(r);
    const auto gf = internal::normalize(g);
    const auto bf = internal::normalize(b);
    const auto af = internal::normalize(a);
    return NormalizedColor(rf, gf, bf, af);   
  }

  constexpr Color premul_alpha() const noexcept {
    // https://github.com/pygame/pygame/blob/ca61671459d2acbba3b5e24deb15f84852d414de/src_c/color.c#L863    
      constexpr auto premul =
        [](ColorChannel value,
           ColorChannel multiplier) noexcept -> ColorChannel {
            if constexpr (FULL == 255u) {
                return ((value + 1) * multiplier) >> 8;
            }
            return (value * multiplier) / FULL;
    };
    return Color{premul(r, a), premul(g, a), premul(b, a), a};
  }
  static constexpr ColorChannel red = FULL;
  static constexpr ColorChannel alpha = FULL;
  static constexpr ColorChannel pygame_blend = (((red + 1) * alpha) >> 8);
  static constexpr ColorChannel my_blend = (red * alpha) / FULL;
  static_assert(pygame_blend == my_blend, "You're mathing wrong.");

  static constexpr Color fromNormalized(Real r, Real g, Real b,
                                        Real a) noexcept {
    using internal::normalizedToChannel;
    assert(isBetween(r, 0, 1) && "fromNormalized: red channel out of range."
                                 "Valid range is [0, 1]");
    assert(isBetween(g, 0, 1) && "fromNormalized: green channel out of range."
                                 "Valid range is [0, 1]");
    assert(isBetween(b, 0, 1) && "fromNormalized: blue channel out of range."
                                 "Valid range is [0, 1]");
    assert(isBetween(a, 0, 1) && "fromNormalized: alpha channel out of range."
                                 "Valid range is [0, 1]");
    return Color{normalizedToChannel(r), normalizedToChannel(g),
                 normalizedToChannel(b), normalizedToChannel(a)};
  };

  static constexpr Color fromDenormalized(Real r, Real g, Real b,
                                          Real a) noexcept {
    using internal::denormalizedToChannel;
    return Color{denormalizedToChannel(r), denormalizedToChannel(g),
                 denormalizedToChannel(b), denormalizedToChannel(a)};
  };
};
