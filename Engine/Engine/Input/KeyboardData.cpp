#include "KeyboardData.hpp"


KeyboardData::KeyboardData()
{

}


KeyboardData::~KeyboardData()
{
}


void KeyboardData::keyPressed(const unsigned int keyVal)
{
	keysHit.insert(keyVal);
}


void KeyboardData::keyReleased(const unsigned int keyVal)
{
	if (keysHit.find(keyVal) != keysHit.end())
	{
		keysHit.erase(keysHit.find(keyVal));
	}
	if (keysHeld.find(keyVal) != keysHeld.end())
	{
		keysHeld.erase(keysHeld.find(keyVal));
	}
	
	keysReleased.insert(keyVal);
}



bool KeyboardData::isKeyHit(const int& keyVal)
{
	bool hit = false;
	if (keysHit.find(keyVal) != keysHit.end())
	{
		hit = true;
	}
	return hit;
}


bool KeyboardData::isKeyHeld(const int& keyVal)
{
	bool hit = false;
	if (keysHeld.find(keyVal) != keysHeld.end())
	{
		hit = true;
	}
	else if (keysHit.find(keyVal) != keysHit.end())
	{
		hit = true;
	}
	return hit;
}

bool KeyboardData::isKeyReleased(const int& keyVal)
{
	bool hit = false;
	if (keysReleased.find(keyVal) != keysReleased.end())
	{
		hit = true;
	}
	return hit;
}


void KeyboardData::frameUpdate()
{
	while (keysHit.size() > 0)
	{
		const unsigned int k = *keysHit.begin();
		keysHit.erase(keysHit.begin());
		keysHeld.insert(k);
	}

	while (keysReleased.size() > 0)
	{
		keysReleased.erase(keysReleased.begin());
	}

}