// Описания в classes.cpp

#pragma once
#include <vector>
#include <string>
using namespace std;

namespace earclipping_triangulation 
{
	/*
	* Класс, описывающий вектор в двумерном пространстве.
	*/
	class Vector
	{
		/*
		* Оператор потокового вывода
		*/
		friend ostream & operator << (ostream & os, Vector v);

	public:
		/*
		* Координаты вектора.
		*/
		float x = 0, y = 0;
		/*
		* Конструктор по умолчанию.
		*/
		Vector(float x = 0, float y = 0);
		/*
		* Конструктор копирования.
		*
		* Создаёт вектор на основе уже существующего вектора.
		*
		* @param source вектор, на совнове которого следует создать
		* новый вектор
		*/
		Vector(const Vector & source);
		/*
		* Оператор присваивания.
		*
		* Присваивает вектору значения из другого верктора.
		*
		* @param that второй операнд. Вектор, из которого следует взять
		* значения для текущего вектора.
		* @returns ссылку на текущий экземпляр класса.
		*/
		Vector & operator = (const Vector & that);
		/*
		* Возвращает сумму векторов.
		*
		* @param that второй операнд. Вектор, с которым следет
		* сложить текущий вектор.
		* @returns новый вектор.
		*/
		Vector operator + (const Vector & that) const;
		/*
		* Возвращает разность векторов.
		*
		* @param that второй операнд. Вектор, который следет
		* вычесть из текущего вектора.
		* @returns новый вектор.
		*/
		Vector operator - (const Vector & that) const;
		/*
		* Возвращает результат деления вектора на скаляр.
		*
		* @param х значение, на которое следует умножить текущий вектор.
		* @returns новый вектор.
		*/
		Vector operator * (const int x) const;
		/*
		* Возвращает результат деления вектора на скаляр.
		*
		* @param х значение, на которое следует поделить текущий вектор.
		* @returns новый вектор.
		*/
		Vector operator / (const int x) const;
		/*
		* Псевдоскалярное(косое) произведение векторов
		*
		* @param that второй операнд. Вектор, с которым следет
		* выполнить косое произведение векторов.
		* @returns число.
		*/
		float Det(const Vector & that) const;
		/*
		* Преобразование вектора в строку
		*/
		string toString() const;
	};
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