#pragma once
#include "Texture.hpp"
#include <SFML/Graphics.hpp>

class TiledTexture
{
public:
	TiledTexture();
	TiledTexture(sf::Texture* newTexture, sf::Vector2f* newPosition, sf::Vector2f* newSize, const sf::Vector2f& setSize);
	~TiledTexture();

	void draw(sf::RenderTexture& render);
	void update();	//makes sure the text coords are up to date with position

private:
	Texture tile;
	sf::Vector2f setSize;
	sf::Vector2f TLC;
	sf::Vector2f* centerPosition;
	sf::Vector2f drawPosition;
	sf::Vector2u texSize;
};