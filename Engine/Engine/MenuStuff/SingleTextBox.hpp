#pragma once
#include "MenuElement.hpp"

class SingleTextBox : public MenuElement									//This class is simply text on the screen that has been wrapped a bit
{

public:

	SingleTextBox();														//constructor empty

	SingleTextBox(	const sf::Vector2f& pos, const sf::Font* const font, const std::string& text,
					const unsigned int& charSize, const unsigned double& maxWidth, const sf::Color& color);
																			//constructor that actually sets everything

	~SingleTextBox();														//destructor

	void setup(	const sf::Vector2f& pos, const sf::Font* const font, const std::string& text,
				const unsigned int& charSize, const unsigned double& maxWidth, const sf::Color& color);
																			//setup -- must run if empty constructor was used


	//inherited virtual
	void update() {};

	void update(InputData& inpData) {};

	void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos);

	void resetMD() {};


	sf::Vector2f getGlobalDimensions();

	sf::Vector2f getLocalDimensions();

	sf::Vector2f getLetterPosition(const unsigned int& index);

	sf::Vector2f getLastLetterPosition();

	void setTextString(const std::string& text);								//set the string of the text

	void setTextColor(const sf::Color& color);									//set the color of the text

	void setFontSize(const unsigned int& charSize);											//set the font size of the text

private:

	void wrapText();														//wraps the text around the edge of the textbox

	sf::Vector2f getDimensionsOfString(const std::string& text);					//gets the dimension of a hypothetical text under the current conditions

	void correctPosition();													//corrects the position of the text; text is weird: the origin is the center point of the line the first line is written on



	sf::Text textBody;														//the actual text

	std::string drawString;													//the string to draw

	unsigned double width;															//the width of the textbox

																			//------------much of this stuff is moved one layer out of textBody  for easy access

};

