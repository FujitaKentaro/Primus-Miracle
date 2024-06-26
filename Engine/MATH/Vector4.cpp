#include "Vector4.h"
#include "Vector3.h"
#pragma warning(push)
#pragma warning(disable: 4819)
#include<cmath>  //sprt
#pragma warning(pop)

Vector4::Vector4() :x(0), y(0), z(0), w(0)
{
}

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(float num)
{
	x = num;
	y = num;
	z = num;
	w = num;
}

Vector4::Vector4(Vector3 vec3, float w)
{
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
	this->w = w;
}

float Vector4::Length()const {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::Normalization() const
{
	Vector4 tmp(*this);

	float len = Length();
	if (len != 0)
	{
		return tmp /= len;

	}

	return tmp;
}

Vector4& Vector4::Normalize() {
	float len = Length();
	if (len != 0) {
		return *this /= len;
	}
	return *this;
}

float Vector4::Dot(const Vector4& v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vector4 Vector4::Cross(const Vector4& v) const
{
	return Vector4(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x,
		v.w
	);
}

Vector4 Vector4::operator+() const
{
	return Vector4(x, y, z, w);
}

Vector4 Vector4::operator-() const
{
	return Vector4(x, y, z, w);
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
	return *this;
}

Vector4& Vector4::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
	return *this;
}

Vector4& Vector4::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}



const Vector4 operator+(const Vector4& v1, const Vector4& v2)
{
	Vector4 temp(v1);
	temp.x += v2.x;
	temp.y += v2.y;
	temp.z += v2.z;
	temp.w += v2.w;
	return temp;
}

const Vector4 operator-(const Vector4& v1, const Vector4& v2)
{
	Vector4 temp(v1);
	temp.x -= v2.x;
	temp.y -= v2.y;
	temp.z -= v2.z;
	temp.w -= v2.w;
	return temp;
}

const Vector4 operator*(const Vector4& v, float s)
{
	Vector4 temp(v);
	temp.x *= s;
	temp.y *= s;
	temp.z *= s;
	temp.w *= s;
	return temp;
}

const Vector4 operator*(float s, const Vector4& v)
{
	Vector4 result;
	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	result.w = v.w * s;
	return result;
}

const Vector4 operator/(const Vector4& v, float s)
{
	Vector4 temp(v);
	temp.x /= s;
	temp.y /= s;
	temp.z /= s;
	temp.w /= s;
	return temp;
}

void Vector4Lerp(const Vector4& src1, const Vector4& src2, float t, Vector4& dest)
{
	dest.x = src1.x + (src2.x - src1.x) * t;
	dest.y = src1.y + (src2.y - src1.y) * t;
	dest.z = src1.z + (src2.z - src1.z) * t;
	dest.w = src1.w + (src2.w - src1.w) * t;
}

Vector4 Vector4Lerp(const Vector4& src1, const Vector4& src2, float t)
{
	Vector4 result;
	Vector4Lerp(src1, src2, t, result);
	return result;
}
