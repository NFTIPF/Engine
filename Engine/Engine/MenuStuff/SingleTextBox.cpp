#include "SingleTextBox.hpp"




SingleTextBox::SingleTextBox()
{

	requiresMouseData = false;					//does not require mouse data

	isHidden = false;							//draw it by default

	resetsOnMD = false;							//does not reset on menu deactivation



}



SingleTextBox::SingleTextBox(	const sf::Vector2f& pos, const sf::Font* const font, const std::string& text,
								const unsigned int& charSize, const unsigned double& maxWidth, const sf::Color& color)
{
	requiresMouseData = false;					//same stuff

	isHidden = false;

	resetsOnMD = false;

	setup(pos, font, text, charSize, maxWidth, color);		//setup


}



SingleTextBox::~SingleTextBox()
{
}




void SingleTextBox::setup(	const sf::Vector2f& pos, const sf::Font* const font, const std::string& text,
							const unsigned int& charSize, const unsigned double& maxWidth, const sf::Color& color)
{

	position = pos;						//set position

	width = maxWidth;							//set width

	drawString = text;						//set drawString



	textBody.setFont(*font);					//set the font to the text

	textBody.setString(text);				//set the text to draw the given string

	textBody.setCharacterSize(charSize);		//set the char size


	textBody.setColor(color);					//set the color


	wrapText();									//wrap the text

	correctPosition();							//corrects the text's position

}






void SingleTextBox::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{
	position += drawPos;					//add the draw position to make things relative

	textBody.move(position);					//move the textBody

	window.draw(textBody);				//draw it

	textBody.move(-position);					//move it back

	position -= drawPos;					//subtract the draw position
}




sf::Vector2f SingleTextBox::getGlobalDimensions()
{
	return sf::Vector2f(textBody.getGlobalBounds().width, textBody.getGlobalBounds().height);
}

sf::Vector2f SingleTextBox::getLocalDimensions()
{
	return sf::Vector2f(textBody.getLocalBounds().width, textBody.getLocalBounds().height);
}



sf::Vector2f SingleTextBox::getLetterPosition(const unsigned int& index)
{
	return textBody.findCharacterPos(index);
}

sf::Vector2f SingleTextBox::getLastLetterPosition()
{
	return textBody.findCharacterPos(drawString.size() + 1);
}

void SingleTextBox::setTextString(const std::string& text)	//sets the string you want to draw
{
	textBody.setString(text);						//set the string
	drawString = text;

	wrapText();											//wrap the text
	correctPosition();
}



void SingleTextBox::setTextColor(const sf::Color& color)		//set the color of the text
{
	textBody.setColor(color);							//yep, do it
}



void SingleTextBox::setFontSize(const unsigned int& charSize)				//set the font size in pixels
{
	textBody.setCharacterSize(charSize);

	wrapText();											//wrap the text

	correctPosition();
}


//private

void SingleTextBox::wrapText()				//wraps the string around a margin
{
	std::string searchString;

	bool spaceless = true;
	for (unsigned int i = 0; i < drawString.size(); i++)
	{
		searchString = drawString[i];
		if (searchString == "\n")
		{
			drawString[i] = ' ';			//first, change all "\n"s to spaces -- that is make the text "one line long"
		}
		if (drawString[i] == ' ')
		{
			spaceless = false;
		}
	}

	if (spaceless)
	{
		textBody.setString(drawString);
	}
	else
	{



		int spaceIndex = 1;							//keeps track of where the last space was

		char letter;							//the current letter

		std::string word = "";					//the current word

		std::string line = "";					//the current line of text

		std::string transline = "";				//the current line of text that is used to test the width of the string

		std::string rtstr = "";					//the string to return

		bool notFirstWord = false;				//true if the current word is not the first word

		bool notFirstLine = false;				//true if the current line is not the first line



		for (unsigned int i = 0; i <= drawString.size(); i++)	//go though the string-to-be-drawn + 1 extra space...
		{

			if (i == drawString.size())
			{
				letter = ' ';					//at the space 'after' the end, we call it a space
			}
			else
			{
				letter = drawString[i];			//otherwise its jsut the index of tthe drawString
			}



			if (letter == ' ')					//if a space is found
			{
				if (notFirstWord)				//if it's not the first space/word
				{
					transline += ' ';			//add a space to the beginning of the word
				}

				transline += word;				//then add the word onto the testing line

				if (getDimensionsOfString(transline).x > width)	//if the width would be greater than acceptable,
				{
					if (notFirstLine)			//if its not the first line
					{
						rtstr += "\n";			//tack a newline on the beginning
					}

					rtstr += line;				//add the line onto the finished string

					notFirstWord = false;		//since it is going ot be a new line on the next teration, it is going to be the first word of that line

					if (!notFirstLine)
					{
						notFirstLine = true;	//it won't be the first line anymore after the first line
					}


					line = "";					//revert the line and testing line back to ""
					transline = "";

					i = spaceIndex;				//revert the index back to the last space

				}

				else							//if the width of the text would be fine, instead
				{
					line = transline;			//replace the current line with the testing line -- it passed the test

					notFirstWord = true;		//it's no longer the first word

					spaceIndex = i;				//the last space was at the current index

					if (i == drawString.size())	//if the iteration is one greater than the possible indices in the string (in the case of "finishing early")
					{

						if (notFirstLine)		//if its not hte first line
						{
							rtstr += "\n";		//tack on a newline at the beginning
						}

						rtstr += line;			//throw on the current line
					}

				}

				word = "";						//reset the word to "" if the letetr was a space

			}

			else								//if the letter wasn't a space
			{
				word += letter;					//throw it on the current word
			}

		}

		textBody.setString(rtstr);				//set the drawn string to the finished string
	}
}



sf::Vector2f SingleTextBox::getDimensionsOfString(const std::string& text)	//gets the dimensions of a hypothetical string given the other conditions of the textBox
{
	if (text == "")
	{
		return sf::Vector2f(0, 0);
	}
	sf::Text tmpText;												//make a temporary text

	tmpText.setFont(*textBody.getFont());							//set it up just like the texBox's Text

	tmpText.setCharacterSize(textBody.getCharacterSize());

	tmpText.setString(text);										//set the string to be the hypothetical one

	return sf::Vector2f(tmpText.getGlobalBounds().width, tmpText.getGlobalBounds().height);
																	//return the dimensions of the Text

}



void SingleTextBox::correctPosition()							//corrects the position of the text because text is dumb
{

	sf::Vector2f tempDimensions;								//make temp dimensions

	tempDimensions = sf::Vector2f(textBody.getLocalBounds().width, textBody.getLocalBounds().height);


	textBody.setOrigin(tempDimensions.x / 2, tempDimensions.y / 2);
																//set the origin in the center

	textBody.setPosition(0,0);									//set the position at 0,0 by default



	double maxHeight = 0;										//declare maxHeight and a temporary string

	std::string tmpString;

	for (unsigned int i = 0; i < drawString.size(); i++)		//go through the drawString
	{
		tmpString = drawString[i];								//set tmep string equal to the char at the indexth point in the drawString

		if (tmpString == "\n")
		{
			break;												//if it's a newline, stop
		}

		else if (getDimensionsOfString(tmpString).y > maxHeight)	//otherwise, if the height of the letter is bigger than the maxHeight,
		{
			maxHeight = getDimensionsOfString(tmpString).y;		//make the maxHeight the current letter's height
		}
	}

	textBody.move(sf::Vector2f(0, - maxHeight / 2));			//move the textBody up by half the maxHeight -- don't ask why
}

