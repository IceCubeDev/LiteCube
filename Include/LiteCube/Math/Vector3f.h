/** 
 * @file Vector3f.h
 * @date 03.03.2016
 * @author Ivan Dortulov (ivandortulov@yahoo.com)
 * @brief Contains the declaration of the Vector3f class
 *
 * @section COPYRIGHT
 * Copyright (C) 2016 Ivan Dortulov (ivandortulov@yahoo.com)
 *
 * @section LICENSE 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef VECTOR3F_H
#define VECTOR3F_H

#include "..\LiteDefines.h"

namespace Lite
{
class Vector2f;

//!  Class representing a 2D mathematical vector. 
class LITE_API Vector3f
{
public:
	Vector3f();
  Vector3f(const Vector2f& other, float z);
	Vector3f(const Vector3f& other);
	Vector3f(float x, float y, float z);
	Vector3f(float pValues[3]);
	~Vector3f();

public:
	void normalize();
	float length() const;
  float lengthSqr() const;
	float dot(const Vector3f& other) const;
	float distance(const Vector3f& other) const;
  float distanceSqr(const Vector3f& other) const;
  float angle(const Vector3f& other) const;
	Vector3f cross(const Vector3f& other) const;
	Vector3f reflect(const Vector3f& normal) const;

public:
	operator float*();
	operator const float*() const;

	bool operator !=(const Vector3f& right) const;
	bool operator ==(const Vector3f& right) const;

	Vector3f& operator =(const Vector3f& right);
	Vector3f operator -() const;

	Vector3f& operator *=(float val);
	Vector3f& operator +=(const Vector3f& right);
	Vector3f& operator -=(const Vector3f& right);

	friend Vector3f operator *(const Vector3f& left, float right);
	friend Vector3f operator *(float left, const Vector3f& right);
	friend Vector3f operator -(const Vector3f& left, const Vector3f& right);
	friend Vector3f operator +(const Vector3f& left, const Vector3f& right);

public:
  static const Vector3f Up;
  static const Vector3f Down;
  static const Vector3f Left;
  static const Vector3f Right;
  static const Vector3f Forward;
  static const Vector3f Back;

public:
	union
	{
		float v[3];
		struct { float x, y, z; };
	};
};

}
#endif	// VECTOR3F_H