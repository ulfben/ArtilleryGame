#pragma once
#include <cassert>
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <iterator>
namespace Utils {
	using namespace std::literals::string_literals;
	template <typename Enum>
	static constexpr typename std::underlying_type<Enum>::type to_underlying(Enum e) noexcept {
		return static_cast<typename std::underlying_type<Enum>::type>(e);
	}

	template <typename T>
	static constexpr T clamp(T val, T min, T max) noexcept {
		return (val > max) ? max : (val < min) ? min : val;
	}	
	
	template <typename Coordinate>
	constexpr int32_t ceil(Coordinate num) noexcept {
		return (static_cast<Coordinate>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
	}

	constexpr size_t log2(size_t n) noexcept{
		return ((n < 2) ? 0 : 1 + log2(n / 2));
	}

	template<typename T>
	bool constexpr isPowerOfTwo(T x) noexcept {
		return (x != 0) && ((x & (x - 1)) == 0);
	}

	//courtesy of Graham Palmer, https://stackoverflow.com/a/53935759
	//This also allows you to specify a minimum power of 2 - i.e.upperPowerOfTwo(1, 3) return 8.
	template <typename T,
		typename = typename std::enable_if<std::is_integral<T>::value>::type>
		constexpr T nextPowerOfTwo(T value, size_t pow = 0) noexcept {		
		return (value >> pow) ? nextPowerOfTwo(value, pow + 1) : T(1) << pow;
	}

	template<typename T>
	constexpr inline bool isInRectangle(T x, T y, T left, T top, T right, T bottom) noexcept {
		return (x > left && x < right) && (y > top && y < bottom);
	}

	template <class Container>
	static void print(const Container& v, const std::string& sep = ", "s) {
		using T = typename Container::value_type;
		std::copy(std::begin(v), std::end(v), std::ostream_iterator<T>{std::cout, sep.c_str()});
	}

	constexpr inline float roundToNthDecimal(float value, int precision=1000) noexcept {
		assert(precision != 0);
		return (static_cast<float>(static_cast<int>(value * precision))) / precision;
	}

	// narrow_cast(): a searchable way to do narrowing casts of values
        template <class T, class U>
        constexpr T narrow_cast(U&& u) noexcept {
          return static_cast<T>(std::forward<U>(u));
        }
        }