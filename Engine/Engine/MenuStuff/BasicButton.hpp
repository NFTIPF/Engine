#pragma once
#include "MenuElement.hpp"
#include "SingleTextBox.hpp"
#include "MultiMenuSprite.hpp"
#include "boost\function.hpp"

class BasicButton : public MenuElement										//BasicButton is a menuElement that is a button with states based on mouse logic and with text.
{
	//typedef void(*function_pointer)(void*);
	//typedef std::pair<function_pointer, void*> memfunc_of_object;



public:

	BasicButton();

	BasicButton(const sf::Vector2f& pos, ResourceGroup * rg,	//Quite a long constructor, these thing define a BasicButton.
																			//You need position, a resourceGroup, a string for the text,
				const std::string& text, const sf::Color& textColor,		//a color for the text, a size for the sprites, and a
																			//size for the text
				const sf::Vector2f& siz,	const unsigned int& charSize, const double& border);


	void setup(const sf::Vector2f& pos, ResourceGroup * rg,

				const std::string& text, const sf::Color& textColor,

				const sf::Vector2f& siz,	const unsigned int& charSize, const double& border);


	//-------------------------------------------
	//Virtual Functions that were inherited

	void update();															//necessary update inherited from MenuElement with an empty update vitrtual function

	void update(InputData& inpData);			//this is the update used because it requires mouse data to determine button states

	void draw(sf::RenderWindow& window, const sf::Vector2f& drawPos);				//drawing something requires a renderwindow and a position to draw at

	void resetMD();

	//------------------------------------------



	void setRelativeSpritePosition(const sf::Vector2f& pos);						//set the sprite position relative to the button poisiton. It's a bit weird but generalized

	void moveRelativeSpritePosition(const sf::Vector2f& disp);						//change the sprite position releative to the button position



	void setRelativeTextPosition(const sf::Vector2f& pos);							//set the Text position releative to the button position

	void moveRelativeTextPosition(const sf::Vector2f& disp);						//change the text position releative to the button position



	unsigned int getButtonState();													//returns the state of the BasicButton



	void addFunctionOnButtonState(boost::function<void()> fxn, const unsigned int& state);//adds a function to do when the button is on a given buttonState


	//void setResources(ResourceGroup& rgroup);

	/*void setTextSize(int fsize);

	void setTextColor(sf::Color fcolor);

	void setTextString(std::string fstring);

	void setPosition(sf::Vector2f fposition);

	void setSpriteSize(sf::Vector2f  fsize);*/






private:

	void updateButtonEvent();

	void updateButtonState(InputData& inpData);							//using mouse data, finds the current state of the button -- yes, click logic




	void callbackOnButtonEvent(const unsigned int& state);							//calls every function in the vector of functions assigned to a
																			//button state when that button state is the current one

	std::vector<std::vector<boost::function<void()> > > doWhenButtonEvent;



	MultiMenuSprite buttonSprites;											//the Button's Sprites

	SingleTextBox buttonTextBox;											//the Button's textBox

	//sf::soundBuffer soundFX[2];											//will be soundbuffers






	int buttonStateCheckers[2];

	sf::Vector2f extremeCorners[2];											//a click logic helper; the top-left and bottom-right corners.

	sf::Vector2f lastDrawPosition;											//keeps track of where the button was told to draw

	int lastMouseHeld;														//a click logic helper; determines if the mouse was pressed down and held off of or on the button

	bool pressedDown;


	unsigned int buttonState;														//which state the BasicButton is in

	enum buttonStatePossibilities { Unheld = 0, Hovered, Held, Unheld_Pressed, Hovered_Pressed, Held_Pressed, States_Number = 6};
																			//the 6 states of the button. States_Namber is just an index,

	enum buttonEventPossibitities { Enter_Unheld = 0, Exit_Unheld, Enter_Hovered, Exit_Hovered, Enter_Held, Exit_Held, Enter_Unheld_Pressed,
									Exit_Unheld_Pressed, Enter_Hovered_Pressed, Exit_Hovered_Pressed, Enter_Held_Pressed, Exit_Held_Pressed,
									Clicked, Released, Events_Number = 14};
																			//the 14 events the button can trigger. Events_Number is an index
};

