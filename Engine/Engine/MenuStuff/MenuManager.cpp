#include "MenuManager.hpp"

MenuManager::MenuManager()															//empty constructor
{
	isActive = false;
	setVectorSize(1);
}



void MenuManager::addMenu(Menu menu, const std::string& name)							//adds a menu
{

	menuVector.push_back(menu);													//add the menu

	addName(name, menuVector.size() - 1);											//add the name of the menu

}

void MenuManager::addMenu(Menu menu, const std::string& name, const sf::Vector2f& pos)
{
	menu.setPosition(pos);
	addMenu(menu, name);
}


Menu* MenuManager::getMenuPtr(const std::string& name)				//returns a pointer to a menu
{

	return &(menuVector[ntoi(name)]);
}



void MenuManager::activateAllMenus()
{
	for (unsigned int i = 0; i < menuVector.size(); i++)
	{
		menuVector[i].activate();
	}
}



void MenuManager::deactivateAllMenus()
{
	for (unsigned int i = 0; i < menuVector.size(); i++)
	{
		menuVector[i].deactivate();
	}
}




void MenuManager::deactivate()
{
	isActive = false;
	deactivateAllMenus();
}

void MenuManager::activate()
{
	isActive = true;
}

bool MenuManager::getActivity()
{
	return isActive;
}


void MenuManager::update(InputData& inpData)										//updates the menus
{
	for (unsigned int i = 0; i < menuVector.size(); i++)							//cycle through all the menus
	{
		if (menuVector[i].getIsActive())
		{
			menuVector[i].update(inpData);											//update them
		}
	}
}



void MenuManager::draw(sf::RenderWindow& window)								//draws all the menus
{
	for (unsigned int i = 0; i < menuVector.size(); i++)							//cycle through all of the menus
	{
		if (menuVector[i].getIsActive())
		{
			menuVector[i].draw(window, sf::Vector2f(0,0));						//draw them all at their respective drawPositions
		}
	}
}
