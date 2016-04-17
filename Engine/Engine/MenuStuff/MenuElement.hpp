#pragma once

#include "MenuIncludes.hpp"

class MenuElement
{
public:


	virtual void update() = 0;															//virtual; every menuElement will have a 0-argument update

	virtual void update(InputData& inpData) = 0;			//and they will have a 3-argument mousedata update

	virtual void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos) = 0;				//and will draw, somehow

	virtual void resetMD() = 0;															//reset on menu deactivation







	void setPosition(const sf::Vector2f& pos);												//set the position of a menuElement

	void move(const sf::Vector2f& disp);													//move the menuElement

	sf::Vector2f getPosition();															//retrieve the position of a menuElement




	void setRequiresMouseData(const bool& _reqsMouseData);									//set if something requires mouseData

	bool getRequiresMouseData();														//retrieve mousedata



	void hide();																		//hide a menuElement from drawing

	void unhide();																		//unhide one

	bool getIsHidden();																	//retrieve oif the thing wnats to be drawn


	void setResetsOnMD(const bool& _resetsOnMD);

	bool getResetsOnMD();




protected:

	sf::Vector2f position;																//position of the menuElement


	bool requiresMouseData;																//if it requires mouseData

	bool isHidden;																		//if it wants to be drawn

	bool resetsOnMD;																	//if it resets on Menu deactivation
};

