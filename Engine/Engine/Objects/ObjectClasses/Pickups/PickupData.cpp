#include "PickupData.hpp"


PickupData::PickupData()
{
}

PickupData::PickupData(const int& tness, const int& nscor, const int& rar)
{
	setup(tness, nscor, rar);
}


PickupData::~PickupData()
{

}


void PickupData::setup(const int& tness, const int& nscor, const int& rar)
{
	setToughness(tness);
	setScore(nscor);
	setRarity(rar);
}

void PickupData::setToughness(const int& tness)
{
	toughness = tness;
}

int PickupData::getToughness()
{
	return toughness;
}

void PickupData::setScore(const int& nscor)
{
	score = nscor;
}

int PickupData::getScore()
{
	return score;
}

void PickupData::setRarity(const int& rar)
{
	rarity = rar;
}

int PickupData::getRarity()
{
	return rarity;
}

void PickupData::load(const std::string& sectionName)
{
	INIParser options("PickupList.ini");

	options.setSection(sectionName);

	options.readValue<int>("Toughness", toughness);
	options.readValue<int>("Score", score);
	options.readValue<int>("Rarity", rarity);
}

bool PickupData::isPowerup()
{
	return powerup;
}

void PickupData::setPowerup(const bool& p)
{
	powerup = p;
}