#pragma once

//project includes
	//include base class
	#include "Objects/Object.hpp"	//gets most dependencies from here. Should they be locally #included?

	//XML parser
	#include "Utility/XMLParser.hpp"
	
	//resource maanger
	#include "ResourceManager/ResourceManager.hpp"

	//layer
	#include "Layers/Layer.hpp"

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
		void update(std::vector<int>& keys);

		void load(boost::property_tree::ptree& dataTree, ResourceManager& resources);	//loads instances object properties based on subtree
		void write();


	private:
		int ID;

		const sf::Texture* testTex;
		sf::VertexArray texCoords;

		sf::Vector2f position;
	};
}