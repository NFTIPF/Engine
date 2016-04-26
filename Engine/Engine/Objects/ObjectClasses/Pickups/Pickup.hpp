#pragma once
#include "../../Physics/Collision/Collidable.hpp"
#include "../../Object.hpp"
#include "PickupData.hpp"

#include "../../../Utility/INIParser.hpp"
#include "../../Graphics/Texture.hpp"

namespace objects
{


	class Pickup : public Collidable, public Object
	{
	public:
		Pickup();
		~Pickup();

		void setup(const sf::Vector2f& pos, const sf::Vector2f& siz, const std::string& pnam, ResourceManager& rman);

		void draw(Layer& renderTarget);
		void update(InputData& inpData);
		void load(boost::property_tree::ptree& dataTree, ResourceManager& rman);
		boost::property_tree::ptree write();


		bool isRemoved();

		PickupData getPickupData();

	private:

		void subSetup(ResourceManager& rman);
		std::string getTexName(const std::string& typname);


		bool removed;


		PickupData pdata;


		sf::Vector2f position;
		sf::Vector2f size;

		std::string pickupName;

		Texture tex;
	};

}