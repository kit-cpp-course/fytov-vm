#include "stdafx.h"
#include "triangulation.h"

namespace earclipping_triangulation
{
	short int Triangulation::sign(const float & n) { return (0 < n) - (n < 0); }
	short int Triangulation::sign(const int & n) { return (0 < n) - (n < 0); }
	/*
	* ������������ �������������� ����� "��������� ����".
	*
	* @param poly �������������.
	* @returns ������������ ������ �������������.
	*/
	vector<Triangle> Triangulation::Triangulate(const Polygon & poly)
	{
		//�������� ����������� ��������������
		short int direction = vectorsDirection(poly);

		///���� ����������� ����� 0, �� ������������� - ������, 
		///������� ��������������� ����������
		if (direction == 0) return vector<Triangle>();

		//���������
		vector<Triangle> res;

		//�������, ������� ����� ���������� ����������� 
		//��-�� �������� ������
		Polygon updatedPoly(poly);

		//������� ��������������� �� ������ ������
		size_t curVertex = 0;

		//���������� ������������� ������
		size_t steppedVertices = 0;

		///����, ���� �� ��� ���, ���� ������� updatedPoly
		///�� ����������� � �����������(���������)
		while (updatedPoly.getPointCount() > 3)
		{
			///��������, � �� �������� �� ������� curVertex ����?
			///�� ����������� ������� �������� ����������� 
			///�������������� - Direction
			if (isEar(updatedPoly, curVertex, direction))
			{
				///������� ����������� � ���������
				res.push_back(Triangle(updatedPoly.getPoint(curVertex + updatedPoly.getPointCount() - 1),
					updatedPoly.getPoint(curVertex),
					updatedPoly.getPoint(curVertex + 1)));

				///������ ������� curVertex �� updatedPoly
				updatedPoly.removePoint(curVertex);

				///�������� ������ ������������� �������
				steppedVertices = 0;
			}
			///����� ���������� ������������� ������ �������������
			else steppedVertices++;

			///���� ����� ���� ������������� ������ �� ��������
			///"����", �� �� �� ����� ��������������� �������������
			if (steppedVertices == updatedPoly.getPointCount()) return vector<Triangle>();

			///��������� � ��������� �������
			if (++curVertex >= updatedPoly.getPointCount())curVertex = 0;
		}

		///� ����� � ��� ������� ��������� �����������, ���
		///���������� ��� �������� � ���������
		res.push_back(Triangle(updatedPoly.getPoint(0), updatedPoly.getPoint(1), updatedPoly.getPoint(2)));

		///������� ����������
		return res;
	}

	short int Triangulation::vectorsDirection(const Polygon & poly)
	{
		///���������� ��������������� ������� ��������������
		float s = 0;
		for (size_t i = 0; i < poly.getPointCount(); i++)
		{
			s += poly.getPoint(i).Det(poly.getPoint(i + 1)) / 2;///������� ������������
		}
		///� ��������� ���� ���� �������
		return sign(s);
	}

	bool Triangulation::isConvex(const Polygon & poly, size_t i, const short int & dir)
	{
		///��������� �� ����������� ������ ������������
		///� ������������ ������ ��������������.
		Triangle t(poly.getPoint(i - 1), poly.getPoint(i), poly.getPoint(i + 1));
		if (dir) return vectorsDirection(t) == dir;
		else return vectorsDirection(t) == vectorsDirection(poly);
	}

	bool Triangulation::inTriangle(const Vector & p, const Triangle & t)
	{
		///��������� ����� ������������ ��������
		float det1 = (p - t.getPoint(0)).Det(t.getPoint(1) - t.getPoint(0));
		float det2 = (p - t.getPoint(1)).Det(t.getPoint(2) - t.getPoint(1));
		float det3 = (p - t.getPoint(2)).Det(t.getPoint(0) - t.getPoint(2));

		///���� ��� ��� ���� �������� ����������������,
		///��  �����(x,y) ������ ������������
		if ((sign(det1) == sign(det2)) && (sign(det2) == sign(det3))) return true;
		else return false;
	}

	bool Triangulation::inTriangle(const Polygon & poly, const Triangle & t, size_t i)
	{
		return inTriangle(poly.getPoint(i), t);
	}

	bool Triangulation::isEar(const Polygon & poly, size_t i, const short int & dir)
	{
		/// ���� �������� ������� Vi, ���� ��������� Vi-1 Vi+1 
		/// ����� ������ �� ���������� ������� ��������

		//�����������
		Triangle t(poly.getPoint(i - 1), poly.getPoint(i), poly.getPoint(i + 1));

		///�������� �� ������� ����� ������ ������������.
		///������� ��� �������, ����� 3-� ������ ������������
		for (size_t j = 0; j < poly.getPointCount() - 3; j++)
			/// ���� ���� ���� ������� ������������ � ������������, 
			/// ������� false � �����
			if (inTriangle(poly.getPoint(i + j + 2), t)) return false;

		///�������� �� ���������� �������
		if (!isConvex(poly, i, dir)) return false;

		///� ������ ������ ����� �������, ��� ������� i �������� ����
		return true;
	}

	Triangulation::triangulationState 
		Triangulation::TriangulateStepByStep(Polygon & poly, vector<Triangle> & triangles, size_t & currentVertex)
	{
		///���� � �������������� ������ ��� �����,
		///�� ����� ������������
		if (poly.getPointCount() == 0) return END;

		//�������� ����������� ��������������
		short int direction = vectorsDirection(poly);

		///���� ����������� ����� 0, �� ������������� - ������, 
		///������� ��������������� ����������
		if (direction == 0) return FAIL;

		//���������� ������������� ������
		size_t steppedVertices = 0;

		///���� ������������� ��� �� �����������
		if (poly.getPointCount() > 3)
		{
			///������ ���
			while (!isEar(poly, currentVertex, direction))
			{
				currentVertex++;
				steppedVertices++;
				///���� ��� �� �������, �� �� �� ����� 
				///��������������� �������������
				if (steppedVertices == poly.getPointCount()) return FAIL;
			}
			///������� ����������� � ���������
			triangles.push_back(Triangle(poly.getPoint(currentVertex - 1),
				poly.getPoint(currentVertex),
				poly.getPoint(currentVertex + 1)));

			///������ ������� curVertex �� poly
			poly.removePoint(currentVertex);

			///��������� � ��������� �������
			if (++currentVertex >= poly.getPointCount())currentVertex = 0;
		}
		///���� ������������� ��� �����������
		else
		{
			///���������� ��� �������� � ���������
			triangles.push_back(Triangle(poly.getPoint(0), poly.getPoint(1), poly.getPoint(2)));

			///������  poly
			poly.clear();
		}

		///��� �� ����� ������������ ������, ���
		///����� ����� � �������������� ��� �����
		return CONTINUE;
	}
}