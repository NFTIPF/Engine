#include "ObjectManager.hpp"

using namespace objects;

//PUBLIC FUNCTIONS

ObjectManager::ObjectManager()	//default constructor
{
	currentID = 0;	//first ID issued will be "1"
	groupLogger.reset(new src::severity_logger<severity_level>());	//groupLogger must be explicitly defined since the overloaded constructor wasn't called
	BOOST_LOG_SEV(*groupLogger, DEBUG) << "ObjectManager Initialized...";
	
}
ObjectManager::~ObjectManager(){}	//default destructor

int ObjectManager::nextID()
{
	BOOST_LOG_SEV(*groupLogger, DEBUG) << "Returning ID #" << currentID+1;
	return ++currentID;
}
