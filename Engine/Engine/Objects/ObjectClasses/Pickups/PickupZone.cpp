#include "PickupZone.hpp"

using namespace objects;

PickupZone::PickupZone()
{
	displaying = true;
	maxNuts = 1;
}


PickupZone::~PickupZone()
{
}



void PickupZone::setManagerPtrs(ResourceManager& rman, ObjectManager& obMan)
{
	resMan = &rman;
	objMan = &obMan;
}


void PickupZone::draw(Layer& renderTarget)
{
	if (displaying)
	{
		if (!isActive){ return; }
		tex.update();
		tex.draw(*renderTarget.getRenderTexture());
	}
}

void PickupZone::update(InputData& inpData)
{
	if (!isActive){ return; }
	for (int pickIt = 0; pickIt < pickups.size(); pickIt++)
	{
		if (pickups[pickIt] == NULL)	//if the pickup has been deleted (picked up)
		{
			pickups.erase(pickups.begin()+pickIt);	//erase it
			pickIt -= 1;							//move back b/c vector is shorter now
		}
	}
}

void PickupZone::load(boost::property_tree::ptree& dataTree, ResourceManager& rman)
{
	XMLParser parser;
	parser.readValue<double>("topYPos", yVal, dataTree);	//loading x coord
	parser.readValue<double>("leftXPos", xValLeft, dataTree);	//loading y coord
	parser.readValue<double>("rightXPos", xValRight, dataTree);
	parser.readValue<double>("ySize", thickness, dataTree);
	parser.readValue<double>("pickupHoverDistance", gapDist, dataTree);
	parser.readValue<std::string>("seasonName", seasonName, dataTree);
	parser.readValue<int>("rarityThreshold", rarityThreshold, dataTree);
	parser.readValue<int>("maxNuts", maxNuts, dataTree);

	//resMan = &rman;

	size = sf::Vector2f(xValRight - xValLeft, thickness);
	position = sf::Vector2f((xValRight + xValLeft) / 2, yVal + thickness/2);

	distrMax = xValRight - xValLeft;
	//loading texture

	parser.readValue<std::string>("texture", textureName, dataTree);

	sf::Texture* tmpTex = rman.getTexturePointerByName(textureName);
	
	tex = Texture(tmpTex, &position, &size);

}


boost::property_tree::ptree PickupZone::write()
{
	boost::property_tree::ptree properties;

	properties.put("topYPos", yVal);
	properties.put("leftXPos", xValLeft);
	properties.put("rightXPos", xValLeft); 
	properties.put("seasonName", seasonName);
	properties.put("ySize", thickness);
	properties.put("pickupHoverDistance", gapDist);
	properties.put("texture", textureName);
	properties.put("rarityThreshold", rarityThreshold);
	properties.put("maxNuts", maxNuts);

	return properties;
}


void PickupZone::changeSeason(const std::string& newSeason)
{
	seasonName = newSeason;
}

void PickupZone::regeneratePickups()
{
	for (int i = pickups.size(); i < maxNuts; i++)
	{
		generatePickup();
	}
}
void PickupZone::generatePickup()
{

	typedef std::map<std::pair<int, int>, std::string>::iterator it_type;



	int randNum = rand() % distrMax;

	std::string typName;
	for (it_type iterator = distribution.begin(); iterator != distribution.end(); iterator++) {

		// iterator->first = key
		// iterator->second = value
		if (isInBounds(randNum, iterator->first))
		{
			typName = iterator->second;
		}
	}


	const sf::Vector2f default_size(100, 100);


	double randXPos = rand() / (float)(RAND_MAX) * (xValRight - xValLeft - default_size.x / 2) + xValLeft + default_size.x / 2;
	

	

	boost::shared_ptr<Object> protoPickup = objMan->getPrototype("Pickup");

	boost::shared_ptr<Pickup> newPickup = util::downcast<Pickup>(protoPickup);
	newPickup->setup(sf::Vector2f(randXPos , yVal + default_size.y / 2 + gapDist), default_size, typName, *resMan);
	newPickup->setActive(true);

	objMan->addObject(protoPickup, "Layers.Layer1");
	objMan->addObject(protoPickup, "Collidables");
}

void PickupZone::createDistribution()
{
	distribution.clear();


	std::string snames[2] = { "YearRound", seasonName };
	std::vector<std::string> pickupNames;
	std::vector<int> rarities;



	INIParser options("PickupList.ini");

	for (unsigned int j = 0; j < 2; j++)
	{
		
		options.setSection(snames[j]);

		std::string keystr;
		int maxValue;
		options.readValue<std::string>("Key", keystr);
		options.readValue<int>("Max", maxValue);


		for (unsigned int i = 0; i < maxValue; i++)
		{
			std::string numstr = boost::lexical_cast<std::string>(i + 1);

			std::string pname;
			options.readValue<std::string>(keystr + numstr, pname);

			pickupNames.push_back(pname);

		}
	}


	

	for (unsigned int i = 0; i < pickupNames.size(); i++)
	{
		options.setSection(pickupNames[i]);
		int tmprar;
		options.readValue<int>("Rarity", tmprar);

		if (tmprar >= rarityThreshold)
		{
			rarities.push_back(tmprar);
		}

	}

	int tlcm = 1;
	for (unsigned int i = 0; i < rarities.size(); i++)
	{
		tlcm = util::lcm(tlcm, rarities[i]);
	}


	int sum = 0;
	int sumOld = 0;
	for (unsigned int i = 0; i < rarities.size(); i++)
	{
		int hitNumber = tlcm / rarities[i];
		sum += hitNumber;

		distribution[std::make_pair(sumOld, sum)] = pickupNames[i];
		sumOld = sum;
	}

	distrMax = sum;
}


bool PickupZone::isInBounds(const int& val, const std::pair<int, int>& bound)
{
	return ((val < bound.second) && (val >= bound.first));
}
