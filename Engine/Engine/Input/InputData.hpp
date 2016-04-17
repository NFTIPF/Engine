#pragma once
#include "KeyboardData.hpp"
#include "MouseData.hpp"


class InputData
{

public:
	
	InputData();
	~InputData();
	
	void keyPressed(const unsigned int keyVal);
	void keyReleased(const unsigned int keyVal);


	bool isKeyHit(const int& keyVal);
	bool isKeyHeld(const int& keyVal);	
	bool isKeyReleased(const int& keyVal);
	
	
	void setLeftData(const unsigned int& state);
	void setRightData(const unsigned int& state);
	void setButtonData(const unsigned int& stateLeft, const unsigned int& stateRight);
	void setMousePosition(const sf::Vector2f& pos);
	void moveMouse(const sf::Vector2f& dist);
	void setScroll(const int& scrollDel);



	unsigned int getLeftData();
	unsigned int getRightData();
	sf::Vector2f getMousePosition();
	sf::Vector2f getMousePositionChange();
	int getScroll();
	
	void setTypedChar(const char& letter);
	char getTypedChar();
	
	std::string getTypedString();
	
	
	void frameUpdate();

	
private:


	KeyboardData keyData;
	MouseData mouseData;
	char typedChar;
	std::string typedString;

};

