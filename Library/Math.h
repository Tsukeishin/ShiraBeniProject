#ifndef __TSULIB_MATH_H_INCLUDE__
#define __TSULIB_MATH_H_INCLUDE__


//================================================================
// PI
//================================================================
#define TSU_PI (3.1415926536f)
#ifndef PI
#define PI TSU_PI
#endif // !PI

#define DegToRad( degree ) ( degree / 180.0f * TSU_PI )
#define RadToDeg( radian ) ( radian / TSU_PI * 180.0f )


//================================================================
// Root
//================================================================
#define ROOT2 (1.4142135624f)
#define ROOT3 (1.7320508076f)
#define ROOT5 (2.2360679775f)
#define ROOT7 (2.6457513111f)


//================================================================
// Calculation
//================================================================
#define Absolute( value ) ( value < 0 ? -value : value )
#define Random( n, m ) (rand() % ((m - n) + 1) + n)


//================================================================
// X2, X3 MultiData
//================================================================
template<typename DATA>
struct X2
{
	DATA x;
	DATA y;

	X2();
	X2(const X2 &x2);
	X2(DATA x, DATA y);

	X2 & operator += (const X2 x2);
	X2 & operator -= (const X2 x2);
	template<typename Type>
	X2 & operator *= (const Type t);
	template<typename Type>
	X2 & operator /= (const Type t);

	X2 operator + (void) const;
	X2 operator - (void) const;

	X2 operator + (const X2 x2) const;
	X2 operator - (const X2 x2) const;
	template<typename Type>
	X2 operator * (const Type t) const;
	template<typename Type>
	X2 operator / (const Type t) const;

	bool operator == (const X2 x2) const;
	bool operator != (const X2 x2) const;

};

template<typename DATA>
X2<DATA>::X2()
{
	this->x = (DATA)0;
	this->y = (DATA)0;
}
template<typename DATA>
X2<DATA>::X2(const X2<DATA> &x2)
{
	*this = x2;
}
template<typename DATA>
X2<DATA>::X2(DATA x, DATA y)
{
	this->x = x;
	this->y = y;
}

template<typename DATA>
X2<DATA> & X2<DATA>::operator+=(const X2 x2)
{
	this->x += x2.x;
	this->y += x2.y;
	return *this;
}
template<typename DATA>
X2<DATA> & X2<DATA>::operator-=(const X2 x2)
{
	this->x -= x2.x;
	this->y -= x2.y;
	return *this;
}
template<typename DATA>
template<typename Type>
X2<DATA> & X2<DATA>::operator*=(const Type t)
{
	this->x *= t;
	this->y *= t;
	return *this;
}
template<typename DATA>
template<typename Type>
X2<DATA> & X2<DATA>::operator/=(const Type t)
{
	this->x /= t;
	this->y /= t;
	return *this;
}

template<typename DATA>
X2<DATA> X2<DATA>::operator+(void) const
{
	return *this;
}
template<typename DATA>
X2<DATA> X2<DATA>::operator-(void) const
{
	return X2(-this->x, -this->y);
}

template<typename DATA>
X2<DATA> X2<DATA>::operator+(const X2 x2) const
{
	return X2(this->x + x2.x, this->y + x2.y);
}
template<typename DATA>
X2<DATA> X2<DATA>::operator-(const X2 x2) const
{
	return X2(this->x - x2.x, this->y - x2.y);
}
template<typename DATA>
template<typename Type>
X2<DATA> X2<DATA>::operator*(const Type t) const
{
	return X2(this->x * t, this->y * t);
}
template<typename DATA>
template<typename Type>
X2<DATA> X2<DATA>::operator/(const Type t) const
{
	return X2(this->x / t, this->y / t);
}

template<typename DATA>
bool X2<DATA>::operator==(const X2 x2) const
{
	return (this->x == x2.x) && (this->y == x2.y);
}
template<typename DATA>
bool X2<DATA>::operator!=(const X2 x2) const
{
	return (this->x != x2.x) && (this->y != x2.y);
}


#endif // !__TSULIB_MATH_INCLUDE__
