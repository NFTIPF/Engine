#include <SFML\Graphics.hpp>
#include <boost\timer.hpp>

class Animation
{
public:

	Animation();
	Animation::Animation(sf::Texture* newSpriteSheet, const sf::Vector2f& newFrameSize);
	Animation(sf::Texture* newSpriteSheet, const sf::Vector2f& newFrameSize, const sf::Vector2f& newDisplaySize, const int& newFps);
	Animation::Animation(sf::Texture* newSpriteSheet, const sf::Vector2f& newFrameSize, const sf::Vector2f& newDisplaySize, const int& newFps, const sf::Vector2f& position);

	~Animation();

	void setFPS(const int& newFPS);
	int getFPS();

	void setFrameSize(const sf::Vector2f& newFrameSize);
	sf::Vector2f getFrameSize();

	void setDisplaySize(const sf::Vector2f& newDisplaySize);
	sf::Vector2f getDisplaySize();

	void setSpriteSheet(sf::Texture* newSprites);
	sf::Texture* getSpriteSheet();

	void setPosition(const sf::Vector2f& newPosition);	
	//there no case where a getter is useful for position (its just a pointer)

	void drawNextFrame(sf::RenderTexture& texture);

	void setFrameFreeze(const bool& onoff);	//freezes on last frame until reset
	void reset();

protected:
	void prepareNextFrame();
	void updatePosition();
	void prepareAnimation();
	void calcFps();

	int fps;						//the frames per second of the animation
	boost::timer frameTimer;	//clock object for determining which frame to draw
	double lastFrameTime;
	double desiredFrameTime;
	
	sf::Vector2f currentSheetPosition;	//current spot of frame in spritesheet
	sf::Vector2f sheetSize;				//dimensions of spritesheet in # of textures
	sf::Vector2f frameSize;
	sf::Vector2f displaySize;
	sf::Texture* spriteSheet;

	sf::VertexArray texCoords;			//coordinates on the spritesheet for drawing frame
	const sf::Vector2f* position;		//this pointer to object position so it doesn't have to be passed
	sf::Vector2f lastPosition;

	bool freezeFrame;
	bool frozen;
};