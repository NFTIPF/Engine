#include "MultiTextBox.hpp"


MultiTextBox::MultiTextBox()
{
	setVectorSize(1);										//only one name map

	requiresMouseData = false;								//does not require mouse data

	isHidden = false;										//will be drawn

	resetsOnMD = false;										//does not reset on menu dectivation

	CTBIndex = 0;											//th current TextBox index starts as -1

}


MultiTextBox::~MultiTextBox()
{

}



void MultiTextBox::update()									//update
{
	for (unsigned int i = 0; i < textBoxVector.size(); i++)
	{
		textBoxVector[i].update();							//update every textBox
	}
}


void MultiTextBox::update(InputData& inpData)			//update with mouse data
{
	for (unsigned int i = 0; i < textBoxVector.size(); i++)
	{
		textBoxVector[i].update(inpData);				//update every textBox with mouse data
	}
}


void MultiTextBox::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{
	position += drawPos;								//add the draw position to make textBoxes' positions relative

	if (!textBoxVector[CTBIndex].getIsHidden())
	{
		textBoxVector[CTBIndex].draw(window, position);
															// if the current TextBox isn't hidden, draw it
	}


	position -= drawPos;								//take away the draw position because it was added
}



void MultiTextBox::setCurrentTextBoxByName(const std::string& name)	//set the current textBox to naother by name
{
	if (CTBIndex >= 0)
	{
		textBoxVector[CTBIndex].hide();						//hide the old textBox; doesnt really matter; just for consistency
	}

	CTBIndex = ntoi(name);									//most important: the current TextBox index is the index associated with the name

	textBoxVector[CTBIndex].unhide();						//unhide the one that was named; again, doesn't matter


}



void MultiTextBox::setCurrentTextBoxByIndex(const unsigned int& index)		//set the textbox being drawn by index
{

	if (CTBIndex >= 0)
	{
		textBoxVector[CTBIndex].hide();
	}

	CTBIndex = index;

	textBoxVector[CTBIndex].unhide();						//unhide the one that was named
}


void MultiTextBox::addTextBox(SingleTextBox singleTextBox, const std::string& name)
{
	if (textBoxVector.size() > 0)
	{
		singleTextBox.hide();								//hide the textBox if it's not the first

	}
	else
	{
		CTBIndex = 0;										//only change the CTBIndex if it is the first
	}

	textBoxVector.push_back(singleTextBox);				//add it to the collection

	addName(name, textBoxVector.size() - 1);				// add the name
}


void MultiTextBox::addTextBox(SingleTextBox singleTextBox, const unsigned int& intname)
															//same thing, essentially as the previous one
{
	if (textBoxVector.size() > 0)
	{
		singleTextBox.hide();

	}
	else
	{
		CTBIndex = 0;
	}

	textBoxVector.push_back(singleTextBox);

	addName(intname, textBoxVector.size() - 1);				// add the inted name
}



SingleTextBox* MultiTextBox::getTextBoxPointerByName(const std::string& name)
{
	return &textBoxVector[ntoi(name)];	//make the pointer
}



SingleTextBox* MultiTextBox::getTextBoxPointerByIndex(const unsigned int& index)
{
	return &textBoxVector[index];			//make the pointer
}

