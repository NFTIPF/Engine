#pragma once
#include <SFML\Graphics.hpp>
#include <math.h>

class HitBox	//convex shape collision
{
public:
	//enum HitBoxType { RECT, CIRCLE, POLY, TRI };

	HitBox();
	~HitBox();

	void updatePosition();

	std::vector<sf::Vector2f> get();

	void setPosition(sf::Vector2f& pos);

	void create(const std::vector<sf::Vector2f>& points);			//defaults to create poly
	void create(const float& radius, const int& resolution = 10);	//defaults to generate circle points

	void create(const sf::Vector2f& dimensions);	//allows generation of tris and rectangles

	sf::Vector2f getPosition();


	void move(sf::Vector2f& newPosition);		//just an alias

	void feather(const bool& onoff, const int& amount = 2);
	bool isFeather();

	bool hasBottom();
	void setHasBottom(const bool& bot);
protected:
	
	sf::Vector2f lastPosition;
	sf::Vector2f *position;

	std::vector<sf::Vector2f> polygon;	//non-translated version of hitbox
	std::vector<sf::Vector2f> hitbox;

	bool feathered;
	bool bottomed;

};

