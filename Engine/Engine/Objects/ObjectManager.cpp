#include "ObjectManager.hpp"

using namespace objects;

//PUBLIC FUNCTIONS

ObjectManager::ObjectManager()	//default constructor
{
	groupLogger.reset(new src::severity_logger<severity_level>());	//groupLogger must be explicitly defined since the overloaded constructor wasn't called
	currentTypeID = 101;
	BOOST_LOG_SEV(*groupLogger, DEBUG) << "ObjectManager Initialized...";
}
ObjectManager::~ObjectManager(){}	//default destructor

void ObjectManager::deleteObject(const int& ID)		//actually deletes object from memory, careful... this could cause issues :z
//public alias for delete object from tree
{
	deleteObjectFromTree(ID);
}

int ObjectManager::getCurrentTypeID()
{
	return currentTypeID;
}

boost::shared_ptr<Object> ObjectManager::getPrototype(const std::string& type)
{
	if (prototypes.find(type) != prototypes.end())	//if the value exists in the map
	{
		boost::shared_ptr<Object> tmp((std::get<0>(prototypes[type]))());	//turns raw pointer into shared_ptr
		int ID = ++std::get<1>(prototypes[type]);
		tmp->setID(ID);								//issues and increments id for that type
		return tmp;
	}
	else    //if the string matches no key value the type must not exist
	{
		BOOST_LOG_SEV(*groupLogger, WARNING) << "String to Object lookup (type = " << type << " ) failed. Type does not exist in lookup table. Returning null...";
		boost::shared_ptr<objects::Object> nullPtr;
		return nullPtr;	//return null ptr -- error handling in recieving functions

	}
}

