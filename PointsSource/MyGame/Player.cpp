#include "Player.h"
#include "Game.h"
#include <iostream>

Player::Player()
	:
	color { color },
	isMoving{ false },
	chipsCount{ 0 }
{
}

Player::~Player()
{
}

void Player::setColor(sf::Color color)
{
	this->color = color;
}

void Player::setIsMove(bool isMoving)
{
	this->isMoving = isMoving;
}

bool Player::getIsMove()
{
	return isMoving;
}

void Player::addPoint(Point point)
{
	points.push_back(point);
}

void Player::addChipCount(size_t count)
{
	chipsCount += count;
}

void Player::subtractChipCount(size_t count)
{
	if ((int)chipsCount - (int)count >= 0)
		chipsCount -= count;
	else
		chipsCount = 0;
}

const size_t Player::getChipsCount()
{
	return chipsCount;
}

std::list<Point>& Player::getPoints()
{
	return points;
}

std::list<sf::VertexArray>& Player::getChips()
{
	return chipsList;
}

void Player::addChip(sf::VertexArray& vertexArray)
{
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].color = this->color;
	}
	chipsList.push_back(vertexArray);
}

