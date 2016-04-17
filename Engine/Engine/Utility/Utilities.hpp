#pragma once


#include <string>
#include <stack>
#include <vector>


namespace util
{
	/*


	std::string reverseString(const std::string& str);	//stack based string flipper

	std::vector<std::string> splitStrAtSubstr(const std::string& str, const std::string& split);	//splits provided string at specified substring ex. One.Two.Three, "." will return {One, Two, Three}


	std::string vecToStr(const std::vector<std::string>& vec, const std::string& between);	//compiles vector into single string

	inline void swapChars(char& a, char& b);

	int imax(int& a, int& b);								//finds the greater of two ints
	int imin(int& a, int& b);								//finds the lesser of two ints
	void ibound(int& a, const int& b, const int& c);		//bounds an int between two other ints

	double dmax(double& a, double& b);						//finds the greater of two doubles
	double dmin(double& a, double& b);						//finds the lesser of two doubles
	void dbound(double& a, const double& b, const double& c);
	//bounds an double between two other doubles


	unsigned int uimax(unsigned int& a, unsigned int& b);	//finds the greater of two unsigned ints
	unsigned int uimin(unsigned int& a, unsigned int& b);	//finds the greater of two nsigned ints
	void uibound(unsigned int& a, const unsigned int& b, const unsigned int& c);
	//bounds an unsigned int between two other unsigned ints
	*/
	//mins, maxes, bounds

	inline float clamp(const float& in, const float& min, const float& max)
	{
		if (in < min)
		{
			return min;
		}
		else if (in > max)
		{
			return max;
		}
		return in;
	};

	inline void swapChars(char& a, char& b)
	{
		char temp = a;
		a = b;
		b = temp;
	}

	inline int imax(int& a, int& b)
	{
		return ((a > b) ? a : b);
	}

	inline int imin(int& a, int& b)
	{
		return ((a < b) ? a : b);
	}

	inline void ibound(int& a, const int& b, const int& c)
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



	inline double dmax(double& a, double& b)
	{
		return ((a > b) ? a : b);
	}

	inline double dmin(double& a, double& b)
	{
		return ((a < b) ? a : b);
	}

	inline void dbound(double& a, const double& b, const double& c)
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




	inline float fmax(float& a, float& b)
	{
		return ((a > b) ? a : b);
	}

	inline float fmin(float& a, float& b)
	{
		return ((a < b) ? a : b);
	}

	inline void fbound(float& a, const float& b, const float& c)
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





	inline unsigned int uimax(unsigned int& a, unsigned int& b)
	{
		return ((a > b) ? a : b);
	}

	inline unsigned int uimin(unsigned int& a, unsigned int& b)
	{
		return ((a < b) ? a : b);
	}

	inline void uibound(unsigned int& a, const unsigned int& b, const unsigned int& c)
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
		toReturn = toReturn.substr(0, toReturn.size() - between.size());	//delete extra "between"
		return toReturn;
	}

	template<class T>
	inline void nullCopyValue(const T& toCopy, T& value)	//only copies a non-null value
	{
		if (toCopy)
		{
			value = toCopy;
		}
	}

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
	}
}



