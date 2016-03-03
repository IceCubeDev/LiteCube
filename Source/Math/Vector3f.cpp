/* Vector3f.h -- Contains the implementation of the Vector3f class
 *
 * Copyright (C) 2016 Ivan Dortulov (ivandortulov@yahoo.com)
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "..\..\Include\LiteCube\Math\Vector2f.h"
#include "..\..\Include\LiteCube\Math\Vector3f.h"

#include <cmath>

namespace Lite
{

/**
 * Default constructor.
 * Initializes the all coordinates to 0.
 */ 
Vector3f::Vector3f()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
{
}

/**
 * Convert a 2D vector to a 3D vector.
 *
 * @param[in] other - vector to convert
 * @param[in] z     - missing coordinate value
 */
Vector3f::Vector3f(const Vector2f& other, float z)
  : x(other.x)
  , y(other.y)
  , z(z)
{

}

/**
 * Copy constructor.
 *
 * @param[in] other - vector being copied
 */
Vector3f::Vector3f(const Vector3f& other)
  : x(other.x)
  , y(other.y)
  , z(other.z)
{
}

/**
 * Parametrized constructor.
 *
 * @param[in] x - x coordinate
 * @param[in] y - y coordinate
 * @param[in] z - y coordinate
 */
Vector3f::Vector3f(float x, float y, float z)
  : x(x)
  , y(y)
  , z(z)
{
}

/**
 * Parametrized constructor.
 *
 * @param[in] pValues[3] - coordinates
 */
Vector3f::Vector3f(float pValues[3])
  : x(pValues[0])
  , y(pValues[1])
  , z(pValues[2])
{
}

/**
 * Destructor.
 */
Vector3f::~Vector3f()
{
}

/**
 * Normalize this vector.
 * This method makes the vector have a length of 1.
 */
inline void Vector3f::normalize()
{
  x /= length();
  y /= length();
  z /= length();
}

/**
 * Calculate this vector's length.
 *
 * @return vector length
*/
inline float Vector3f::length() const
{
  return sqrt(x * x + y * y + z * z);
}

/**
 * Calculate this vector's squared length.
 *
 * @return vector squared length
*/
inline float Vector3f::lengthSqr() const
{
  return x * x + y * y + z * z;
}

/**
 * Calculates the dot product between this vector and the vector other.
 *
 * @param[in] other - right hand side vector of the operation
 *
 * @return the dot product
 */
inline float Vector3f::dot(const Vector3f& other) const
{
  return x * other.x + y * other.y + z * other.z;
}

/**
 * Calculates the distance between this vector and the vector other.
 *
 * @param[in] other - right hand side vector of the operation
 *
 * @return distance to other vector
 */
inline float Vector3f::distance(const Vector3f& other) const
{
  return sqrt((x - other.x) * (x - other.x) +
              (y - other.y) * (y - other.y) + 
              (z - other.z) * (z - other.z));
}

/**
 * Calculates the squared distance between this vector and the vector other.
 *
 * @param[in] other - right hand side vector of the operation
 *
 * @return squared distance to other vector
 */
inline float Vector3f::distanceSqr(const Vector3f& other) const
{
  return (x - other.x) * (x - other.x) +
         (y - other.y) * (y - other.y) + 
         (z - other.z) * (z - other.z);
}

/**
 * Returns the angle, in degrees, between this vector and the other vector.
 *
 * @param[in] other - right hand side vector of the operation
 *
 * @return angle in degrees
 */
float Vector3f::angle(const Vector3f& other) const 
{
  float dot = this->dot(other);
  float len1 = this->lengthSqr();
  float len2 = this->lengthSqr();
  return acos(dot / sqrt(len1 * len2));
}

Vector3f Vector3f::cross(const Vector3f& other) const
{
  return Vector3f(y * other.z - z * other.y,
                  z * other.x - x * other.z,
                  x * other.y - y * other.x);
}

Vector3f Vector3f::reflect(const Vector3f& normal) const
{
  float dot = this->dot(normal);
  return Vector3f(x - 2.0f * dot * normal.x,
                  y - 2.0f * dot * normal.y,
                  z - 2.0f * dot * normal.z);
}

/**
 * Conversion function which converts the Vector2f to a float array to be
 * used in OpenGL functions.
 *
 * @return coordinates array with two elements
 */
Vector3f::operator float*()
{
  return v;
}

/**
 * Conversion function which converts the Vector2f to a const float array to
 * be used in OpenGL functions.
 *
 * @return const coordinates array with two elements
 */
Vector3f::operator const float*() const
{
  return v;
}

bool Vector3f::operator !=(const Vector3f& right) const
{
  return (fabs(x - right.x) > EPSILON ||
          fabs(y - right.y) > EPSILON ||
          fabs(z - right.z) > EPSILON);
}

bool Vector3f::operator ==(const Vector3f& right) const
{
  return (fabs(x - right.x) < EPSILON &&
          fabs(y - right.y) < EPSILON &&
          fabs(z - right.z) < EPSILON);
}

Vector3f& Vector3f::operator =(const Vector3f& right)
{
  if ( this != &right )
  {
    x = right.x;
    y = right.y;
    z = right.z;
  }

  return *this;
}

Vector3f Vector3f::operator -() const
{
  return Vector3f(-x, -y, -z);
}

Vector3f& Vector3f::operator *=(float val)
{
  x *= val;
  y *= val;
  z *= val;
  return *this;
}

Vector3f& Vector3f::operator +=(const Vector3f& right)
{
  x += right.x;
  y += right.y;
  z += right.z;
  return *this;
}

Vector3f& Vector3f::operator -=(const Vector3f& right)
{
  x -= right.x;
  y -= right.y;
  z -= right.z;
  return *this;
}

Vector3f operator *(const Vector3f& left, float right)
{
  return Vector3f(left.x * right,
                  left.y * right,
                  left.z * right);
}

Vector3f operator *(float left, const Vector3f& right)
{
  return Vector3f(right.x * left, 
                  right.y * left, 
                  right.z * left);
}

Vector3f operator -(const Vector3f& left, const Vector3f& right)
{
  return Vector3f(left.x - right.x,
                  left.y - right.y,
                  left.z - right.z);
}

Vector3f operator +(const Vector3f& left, const Vector3f& right)
{
  return Vector3f(left.x + right.x,
                  left.y + right.y,
                  left.z + right.z);
}

}