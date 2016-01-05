#pragma once

//standard includes
#include <vector>
#include <string> 

//boost stuff
#include "boost\shared_ptr.hpp"

//project includes
#include "Object.hpp"
#include "NameSearchable\NameSearchable.hpp"
#include "Utilities.hpp"

//This class is a way to organize various groups of objects, for example 
//you may want a group to hold all physics objects and then subgroups for collidables, movables etc

namespace objects
{
	typedef boost::shared_ptr<src::severity_logger<severity_level>> logSharedPtr;	//alias for shared_ptr to a severity logger object

	class ObjectGroup : public NameSearchable
	{
	public:
		ObjectGroup();
		~ObjectGroup();

		ObjectGroup(logSharedPtr logger);


		void setLoggerObject(src::severity_logger<severity_level>& logger);
		void setLoggerObject(logSharedPtr);


		//object vector manipulation functions
		void addObject(boost::shared_ptr<Object>& newObject, const std::string& path="");	//adds object to objects vector inserted in sorted location
		void removeObject(const std::string& path);						//simply removes object from "objects" vector or from any location in tree
		void removeObject(const int& ID);								//removes object by ID
		void removeObject(const boost::shared_ptr<Object>& objectPtr);	//deletes object by searching for specific pointer

		boost::shared_ptr<Object> getObject(const std::string& path);	//returns pointer to specified object, "path" includes ID
		boost::shared_ptr<Object> getObject(const int& ID);			//overloaded for index only, supports arrays

		//ObjectGroup vector manipulation functions
		void addObjectGroup(const ObjectGroup& newGroup, const std::string& name);	//adds new group to "groups" vector
		void addObjectGroup(const std::string& name);

		void deleteObjectGroup(const std::string& groupName);						//physically deallocates specified objectGroup from memory

		ObjectGroup* getObjectGroup(const std::vector<std::string>& pathVec);		//get specified objectgroup ptr
		ObjectGroup* getObjectGroup(const std::string& path);						


		void forceObjectSort();		//essentially checks sorting of objects by ID by sorting everything again using insertion sort

	protected:
		template<class T>
		void deleteObjectFromTree(const T& object)
		{
			removeObject(object);
			for (int i = 0; i < groups.size(); i++)
			{
				groups[i].deleteObjectFromTree(object)
			}
		}

		std::vector<boost::shared_ptr<Object>> objects;		//flexible safe pointers to objects --- should stay sorted from least to greatest
		std::vector<ObjectGroup> groups;					//nesting object group vector this is named using name searchable

		//SHOULD OBJECT GROUP HAVE ITS OWN REAL LOGGER?
		logSharedPtr groupLogger;	//local pointer to logger contained in ObjectManager 

		bool sorted;	//true if the object vector has been sorted by ID else false
	};
}


