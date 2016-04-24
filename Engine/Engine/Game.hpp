#pragma once

//boost includes
#include <boost\shared_ptr.hpp>

//SFML includes
#include <SFML\Graphics.hpp>

//project includes
	#include "Defines.hpp"

	//basic management classes
	#include "Objects\ObjectManager.hpp"
	#include "Layers\LayerManager.hpp"
	#include "ResourceManager\ResourceManager.hpp"

	//utility classes
	#include "Utility\Utilities.hpp"
	#include "Utility\INIParser.hpp"
	#include "Utility\Logger.hpp"
	#include "Utility\XMLParser.hpp"

	#include "Input\InputData.hpp"

	#include "MenuStuff\MenuManager.hpp"

	#include "Objects/Squirrel.hpp"
#include "MainMenu.hpp"
	#include "Objects/ObjectClasses/Pickups/Pickup.hpp"
#include "Objects/ObjectClasses/Pickups/PickupZone.hpp"

#include "Objects/Platform.hpp"
#include "Objects/Physics/Collision/Collidable.hpp"
#include "Objects\Physics\Collision\Collider.hpp"
#include "Objects\Home.hpp"
#include "Objects\ParticleSystem.hpp"


class Game
{
public:
	Game();
	~Game();

	void initialize(const std::string& cfgFile, const std::string& resFile, const std::string& objFile, const std::string& mpFile, const std::string& save, const bool& doLoadScreen);	//initializes the game and begins loading of objects
	void begin();			//starts sfml main loop

	void pause();
	void unpause();
protected:
	void setDisplay(const bool& onoff);

	void draw();			//renders drawables to screen
	void update();			//calculates physics, item interactions, etc
	void doChunks();		//calculates chunks and deactivates uneeded objects
	void loadGameConfig(const std::string& configFile);	//loads basic game settings
	void loadResources();	//loads all textures, shaders, etc
	void loadObjects();		//initializes object base types
	void loadMap();			//loads basic map information

	void updateMap();		//finds new bounds and adds/removes objects

	MainMenu mainMenu;

	std::string configFile;
	std::string resourceFile;
	std::string objectFile;
	std::string mapFile;
	std::string saveFile;


	boost::shared_ptr<sf::RenderWindow> windowPtr;
	objects::ObjectManager objMan;
	LayerManager layMan;
	ResourceManager recMan;

	std::string windowName;		//name of the window
	sf::Vector2i renderSize;	//resolution of game
	int maxFPS;					//fps cap - 0 would mean uncapped

	sf::Vector2i chunkSize;		//size in pixels (for now) of each chunk
	sf::Vector2i mapSize;		//size in chunks of the map
	sf::Vector2i mapSizePixel;	//map size in pixels

	sf::Vector2f tmpCenter;

	xmlTree<boost::property_tree::ptree> mapData;
	int numLayers;



	std::map<std::string, std::string> testMap;

	InputData inpData;

	src::severity_logger<severity_level> logger;	//logger to handle debuging and errors


	//GAMEPLAY STUFF
	void organizeObjects();
	void updateCollidables();
	void doCollisions();

	int ghosting;	//id of ghosting platform
	boost::shared_ptr<objects::Squirrel> player;
	boost::shared_ptr<objects::ParticleSystem> part;

	std::map<int, std::vector<boost::shared_ptr<Collidable> > > collidableMap;
	std::vector<boost::shared_ptr<objects::PickupZone> > zones;
	int lastCollidablesSize;

	bool paused;
	bool displaying;
	
};