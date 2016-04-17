#pragma once
#include <boost\shared_ptr.hpp>
#include "CollisionData.hpp"
#include "../Movement/PhysicsObject.hpp"

class Collidable : public PhysicsObject
{
public:
	Collidable();
	~Collidable();


	void setColliding(const bool& col);
	bool getColliding();

	HitBox getHitBox();

protected:
	HitBox hitbox;
	bool colliding;
};

