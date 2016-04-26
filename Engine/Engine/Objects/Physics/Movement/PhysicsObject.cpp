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

		if (air)
		{
			sf::Vector2f s = sf::Vector2f(sign(velocity.x), sign(velocity.y));
			sf::Vector2f air = sf::Vector2f(s.x * velocity.x * (s.x * util::clamp(abs(velocity.x), 10, 100)) * AIR, s.y * velocity.y * velocity.y * AIR);	//calculating air resistance
			acceleration -= air;	//apply air resistance
		}

		if (gravity)
		{
			acceleration += sf::Vector2f(0, GRAVITY);	//apply gravity for next frame
		}
		
		velocity += sf::Vector2f(acceleration.x * frameTime, acceleration.y * frameTime);
		position += velocity;




		if ((acceleration.x != acceleration.x) || (acceleration.y != acceleration.y))
		{
			std::cout << "why?" << std::endl;
		}
		if ((velocity.x != velocity.x) || (velocity.y != velocity.y))
		{
			std::cout << "why?" << std::endl;
		}
		if ((position.x != position.x) || (position.y != position.y))
		{
			std::cout << "why?" << std::endl;
		}






		acceleration = sf::Vector2f(0, 0);

	}

	if (velocity.x < .05 && velocity.x > -.05)
	{
		velocity.x = 0;
	}
	if (velocity.y < .05 && velocity.y > -.05)
	{
		velocity.y = 0;
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