// �������� � polygon.cpp

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <vector.h> // ������ � ��������� ������������.
using namespace std;

namespace earclipping_triangulation
{
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
}