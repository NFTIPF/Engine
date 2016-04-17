#include "BasicButton.hpp"



BasicButton::BasicButton()
{

	//setting inherited protected stuff------------------

	requiresMouseData = true;															//set the inherited protected bool requiresMouseData to true because BasicButton requires mouse data

	isHidden = false;																	//set the inherited protected bool isHidden to false because BasicButton should be drawn by default

	resetsOnMD = true;																	//BasicButtons reset when their menu deactivates typically

	//done-----------------------------------------------

	for (int i = 0; i < 2; i++)
	{
		buttonStateCheckers[i] = 0;
	}

	buttonState = Unheld;																//buttonState is unheld at the start of BasicButton's existence

	lastMouseHeld = 0;																	//lastMouseHeld starts off as not having a hold value

	pressedDown = 0;																	//the button is initially not held down
}



BasicButton::BasicButton(	const sf::Vector2f& pos, ResourceGroup * rg,
							const std::string& text, const sf::Color& textColor,
							const sf::Vector2f& siz, const unsigned int& charSize, const double& border)
{

	//setting inherited protected stuff------------------



	requiresMouseData = true;															//set the inherited protected bool requiresMouseData to true because BasicButton requires mouse data

	isHidden = false;																	//set the inherited protected bool isHidden to false because BasicButton should be drawn by default

	resetsOnMD = true;																	//BasicButtons reset when their menu deactivates typically

	//done-----------------------------------------------

	for (int i = 0; i < 2; i++)
	{
		buttonStateCheckers[i] = 0;														//button state checkers are both initially 0
	}

	buttonState = Unheld;																//buttonState is unheld at the start of BasicButton's existence

	lastMouseHeld = 0;																	//lastMouseHeld starts off as not having a hold value

	pressedDown = 0;																	//the button is initially not held down

	setup(pos, rg, text, textColor, siz, charSize, border);//call the setup
}


void BasicButton::setup(	const sf::Vector2f& pos, ResourceGroup * rg,
							const std::string& text, const sf::Color& textColor,
							const sf::Vector2f& siz, const unsigned int& charSize, const double& border)
{

	position = pos;									//set the inherited protected position to the entered position; this will be the position of the button
															//relative to a menu

	for (int i = 0; i < 2; i++)															//cycle through extreme corner indices
	{
		extremeCorners[i] = sf::Vector2f(position.x + (2 * i - 1) * siz.x / 2, position.y + (2 * i - 1) * siz.y / 2);
		//set the extreme corner position; note: f: x -> (2x - 1) maps 0 to -1 and 1 to 1
	}


	//Here, the Sprites are set


	MenuSprite tempSprite;																//declare a temporary Sprite to be pushed back

	sf::Vector2f tempDimensions;														//declare temporary helper dimensioins of the sprite



	for (unsigned int i = 0; i < States_Number; i++)									//cycle through 6 times
	{

		tempSprite.setup(rg->getTexturePointer(i), sf::Vector2f(0, 0), siz);//setup the temporary sprite with the desired textures

		buttonSprites.addMenuSprite(tempSprite, i);										//add the tempoarary sprite to the sprite vector

	}


	doWhenButtonEvent.resize(Events_Number);											//resize the callback vector to the appropriate amount


	//Now, the text is set

	buttonTextBox.setup(sf::Vector2f(0, 0), rg->getFontPointer(0), text, charSize, siz.x - border, textColor);
																						//setup the textbox




	//soundBuffer stuff?
}



void BasicButton::update()															//Empty update -- inherited virtual
{

}



void BasicButton::update(InputData& inpData)					//mouse data update -- inherited virtual
{

	updateButtonState(inpData);													//update the buttonState

	updateButtonEvent();															//do callbacks

}


void BasicButton::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)	//draws the Button
{

	if (lastDrawPosition != drawPos)
	{
		lastDrawPosition = drawPos;							//the last draw position becomes the draw position if it's not already
	}


	position += drawPos;								//increase the position by thedesired draw position -- makes the position relative




	buttonSprites.draw(window, position);			//draw the sprite


	buttonTextBox.draw(window, position);			//draw the text



	position -= drawPos;								//finally, subtract the drawPosition because we added it

}



void BasicButton::resetMD()								//this is called when the menu deactivates
{

	buttonState = Unheld;								//the button state becomes unheld

	buttonSprites.setCurrentMenuSpriteByIndex(0);		//set the current state being drawn to the default

	pressedDown = false;								//the button is no longer being pressed down


}



void BasicButton::setRelativeSpritePosition(const sf::Vector2f& pos)		//sets the position of all the Sprites (relatively).
{
	for (int i= 0; i < 2; i++)
	{
		extremeCorners[i] = extremeCorners[i] + pos - buttonSprites.getPosition();
																	//set the extremeCorners to be around the new position;
	}


	buttonSprites.setPosition(pos);									//set the position (which will in draw() be relative) to the desired position

}



void BasicButton::moveRelativeSpritePosition(const sf::Vector2f& disp)		//moves the position of all the Sprites
{

	for (int i = 0; i < 2; i++)
	{
		extremeCorners[i] += disp;									//move the Extreme Corners by the velocity
	}


	buttonSprites.move(disp);										//move the Sprites by the desired velocity

}


void BasicButton::setRelativeTextPosition(const sf::Vector2f& pos)			//set the position of the text (relative to the button)
{

	buttonTextBox.setPosition(pos);									//move the Text to the desired position

}


void BasicButton::moveRelativeTextPosition(const sf::Vector2f& disp)			//move the position of the text by the desired velocity
{

	buttonTextBox.move(disp);												//move it by the velocity

}



unsigned int BasicButton::getButtonState()										//returns the buttonState
{

	return buttonState;

}



void BasicButton::addFunctionOnButtonState(boost::function<void()> fxn, const unsigned int& state)		//adds a function to do when the button is a certain buttonState
{

	doWhenButtonEvent[state].push_back(fxn);								//add the desired function

}



void BasicButton::updateButtonState(InputData& inpData)			//*groan* Click logic...
{


	const sf::Vector2f mousePos = inpData.getMousePosition() - lastDrawPosition;
																	//make a new vec2f, mousePos that is the mousePosition from
																	//the mouseData; only here to shorten and simplify code
	const unsigned int leftData = inpData.getLeftData();

	/*bool pressedDown = (buttonState == Clicked) || (buttonState == Unheld_Pressed) || (buttonState == Hovered_Pressed) || (buttonState == Held_Pressed);*/
																	//if any of the above statements were true, pressed down should be true.
																	//This means that the mouse is being held down.



	//here goes the click logic. There will be weird tabbing to match the if satements

	if (mousePos.x > extremeCorners[0].x && mousePos.x < extremeCorners[1].x && mousePos.y > extremeCorners[0].y && mousePos.y < extremeCorners[1].y)
																//if the mousePosition was inside the extreme corners
	{


		if (leftData == 3)											//if the mouse was being released
		{
			if (lastMouseHeld != 1)										//if the mouse was not last pressed outside of the button
			{
				pressedDown = !pressedDown;								//the pressedDown state changes
			}



			else														//otherwise if the mouse was pressed off of the Button
			{
				if (pressedDown)											//if the button is held down
				{
					buttonState = Unheld_Pressed;							//the button is now hovered and pressed
				}


				else														//otherwise
				{
					buttonState = Unheld;									//the button is hovered
				}


			}

			lastMouseHeld = 0;			//when the mouse is released, it is no longer held
		}



		else if(leftData == 0)											//else if the left mouse is unheld
		{
			if (pressedDown)											//if the button is currently in the down state
			{
				buttonState = Hovered_Pressed;							//it's hovered and pressed
			}

			else														//otherwise
			{
				buttonState = Hovered;									//it's only hovered
			}
		}



		else if (leftData == 2)										//else if the left mouse was being held
		{
			if (lastMouseHeld != 1)										//if the mouse was not last pressed outside of the button
			{
				if (pressedDown)											//if the button is presed down
				{
					buttonState = Held_Pressed;								//the button is now pressed
				}

				else														//otherwise
				{
					buttonState = Held;										//it's pressed
				}

			}



			else														//if it was pressed outside	and is now in
			{
				if (pressedDown)											//if the button is pressed down
				{
					buttonState = Hovered_Pressed;							//it's hovered and pressed
				}

				else														//otherwise
				{
					buttonState = Hovered;									//it's hovered
				}
			}
		}





		else if (leftData == 1)										//else if the mouse was just pressed on the button
		{
			lastMouseHeld = 2;										//last held was on the button
		}



	}

	else															//else if the mouse was outside the button
	{
		if (lastMouseHeld == 2)											//if the mouse was last held on the button
		{
			if (pressedDown)												//if the button was pressed down
			{
				buttonState = Hovered_Pressed;								//it's hovered and pressed even if the
			}

			else															//otherwise
			{
				buttonState = Hovered;										//it's only hovered
			}
		}

		else if (leftData == 1)											//else if the mouse was just held down and was not already held down somewhere else
		{
			lastMouseHeld = 1;											//the mouse was last held off of the button
		}


		if (leftData == 3)												//if the mouse was released
		{
			lastMouseHeld = 0;											//the mouse wasnt held
		}


		if (lastMouseHeld != 2)											//if the mouse was not dragged off of the button
		{
			if (pressedDown)												//if the button was pressed down
			{
				buttonState = Unheld_Pressed;								//the button is now unheld and pressed
			}

			else															//otherwise
			{
				buttonState = Unheld;										//the button is simply unheld
			}
		}
	}

}



void BasicButton::updateButtonEvent()										//This function calls the callback functions based on the event
{
	buttonStateCheckers[0] = buttonStateCheckers[1];						//keep track of last two button states...

	buttonStateCheckers[1] = buttonState;

	if (buttonStateCheckers[0] != buttonStateCheckers[1])					//if they are different...
	{
		if (buttonStateCheckers[0] == Held && (buttonStateCheckers[1] == Unheld_Pressed || buttonStateCheckers[1] == Hovered_Pressed))
		{																	//if the button was held and is now either unheld pressed or hovered pressed, it was clicked

			callbackOnButtonEvent(Clicked);									//do the clicked callback

		}

		else if (buttonStateCheckers[0] == Held_Pressed && (buttonStateCheckers[1] == Unheld || buttonStateCheckers[1] == Hovered))
		{																	//similar logic -> released

			callbackOnButtonEvent(Released);								//do the released callback
		}

		for (unsigned int i = 0; i < States_Number; i++)					//go through all of the button states
		{
			if (buttonStateCheckers[0] == i)								//if the previous button state was i
			{

				callbackOnButtonEvent(2 * i + 1);							//do the exit callback of i
			}

			if (buttonStateCheckers[1] == i)								//if the current button sate was i
			{

				buttonSprites.setCurrentMenuSpriteByIndex(i);				//set the current menuSpite to i


				callbackOnButtonEvent(2 * i);								//do the entry callback of i

			}
		}
	}
}




void BasicButton::callbackOnButtonEvent(const unsigned int& state)										//do this when the button is clicked
{
	for (unsigned int i = 0; i < doWhenButtonEvent[state].size(); i++)					//cycle through all functions to be called
	{

		if (doWhenButtonEvent[state][i])		//if the function exists
		{
			doWhenButtonEvent[state][i]();	//call it
		}
	}
}

