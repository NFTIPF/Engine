#include "TestObject.hpp"

using namespace objects;

TestObject::TestObject(){}

TestObject::~TestObject(){}

void TestObject::draw(Layer& renderTarget)
{
	renderTarget.getRenderTexture()->draw(texCoords, testTex);
}

void TestObject::update(InputData& inpData)
{

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
	testTex = resources.getTexturePointerByName(textureName);
	
	sf::Vector2f texSize = (sf::Vector2f)testTex->getSize();

	texCoords = sf::VertexArray(sf::Quads, 4); 

	//defining edge coordinates centered on position
	if (size.x + size.y == 0)
	{
		texCoords[0].position = sf::Vector2f(position.x + texSize.x / 2, position.y + texSize.y / 2);	//bottom right
		texCoords[1].position = sf::Vector2f(position.x - texSize.x / 2, position.y + texSize.y / 2);	//bottom left
		texCoords[2].position = sf::Vector2f(position.x - texSize.x / 2, position.y - texSize.y / 2);	//top left
		texCoords[3].position = sf::Vector2f(position.x + texSize.x / 2, position.y - texSize.y / 2);	//top right
	}
	else
	{
		texCoords[0].position = sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2);	//bottom right
		texCoords[1].position = sf::Vector2f(position.x - size.x / 2, position.y + size.y / 2);	//bottom left
		texCoords[2].position = sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2);	//top left
		texCoords[3].position = sf::Vector2f(position.x + size.x / 2, position.y - size.y / 2);	//top right
	}
	

	//defining texture mapping coords
	texCoords[0].texCoords = sf::Vector2f(texSize.x, texSize.y);			//bottom right
	texCoords[1].texCoords = sf::Vector2f(0, texSize.y);					//bottom left
	texCoords[2].texCoords = sf::Vector2f(0, 0);			//top left
	texCoords[3].texCoords = sf::Vector2f(texSize.x, 0);	//top right

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

