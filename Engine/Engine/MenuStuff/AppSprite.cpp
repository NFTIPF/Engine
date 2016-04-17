#include "AppSprite.hpp"


AppSprite::AppSprite()
{
	rotation = 0;
	position = sf::Vector2f(0, 0);
}


AppSprite::AppSprite(const sf::Texture* const & texture, const sf::Vector2f& pos, const sf::Vector2f& size, const double& rot)
{
	rotation = rot;

	position = sf::Vector2f(0, 0);

	setup(texture, position, size, rotation);		//setup
}


AppSprite::AppSprite(const sf::Texture* const & texture, const sf::Vector2f& TL, const sf::Vector2f& BR)
{
	//find average point of top left and bottom right -- the center, the position
	sf::Vector2f tpos = TL + BR;
	tpos.x /= 2.0000;
	tpos.y /= 2.0000;



	sf::Vector2f dimensions(fabs(BR.x - TL.x), fabs(BR.y - TL.y));	//get size, esentially

	setup(texture, tpos, dimensions, 0);
}


AppSprite::~AppSprite()
{

}


void AppSprite::setup(const sf::Texture* const & texture, const sf::Vector2f& pos, const sf::Vector2f& siz, const double& rot)
{
	position = pos;				//position is set

	rotation = rot;

	appImage.setTexture(*texture);	//set the texture of the Sprite

	sf::Vector2f tempDimensions(sf::Vector2f(appImage.getLocalBounds().width, appImage.getLocalBounds().height));
	//make temporary helper dimensions

	appImage.setOrigin(tempDimensions.x / 2, tempDimensions.y / 2);
	//set the origin in the center of the temp dimensions

	appImage.setScale(siz.x / tempDimensions.x, siz.y / tempDimensions.y);
	//set the scale such that it is the correct size

	appImage.setPosition(0, 0);		//position is set (relatively) to (0,0)

	appImage.setRotation(rot);
}



void AppSprite::move(const sf::Vector2f& disp)
{
	position += disp;
}

void AppSprite::setPosition(const sf::Vector2f& pos)
{
	position = pos;
}


void AppSprite::rotate(const double& rot)
{
	appImage.rotate(rot);
	rotation = rot;
	reduceRotation();
}

void AppSprite::setRotation(const double& deltaRot)
{
	appImage.setRotation(deltaRot);
	rotation += deltaRot;
	reduceRotation();
}


void AppSprite::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{

	position += drawPos;		//add the drawPosition  to make position relative



	appImage.move(position);		//move the appImage

	window.draw(appImage);	//draw the appImage

	appImage.move(-position);		//move the appImage back



	position -= drawPos;		//subtract the drawPosition because we added it

}

void AppSprite::draw(Layer& lay, const sf::Vector2f& drawPos)
{
    position += drawPos;		//add the drawPosition  to make position relative



	appImage.move(position);		//move the appImage

	lay.getRenderTexture()->draw(appImage);	//draw the appImage

	appImage.move(-position);		//move the appImage back



	position -= drawPos;		//subtract the drawPosition because we added it

}



sf::Vector2f AppSprite::getGlobalDimensions()				//all this function does is literally return the global dimensions of the Sprite
{
	return sf::Vector2f(appImage.getGlobalBounds().width, appImage.getGlobalBounds().height);
}


sf::Vector2f AppSprite::getLocalDimensions()				//same thing as above, except the dimensions are local
{
	return sf::Vector2f(appImage.getLocalBounds().width, appImage.getLocalBounds().height);
}


void AppSprite::reduceRotation()									//bounds the rotation in the interval [0, 2pi)
{
	const double pi = 3.1415926535898;
	const double two_pi = 2 * pi;

	while ((rotation >= two_pi) || (rotation < 0))
	{
		if (rotation < 0)
		{
			rotation += two_pi;
		}
		else
		{
			rotation -= two_pi;
		}
	}

}
