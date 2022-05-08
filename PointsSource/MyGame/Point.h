#pragma once
#include "SFML/Graphics.hpp"

class Point : public sf::CircleShape
{
public:
	Point();
	enum owners
	{
		RED, BLUE, NONE
	};
	void setOwner(owners a);
	owners getOwner();
	void setIsChecked(bool isChecked);
	void setIsCaptured(bool isCaptured);
	bool getIsChecked();
	bool getIsCaptured();
private:
	bool isChecked = false;
	bool isCaptured = false;
	owners owner;
};

