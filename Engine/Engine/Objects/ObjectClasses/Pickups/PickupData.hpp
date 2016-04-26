#pragma once

#include "../../../Utility/INIParser.hpp"

class PickupData
{
public:
	PickupData();
	PickupData(const int& tness, const int& nscor, const int& rar);
	~PickupData();

	void setup(const int& tness, const int& nscor, const int& rar);

	void setToughness(const int& tness);
	int getToughness();

	void setScore(const int& nscor);
	int getScore();

	void setRarity(const int& rar);
	int getRarity();

	void load(const std::string& sectionName);

	bool isPowerup();
	void setPowerup(const bool& p);


private:

		int toughness;
		int score;
		int rarity;

		bool powerup;
};

