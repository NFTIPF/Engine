#pragma once

//sfml includes
#include "SFML/Graphics.hpp"

//project includes
#include "..\Utility\Utilities.hpp"
#include "..\Utility\XMLParser.hpp"	//this will be used in load/write

#include "..\ResourceManager\ResourceManager.hpp";

#include "..\Layers\Layer.hpp"
#include "..\Input\InputData.hpp"

namespace objects
{
	class Object	//virtual class template for basic Object type
	{
	public:
		Object();
		~Object();

		//public interfaces to private members
		int getID();
		void setID(int newID);

		const std::string getType();
		void setType(const std::string& newType);

		bool getActive();
		void setActive(bool activity);

		//base virtual functions
		virtual void draw(Layer& renderTarget) = 0;		//renders object to given sf::RenderTexture&

		virtual void update(InputData& inpData) = 0;


		virtual void load(boost::property_tree::ptree& dataTree, ResourceManager&) = 0;	//defined in children to load from (INI?) file
		virtual boost::property_tree::ptree write() = 0;	//defined in children to write to (INI?) file

	protected:
		int ID;				//unique ID for this instance of object
		bool isActive;		//wether or not the object will be drawn/updated etc
		std::string type;

	};
}
