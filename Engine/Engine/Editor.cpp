#include "Editor.hpp"

Editor::Editor()
{
	currentLayer = 1;
	currentLayerMap["Layer"] = "1";

	objID = 1;
	objIDMap["Object ID"] = "1";

	popData = "";
	objectPrompt["Enter Type:"] = "";
	resourcePrompt["Enter Name:"] = "";

	objSelection = false;
	recSelection = false;

	version = 1;
}

Editor::~Editor()
{

}

void Editor::editorInitialize()
{
	loadAttributes("attributes.xml");
	gui.initialize(&recMan);
	
	boost::function<void()> boundFxn = boost::bind(&Editor::promptObjectType, this);
	gui.setButtonCallback("editorMenu", "newObject", boundFxn, 12);

	boundFxn = boost::bind(&Editor::updateSelection, this);
	gui.setButtonCallback("editorMenu", "updateButton", boundFxn, 12);

	boundFxn = boost::bind(&Editor::addResource, this);
	gui.setButtonCallback("editorMenu", "newResource", boundFxn, 12);

	boundFxn = boost::bind(&Editor::saveMap, this);
	gui.setButtonCallback("editorMenu", "save", boundFxn, 12);

	boundFxn = boost::bind(&Editor::selectLayer, this);
	gui.setButtonCallback("editorMenu", "selectLayer", boundFxn, 12);

	boundFxn = boost::bind(&Editor::selectObject, this);
	gui.setButtonCallback("editorMenu", "selectObject", boundFxn, 12);

	boundFxn = boost::bind(&Editor::removeObject, this);
	gui.setButtonCallback("editorMenu", "removeButton", boundFxn, 12);

	loadSavedMap();		//loads objects allready in manager into dynamic memory
	gui.setMap("editorMenu", "selectedObject", currentLayerMap, 1);
	gui.setMap("editorMenu", "selectedLayer", objIDMap, 1);
}

void Editor::editorBegin()
{
	selectObject(1);

	sf::RenderWindow& window = *windowPtr;
	window.setKeyRepeatEnabled(false);		//makes it so when a key is hit, only one event is recorded, not nine, or whatever -- ignores holding keys
	window.setFramerateLimit(60);

	sf::Vector2f start = *player->getPosition();
	while (window.isOpen())
	{
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

		if (gui.getPopData())
		{
			parsePopupOutput();
		}

		update();
		editorUpdate();
		sf::Vector2f mPos = inpData.getMousePosition();
		sf::Vector2f ppos = *player->getPosition() - start;
		sf::Vector2f sspeed = layMan.getLayerPtr(currentLayer)->getScrollSpeed();
		ppos = sf::Vector2f(sspeed.x * ppos.x, sspeed.y*ppos.y);
		sf::Vector2f tmPos = mPos + ppos;
		std::cout << "TMPOS:" << tmPos.x << ", " << tmPos.y << std::endl;


		draw();
		editorDraw();

		window.display();

		inpData.frameUpdate();
	}
}

void Editor::updateSelection()
{
	if (objSelection != recSelection)	//if they are the same something is wrong nothing happens
	{
		if (objSelection)
		{
			updateObject();
		}
		else if (recSelection)
		{
			updateResource();
		}
	}
}
//update needs to allow for GUI and object selection
void Editor::editorUpdate()
{
	//run selection check for (all???) objects or at least the current layer

	//update gui
	gui.update(inpData);
}

//draw needs to draw GUI
void Editor::editorDraw()
{
	//find object with id of currently selected
	//highlight its rectangle bounds

	gui.draw(*windowPtr);	//tell menus to draw
}

void Editor::promptObjectType()
{
	gui.popup(objectPrompt);	//get that object type
	popInfoType = 0;
}

void Editor::addObject()
{
	popData = objectPrompt.begin()->second;
	//check for type validity

	StringMap properties = objectAttributes[popData];
	boost::property_tree::ptree objectRoot;

	try
	{
		auto tempObject = objMan.getPrototype(popData);
		if (!tempObject){ throw; };
		tempObject->setType(popData);
		tempObject->setActive(false);

		idList[tempObject->getID()] = std::make_tuple(objectRoot, properties);
		selectObject(tempObject->getID());

		gui.setMap("editorMenu", "attributeEditor", *objProperties, 5);	//prompt for all object attributes

		std::string pathString = "Layers.Layer" + boost::lexical_cast<std::string>(currentLayer);
		objMan.addObject(tempObject, pathString);
	}
	catch (...){	//catch all exceptions
		BOOST_LOG_SEV(logger, WARNING) << "Object prototype \"" << popData << "\" not found.  Object was not added.";
	}
	//need to catch out of bounds exception coming from prototype creation w/ invalid string	


	//ask for object type
	//get the object stuff and display it with dropdowns options in the gui
	//wait for all input to be complete
	//update object

}

void Editor::editObject()	//edits currently selected object
{
	gui.setMap("editorMenu", "attributeEditor", *objProperties, 5);

	//find object xml by id in storage
	//redisplays option with current selection for editing
	//resaves and updat");
}

void Editor::updateObject()
{
	//actually add the object to game with button press
	//construct object property tree
	//create object prototype and load properties
	//display object
	//save tree in temporary location (not in file)(hard to delete there)
	//save xml
	boost::property_tree::ptree newXml;
	std::map<std::string, std::string>::iterator it;
	for (it = objProperties->begin(); it != objProperties->end(); it++)	//iterate through values and store them in property tree
	{
		newXml.put(it->first, it->second);
	}



	auto tmp = objMan.getObject(objID);	
	newXml.put("type", tmp->getType());
	*objXml = newXml;
	tmp->load(*objXml, recMan);
	tmp->setActive(true);
	//calculate chunk and add here
}

void Editor::selectObject(const int& ID)
{
	SelectionData& toSelect = idList[ID];

	objXml = &std::get<0>(toSelect);
	objProperties = &std::get<1>(toSelect);
	objID = ID;
	objSelection = true;
	recSelection = false;
	objIDMap.begin()->second = boost::lexical_cast<std::string>(ID);
	gui.setMap("editorMenu", "attributeEditor", *objProperties, 5);
}

void Editor::removeObject()	//deletes object xml and clears id from storage
{
	//std::map<int, SelectionData>::iterator it;

	//for (it = idList.begin(); it != idList.end(); it++)
	//{
	//	if (it->second == idList[objID])
	//	{
	//		idList.erase(it);
	//	}
	//}

	idList.erase(objID);


	objMan.deleteObject(objID);

	
	//could add ctrl-z functionality here
}

void Editor::saveMap()
{
	typedef std::vector<boost::property_tree::ptree>::iterator treeIt;

	boost::property_tree::ptree root;
	boost::property_tree::ptree layers;

	std::vector<int> objIDs;
	for (int layIt = 0; layIt < numLayers; layIt++)
	{
		boost::property_tree::ptree layer;
		objIDs = objMan.getObjectGroup("Layers.Layer" + boost::lexical_cast<std::string>(layIt))->getObjectIDs(true);
		layer = std::get<0>(layerList[layIt]);
		boost::property_tree::ptree chunk;
		chunk.add("<xmlattr>.index", 1);
		for (unsigned int IDit = 0; IDit < objIDs.size(); IDit++)
		{
			chunk.add_child("object", std::get<0>(idList[objIDs[IDit]]));
		}

		layer.add_child("chunk", chunk);
		layers.add_child("layer", layer);
	}
	root.add_child("map", layers);
	boost::property_tree::write_xml(saveFile + boost::lexical_cast<std::string>(version), root);	//write xml to file
	version++;
}

void Editor::loadSavedMap()
{
	XMLParser reader;
	boost::property_tree::ptree xml;
	StringMap properties;

	std::vector<int> objIDs = objMan.getObjectGroup("Layers")->getObjectIDs(true);

	for (objID = 0; objID < objIDs.size(); objID++)
	{
		auto tempObj = objMan.getObject(objIDs[objID]);
		
		if (tempObj)
		{
			xml = tempObj->write();

			properties = objectAttributes[tempObj->getType()];	//construct map with current object properties
			StringMap::iterator it;
			for (it = properties.begin(); it != properties.end(); it++)
			{
				reader.readValue<std::string>(it->first, it->second, xml);
			}

			idList[objIDs[objID]] = std::make_tuple(xml, properties);
		}
	}

	for (unsigned int layIt = 0; layIt < numLayers; layIt++)
	{
		layerList[layIt] = std::make_tuple (layMan.getLayerXML(layIt), objectAttributes["layer"]);
	}
}

void Editor::reloadObjects()
{
	std::map<int, SelectionData>::iterator it;
	for (it = idList.begin(); it != idList.end(); it++)
	{
		reloadObject(it->first);
	}
}

void Editor::reloadObject(const int& ID)
{

}

void Editor::promptResourceName()
{
	gui.popup(resourcePrompt);
}
void Editor::addResource()
{
	popData = resourcePrompt.begin()->second;
	boost::property_tree::ptree filler;
	resourceList[popData] = std::make_tuple(filler, objectAttributes["resource"]);
	selectResource(popData);
	gui.setMap("editorMenu", "attributeEditor", *currentRecMap, 1);
}

void Editor::editResource()
{
	gui.setMap("editorMenu", "attributeEditor", *currentRecMap, 1);
}

void Editor::updateResource()
{
	//add resource to manager
	std::vector<std::string> returned = util::splitStrAtSubstr((*currentRecMap)["path"], ".");					//finds extension from filepath
	std::vector<std::string> numtoadd = util::splitStrAtSubstr((*currentRecMap)["group"], ":");
	if (returned.size() > 1)	//if the thing has an extension
	{
		recMan.loadFile((*currentRecMap)["path"], (*currentRecMap)["name"]);
	}
	else
	{
		if ((*currentRecMap)["group"] != "")	//check if it should be added to group
		{
			recMan.addFilesResourceGroupFromDirectory(returned[0], numtoadd[0]);
		}
		else
		{
			recMan.loadFileDirectory(returned[0]);
		}
	}
	
	StringMap::iterator it;
	boost::property_tree::ptree& recTree = std::get<0>(resourceList[currentRecName]);
	for (it = currentRecMap->begin(); it != currentRecMap->begin(); it++)	//writing new resource data to xml
	{
		recTree.put(it->first, it->second);
	}
	//make sure it actually added before grouping
	//check if group
		//check for group existence
		//if exists nothing
		//if not create
		//add to group
	
}

void Editor::removeResource()
{

}

void Editor::selectResource(const std::string& name)
{
	currentRecMap = &std::get<1>(resourceList[name]);
	currentRecName = name;
	objSelection = false;
	recSelection = true;
}

void Editor::addLayer()
{
	boost::property_tree::ptree tree;
	numLayers++;
	layerList[numLayers+1] = std::make_tuple (tree, objectAttributes["layer"]);
	selectLayer(numLayers);
	gui.setMap("editorMenu", "attributeEditor", std::get<1>(layerList[currentLayer]), 5);
}

void Editor::editLayer()	//this can't actually happen cuz layers and time
{
	gui.setMap("editorMenu", "attributeEditor", std::get<1>(layerList[currentLayer]), 5);
}

void Editor::selectLayer(const int& index)
{
	currentLayer = boost::lexical_cast<int>(currentLayerMap.begin()->second);
}

void Editor::updateLayer()
{
	StringMap& layerProperties = std::get<1>(layerList[currentLayer]);

	std::string layerNumber = "1";	//default is 1
	layerNumber = layerProperties["<xmlattr>.z"];

	sf::Vector2f scrollSpeed = sf::Vector2f(boost::lexical_cast<int>(layerProperties["<xmlattr>.scrollx"]),
		boost::lexical_cast<int>(layerProperties["<xmlattr>.scrolly"]));	//default to not moving

	layMan.setScrollSpeed(scrollSpeed, currentLayer);

	sf::Vector2f bounds = sf::Vector2f(boost::lexical_cast<int>(layerProperties["<xmlattr>.boundx"]),
		boost::lexical_cast<int>(layerProperties["<xmlattr>.boundy"]));	//maximum bounds of layer

	layMan.setScrollBounds({ 0, 0, bounds.x, bounds.y }, currentLayer);
	layMan.setCorners(sf::Vector2f(0, 0), (sf::Vector2f)windowPtr->getSize(), currentLayer);
	layMan.getLayerPtr(currentLayer)->setScrollBoundedness(true);

	std::get<0>(layerList[currentLayer]) = layMan.getLayerXML(currentLayer);
}

void Editor::saveResources()
{
	boost::property_tree::ptree file;
	boost::property_tree::ptree resourceRoot;

	std::map<std::string, SelectionData>::iterator it;
	for (it = resourceList.begin(); it != resourceList.end(); it++)		//cyle through resources and write their xml together
	{
		resourceRoot.add_child("resource", std::get<0>(it->second));
	}
}

void Editor::loadAttributes(const std::string& path) //loads object attributes from set of files....??
{
	XMLParser attrLoader("attributes.xml");

	xmlTree<boost::property_tree::ptree> attrTree;

	attrTree.trees["types"];
	attrTree.tags["type"];
	attrTree.trees["types"].trees[""];
	attrTree.trees["types"].tags["attr"];

	attrLoader.getSubTree(attrTree);

	auto& types = attrTree.output;
	auto& attributes = attrTree.trees["types"].output;

	std::string tmp;
	for (int typeIt = 0; typeIt < types[0].size(); typeIt++)
	{
		StringMap attrMap;
		for (int attrIt = 0; attrIt < attributes[typeIt].size(); attrIt++)
		{
			attrLoader.readValue<std::string>("<xmlattr>.attr", tmp, attributes[typeIt][attrIt]);
			attrMap[tmp] = "";
		}
		attrLoader.readValue<std::string>("<xmlattr>.name", tmp, types[0][typeIt]);
		objectAttributes[tmp] = attrMap;
	}

	//for files in directory
	//load file name
	//while getline load attribute to that map
	//done

	//somehow get stringified object prototype names (xml format?)
}

//PRIVATE FUNCTIONS

void Editor::parsePopupOutput()
{
	gui.setPopData(0);

	switch (popInfoType)	//figure out which version of the popup it was
	{
	case 0: addObject();
		break;
	case 1: addResource();
		break;
	}

	//reset the entryt table
	resourcePrompt.begin()->second = "";
	objectPrompt.begin()->second = "";
}


void Editor::resetMap(StringMap& smap)
{
	std::map<std::string, std::string>::iterator it;
	for (it = smap.begin(); it != smap.end(); it++)
	{
		smap[it->first] = "";
	}
}

void Editor::selectLayer()
{
	currentLayer = boost::lexical_cast<int>(currentLayerMap.begin()->second);
}

void Editor::selectObject()
{
	selectObject(boost::lexical_cast<int>(objIDMap.begin()->second));
}