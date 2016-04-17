#pragma once
#include "HitBox.hpp"
class CircularHitbox : public HitBox
{
public:
	CircularHitbox();
	~CircularHitbox();

	void setRadius(const double& rad);
	double getRadius();

	bool isPointInside(const sf::Vector2f& point);

private:

	double radius;
};

