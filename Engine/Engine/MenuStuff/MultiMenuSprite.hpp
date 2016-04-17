#pragma once
#include "MenuSprite.hpp"

class MultiMenuSprite : public MenuElement, public NameSearchable			//This class is a named collection of menuSprites
{
public:
	MultiMenuSprite();														//constructor

	~MultiMenuSprite() {};														//destructor


	//inherited virtuals
	void update();

	void update(InputData& inpData);

	void draw(sf::RenderWindow& fwindow, const sf::Vector2f& drawPos);

	void resetMD() {};


	void setCurrentMenuSpriteByName(const std::string& name);						//sets which menuSprite to draw; can only draw one at a time

	void setCurrentMenuSpriteByIndex(const unsigned int& index);					//same thing, but by index instead of by name


	void addMenuSprite(MenuSprite menuSprite, const std::string& name);			//Adds a menusprite to the collection with a name

	void addMenuSprite(MenuSprite menuSprite, const unsigned int& intname);		//same thing, but with an index that will be converted to a name -- useful in for loops


	MenuSprite* getMenuSpritePtrByName(const std::string& name);				//returns a pointer to a menuSprite by name

	MenuSprite* getMenuSpritePtrByIndex(const unsigned int& index);			//same, bu by index

private:

	std::vector<MenuSprite> spriteVector;									//the collection of MenuSprites

	unsigned int CMSIndex;													//current menuSprite index

};

