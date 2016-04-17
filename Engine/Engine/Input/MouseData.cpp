#include "MouseData.hpp"


MouseData::MouseData()
{
	leftButtonData = Unheld;
	rightButtonData = Unheld;
	position = sf::Vector2f(0, 0);
	oldPosition = sf::Vector2f(0, 0);
	scrollDelta = 0;

}


MouseData::~MouseData()
{
}

void MouseData::setLeftData(const unsigned int& state)
{
	leftButtonData = state;
}

void MouseData::setRightData(const unsigned int& state)
{
	rightButtonData = state;
}

void MouseData::setButtonData(const unsigned int& stateLeft, const unsigned int& stateRight)
{
	leftButtonData = stateLeft;
	rightButtonData = stateRight;
}

void MouseData::setPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void MouseData::move(const sf::Vector2f& dist)
{
	position += dist;
}

void MouseData::setScroll(const int& scrollDel)
{
	scrollDelta = scrollDel;
}


unsigned int MouseData::getLeftData()
{
	return leftButtonData;
}

unsigned int MouseData::getRightData()
{
	return rightButtonData;
}

sf::Vector2f MouseData::getPosition()
{
	return position;
}

sf::Vector2f MouseData::getPositionChange()
{
	return position - oldPosition;
}

int MouseData::getScroll()
{
	return scrollDelta;
}

void MouseData::frameUpdate()
{
	oldPosition = position;


	if (leftButtonData == Hit)
	{
		leftButtonData = Held;
	}
	else if (leftButtonData == Released)
	{
		leftButtonData = Unheld;
	}


	if (rightButtonData == Hit)
	{
		rightButtonData = Held;
	}
	else if (leftButtonData == Released)
	{
		rightButtonData = Unheld;
	}

	scrollDelta = 0;
}