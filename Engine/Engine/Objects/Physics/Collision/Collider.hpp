#pragma once
#include "../../../Utility/Utilities.hpp"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Collidable.hpp"
#include "CollisionData.hpp"

class Collider
{
public:
	Collider();
	~Collider();

	CollisionData collide(Collidable& o1, Collidable& o2);
	CollisionData collide(Collidable& o1, std::vector<Collidable*>& oVec);
	CollisionData collide(HitBox& b1, HitBox& b2);
	CollisionData collide(HitBox& b1, std::vector<HitBox*>& b2);

	std::pair<sf::Vector2f, bool> getLinePoint(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& a, const sf::Vector2f& b);
	bool checkPointOnLine(const sf::Vector2f& point, const sf::Vector2f& pa, const sf::Vector2f& vec);
	std::pair<sf::Vector2f, sf::Vector2f> getBoundingBoxCorners(const std::vector<sf::Vector2f>& points);
	bool isCollide(const std::vector<sf::Vector2f>& hb1, const std::vector<sf::Vector2f>& hb2);
	bool checkBoundingBoxCollision(const sf::Vector2f& tla, const sf::Vector2f& bra, const sf::Vector2f& tlb, const sf::Vector2f& brb);
};


