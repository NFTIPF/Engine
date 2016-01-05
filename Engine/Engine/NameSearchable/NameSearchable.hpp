#pragma once

#include <vector>
#include <map>
#include <sstream>
#include "../Logger.hpp"

class NameSearchable											//A useful parent class to make other classes have standard name maps for vectors
{

public:

	NameSearchable();											//constructor

	~NameSearchable();											//constructor

protected:
	
	std::string intToString(int finput);						//useful function for converting between int to string

	int ntoi(const std::string& name);							//converts a name to an index (vector index is assumed to be 0)

	int ntoi(const std::string& name, const int& vecIndex);		//converts a name to an index using a specific vector index

	

	void setVectorSize(const int& size);						//only call once; fills the Vecotr of Name maps with the desired number of maps


	void addName(const int& intName, const int& mapIndex);		//adds a named number if you dont care about the name
																//(assumed to be put into the first name map)

	void addName(const int& intName, const int& vecIndex, const int& mapIndex);	//adds a named number by index ('1' gets stored as Unnamed.1)

	void addName(const std::string& name, const int& mapIndex);					//adds a name (assumed to be put into the first name map)

	void addName(std::string name, const int& vecIndex, const int& mapIndex);	//adds a name into a certain map to correspond to a certain index
	

	std::vector<std::map<std::string, int> > nameMapVector;						//a vector of hashmaps that maps names to indices (maybe one for textures,
																				//one for fonts, etc.)
		
};

