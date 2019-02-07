// Описание в polygon.cpp

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <vector.h> // вектор в двумерном пространстве.
using namespace std;

namespace earclipping_triangulation
{
	/*
	* Класс, описывающий многоугольник в двумерном пространстве.
	*/
	class Polygon
	{
	protected:
		/*
		* Динамический массив точек, из которых состоит многоугольник.
		*/
		vector<Vector> vertices;
		/*
		* Возврат действительного индекса точки
		*
		* @param n число
		* @returns индекс вершины
		*/
		size_t getValidIndex(const int & n) const;
		/*
		* Оператор потокового вывода
		*/
		friend ostream & operator << (ostream & os, Polygon p);
	public:
		/*
		* Конструктор по умолчанию.
		*/
		Polygon();
		/*
		* Задает многоугольник с точками из массива array
		* с количеством точек count
		*
		* @param a array массив точек
		* @param b количество точек
		*/
		Polygon(Vector * array, size_t count);
		/*
		* Конструктор копирования.
		*
		* Создаёт многоугольник на основе уже существующего многоугольника.
		*
		* @param source многоугольник, на совнове которого следует создать
		* новый многоугольник
		*/
		Polygon(const Polygon & source);
		/*
		* Оператор присваивания.
		*
		* Присваивает многоугольнику значения из другого многоугольника.
		*
		* @param that второй операнд. многоугольник, из которого следует взять
		* значения для текущего многоугольника.
		* @returns ссылку на текущий экземпляр класса.
		*/
		Polygon & operator = (const Polygon & that);
		/*
		* Добавляет точку в конец многоугольника.
		*
		* @param p вектор как точка
		*/
		void addPoint(const Vector & p);
		/*
		* Добавляет точку в многоугольник.
		*
		* @param i индекс для добавления
		* @param p вектор как точка
		*/
		void addPoint(int i, const Vector & p);
		/*
		* Удаляет последнюю точку из многоугольника.
		*/
		void removePoint();
		/*
		* Удаляет точку из многоугольника.
		*
		* @param i индекс точки
		*/
		void removePoint(int i);
		/*
		* Очищает многоугольник от точек.
		*/
		void clear();
		/*
		* Задает точку многоугольника.
		*
		* @param i индекс точки
		* @param p вектор как точка
		*/
		virtual void setPoint(int i, const Vector & p);
		/*
		* Доступ к точке многоугольника.
		*
		* @param i индекс точки
		* @returns вектор как точка.
		*/
		virtual Vector getPoint(int i) const;
		/*
		* Кол-во точек многоугольника
		*/
		virtual size_t getPointCount() const;
		/*
		* Преобразование многоугольника в строку
		*/
		string toString() const;
	};
}