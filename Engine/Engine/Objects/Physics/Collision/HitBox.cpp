#include "HitBox.hpp"


HitBox::HitBox()
{
	position = sf::Vector2f(0, 0);	//default position to prevent errors
}

HitBox::~HitBox(){}

std::vector<sf::Vector2f> HitBox::get()
{
	return hitbox;

}
void HitBox::setPosition(const sf::Vector2f& pos)
{
	position = pos;
	move(position);
}

void HitBox::setPosition(const double& x, const double& y)
{
	position.x = x;
	position.y = y;
	move(position);
}

void HitBox::create(const std::vector<sf::Vector2f>& points)
{
	polygon = points;
	move(position);	//translate
}

void HitBox::create(const float& radius, const int& resolution)
{
	polygon.clear();

	double increment = (2 * 3.1415) / resolution;
	for (unsigned int i = 0; i < resolution; i++)
	{
		polygon.push_back(sf::Vector2f(radius * cos(increment * i), radius * sin(increment * i)));
	}
	move(position);
}

void HitBox::create(const int& height, const int& width)
{
	polygon.clear();
	polygon.push_back(sf::Vector2f(width * -1 / 2, height*-1 / 2));
	polygon.push_back(sf::Vector2f(width / 2, height / 2));
	polygon.push_back(sf::Vector2f(width *-1 / 2, height / 2));
	polygon.push_back(sf::Vector2f(width / 2, height*-1 / 2));

	move(position);
}

sf::Vector2f HitBox::getPosition()
{
	return position;
}

void HitBox::move(const sf::Vector2f& newPosition)
{
	position = newPosition;
	hitbox.clear();

	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		hitbox[i] += position;
	}
}
