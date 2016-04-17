#include "InputData.hpp"


InputData::InputData()
{
	typedString = "";
	typedChar = 0;
}


InputData::~InputData()
{
}


	
void InputData::keyPressed(const unsigned int keyVal)
{
	keyData.keyPressed(keyVal);
}
void InputData::keyReleased(const unsigned int keyVal)
{
	keyData.keyReleased(keyVal);
}




bool InputData::isKeyHit(const int& keyVal)
{
	return keyData.isKeyHit(keyVal);
}

bool InputData::isKeyHeld(const int& keyVal)
{
	return keyData.isKeyHeld(keyVal);
}

bool InputData::isKeyReleased(const int& keyVal)
{
	return keyData.isKeyReleased(keyVal);
}
	
	
void InputData::setLeftData(const unsigned int& state)
{
	mouseData.setLeftData(state);
}

void InputData::setRightData(const unsigned int& state)
{
	mouseData.setRightData(state);
}

void InputData::setButtonData(const unsigned int& stateLeft, const unsigned int& stateRight)
{
	mouseData.setButtonData(stateLeft, stateRight);
}

void InputData::setMousePosition(const sf::Vector2f& pos)
{
	mouseData.setPosition(pos);
}

void InputData::moveMouse(const sf::Vector2f& dist)
{
	mouseData.move(dist);
}

void InputData::setScroll(const int& scrollDel)
{
	mouseData.setScroll(scrollDel);
}

unsigned int InputData::getLeftData()
{
	return mouseData.getLeftData();
}

unsigned int InputData::getRightData()
{
	return mouseData.getRightData();
}

sf::Vector2f InputData::getMousePosition()
{
	return mouseData.getPosition();
}

sf::Vector2f InputData::getMousePositionChange()
{
	return mouseData.getPositionChange();
}

int InputData::getScroll()
{
	return mouseData.getScroll();
}
	
	
	
void InputData::setTypedChar(const char& letter)
{
	typedChar = letter;
	
	if (typedChar != '\b')
	{
		typedString += typedChar;
	}
	else if (typedString.size())
	{
		typedString.erase(typedString.size() - 1);
	}
}

char InputData::getTypedChar()
{
	return typedChar;
}
	
std::string InputData::getTypedString()
{
	return typedString;
}
	
	
void InputData::frameUpdate()
{
	keyData.frameUpdate();
	mouseData.frameUpdate();
	typedChar = 0;
}
	