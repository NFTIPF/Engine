#include "UnitTester.hpp"

#ifdef RUN_TESTS



using namespace testing;

UnitTester::UnitTester(){}
UnitTester::~UnitTester(){}

void UnitTester::runTests()
{
#ifdef RUN_ALL	
	utilities();
	logging();
	resourceGroup();
	resourceManager();
	INIParser();
	hitboxes();
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

	#ifdef TEST_HIT_BOXES
			hitboxes();
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

	int one = 1;
	int two = 2;
	int three = 3;

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: int util::imax(int& a, int& b);";
	if(util::imax(one, two) != 2){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::imax failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: int util::imin(int& a, int& b);";
	if(util::imin(one, two) != 1){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::imin failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: void util::ibound(int& a, const int& b, const int& c)";
	util::ibound(three, two, one);
	if(three != 2){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::ibound failed."; }

	double done = 1.1;
	double dtwo = 2.2;
	double dthree = 3.3;

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: double util::dmax(double& a, double& b);";
	if(util::dmax(done, dtwo) != 2.2){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::dmax failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: double util::dmin(double& a, double& b);";
	if(util::dmin(done, dtwo) != 1.1){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::dmin failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: void util::dbound(double& a, const double& b, const double& c)";
	util::dbound(dthree, dtwo, done);
	if(dthree != 2.2){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::dbound failed."; }

	float fone = 1.1;
	float ftwo = 2.2;
	float fthree = 3.3;

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: float util::fmax(float& a, float& b);";
	if(util::fmax(fone, ftwo) != ftwo){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::fmax failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: float util::fmin(float& a, float& b);";
	if(util::fmin(fone, ftwo) != fone){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::fmin failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: void util::fbound(float& a, const float& b, const float& c)";
	util::fbound(fthree, ftwo, fone);
	if(fthree != ftwo){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::fbound failed."; }

	unsigned int uone = 1;
	unsigned int utwo = 2;
	unsigned int uthree = 3;

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: unsigned int util::uimax(unsigned int& a, unsigned int& b);";
	if(util::uimax(uone, utwo) != 2){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::uimax failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: unsigned int util::uimin(unsigned int& a, unsigned int& b);";
	if(util::uimin(uone, utwo) != 1){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::uimin failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: void util::uibound(unsigned int& a, const unsigned int& b, const unsigned int& c)";
	util::uibound(uthree, utwo, uone);
	if(uthree != 2){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::uibound failed."; }

	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: void util::void nullCopyValue(const T& toCopy, T& value);";
	float copy = 3.141;
	float pie;
	util::nullCopyValue<float>(copy, pie);
	if(pie != copy){ BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::nullCopyValue failed."; }
	
	BOOST_LOG_SEV(testLogger, INFO) << "Now testing: void nullCopyVector(const std::vector<T>& toCopy, const std::vector<T>& vec);";
	int nullInt = NULL;
	std::vector<int> mixedVec = { 4, nullInt, 5, nullInt, 124 };
	std::vector<int> startingVec = { 3, 5, 8, 5, 1265 };
	std::vector<int> expectedVec = { 4, 4, 5, 5, 124 };
	util::nullCopyVector<int>(mixedVec, startingVec);
	if (startingVec != expectedVec) { BOOST_LOG_SEV(testLogger, ERROR) << "Input to util::nullCopyVector failed. IN: {4, nullInt, 5, nullInt, 124}, {3, 5, 8, 5, 1265}"; }
	
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

void UnitTester::hitboxes()
{
	HitBoxCollider hbCollider;


	AAHitbox aahb_t1a;
	aahb_t1a.setPosition(0,0);
	aahb_t1a.setSize(100,100);

	AAHitbox aahb_t1b;
	aahb_t1b.setPosition(50, 50);
	aahb_t1b.setSize(100, 100);

	bool testResult = hbCollider.checkCollision(&aahb_t1a, &aahb_t1b);

	BOOST_LOG_SEV(testLogger, DEBUG) << "Double Axis-Aligned Hitbox Collision test 1 should have returned 1 (true). Actually returns: " << testResult << " Corners: hbA: { (-50, -50), (50, 50) }, hbB: { (0, 0), (100, 100) } ";




	AAHitbox aahb_t2a;
	aahb_t2a.setPosition(0, 0);
	aahb_t2a.setSize(100, 100);

	AAHitbox aahb_t2b;
	aahb_t2b.setPosition(500, 500);
	aahb_t2b.setSize(100, 100);

	testResult = hbCollider.checkCollision(&aahb_t2a, &aahb_t2b);


	BOOST_LOG_SEV(testLogger, DEBUG) << "Double Axis-Aligned Hitbox Collision test 2 should have returned 0 (false). Actually returns: " << testResult << " Corners: hbA: { (-50, -50), (50, 50) }, hbB: { (450, 450), (550, 550) } ";

	


	CircularHitbox chb_t1a;
	chb_t1a.setPosition(0, 0);
	chb_t1a.setRadius(60);


	CircularHitbox chb_t1b;
	chb_t1b.setPosition(100, 0);
	chb_t1b.setRadius(60);

	testResult = hbCollider.checkCollision(&chb_t1a, &chb_t1b);

	BOOST_LOG_SEV(testLogger, DEBUG) << "Double Circular Hitbox Collision test 1 should have returned 1 (true). Actually returns: " << testResult << " CircleA: {position: (0,0) rad: 60},  CircleB: {position: (100,0) rad: 60}";



	CircularHitbox chb_t2a;
	chb_t2a.setPosition(0, 0);
	chb_t2a.setRadius(45);


	CircularHitbox chb_t2b;
	chb_t2b.setPosition(100, 0);
	chb_t2b.setRadius(45);

	testResult = hbCollider.checkCollision(&chb_t2a, &chb_t2b);

	BOOST_LOG_SEV(testLogger, DEBUG) << "Double Circular Hitbox Collision test 2 should have returned 0 (false). Actually returns: " << testResult << " CircleA: {position: (0,0) rad: 45},  CircleB: {position: (100,0) rad: 45}";



	CircularHitbox db_t1a;
	db_t1a.setPosition(0, 0);
	db_t1a.setRadius(400);


	AAHitbox db_t1b;
	db_t1b.setPosition(100, 0);
	db_t1b.setSize(100, 100);

	testResult = hbCollider.checkCollision(&db_t1a, &db_t1b);

	BOOST_LOG_SEV(testLogger, DEBUG) << "Diffrent Collision test 1 should have returned 1 (true). Actually returns: " << testResult << " CircleA: {position: (0,0) rad: 400},  BoxB: corners { (50, -50), (150, 50)}";


	CircularHitbox db_t2a;
	db_t2a.setPosition(0, 0);
	db_t2a.setRadius(400);


	AAHitbox db_t2b;
	db_t2b.setPosition(1000, 0);
	db_t2b.setSize(100, 100);

	testResult = hbCollider.checkCollision(&db_t2a, &db_t2b);

	BOOST_LOG_SEV(testLogger, DEBUG) << "Diffrent Collision test 2 should have returned 0 (false). Actually returns: " << testResult << " CircleA: {position: (0,0) rad: 400},  BoxB: corners { (950, -50), (1050, 50)}";




	CircularHitbox db_t3a;
	db_t3a.setPosition(52, 0);
	db_t3a.setRadius(5);


	AAHitbox db_t3b;
	db_t3b.setPosition(0, 0);
	db_t3b.setSize(100, 100);

	testResult = hbCollider.checkCollision(&db_t3a, &db_t3b);

	BOOST_LOG_SEV(testLogger, DEBUG) << "Diffrent Collision test 3 should have returned 1 (true). Actually returns: " << testResult << " CircleA: {position: (52,0) rad: 5},  BoxB: corners { (-50, -50), (50, 50)}";



	CircularHitbox db_t4a;
	db_t4a.setPosition(0,0);
	db_t4a.setRadius(100);


	AAHitbox db_t4b;
	db_t4b.setCorners(sf::Vector2f(72, 72), sf::Vector2f(200, 200));

	testResult = hbCollider.checkCollision(&db_t4a, &db_t4b);

	BOOST_LOG_SEV(testLogger, DEBUG) << "Diffrent Collision test 4 should have returned 0 (false). Actually returns: " << testResult << " CircleA: {position: (0,0) rad: 100},  BoxB: corners { (72, 72), (200, 200)}";


}
#endif