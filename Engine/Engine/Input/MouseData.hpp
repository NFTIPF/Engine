#pragma once
#include <SFML/Graphics.hpp>

class MouseData
{

public:
	MouseData();
	~MouseData();

	enum MouseStates {Unheld = 0, Hit, Held, Released};

	void setLeftData(const unsigned int& state);

	void setRightData(const unsigned int& state);

	void setButtonData(const unsigned int& stateLeft, const unsigned int& stateRight);

	void setPosition(const sf::Vector2f& pos);

	void move(const sf::Vector2f& dist);

	void setScroll(const int& scrollDel);



	unsigned int getLeftData();

	unsigned int getRightData();

	sf::Vector2f getPosition();

	sf::Vector2f getPositionChange();

	int getScroll();

	void frameUpdate();

private:


	unsigned int leftButtonData;
	unsigned int rightButtonData;
	int scrollDelta;
	sf::Vector2f position;
	sf::Vector2f oldPosition;

	

};

