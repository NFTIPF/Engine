#include "TiledTexture.hpp"

TiledTexture::TiledTexture(){}

TiledTexture::TiledTexture(sf::Texture* newTexture, sf::Vector2f* newPosition, sf::Vector2f* newSize, const sf::Vector2f& newSetSize)
{
	centerPosition = newPosition;
	drawPosition = *centerPosition;
	setSize = newSetSize;
	texSize = newTexture->getSize();
	tile = Texture(newTexture, &drawPosition, newSize);

	TLC = *centerPosition - sf::Vector2f(tile.getSize()->x * setSize.x/2, tile.getSize()->y * setSize.y/2);
}

TiledTexture::~TiledTexture(){}

void TiledTexture::draw(sf::RenderTexture& render)
{
	TLC = *centerPosition - sf::Vector2f(texSize.x * setSize.x/2, texSize.y * setSize.y/2);
	
	for (int xit = 0; xit < setSize.x; xit++)
	{
		for (int yit = 0; yit < setSize.y; yit++)
		{
			drawPosition = TLC + sf::Vector2f(xit * tile.getSize()->x + tile.getSize()->x/2, yit * tile.getSize()->y + tile.getSize()->y/2);
			tile.setPosition(&drawPosition);
			tile.update();
			tile.draw(render);
		}
	}
}

void TiledTexture::update()
{

}

