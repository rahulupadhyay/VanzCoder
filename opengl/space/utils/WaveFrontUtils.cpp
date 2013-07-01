/**
 * Author: José Guilherme Vanz <guilherme.sft@gmai.com>
 */

#include <WaveFrontUtils.h>
#include <iostream>

using namespace std;

void WaveFrontUtils::LoadObj(const char * path)
{
	ifstream arquivo(path);
	string linha;

	if(arquivo.is_open()){
		while(arquivo.good()){
			getline(arquivo, linha);
			if(linha[0] == "v"){
				cout << "Vertice" << endl;
			}else if(linha[0] == "vt"){
				cout << "Coordenada textura" << endl;
			}else if(linha[0] == "vn"){
				cout << "Normals" << endl;
			}else if(linha[0] == "vp"){
				cout << "Parameter space" << endl;
			}else if(linha[0] == "f"){
				cout << "face" << endl;
			}
			
		}
		arquivo.close();
	
	}
}

int main(void)
{
	WaveFrontUtils::LoadObj("/home/vanz/gitroot/VanzCoder/opengl/space/data/asteroid.obj");
}

