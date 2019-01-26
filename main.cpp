#include <iostream>
#include <vector>
#include <stdafx.h>
// Здесь прописаны классы для работы с триангуляцией,
// такие как Vector, Polygon и Triangle.
#include <base_classes.h>
// Здесь прописан алгоритм триангуляции
#include <triangulation.h>
// Режим консольного управления
#include <console.h>
// Режим графического управления
#include <graphic.h>

using namespace earclipping_triangulation;

//
//
//  MAIN
//
//

int main()
{
	char choice;

	cout << "Do you want to use graphic mode? (y/n)  ";
	cin >> choice;

	if (choice =='y' || choice == 'Y') 
	{
		if (GraphicMode::activate())
		{
			cout << "Cannot use graphic mode. Please, check resource folder.\n";
		}
	}

	do
	{
		//ConsoleMode::showMenu();
		cout << "\n1 - Create new polygon\n";
		cout << "2 - Show current polygon\n";
		cout << "3 - Add point to current polygon\n";
		cout << "4 - Remove point from current polygon\n";
		cout << "5 - Replace point of current polygon\n";
		cout << "6 - Triangulate current polygon\n";
		cout << "7 - exit\n";
		cin >> choice;

		switch (choice)
		{
		case '1':
			ConsoleMode::createPolygon();
			break;

		case '2':
			ConsoleMode::showPolygon();
			break;

		case '3':
			ConsoleMode::addPoint();
			break;

		case '4':
			ConsoleMode::removePoint();
			break;

		case '5':
			ConsoleMode::replacePoint();
			break;

		case '6':
			// Основная функция
			triangles = Triangulation::Triangulate(polygon);

			if (triangles.empty()) cout << "Impossibly to triangulate this polygon.\n";
			else 
			{
				ConsoleMode::showTriangles();
				cout << "\nDo you want to see result in the graphic mode? (y/n): ";
				cin >> choice;
				if (choice == 'y' || choice == 'Y')
				{
					if (GraphicMode::activate())
					{
						cout << "Cannot use graphic mode. Please, check resource folder.\n";
					}
				}
				choice = '0';
			}

			break;

		case '7':
			break;

		default:
			cout << "Wrong number!\n";
			break;
		}

	} while (choice != '7');

	return 0;
}
