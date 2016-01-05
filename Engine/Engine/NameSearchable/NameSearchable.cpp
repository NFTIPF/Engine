#include "NameSearchable.hpp"

//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************

NameSearchable::NameSearchable()
{

}

NameSearchable::~NameSearchable()
{

}


//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PROTECTED--------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************

std::string NameSearchable::intToString(int finput)		//converts an int to a string using boost
{
	return boost::lexical_cast<std::string>(finput);	//boost does these things, thank god
}



int NameSearchable::ntoi(const std::string& name)	//accesses the nameMap to get the int associated with the name (assumes the amount of name maps is 1)
													//(Name-to-Index)
{
	return ntoi(name, 0);							//assumes the index is 0
}

int NameSearchable::ntoi(const std::string& name, const int& vecIndex)	//accesses the nameMap to get the int associated with the name
{
	return nameMapVector[vecIndex][name];								//returns the int associated with the name of
																		//the "vecIndexth" vector (for instance, textures as oppesd to fonts)			

}



void NameSearchable::setVectorSize(const int& size)	//resizes the vector of name maps -- typically used only once
{
	std::map<std::string, int> val;
	nameMapVector.resize(size, val);						//resize it
}



void  NameSearchable::addName(const int& intName, const int& mapIndex)	//adds an int 'name' (used for general creation of things) and an
																		//index, assuming the vector index is 0 
{
	addName(intName, 0, mapIndex);										//assumes the vector index is 0
}

void  NameSearchable::addName(const int& intName, const int& vecIndex, const int& mapIndex)	
																		//adds an int 'name', a vector index, and a desired index
{
	std::string tmpString = "Unnamed" + intToString(intName) + ".";		//make a name out of the int (23 -> "Unnamed23.") The '.' is to
																		//prevent multiple copies from having confusing names 
																		//(e.g. add 2 then 2 again, you get "Unnamed2." and "Unnamed2.2"
																		//rather than "Unnamed2" and "Unnamed22")

	addName(tmpString, vecIndex, mapIndex);								//then add the name using the string-ified int
}

void NameSearchable::addName(const std::string& name, const int& mapIndex)	//adds a name and a desired index to map to, assuming the vector index is 0 
{
	addName(name, 0, mapIndex);												//assume the vector index is 0
}

void NameSearchable::addName(std::string name, const int& vecIndex, const int& mapIndex)	
														//the BIG one -- adds a name, an index to correspond to, and a vector index
{
	name += "1";
	int size = name.size();
	int endNumber = 1;
	bool sameName = true;								//true if there may be a duplicate already
	bool firstDuplicate = true;							//true if the duplicate found was the first duplicate

	while (sameName == true)							//go through, finding duplicates
	{
		if (nameMapVector[vecIndex].count(name) == 1)
		{
			endNumber = boost::lexical_cast<int> (name.substr(size - 1, name.size()));				//if there exists a "RedTexture" and a "RedTexture2" already,
			endNumber++;									//and you try to add another "RedTexture",it will become "RedTexture3"		
			name = name.substr(0, size - 1);
			name += intToString(endNumber);
		}
		else
		{
			sameName = false;							//if there is no same name, exit the while loop
		}
	}

	nameMapVector[vecIndex][name] = mapIndex;			//then add the altered name
}
