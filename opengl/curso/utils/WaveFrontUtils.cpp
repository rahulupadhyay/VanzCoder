/**
 * Author: José Guilherme Vanz <guilherme.sft@gmai.com>
 */

#include <WaveFrontUtils.h>

WaveFrontObj WaveFrontUtils::LoadObj(const char * path)
{
	WaveFrontObj obj;
	ifstream objFile(path,std::ifstream::in);
	if(objFile.is_open()){ // Verifica se arquivo esta aberto
		while(objFile.good() && !objFile.eof()){
			string linha;
			getline(objFile, line);
			if(linha.front() == 'v'){ // linha de vertex
				vector<float> vertex = Utils::SplitStringToFloat(' ', linha);
				obj.addVertex(vertex);
			}
		}
		objFile.close();
	}
	return obj;
}

