#pragma once
#include <SFML\Graphics.hpp>
#include "..\Layers\Layer.hpp"

class AppSprite																	//This class is a more useful sprite
{

public:

	AppSprite();																	//0-argument constructor

	AppSprite(const sf::Texture* const & texture, const sf::Vector2f& pos, const sf::Vector2f& size, const double& rot);	//constructor with all elements

	AppSprite(const sf::Texture* const & texture, const sf::Vector2f& TL, const sf::Vector2f& BR);

	~AppSprite();																	//destructor


	void setup(const sf::Texture* const & texture, const sf::Vector2f& pos, const sf::Vector2f& size, const double& rot);	//sets up the MenuSprite


	void move(const sf::Vector2f& disp);

	void setPosition(const sf::Vector2f& pos);


	void rotate(const double& rot);

	void setRotation(const double& deltaRot);


	void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos);

	void draw(Layer& lay, const sf::Vector2f& drawPos);




	sf::Vector2f getGlobalDimensions();												//returns the dimensions of the AppSprite globally

	sf::Vector2f getLocalDimensions();												//returns the dimensions of the AppSprite locally

private:
	void reduceRotation();

	sf::Vector2f position;

	sf::Sprite appImage;															//the Sprite that AppSprite	is just a wrappedd version of.

	double rotation;

};

