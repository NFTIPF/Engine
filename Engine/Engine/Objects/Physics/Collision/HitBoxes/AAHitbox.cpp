#include "AAHitbox.hpp"


AAHitbox::AAHitbox()
{
	setType(HitBox::AABB);
}


AAHitbox::~AAHitbox()
{
}

void AAHitbox::setSize(const sf::Vector2f& siz)
{
	size = siz;
	
}

void AAHitbox::setSize(const double& width, const double& height)
{
	size = sf::Vector2f(width, height);
}


void AAHitbox::setCorners(const sf::Vector2f& tl, const sf::Vector2f& br)
{
	size = sf::Vector2f(br.x - tl.x, br.y - tl.y);

	position = sf::Vector2f((tl.x + br.x) / 2, (tl.y + br.y) / 2);
}

std::pair<sf::Vector2f, sf::Vector2f> AAHitbox::getCorners()
{
	findCorners();
	return std::make_pair(TLCorner, BRCorner);
}

sf::Vector2f AAHitbox::getSize()
{
	return size;
}

bool AAHitbox::isPointInside(const sf::Vector2f& point)
{
	findCorners();

	bool inside = false;

	double bounds[4];
	bounds[Top] = TLCorner.y;
	bounds[Bot] = BRCorner.y;
	bounds[Left] = TLCorner.x;
	bounds[Right] = BRCorner.x;

	if (bounds[Top] <= point.y && bounds[Right] >= point.x && bounds[Bot] >= point.y && bounds[Left] <= point.x)
	{
		inside = true;
	}
	return inside;
}


//private

void AAHitbox::findCorners()
{
	TLCorner = sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2);
	BRCorner = sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2);
}