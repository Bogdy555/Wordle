#include "..\Headers\WordleAPI.hpp"



const WordleAPI::Vec2& WordleAPI::Vec2::operator+ () const
{
	return *this;
}

const WordleAPI::Vec2 WordleAPI::Vec2::operator- () const
{
	return Vec2(-x, -y);
}

const WordleAPI::Vec2 WordleAPI::Vec2::operator+ (const Vec2& _Other) const
{
	return Vec2(x + _Other.x, y + _Other.y);
}

const WordleAPI::Vec2 WordleAPI::Vec2::operator+ (float _Value) const
{
	return Vec2(x + _Value, y + _Value);
}

WordleAPI::Vec2& WordleAPI::Vec2::operator+= (const Vec2& _Other)
{
	x += _Other.x;
	y += _Other.y;

	return *this;
}

WordleAPI::Vec2& WordleAPI::Vec2::operator+= (float _Value)
{
	x += _Value;
	y += _Value;

	return *this;
}

const WordleAPI::Vec2 WordleAPI::Vec2::operator- (const Vec2& _Other) const
{
	return Vec2(x - _Other.x, y - _Other.y);
}

const WordleAPI::Vec2 WordleAPI::Vec2::operator- (float _Value) const
{
	return Vec2(x - _Value, y - _Value);
}

WordleAPI::Vec2& WordleAPI::Vec2::operator-= (const Vec2& _Other)
{
	x -= _Other.x;
	y -= _Other.y;

	return *this;
}

WordleAPI::Vec2& WordleAPI::Vec2::operator-= (float _Value)
{
	x -= _Value;
	y -= _Value;

	return *this;
}

const WordleAPI::Vec2 WordleAPI::Vec2::operator* (const Vec2& _Other) const
{
	return Vec2(x * _Other.x, y * _Other.y);
}

const WordleAPI::Vec2 WordleAPI::Vec2::operator* (float _Value) const
{
	return Vec2(x * _Value, y * _Value);
}

WordleAPI::Vec2& WordleAPI::Vec2::operator*= (const Vec2& _Other)
{
	x *= _Other.x;
	y *= _Other.y;

	return *this;
}

WordleAPI::Vec2& WordleAPI::Vec2::operator*= (float _Value)
{
	x *= _Value;
	y *= _Value;

	return *this;
}

const WordleAPI::Vec2 WordleAPI::Vec2::operator/ (const Vec2& _Other) const
{
	return Vec2(x / _Other.x, y / _Other.y);
}

const WordleAPI::Vec2 WordleAPI::Vec2::operator/ (float _Value) const
{
	return Vec2(x / _Value, y / _Value);
}

WordleAPI::Vec2& WordleAPI::Vec2::operator/= (const Vec2& _Other)
{
	x /= _Other.x;
	y /= _Other.y;

	return *this;
}

WordleAPI::Vec2& WordleAPI::Vec2::operator/= (float _Value)
{
	x /= _Value;
	y /= _Value;

	return *this;
}



const WordleAPI::Vec3& WordleAPI::Vec3::operator+ () const
{
	return *this;
}

const WordleAPI::Vec3 WordleAPI::Vec3::operator- () const
{
	return Vec3(-x, -y, -z);
}

const WordleAPI::Vec3 WordleAPI::Vec3::operator+ (const Vec3& _Other) const
{
	return Vec3(x + _Other.x, y + _Other.y, z + _Other.z);
}

const WordleAPI::Vec3 WordleAPI::Vec3::operator+ (float _Value) const
{
	return Vec3(x + _Value, y + _Value, z + _Value);
}

WordleAPI::Vec3& WordleAPI::Vec3::operator+= (const Vec3& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;

	return *this;
}

WordleAPI::Vec3& WordleAPI::Vec3::operator+= (float _Value)
{
	x += _Value;
	y += _Value;
	z += _Value;

	return *this;
}

const WordleAPI::Vec3 WordleAPI::Vec3::operator- (const Vec3& _Other) const
{
	return Vec3(x - _Other.x, y - _Other.y, z - _Other.z);
}

const WordleAPI::Vec3 WordleAPI::Vec3::operator- (float _Value) const
{
	return Vec3(x - _Value, y - _Value, z - _Value);
}

WordleAPI::Vec3& WordleAPI::Vec3::operator-= (const Vec3& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;

	return *this;
}

WordleAPI::Vec3& WordleAPI::Vec3::operator-= (float _Value)
{
	x -= _Value;
	y -= _Value;
	z -= _Value;

	return *this;
}

const WordleAPI::Vec3 WordleAPI::Vec3::operator* (const Vec3& _Other) const
{
	return Vec3(x * _Other.x, y * _Other.y, z * _Other.z);
}

const WordleAPI::Vec3 WordleAPI::Vec3::operator* (float _Value) const
{
	return Vec3(x * _Value, y * _Value, z * _Value);
}

WordleAPI::Vec3& WordleAPI::Vec3::operator*= (const Vec3& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;

	return *this;
}

WordleAPI::Vec3& WordleAPI::Vec3::operator*= (float _Value)
{
	x *= _Value;
	y *= _Value;
	z *= _Value;

	return *this;
}

const WordleAPI::Vec3 WordleAPI::Vec3::operator/ (const Vec3& _Other) const
{
	return Vec3(x / _Other.x, y / _Other.y, z / _Other.z);
}

const WordleAPI::Vec3 WordleAPI::Vec3::operator/ (float _Value) const
{
	return Vec3(x / _Value, y / _Value, z / _Value);
}

WordleAPI::Vec3& WordleAPI::Vec3::operator/= (const Vec3& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;

	return *this;
}

WordleAPI::Vec3& WordleAPI::Vec3::operator/= (float _Value)
{
	x /= _Value;
	y /= _Value;
	z /= _Value;

	return *this;
}



const WordleAPI::Vec4& WordleAPI::Vec4::operator+ () const
{
	return *this;
}

const WordleAPI::Vec4 WordleAPI::Vec4::operator- () const
{
	return Vec4(-x, -y, -z, -w);
}

const WordleAPI::Vec4 WordleAPI::Vec4::operator+ (const Vec4& _Other) const
{
	return Vec4(x + _Other.x, y + _Other.y, z + _Other.z, w + _Other.w);
}

const WordleAPI::Vec4 WordleAPI::Vec4::operator+ (float _Value) const
{
	return Vec4(x + _Value, y + _Value, z + _Value, w + _Value);
}

WordleAPI::Vec4& WordleAPI::Vec4::operator+= (const Vec4& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;
	w += _Other.w;

	return *this;
}

WordleAPI::Vec4& WordleAPI::Vec4::operator+= (float _Value)
{
	x += _Value;
	y += _Value;
	z += _Value;
	w += _Value;

	return *this;
}

const WordleAPI::Vec4 WordleAPI::Vec4::operator- (const Vec4& _Other) const
{
	return Vec4(x - _Other.x, y - _Other.y, z - _Other.z, w - _Other.w);
}

const WordleAPI::Vec4 WordleAPI::Vec4::operator- (float _Value) const
{
	return Vec4(x - _Value, y - _Value, z - _Value, w - _Value);
}

WordleAPI::Vec4& WordleAPI::Vec4::operator-= (const Vec4& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;
	w -= _Other.w;

	return *this;
}

WordleAPI::Vec4& WordleAPI::Vec4::operator-= (float _Value)
{
	x -= _Value;
	y -= _Value;
	z -= _Value;
	w -= _Value;

	return *this;
}

const WordleAPI::Vec4 WordleAPI::Vec4::operator* (const Vec4& _Other) const
{
	return Vec4(x * _Other.x, y * _Other.y, z * _Other.z, w * _Other.w);
}

const WordleAPI::Vec4 WordleAPI::Vec4::operator* (float _Value) const
{
	return Vec4(x * _Value, y * _Value, z * _Value, w * _Value);
}

WordleAPI::Vec4& WordleAPI::Vec4::operator*= (const Vec4& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;
	w *= _Other.w;

	return *this;
}

WordleAPI::Vec4& WordleAPI::Vec4::operator*= (float _Value)
{
	x *= _Value;
	y *= _Value;
	z *= _Value;
	w *= _Value;

	return *this;
}

const WordleAPI::Vec4 WordleAPI::Vec4::operator/ (const Vec4& _Other) const
{
	return Vec4(x / _Other.x, y / _Other.y, z / _Other.z, w / _Other.w);
}

const WordleAPI::Vec4 WordleAPI::Vec4::operator/ (float _Value) const
{
	return Vec4(x / _Value, y / _Value, z / _Value, w / _Value);
}

WordleAPI::Vec4& WordleAPI::Vec4::operator/= (const Vec4& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;
	w /= _Other.w;

	return *this;
}

WordleAPI::Vec4& WordleAPI::Vec4::operator/= (float _Value)
{
	x /= _Value;
	y /= _Value;
	z /= _Value;
	w /= _Value;

	return *this;
}
