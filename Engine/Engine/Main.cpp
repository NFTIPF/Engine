#include "Defines.hpp"	//global #defines

#ifndef RUN_TESTS

#include "Logger.hpp"
#include "INIParser.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Utilities.hpp"
#include "ObjectManager.hpp"
#include "TestObject.hpp"
#include "Object.hpp"

void logging_function()
{
	//BOOST_LOG_NAMED_SCOPE("INI_Reader_Testing");											<<--- adds specified namespace to logs in all nested scopes
	//BOOST_LOG_SCOPED_THREAD_ATTR("Timeline", attrs::timer()));							<<--- adds timer to logs in all nested scopes
	//severity_logger.add_attribute("Tag", attrs::constant<std::string>("<yourstring>"));	<<--- adds tag attribute in brackets ex. [<yourstring>]

	INIParser reader("config.ini");

	int one =3, two = 1, three = 3;
	reader.setSection("Beans");
	std::map<std::string, int*> variables;
	variables["Ehhh"] = &one;
	variables["Meh"] = &two;
	variables["Heh"] = &three;
	std::string testing = "test";
	reader.readValue<std::string>("string", testing);
	reader.readMap<int>(variables);

	reader.setSection("");
	reader.writeValue<int>("Eugene.cookies", 7);	//Adds header called "eugene" with an attribute called "cookies" which has a value of 7

	reader.writeMap<int>(variables);				//writeMap() test
	reader.readMap<int>(variables);



	auto slg = logger::getSLogger();
	slg.add_attribute("Scope", attrs::named_scope());
	int cookies = 1;
	reader.readValue<int>("Eugene.cookies", cookies);
	//BOOST_LOG_SEV(slg, DEBUG) << "This is the first value as a string. " << reader.readValue<std::string>("Beans.Smoky");
	BOOST_LOG_SEV(slg, ERROR) << "Array values as int. " << one << " + " << two;
	BOOST_LOG_SEV(slg, INFO) << "This is a string: " << testing;
	BOOST_LOG_SEV(slg, ERROR) << "Eugene's cookies: " << cookies;

}



int main(int, char*[])
{

	logger::init();
	logger::setSeverityLevel(DEBUG);
	//logging_function();
	auto slg = logger::getSLogger();

	objects::ObjectManager OhMan;
	util::Downcaster<objects::Object> dc;

	boost::shared_ptr<objects::Object> tmp(new objects::TestObject);
	tmp->setID(OhMan.nextID());

	
	OhMan.addObject(tmp, "Test.Update");

	auto testObject = dc.downcast(OhMan.getObject("Test.Update.1"));
	
	for (unsigned int i = 0; i < 100; i++)
	{
		testObject->update();
		BOOST_LOG_SEV(slg, INFO) << testObject->getCounter();
	}
	//util::splitStrAtSubstr("One.Two.Three", ".");
	//util::reverseString("aaaaa");
	//std::string directoryToResources = boost::filesystem::current_path().string() + "\\Resources\\";
	//ResourceManager testRM;
	//testRM.addFilesResourceGroupFromDirectory(directoryToResources + "TestResources");

	for (int i = 0; i < 40; i++){
		testRM.addFile(directoryToResources + "TestResources\\ModernArtBlue.png", "ModernArtBlueTest");
	}


	BOOST_LOG_SEV(slg, DEBUG) << "Exiting soon";
	//while (true){}
	return 0;
}

#endif


#ifdef RUN_TESTS


#include "Logger.hpp"
#include "UnitTester.hpp"
#include "Utilities.hpp"

#define TEST_ALL

int main(int, char*[])
{
	logger::init();
	logger::setSeverityLevel(INFO);
	auto slg = logger::getSLogger();

	BOOST_LOG_SEV(slg, INFO) << "Starting Unit Tests...";

	testing::UnitTester testObject;
	testObject.runTests();

	BOOST_LOG_SEV(slg, INFO) << "Unit test completed...";
}

#endif
