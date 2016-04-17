#pragma once

#include "MenuElementList.hpp"


class Menu : public NameSearchable											//a Grouping of menuElements; one example could be a pause menu of options menu
{

public:

	Menu();																	//constructor

	Menu(const sf::Vector2f& pos);

	void addMenuElement(MenuElement* element, const std::string& name);		//adds a menuElement and its name

	void addMenuElement(boost::shared_ptr<MenuElement> element, const std::string& name);		//same thing, just no reference, replaced with pointer



	void setPosition(const sf::Vector2f& pos);						//sets the relative position of the menu

	void move(const sf::Vector2f& disp);						//adds relative position




	void deactivate();														//deactivates the menu

	void activate();														//activates the menu


	void switchActive();													//switch the activfe states

	void setIsActive(const bool& activity);										//set the activity to a certain state


	bool getIsActive();														//returns if the menu is active -- don't draw if it is


	boost::shared_ptr<MenuElement> getPointerToElementByIndex(const unsigned int& index);			//gets a pointer to a menuElement by index, NOT A CHILD CLASS

	boost::shared_ptr<MenuElement> getPointerToElementByName(const std::string& name);				//gets a pointer to a menuElement by name, NOT A CHILD CLASS


	template<class C>
	boost::shared_ptr<C> getPointerToChildByName(const std::string& fname)					//gets a pointer to a child by name
	{
		return (boost::shared_ptr<C>)(elementVector[ntoi(fname)]);
	}


	void update(InputData& inpData);										//updates all of the menuElements

	void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos);	//draws all of the menuElements



private:


	std::vector<boost::shared_ptr<MenuElement>> elementVector;				//a vector of pointers to menuElements

	sf::Vector2f position;													//the position of the menu (relative)

	bool isActive;															//determines if the menu is active
};

