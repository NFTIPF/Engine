#include "Slider.hpp"

Slider::Slider(const sf::Vector2f& p, sf::Texture* bg, sf::Texture* indicator, sf::Font* newFont, double M, double m, double start, const std::string& t, const unsigned int& fcharSize)
{
	requiresMouseData = true;
	textString = t;
	charSize = fcharSize;
	currentValue = start;
	background = bg;
	sliderThing = indicator;
	maxValue = M;
	minValue = m;
	position = p;
	cordScale = bg->getSize().x / (maxValue - minValue);
	font = newFont;

	bgSprite.setup(background, position, sf::Vector2f(400, 75), 0);
	slSprite.setup(sliderThing, position, sf::Vector2f(10, 100), 0);
	textBox.setup(position, font, textString, charSize, 300, sf::Color::Blue);

	text.setFont(*font);
	text.setString(textString);
	text.setCharacterSize(charSize);
	//std::cout << cordScale;
}

//bool Slider::getEventDataBool(){}//here so its not abstract

int Slider::getEventDataInt()
{
	return currentValue;
}
void Slider::setButtonTextString(std::string newString)
{
	textString = newString;
}
std::string Slider::getButtonTextString()
{
	return textString;
}
void Slider::updateButtonState(InputData& inpData)
{
	const sf::Vector2f mousePos = inpData.getMousePosition() - lastDrawPosition;


	if (mousePos.x > bgTLPos.x && mousePos.x < bgBRPos.x && mousePos.y > bgTLPos.y && mousePos.y < bgBRPos.y && inpData.getLeftData() == MouseData::Held)
	{
		slSprite.setPosition(sf::Vector2f(mousePos.x, position.y));

		currentValue = (mousePos.x - bgTLPos.x) / cordScale + minValue;

		if (currentValue > maxValue)
		{
			currentValue = maxValue;
		}
		else if (currentValue < minValue)
		{
			currentValue = minValue;
		}
	}
}

void Slider::update()
{

}

void Slider::update(InputData& inpData)
{
	updateButtonState(inpData);
}


//also just here to prevent error

void Slider::resetMD(){}
/*
void Slider::update(sf::Vector2f& mousePos, bool& clicked, bool& pressed)
{
	if (pressed == true)
	{
		// std::cout << "here1" << std::endl;
		//nowClicked = !nowClicked; //toggle clicked status

		//if it is...test to see if a point is not inside the button
		if (mousePos.x < bgTLPos.x ||
			mousePos.y < bgTLPos.y ||
			mousePos.x > bgBRPos.x ||
			mousePos.y > bgBRPos.y)
		{

		}
		else
		{
			//std::cout<<cordScale<<endl<<minValue<<endl;
			//std::cout << bgTLPos.x <<endl<< bgBRPos.x<<endl;
			//std::cout <<mousePos.x - bgTLPos.x<<endl;
			//std::cout << currentValue << std::endl;
			currentValue = (mousePos.x - bgTLPos.x) / cordScale + minValue;
		}
	}
	if (currentValue > maxValue)
	{
		currentValue = maxValue;
	}
	else if (currentValue < minValue)
	{
		currentValue = minValue;
	}
}
*/
void Slider::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{
	//reset BR and TL corner positions for collision
	if (lastDrawPosition != drawPos)
	{
		lastDrawPosition = drawPos;
	}

	bgTLPos = sf::Vector2f((position.x - (background->getSize().x / 2)), (position.y - (background->getSize().y / 2)));
	bgBRPos = sf::Vector2f((bgTLPos.x + (background->getSize().x)), (bgTLPos.y + (background->getSize().y)));
	
	
	bgSprite.draw(window, drawPos);
	slSprite.draw(window, drawPos);
	textBox.draw(window, drawPos);
	
	//window.display();
	//sliderThing->draw(sf::Vector2f(bgTLPos.x + ((currentValue - minValue)*cordScale) - sliderThing->getSize().y / 2, (bgTLPos.y + ((background->getSize().y / 2) - (sliderThing->getSize().y / 2))))); //needs to be centered

	//        ofCircle(bgTLPos, 10);
	//        ofCircle(bgBRPos, 10);


}