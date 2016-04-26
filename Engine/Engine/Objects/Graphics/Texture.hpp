#pragma once

#include <SFML\Graphics.hpp>


class Texture
{

public:
	Texture();
	Texture(sf::Texture* newTexture, sf::Vector2f* newPosition, sf::Vector2f* newSize);
	~Texture();

	void draw(sf::RenderTexture& render);
	void update();	//makes sure the text coords are up to date with position

	void setSize(sf::Vector2f* newSize);
	sf::Vector2f* getSize();
	
	void setPosition(sf::Vector2f* newPosition);
	sf::Vector2f* getPosition();

	void setTexture(sf::Texture* newTexture);
	sf::Texture* getTexture();
	
private:
	void updatePosition();
	void updateSize();
	void updateTexCoords();

	sf::Texture* texture;

	sf::Vector2f lastPosition;
	sf::Vector2f* position;
	sf::Vector2f* size;	//size to draw

	sf::VertexArray texCoords;
};