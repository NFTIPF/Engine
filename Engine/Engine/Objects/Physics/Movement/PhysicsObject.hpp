#pragma once

#include <SFML\Graphics.hpp>
#include "../../../Defines.hpp"
#include "boost/timer.hpp"
#include "../../../Utility/Utilities.hpp"
#include <iostream>

class PhysicsObject
{
public:
	PhysicsObject();
	PhysicsObject(const sf::Vector2f& newPosition, const sf::Vector2f& newVelocity = sf::Vector2f(0, 0), sf::Vector2f& newAcceleration = sf::Vector2f(0, 0));

	void updateMovement();
	
	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f* getPosition();

	void setVelocity(const sf::Vector2f& newVelocity);
	sf::Vector2f* getVelocity();

	void setAcceleration(const sf::Vector2f& newAcceleration);
	sf::Vector2f* getAcceleration();

	void applyForce(const sf::Vector2f& force);

	void setMaxSpeed(const int& newMax);
	
	void setGravity(const bool& isGravity);
protected:
	int sign(const float&);
	//basic physics components
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	int maxSpeed;

	bool gravity;		//toggles gravity
	bool air;			//toggles air resistance
	bool movable;

	sf::Clock frameTimer;


	//not sure if these will be used here
	//double mass;
	//sf::Vector2f gravity;
};