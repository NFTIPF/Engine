#pragma once
#include "MenuElement.hpp"
#include "AppSprite.hpp"


class MenuSprite : public MenuElement												//This class is a sprite that is also a menuElement, essentially
{

public:

	MenuSprite();																	//0-argument constructor

	MenuSprite(const sf::Texture* const texture, const sf::Vector2f& pos, const sf::Vector2f& size);	//constructor with all elements

	~MenuSprite();																	//destructor


	void setup(const sf::Texture* const texture, const sf::Vector2f& pos, const sf::Vector2f& size);	//sets up the MenuSprite


	//inherited virtuals
	void update() {};

	void update(InputData& inpData) {};

	void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos);

	void resetMD() {};




	sf::Vector2f getGlobalDimensions();												//returns the dimensions of the MenuSprite globally

	sf::Vector2f getLocalDimensions();												//returns the dimensions of the MenuSprite locally

private:

	AppSprite menuImage;															//the AppSprite that Menusprite is just a wrappedd version of.

};

