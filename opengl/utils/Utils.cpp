#include <Utils.h>

std::vector<string> Utils::SplitString(char delimiter, std::string str)
{
	std::vector<string> splitedString = str.split(delimiter);
	return splitedString;
}

std::vector<float> Utils::SplitStringToFloat(char delimiter, std::string str)
{
	std::vector<float> floats;
	for(string s : Utils::splitString(delimiter,str)){
		Utils::StringToNumber<float>(s);
	}
	return floats;
}

