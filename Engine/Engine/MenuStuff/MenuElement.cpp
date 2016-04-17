#include "MenuElement.hpp"


void MenuElement::setPosition(const sf::Vector2f& pos)
{
	position = pos;
}


void MenuElement::move(const sf::Vector2f& disp)
{
	position += disp;
}



sf::Vector2f MenuElement::getPosition()
{
	return position;
}



bool MenuElement::getRequiresMouseData()
{
	return requiresMouseData;
}


void MenuElement::setRequiresMouseData(const bool& _reqsMouseData)
{
	requiresMouseData = _reqsMouseData;
}




void MenuElement::hide()
{
	isHidden = true;
}



void MenuElement::unhide()
{
	isHidden = false;
}




bool MenuElement::getIsHidden()
{
	return isHidden;
}



void MenuElement::setResetsOnMD(const bool& _resetsOnMD)
{

	resetsOnMD = _resetsOnMD;

}

bool MenuElement::getResetsOnMD()
{
	return resetsOnMD;
}