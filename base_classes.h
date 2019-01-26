// �������� � classes.cpp

#pragma once
#include <vector>
#include <string>
using namespace std;

namespace earclipping_triangulation 
{
	/*
	* �����, ����������� ������ � ��������� ������������.
	*/
	class Vector
	{
		/*
		* �������� ���������� ������
		*/
		friend ostream & operator << (ostream & os, Vector v);

	public:
		/*
		* ���������� �������.
		*/
		float x = 0, y = 0;
		/*
		* ����������� �� ���������.
		*/
		Vector(float x = 0, float y = 0);
		/*
		* ����������� �����������.
		*
		* ������ ������ �� ������ ��� ������������� �������.
		*
		* @param source ������, �� ������� �������� ������� �������
		* ����� ������
		*/
		Vector(const Vector & source);
		/*
		* �������� ������������.
		*
		* ����������� ������� �������� �� ������� ��������.
		*
		* @param that ������ �������. ������, �� �������� ������� �����
		* �������� ��� �������� �������.
		* @returns ������ �� ������� ��������� ������.
		*/
		Vector & operator = (const Vector & that);
		/*
		* ���������� ����� ��������.
		*
		* @param that ������ �������. ������, � ������� ������
		* ������� ������� ������.
		* @returns ����� ������.
		*/
		Vector operator + (const Vector & that) const;
		/*
		* ���������� �������� ��������.
		*
		* @param that ������ �������. ������, ������� ������
		* ������� �� �������� �������.
		* @returns ����� ������.
		*/
		Vector operator - (const Vector & that) const;
		/*
		* ���������� ��������� ������� ������� �� ������.
		*
		* @param � ��������, �� ������� ������� �������� ������� ������.
		* @returns ����� ������.
		*/
		Vector operator * (const int x) const;
		/*
		* ���������� ��������� ������� ������� �� ������.
		*
		* @param � ��������, �� ������� ������� �������� ������� ������.
		* @returns ����� ������.
		*/
		Vector operator / (const int x) const;
		/*
		* ���������������(�����) ������������ ��������
		*
		* @param that ������ �������. ������, � ������� ������
		* ��������� ����� ������������ ��������.
		* @returns �����.
		*/
		float Det(const Vector & that) const;
		/*
		* �������������� ������� � ������
		*/
		string toString() const;
	};
	/*
	* �����, ����������� ������������� � ��������� ������������.
	*/
	class Polygon
	{
	protected:
		/*
		* ������������ ������ �����, �� ������� ������� �������������.
		*/
		vector<Vector> vertices;
		/*
		* ������� ��������������� ������� �����
		*
		* @param n �����
		* @returns ������ �������
		*/
		size_t getValidIndex(const int & n) const;
		/*
		* �������� ���������� ������
		*/
		friend ostream & operator << (ostream & os, Polygon p);
	public:
		/*
		* ����������� �� ���������.
		*/
		Polygon();
		/*
		* ������ ������������� � ������� �� ������� array
		* � ����������� ����� count
		*
		* @param a array ������ �����
		* @param b ���������� �����
		*/
		Polygon(Vector * array, size_t count);
		/*
		* ����������� �����������.
		*
		* ������ ������������� �� ������ ��� ������������� ��������������.
		*
		* @param source �������������, �� ������� �������� ������� �������
		* ����� �������������
		*/
		Polygon(const Polygon & source);
		/*
		* �������� ������������.
		*
		* ����������� �������������� �������� �� ������� ��������������.
		*
		* @param that ������ �������. �������������, �� �������� ������� �����
		* �������� ��� �������� ��������������.
		* @returns ������ �� ������� ��������� ������.
		*/
		Polygon & operator = (const Polygon & that);
		/*
		* ��������� ����� � ����� ��������������.
		*
		* @param p ������ ��� �����
		*/
		void addPoint(const Vector & p);
		/*
		* ��������� ����� � �������������.
		*
		* @param i ������ ��� ����������
		* @param p ������ ��� �����
		*/
		void addPoint(int i, const Vector & p);
		/*
		* ������� ��������� ����� �� ��������������.
		*/
		void removePoint();
		/*
		* ������� ����� �� ��������������.
		*
		* @param i ������ �����
		*/
		void removePoint(int i);
		/*
		* ������� ������������� �� �����.
		*/
		void clear();
		/*
		* ������ ����� ��������������.
		*
		* @param i ������ �����
		* @param p ������ ��� �����
		*/
		virtual void setPoint(int i, const Vector & p);
		/*
		* ������ � ����� ��������������.
		*
		* @param i ������ �����
		* @returns ������ ��� �����.
		*/
		virtual Vector getPoint(int i) const;
		/*
		* ���-�� ����� ��������������
		*/
		virtual size_t getPointCount() const;
		/*
		* �������������� �������������� � ������
		*/
		string toString() const;
	};

	/*
	* �����, ����������� ����������� � ��������� ������������.
	*/
	class Triangle : public Polygon
	{
	public:
		/*
		* ���������� ������ ������������
		*/
		const size_t count = 3;
		/*
		* ����������� �� ���������.
		*/
		Triangle();
		/*
		* ����� ����������� ����� ������� �� ������� array.
		* @param a array ������ �����
		*/
		Triangle(Vector * array);
		/*
		* ����� ����������� ������� �1, �2 � �3.
		* @param pi i-�� �����
		*/
		Triangle(const Vector & p1, const Vector & p2, const Vector & p3);
		/*
		* ����������� �����������.
		*
		* ������ ����������� �� ������ ��� ������������� ������������.
		*
		* @param source �����������, �� ������� �������� ������� �������
		* ����� �����������
		*/
		Triangle(const Triangle & source);
		/*
		* �������� ������������.
		*
		* ����������� ������������ �������� �� ������� ������������.
		*
		* @param that ������ �������. �����������, �� �������� ������� �����
		* �������� ��� �������� ������������.
		* @returns ������ �� ������� ��������� ������.
		*/
		Triangle & operator = (const Triangle & that);
	};
}