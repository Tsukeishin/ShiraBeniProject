#ifndef __VECTOR_H_INCLUDE__
#define __VECTOR_H_INCLUDE__


#include <d3dx9math.h>	// DirectX9


class Vector2
{
public:
	static float Dot(  Vector2 const &a, Vector2 const &b);
	static float Cross(Vector2 const &a, Vector2 const &b);

public:
	float x;
	float y;

	Vector2();
	Vector2(const Vector2 &vec2);
	Vector2(float x, float y);

	Vector2 & operator += (const Vector2 v);
	Vector2 & operator -= (const Vector2 v);
	Vector2 & operator *= (const float f);
	Vector2 & operator /= (const float f);

	Vector2 operator + (void) const;
	Vector2 operator - (void) const;

	Vector2 operator + (const Vector2 v) const;
	Vector2 operator - (const Vector2 v) const;
	Vector2 operator * (const float f) const;
	Vector2 operator / (const float f) const;

	bool operator == (const Vector2 v) const;
	bool operator != (const Vector2 v) const;

	float   Length(void);
	float   sqrLength(void);
	Vector2 Normalized(void);

	/* DirectX9 */
	operator D3DXVECTOR2() const;

};


class Vector3
{
public:
	static float   Dot(  Vector3 const &a, Vector3 const &b);
	static Vector3 Cross(Vector3 const &a, Vector3 const &b);

public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(const Vector3&);
	Vector3(float x, float y, float z);

	Vector3 & operator += (const Vector3 v);
	Vector3 & operator -= (const Vector3 v);
	Vector3 & operator *= (const float f);
	Vector3 & operator /= (const float f);

	Vector3 operator + (void) const;
	Vector3 operator - (void) const;

	Vector3 operator + (const Vector3 v) const;
	Vector3 operator - (const Vector3 v) const;
	Vector3 operator * (const float f) const;
	Vector3 operator / (const float f) const;

	bool operator == (const Vector3 v) const;
	bool operator != (const Vector3 v) const;

	float   Length(void) const;
	float   sqrLength(void) const;
	Vector3 Normalized(void) const;
	Vector2 ToVector2(void) const;

	/* DirectX9 */
	operator D3DXVECTOR3() const;

};

#endif // !__CLASS_VECTOR_INCLUDE__

