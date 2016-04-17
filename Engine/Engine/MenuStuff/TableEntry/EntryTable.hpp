#pragma once
#include "TablePair.hpp"

class EntryTable : public MenuElement
{
public:
	EntryTable();
	EntryTable(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos, sf::Font * const ffont,
				const sf::Color& fcolor, sf::Texture* const bgTex, const sf::Vector2f& bgSiz, sf::Texture * const fbarTex, 
				const double& findent);

	~EntryTable();
	void setup(const double& xspac, const double& yspac, const unsigned int& csiz, const sf::Vector2f& pos);

	void setMap(std::map<std::string, std::string>& fmap, const unsigned int& dispAmt);

	void update() {};
	void update(InputData& inpData);
	void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos);
	void resetMD() {};
private:

	void setActivities(InputData& inpData);
	
	std::vector<unsigned int> getDisplayIndeces();
	void shiftInterval(const int& shift);
	void setTablePositions();
	void setTableHiddenness();
	bool isInInterval(const unsigned int& val);

	sf::Vector2f position;
	sf::Font* font;
	sf::Color color;
	sf::Texture* bgTexture;
	sf::Vector2f bgSize;
	sf::Texture * barTexture;
	double indent;
	
	std::vector<TablePair> tablePairs;

	double xSpacing;
	double ySpacing;
	unsigned int charSize;


	unsigned int displayAmt;
	std::pair<unsigned int, unsigned int> displayInterval;

};

