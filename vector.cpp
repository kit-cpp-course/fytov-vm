#include "stdafx.h"
#include "vector.h"

namespace earclipping_triangulation
{
	Vector::Vector(float x, float y) : x(x), y(y) {}
	Vector::Vector(const Vector & source) : x(source.x), y(source.y) {}
	Vector & Vector::operator = (const Vector & that)
	{
		x = that.x;
		y = that.y;
		return *this;
	}
	Vector Vector::operator + (const Vector & that) const { return Vector(x + that.x, y + that.x); }
	Vector Vector::operator - (const Vector & that) const { return Vector(x - that.x, y - that.y); }
	Vector Vector::operator * (const int x) const { return Vector(this->x*x, this->y*x); }
	Vector Vector::operator / (const int x) const { return Vector(this->x / x, this->y / x); }
	float Vector::Det(const Vector & that) const { return x*that.y - y*that.x; }
	string Vector::toString() const { return  to_string(x) + "," + to_string(y); }
	ostream & operator << (ostream & os, Vector v) { return os << v.x << "," << v.y; }// Operator <<
}