#pragma once
#include <triangulation.h>

namespace earclipping_triangulation
{
	// Многоугольник
	Polygon polygon;

	// Треугольники
	vector<Triangle> triangles;

	//
	// --- CONSOLE MODE ---
	//
	class ConsoleMode
	{
	public:

		// Показать меню
		static void showMenu();

		// Показать многоугольник
		static void showPolygon();

		// Показать треугольники
		static void showTriangles();

		// Создать многоугольник
		static void createPolygon();

		// Получить координаты от пользователя
		static void getPointCoords(float & x, float & y);

		// Добавить точку
		static void addPoint();

		// Удалить точку
		static void removePoint();

		// Заменить точку
		static void replacePoint();
	};

	//
	//
	//  IMPLEMENTATION
	//
	//

	void ConsoleMode::showMenu()
	{
		cout << "\n1 - Create new polygon\n";
		cout << "2 - Show current polygon\n";
		cout << "3 - Add point to current polygon\n";
		cout << "4 - Remove point from current polygon\n";
		cout << "5 - Replace point of current polygon\n";
		cout << "6 - Triangulate current polygon\n";
		cout << "7 - exit\n";
	}

	void ConsoleMode::showPolygon()
	{
		cout << "\nPolygon have " << polygon.getPointCount() << " points.\n";
		cout << polygon;
	}

	void ConsoleMode::showTriangles()
	{
		cout << "\nTriangles:\n";
		for (size_t i = 0; i < triangles.size(); i++)
		{
			cout << "Triangle" << i + 1 << ":\n";
			cout << triangles[i];
		}
		cout << "Total triangles count: " << triangles.size() << endl;
	}

	void ConsoleMode::createPolygon()
	{
		int n;
		float x, y;
		cout << "Start creating polygon. Enter number of points: ";
		polygon.clear();
		cin >> n;
		for (size_t i = 0; i < n; i++)
		{
			cout << "Enter coordinates of Point" << i + 1 << ":\n";
			cout << "X: ";
			cin >> x;
			cout << "Y: ";
			cin >> y;
			polygon.addPoint(Vector(x, y));
		}
		showPolygon();
	}

	void ConsoleMode::getPointCoords(float & x, float & y)
	{
		cout << "X: ";
		cin >> x;
		cout << "Y: ";
		cin >> y;
	}

	void ConsoleMode::addPoint()
	{
		int n;
		float x, y;
		cout << "Enter point number to insert, 0 - to add to end, -1 to cancel: ";
		cin >> n;
		if (n == 0)
		{
			cout << "Enter coordinates of Point:\n";
			getPointCoords(x, y);
			polygon.addPoint(Vector(x, y));
		}
		else if (n > 0)
		{
			cout << "Enter coordinates of Point" << (n - 1) % polygon.getPointCount() + 1 << ":\n";
			getPointCoords(x, y);
			polygon.addPoint(n - 1, Vector(x, y));
		}
		showPolygon();
	}

	void ConsoleMode::removePoint()
	{
		int n;
		cout << "Enter point number, 0 - to remove last, -1 to cancel: ";
		cin >> n;
		if (n == 0)	polygon.removePoint();
		else if (n > 0)polygon.removePoint(n - 1);
		showPolygon();
	}

	void ConsoleMode::replacePoint()
	{
		int n;
		do
		{
			cout << "Enter point number(0 to cancel): ";
			cin >> n;
			if (n > polygon.getPointCount() && n != 0) cout << "Incorrect number of point. Retry:\n";
		} while (n > polygon.getPointCount() && n != 0);

		if (n > 0) 
		{
			float x, y;
			cout << "Enter new coordinates of Point:\n";
			getPointCoords(x, y);
			polygon.setPoint(n - 1, Vector(x, y));
		}
		showPolygon();
	}
}