#include "Game.hpp"



//PUBLIC FUNCTIONS

Game::Game()
{
	logger = logger::getSLogger();
}


Game::~Game(){}

void Game::initialize(const std::string& cfgFile, const std::string& resFile, const std::string& objFile, const std::string& mpFile, const std::string& save, const bool& doLoadScreen)
{
	configFile = cfgFile; resourceFile = resFile; objectFile = objFile; mapFile = mpFile; saveFile = save;
	loadGameConfig(configFile);

	windowPtr = boost::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(renderSize.x, renderSize.y), windowName));
	
	if (maxFPS > 0)
	{
		windowPtr.get()->setFramerateLimit(maxFPS);	//initial FPS limit
	}
	
	loadResources();	//loads texture sounds, etc
		
	loadObjects();		//creates object prototypes
	
	loadMap();			//displays correct objects

	//thats all for now folks
	inpData.frameUpdate();
	
}

void Game::begin()
{
	//sfml main loop
	boost::timer frameTimer;
	sf::RenderWindow& window = *windowPtr;
	window.setKeyRepeatEnabled(false);		//makes it so when a key is hit, only one event is recorded, not nine, or whatever -- ignores holding keys
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		frameTimer.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				for (int i = 0; i < sf::Keyboard::KeyCount; i++)			//KeyCount is the number of Keys; this is intended to check every key
				{
					if (event.key.code == (sf::Keyboard::Key)(i))			//trying to typecast int i as a Key enum 
					{
						inpData.keyPressed(i);
				
					}
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				for (int i = 0; i < sf::Keyboard::KeyCount; i++)
				{
					if (event.key.code == (sf::Keyboard::Key)(i))
					{
						inpData.keyReleased(i);

					}
				}
			}

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					inpData.setTypedChar(static_cast<char>(event.text.unicode));
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				inpData.setMousePosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
			}
			
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					inpData.setRightData(MouseData::Hit);
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					inpData.setLeftData(MouseData::Hit);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					inpData.setRightData(MouseData::Released);
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					inpData.setLeftData(MouseData::Released);
				}
			}

			if (event.type == sf::Event::MouseWheelMoved)
			{
				inpData.setScroll(event.mouseWheel.delta);
			}

		}

		window.clear();

		update();
		draw();

		window.display();

		inpData.frameUpdate();
		frameTimer.elapsed();
	}


}


//PRIVATE FUNCTIONS

void Game::draw()
{

	layMan.setupDraw();										//need to setup draw before objects are drawn


	numLayers = layMan.getLayerAmount();

	for (int i = 0; i < numLayers; i++)	//draw objects to all layers
	{
		boost::function<void(objects::Object&)> draw = boost::bind(&objects::Object::draw, _1, boost::ref(*layMan.getLayerPtr(i)));
		objMan.callFunction<boost::function<void(objects::Object&)> >("Layers.Layer" + boost::lexical_cast<std::string>(i), draw);
	}
	
	layMan.draw(*windowPtr.get());	//actually draw layers to window

}

void Game::update()
{
	doChunks();
	objMan.getObject(1030001)->update(inpData);


	//for each layer
		//get draw bounds for layer
		//remove out of bound objects
		//add new in-bound objects
}

void Game::doChunks()
{
	for (unsigned int layIt = 0; layIt < numLayers; layIt++)	//for each layer
	{
		//reading layer data
		sf::Vector2f TLC = layMan.getLayerPtr(layIt)->getWindowCorners().first;
		sf::Vector2f BRC = layMan.getLayerPtr(layIt)->getWindowCorners().second;

		TLC = sf::Vector2f(std::floor(TLC.x/chunkSize.x), std::floor(TLC.y/chunkSize.y));
		BRC = sf::Vector2f(std::ceil(BRC.x / chunkSize.x), std::ceil(BRC.y / chunkSize.y));

		for (int width = TLC.x; width < (int)BRC.x; width++)
		{
			for (int height = TLC.y; height < (int)BRC.y; height++)
			{
				boost::function<void(objects::Object&)> setActive = boost::bind(&objects::Object::setActive, _1, 1);
				objMan.callFunction<boost::function<void(objects::Object&)> >("Layers.Layer" + boost::lexical_cast<std::string>(layIt)
					+ "." + boost::lexical_cast<std::string>(width) + "." + boost::lexical_cast<std::string>(height), setActive);
			}
		}

	}
}

void Game::loadGameConfig(const std::string& configFile)
{
	INIParser parser(configFile);
	windowName = "Squirrel Game";
	renderSize = sf::Vector2i(960, 540);
	maxFPS = 0;
	mapSize = sf::Vector2i(5, 5);

	parser.setSection("Render_Options");
	parser.readValue<std::string>("Window_Name", windowName);
	parser.readValue<int>("Res_X", renderSize.x); parser.readValue<int>("Res_Y", renderSize.y);
	parser.readValue<int>("FPS_Cap", maxFPS);

	parser.readValue<int>("ChunkSize_X", chunkSize.x);
	parser.readValue<int>("ChunkSize_Y", chunkSize.y);
	if (!chunkSize.y || chunkSize.y == 0){ chunkSize.y = chunkSize.x; }

	parser.readValue<int>("MapSize_X", mapSize.x);
	parser.readValue<int>("MapSize_Y", mapSize.y);

	mapSizePixel = sf::Vector2i(chunkSize.x * mapSize.x, chunkSize.y * mapSize.y);	//the resolution of the map is just the product of chunk size and map size

	parser.setSection("Game_Options");

}

void Game::loadResources()
{
	XMLParser parser(resourceFile);
	
	xmlTree<std::string> groupTree;
	groupTree.branch("resources");

	groupTree.trees["resources"].tags["path"] = "";	//path to resource
	groupTree.trees["resources"].tags["name"] = "";	//storage name of resource
	groupTree.trees["resources"].tags["group"] = "";

	parser.readTree<std::string>(groupTree);		//read data from file and place in output vector

	std::vector<std::string> groups;

	auto &output = groupTree.trees["resources"].output;


	for (unsigned int ii = 0; ii < output.size(); ii++)
	{
		std::vector<std::string> returned = util::splitStrAtSubstr(output[ii][2], ".");					//finds extension from filepath
		std::vector<std::string> numtoadd = util::splitStrAtSubstr(output[ii][0], ":");
		if (returned.size() > 1)	//if the thing has an extension
		{
			recMan.loadFile(output[ii][2], output[ii][1]);	//load each resource


			if (output[ii][0] != "")	//if a third element (being group) exists
			{
				bool groupExists = false;
				for (int groupIt = 0; groupIt < groups.size(); groupIt++)	//cycle through groups
				{
					if (groups[groupIt] == numtoadd[0])
					{
						groupExists = true;
					}
				}

				if (!groupExists)
				{
					recMan.addEmptyResourceGroup(numtoadd[0]);
					groups.push_back(numtoadd[0]);
				}


				for (unsigned int i = 0; i < boost::lexical_cast<int>(numtoadd.back()); i++)
				{
					recMan.addResourcetoResourceGroup(numtoadd[0], output[ii][1], returned.back());	//adds resource to group with type of
				}

			}

		}
		else
		{
			if (numtoadd.size() > 0)	//check if it should be added to group
			{
				recMan.addFilesResourceGroupFromDirectory(returned[0], numtoadd[0]);
			}
			else
			{
				recMan.loadFileDirectory(returned[0]);
			}
		}
	}

}

void Game::loadObjects()
{
	objMan.addPrototype<objects::TestObject>("TestObject");
	objMan.addPrototype<objects::MovingTestObject>("MovingTestObject");
	objMan.addPrototype<objects::Squirrel>("Squirrel");
	objMan.addPrototype<objects::Platform>("Platform");
}

void Game::loadMap()
{
	XMLParser parser(mapFile);

	mapData.trees["map"];
	mapData.tags["layer"];
	mapData.trees["map"].trees[""];
	mapData.trees["map"].tags["chunk"];
	mapData.trees["map"].trees[""].trees[""];
	mapData.trees["map"].trees[""].tags["object"];


	parser.getSubTree(mapData);

	auto& layers = mapData.output;
	auto& chunks = mapData.trees["map"].output;
	auto& objects = mapData.trees["map"].trees[""].output;

	layMan.setLayerAmount(layers[0].size());
	numLayers = layMan.getLayerAmount();

	for (unsigned int layIt = 0; layIt < layers[0].size(); layIt++)	//for each layer
	{
		//reading layer data
		for (int chunkIt = 0; chunkIt < chunks[layIt].size(); chunkIt++)		//for every object
		{
			int chunkNum = 1;	//converted from scalar to vector to get chunk position on map -- starts at #1
			parser.readValue<int>("<xmlattr>.index", chunkNum, chunks[layIt][chunkIt]);
			sf::Vector2i chunk = sf::Vector2i(chunkNum % mapSize.x, chunkNum / mapSize.y);


			for (int objIt = 0; objIt < objects[layIt].size(); objIt++)
			{
				//making a new object
				std::string type = "";
				parser.readValue<std::string>("type", type, objects[chunkIt+layIt][objIt]);	//read type from tree
				auto tmp = objMan.getPrototype(type);						//make object of that type
				tmp->load(objects[layIt][objIt], recMan);
				tmp->setType(type);
				std::string pathString = "Layers.Layer" + boost::lexical_cast<std::string>(layIt);
				pathString += "." + boost::lexical_cast<std::string>(chunk.x);
				pathString += "." + boost::lexical_cast<std::string>(chunk.y);
				objMan.addObject(tmp, pathString);	//appends object to appropriate spot in tree
			}

		}

	}


	tmpCenter = sf::Vector2f(500, 500);							//starting point of reference

	layMan.setReferencePoint(*util::downcast<objects::Squirrel>(objMan.getObject(1030001))->getPosition());						//make sure the layers reference the point

	for (int i = 0; i < numLayers; i++)
	{
		std::string layerNumber = "1";	//default is 1
		parser.readValue<std::string>("<xmlattr>.z", layerNumber, layers[0][i]);

		sf::Vector2f scrollSpeed = sf::Vector2f(0, 0);	//default to not moving
		parser.readValue<float>("<xmlattr>.scrollx", scrollSpeed.x, layers[0][i]);
		parser.readValue<float>("<xmlattr>.scrolly", scrollSpeed.y, layers[0][i]);
		layMan.setScrollSpeed(scrollSpeed, i);

		sf::Vector2f bounds = sf::Vector2f(0, 0);	//maximum bounds of layer
		parser.readValue<float>("<xmlattr>.boundx", bounds.x, layers[0][i]);
		parser.readValue<float>("<xmlattr>.boundy", bounds.y, layers[0][i]);

		layMan.setScrollBounds({ 0, 0, bounds.x, bounds.y}, i);
		layMan.setCorners(sf::Vector2f(0, 0), (sf::Vector2f)windowPtr->getSize(), i);
		layMan.getLayerPtr(i)->setScrollBoundedness(true);

	}
	
	layMan.createLayers();	//i just added this to the constructor...... and it broke 
	layMan.setDependentLocking(true, 0);

	
	
}
