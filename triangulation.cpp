#include "stdafx.h"
#include "triangulation.h"

namespace earclipping_triangulation
{
	short int Triangulation::sign(const float & n) { return (0 < n) - (n < 0); }
	short int Triangulation::sign(const int & n) { return (0 < n) - (n < 0); }
	/*
	* Триангуляция многоугольника через "отрезание ушей".
	*
	* @param poly многоугольник.
	* @returns динамический массив треугольников.
	*/
	vector<Triangle> Triangulation::Triangulate(const Polygon & poly)
	{
		//Основное направление многоугольника
		short int direction = vectorsDirection(poly);

		///Если направление равно 0, то многоугольник - прямая, 
		///которую триангулировать невозможно
		if (direction == 0) return vector<Triangle>();

		//Результат
		vector<Triangle> res;

		//Полигон, который будет постепенно уменьшаться 
		//из-за удаления вершин
		Polygon updatedPoly(poly);

		//Вершина рассматриваемая на данный момент
		size_t curVertex = 0;

		//Количество просмотренных вершин
		size_t steppedVertices = 0;

		///Итак, цикл до тех пор, пока полигон updatedPoly
		///не превратится в треугольник(последний)
		while (updatedPoly.getPointCount() > 3)
		{
			///Проверим, а не является ли вершина curVertex ухом?
			///За направление выберем основное направление 
			///многоугольника - Direction
			if (isEar(updatedPoly, curVertex, direction))
			{
				///Добавим треугольник в результат
				res.push_back(Triangle(updatedPoly.getPoint(curVertex + updatedPoly.getPointCount() - 1),
					updatedPoly.getPoint(curVertex),
					updatedPoly.getPoint(curVertex + 1)));

				///Удалим вершину curVertex из updatedPoly
				updatedPoly.removePoint(curVertex);

				///Начинаем заново просматривать вершины
				steppedVertices = 0;
			}
			///Иначе количество просмотренных вершин увеличивается
			else steppedVertices++;

			///Если среди всех просмотренных вершин не осталось
			///"ушей", то мы не можем триангулировать многоугольник
			if (steppedVertices == updatedPoly.getPointCount()) return vector<Triangle>();

			///Переходим к следующей вершине
			if (++curVertex >= updatedPoly.getPointCount())curVertex = 0;
		}

		///И когда у нас остался последний треугольник, нам
		///необходимо его добавить в результат
		res.push_back(Triangle(updatedPoly.getPoint(0), updatedPoly.getPoint(1), updatedPoly.getPoint(2)));

		///Возврат результата
		return res;
	}

	short int Triangulation::vectorsDirection(const Polygon & poly)
	{
		///Подсчитаем ориентированную площадь многоугольника
		float s = 0;
		for (size_t i = 0; i < poly.getPointCount(); i++)
		{
			s += poly.getPoint(i).Det(poly.getPoint(i + 1)) / 2;///Площадь треугольника
		}
		///И возвратим знак этой площади
		return sign(s);
	}

	bool Triangulation::isConvex(const Polygon & poly, size_t i, const short int & dir)
	{
		///Совпадает ли направление обхода треугольника
		///с направлением обхода многоугольника.
		Triangle t(poly.getPoint(i - 1), poly.getPoint(i), poly.getPoint(i + 1));
		if (dir) return vectorsDirection(t) == dir;
		else return vectorsDirection(t) == vectorsDirection(poly);
	}

	bool Triangulation::inTriangle(const Vector & p, const Triangle & t)
	{
		///Вычисляем косые произведения векторов
		float det1 = (p - t.getPoint(0)).Det(t.getPoint(1) - t.getPoint(0));
		float det2 = (p - t.getPoint(1)).Det(t.getPoint(2) - t.getPoint(1));
		float det3 = (p - t.getPoint(2)).Det(t.getPoint(0) - t.getPoint(2));

		///Если все три пары векторов однонаправленные,
		///то  точка(x,y) внутри треугольника
		if ((sign(det1) == sign(det2)) && (sign(det2) == sign(det3))) return true;
		else return false;
	}

	bool Triangulation::inTriangle(const Polygon & poly, const Triangle & t, size_t i)
	{
		return inTriangle(poly.getPoint(i), t);
	}

	bool Triangulation::isEar(const Polygon & poly, size_t i, const short int & dir)
	{
		/// Ухом является вершина Vi, если диагональ Vi-1 Vi+1 
		/// лежит строго во внутренней области полигона

		//Треугольник
		Triangle t(poly.getPoint(i - 1), poly.getPoint(i), poly.getPoint(i + 1));

		///Проверка на наличие точек внутри треугольника.
		///Обходим все вершины, кроме 3-х вершин треугольника
		for (size_t j = 0; j < poly.getPointCount() - 3; j++)
			/// если хоть одна вершина присутствует в треугольнике, 
			/// возврат false и выход
			if (inTriangle(poly.getPoint(i + j + 2), t)) return false;

		///Проверка на выпуклость вершины
		if (!isConvex(poly, i, dir)) return false;

		///И только теперь можно сказать, что вершина i является ухом
		return true;
	}

	Triangulation::triangulationState 
		Triangulation::TriangulateStepByStep(Polygon & poly, vector<Triangle> & triangles, size_t & currentVertex)
	{
		///Если в многоугольнике больше нет точек,
		///то конец триангуляции
		if (poly.getPointCount() == 0) return END;

		//основное направление многоугольника
		short int direction = vectorsDirection(poly);

		///Если направление равно 0, то многоугольник - прямая, 
		///которую триангулировать невозможно
		if (direction == 0) return FAIL;

		//Количество просмотренных вершин
		size_t steppedVertices = 0;

		///Если многоугольник еще не треугольник
		if (poly.getPointCount() > 3)
		{
			///Найдем ухо
			while (!isEar(poly, currentVertex, direction))
			{
				currentVertex++;
				steppedVertices++;
				///Если ухо не найдено, то мы не можем 
				///триангулировать многоугольник
				if (steppedVertices == poly.getPointCount()) return FAIL;
			}
			///Добавим треугольник в результат
			triangles.push_back(Triangle(poly.getPoint(currentVertex - 1),
				poly.getPoint(currentVertex),
				poly.getPoint(currentVertex + 1)));

			///Удалим вершину curVertex из poly
			poly.removePoint(currentVertex);

			///Переходим к следующей вершине
			if (++currentVertex >= poly.getPointCount())currentVertex = 0;
		}
		///Если многоугольник уже треугольник
		else
		{
			///необходимо его добавить в результат
			triangles.push_back(Triangle(poly.getPoint(0), poly.getPoint(1), poly.getPoint(2)));

			///Удалим  poly
			poly.clear();
		}

		///Еще не конец триангуляции потому, что
		///конец когда в многоугольнике нет точек
		return CONTINUE;
	}
}