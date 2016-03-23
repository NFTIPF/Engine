#include "Defines.hpp"	//global #defines

#ifndef RUN_TESTS

#include "Utility/Logger.hpp"
#include "Utility/INIParser.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Utility/Utilities.hpp"
#include "Objects/ObjectManager.hpp"
#include "TestObject.hpp"
#include "Objects/Object.hpp"
#include "Game.hpp"
#include "Utility\XMLParser.hpp"
#include <iostream>

int main(int, char*[])
{

	logger::init();
	logger::setSeverityLevel(DEBUG);
	auto slg = logger::getSLogger();

	Game theGame;
	theGame.initialize("gameConfig.ini", "resources.xml", "objects.xml", "map.xml", "save.xml", 0);
	theGame.begin();	//starts SFML main loop

	BOOST_LOG_SEV(slg, DEBUG) << "Exiting soon";
	return 0;
}

#endif


#ifdef RUN_TESTS


#include "Utility\Logger.hpp"
#include "Utility\UnitTester.hpp"
#include "Utility\Utilities.hpp"

#define TEST_ALL

int main(int, char*[])
{
	logger::init();
	logger::setSeverityLevel(INFO);
	auto slg = logger::getSLogger();

	BOOST_LOG_SEV(slg, INFO) << "Starting Unit Tests...";

	testing::UnitTester testObject;
	testObject.runTests();

	BOOST_LOG_SEV(slg, INFO) << "Unit test completed...";
}

#endif
