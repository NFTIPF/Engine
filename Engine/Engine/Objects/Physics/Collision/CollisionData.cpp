#include "CollisionData.hpp"


CollisionData::CollisionData(){}
CollisionData::CollisionData(bool c, HitBox& hit)
{
	hasCollision = c;
	collidedHitbox = &hit;
}

CollisionData::~CollisionData(){}

bool CollisionData::collided()
{
	return hasCollision;
}

HitBox* CollisionData::getCollidedHitbox()
{
	return collidedHitbox;
}

std::vector<sf::Vector2f> CollisionData::getCollisionPoints()
{
	return collisionPoints;
}