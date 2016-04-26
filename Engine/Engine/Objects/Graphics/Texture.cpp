#include "Texture.hpp"

Texture::Texture()
{
	lastPosition = sf::Vector2f(0, 0);
}

Texture::Texture(sf::Texture* newTexture, sf::Vector2f* newPosition, sf::Vector2f* newSize)
{
	Texture();
	setTexture(newTexture);
	setPosition(newPosition);
	setSize(newSize);
}

Texture::~Texture()
{
	
}

void Texture::draw(sf::RenderTexture& render)
{
	render.draw(texCoords, texture);
}

void Texture::update()
{
	updatePosition();
	//updateSize(); //if we have scaling?
	lastPosition = *position;
}

void Texture::setSize(sf::Vector2f* newSize)
{
	size = newSize;
	updateSize();
}

sf::Vector2f* Texture::getSize()
{
	return size;
}

void Texture::setPosition(sf::Vector2f* newPosition)
{
	position = newPosition;
	lastPosition = sf::Vector2f(0, 0);
}

sf::Vector2f* Texture::getPosition()
{
	return position;
}
void Texture::setTexture(sf::Texture* newTexture)
{
	texture = newTexture;
	updateTexCoords();
}

sf::Texture* Texture::getTexture()
{
	return texture;
}

//PRIVATE FUNCTIONS

void Texture::updatePosition()
{
	sf::Vector2f diff = sf::Vector2f((position->x - lastPosition.x)/2, (position->y - lastPosition.y)/2);

	texCoords[0].position += diff;		//bottom right
	texCoords[1].position += diff;		//bottom left
	texCoords[2].position += diff;		//top left
	texCoords[3].position += diff;		//top right
}

void Texture::updateSize()
{
	if (size->x + size->y == 0)
	{
		texCoords[0].position = sf::Vector2f(position->x + texture->getSize().x / 2, position->y + texture->getSize().y / 2);			//bottom right
		texCoords[1].position = sf::Vector2f(position->x - texture->getSize().x / 2, position->y + texture->getSize().y / 2);			//bottom left
		texCoords[2].position = sf::Vector2f(position->x - texture->getSize().x / 2, position->y - texture->getSize().y / 2);			//top left
		texCoords[3].position = sf::Vector2f(position->x + texture->getSize().x / 2, position->y - texture->getSize().y / 2);			//top right
	}
	else
	{
		texCoords[0].position = sf::Vector2f(position->x + size->x / 2, position->y + size->y / 2);	//bottom right
		texCoords[1].position = sf::Vector2f(position->x - size->x / 2, position->y + size->y / 2);	//bottom left
		texCoords[2].position = sf::Vector2f(position->x - size->x / 2, position->y - size->y / 2);	//top left
		texCoords[3].position = sf::Vector2f(position->x + size->x / 2, position->y - size->y / 2);	//top right
	}
	lastPosition = *position;
}

void Texture::updateTexCoords()
{
	texCoords = sf::VertexArray(sf::Quads, 4);
	//defining texture mapping coords
	texCoords[0].texCoords = sf::Vector2f(texture->getSize().x, texture->getSize().y);	//bottom right
	texCoords[1].texCoords = sf::Vector2f(0, texture->getSize().y);						//bottom left
	texCoords[2].texCoords = sf::Vector2f(0, 0);										//top left
	texCoords[3].texCoords = sf::Vector2f(texture->getSize().x, 0);						//top right
}