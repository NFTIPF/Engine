#pragma once


#include <string>
#include <stack>
#include <vector>


namespace util
{
	/*
	void swapChars(char& a, char& b);

	std::string reverseString(const std::string& str);	//stack based string flipper

	std::vector<std::string> splitStrAtSubstr(const std::string& str, const std::string& split);	//splits provided string at specified substring ex. One.Two.Three, "." will return {One, Two, Three}

	std::string vecToStr(const std::vector<std::string>& vec, const std::string& between);	//compiles vector into single string
	*/
	inline void swapChars(char& a, char& b)
	{
		char tmp = a;
		a = b;
		b = tmp;
	}

	inline std::string reverseString(const std::string& str)
	{
		std::stack<char> string;

		for (unsigned int i = 0; i < str.size(); i++)	//push all chars into stack
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


	inline std::vector<std::string> splitStrAtSubstr(const std::string& str, const std::string& split)
	{
		int lastHit = 0; //stores location of last split
		std::vector<std::string> splits;
		const int size = splits.size();
		for (unsigned int i = 0; i < str.size(); i++)	//iterate through string
		{
			std::string debug = str.substr(i, split.size());
			if (str.substr(i, split.size()) == split)	//once the split is found
			{
				splits.push_back(str.substr(lastHit, i - lastHit));	//add the section before the split
				i += split.size();							//move i to the end of the split
				lastHit = i;								//the current i is the character after the split
			}
		}
		splits.push_back(str.substr(lastHit, str.size()));	//push back any characters after the final split

		return splits;	//return vector containing all splits
	}

	inline std::string vecToStr(const std::vector<std::string>& vec, const std::string& between)	//compiles vector into single string
	{
		std::string toReturn = "";
		for (unsigned int i = 0; i < vec.size(); i++)
		{
			toReturn += vec[i] + between;	//concatenate strings
		}
		toReturn = toReturn.substr(0, toReturn.size()-between.size());	//delete extra "between"
		return toReturn;
	}

	template<class T>
	inline void nullCopyValue(const T& toCopy, T& value)	//only copies a non-null value
	{
		if (toCopy)
		{
			value = toCopy;
		}
	};

	template<class T>
	inline void nullCopyVector(const std::vector<T>& toCopy, std::vector<T>& vec)	//only copies non-null values from vector
	{
		for (int i = 0; i < vec.size(); i++)
		{
			if (toCopy[i])
			{
				vec[i] = toCopy[i];
			};
		}
	};
	
}




