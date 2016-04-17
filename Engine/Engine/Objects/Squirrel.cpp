#include "squirrel.hpp"

using namespace objects;

Squirrel::Squirrel()
{
	displaySize = sf::Vector2f(100, 100);
	jumping = false;
	colliding = false;
	movable = true;
}

Squirrel::~Squirrel(){}

void Squirrel::draw(Layer& renderTarget)
{
	if (!isActive){return;}

	if (abs(velocity.x) > .5)
	{
		//sf::RenderTexture* renderTex = renderTarget.getRenderTexture();
		walking.drawNextFrame(*renderTarget.getRenderTexture());
	}
	else
	{
		idle.drawNextFrame(*renderTarget.getRenderTexture()); 
	}
}

void Squirrel::update(InputData& inpData)
{
	if (!isActive){ return; }

	if (abs(position.y - 1000) < .5)
	{
		colliding = true;
	}
	else
	{
		colliding = false;
	}

	if (inpData.isKeyHeld(sf::Keyboard::Up))
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
				if (abs(velocity.y) > .1 && colliding)
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

	updateMovement();
}

void Squirrel::load(boost::property_tree::ptree& dataTree, ResourceManager& recMan)
{
	XMLParser reader;
	walkingSSName = reader.readValue<std::string>("walking", dataTree);
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
	walking = Animation(recMan.getTexturePointerByName(walkingSSName), frameSize, displaySize, fps, position);
	idle = Animation(recMan.getTexturePointerByName(idleSSName), frameSize, displaySize, fps, position);

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
	

}

boost::property_tree::ptree Squirrel::write()
{
	boost::property_tree::ptree xml;
	xml.put("walking", walkingSSName);
	xml.put("idle", idleSSName);
	xml.put("fps", fps);
	xml.put("moveSpeed", moveForce);
	xml.put("position.<xmlattr>.x", position.x);
	xml.put("position.<xmlattr>.y", position.y);
	xml.put("size.<xmlattr>.x", displaySize.x);
	xml.put("size.<xmlattr>.y", displaySize.y);
	xml.put("frameSize.<xmlattr>.x", frameSize.x);
	xml.put("frameSize.<xmlattr>.y", frameSize.y);


	return xml;
}