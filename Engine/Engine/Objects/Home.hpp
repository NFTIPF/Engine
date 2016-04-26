#pragma once
#include "DropoffZone.hpp"
#include "..\MenuStuff\MenuManager.hpp"

namespace objects
{
	class Home : public DropoffZone, public MenuManager
	{
		public:
		Home();
		~Home();

		void initialize(ResourceManager* resources);


		void setUpgradePoints(const int& up);



		private:

		int upgradePoints;
		void closeUpgradeMenu();

		void setButtonCallback(const std::string& menuName, const std::string& buttonName, boost::function<void()> fxn, int buttonState);
		
			
	};

}

