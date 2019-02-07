// ќписание в vector.cpp

#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace earclipping_triangulation
{
	/*
	*  ласс, описывающий вектор в двумерном пространстве.
	*/
	class Vector
	{
		/*
		* ќператор потокового вывода
		*/
		friend ostream & operator << (ostream & os, Vector v);

	public:
		/*
		*  оординаты вектора.
		*/
		float x = 0, y = 0;
		/*
		*  онструктор по умолчанию.
		*/
		Vector(float x = 0, float y = 0);
		/*
		*  онструктор копировани€.
		*
		* —оздаЄт вектор на основе уже существующего вектора.
		*
		* @param source вектор, на совнове которого следует создать
		* новый вектор
		*/
		Vector(const Vector & source);
		/*
		* ќператор присваивани€.
		*
		* ѕрисваивает вектору значени€ из другого верктора.
		*
		* @param that второй операнд. ¬ектор, из которого следует вз€ть
		* значени€ дл€ текущего вектора.
		* @returns ссылку на текущий экземпл€р класса.
		*/
		Vector & operator = (const Vector & that);
		/*
		* ¬озвращает сумму векторов.
		*
		* @param that второй операнд. ¬ектор, с которым следет
		* сложить текущий вектор.
		* @returns новый вектор.
		*/
		Vector operator + (const Vector & that) const;
		/*
		* ¬озвращает разность векторов.
		*
		* @param that второй операнд. ¬ектор, который следет
		* вычесть из текущего вектора.
		* @returns новый вектор.
		*/
		Vector operator - (const Vector & that) const;
		/*
		* ¬озвращает результат делени€ вектора на скал€р.
		*
		* @param х значение, на которое следует умножить текущий вектор.
		* @returns новый вектор.
		*/
		Vector operator * (const int x) const;
		/*
		* ¬озвращает результат делени€ вектора на скал€р.
		*
		* @param х значение, на которое следует поделить текущий вектор.
		* @returns новый вектор.
		*/
		Vector operator / (const int x) const;
		/*
		* ѕсевдоскал€рное(косое) произведение векторов
		*
		* @param that второй операнд. ¬ектор, с которым следет
		* выполнить косое произведение векторов.
		* @returns число.
		*/
		float Det(const Vector & that) const;
		/*
		* ѕреобразование вектора в строку
		*/
		string toString() const;
	};
}