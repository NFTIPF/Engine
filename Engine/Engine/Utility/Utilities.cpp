#include "Utilities.hpp"

using namespace util;
/*
void swapChars(char& a, char& b)
{
	char tmp = a;
	a = b;
	b = tmp;
}


std::string util::intToString(int finput)		//converts an int to a string using boost
{
	return boost::lexical_cast<std::string>(finput);	//boost does these things, thank god
}

std::string util::reverseString(const std::string& str)
{
	std::stack<char> string;

	for (int i = 0; i < str.size(); i++)	//push all chars into stack
	{
		string.push(str[i]);
	}

	std::string toReturn = "";	//initialize empty string

	const int size = string.size();	//store the largest size
	for (int i = 0; i < size; i++)	//store then pop back values in reverse order
	{
		toReturn += string.top();
		string.pop();
	}

	return toReturn;
}


std::vector<std::string> splitStrAtSubstr(const std::string& str, const std::string& split)
{
	int lastHit = 0; //stores location of last split
	std::vector<std::string> splits;
	const int size = splits.size();
	for (int i = 0; i < str.size(); i++)	//iterate through string
	{
		std::string debug = str.substr(i, split.size());
		if (str.substr(i, split.size()) == split)	//once the split is found
		{
			splits.push_back(str.substr(lastHit, i-lastHit));	//add the section before the split
			i += split.size();							//move i to the end of the split
			lastHit = i;								//the current i is the character after the split
		}
	}
	splits.push_back(str.substr(lastHit, str.size()));	//push back any characters after the final split

	return splits;	//return vector containing all splits
}

std::string vecToStr(const std::vector<std::string>& vec, const std::string& between)	//compiles vector into single string
{
	std::string toReturn = "";
	for (int i = 0; i < vec.size(); i++)
	{
		toReturn += vec[i] + between;	//concatenate strings
	}
	toReturn.erase(toReturn.end(), toReturn.end() - between.size());	//delete extra "between"
	return toReturn;
}

//mins, maxes, bounds
int imax(int& a, int& b)
{
	return ((a > b) ? a : b);
}

int imin(int& a, int& b)
{
	return ((a < b) ? a : b);
}

void ibound(int& a, const int& b, const int& c)
{
	if (b > c)
	{
		if (a > b){ a = b; }
		else if (a < c){ a = c; }
	}
	else
	{
		if (a > c){ a = c; }
		else if (a < b) { a = b; }
	}
}



double dmax(double& a, double& b)
{
	return ((a > b) ? a : b);
}

double dmin(double& a, double& b)
{
	return ((a < b) ? a : b);
}

void dbound(double& a, const double& b, const double& c)
{
	if (b > c)
	{
		if (a > b){ a = b; }
		else if (a < c){ a = c; }
	}
	else
	{
		if (a > c){ a = c; }
		else if (a < b) { a = b; }
	}
}


unsigned int uimax(unsigned int& a, unsigned int& b)
{
	return ((a > b) ? a : b);
}

unsigned int uimin(unsigned int& a, unsigned int& b)
{
	return ((a < b) ? a : b);
}

void uibound(unsigned int& a, const unsigned int& b, const unsigned int& c)
{
	if (b > c)
	{
		if (a > b){ a = b; }
		else if (a < c){ a = c; }
	}
	else
	{
		if (a > c){ a = c; }
		else if (a < b) { a = b; }
	}
}
*/
