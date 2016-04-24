#pragma once
#include "Layer.hpp"
#include "../Utility/Logger.hpp"
#include <vector>
#include "../Utility/Utilities.hpp"
#include <iostream>


class LayerManager										//holds and manages layers of graphics -- useful for parallax
{
public:

	LayerManager();										//constructor

	LayerManager(const int& amt);						//overloaded to dictate amount of layers at creation

	LayerManager(sf::Vector2f* refPoint);				//overloaded to specify the reference point at creation

	LayerManager(sf::Vector2f* refPoint, const unsigned int& amt);
														//overloaded to specify amount of layers and refernce point

	~LayerManager();									//nothing in destructor

	void setDefaultSize(const sf::Vector2f& s);			//sets new default size for window !!!!needs to be loaded from xml!!!
	void updateWindowSize(const sf::Vector2u size);						//updates dimensions of

	void createLayers();								//creates all the layers -- must call after corners are set




	void addLayer();									//adds a new, empty layer

	void setLayerAmount(const unsigned int& amt);				//sets the amount of layers -- ideally used once only

	unsigned int getLayerAmount();						//returns the amount of layers -- supports iteration




	void setScrollSpeed(const sf::Vector2f& speed, const unsigned int& index);	//set the scroll speed of a particular layer

	void setScrollSpeed(std::vector<const sf::Vector2f> scrollSpeeds);			//set the scroll speed of all layers; should start with 1 and descend



	boost::shared_ptr<Layer> getLayerPtr(const unsigned int& index);			//gets a shared pointer to a layer

	boost::property_tree::ptree getLayerXML(const int& index);						//write layer to boost xml

	void setReferencePoint(sf::Vector2f* refPoint);								//sets the point that the layers will center on


	void setScrollBounds(std::vector<const double> bounds, const unsigned int& layerIndex);	//set all scroll bounds of a single layer

	void setScrollBounds(std::vector<std::vector<const double>> boundVec);	//set all scroll bounds of all layers



	void setCorners(const sf::Vector2f& TLCorner, const sf::Vector2f& BRCorner, const unsigned int& layerIndex);
														//set the corners of a single layer

	void setCorners(std::vector<std::pair<const sf::Vector2f, const sf::Vector2f>> cornerVec);
														//set the corner of every layer


	void setDependentLocking(const bool& b, const unsigned int& indLay);
														//make the layers' scroll-locking dependent on a specific layer


	void setupDraw();									//setup a draw before objects are drawn each frame

	void draw(sf::RenderWindow& window);				//draws all of the layers



private:

	void basicSetup();									//setup called in every constructor

	void lockAll(const char& lockAxis);					//scroll-locks all layers, either x or y -- takes 'y', 'Y', or 1 for y-scroll-locking and 'x', 'X', or 0 for x-scroll-locking

	void unlockAll(const char& lockAxis);				//scroll-unlocks all layers, either x or y



	template<class T> 
	void resizeToMatchLayer(std::vector<T>& vec, const std::string& name)	
														//resizes a vector to match the layer size -- could be weird if vector is wrong size, but hey, you entered it wrong
	{
		if (vec.size() != layers.size())				//if the sizes don't match
		{
			BOOST_LOG_SEV(layerManagerLogger, WARNING) << "The amount of input " << name << " does not match the amount of layers. It was resized to match.";
														//log a warning

			vec.resize(layers.size());					//resize the vector
		}
	}
	

	bool dependentScrollLocking;						//true if dependent scroll locking is enabled

	unsigned int indLayer;								//the index of the independent layer

	//sf::Vector2f defaultSize;							//default size of the layers


	sf::Vector2f* referencePoint;						//The point the LayerManager is centered on

	sf::Vector2f oldReferencePointValue;				//the position of the reference point in the previous frame 


	std::vector<boost::shared_ptr<Layer>> layers;		//vector of shared pointers to Layers


	src::severity_logger<severity_level> layerManagerLogger;	//the logger for layerManager

};

