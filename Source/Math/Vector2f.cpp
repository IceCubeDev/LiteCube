/* Vector2f.h -- Contains the implementation of the Vector2f class
 *
 * Copyright (C) 2016 Ivan Dortulov (ivandortulov@yahoo.com)
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "..\..\Include\LiteCube\Math\Vector2f.h"
#include <cmath>

const float EPSILON = 0.0000001f;

namespace Lite
{
const Vector2f Vector2f::Zero;
const Vector2f Vector2f::One	( 1.0f, 1.0f);
const Vector2f Vector2f::Left	(-1.0f, 0.0f);
const Vector2f Vector2f::Right( 1.0f, 0.0f);
const Vector2f Vector2f::Up		( 0.0f, 1.0f);
const Vector2f Vector2f::Down	( 0.0 ,-1.0f);

/**
 * Default constructor.
 * Initializes the x and y coordinates to 0.
 */ 
Vector2f::Vector2f()
	: x(0)
	, y(0)
{
}


/**
 * Parametrized constructor.
 *
 * @param[in] x - x coordinate
 * @param[in] y - y coordinate
 */
Vector2f::Vector2f(float x, float y)
	: x(x)
	, y(y)
{
}

/**
 * Parametrized constructor.
 *
 * @param[in] pValues[2] - coordinates
 */
Vector2f::Vector2f(float pValues[2])
{
	if (pValues != 0)
	{
		x = pValues[0];
		y = pValues[1];
	}
}

/**
 * Copy constructor.
 *
 * @param[in] other - vector being copied
 */
Vector2f::Vector2f(const Vector2f& other)
  : x(other.x)
  , y(other.y)
{

}

/**
 * Destructor.
 */
Vector2f::~Vector2f()
{
}

/**
 * Normalize this vector.
 * This method makes the vector have a length of 1.
 */
inline void Vector2f::normalize()
{
	float length = this->length();
	x /= length;
	y /= length;
}

/**
 * Calculate this vector's length.
 *
 * @return vector length
*/
inline float Vector2f::length() const
{
	return (float)sqrt((double) x * x + y * y);
}

/**
 * Calculates the dot product between this vector and the vector other.
 *
 * @param[in] other - right hand side vector of the operation
 *
 * @return the dot product
 */
inline float Vector2f::dot(const Vector2f& other) const
{
	return x * other.x + y * other.y;
}

/**
 * Calculates the distance between this vector and the vector other.
 *
 * @param[in] other - right hand side vector of the operation
 *
 * @return distance to other vector
 */
inline float Vector2f::distance(const Vector2f& other) const
{
	return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

/**
 * Calculates a reflection of this vector off the plane represented by the
 * normal vector.
 *
 * @param[in] normal - reflection plane normal
 *
 * @return the reflection
 */
inline Vector2f Vector2f::reflect(const Vector2f& normal) const
{
	float dot = this->dot(normal);
	return Vector2f(x - 2.0f * dot * normal.x,
		            y - 2.0f * dot * normal.y);
}

/**
 * Returns the angle, in degrees, between this vector and the other vector.
 *
 * @param[in] other - right hand side vector of the operation
 *
 * @return angle in degrees
 */
inline float Vector2f::angle(const Vector2f& other) const
{
	return atan2(x * other.y - y * other.x,
		         dot(other));
}

/**
 * Conversion function which converts the Vector2f to a float array to be
 * used in OpenGL functions.
 *
 * @return coordinates array with two elements
 */
inline Vector2f::operator float*()
{
	return v;
}

/**
 * Conversion function which converts the Vector2f to a const float array to
 * be used in OpenGL functions.
 *
 * @return const coordinates array with two elements
 */
inline Vector2f::operator const float*() const
{
	return v;
}

inline bool Vector2f::operator !=(const Vector2f& right) const
{
	return x != right.x || y != right.y;
}

inline bool Vector2f::operator ==(const Vector2f& right) const
{
	return fabs(x - right.x) < EPSILON &&
		   fabs(y - right.y) < EPSILON;
}

inline Vector2f& Vector2f::operator =(const Vector2f& right)
{
	if (this == &right)
	{
		return *this;
	}

	x = right.x;
	y = right.y;
	return *this;
}

inline Vector2f Vector2f::operator -() const
{
	return Vector2f(-x, -y);
}

inline Vector2f& Vector2f::operator *=(float val)
{
	x *= val;
	y *= val;
	return *this;
}

inline Vector2f& Vector2f::operator +=(const Vector2f& right)
{
	x += right.x;
	y += right.y;
	return *this;
}

inline Vector2f& Vector2f::operator -=(const Vector2f& right)
{
	x -= right.x;
	y -= right.y;
	return *this;
}

inline Vector2f operator *(const Vector2f& left, float val)
{
	return Vector2f(left.x * val, left.y * val);
}

inline Vector2f operator *(float val, const Vector2f& left)
{
	return Vector2f(left.x * val, left.y * val);
}

inline Vector2f operator -(const Vector2f& left, const Vector2f& right)
{
	return Vector2f(left.x - right.x, left.y - right.y);
}

inline Vector2f operator +(const Vector2f& left, const Vector2f& right)
{
	return Vector2f(left.x + right.x, left.y + right.y);
}

}
