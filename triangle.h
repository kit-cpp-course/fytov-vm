// �������� � triangle.cpp

#pragma once
#include <polygon.h>

namespace earclipping_triangulation
{
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