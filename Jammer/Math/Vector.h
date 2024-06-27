#ifndef JAMMER_MATH_VECTOR_H
#define JAMMER_MATH_VECTOR_H

#include "Math/Math.h"

namespace Jammer{
	struct Vector2{
		float x;
		float y;

		explicit constexpr Vector2(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_){}

		static inline constexpr Vector2 Zero(){ return Vector2(0.0f, 0.0f); }
		static inline constexpr Vector2 Fill(float v_){ return Vector2(v_, v_); }

		inline constexpr Vector2 operator -() const{ return Vector2(-x, -y); }
		inline constexpr Vector2 operator +(const Vector2& v_) const{ return Vector2(x + v_.x, y + v_.y); }
		inline constexpr Vector2 operator -(const Vector2& v_) const{ return Vector2(x - v_.x, y - v_.y); }
		inline constexpr Vector2 operator *(float s_) const{ return Vector2(x * s_, y * s_); }

		inline constexpr Vector2 operator /(float s_) const{ return Vector2(Math::SafeDivide(x, s_), Math::SafeDivide(y, s_)); }

		inline friend constexpr Vector2 operator *(float s_, const Vector2& v_){ return v_ * s_; }

		inline constexpr void operator +=(const Vector2& v_){ *this = *this + v_; }
		inline constexpr void operator -=(const Vector2& v_){ *this = *this - v_; }
		inline constexpr void operator *=(float s_){ *this = *this * s_; }
		inline constexpr void operator /=(float s_){ *this = *this / s_; }

		inline constexpr float SquaredMagnitude() const{ return (x * x) + (y * y); }
		inline float Magnitude() const{ return Math::Sqrt(SquaredMagnitude()); }
		inline Vector2 Normalized() const{ return *this / Magnitude(); }
		inline void Normalize(){ *this = Normalized(); }
		static inline constexpr float Dot(const Vector2& a_, const Vector2& b_){ return (a_.x * b_.x) + (a_.y * b_.y); }
		static inline constexpr Vector2 Hadamard(const Vector2& a_, const Vector2& b_){ return Vector2(a_.x * b_.x, a_.y * b_.y); }

		//These allow us to pass this as an array to legacy code or things like OpenGL very easily
		inline constexpr operator const float* () const{ return static_cast<const float*>(&x); }
		inline constexpr operator float* (){ return static_cast<float*>(&x); }
	};
}

#endif //!JAMMER_MATH_VECTOR_H