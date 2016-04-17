#pragma once
#include <SFML\Graphics.hpp>
#include "HitBox.hpp"

class CollisionData
{
public:
	CollisionData();
	CollisionData(bool, HitBox&);
	~CollisionData();

	bool collided();

	HitBox* getCollidedHitbox();

	std::vector<sf::Vector2f> getCollisionPoints();

private:
	HitBox * collidedHitbox;

	std::vector<sf::Vector2f> collisionPoints;

	bool hasCollision;
};

