// �������� � vector.cpp

#pragma once
#include <iostream>
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
}