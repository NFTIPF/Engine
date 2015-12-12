#pragma once
#include <vector>
#include <map>
#include <sstream>

class NameSearchable										//A useful parent class to make other classes have standard name maps for vectors
{

public:

	NameSearchable();										//constructor

	~NameSearchable();										//constructor

protected:
	
	std::string intToString(int finput);					//useful function for converting between int to string

	int ntoi(std::string fname);							//converts a name to an index (vector index is assumed to be 0)

	int ntoi(std::string fname, int findex);				//converts a name to an index using a specific vector index

	

	void setVectorSize(int fsize);							//only call once; fills the Vecotr of Name maps with the desired number of maps


	void addName(int fintname, int fend);					//adds a named number if you dont care about the name (assumed to be put into the first name map)

	void addName(int fintname, int findex, int fend);		//adds a named number by index ('1' gets stored as Unnamed.1)

	void addName(std::string fname, int fend);				//adds a name (assumed to be put into the first name map)

	void addName(std::string fname, int findex, int fend);	//adds a name into a certain map to correspond to a certain index
	

	std::vector<std::map<std::string, int> > nameMapVector;	//a vector of hashmaps that maps names to indices (maybe one for textures, one for fonts, etc.)

};

