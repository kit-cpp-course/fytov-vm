// Описания в triangulation.cpp

#pragma once
#include <base_classes.h>

namespace earclipping_triangulation
{
	class Triangulation
	{
	private:
		/*
		* Переменная для хранения направления 
		* триангулирующегося многоугольника
		*/
		static short int direction;
		/*
		* Знак числа.
		*
		* @param n число.
		* @ returns знак числа.
		*/
		static short int sign(const float & n);
		/*
		* Знак числа.
		*
		* @param n число.
		* @ returns знак числа.
		*/
		static short int sign(const int & n);

	public:
		/*
		* Триангуляция многоугольника через "отрезание ушей".
		*
		* @param poly многоугольник.
		* @returns динамический массив треугольников.
		*/
		static vector<Triangle> Triangulate(const Polygon & poly);
		/*
		* Направление обхода вершин многоугольника.
		* 
		* @param poly многоугольник
		* @returns 1, если по часовой. -1, если против. Иначе 0.
		*/
		static short int vectorsDirection(const Polygon & poly);
		/*
		* Проверка точки на выпуклость.
		*
		* @param poly многоугольник.
		* @param i индекс вершины многоугольника.
		* @param dir направление обхода вершин многоугольника
		* @returns true, если i-ая вершина выпуклая, иначе false
		*/
		static bool isConvex(const Polygon & poly, size_t i, const short int & dir = NULL);
		/*
		* Находится ли точка внутри треугольника.
		*
		* @param p вектор как точка.
		* @param t треугольник.
		* @returns true, если точка находится внутри треугольника, иначе false.
		*/
		static bool inTriangle(const Vector & p, const Triangle & t);
		/*
		* Находится ли i-я вершина многоугольника внутри треугольника.
		*
		* @param poly многоугольник.
		* @param t треугольник.
		* @param i индекс вершины.
		* @returns true, если вершина находится внутри треугольника, иначе false.
		*/
		static bool inTriangle(const Polygon & poly, const Triangle & t, size_t i);
		/*
		* Является ли i-ая вершна многоугольника ухом.
		*
		* @param poly многоугольник
		* @param i индекс вершины.
		* @param dir направление обхода вершин многоугольника
		* @returns true, если вершина является ухом, иначе false.
		*/
		static bool isEar(const Polygon & poly, size_t i, const short int & dir = NULL);
		/*
		* Состояние триангулирования по шагам
		*/
		enum triangulationState { CONTINUE, END, FAIL };
		/*
		* Триангуляция многоугольника через "отрезание ушей".
		* Выполнение пошагово.
		*
		* @param poly многоугольник, который уменьшается в процессе.
		* @param triangles динамический массив треугольников, 
		* который заполняется в процессе.
		* @param currentVertex вершина, просматриваемая в процессе.
		* @returns состояние триангуляции.
		*/
		static triangulationState TriangulateStepByStep(Polygon & poly, vector<Triangle> & triangles, size_t & currentVertex);
	};
}