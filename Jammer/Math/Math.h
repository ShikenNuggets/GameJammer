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

		static inline constexpr int32_t Round(double num_){
			if(num_ < 0.0){
				return static_cast<int32_t>(num_ - 0.5);
			}

			return static_cast<int32_t>(num_ + 0.5);
		}

		static inline constexpr bool IsPrime(uint64_t num_){
			if(num_ <= 1){
				return false;
			}

			double sqrtNum = sqrt(num_);
			for(uint64_t i = 2; i < sqrtNum; i++){
				if(num_ % i == 0){
					return false;
				}
			}

			return true;
		}

		static inline constexpr uint64_t NextPrime(uint64_t start_){
			for(uint64_t i = start_ + 1; i < std::numeric_limits<uint64_t>::max(); i++){
				if(IsPrime(i)){
					return i;
				}
			}

			return 0;
		}
	}
}

#endif //!JAMMER_MATH_MATH_H