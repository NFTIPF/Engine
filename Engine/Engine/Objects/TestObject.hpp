#pragma once

//project includes
	//include base class
	#include "Object.hpp"	//gets most dependencies from here. Should they be locally #included?

	//XML parser
	#include "../Utility/XMLParser.hpp"
	
	//resource maanger
	#include "../ResourceManager/ResourceManager.hpp"

	//layer
	#include "../Layers/Layer.hpp"

//SFML includes
#include <SFML/Graphics.hpp>

namespace objects
{
//class for testing ObjectManager/group and so on
	class TestObject : public Object
	{
	public:
		TestObject();
		~TestObject();

		void draw(Layer& renderTarget);

		void update(InputData& inpData);

		void load(boost::property_tree::ptree& dataTree, ResourceManager& resources);	//loads instances object properties based on subtree
		boost::property_tree::ptree write();


	private:

		const sf::Texture* testTex;
		sf::VertexArray texCoords;

		sf::Vector2f position;
		sf::Vector2f size;

		std::string textureName;
	};
}