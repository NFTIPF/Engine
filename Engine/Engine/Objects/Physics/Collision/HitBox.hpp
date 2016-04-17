#pragma once
#include <SFML\Graphics.hpp>

class HitBox	//convex shape collision
{
public:
	//enum HitBoxType { RECT, CIRCLE, POLY, TRI };

	HitBox();
	~HitBox();

	std::vector<sf::Vector2f> get();

	void setPosition(const sf::Vector2f& pos);
	void setPosition(const double& x, const double& y);

	void create(const std::vector<sf::Vector2f>& points);			//defaults to create poly
	void create(const float& radius, const int& resolution = 10);	//defaults to generate circle points

	void create(const int& height, const int& width);	//allows generation of tris and rectangles

	sf::Vector2f getPosition();


	void move(const sf::Vector2f& newPosition);		//just an alias


protected:
	
	sf::Vector2f lastPosition;
	sf::Vector2f position;

	std::vector<sf::Vector2f> polygon;	//non-translated version of hitbox
	std::vector<sf::Vector2f> hitbox;

};

