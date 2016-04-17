#include "Movable.hpp"

Movable::Movable(){}

Movable::Movable(const sf::Vector2f& newPosition, const sf::Vector2f& newVelocity, sf::Vector2f& newAcceleration)
{
	setPosition(newPosition);
	setVelocity(newVelocity);
	setAcceleration(newAcceleration);
}

void Movable::updateMovement()
{

	velocity += acceleration;
	position += velocity;

	acceleration = sf::Vector2f(0, 0);
	if (velocity.x > maxSpeed)
	{
		velocity.x = maxSpeed;
	}
	else if(velocity.x < maxSpeed*-1)
	{
		velocity.x = maxSpeed*-1;
	}

}

void Movable::setPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
}

sf::Vector2f* Movable::getPosition()
{
	return &position;
}

void Movable::setVelocity(const sf::Vector2f& newVelocity)
{
	velocity = newVelocity;
}

sf::Vector2f* Movable::getVelocity()
{
	return &velocity;
}

void Movable::setAcceleration(const sf::Vector2f& newAcceleration)
{
	acceleration = newAcceleration;
}

sf::Vector2f* Movable::getAcceleration()
{
	return &acceleration;
}

void Movable::applyForce(const sf::Vector2f& force)
{
	acceleration += force;
}

void Movable::setMaxSpeed(const int& newMax)
{
	maxSpeed = newMax;
}