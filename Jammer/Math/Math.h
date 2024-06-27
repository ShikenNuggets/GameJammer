#ifndef JAMMER_MATH_MATH_H
#define JAMMER_MATH_MATH_H

#include <cmath>
#include <limits>

#include "Debug.h"

namespace Jammer{
	namespace Math{
		static constexpr float NearZero = std::numeric_limits<float>::denorm_min();

		static inline float Sqrt(float value_){
			return static_cast<float>(sqrt(value_));
		}

		static inline constexpr bool IsNearZero(float s_){ return s_ <= NearZero && s_ >= -NearZero; }

		static inline constexpr float SafeDivide(float a_, float b_){
			if(Math::IsNearZero(b_)){
				JLOG_WARNING("Attempted to divide by 0");
				return 0.0f;
			}

			return a_ / b_;
		}

		template <class T>
		static inline constexpr T Clamp(T value_, T min_ = 0, T max_ = 0){
			if(value_ < min_){
				return min_;
			}else if(value_ > max_){
				return max_;
			}

			return value_;
		}
	}
}

#endif //!JAMMER_MATH_MATH_H