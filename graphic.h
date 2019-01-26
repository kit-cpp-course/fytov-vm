#pragma once
#include <console.h>
#include <SFML/Graphics.hpp>

namespace earclipping_triangulation
{
	//
	// --- GRAPHIC MODE ---
	//
	class GraphicMode
	{
	public:
		// Window size
		static size_t window_width, window_height;
		// Main window
		static sf::RenderWindow window;
		// Центр окна
		static sf::Vector2f windowCenter;
		// Font
		static sf::Font font;
		// Радиус вершин
		static float vertexRadius;
		// Рисующийся многоугольник
		static sf::ConvexShape drawingPoly;
		// Толщина линий
		static float lineThickness;
		// Цвет линий
		static sf::Color lineColor;
		// Цвет многоугольника
		static sf::Color polygonColor;
		// Цвет окна
		static sf::Color windowColor;
		/// Strings
		static size_t characterSize;
		static sf::Text text1;
		static sf::Text text2;
		static sf::Text text3;
		static sf::Text text4;
		static sf::Text text_error;
		static sf::Color textColor;
		// Происходит ли триангуляция по шагам
		static bool triangulatingStepByStep;
		// Многоугольник для триангуляции по шагам
		static Polygon updatedPoly;
		// Треугольники для триангуляции по шагам
		static vector<Triangle> updatedTriangles;
		// Вершина на данный момент для триангуляции по шагам
		static size_t currentVertex;
		// Время(мс) между триангуляциями по шагам
		static sf::Time tsbs_time;
		// SFML часы
		static sf::Clock sfmlClock;

		// Режим графического окна
		static int activate();

		// Прорисовка окна
		static void draw();

		// Прорисовка треугольников
		static void drawTriangles();

		// Очистка от многоугольника
		static void clear();

		// Создает многоугольник из sfml ConvexShape
		static Polygon fromSFMLConvexShape(const sf::ConvexShape & shape);

		// Создает sfml ConvexShape из многоугольника
		static sf::ConvexShape toSFMLConvexShape(const Polygon & shape);
	};

	// Window size
	size_t GraphicMode::window_width = 800, GraphicMode::window_height = 600;
	// Main window
	sf::RenderWindow GraphicMode::window;
	// Центр окна
	sf::Vector2f GraphicMode::windowCenter(sf::Vector2f(800 / 2.F, 600 / 2.F));
	// Font
	sf::Font GraphicMode::font;
	// Радиус вершин
	float GraphicMode::vertexRadius = 3;
	// Рисующийся многоугольник
	sf::ConvexShape GraphicMode::drawingPoly;
	// Толщина линий
	float GraphicMode::lineThickness = 1.0F;
	// Цвет линий
	sf::Color GraphicMode::lineColor = sf::Color::White;
	// Цвет многоугольника
	sf::Color GraphicMode::polygonColor = sf::Color::Black;
	// Цвет окна
	sf::Color GraphicMode::windowColor = sf::Color::Black;
	/// Strings
	size_t GraphicMode::characterSize = 16;
	sf::Text GraphicMode::text1("Click to set polygon points", font, characterSize);
	sf::Text GraphicMode::text2("Press key C to clear polygon", font, characterSize);
	sf::Text GraphicMode::text3("Press key T to triangulate polygon", font, characterSize);
	sf::Text GraphicMode::text4("Press key R to see how polygon is triangulating", font, characterSize);
	sf::Text GraphicMode::text_error("", font, characterSize + characterSize / 2);
	sf::Color GraphicMode::textColor = sf::Color::White;
	// Происходит ли триангуляция по шагам
	bool GraphicMode::triangulatingStepByStep = false;
	// Многоугольник для триангуляции по шагам
	Polygon GraphicMode::updatedPoly;
	// Треугольники для триангуляции по шагам
	vector<Triangle> GraphicMode::updatedTriangles;
	// Вершина на данный момент для триангуляции по шагам
	size_t GraphicMode::currentVertex;
	// Время(мс) между триангуляциями по шагам
	sf::Time GraphicMode::tsbs_time = sf::milliseconds(500);
	// SFML часы
	sf::Clock GraphicMode::sfmlClock;

	//
	//
	//  IMPLEMENTATION
	//
	//

	int GraphicMode::activate()
	{
		// Загрузка шрифта из resource
		if (!font.loadFromFile("resources/arial.ttf"))
			return EXIT_FAILURE;

		cout << "\n--- GRAPHIC MODE ---\n";

		window.create(sf::VideoMode(window_width, window_height), "Triangulation ear clipping. Graphic mode");

		// Menu characterSize
		text1.setPosition(sf::Vector2f(0, window_height - characterSize * 5));
		text2.setPosition(sf::Vector2f(0, window_height - characterSize * 4));
		text3.setPosition(sf::Vector2f(0, window_height - characterSize * 3));
		text4.setPosition(sf::Vector2f(0, window_height - characterSize * 2));
		text2.setFillColor(textColor);
		text3.setFillColor(textColor);
		text4.setFillColor(textColor);

		// Error
		text_error.setFillColor(sf::Color::Red);
		text_error.setStyle(text_error.Bold);
		text_error.setPosition(windowCenter);

		drawingPoly.setOutlineColor(lineColor);
		drawingPoly.setOutlineThickness(lineThickness);
		drawingPoly.setFillColor(polygonColor);

		drawingPoly = toSFMLConvexShape(polygon);

		// Прорисовка окна
		draw();

		// Покажем многоугольник на данный момент в консоли
		ConsoleMode::showPolygon();

		// Основной цикл
		while (window.isOpen())
		{
			// Process events
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Закрыть окно: выход
				if (event.type == sf::Event::Closed)
					window.close();

				//
				//  MouseButtonPressed
				//
				if (event.type == sf::Event::MouseButtonPressed && !triangulatingStepByStep)
				{
					// Очистка, если была триангуляция или ошибка
					if (!triangles.empty() || text_error.getString() != "")
					{
						clear();
					}

					// Создание точки
					drawingPoly.setPointCount(drawingPoly.getPointCount() + 1);
					drawingPoly.setPoint(drawingPoly.getPointCount() - 1, sf::Vector2f(sf::Mouse::getPosition(window)));

					// Получаем нарисованный многоугольник
					polygon = fromSFMLConvexShape(drawingPoly);

					// Покажем его и в консоли
					ConsoleMode::showPolygon();

					// Прорисовка окна
					draw();
				}
				//
				//  KeyPressed
				//
				if (event.type == sf::Event::KeyPressed && !triangulatingStepByStep)
				{
					// Триангуляция
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
					{
						// Получаем нарисованный многоугольник
						polygon = fromSFMLConvexShape(drawingPoly);

						// Покажем его и в консоли
						ConsoleMode::showPolygon();

						// Основная функция
						triangles = Triangulation::Triangulate(polygon);

						if (triangles.empty()) text_error.setString("Impossibly to triangulate this polygon");
						else ConsoleMode::showTriangles();
					}
					// Старт триангуляции по шагам
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
					{
						// Подготовка еременных
						updatedPoly = fromSFMLConvexShape(drawingPoly);
						updatedTriangles.clear();
						currentVertex = 0;

						// Состояние триангуляции на первом шаге
						Triangulation::triangulationState ts =
							Triangulation::TriangulateStepByStep(updatedPoly, updatedTriangles, currentVertex);

						if (ts == Triangulation::triangulationState::FAIL
							||
							ts == Triangulation::triangulationState::END)
							text_error.setString("Triangulation step by step failed");
						else
						{
							// Все хорошо: начинаем триангуляцию
							triangulatingStepByStep = true;
							triangles.clear();
							triangles.push_back(updatedTriangles[0]);
							// Сброс таймера
							sfmlClock.restart();
						}
					}
					// Очистка многоугольника
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
					{
						clear();
					}

					// Прорисовка окна
					draw();
				}
			}

			//
			// TriangulationStepByStep
			//
			if (triangulatingStepByStep)
			{
				if (sfmlClock.getElapsedTime() >= tsbs_time)
				{
					if (triangles.empty()) {
						switch (Triangulation::TriangulateStepByStep(updatedPoly, updatedTriangles, currentVertex))
						{
						case Triangulation::triangulationState::CONTINUE:
							triangles.push_back(updatedTriangles.back());
							break;
						case Triangulation::triangulationState::END:
							// Конец триангуляции
							triangulatingStepByStep = false;
							triangles = updatedTriangles;
							// В консоль
							ConsoleMode::showTriangles();
							break;
						case Triangulation::triangulationState::FAIL:
							// Конец триангуляции
							triangulatingStepByStep = false;
							text_error.setString("Triangulation step by step failed");
							break;
						}
					}
					else
					{
						triangles.clear();
					}

					// Перезапуск часов
					sfmlClock.restart();

					// Прорисовка окна
					draw();
				}
			}
		}

		cout << "\n--- CONSOLE MODE ---\n";

		return EXIT_SUCCESS;
	}

	void GraphicMode::draw()
	{
		// Clear screen
		window.clear(windowColor);

		// Draw the poly and triangles
		if (!triangulatingStepByStep)
		{
			// При обычной триангуляции прорисовывается
			// обычный многоугольник
			window.draw(drawingPoly);
			drawTriangles();
			for (size_t i = 0; i < drawingPoly.getPointCount(); i++)
			{
				sf::CircleShape c(vertexRadius);
				c.setFillColor(lineColor);
				c.setPosition(drawingPoly.getPoint(i) - sf::Vector2f(vertexRadius, vertexRadius));
				window.draw(c);
			}
		}
		else
		{
			// При триангуляции по шагам прорисовывается updatedPoly
			sf::ConvexShape cs = toSFMLConvexShape(updatedPoly);
			window.draw(cs);
			drawTriangles();
			for (size_t i = 0; i < cs.getPointCount(); i++)
			{
				sf::CircleShape c(vertexRadius);
				c.setFillColor(lineColor);
				c.setPosition(cs.getPoint(i) - sf::Vector2f(vertexRadius, vertexRadius));
				window.draw(c);
			}
		}

		// Отцентровка текста по середине окна
		text_error.setPosition(windowCenter - sf::Vector2f(text_error.getLocalBounds().width / 2,
			text_error.getCharacterSize() / 2));

		// Draw the string
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		window.draw(text_error);

		// Update the window
		window.display();
	}

	void GraphicMode::drawTriangles()
	{
		for (size_t i = 0; i < triangles.size(); i++)
		{
			sf::ConvexShape c(3);
			/*c.setOutlineColor(lineColor);
			c.setOutlineThickness(lineThickness);*/
			c.setFillColor(sf::Color::Color(rand() % 256, rand() % 256, rand() % 256, 255));
			for (size_t j = 0; j < 3; j++)
			{
				c.setPoint(j, sf::Vector2f(triangles[i].getPoint(j).x, triangles[i].getPoint(j).y));
			}
			window.draw(c);
		}
	}

	void GraphicMode::clear()
	{
		drawingPoly.setPointCount(0);
		text_error.setString("");

		triangles.clear();
		polygon.clear();
		ConsoleMode::showPolygon();
	}

	Polygon GraphicMode::fromSFMLConvexShape(const sf::ConvexShape & shape)
	{
		Polygon poly;
		for (size_t i = 0; i < shape.getPointCount(); i++)
		{
			poly.addPoint(Vector(shape.getPoint(i).x, shape.getPoint(i).y));
		}
		return poly;
	}

	sf::ConvexShape GraphicMode::toSFMLConvexShape(const Polygon & poly)
	{
		sf::ConvexShape shape;
		shape.setPointCount(poly.getPointCount());
		shape.setOutlineColor(lineColor);
		shape.setOutlineThickness(lineThickness);
		shape.setFillColor(polygonColor);
		for (size_t i = 0; i < poly.getPointCount(); i++)
		{
			shape.setPoint(i, sf::Vector2f(poly.getPoint(i).x, poly.getPoint(i).y));
		}
		return shape;
	}
}