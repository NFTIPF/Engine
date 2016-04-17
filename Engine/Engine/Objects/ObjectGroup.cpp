#include "ObjectGroup.hpp"

using namespace objects;

//PUBLIC FUNCTIONS

ObjectGroup::ObjectGroup()
{
	setVectorSize(1);	//tell nameSearchable that only one vector (ObjectGroups) will be named

}
ObjectGroup::~ObjectGroup(){}	//default constructor

ObjectGroup::ObjectGroup(logSharedPtr logger)
{
	groupLogger = logger;
}

void ObjectGroup::setLoggerObject(logSharedPtr logger)
{
	groupLogger = logger;
}

void ObjectGroup::addObject(boost::shared_ptr<Object>& newObject, const std::string& path)
{
	ObjectGroup* group = this;	//group which object will be added to 

	if (path != "")
	{
		std::vector<std::string> pathVec = util::splitStrAtSubstr(path, ".");

		for (int i = 0; i < pathVec.size(); i++)	//make sure the path exists
		{
			if (group->nameMapVector[0].find(pathVec[i]) != group->nameMapVector[0].end())	//if the group allready exists
			{

				group = group->getObjectGroup(pathVec[i]);

			}
			else
			{
				group->addObjectGroup(pathVec[i]);		//add group
				group = group->getObjectGroup(pathVec[i]);
			}
		}
		//group = getObjectGroup(path);	//get the object group from the path just verified/created 
	}
	else
	{
		group = this;	//otherwise, the object should be added to this instance of ObjectGroup
	}


	group->objects.push_back(newObject);	//add the object
}

void ObjectGroup::removeObject(const std::string& path)
{
	removeObject(getObject(path));	//just gets the object ptr and deletes with that
}

void ObjectGroup::removeObject(const int& ID)
{
	auto obj = getObject(ID, false);
	removeObject(obj);	//just gets the object ptr and deletes with that
}

void ObjectGroup::removeObject(const boost::shared_ptr<Object>& objectPtr)
{
	auto it = std::find(objects.begin(), objects.end(), objectPtr);	//get iterator to object if it exists
	if (it != objects.end())	//check if value was actually found
	{
		objects.erase(it);		//erase object
	}
	else //otherwise give a debug message
	{
		BOOST_LOG_SEV(*groupLogger, WARNING) << "Object deletion failed... Object ptr not found.";
	}

}


boost::shared_ptr<Object> ObjectGroup::getObject(const std::string& path)
{
	std::vector<std::string> pathVec = util::splitStrAtSubstr(path, ".");
	int ID = boost::lexical_cast<int, std::string>(pathVec[pathVec.size()-1]);	//convert ID string to int
	pathVec.erase(pathVec.end()-1);			//get rid of the id remove the ID from the vector

	return getObjectGroup(util::vecToStr(pathVec, "."))->getObject(ID);	//retrieves object group from reconstructed string and return objPtr
}

boost::shared_ptr<Object> ObjectGroup::getObject(const int& ID, const bool& tree)	//quick binary search
{
	if (objects.size() != 0)
	{
		forceObjectSort();

		int position;
		int comparisonCount = 1;    //count the number of comparisons (optional)

		// To start, find the subscript of the middle position.
		position = (objects.size()) / 2;

		int lowerbound = 0;
		int upperbound = objects.size();

		while ((lowerbound < upperbound) && (objects[position]->getID() != ID))	
		{
			comparisonCount++;
			if (objects[position]->getID() > ID)               // If the number is > key, ..
			{                                                       // decrease position by one.
				upperbound = position - 1;
			}
			else
			{                                                        // Else, increase position by one.
				lowerbound = position + 1;
			}
			position = (lowerbound + upperbound) / 2;
			if (position >= objects.size())
			{
				goto AVOID_ERRORS;
			}
		}
		if (objects[position]->getID() == ID)
		{
			return objects[position];
		}
		else
		{
			BOOST_LOG_SEV(*groupLogger, ERROR) << "Object with ID = " << ID << " not found in group.";
			return NULL;
		}
	AVOID_ERRORS:;
	}
	if (tree)	//only do this if the entire tree should be searched for object
	{
		for (int i = 0; i < groups.size(); i++)
		{
			boost::shared_ptr<Object> tmp = groups[i].getObject(ID);
			if (tmp)
			{
				return tmp;
			}
		}
	}
	
}

void ObjectGroup::addObjectGroup(const ObjectGroup& newGroup, const std::string& name)
{
	groups.push_back(newGroup);
	addName(name, 0, groups.size() - 1);
}

void ObjectGroup::addObjectGroup(const std::string& name)
{
	ObjectGroup tmp;					//temporary group object
	tmp.setLoggerObject(groupLogger);	//assign this logger to new group
	groups.push_back(tmp);				//add new group to list of all groups
	addName(name, 0, groups.size() - 1);//index by name
}

void ObjectGroup::deleteObjectGroup(const std::string& path)
{
	std::vector<std::string> pathVec = util::splitStrAtSubstr(path, ".");	//split path into 
	if (pathVec.size() > 1)
	{
		std::string toDelete = *pathVec.end();	//get the last element of the vector
		ObjectGroup *tmpGroup = getObjectGroup(util::vecToStr(pathVec, "."));
		tmpGroup->deleteObjectGroup(toDelete);	//calls delete on that specific object group since groups is private
	}
	else
	{
		groups.erase(groups.begin() + ntoi(path));
	}
	
}

ObjectGroup* ObjectGroup::getObjectGroup(const std::vector<std::string>& pathVec)
{
	ObjectGroup* tmpGroup = this;

	for (int i = 0; i < pathVec.size(); i++)	//increments until second-to-last spot since the ID is the last
	{
		tmpGroup = &(tmpGroup->groups[tmpGroup->ntoi(pathVec[i])]);	//requests next object group by name and assigns it to temp object
	}

	return tmpGroup;
}

ObjectGroup* ObjectGroup::getObjectGroup(const std::string& path)
{
	std::vector<std::string> pathVec = util::splitStrAtSubstr(path, ".");	//parses "path" to individual directories

	return getObjectGroup(pathVec);
}

std::vector<int> ObjectGroup::getObjectIDs(bool recursive)
{
	std::vector<int> ret;
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		ret.push_back(objects[i]->getID());
	}
	for (unsigned int groupIt = 0; groupIt < groups.size(); groupIt++)
	{
		std::vector<int> groupRet = groups[groupIt].getObjectIDs();
		ret.insert(ret.end(), groupRet.begin(), groupRet.end());
	}
	return ret;
}

void ObjectGroup::forceObjectSort()	//could be more efficient but really shouldn't be called too much
{
	int currentInsert = 0;

	//insertion sort
	for (unsigned int i = 0; i < objects.size(); i++)	//iterate through objects starting on second
	{
		currentInsert = 0;
		while (i > 0 && objects[i - 1]->getID() > objects[i]->getID())	//while the place i-1 is higher than place i
		{
			iter_swap(objects.begin() + i - 1, objects.begin() + i);	//swap places
		}
	}
}

//PROTECTED FUNCTIONS

void ObjectGroup::deleteObjectFromTree(const int& ID)
{
	removeObject(ID);
	for (int i = 0; i < groups.size(); i++)
	{
		groups[i].deleteObjectFromTree(ID);
	}
}

//PRIVATE FUNCTIONS

