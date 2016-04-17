#pragma once


#include "../Defines.hpp"	//global #defines

#ifdef RUN_TESTS

#include "Logger.hpp"
#include <string>
#include <vector>

#include "Utilities.hpp"
#include "Logger.hpp"
#include "..\ResourceManager\ResourceGroup.hpp"
#include "INIParser.hpp"
#include "../Objects/Physics/Collision/HitBoxCollider.hpp"


namespace testing
{

	class UnitTester
	{
	public:
		UnitTester();
		~UnitTester();
		void runTests();

	private:
		src::severity_logger<severity_level> testLogger;

		void utilities();
		void logging();
		void resourceGroup();
		void resourceManager();
		void INIParser();
		void hitboxes();
	};

}
#endif