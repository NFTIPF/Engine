#include "Animation.hpp"

Animation::Animation()
{
	frameTimer.restart();
	lastFrameTime = 0;
	texCoords = sf::VertexArray(sf::Quads, 4);
	currentSheetPosition = sf::Vector2f(1, 1);
	frozen = false;
	setFrameFreeze(false);
}

Animation::Animation(sf::Texture* newSpriteSheet, const sf::Vector2f& newFrameSize)
{
	frozen = false;
	setFrameFreeze(false);
	setSpriteSheet(newSpriteSheet);
	setFrameSize(newFrameSize);
	calcFps();
	setDisplaySize(frameSize);
	Animation();
	prepareAnimation();
}

Animation::Animation(sf::Texture* newSpriteSheet, const sf::Vector2f& newFrameSize, const sf::Vector2f& newDisplaySize, const int& newFps)
{
	frozen = false;
	setFrameFreeze(false);
	setSpriteSheet(newSpriteSheet);
	setFrameSize(newFrameSize);
	setDisplaySize(newDisplaySize);
	setFPS(newFps);
	Animation();
	prepareAnimation();
}

Animation::Animation(sf::Texture* newSpriteSheet, const sf::Vector2f& newFrameSize, const sf::Vector2f& newDisplaySize, const int& newFps, const sf::Vector2f& position)
{
	frozen = false;
	setFrameFreeze(false);
	setSpriteSheet(newSpriteSheet);
	setFrameSize(newFrameSize);
	setDisplaySize(newDisplaySize);
	setFPS(newFps);
	setPosition(position);
	Animation();
	prepareAnimation();
}

Animation::~Animation(){}

void Animation::setFPS(const int& newFPS)
{
	fps = newFPS;
	desiredFrameTime = 1.0 / fps;
}

int Animation::getFPS()
{
	return fps;
}

void Animation::setFrameSize(const sf::Vector2f& newFrameSize)
{
	frameSize = newFrameSize;
}

sf::Vector2f Animation::getFrameSize()
{
	return frameSize;
}

void Animation::setDisplaySize(const sf::Vector2f& newDisplaySize)
{
	displaySize = newDisplaySize;
}
sf::Vector2f Animation::getDisplaySize()
{
	return displaySize;
}

void Animation::setSpriteSheet(sf::Texture* newSpriteSheet)
{
	spriteSheet = newSpriteSheet;
	if (!fps)
	{
		calcFps();
	}
}

sf::Texture* Animation::getSpriteSheet()
{
	return spriteSheet;
}

void Animation::setPosition(const sf::Vector2f& newPosition)
{
	position = &newPosition;
	lastPosition = newPosition;
}

void Animation::drawNextFrame(sf::RenderTexture& texture)
{
	if (frameTimer.elapsed() - lastFrameTime >= desiredFrameTime)		//if its been more than 1/fps since the last frame
	{
		prepareNextFrame();		//sets texture coords etc.
		lastFrameTime = frameTimer.elapsed();
	}
	updatePosition();
	texture.draw(texCoords, spriteSheet);
}

void Animation::setFrameFreeze(const bool& onoff)
{
	freezeFrame = onoff;
}

void Animation::reset()
{
	if (freezeFrame)
	{
		currentSheetPosition = sf::Vector2f(1, 1);	//reset to first texture
		texCoords[0].texCoords = sf::Vector2f(frameSize.x, frameSize.y);		//bottom right
		texCoords[1].texCoords = sf::Vector2f(0, frameSize.y);					//bottom left
		texCoords[2].texCoords = sf::Vector2f(0, 0);							//top left
		texCoords[3].texCoords = sf::Vector2f(frameSize.x, 0);					//top right
		frozen = false;
	}
}

//PROTECTED FUNCTIONS
void Animation::prepareNextFrame()
{
	if (!frozen)
	{
		if (currentSheetPosition.x < sheetSize.x)
		{
			for (int i = 0; i < texCoords.getVertexCount(); i++)
			{
				texCoords[i].texCoords.x += frameSize.x;
			}
			currentSheetPosition.x++;
		}
		else if (currentSheetPosition.y < sheetSize.y)
		{
			for (int i = 0; i < texCoords.getVertexCount(); i++)
			{
				texCoords[i].texCoords.y += frameSize.y;
			}
			currentSheetPosition.y++;
		}
		else
		{
			if (!freezeFrame)
			{
				currentSheetPosition = sf::Vector2f(1, 1);	//reset to first texture
				texCoords[0].texCoords = sf::Vector2f(frameSize.x, frameSize.y);		//bottom right
				texCoords[1].texCoords = sf::Vector2f(0, frameSize.y);					//bottom left
				texCoords[2].texCoords = sf::Vector2f(0, 0);							//top left
				texCoords[3].texCoords = sf::Vector2f(frameSize.x, 0);					//top right
			}
			else
			{
				frozen = true;
			}

		}
	}

}

void Animation::updatePosition()
{
	for (int i = 0; i < texCoords.getVertexCount(); i++)
	{
		sf::Vector2f dif = *position - lastPosition;
		texCoords[i].position += dif;
	}

	lastPosition = *position;
}

void Animation::prepareAnimation()
{
	sheetSize.x = spriteSheet->getSize().x / frameSize.x;
	sheetSize.y = spriteSheet->getSize().y / frameSize.y;

	texCoords = sf::VertexArray(sf::Quads, 4);
	texCoords[0].position = sf::Vector2f((*position).x + displaySize.x / 2, (*position).y + displaySize.y / 2);	//bottom right
	texCoords[1].position = sf::Vector2f((*position).x - displaySize.x / 2, (*position).y + displaySize.y / 2);		//bottom left
	texCoords[2].position = sf::Vector2f((*position).x - displaySize.x / 2, (*position).y - displaySize.y / 2);		//top left
	texCoords[3].position = sf::Vector2f((*position).x + displaySize.x / 2, (*position).y - displaySize.y / 2);		//top right

	texCoords[0].texCoords = sf::Vector2f(frameSize.x, frameSize.y);		//bottom right
	texCoords[1].texCoords = sf::Vector2f(0, frameSize.y);					//bottom left
	texCoords[2].texCoords = sf::Vector2f(0, 0);							//top left
	texCoords[3].texCoords = sf::Vector2f(frameSize.x, 0);					//top right
}
void Animation::calcFps()	//if no fps is specified, fps is assumed to be 
{
	
}