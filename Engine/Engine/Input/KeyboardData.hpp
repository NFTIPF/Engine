#pragma once
#include <SFML/Graphics.hpp>
#include <set>

class KeyboardData
{
public:
	KeyboardData();
	~KeyboardData();

	void keyPressed(const unsigned int keyVal);
	void keyReleased(const unsigned int keyVal);


	bool isKeyHit(const int& keyVal);
	bool isKeyHeld(const int& keyVal);	
	bool isKeyReleased(const int& keyVal);

	//bool isKeyUnheld(const int& keyVal); //not useful

	void frameUpdate();						//call once every time frame repeats

private:

	/*template <class T>
	bool setContains(const std::set<T>& set, const T& value)
	{
		if (set.find(value) == set.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}*/

	std::set<const unsigned int> keysHit;
	std::set<const unsigned int> keysHeld;
	std::set<const unsigned int> keysReleased;


};

