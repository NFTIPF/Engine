#include "TablePair.hpp"


TablePair::TablePair()
{
	requiresMouseData = true;															

	isHidden = false;																	

	resetsOnMD = false;	
}


TablePair::~TablePair()
{
}



TablePair::TablePair( 	sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color &fcolor, sf::Texture* const bgTex,
						const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent, const double& spac
						)
{
	requiresMouseData = true;															

	isHidden = false;																	

	resetsOnMD = false;	

	setup(ffont, ffontsize, fcolor, bgTex, bgSiz, barTex, fpos, indent, spac);
}

	
void TablePair::setup( 	sf::Font * const ffont, const unsigned int& ffontsize, const sf::Color &fcolor, sf::Texture* const bgTex,
						const sf::Vector2f& bgSiz, sf::Texture * const barTex, const sf::Vector2f& fpos, const double& indent, const double& spac
						)
{
	position = fpos;

	keyText.setup(sf::Vector2f(0, 0), ffont, "", ffontsize, bgSiz.x - 2 * indent, fcolor);

	colonDivider.setup(sf::Vector2f(spac, 0), ffont, "|:|", ffontsize, bgSiz.x - 2 * indent, fcolor);

	entryBox.setup(ffont, ffontsize, fcolor, bgTex, bgSiz, barTex, sf::Vector2f(2*spac + bgSiz.x/2, 0), indent);

	
}

void TablePair::setKeyString(const std::string& kstr)
{
	keyText.setTextString(kstr);
}


void TablePair::setEntryString(std::string& estr)
{
	entryBox.setEntryString(estr);
}


//std::string TablePair::getInput()
//{
//	return entryBox.getEntryString();
//}

void TablePair::setActivity(bool b)
{
	entryBox.setActivity(b);
}

bool TablePair::getActivity()
{
	return entryBox.getActivity();
}


void TablePair::update(InputData& inpData)
{
	entryBox.update(inpData);
}

void TablePair::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{
	position += drawPos;

	keyText.draw(window, position);

	colonDivider.draw(window, position);

	entryBox.draw(window, position);


	position -= drawPos;
}