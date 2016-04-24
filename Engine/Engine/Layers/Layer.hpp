#pragma once
#include <SFML/Graphics.hpp>
#include "..\Utility\Utilities.hpp"
#include "../Utility/XMLParser.hpp"

class Layer
{

public:

	Layer();	
	~Layer();


	void create();
	boost::property_tree::ptree write();

	void setScrollSpeed(const sf::Vector2f& fspeed);	//set the scrolling speed of the layer; should be pairs of numbers bewtween 0 and 1 inclusive

	sf::Vector2f getScrollSpeed();						//get scroll speed



	void setScrollBounds(const double& nsBound, const unsigned int& index);
														//sets a specific scrollBound

	void setScrollBounds(std::vector<const double> nsBound);	//set all scrollBounds

	double getScrollBound(const unsigned int& index);	//gets a scroll bound by index


	void setScrollBoundedness(const bool& nscrollBounded);

	bool getScrollBoundedness();



	std::pair<unsigned int, unsigned int> getScrollLock();

	void setScrollLock(const unsigned int& lockState, const unsigned char& lockAxis);

	void setTrackLocking(const bool& b);



	void setExtremeCorners(const sf::Vector2f& fTLCorner, const sf::Vector2f& fBRCorner);

	void setTopLeftCorner(const sf::Vector2f& fTLCorner);

	void setBottomRightCorner(const sf::Vector2f& fBRCorner);


	float getMinWindowX();
	float getMaxWindowX();
	float getMinWindowY();
	float getMaxWindowY();

	std::pair<sf::Vector2f, sf::Vector2f> getWindowCorners();	//first is top left and second is bottom right

	void setViewCenter(const sf::Vector2f& viewCent);

	sf::Vector2f getViewCenter();

	void interpretViewPos(const sf::Vector2f& scrollDist);	//moves the view based on a position entered -- this is scrolling



	sf::RenderTexture* getRenderTexture();



private:

	void moveBoundCorners(const sf::Vector2f& dist);
	void moveTrackCorners(const sf::Vector2f& dist);

	sf::Vector2f getCorrectiveDistance();				

	sf::Vector2f scrollSpeed;							//the fraction of the "normal" scroll speed at which a layer will scroll; a layer with
														//.5 scroll speed will scroll half as quickly as a layer with 1 scroll speed; a layer with 0
														//scroll speed will be stationary.

	double scrollBounds[4];								//the purpose is that a layer should not be able to scroll forever. see http://imgur.com/SzH03Ju for a lack of scroll bounds.

	bool scrollBounded;									//true if the layer has active scrolling bounds.


	bool trackLocking;									//true if the layer is independent -- then we care about it's self-identified scroll locks (as opposed to ones we imposed on it)

	//sf::Vector2f scrollTracker;						//keeps track of the scrolling

	//sf::Vector2f oldScrollTracker;


	sf::Vector2f boundTLCorner;							//The top left corner, bounded by the scroll bounds
	sf::Vector2f boundBRCorner;							//the bottom right corner, bounded


	sf::Vector2f trackTLCorner;							//the TL corner if it had ignored all scrollbounds
	sf::Vector2f trackBRCorner;							//BR corner agnostic of scrollbounds
	

	enum boundPositions { Top = 0, Left, Bottom, Right };


	sf::RenderTexture renderTexture;					//the rendertexture of the Layer

	sf::View view;										//the view used by the layer -- responsible for scrolling

	

	unsigned int scrollLockX;							//really a trinary bool -- if the horizontal scrolling is locked or not
	unsigned int scrollLockY;							//locking on the vertical scrolling

	enum lockState {Lockless = 0, Unlocked, Locked};

};

