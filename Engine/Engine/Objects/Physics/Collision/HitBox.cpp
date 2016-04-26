#include "HitBox.hpp"


HitBox::HitBox()
{
	position = &sf::Vector2f(0, 0);	//default position to prevent errors
	feathered = false;
	bottomed = true;
}

HitBox::~HitBox(){}

void HitBox::updatePosition()
{
	hitbox.clear();

	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		hitbox.push_back(*position + polygon[i]);
	}
}

std::vector<sf::Vector2f> HitBox::get()
{
	return hitbox;
}
void HitBox::setPosition(sf::Vector2f& pos)
{
	position = &pos;
	updatePosition();
}

void HitBox::create(const std::vector<sf::Vector2f>& points)
{
	polygon = points;
	
}

void HitBox::create(const float& radius, const int& resolution)
{
	polygon.clear();

	double increment = (2 * 3.1415) / resolution;
	for (unsigned int i = 0; i < resolution; i++)
	{
		polygon.push_back(sf::Vector2f(radius * cos(increment * i), radius * sin(increment * i)));
	}
	updatePosition();
}

void HitBox::create(const sf::Vector2f& dimensions)
{
	polygon.clear();
	polygon.push_back(sf::Vector2f(dimensions.x * -1 / 2, dimensions.y*-1 / 2));
	polygon.push_back(sf::Vector2f(dimensions.x / 2, dimensions.y*-1 / 2));
	polygon.push_back(sf::Vector2f(dimensions.x / 2, dimensions.y / 2));
	polygon.push_back(sf::Vector2f(dimensions.x *-1 / 2, dimensions.y / 2));

	updatePosition();
}

sf::Vector2f HitBox::getPosition()
{
	return *position;
}

void HitBox::move(sf::Vector2f& newPosition)
{
	position = &newPosition;
	hitbox.clear();

	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		hitbox.push_back(*position + polygon[i]);
	}
}

void HitBox::feather(const bool& onoff, const int& amount)
{
	feathered = onoff;
	if (onoff == feathered) //all good
	{
		return;
	}
	for (int i = 0; i < polygon.size(); i++)
	{
		float slope = polygon[i].y / polygon[i].x;
		sf::Vector2f disp = sf::Vector2f(amount, slope*amount);
		if (!onoff) //if its being removed reverse it
		{
			polygon[i] -= disp;
		}
		else
		{
			polygon[i] += disp;
		}
	}

}

bool HitBox::isFeather()
{
	return feathered;
}

bool HitBox::hasBottom()
{
	return bottomed;
}

void HitBox::setHasBottom(const bool& bot)
{
	bottomed = bot;
}
