#pragma once

#include "Logger.hpp"
#include <boost\property_tree\ini_parser.hpp>
#include <boost\property_tree\ptree.hpp>
#include <string.h>
#include <vector>
#include "Utilities.hpp"

class INIParser
{
public:
	INIParser();
	~INIParser();
	INIParser(const std::string& INIPath);

	void init();
	void setFilePath(const std::string& INIPath);
	void setSection(const std::string& newSection);

	void writeFile();								//actually writes property tree to file
	void writeFile(const std::string& fileName);	//overloaded for specific name

	template<class T>
	void readValue(const std::string& key, T& var)	//takes a string and return its value loaded from INI
	{
		//tree.get would throw ptree_bad_path (ptree_error) on nonexistent value
		boost::optional<T> op = tree.get_optional<T>(assemblePath(key)); //returns uninitialized boost::optional object if value != exist

		if (op)
		{
			var = *op;
		}
		else
		{
			BOOST_LOG_SEV(logger, INFO) << "Value not loaded from INI file \"" << filePath << "\": Section=\"" << sectionName << "\" Key=\"" << key << "\"";
		}
	}

	template<class T>
	void writeValue(const std::string& key, T value) //writes value to ini file
	{
		tree.put(assemblePath(key), value);		//adds value to tree
		//not necessary to call write_ini every time	
	}

	template<class T>
	void readVector(const std::vector<std::string> &keyNames, std::vector<T>& endVector)	//reads vector of strings and returns vector of matching values as loaded from ini value
	{
		std::vector<T> toReturn;
		for (int i = 0; i < keyNames.size(); i++)
		{
			toReturn.push_back(readValue<T>(keyNames[i])); //get and push back value --- (NOT ASSEMBLING PATH HERE BECAUSE IT IS DONE IN readValue())
		}
		util::nullCopyVector(toReturn, endVector);

	}

	template<class T>
	void writeMap(std::map <std::string, T*>& values)	//writes all keys and their corresponding values from a map
	{
		typedef std::map<std::string, T*>::iterator it;

		for (it i = values.begin(); i != values.end(); i++)	//iterates through map and calls writeValue() function for every key
		{
			writeValue(i->first, *values[i->first]);	
		}
	}

	template<class T>
	void readMap(std::map < std::string, T*>& valMap)
	{
		typedef std::map<std::string, T*>::iterator it;		//construct iterator for map object
		for (it i= valMap.begin(); i != valMap.end(); i++)	//iterate through map
		{
			readValue<T>(i->first, *valMap[i->first]);		//read value and place it in the map --- (NOT ASSEMBLING PATH HERE BECAUSE IT IS DONE IN readValue())
		}
	}

private:
	std::string assemblePath(const std::string& key);	//if section exists concatenate it with the key value

	boost::property_tree::ptree tree;				//boost class that handles ini parsing
	std::string filePath;							//file to read from
	src::severity_logger<severity_level> logger;	//logger to handle debuging and errors
	std::string sectionName;						//name of current section
};

