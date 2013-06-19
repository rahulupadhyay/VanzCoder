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

FILE LoadFile(std::string path)
{
	// TODO - validação
	FILE * file = fopen(path);
	return file;
}
	
std::string LoadFileToString(std::string path)
{
	string file;
	ifstream myfile (path);
	if(myfile.is_open()){
		while(myfile.good()){
			getline (myfile,file);
    		}
		myfile.close();
	}else{
		 cout << "Unable to open file"; 
	}
  return 0;
}
