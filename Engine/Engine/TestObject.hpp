#pragma once

//include base class
#include "Object.hpp"	//gets most dependencies from here. Should they be locally #included?


namespace objects
{
//class for testing ObjectManager/group and so on
	class TestObject : public Object
	{
	public:
		TestObject();
		~TestObject();

		void draw(sf::RenderTexture& renderTarget);
		void update();

		void load();	//still need interface for controlling file names
		void write();

		void uFunc();	//function not defined in base to test downcasting
		int getCounter();
	private:
		int attributeOne;
		float attributeTwo;
		std::string nameOne, nameTwo, nameThree;
		int counter;	//counter for testing update()
	};
}