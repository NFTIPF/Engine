#pragma once

#include "Object.hpp"
#include "Physics/Collision/Collidable.hpp"
#include "ObjectClasses/Pickups/Pickup.hpp"

namespace objects
{
	class DropoffZone : public Collidable, public Object
	{
	public:
		DropoffZone();
		~DropoffZone();

		void draw(Layer& renderTarget);
		void update(InputData& inpData);
		void load(boost::property_tree::ptree& dataTree, ResourceManager& rMan);
		boost::property_tree::ptree write();

		std::vector<boost::shared_ptr<objects::Pickup> > getPickupArray();
		boost::shared_ptr<objects::Pickup> getNextPickup();

		bool dropoff(boost::shared_ptr<objects::Pickup> p);
	private:

		int capacity;
		std::vector<boost::shared_ptr<Pickup>> pickups;

		Texture tex;
		std::string textureName;
		bool displaying;

		double minDropTime;
		sf::Clock dropoffClock;

		sf::Vector2f position;
		sf::Vector2f size;
	};
}
