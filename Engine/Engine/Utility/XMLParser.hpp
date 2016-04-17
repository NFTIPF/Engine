#pragma once

//boost includes
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

//project includes
#include "Logger.hpp"
#include "Utilities.hpp"

//standard includes
#include <string.h>
#include <vector>
#include <map>

template <class T> class xmlTree		//tree for loading xml
{
public:
	std::map<std::string, T> tags;					//input names and values or just names for reading
	std::map<std::string, xmlTree<T>> trees;	//this makes it a tree
	std::vector<std::vector<T> > output;				//filled when tags from tagmap are read

	void branch(const std::string& childName)	//add new tree to tree
	{
		xmlTree<T> branch;
		trees[childName] = branch;
	}
};

class XMLParser
{
public:
	XMLParser();
	~XMLParser();
	XMLParser(const std::string& XMLPath);			//just call setFilePath()

	void init();
	void setFilePath(const std::string& XMLPath);	//fills property tree with xml file data

	void setWorkingPath(const std::string& XMLPath);			//sets the working path and changes subtree to that child
	void setWorkingPathNotSubtree(const std::string& XMLPath);	//sets working path but doesn't get new child --- USE FOR WRITING ONLY
	std::string getWorkingPath();
	
	void writeFile();							//writes property tree to file on disk
	void writeFile(const std::string& XMLPath);	//overloaded for names other than default

	template<class T>
	void readValue(const std::string& path, T& var, const boost::property_tree::ptree& currentTree)
	{
		//tree.get would throw ptree_bad_path (ptree_error) on nonexistent value
		boost::optional<T> op = currentTree.get_optional<T>(path); //returns uninitialized boost::optional object if value != exist

		if (op)
		{
			var = *op;
		}
		else
		{
			BOOST_LOG_SEV(logger, INFO) << "Value not loaded from XML file \"" << filePath << "\": Section=\"" << workingPath << "\" Key=\"" << path << "\"";
		}
	}

	template<class T>
	T readValue(const std::string& path, const boost::property_tree::ptree& currentTree)
	{
		//tree.get would throw ptree_bad_path (ptree_error) on nonexistent value
		T ret;
		readValue<T>(path, ret, currentTree);
		return ret;
	}

	template<class T>
	void readValue(const std::string& path, T& var)		//overloaded for default this.subTree
	{
		readValue(path, var, subTree);
	}

	template<class T>
	void writeValue(const std::string& path, T& var)
	{
		tree.put(assemblePath(path), var);
	}

	template<class T>
	void readTree(xmlTree<T>& data, boost::property_tree::ptree& currentTree)
	{
		std::vector<T> output;	//vector to hold read tag values
		std::map<std::string, T>::iterator tagIt;
		for (tagIt = data.tags.begin(); tagIt != data.tags.end(); tagIt++)	//iterate through tags in children
		{
			T val;
			readValue<T>(tagIt->first, val, currentTree);	//reading value from tag
			output.push_back(val);
		}
		data.output.push_back(output);	//add tag data to output vector

		std::map<std::string, xmlTree<T>>::iterator treeIt;

		for (treeIt = data.trees.begin(); treeIt != data.trees.end(); treeIt++)	//iterate through all children
		{
			BOOST_FOREACH(boost::property_tree::ptree::value_type &v, subTree.get_child(treeIt->first))
			{
				readTree<T>(treeIt->second, v.second);
			}
		}
	}

	template<class T>
	void readTree(xmlTree<T>& data)
	{
		readTree(data, subTree);
	}

	void getSubTree(xmlTree<boost::property_tree::ptree>& data, boost::property_tree::ptree& currentTree);	//recursively searches xmlTree for property trees and returns them in  output

	void getSubTree(xmlTree <boost::property_tree::ptree>& data);											//wrapper for default call with private member "subTree"

	boost::property_tree::ptree getSubTree(const std::string& path);		//gets specified subtree from tree and stores it for later use.

	boost::property_tree::ptree getSubTree();
private:
	std::string assemblePath(const std::string& path);

	boost::property_tree::ptree tree;				//boost class to hand xml parsing
	std::string filePath;							//file to read from
	src::severity_logger<severity_level> logger;	//logging for parser object

	std::string workingPath;				//current position in the xml file
	boost::property_tree::ptree subTree;	//tree starting at current position in file
};
