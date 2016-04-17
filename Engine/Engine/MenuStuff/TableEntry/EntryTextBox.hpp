#pragma once
#include <SFML/Graphics.hpp>
#include "..\..\Utility\Utilities.hpp"
#include <iostream>
#include "..\SingleTextBox.hpp"
#include "..\MenuSprite.hpp"
class EntryTextBox : public MenuElement
{
public:
	EntryTextBox();

	EntryTextBox(	sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color &fcolor,
					sf::Texture* const bgTex, const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent
				);

	~EntryTextBox();

	void setup(		sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color &fcolor,
					sf::Texture* const bgTex, const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent
				);


	void setEntryString(std::string& estr);

	void setActivity(bool b);
	bool getActivity();

	//std::string getEntryString();

	void update() {};
	void update(InputData& inpData);
	void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos);
	void resetMD() {};
private:


	void buildEntryString(InputData& inpData);
	void setActivity(InputData& inpData);

	void setBarPos();
	//bool isDif(const char& typedChar, const unsigned int& i);

	sf::Vector2f lastDrawPos;
	
	std::string* entryString;
	SingleTextBox textBox;
	MenuSprite textBar;
	MenuSprite background;
	
	bool isActive;

};

