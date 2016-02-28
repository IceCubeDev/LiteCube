/* Vector2f.h -- Contains the implementation of the Vector2f class
 *
 * Copyright (C) 2016 Ivan Dortulov
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "..\..\Include\LiteCube\Math\Vector2f.h"
#include <cmath>

const float EPSILON = 0.0000001f;

namespace Lite
{

///////////////////////////////////////////////////////////////////////////////
/// Default constructor.
///
/// Initializes the x and y coordinates to 0.
///////////////////////////////////////////////////////////////////////////////
Vector2f::Vector2f()
	: x(0)
	, y(0)
{
}


///////////////////////////////////////////////////////////////////////////////
/// Parametrized constructor.
///
/// @param[in] x - x coordinate
/// @param[in] y - y coordinate
///////////////////////////////////////////////////////////////////////////////
Vector2f::Vector2f(float x, float y)
	: x(x)
	, y(y)
{
}

///////////////////////////////////////////////////////////////////////////////
/// Parametrized constructor.
///
/// @param[in] pValues - coordinates
///////////////////////////////////////////////////////////////////////////////
Vector2f::Vector2f(float pValues[2])
{
	if (pValues != 0)
	{
		x = pValues[0];
		y = pValues[1];
	}
}

///////////////////////////////////////////////////////////////////////////////
/// Destructor.
///////////////////////////////////////////////////////////////////////////////
Vector2f::~Vector2f()
{
}

///////////////////////////////////////////////////////////////////////////////
/// Normalizes the vector.
///////////////////////////////////////////////////////////////////////////////
void Vector2f::normalize()
{
	float length = this->length();
	x /= length;
	y /= length;
}

///////////////////////////////////////////////////////////////////////////////
/// Calculates the vector's magnitude.
///
/// @retval float - vector magnitude
///////////////////////////////////////////////////////////////////////////////
float Vector2f::length() const
{
	return (float)sqrt((double) x * x + y * y);
}

///////////////////////////////////////////////////////////////////////////////
/// Calculates the dot product between this vector and another vector.
///
/// @param[in] right - other vector
///
/// @retval float - the dot product
///////////////////////////////////////////////////////////////////////////////
float Vector2f::dot(const Vector2f& right) const
{
	return x * right.x + y * right.y;
}

///////////////////////////////////////////////////////////////////////////////
/// Calculates the distance between this vector and another vector.
///
/// @param[in] other - other vector
///
/// @retval float - distance to other vector
///////////////////////////////////////////////////////////////////////////////
float Vector2f::distance(const Vector2f& other) const
{
	return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

///////////////////////////////////////////////////////////////////////////////
/// Calculates a reflection of this vector agains a plane represented by the
/// normal vector.
///
/// @param[in] normal - reflection plane normal
///
/// @retval Vector2f - the reflected vector
///////////////////////////////////////////////////////////////////////////////
Vector2f Vector2f::reflect(const Vector2f& normal) const
{
	float dot = this->dot(normal);
	return Vector2f(x - 2.0f * dot * normal.x,
		            y - 2.0f * dot * normal.y);
}

///////////////////////////////////////////////////////////////////////////////
/// Conversion function which converts the Vector2f to a float array to be
/// used in OpenGL functions.
///
/// @retval float* - coordinates array
///////////////////////////////////////////////////////////////////////////////
Vector2f::operator float*()
{
	return v;
}

///////////////////////////////////////////////////////////////////////////////
/// Conversion function which converts the Vector2f to a const float array to
/// be used in OpenGL functions.
///
/// @retval const float* - coordinates array
///////////////////////////////////////////////////////////////////////////////
Vector2f::operator const float*() const
{
	return v;
}

bool Vector2f::operator !=(const Vector2f& right) const
{
	return x != right.x || y != right.y;
}

bool Vector2f::operator ==(const Vector2f& right) const
{
	return fabs(x - right.x) < EPSILON &&
		   fabs(y - right.y) < EPSILON;
}

Vector2f& Vector2f::operator =(const Vector2f& right)
{
	if (this == &right)
	{
		return *this;
	}

	x = right.x;
	y = right.y;
	return *this;
}

Vector2f Vector2f::operator -() const
{
	return Vector2f(-x, -y);
}

Vector2f& Vector2f::operator *=(float val)
{
	x *= val;
	y *= val;
	return *this;
}

Vector2f& Vector2f::operator +=(const Vector2f& right)
{
	x += right.x;
	y += right.y;
	return *this;
}

Vector2f& Vector2f::operator -=(const Vector2f& right)
{
	x -= right.x;
	y -= right.y;
	return *this;
}

Vector2f operator *(const Vector2f& left, float val)
{
	return Vector2f(left.x * val, left.y * val);
}

Vector2f operator *(float val, const Vector2f& left)
{
	return Vector2f(left.x * val, left.y * val);
}

Vector2f operator -(const Vector2f& left, const Vector2f& right)
{
	return Vector2f(left.x - right.x, left.y - right.y);
}

Vector2f operator +(const Vector2f& left, const Vector2f& right)
{
	return Vector2f(left.x + right.x, left.y + right.y);
}

}
