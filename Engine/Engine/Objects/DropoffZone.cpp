#include "DropoffZone.hpp"	

using namespace objects;

DropoffZone::DropoffZone()
{
	pickups.resize(100);
}

DropoffZone::~DropoffZone(){}

void DropoffZone::draw(Layer& renderTarget)
{
	if (!isActive){ return; }
	if (displaying)
	{
		tex.draw(*renderTarget.getRenderTexture());
	}

}

void DropoffZone::update(InputData& inpData)
{
	if (!isActive){ return; }
	hitbox.updatePosition();
}

void DropoffZone::load(boost::property_tree::ptree& dataTree, ResourceManager& rMan)
{
	XMLParser parser;
	minDropTime = parser.readValue<double>("minDropTime", dataTree);
	textureName = parser.readValue<std::string>("texture", dataTree);
	displaying = parser.readValue<bool>("display", dataTree);
	position.x = parser.readValue<float>("position.<xmlattr>.x", dataTree);
	position.y = parser.readValue<float>("position.<xmlattr>.y", dataTree);
	size.x = parser.readValue<float>("size.<xmlattr>.x", dataTree);
	size.y = parser.readValue<float>("size.<xmlattr>.y", dataTree);
	capacity = parser.readValue<int>("capacity", dataTree);

	if (displaying)
	{
		sf::Texture* texture = rMan.getTexturePointerByName(textureName);
		tex = Texture(texture, &position, &size);
	}

	HitBox box;
	box.create(size);
	box.setPosition(position);
	hitbox = box;
}

boost::property_tree::ptree DropoffZone::write()
{
	boost::property_tree::ptree xml;
	xml.put("type", type);
	xml.put("minDropTime", minDropTime);
	xml.put("texture", textureName);
	xml.put("display", displaying);
	xml.put("position.<xmlattr>.x", position.x);
	xml.put("position.<xmlattr>.y", position.y);
	xml.put("size.<xmlattr>.x", size.x);
	xml.put("size.<xmlattr>.y", size.y);
	xml.put("capacity", capacity);

	return xml;
}

std::vector<boost::shared_ptr<objects::Pickup>> DropoffZone::getPickupArray()
{
	return pickups;
}

boost::shared_ptr<objects::Pickup> DropoffZone::getNextPickup()
{
	if (pickups.size() > 0)
	{
		return pickups[0];
	}

	return boost::shared_ptr<objects::Pickup>();	//return null if there are none
}

bool DropoffZone::dropoff(boost::shared_ptr<objects::Pickup> p)
{


	if (dropoffClock.getElapsedTime().asSeconds() > minDropTime)
	{

		if (pickups.size() < capacity)
		{
			pickups.push_back(p);
			dropoffClock.restart();
			return 1;
		}
	}
	return 0;
}
