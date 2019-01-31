// Описание в triangle.cpp

#pragma once
#include <polygon.h>

namespace earclipping_triangulation
{
	/*
	* Класс, описывающий треугольник в двумерном пространстве.
	*/
	class Triangle : public Polygon
	{
	public:
		/*
		* Количество вершин треугольника
		*/
		const size_t count = 3;
		/*
		* Конструктор по умолчанию.
		*/
		Triangle();
		/*
		* Задаёт треугольник тремя точками из массива array.
		* @param a array массив точек
		*/
		Triangle(Vector * array);
		/*
		* Задаёт треугольник точками р1, р2 и р3.
		* @param pi i-ая точка
		*/
		Triangle(const Vector & p1, const Vector & p2, const Vector & p3);
		/*
		* Конструктор копирования.
		*
		* Создаёт треугольник на основе уже существующего треугольника.
		*
		* @param source треугольник, на совнове которого следует создать
		* новый треугольник
		*/
		Triangle(const Triangle & source);
		/*
		* Оператор присваивания.
		*
		* Присваивает теругольнику значения из другого теругольника.
		*
		* @param that второй операнд. теругольник, из которого следует взять
		* значения для текущего теругольника.
		* @returns ссылку на текущий экземпляр класса.
		*/
		Triangle & operator = (const Triangle & that);
	};
}