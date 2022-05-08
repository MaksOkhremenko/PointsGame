#pragma once
#include <list>
#include "Point.h"
#include "SFML/Graphics.hpp"

class Player
{
private:
	sf::Color color;
	bool isMoving;
	size_t chipsCount;
	std::list<Point> points;
	std::list<sf::VertexArray> chipsList;
public:
	Player();
	~Player();
	void setColor(sf::Color color);
	void setIsMove(bool isMoving);
	bool getIsMove();
	void addPoint(Point point);
	void addChipCount(size_t count = 1);
	void subtractChipCount(size_t count = 1);
	const size_t getChipsCount();
	std::list<Point>& getPoints();
	std::list<sf::VertexArray>& getChips();
	void addChip(sf::VertexArray& vertexArray);
};

