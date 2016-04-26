#include "Collidable.hpp"

Collidable::Collidable()
{
}


Collidable::~Collidable()
{
}


void Collidable::setColliding(const bool& col)
{
	colliding = col;
}

bool Collidable::getColliding()
{
	return colliding;
}

void Collidable::setHitBox(HitBox newBox)
{
	hitbox = newBox;
}
HitBox* Collidable::getHitBox()
{
	return &hitbox;
}