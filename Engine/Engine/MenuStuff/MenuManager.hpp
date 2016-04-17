#pragma once
#include "Menu.hpp"


class MenuManager : public NameSearchable									//holds menus
{
public:

	MenuManager();															//constructor


	void addMenu(Menu menu, const std::string& name);						//adds a menu
	void addMenu(Menu menu, const std::string& name, const sf::Vector2f& pos);

	Menu* getMenuPtr(const std::string& name);								//returns a pointer to a menu



	void activateAllMenus();												//activates all menus

	void deactivateAllMenus();												//deactivates all menus


	void deactivate();

	void activate();

	bool getActivity();



	void update(InputData& inpData);										//updates all of the menus

	void draw(sf::RenderWindow& window);								//draws all of the menus


private:

	std::vector<Menu> menuVector;											//vector of all the menus

	bool isActive;
};

