#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

struct Curve {
	vector<vector<Vertex>> vertices;
	int NumberOfVertices = 0;
};

int main()
{
	Vector2i mousePos;
	vector<Curve> curves(1);
	vector<Vertex> points;
	RenderWindow window(sf::VideoMode(1000, 1000), "BEZIE");
	Event event;

	Image heroimage;
	heroimage.loadFromFile("morgen.png");

	Texture herotexture;
	herotexture.loadFromImage(heroimage);

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setPosition(0, 0);

	while (window.isOpen())
	{
		window.clear();
		window.draw(herosprite);
		while (window.pollEvent(event)) 
		{
			mousePos = Mouse::getPosition(window);

			if (event.type == Event::Closed) window.close();

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) 
			{
				curves[curves.size() - 1].NumberOfVertices++;
				curves[curves.size() - 1].vertices.clear();

				Vertex tempPoint;
				tempPoint.position.x = mousePos.x;
				tempPoint.position.y = mousePos.y;

				points.push_back(tempPoint);
				curves[curves.size() - 1].vertices.push_back(points);
				for (int i = curves[curves.size() - 1].NumberOfVertices - 1; i > 0; --i) 
				{
					vector<Vertex> temp;
					for (int j = i; j > 0; --j) 
					{
						Vertex emptyVertex;
						temp.push_back(emptyVertex);
					}
					curves[curves.size() - 1].vertices.push_back(temp);
				}
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Right) 
			{
				Curve newCurve;
				points.clear();
				points.push_back(curves[curves.size() - 1].vertices[0][curves[curves.size() - 1].NumberOfVertices - 1]);
				newCurve.vertices.push_back(points);
				newCurve.NumberOfVertices++;
				curves.push_back(newCurve);
			}
		}

		for (auto& curve : curves) 
		{
			if (curve.NumberOfVertices > 0) 
			{
				for (double i = 0; i <= 1.; i += 0.0001) 
				{
					for (int j = 0; j < curve.vertices.size() - 1; ++j) 
					{
						for (int k = 0; k < curve.vertices[j].size() - 1; ++k) 
						{
							curve.vertices[j + 1][k].position.x = curve.vertices[j][k].position.x +(curve.vertices[j][k + 1].position.x - curve.vertices[j][k].position.x)*i;
							curve.vertices[j + 1][k].position.y = curve.vertices[j][k].position.y + (curve.vertices[j][k + 1].position.y - curve.vertices[j][k].position.y) * i;
						}
					}
					curve.vertices[curve.vertices.size() - 1][0].color = Color::Red;
					window.draw(&curve.vertices[curve.vertices.size() - 1][0], 10, Points);
				}
			}
		}
		window.display();
	}

	return 0;
}
