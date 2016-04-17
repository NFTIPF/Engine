#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(){}

PhysicsObject::PhysicsObject(const sf::Vector2f& newPosition, const sf::Vector2f& newVelocity, sf::Vector2f& newAcceleration)
{
	setPosition(newPosition);
	setVelocity(newVelocity);
	setAcceleration(newAcceleration);
	movable = false;
	frameTimer.restart();
}

void PhysicsObject::updateMovement()
{
	if (movable)
	{
		double frameTime = frameTimer.restart().asSeconds();

		//HARDCODED platform  REMOVE
		if (position.y > 1000)
		{
			velocity.y = 0;
			position.y = 1000;
		}

		if (air)
		{
			sf::Vector2f s = sf::Vector2f(sign(velocity.x), sign(velocity.y));
			sf::Vector2f air = sf::Vector2f(s.x * velocity.x * (s.x * util::clamp(abs(velocity.x), 10, 100)) * AIR, s.y * velocity.y * velocity.y * AIR);	//calculating air resistance
			acceleration -= air;	//apply air resistance
		}

		velocity += sf::Vector2f(acceleration.x * frameTime, acceleration.y * frameTime);
		position += velocity;

		if (gravity)
		{
			acceleration = sf::Vector2f(0, GRAVITY);	//apply gravity for next frame
		}
		else
		{
			acceleration = sf::Vector2f(0, 0);
		}
	}

}

void PhysicsObject::setPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
}

sf::Vector2f* PhysicsObject::getPosition()
{
	return &position;
}

void PhysicsObject::setVelocity(const sf::Vector2f& newVelocity)
{
	velocity = newVelocity;
}

sf::Vector2f* PhysicsObject::getVelocity()
{
	return &velocity;
}

void PhysicsObject::setAcceleration(const sf::Vector2f& newAcceleration)
{
	acceleration = newAcceleration;
}

sf::Vector2f* PhysicsObject::getAcceleration()
{
	return &acceleration;
}

void PhysicsObject::applyForce(const sf::Vector2f& force)
{
	acceleration += force;
}

//private

int PhysicsObject::sign(const float& d)
{
	if (d >= 0){ return 1; }
	else{ return -1; }
}