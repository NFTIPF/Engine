#include "Object.hpp"

using namespace objects;

Object::Object()
{
	
}

Object::~Object(){}

int Object::getID()
{
	return ID;
}

void Object::setID(int newID)
{
	ID = newID;
}

const std::string Object::getType()
{
	return type;
}

void Object::setType(const std::string& newType)
{
	type = newType;
}

bool Object::getActive()
{
	return isActive;
}

void Object::setActive(bool activity)
{
	isActive = activity;
}
