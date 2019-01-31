// �������� � triangulation.cpp

#pragma once
#include <vector.h>
#include <polygon.h>
#include <triangle.h>

namespace earclipping_triangulation
{
	class Triangulation
	{
	private:
		/*
		* ���������� ��� �������� ����������� 
		* ������������������ ��������������
		*/
		static short int direction;
		/*
		* ���� �����.
		*
		* @param n �����.
		* @ returns ���� �����.
		*/
		static short int sign(const float & n);
		/*
		* ���� �����.
		*
		* @param n �����.
		* @ returns ���� �����.
		*/
		static short int sign(const int & n);

	public:
		/*
		* ������������ �������������� ����� "��������� ����".
		*
		* @param poly �������������.
		* @returns ������������ ������ �������������.
		*/
		static vector<Triangle> Triangulate(const Polygon & poly);
		/*
		* ����������� ������ ������ ��������������.
		* 
		* @param poly �������������
		* @returns 1, ���� �� �������. -1, ���� ������. ����� 0.
		*/
		static short int vectorsDirection(const Polygon & poly);
		/*
		* �������� ����� �� ����������.
		*
		* @param poly �������������.
		* @param i ������ ������� ��������������.
		* @param dir ����������� ������ ������ ��������������
		* @returns true, ���� i-�� ������� ��������, ����� false
		*/
		static bool isConvex(const Polygon & poly, size_t i, const short int & dir = NULL);
		/*
		* ��������� �� ����� ������ ������������.
		*
		* @param p ������ ��� �����.
		* @param t �����������.
		* @returns true, ���� ����� ��������� ������ ������������, ����� false.
		*/
		static bool inTriangle(const Vector & p, const Triangle & t);
		/*
		* ��������� �� i-� ������� �������������� ������ ������������.
		*
		* @param poly �������������.
		* @param t �����������.
		* @param i ������ �������.
		* @returns true, ���� ������� ��������� ������ ������������, ����� false.
		*/
		static bool inTriangle(const Polygon & poly, const Triangle & t, size_t i);
		/*
		* �������� �� i-�� ������ �������������� ����.
		*
		* @param poly �������������
		* @param i ������ �������.
		* @param dir ����������� ������ ������ ��������������
		* @returns true, ���� ������� �������� ����, ����� false.
		*/
		static bool isEar(const Polygon & poly, size_t i, const short int & dir = NULL);
		/*
		* ��������� ���������������� �� �����
		*/
		enum triangulationState { CONTINUE, END, FAIL };
		/*
		* ������������ �������������� ����� "��������� ����".
		* ���������� ��������.
		*
		* @param poly �������������, ������� ����������� � ��������.
		* @param triangles ������������ ������ �������������, 
		* ������� ����������� � ��������.
		* @param currentVertex �������, ��������������� � ��������.
		* @returns ��������� ������������.
		*/
		static triangulationState TriangulateStepByStep(Polygon & poly, vector<Triangle> & triangles, size_t & currentVertex);
	};
}