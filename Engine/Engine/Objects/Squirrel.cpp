#include "Squirrel.hpp"

using namespace objects;

Squirrel::Squirrel()
{
	displaySize = sf::Vector2f(100, 100);
	lastAcceleration = sf::Vector2f(0, 0);
	jumping = false;
	colliding = false;
	movable = true;
	nutCapacity = 2;
}

Squirrel::~Squirrel(){}

void Squirrel::draw(Layer& renderTarget)
{
	if (!isActive){return;}

	if (velocity.x > 0)
	{
		if (velocity.y > .1 || velocity.y < -.1)
		{
			JR.drawNextFrame(*renderTarget.getRenderTexture());
		}
		else if (lastAcceleration.x < 0)
		{
			TR.drawNextFrame(*renderTarget.getRenderTexture());
		}
		else
		{
			RR.drawNextFrame(*renderTarget.getRenderTexture());
		}
		//sf::RenderTexture* renderTex = renderTarget.getRenderTexture();

	}
	else if (velocity.x < 0)
	{
		if (velocity.y > .1 || velocity.y < -.1)
		{
			JL.drawNextFrame(*renderTarget.getRenderTexture());
		}
		else if (lastAcceleration.x > 0)
		{
			TL.drawNextFrame(*renderTarget.getRenderTexture());
		}
		else
		{
			RL.drawNextFrame(*renderTarget.getRenderTexture());
		}

	}
	else
	{
		idle.drawNextFrame(*renderTarget.getRenderTexture()); 
	}
	
	//setAcceleration(sf::Vector2f(0, 0));
}

void Squirrel::update(InputData& inpData)
{
	if (!isActive){ return; }
	if (colliding)
	{
		jumping = false;
		JL.reset();
		JR.reset();
	}
	if (inpData.isKeyHeld(sf::Keyboard::Up))
	{
		//applyForce(sf::Vector2f(0, -moveForce));
		if (jumpTimer.getElapsedTime().asSeconds() > jumpTime*4 || jumping)
		{
			float time;
			if (!jumping)
			{
				jumping = true;
				jumpTimer.restart().asSeconds();

			}

			if (jumping)
			{
				time = jumpTimer.getElapsedTime().asSeconds();

				if (time > jumpTime)
				{
					if (colliding)
					{
						jumping = false;
					}
				}
				else
				{
					applyForce(sf::Vector2f(0, -jumpForce));
				}

			}
		}


	}
	float multiplier = 1;
	if (!colliding)
	{
		multiplier *= airborneMultiplier;
	}
	if (inpData.isKeyHeld(sf::Keyboard::Left))
	{
		applyForce(sf::Vector2f(-moveForce*multiplier, 0));
	}
	if (inpData.isKeyHeld(sf::Keyboard::Right))
	{
		applyForce(sf::Vector2f(moveForce*multiplier, 0));
	}
	if (inpData.isKeyHeld(sf::Keyboard::Down))
	{
		//applyForce(sf::Vector2f(0, moveForce));
		falling = true;
	}
	else
	{
		falling = false;
	}
	lastAcceleration = acceleration;

	updateMovement();
	hitbox.updatePosition();

	colliding = false;
}

void Squirrel::load(boost::property_tree::ptree& dataTree, ResourceManager& recMan)
{
	XMLParser reader;
	RRName = reader.readValue<std::string>("RunRight", dataTree);
	RLName = reader.readValue<std::string>("RunLeft", dataTree);
	idleSSName = reader.readValue<std::string>("idle", dataTree);
	fps = reader.readValue<int>("fps", dataTree);
	moveForce = reader.readValue<float>("moveSpeed", dataTree);
	position.x = reader.readValue<float>("position.<xmlattr>.x", dataTree);
	position.y = reader.readValue<float>("position.<xmlattr>.y", dataTree);
	displaySize.x = reader.readValue<float>("size.<xmlattr>.x", dataTree);
	displaySize.y = reader.readValue<float>("size.<xmlattr>.y", dataTree);
	frameSize.x = reader.readValue<float>("frameSize.<xmlattr>.x", dataTree);
	frameSize.y = reader.readValue<float>("frameSize.<xmlattr>.y", dataTree);

	//should some of these be loaded from ini??


	//default values
	jumpTime = 1000;
	maxSpeed = 5;
	gravity = true;
	air = true;

	//load from ini
	INIParser options("SquirrelOptions.ini");

	options.setSection("Movement");
	options.readValue<int>("MaxSpeed", maxSpeed);
	options.readValue<bool>("Gravity", gravity);
	options.readValue<float>("MoveForce", moveForce);
	options.readValue<float>("JumpForce", jumpForce);
	options.readValue<float>("JumpTime", jumpTime);
	options.readValue<float>("AirMoveMultiplier", airborneMultiplier);


	options.setSection("Graphics");
	options.readValue<int>("AnimationFPS", fps);
	options.readValue <std::string>("TurnLeft", TLName);
	options.readValue<std::string>("TurnRight", TRName);
	options.readValue<std::string>("JumpLeft", JLName);
	options.readValue<std::string>("JumpRight", JRName);

	RR = Animation(recMan.getTexturePointerByName(RRName), frameSize, displaySize, fps, position);
	RL = Animation(recMan.getTexturePointerByName(RLName), frameSize, displaySize, fps, position);
	idle = Animation(recMan.getTexturePointerByName(idleSSName), frameSize, displaySize, fps, position);
	TL = Animation(recMan.getTexturePointerByName(TLName), frameSize, displaySize, fps, position);
	TR = Animation(recMan.getTexturePointerByName(TRName), frameSize, displaySize, fps, position);

	JR = Animation(recMan.getTexturePointerByName(JRName), frameSize, displaySize, fps, position);
	JR.setFrameFreeze(true);
	JL = Animation(recMan.getTexturePointerByName(JLName), frameSize, displaySize, fps, position);
	JL.setFrameFreeze(true);

	HitBox box;
	box.create(sf::Vector2f(displaySize.x/3, displaySize.y));
	box.setPosition(position);
	hitbox = box;

}

boost::property_tree::ptree Squirrel::write()
{
	boost::property_tree::ptree xml;
	xml.put("RunRight", RRName);
	xml.put("RunLeft", RLName);
	xml.put("idle", idleSSName);
	xml.put("fps", fps);
	xml.put("moveSpeed", moveForce);
	xml.put("position.<xmlattr>.x", position.x);
	xml.put("position.<xmlattr>.y", position.y);
	xml.put("size.<xmlattr>.x", displaySize.x);
	xml.put("size.<xmlattr>.y", displaySize.y);
	xml.put("frameSize.<xmlattr>.x", frameSize.x);
	xml.put("frameSize.<xmlattr>.y", frameSize.y);
	xml.put("type", type);


	return xml;
}

bool Squirrel::physicalCollide(CollisionData& data, bool isGhosting)
{
	std::tuple<sf::Vector2f, sf::Vector2f, int> response = Collider::getKineticResponseDoublePolygon(velocity, hitbox.get(), data.getCollidedHitbox()->get(), false);


	colliding = std::get<2>(response);

	/*
	if (velocity.y < -.1 && !data.getCollidedHitbox()->hasBottom())
	{
		//dont apply transform

		setPosition(data.getCollidedHitbox()->getPosition() + sf::Vector2f(0, -150));
		setVelocity(velocity - sf::Vector2f(0, velocity.y));
		colliding = true;

		return true;
	}
	else if (falling && !data.getCollidedHitbox()->hasBottom())
	{
		setPosition(data.getCollidedHitbox()->getPosition() + sf::Vector2f(0, 150));
		colliding = false;
		return true;
	}
	*/
	//else
	//{
		setPosition(position + std::get<1>(response));
		setVelocity(std::get<1>(response)+velocity);
	//}

	hitbox.updatePosition();

	//gravity = false;
	//applyForce(sf::Vector2f(0, -GRAVITY));
	//std::cout << "Normal: " << std::get<1>(response).x << ", " << std::get<1>(response).y << std::endl;
	//std::cout << "PositionF: " << position.x << ", " << position.y << std::endl;
	//std::cout << "VelocityF: " << velocity.x << ", " << velocity.y << std::endl;
	//std::cout <<std::endl;
	//std::cout << colliding << ": " << std::get<0>(response).x << ", " << std::get<0>(response).y << ": " << std::get<1>(response).x << ", " << std::get<1>(response).y << std::endl;
	//std::cout << "vel:" << velocity.x << ", " << velocity.y << std::endl;
	return true;
}

bool Squirrel::pickupCollide(boost::shared_ptr<Pickup>& pickup)
{
	if (pickup->getPickupData().isPowerup())
	{
		//apply powerup
		return true;
	}
	else
	{
		if (nuts.size() < nutCapacity)
		{
			nuts.push_back(pickup);
			return true;
		}
		return false;
	}
	return false;
}

void Squirrel::dropoffCollide(boost::shared_ptr<objects::DropoffZone>& d)
{
	if (nuts.size() > 0)
	{
		if (d->dropoff(nuts[0]))
		{
			nuts.erase(nuts.begin());
		}
	}

}

