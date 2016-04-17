#pragma once
#include "SingleTextBox.hpp"


class MultiTextBox : public MenuElement, public NameSearchable				//a named collection of textboxes -- useful for changing text
{
public:

	MultiTextBox();															//constructor

	~MultiTextBox();														//destructor


	//inherited virtual
	void update();

	void update(InputData& inpData);

	void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos);

	void resetMD() {};



	void setCurrentTextBoxByName(const std::string& name);						//set the textbox being drawn by name -- can only draw one at a time

	void setCurrentTextBoxByIndex(const unsigned int& index);								//set the textbox being drawn by index

	void addTextBox(SingleTextBox singleTextBox, const std::string& name);		//adds a textbox and name to the collection

	void addTextBox(SingleTextBox singleTextBox, const unsigned int& intname);		//adds a textbox and inted name to the collection

	SingleTextBox* getTextBoxPointerByName(const std::string& fname);				//returns a pointer to a textbox by name

	SingleTextBox* getTextBoxPointerByIndex(const unsigned int& findex);					//returns a pointer to a textbox by index



private:


	std::vector<SingleTextBox> textBoxVector;								//the collection of textboxes

	unsigned int CTBIndex;													//current textbox index


};

