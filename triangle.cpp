#include "stdafx.h"
#include "triangle.h"

namespace earclipping_triangulation
{
	Triangle::Triangle() { for (size_t i = 0; i < count; i++) vertices.push_back(Vector()); }
	Triangle::Triangle(Vector * array) { for (size_t i = 0; i < count; i++) vertices.push_back(Vector(array[i])); }
	Triangle::Triangle(const Vector & p1, const Vector & p2, const Vector & p3)
	{
		vertices.push_back(Vector(p1));
		vertices.push_back(Vector(p2));
		vertices.push_back(Vector(p3));
	}
	Triangle::Triangle(const Triangle & source)
	{
		for (size_t i = 0; i < count; i++) vertices.push_back(Vector(source.vertices[i]));
	}
	Triangle & Triangle::operator = (const Triangle & that)
	{
		vertices.clear();
		for (size_t i = 0; i < count; i++) vertices.push_back(Vector(that.vertices[i]));
		return *this;
	}
}