//based on Cheinan Marks talk at CPPCon2016: https://www.youtube.com/watch?v=4_QO1nm7uJs
#pragma once
#include <random>
class Random {
	static std::mt19937& rng() {
		static std::mt19937 u{};
		return u;
	}
public:		
	static void randomize() {
		static std::random_device rd{};
		rng().seed(rd());
	}	
	static unsigned char color() {//0-255 inclusive 
		static std::uniform_int_distribution<> dist{0, 255};		
		return static_cast<unsigned char>(dist(rng())); 
	}	
	static int getInt(int from, int thru) {//[from,trhu] (inclusive)
		static std::uniform_int_distribution<int> dist{};
		using parm_t = decltype(dist)::param_type;
		return dist(rng(), parm_t{ from, thru });
	}
	static float getFloat(float from = 0.0f, float upto = 1.0f) {// [from, upto) (exclusive)
		static std::uniform_real_distribution<float> dist{};
		using parm_t = decltype(dist)::param_type;
		return dist(rng(), parm_t{ from, upto });
	}
	static double getDouble(double from = 0.0, double upto = 1.0) {// [from, upto) (exclusive)
		static std::uniform_real_distribution<double> dist{};
		using parm_t = decltype(dist)::param_type;
		return dist(rng(), parm_t{ from, upto });
	}
	template<class T>
	static T getNumber(T min, T max) {
		static std::uniform_int_distribution<T> dist{};
		using parm_t = decltype(dist)::param_type;
		return dist(rng(), parm_t{ min, max });
	};
	static float getNumber(float from, float upto) {// [from, upto) (exclusive)
		return getFloat(from, upto);
	}
	static double getNumber(double from, double upto) {// [from, upto) (exclusive)
		return getDouble(from, upto);
	}
};