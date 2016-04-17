#pragma once

//boost stuff
#include "boost\shared_ptr.hpp"
#include "boost\function.hpp"

//project includes
#include "..\Utility\Logger.hpp"
#include "ObjectGroup.hpp"
#include "..\Utility\Downcast.hpp"
#include <typeinfo>

namespace objects
{
	class ObjectManager : public ObjectGroup
		//most stuff from ObjectGroup
	{
	public:

		ObjectManager();
		~ObjectManager();

		void deleteObject(const int& ID);		//actually deletes object from memory, careful... this could cause issues :z
		int getCurrentTypeID();

		boost::shared_ptr<Object> getPrototype(const std::string& type);

		template<class T>
		void addPrototype(const std::string& type)
		{
			if (prototypes.find(type) != prototypes.end())	//if the object is found
			{
				//give an error because it cannot be added
				BOOST_LOG_SEV(*groupLogger, ERROR) << "Object (type = " << type << " ) was not added to prototype list: an object with that key was found";
			}
			else
			{
				prototypes[type] = std::make_tuple(boost::bind(&ObjectManager::instancePrototype<T>, this), currentTypeID*10000);	//id needs some (4) extra zeros
				currentTypeID++;
			}
		}

	private:
		template<class derived>
		Object* instancePrototype()		//return raw pointer to child of Object
		{
			return new derived();
		}

		int currentTypeID;
		std::map<std::string, std::tuple<boost::function<Object*()>, int> > prototypes;	//function pointer and id iterator for that type
		//ID is an 8 digit integer first 3 are the type ID 4 are the object ID
		//boost::shared_ptr<Object>(ObjectManager::*makeObject)()

		src::severity_logger<severity_level> objectLogger;				//real logger object -- passed to all objectGroups

		typedef boost::shared_ptr<objects::Object> Base;

	};
}




