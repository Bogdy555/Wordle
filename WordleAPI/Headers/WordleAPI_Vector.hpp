#ifndef WordleAPI_Vector_hpp

#define WordleAPI_Vector_hpp



#include "WordleAPI.hpp"



namespace WordleAPI
{

	struct Vec2
	{
		float x = 0.0f, y = 0.0f;

		const Vec2& operator+ () const;
		const Vec2 operator- () const;

		const Vec2 operator+ (const Vec2& _Other) const;
		const Vec2 operator+ (float _Value) const;

		Vec2& operator+= (const Vec2& _Other);
		Vec2& operator+= (float _Value);

		const Vec2 operator- (const Vec2& _Other) const;
		const Vec2 operator- (float _Value) const;

		Vec2& operator-= (const Vec2& _Other);
		Vec2& operator-= (float _Value);

		const Vec2 operator* (const Vec2& _Other) const;
		const Vec2 operator* (float _Value) const;

		Vec2& operator*= (const Vec2& _Other);
		Vec2& operator*= (float _Value);

		const Vec2 operator/ (const Vec2& _Other) const;
		const Vec2 operator/ (float _Value) const;

		Vec2& operator/= (const Vec2& _Other);
		Vec2& operator/= (float _Value);
	};

	struct Vec3
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;

		const Vec3& operator+ () const;
		const Vec3 operator- () const;

		const Vec3 operator+ (const Vec3& _Other) const;
		const Vec3 operator+ (float _Value) const;

		Vec3& operator+= (const Vec3& _Other);
		Vec3& operator+= (float _Value);

		const Vec3 operator- (const Vec3& _Other) const;
		const Vec3 operator- (float _Value) const;

		Vec3& operator-= (const Vec3& _Other);
		Vec3& operator-= (float _Value);

		const Vec3 operator* (const Vec3& _Other) const;
		const Vec3 operator* (float _Value) const;

		Vec3& operator*= (const Vec3& _Other);
		Vec3& operator*= (float _Value);

		const Vec3 operator/ (const Vec3& _Other) const;
		const Vec3 operator/ (float _Value) const;

		Vec3& operator/= (const Vec3& _Other);
		Vec3& operator/= (float _Value);
	};

	struct Vec4
	{
		float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

		const Vec4& operator+ () const;
		const Vec4 operator- () const;

		const Vec4 operator+ (const Vec4& _Other) const;
		const Vec4 operator+ (float _Value) const;

		Vec4& operator+= (const Vec4& _Other);
		Vec4& operator+= (float _Value);

		const Vec4 operator- (const Vec4& _Other) const;
		const Vec4 operator- (float _Value) const;

		Vec4& operator-= (const Vec4& _Other);
		Vec4& operator-= (float _Value);

		const Vec4 operator* (const Vec4& _Other) const;
		const Vec4 operator* (float _Value) const;

		Vec4& operator*= (const Vec4& _Other);
		Vec4& operator*= (float _Value);

		const Vec4 operator/ (const Vec4& _Other) const;
		const Vec4 operator/ (float _Value) const;

		Vec4& operator/= (const Vec4& _Other);
		Vec4& operator/= (float _Value);
	};

}



#endif
