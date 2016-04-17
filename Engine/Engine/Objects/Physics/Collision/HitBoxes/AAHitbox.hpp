#pragma once
#include "../HitBox.hpp"

class AAHitbox : public HitBox
{
public:
	AAHitbox();
	~AAHitbox();

	void setSize(const sf::Vector2f& siz);
	void setSize(const double& width, const double& height);

	void setCorners(const sf::Vector2f& tl, const sf::Vector2f& br);
	std::pair<sf::Vector2f, sf::Vector2f> getCorners();
	sf::Vector2f getSize();
	bool isPointInside(const sf::Vector2f& point);

private:
	
	void findCorners();

	sf::Vector2f TLCorner;
	sf::Vector2f BRCorner;
	sf::Vector2f size;

	enum boundvals {Top = 0, Right, Bot, Left};
};

