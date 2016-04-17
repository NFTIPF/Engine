#include "MultiMenuSprite.hpp"



MultiMenuSprite::MultiMenuSprite()								//constructor
{
	setVectorSize(1);											//There is only one name map

	requiresMouseData = true;									//it does require mouse data, strangely

	isHidden = false;											//draws by default

	resetsOnMD = false;											//does  not reset on menu deactvation

	CMSIndex = 0;
}







void MultiMenuSprite::update()
{
	for (unsigned int i = 0; i < spriteVector.size(); i++)		//update all of the menuSprites, just in case
	{
		spriteVector[i].update();
	}
}



void MultiMenuSprite::update(InputData& inpData)
{
	for (unsigned int i = 0; i < spriteVector.size(); i++)		//update all of the menuSprites
	{
		spriteVector[i].update(inpData);
	}
}

void MultiMenuSprite::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{
	position += drawPos;								//add the draw position to make position relative

	for (unsigned int i = 0; i < spriteVector.size(); i++)
	{
		if (!spriteVector[i].getIsHidden())
		{
			spriteVector[i].draw(window, position);	//draw all the unhidden menuSprites
		}

	}

	position -= drawPos;								//subtract draw position because it was added
}





void MultiMenuSprite::setCurrentMenuSpriteByName(const std::string& name)	//changes the current menu sprite to another by name
{

	if (CMSIndex >= 0)
	{
		spriteVector[CMSIndex].hide();								//hide the old menuSprite ; in this case, doesn't actually do anything; just is for consistency
	}

	CMSIndex = ntoi(name);											//set the current menu sprite equal to the index associated with the name

	spriteVector[CMSIndex].unhide();								//unhide the one that was named; again, doesn't matter

}


void MultiMenuSprite::setCurrentMenuSpriteByIndex(const unsigned int& index)		//same thing as above but by index
{
	if (CMSIndex >= 0)
	{
		spriteVector[CMSIndex].hide();
	}

	CMSIndex = index;

	spriteVector[CMSIndex].unhide();
}



void MultiMenuSprite::addMenuSprite(MenuSprite menuSprite, const std::string& name)	//adds a named menuSprite
{
	if (spriteVector.size() > 0)
	{
		menuSprite.hide();														//hide the menu sprite if it's not the first
	}
	else
	{
		CMSIndex = 0;															//only change the CMSIndex if it is the first
	}

	spriteVector.push_back(menuSprite);										//push it to the vector

	addName(name, spriteVector.size() - 1);									//add the name

}


void MultiMenuSprite::addMenuSprite(MenuSprite menuSprite, const unsigned int& intname)		//adds a named (based on an int this time) menusprite -- essetially same thing
{
	if (spriteVector.size() > 0)
	{
		menuSprite.hide();
	}
	else
	{
		CMSIndex = 0;
	}

	spriteVector.push_back(menuSprite);

	addName(intname, spriteVector.size() - 1);
}



MenuSprite* MultiMenuSprite::getMenuSpritePtrByName(const std::string& name)		//get a pointer to a menuSprite by name
{
	return  &spriteVector[ntoi(name)];
}


MenuSprite* MultiMenuSprite::getMenuSpritePtrByIndex(const unsigned int& index)			//same thing, but by index
{
	return &spriteVector[index];
}

