#pragma once
#include "HitBoxes\CircularHitbox.hpp"
#include "HitBoxes\AAHitbox.hpp"
#include "../../../Utility/Utilities.hpp"

class HitBoxCollider
{
	typedef std::vector<sf::Vector2f> polygon;

public:
	HitBoxCollider();
	~HitBoxCollider();

    sf::Vector2f getNewPosition(HitBox* boxA, sf::Vector2f velA, HitBox* boxB, sf::Vector2f velB);
	bool checkCollision(HitBox* boxA, HitBox* boxB);

private:

	bool collideDoubleAABB(AAHitbox* boxA, AAHitbox* boxB);
	//bool collideAABBCirc(AAHitbox* boxA, CircularHitbox* boxB);
	//bool collideDoubleCirc(CircularHitbox* boxA, CircularHitbox* boxB);
	bool collideDoublePolygon(const polygon& hb1, const polygon& hb2);



	std::pair<sf::Vector2f, sf::Vector2f> getBoundingBoxCorners(const std::vector<sf::Vector2f>& points);

	sf::Vector2f getCorVelDoubleAABB(const sf::Vector2f& vel, AAHitbox* boxA, AAHitbox* boxB);
	//sf::Vector2f getCorVelCircAABB(sf::Vector2f vel, CircularHitbox* circA,  AAHitbox* boxB);
	//sf::Vector2f getCorVelAABBCirc(sf::Vector2f vel, AAHitbox* boxB, CircularHitbox* circA);
	//sf::Vector2f getCorVelDoubleCirc(sf::Vector2f vel, CircularHitbox* circA, CircularHitbox* circB);
	std::pair<sf::Vector2f, sf::Vector2f> getKineticResponseDoublePolygon(const sf::Vector2f& vel, const polygon& polyA, const polygon& polyB);



 

	AAHitbox* downcastAABB(HitBox* box);
	CircularHitbox* downcastCirc(HitBox* box);

	double magSq(const sf::Vector2f& vec);
	double distSq(const sf::Vector2f& veca, const sf::Vector2f& vecb);
	//double distanceSqToAALine(const sf::Vector2f& point, const sf::Vector2f& c1, const sf::Vector2f& c2);

	std::pair<sf::Vector2f, bool> getLinePoi(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& a, const sf::Vector2f& b);
	//std::pair<std::pair<sf::Vector2f, bool>, std::pair<sf::Vector2f, bool>> getLineCirclePois(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& c, const double& rad);
	

	bool checkPointOnLine(const sf::Vector2f& point, const sf::Vector2f& pa, const sf::Vector2f& pb);

    double knockback;
};

