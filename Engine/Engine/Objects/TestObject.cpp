#include "TestObject.hpp"

using namespace objects;

TestObject::TestObject(){}

TestObject::~TestObject(){}

void TestObject::draw(Layer& renderTarget)
{
	if (!isActive){ return; }
	tex.update();
	tex.draw(*renderTarget.getRenderTexture());
}

void TestObject::update(InputData& inpData)
{
	if (!isActive){ return; }
}

void TestObject::load(boost::property_tree::ptree& dataTree, ResourceManager& resources)
{
	
	XMLParser parser;
	parser.readValue<float>("position.<xmlattr>.x", position.x, dataTree);	//loading x coord
	parser.readValue<float>("position.<xmlattr>.y", position.y, dataTree);	//loading y coord
	parser.readValue<float>("size.<xmlattr>.x", size.x, dataTree);
	parser.readValue<float>("size.<xmlattr>.y", size.y, dataTree);

	//loading texture
	parser.readValue<std::string>("texture", textureName, dataTree);
	sf::Texture* testTex = resources.getTexturePointerByName(textureName);
	tex = Texture(testTex, &position, &size);

}

boost::property_tree::ptree TestObject::write()
{
	boost::property_tree::ptree properties;
	properties.put("position.<xmlattr>.x", position.x);
	properties.put("position.<xmlattr>.y", position.y);
	properties.put("size.<xmlattr>.x", size.x);
	properties.put("size.<xmlattr>.y", size.y);
	properties.put("texture", textureName);
	properties.put("type", type);

	return properties;
	//more INIParser stuff
}

