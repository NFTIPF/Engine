#include "Platform.hpp"

using namespace objects;

Platform::Platform()
{
    colliding = true;
	isActive = false;
	movable = false;
	gravity = false;
	//air = false;
}

Platform::~Platform(){}


void Platform::draw(Layer& renderTarget)
{
	if (!isActive){ return; }
	tex.update();
	tex.draw(*renderTarget.getRenderTexture());
	hitbox.updatePosition();
}		//renders object to given sf::RenderTexture&


void Platform::load(boost::property_tree::ptree& dataTree, ResourceManager& resources)
{
	bool hasBottom = true;
	setSize = sf::Vector2f(1, 1);
	tiled = false;
	HBFrac = sf::Vector2f(1, 1);

	XMLParser parser;
	parser.readValue<float>("position.<xmlattr>.x", position.x, dataTree);	//loading x coord
	parser.readValue<float>("position.<xmlattr>.y", position.y, dataTree);	//loading y coord
	parser.readValue<float>("size.<xmlattr>.x", size.x, dataTree);
	parser.readValue<float>("size.<xmlattr>.y", size.y, dataTree);
	parser.readValue<bool>("hasBottom", hasBottom, dataTree);
	parser.readValue<bool>("tiled", tiled, dataTree);
	parser.readValue<float>("setSize.<xmlattr>.x", setSize.x, dataTree);
	parser.readValue<float>("setSize.<xmlattr>.y", setSize.y, dataTree);
	parser.readValue<float>("HBFrac.<xmlattr>.y", HBFrac.y, dataTree);
	parser.readValue<float>("HBFrac.<xmlattr>.x", HBFrac.x, dataTree);

	//loading texture
	parser.readValue<std::string>("texture", textureName, dataTree);
	sf::Texture* platformTexture = resources.getTexturePointerByName(textureName);

	if (!tiled)
	{
		tex = Texture(platformTexture, &position, &size);
	}
	else if (tiled)
	{
		tTex = TiledTexture(platformTexture, &position, &size, setSize);
	}

	HitBox box;
	if (!tiled)
	{
		hitbox.create(sf::Vector2f(size.x *HBFrac.x, size.y * HBFrac.y));
	}
	else if (tiled)
	{
		hitbox.create(sf::Vector2f(setSize.x * size.x * HBFrac.x, setSize.y * size.y * HBFrac.y));
	}
	hitbox.setPosition(position);
	hitbox.setHasBottom(hasBottom);

	setHitBox(hitbox);

}


boost::property_tree::ptree Platform::write()
{
	boost::property_tree::ptree xml;
	xml.put("position.<xmlattr>.x", position.x);
	xml.put("position.<xmlattr>.y", position.y);
	xml.put("size.<xmlattr>.x", size.x);
	xml.put("size.<xmlattr>.y", size.y);
	xml.put("texture", textureName);
	xml.put("hasBottom", hitbox.hasBottom());
	xml.put("tiled", tiled);
	xml.put("setSize.<xmlattr>.x", setSize.x);
	xml.put("setSize.<xmlattr>.y", setSize.y);
	xml.put("type", type);
	xml.put("HBFrac.<xmlattr>.x", HBFrac.x);
	xml.put("HBFrac.<xmlattr>.y", HBFrac.y);
	return xml;
}

