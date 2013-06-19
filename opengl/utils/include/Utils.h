#include <string>
#include <iostream>
#include <vector>

class Utils
{
public:
	static std::vector<std::string> SplitString(const char delimiter, const std::string str);
	static std::vector<float> SplitStringToFloat(const char delimiter, const std::string str);
	template<class T>
	static T StringToNumber(const std::string& numberAsString)
	{
		T valor;
		std::stringstream stream(numberAsString);
		stream >> valor;
		return valor;
	}
	static FILE LoadFile(std::string);
	static std::string LoadFileToString(std::string);
};
