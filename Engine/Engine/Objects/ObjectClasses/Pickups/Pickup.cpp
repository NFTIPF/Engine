#include "Pickup.hpp"

using namespace objects;

Pickup::Pickup()
{
	removed = false;
}


Pickup::~Pickup()
{
}


void Pickup::setup(const sf::Vector2f& pos, const sf::Vector2f& siz, const std::string& pnam, ResourceManager& rman)
{
	position = pos;
	size = siz;
	pickupName = pnam;

	

	subSetup(rman);



}

void Pickup::draw(Layer& renderTarget)
{
	if (!removed)
	{
		if (!isActive){ return; }
		tex.update();
		tex.draw(*renderTarget.getRenderTexture());
	}
	
}

void Pickup::update(InputData& inpData)
{
	if (!removed)
	{
		if (!isActive){ return; }
		//if (/*getCollidingWithSquirrel*/)
		//{
		//	removed = true;
		//}
	}
}

void Pickup::load(boost::property_tree::ptree& dataTree, ResourceManager& rman)
{
	XMLParser parser;
	parser.readValue<float>("position.<xmlattr>.x", position.x, dataTree);	//loading x coord
	parser.readValue<float>("position.<xmlattr>.y", position.y, dataTree);	//loading y coord
	parser.readValue<float>("size.<xmlattr>.x", size.x, dataTree);
	parser.readValue<float>("size.<xmlattr>.y", size.y, dataTree);
	parser.readValue<std::string>("pickupName", pickupName, dataTree);

	//loading texture


	subSetup(rman);

}

 boost::property_tree::ptree Pickup::write()
{
	boost::property_tree::ptree properties;
	properties.put("position.<xmlattr>.x", position.x);
	properties.put("position.<xmlattr>.y", position.y);
	properties.put("size.<xmlattr>.x", size.x);
	properties.put("size.<xmlattr>.y", size.y);
	properties.put("pickupName", pickupName);
	properties.put("type", type);


	return properties;
}

 bool Pickup::isRemoved()
 {
	 return removed;
 }

 PickupData Pickup::getPickupData()
 {
	 return pdata;
 }


 void Pickup::subSetup(ResourceManager& rman)
 {

	sf::Texture* platformTexture = rman.getTexturePointerByName(getTexName(pickupName));

	tex = Texture(platformTexture, &position, &size);

	
	pdata.load(pickupName);

	HitBox box;
	//box.create(sqrt(pow(size.x, 2) + pow(size.y, 2)));
	box.create(size);
	box.setPosition(position);

	hitbox = box;

 }


 std::string Pickup::getTexName(const std::string& typname)
 {
	 INIParser options("PickupList.ini");

	 options.setSection(typname);

	 std::string tname;
	 options.readValue<std::string>("Texture", tname);
	 return tname;
 }