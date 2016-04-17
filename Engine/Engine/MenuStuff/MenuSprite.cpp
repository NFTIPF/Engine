#include "MenuSprite.hpp"



MenuSprite::MenuSprite()
{
	requiresMouseData = false;			//by default, the MenuSprite does not require mouse data

	isHidden = false;					//it shall be drawn

	resetsOnMD = false;					//it does not reset when the menu deactivates
}


MenuSprite::MenuSprite(const sf::Texture* const texture, const sf::Vector2f& pos, const sf::Vector2f& siz)
{
	requiresMouseData = false;			//same stuff

	isHidden = false;

	resetsOnMD = false;

	setup(texture, pos, siz);	//setup
}



MenuSprite::~MenuSprite()
{

}


void MenuSprite::setup(const sf::Texture* const texture, const sf::Vector2f& pos, const sf::Vector2f& siz)
{
	position = pos;				//position is set

	menuImage.setup(texture, sf::Vector2f(0, 0), siz, 0);
}


void MenuSprite::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{

	position += drawPos;		//add the drawPosition  to make position relative


	menuImage.draw(window, position);


	position -= drawPos;		//subtract the drawPosition because we added it

}



sf::Vector2f MenuSprite::getGlobalDimensions()													//all this function does is literally return the global
																								//dimensions of the Sprite
{
	return menuImage.getGlobalDimensions();
}


sf::Vector2f MenuSprite::getLocalDimensions()													//same thing as above, except the dimensions are local
{
	return menuImage.getLocalDimensions();
}
