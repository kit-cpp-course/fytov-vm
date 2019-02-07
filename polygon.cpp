#include "stdafx.h"
#include "polygon.h"

namespace earclipping_triangulation
{
	Polygon::Polygon() {}
	Polygon::Polygon(Vector * array, size_t count) { for (size_t i = 0; i < count; i++) vertices.push_back(Vector(array[i])); }
	Polygon::Polygon(const Polygon & source)
	{
		for (size_t i = 0; i < source.getPointCount(); i++) vertices.push_back(Vector(source.vertices[i]));
	}
	Polygon & Polygon::operator = (const Polygon & that)
	{
		vertices.clear();
		for (size_t i = 0; i < that.getPointCount(); i++) vertices.push_back(Vector(that.vertices[i]));
		return *this;
	}
	size_t Polygon::getValidIndex(const int & n) const
	{
		if (n < 0)
		{
			return abs(n) <= vertices.size() ? vertices.size() + n : vertices.size() + n % vertices.size();
		}
		else return n < vertices.size() ? n : n % vertices.size();
	}
	void Polygon::addPoint(int i, const Vector & p)
	{
		vector<Vector>::iterator iter = vertices.begin() + getValidIndex(i);
		vertices.insert(iter, Vector(p));
	}
	void Polygon::removePoint(int i)
	{
		if (vertices.empty()) return;
		vector<Vector>::iterator iter = vertices.begin() + getValidIndex(i);
		vertices.erase(iter);
	}
	void Polygon::clear() { vertices.clear(); }
	void Polygon::setPoint(int i, const Vector & p)
	{
		i = getValidIndex(i);
		vertices[i].x = p.x;
		vertices[i].y = p.y;
	}
	Vector Polygon::getPoint(int i) const { return Vector(vertices[getValidIndex(i)]); }
	void Polygon::addPoint(const Vector & p) { vertices.push_back(Vector(p)); }
	void Polygon::removePoint() { if (!vertices.empty())vertices.pop_back(); }
	size_t Polygon::getPointCount() const { return vertices.size(); }
	string Polygon::toString() const
	{
		string s;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			s += "Point" + to_string(i) + "(" + vertices[i].toString() + ")\n";
		}
		return s;
	}
	// Operator <<
	ostream & operator << (ostream & os, Polygon p)
	{
		for (size_t i = 0; i < p.vertices.size(); i++)
		{
			os << "Point" << i + 1 << "(" << p.vertices[i] << ")\n";
		}
		return os;
	}
}