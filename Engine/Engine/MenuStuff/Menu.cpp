#include "Menu.hpp"


Menu::Menu()															//Constructor
{
	isActive = true;													//isActive is true at the start
	position = sf::Vector2f(0, 0);										//position is 0,0 at the start
	setVectorSize(1);
}

Menu::Menu(const sf::Vector2f& pos)
{
	isActive = true;													//isActive is true at the start
	position = pos;
	setVectorSize(1);
}

void Menu::addMenuElement(MenuElement* element, const std::string& name)	//adds a menuElement
{
	boost::shared_ptr<MenuElement> tmpPtr(element);
	elementVector.push_back(tmpPtr);									//adds a pointer to a menuElement

	addName(name, elementVector.size() - 1);							//adds the name
}



void Menu::addMenuElement(boost::shared_ptr<MenuElement> element, const std::string& name)
{
	elementVector.push_back(element);								//adds a pointer to a menuElement

	addName(name, elementVector.size() - 1);												//adds the name
}



void Menu::setPosition(const sf::Vector2f& pos)						//set the relative position of the menu
{

	position = pos;													//change to the new position

}



void Menu::move(const sf::Vector2f& disp)					//add position to the menu
{

	position += disp;												//add displacement to position

}



void Menu::deactivate()													//deactivates the menu
{

	isActive = false;													//isActive is turned to false

	for (unsigned int i = 0; i < elementVector.size(); i++)
	{
		if (elementVector[i]->getResetsOnMD())
		{
			elementVector[i]->resetMD();
		}
	}

}



void Menu::activate()													//activates the menu
{

	isActive = true;													//isActive is turned to true

}


void Menu::switchActive()												//switches the activity of the menu
{

	setIsActive(!isActive);

}


void Menu::setIsActive(const bool& activity)									//sets the activity of the menu
{

	if (activity)
	{
		activate();
	}
	else
	{
		deactivate();
	}

}


bool Menu::getIsActive()												//returns if the menu is active
{

	return isActive;													//returns isActive

}



boost::shared_ptr<MenuElement> Menu::getPointerToElementByIndex(const unsigned int& index)				//gets a pointer to a menuElement, not a child
{

	return elementVector[index];										//returns the index'th part of elementVector

}



boost::shared_ptr<MenuElement> Menu::getPointerToElementByName(const std::string& name)			//returns a pointer to a menuElemtn by name, not a child
{

	return elementVector[ntoi(name)];							//returns the (int that the name was mapped to)th element of elementVector

}


void Menu::update(InputData& inpData)								//updates all of the menuElements
{
	for (unsigned int i = 0; i < elementVector.size(); i++)				//cycle through all menuElements
	{
		if (elementVector[i]->getRequiresMouseData())					//if it requires mouse data
		{
			elementVector[i]->update(inpData);						//give it mouse data
		}
		else															//otherwise
		{
			elementVector[i]->update();									//just update it
		}
	}
}



void Menu::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)	//draws all of the menuElements
{
	position += drawPos;												//adds the draw position to make position relative

	for (unsigned int i = 0; i < elementVector.size(); i++)					//cycle through all menuElements
	{
		if (!elementVector[i]->getIsHidden())								//if its not hidden
		{
			elementVector[i]->draw(window, position);				//draw it
		}
	}

	position -= drawPos;												//subtract the draw position because we added it
}




