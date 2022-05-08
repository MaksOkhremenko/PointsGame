#include "Point.h"

Point::Point()
	:
	owner{ NONE }
{}

void Point::setOwner(owners a)
{
	owner = a;
}

Point::owners Point::getOwner()
{
	return owner;
}

void Point::setIsChecked(bool isChecked)
{
	this->isChecked = isChecked;
}

void Point::setIsCaptured(bool isCaptured)
{
	this->isCaptured = isCaptured;
}

bool Point::getIsChecked()
{
	return isChecked;
}

bool Point::getIsCaptured()
{
	return isCaptured;
}

