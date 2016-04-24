#include "LayerManager.hpp"


// public


//constructors---

LayerManager::LayerManager()										//basic constructor
{
	basicSetup();
}

LayerManager::LayerManager(const int& amt)							//determines amount of layers on construction
{
	basicSetup();
	setLayerAmount(amt);
}

LayerManager::LayerManager(sf::Vector2f* refPoint)					//determines reference point on contruction
{
	basicSetup();
	setReferencePoint(refPoint);
}

LayerManager::LayerManager(sf::Vector2f* refPoint, const unsigned int& amt)	//conjugation of above two constructors
{
	basicSetup();
	setLayerAmount(amt);
	setReferencePoint(refPoint);
	
}

//---done

LayerManager::~LayerManager()										//empty
{

}

void LayerManager::updateWindowSize(const sf::Vector2u size)
{
	std::vector<const double> bounds = { 0, 0, (double)size.x, (double)size.y };
	for (unsigned int i = 0; i < layers.size(); i++)
	{
		setScrollBounds(bounds, i);
	}
}


void  LayerManager::createLayers()									//creates all layers -- must call sometime
{
	for (unsigned int i = 0; i < layers.size(); i++)
	{
		layers[i]->create();
		//layers[i]->setViewCenter(*referencePoint);
	}
}


void LayerManager::addLayer()										//adds an empty layer
{
	boost::shared_ptr<Layer> emptyLayer(new Layer);
	layers.push_back(emptyLayer);									//makes and adds a new, empty Layer
}


void LayerManager::setLayerAmount(const unsigned int& amt)			//sets the layer amount -- can't remove layers yet
{
	const unsigned int sizdif = amt - layers.size();				//size difference in desired amount and layersSize 

	if (sizdif < 0)
	{
		BOOST_LOG_SEV(layerManagerLogger, WARNING) << "There are already more than " << amt << " layers; removing layers in neither allowed or recommended; resizing layers failed.";
																	//if the size difference is negative, log a warning
	}

	else if (sizdif == 0)
	{
		BOOST_LOG_SEV(layerManagerLogger, INFO) << "There are already " << amt << " layers; resizing layers is meaningless.";
																	//if the size differnece is 0, log info
	}

	else
	{
		for (unsigned int i = 0; i < sizdif; i++)
		{
			addLayer();
		}
																	//otherwise, add a layer that many times
	}

}

unsigned int LayerManager::getLayerAmount()
{
	return layers.size();
}


void LayerManager::setScrollSpeed(const sf::Vector2f& speed, const unsigned int& index)
{
	if (index < layers.size())
	{
		layers[index]->setScrollSpeed(speed);	//if the index is valid, set the scrollSpeed

		if (speed.x < 0 || speed.x > 1 || speed.y < 0 || speed.y > 1)
		{
			BOOST_LOG_SEV(layerManagerLogger, WARNING) << "The desired scroll speed is not between 0 and 1 inclusive. It will still work but will look odd.";
			//if the speed is not between 0 and 1, log a warning
		}
	}
	else
	{
		BOOST_LOG_SEV(layerManagerLogger, ERROR) << "There do not exist at least " << index + 1 << " layers yet; Accessing spot " << index << " failed.";
		//if it's a bad index, log an error
	}
}



void LayerManager::setScrollSpeed(std::vector<const sf::Vector2f> scrollSpeeds)
{

	bool oddSpeed = false;												//if there is a speed < 0 or a speed > 1 or not

	resizeToMatchLayer(scrollSpeeds, "ScrollSpeeds");					//resizes the vector to have the same number of elements as the vector of layers. It also logs a warning sometimes

	for (unsigned int i = 0; i < layers.size(); i++)
	{

		const sf::Vector2f tmpSpeed = scrollSpeeds[i];					//record the speed of the corresponding scrollSpeed value

		layers[i]->setScrollSpeed(tmpSpeed);							//set the scrollSpeed of a layer to its previously determined matching speed

		if (!oddSpeed)
		{
			if (tmpSpeed.x < 0 || tmpSpeed.x  > 1 || tmpSpeed.y < 0 || tmpSpeed.y > 1)
			{
				oddSpeed = true;										//if a speed is < 0 or > 1, record that fact and don't record it again
			}
		}

	}


	if (oddSpeed)
	{
		BOOST_LOG_SEV(layerManagerLogger, WARNING) << "An odd scrollSpeed was detected. It was either < 0 or > 1. It will still work, however.";
		//if there was an odd scrollSpeed, log a warning
	}
}



boost::shared_ptr<Layer> LayerManager::getLayerPtr(const unsigned int& index)
{
	if (index < layers.size())
	{
		return 	layers[index];											//return the memory location of the desired layer
	}
	else
	{
		BOOST_LOG_SEV(layerManagerLogger, ERROR) << "Index " << index << "was out of range -- returning first layer instead";
		return layers[0];
	}
	
}

boost::property_tree::ptree LayerManager::getLayerXML(const int& layer)
{
	boost::property_tree::ptree ret = layers[layer]->write();
	ret.put("<xmlattr>.z", layer);
	return ret;
}


void LayerManager::setReferencePoint(sf::Vector2f* refPoint)
{
	referencePoint = refPoint;										//set the reference point
	oldReferencePointValue = *refPoint;								//set the old refernce point value, too
}


void  LayerManager::setupDraw()										//pieces of draw that function better if called before objects are drawn to layers
{

	sf::Vector2f distance = *referencePoint - oldReferencePointValue;	//distance from the reference point to where it used to be
	std::cout << distance.x << ", " << distance.y << std::endl;

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		layers[i]->getRenderTexture()->clear(sf::Color(0, 0, 0, 0));	//clear the layer
		layers[i]->interpretViewPos(distance);							//interpret the view position -- scrolling
	}

	oldReferencePointValue = *referencePoint;							//update the oldReferencePointValue

	if (dependentScrollLocking)											//if there is dependent scroll locking
	{

		if (layers[indLayer]->getScrollLock().first == 2)
		{
			lockAll(0);													//if the independent layer is x-locked, x-lock all
		}
		else
		{
			unlockAll(0);												//otherwise, x-unlock them
		}

		if (layers[indLayer]->getScrollLock().second == 2)				//same for y
		{
			lockAll(1);												
		}
		else
		{
			unlockAll(1);
		}

	}
}



void LayerManager::draw(sf::RenderWindow& window)
{

	sf::RenderTexture* tmpRenderTex;									//make a temporary RenderTexture pointer

	for (int i = layers.size()-1; i>=0; i--)							//draw in reverse order -- makes intuitive sense: the first layer in the vector
																		//is the forwardmost layer, not backmost
	{

		tmpRenderTex = layers[i]->getRenderTexture();					//set tmpRenderTex to point to the current layer's renderTexture;

		tmpRenderTex->display();										//display it -- necessary to draw anything


		const sf::Texture& tmpTex = (tmpRenderTex->getTexture());		//get the texture from the layer

		sf::Sprite tmpSprite(tmpTex);									//set a sprite's texture as it

		window.draw(tmpSprite);											//draw the new sprite

	}

}


void LayerManager::setScrollBounds(std::vector<const double> bounds, const unsigned int& layerIndex)
																		//set scroll bounds of a single layer
{
	layers[layerIndex]->setScrollBounds(bounds);
}

void LayerManager::setScrollBounds(std::vector<std::vector<const double>> boundVec)
																		//set scroll bounds of all layers
{

	resizeToMatchLayer(boundVec, "ScrollBounds");						//resize the bound vector

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		layers[i]->setScrollBounds(boundVec[i]);						//set the vounds
	}
}


void LayerManager::setCorners(const sf::Vector2f& fTLCorner, const sf::Vector2f& fBRCorner, const unsigned int& layerIndex)	
																		//set corners of single layer
{
	if (layerIndex < layers.size())
	{
		layers[layerIndex]->setExtremeCorners(fTLCorner, fBRCorner);	//set the corners if index is good
	}
	else
	{
		BOOST_LOG_SEV(layerManagerLogger, ERROR) << "Index " << layerIndex << "was out of range -- setting corners failed";
																		//log an error if index was bad
	}
}

void LayerManager::setCorners(std::vector<std::pair<const sf::Vector2f, const sf::Vector2f>> cornerVec)
{
	resizeToMatchLayer(cornerVec, "WindowCorners");				//resize the corner vector

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		layers[i]->setExtremeCorners(cornerVec[i].first, cornerVec[i].second);
																		//set them all
	}
}

void LayerManager::setDependentLocking(const bool& b, const unsigned int& indLay)
{
	if (indLay < layers.size())
	{
		dependentScrollLocking = b;
		indLayer = indLay;
		layers[indLayer]->setTrackLocking(true);
	}
	else
	{
		BOOST_LOG_SEV(layerManagerLogger, ERROR) << "Index " << indLay << "was out of range -- setting dependent locking failed";
	}

}


// private

void LayerManager::basicSetup()
{
	oldReferencePointValue = sf::Vector2f(0, 0);	//start the oldReferencePoint value at (0,0)
	layerManagerLogger = logger::getSLogger();		//setup the logger
	dependentScrollLocking = false;					//set dependent scroll locking to false
	indLayer = 0;									//indLayer is 0
}

void LayerManager::lockAll(const char& lockAxis)	//locks all dependent layers (x or y)
{
	if (dependentScrollLocking)						//only works if dependent scroll locking is enabled
	{
		for (unsigned int i = 0; i < layers.size(); i++)
		{
			if (layers[i]->getScrollBoundedness() && i != indLayer)	//doesn't lock boundless layers or independent layer
			{
				if (lockAxis == 'x' || lockAxis == 'X' || lockAxis == 0)
				{
					layers[i]->setScrollLock(2, 0);
				}
				else if (lockAxis == 'y' || lockAxis == 'Y' || lockAxis == 1)
				{
					layers[i]->setScrollLock(2, 1);
				}
				else
				{
					BOOST_LOG_SEV(layerManagerLogger, ERROR) << indLayer << " does not correspond to a locking axis -- locking failed";
					break;
				}
			}
		}
	}

}

void LayerManager::unlockAll(const char& lockAxis)	//very similar to lockAll
{
	if (dependentScrollLocking)
	{
		for (unsigned int i = 0; i < layers.size(); i++)
		{
			if (layers[i]->getScrollBoundedness() && i != indLayer)
			{
				if (lockAxis == 'x' || lockAxis == 'X' || lockAxis == 0)
				{
					layers[i]->setScrollLock(1, 0);
				}
				else if (lockAxis == 'y' || lockAxis == 'Y' || lockAxis == 1)
				{
					layers[i]->setScrollLock(1, 1);
				}
				else
				{
					BOOST_LOG_SEV(layerManagerLogger, ERROR) << indLayer << " does not correspond to a locking axis -- locking failed";
					break;
				}
			}
		}
	}
}