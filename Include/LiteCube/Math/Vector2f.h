/** 
 * @file Vector2f.h
 * @date 28.02.2016
 * @author Ivan Dortulov (ivandortulov@yahoo.com)
 * @brief Contains the declaration of the Vector2f class
 *
 * @section COPYRIGHT
 * Copyright (C) 2016 Ivan Dortulov (ivandortulov@yahoo.com)
 *
 * @section LICENSE 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef VECTOR2F_H
#define VECTOR2F_H

#include "..\LiteDefines.h"

namespace Lite
{

//!  Class representing a 2D mathematical vector. 
class LITE_API Vector2f
{
public:
	Vector2f();
	Vector2f(const Vector2f& other);
	Vector2f(float x, float y);
	Vector2f(float pValues[2]);
	~Vector2f();

public:
	void normalize();
	float length() const;
  float lengthSqr() const;
	float dot(const Vector2f& other) const;
	float distance(const Vector2f& other) const;
  float distanceSqr(const Vector2f& other) const;
	Vector2f reflect(const Vector2f& normal) const;
	float angle(const Vector2f& other)  const;

public:
	operator float*();
	operator const float*() const;

	bool operator !=(const Vector2f& right) const;
	bool operator ==(const Vector2f& right) const;

	Vector2f& operator =(const Vector2f& right);
	Vector2f operator -() const;

	Vector2f& operator *=(float val);
	Vector2f& operator +=(const Vector2f& right);
	Vector2f& operator -=(const Vector2f& right);

	friend Vector2f operator *(const Vector2f& left, float right);
	friend Vector2f operator *(float left, const Vector2f& right);
	friend Vector2f operator -(const Vector2f& left, const Vector2f& right);
	friend Vector2f operator +(const Vector2f& left, const Vector2f& right);

public:
	static const Vector2f Zero;
	static const Vector2f One;
	static const Vector2f Left;
	static const Vector2f Right;
	static const Vector2f Up;
	static const Vector2f Down;

public:
		union
		{
			float v[2];
			struct { float x, y; };
		};
};

}
#endif	// VECTOR2F_H
