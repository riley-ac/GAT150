#pragma once
#include "Math.h"
#include <cassert>

namespace viper {
	template<typename T>
	struct Vector3
	{
		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vector3() = default;
		Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		T  operator [] (unsigned int index) const { assert(index < 3); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 3); return (&x)[index]; }

		Vector3 operator + (const Vector3& v) const { return Vector3{ x + v.x, y + v.y, z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ x - v.x, y - v.y, z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ x * v.x, y * v.y, z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ x / v.x, y / v.y, z / v.z }; }

		Vector3 operator + (float s) const { return Vector3{ x + s, y + s, z + s };	}
		Vector3 operator - (float s) const { return Vector3{ x - s, y - s, z - s }; }
		Vector3 operator * (float s) const { return Vector3{ x * s, y * s, z * s }; }
		Vector3 operator / (float s) const { return Vector3{ x / s, y / s, z / s }; }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		Vector3& operator += (float s) { x += s; y += s; z += s; return *this; }
		Vector3& operator -= (float s) { x -= s; y -= s; z -= s; return *this; }
		Vector3& operator *= (float s) { x *= s; y *= s; z *= s; return *this; }
		Vector3& operator /= (float s) { x /= s; y /= s; z /= s; return *this; }

		/// <summary>
		/// Calculates the squared length (magnitude) of a 3D vector.
		/// </summary>
		/// <returns>The sum of the squares of the x, y, and z components of the vector.</returns>
		float LengthSqr() const { return (x * x) + (y * y) + (z * z); }

		/// <summary>
		/// Calculates the length (magnitude) of the vector.
		/// </summary>
		/// <returns>The length of the vector as a floating-point value.</returns>
		float Length() const { return viper::math::sqrtf(LengthSqr()); }
	};

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}