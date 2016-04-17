#include "Platform.hpp"

using namespace objects;

Platform::Platform()
{
    colliding = true;
    isActive = true;
}


Platform::Platform(const sf::Vector2f& pos, const double& width, const double& height, sf::Texture* tex)
{
	setup(pos, width, height, tex);
}

Platform::Platform(const sf::Vector2f& TL, const sf::Vector2f& BR, sf::Texture* tex)
{
    setup(TL, BR, tex);
}

Platform::~Platform()
{


}

void Platform::setup(const sf::Vector2f& pos, const double& width, const double& height, sf::Texture* tex)
{
	position = pos;
	size = sf::Vector2f(width, height);
	//sprite.setup(tex, sf::Vector2f(0,0), siz, 0);

}

void Platform::setup(const sf::Vector2f& TL, const sf::Vector2f& BR, sf::Texture* tex)
{
    setup(sf::Vector2f((BR.x + TL.x) / 2, (BR.y + TL.y) / 2), BR.x - TL.x, BR.y - TL.y, tex);
}

void Platform::draw(Layer& renderTarget)
{
	renderTarget.getRenderTexture()->draw(texCoords, platformTexture);
}		//renders object to given sf::RenderTexture&



void Platform::load(boost::property_tree::ptree& dataTree, ResourceManager& resources)
{

	XMLParser parser;
	parser.readValue<float>("position.<xmlattr>.x", position.x, dataTree);	//loading x coord
	parser.readValue<float>("position.<xmlattr>.y", position.y, dataTree);	//loading y coord
	parser.readValue<float>("size.<xmlattr>.x", size.x, dataTree);
	parser.readValue<float>("size.<xmlattr>.y", size.y, dataTree);

	//loading texture
	parser.readValue<std::string>("texture", textureName, dataTree);
	platformTexture = resources.getTexturePointerByName(textureName);
	
	
	sf::Vector2f texSize = (sf::Vector2f)platformTexture->getSize();

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

}	//defined in children to load from (INI?) file


boost::property_tree::ptree Platform::write()
{
	boost::property_tree::ptree xml;
	xml.put("position.<xmlattr>.x", position.x);
	xml.put("position.<xmlattr>.y", position.y);
	xml.put("size.<xmlattr>.x", size.x);
	xml.put("size.<xmlattr>.y", size.y);
	xml.put("texture", textureName);
	return xml;
}

sf::Vector2f Platform::getTlCorner()
{
	return texCoords[2].position;
}

sf::Vector2f Platform::getBRCorner()
{
	return texCoords[0].position;
}
