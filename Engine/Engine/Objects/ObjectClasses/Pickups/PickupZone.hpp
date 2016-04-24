#pragma once
#include "Pickup.hpp"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../../ObjectManager.hpp"

namespace objects
{

	class PickupZone : public Object
	{
	public:
		PickupZone();
		~PickupZone();

		void setManagerPtrs(ResourceManager& rman, ObjectManager& obMan);

		void draw(Layer& renderTarget);
		void update(InputData& inpData);
		void load(boost::property_tree::ptree& dataTree, ResourceManager& rman);

		boost::property_tree::ptree write();

		void changeSeason(const std::string& newSeason);

		void regeneratePickups();
		void generatePickup();
		void createDistribution();

	private:


		bool isInBounds(const int& val, const std::pair<int, int>& bound);

		bool displaying;

		Texture tex;

		std::string textureName;


		double yVal;
		double xValLeft;
		double xValRight;
		double thickness;

		int maxNuts;
		

		sf::Vector2f position;
		sf::Vector2f size;

		std::string seasonName;

		int rarityThreshold;
		std::map<std::pair<int, int>, std::string> distribution;
		int distrMax;
		double gapDist;

		ResourceManager* resMan;
		ObjectManager* objMan;

		std::vector<Pickup*> pickups;

	};



}


