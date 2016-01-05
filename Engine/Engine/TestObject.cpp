#include "TestObject.hpp"

using namespace objects;

TestObject::TestObject(){ counter = 0; }

TestObject::~TestObject(){}

void TestObject::draw(sf::RenderTexture& renderTarget)
{
	//do nothing cuz this doesnt render
}

void TestObject::update()
{
	counter++;	//just a testable counter
}

void TestObject::load()
{
	//INIParser stuff
}

void TestObject::write()
{
	//more INIParser stuff
}

void TestObject::uFunc()
{
	attributeOne = 1;
	attributeTwo = 3;
	nameOne = "One";
	nameTwo = "Two";
	nameThree = "Three";

}

int TestObject::getCounter()
{
	return counter;
}