#include "UnitTester.hpp"

#ifdef RUN_TESTS

#include "Utilities.hpp"
#include "Logger.hpp"
#include "ResourceManager\ResourceGroup.hpp"
#include "ResourceManager\ResourceGroup.hpp"
#include "INIParser.hpp"

using namespace testing;

UnitTester::UnitTester(){}
UnitTester::~UnitTester(){}

void UnitTester::runTests()
{
#ifdef TEST_ALL	
	utilities();
	logging();
	resourceGroup();
	resourceManager();
	INIParser();
#elif
	#ifdef TEST_UTILITIES
		utilities();
	#endif
	#ifdef TEST_LOGGING
			logging();
	#endif
	#ifdef TEST_RESOURCE_GROUP
			resourceGroup();
	#endif
	#ifdef TEST_RESOURCE_MANAGER
			resourceMananager();
	#endif
	#ifdef TEST_INI_PARSER
			INIParser();
	#endif
#endif
}

//PRIVATE FUNCTIONS

void UnitTester::utilities()
{


	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: void util::swapChars(char& a, char& b);";
	char a = 'a', b = 'b';
	util::swapChars(a, b);
	if (a != 'b' || b != 'a') { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::swapChars failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: std::string util::reverseString(const std::string& str);";
	if (util::reverseString("myString") != "gnirtSym") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"myString\""; }
	if (util::reverseString("MYSTRING ") != " GNIRTSYM") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"MYSTRING \""; }
	if (util::reverseString("aaaaaa") != "aaaaaa") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"aaaaaa\""; }
	if (util::reverseString("This Is An Extended TEST") != "TSET dednetxE nA sI sihT") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"This Is An Extended Test\""; }
	if (util::reverseString("\"\\\"Escape") != "epacsE\"\\\"") { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::reverseString failed.  IN: \"\"\\\"Escape\""; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: std::vector<std::string> util::splitStrAtSubstr(const std::string& str, const std::string& split)";
	std::vector<std::string> expected = { "One", "Two", "Three" };
	std::vector<std::string> expected2 = { "One", "Three" };
	std::vector<std::string> expected3 = { "OneTwoThree" };
	if (util::splitStrAtSubstr("One.Two.Three", ".") != expected) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::splitStrAtSubstr failed. IN: \"One.Two.Three\", \".\""; }
	if (util::splitStrAtSubstr("One\"Two\"Three", "\"") != expected) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::splitStrAtSubstr failed. IN: \"One\"Two\"Three\", \"\"\""; }
	if (util::splitStrAtSubstr("OneTwoThree", ".") != expected3) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::splitStrAtSubstr failed. IN: \"One.Two.Three\", \".\""; }
	if (util::splitStrAtSubstr("OneTwoThree", "Two") != expected2) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::splitStrAtSubstr failed. IN: \"OneTwoThree\", \"Two\""; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: std::string util::vecToStr(const std::vector<std::string>& vec, const std::string& between);";
	std::vector<std::string> in1 = {"One", "Two", "Three"}; std::string in12 = "."; std::string out1 = "One.Two.Three";
	std::vector<std::string> in2 = {"Hello", "World"}; std::string in22 = " To The "; std::string out2 = "Hello To The World";
	std::string out3 = "OneTwoThree";
	if (util::vecToStr(in1, in12) != out1){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::vecToStr failed.  IN: {One, Two, Three}, \".\""; }
	if (util::vecToStr(in2, in22) != out2) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::vecToStr faile. IN: {Hello, World}, \" To The \""; }
	if (util::vecToStr(in1, "") != out3) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::vecToStr filed. IN: {One, Two, Three}, NOTHING"; }

	/*
	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: void nullCopyVector(const std::vector<T>& toCopy, const std::vector<T>& vec);";
	int nullInt = NULL;
	std::vector<int> mixedVec = { 4, nullInt, 5, nullInt, 124 };
	std::vector<int> startingVec = { 3, 5, 8, 5, 1265 };
	std::vector<int> expectedVec = { 4, 4, 5, 5, 124 };
	util::nullCopyVector<int>(mixedVec, startingVec);
	if (startingVec != expectedVec) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::nullCopyVector failed. IN: {4, nullInt, 5, nullInt, 124}, {3, 5, 8, 5, 1265}"; }
	*/
}

void UnitTester::logging()
{

}

void UnitTester::resourceGroup()
{

}

void UnitTester::resourceManager()
{
	
}

void UnitTester::INIParser()
{

}
#endif