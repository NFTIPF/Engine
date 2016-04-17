#include "Layer.hpp"


//public

Layer::Layer()
{
	scrollBounded = false;				//by default, scrollBoundedness is false

	scrollSpeed = sf::Vector2f(1, 1);	//The scrollspeed is by default (1,1). This means that the layer will scroll at the same speed as the reference point's movement
	scrollLockX = Lockless;				//both scrollLocks are lockless
	scrollLockY = Lockless;
	trackLocking = false;				//trackLocking is false -- only true if all other layers' locking are dependent on this layer
	//create();
}

Layer::~Layer()
{
}



void Layer::create()					//sets up the Layer -- only call after corners are set
{

	if (!renderTexture.create(boundBRCorner.x - boundTLCorner.x, boundBRCorner.y - boundTLCorner.x))		//creates the renderTexture
	{

	}

	renderTexture.clear(sf::Color(0, 0, 0, 0));															//clears it with transparency
	
	view.setSize(boundBRCorner.x - boundTLCorner.x, boundBRCorner.y - boundTLCorner.x);					//seup the view
	view.setCenter((boundBRCorner.x + boundTLCorner.x) / 2, (boundBRCorner.y + boundTLCorner.y) / 2);

}

boost::property_tree::ptree Layer::write()
{
	boost::property_tree::ptree ret;
	ret.put("<xmlattr>.scrollx", scrollSpeed.x);
	ret.put("<xmlattr>.scrolly", scrollSpeed.y);
	ret.put("<xmlattr>.boundx", scrollBounds[2]);
	ret.put("<xmlattr>.boundy", scrollBounds[3]);
	return ret;
}

void Layer::setScrollSpeed(const sf::Vector2f& fspeed)
{
	scrollSpeed = fspeed;				//set scroll speed
}

sf::Vector2f Layer::getScrollSpeed()
{
	return scrollSpeed;
}



void Layer::setScrollBounds(const double& nsBound, const unsigned int& index)
{
	scrollBounds[index] = nsBound;		//set individual scroll bound
}

void Layer::setScrollBounds(std::vector<const double> nsBound)
{
										//sets all scroll bounds
	if (nsBound.size() != 4)
	{
		nsBound.resize(4);				//resize to be 4
	}

	for (unsigned int i = 0; i < 4; i++)
	{
		scrollBounds[i] = nsBound[i];	//then copy the vector values into the scrollBounds
	}

}

double Layer::getScrollBound(const unsigned int& index)
{
	return scrollBounds[index];			//returns a specific scroll bound
}

void Layer::setScrollBoundedness(const bool& nscrollBounded)
{
	scrollBounded = nscrollBounded;

	if (nscrollBounded)				//when the scrollBoundedness is set, the locks change
	{
		scrollLockX = Unlocked;		//if it's scroll bounded, set it to unlocked
		scrollLockY = Unlocked;
	}
	else
	{
		scrollLockX = Lockless;		//otherwise it's lockless
		scrollLockY = Lockless;
	}
}

bool Layer::getScrollBoundedness()
{
	return scrollBounded;
}



std::pair<unsigned int, unsigned int> Layer::getScrollLock()
{
	return std::make_pair(scrollLockX, scrollLockY);
}

void Layer::setScrollLock(const unsigned int& lockState, const unsigned char& lockAxis)	//set a single scroll lock -- give it a letter or 0 or 1
{
	if (scrollBounded)
	{
		if (lockAxis == 'x' || lockAxis == 'X' || lockAxis == 0)
		{
			scrollLockX = lockState;
		}
		else if (lockAxis == 'y' || lockAxis == 'Y' || lockAxis == 1)
		{
			scrollLockY = lockState;
		}
	}
}

void Layer::setTrackLocking(const bool& b)
{
	trackLocking = b;
}



//setting corners -- lots of these can be removed
void Layer::setExtremeCorners(const sf::Vector2f& fTLCorner, const sf::Vector2f& fBRCorner)
{
	setTopLeftCorner(fTLCorner);
	setBottomRightCorner(fBRCorner);
}


void Layer::setTopLeftCorner(const sf::Vector2f& fTLCorner)
{
	boundTLCorner = fTLCorner;
	trackTLCorner = fTLCorner;
}

void Layer::setBottomRightCorner(const sf::Vector2f& fBRCorner)
{
	boundBRCorner = fBRCorner;
	trackBRCorner = fBRCorner;
}



float Layer::getMinWindowX()
{
	return boundTLCorner.x;
}

float Layer::getMaxWindowX()
{
	return boundBRCorner.x;
}

float Layer::getMinWindowY()
{
	return boundTLCorner.y;
}

float Layer::getMaxWindowY()
{
	return boundBRCorner.y;
}


std::pair<sf::Vector2f, sf::Vector2f> Layer::getWindowCorners()
{
	return std::make_pair(boundTLCorner, boundBRCorner);
}




void Layer::interpretViewPos(const sf::Vector2f& scrollDist)	//this interprets a distance and moves the view based on this -- this gives the illusion of scrolling
{

	//make a new distance based on the scrollspeed
	sf::Vector2f dist;
	dist.x = scrollSpeed.x * scrollDist.x;
	dist.y = scrollSpeed.y * scrollDist.y;


	// if the layer is not independet (not tracking locking), nullify the distance based on the scrollLocks
	if (scrollBounded && !trackLocking)
	{
		if (scrollLockX == Locked)
		{
			dist.x = 0;
		}

		if (scrollLockY == Locked)
		{
			dist.y = 0;
		}
	}


	//move the bound corners and the track corners
	moveBoundCorners(dist);
	moveTrackCorners(dist);

	
	
	if (scrollBounded)
	{
		sf::Vector2f corDist = getCorrectiveDistance();				//get the corrective distance that will align the layer to the bounds 
		


		//if the layer is dependent, based on the scroll locking, nullify the corrective distance
		if (!trackLocking)		
		{
			if (scrollLockX == Locked)
			{
				corDist.x = 0;
			}

			if (scrollLockY == Locked)
			{
				corDist.y = 0;
			}
		}
		

		//move the bound corners back, NOT the track corners -- track corners are for calculations and shouldn't be bounded
		moveBoundCorners(corDist);


		//move the view -- this is the scrolling
		view.move(dist + corDist);

	}
	else
	{
		view.move(dist);
	}
	

	renderTexture.setView(view); //set the renderTexture to use the view
}



sf::RenderTexture* Layer::getRenderTexture()
{
	return &renderTexture;
}



//private

void Layer::moveBoundCorners(const sf::Vector2f& dist)
{
	boundTLCorner += dist;
	boundBRCorner += dist;
}

void Layer::moveTrackCorners(const sf::Vector2f& dist)
{
	trackTLCorner += dist;
	trackBRCorner += dist;
}

sf::Vector2f Layer::getCorrectiveDistance()				//gets the distance required to align the corners with the scrollBounds -- this is scrollBounding
{
	

	
	
	//finds the difference in bounds derived from the corners and the desired bounds. If there is no undesired occurrence, it will be 0
	
	double xval = 0;									//assume the corrective x value is 0

	if (trackTLCorner.x < scrollBounds[Left])			//if the left bound of the layer is beyond the left bound
	{
		xval = scrollBounds[Left] - boundTLCorner.x;	//one would have to move it back this distance;

		if (scrollLockX == Unlocked && trackLocking)	//it also was out of bounds, so it's locked if it's independent
		{
			scrollLockX = Locked;
		}
	}

	else if (trackBRCorner.x > scrollBounds[Right])		//same for right bound
	{
		xval = scrollBounds[Right] - boundBRCorner.x;

		if (scrollLockX == Unlocked && trackLocking)
		{
			scrollLockX = Locked;
		}
	}

	else if (trackLocking)								//if the corners aren't out of bound and the layer is independent, the scrollLock is unlocked
	{
		scrollLockX = Unlocked;
	}





	//similiar for the y scroll lock

	double yval = 0;

	if (trackTLCorner.y < scrollBounds[Top])
	{
		yval = scrollBounds[Top] - boundTLCorner.y;

		if (scrollLockY == Unlocked && trackLocking)
		{
			scrollLockY = Locked;
		}
	}
	else if (trackBRCorner.y > scrollBounds[Bottom])
	{
		yval = scrollBounds[Bottom] - boundBRCorner.y;

		if (scrollLockY == Unlocked && trackLocking)
		{
			scrollLockY = Locked;
		}
	}
	else if (trackLocking)
	{
		scrollLockY = Unlocked;
	}


	//return the required distance
	return sf::Vector2f(xval, yval);
}
