
#include "WaveFrontUtil.h"
#include "Obj.h"

void WaveFrontUtil::ReadObjFile(const char* path)
{

	std::string line;
	std::ifstream myfile(path);
	if (myfile.is_open()){
		while ( myfile.good() ){
			getline (myfile,line);
			int lineType = -1;
			if(line[0] == 'v' & line[1] == ' '){
				std::cout << "LINHA COM VERTICE" << std::endl;
				lineType = 0;
			}else if(line[0] == 'v' & line[1] == 't'){
				std::cout << "COORDENADA DE TEXTURA" << std::endl;
				lineType = 1;
			}else if(line[0] == 'v' & line[1] == 'n'){
				std::cout << "NORMALS" << std::endl;
				lineType = 2;
			}else if(line[0] == 'f' & line[1] == ' '){
				std::cout << "FACE" << std::endl;
				lineType = 3;
			}
			line.erase(0,2);
			if(line[0] == ' '){
				line.erase(0,1);
			}
			if(line[line.length()-1] == ' '){
				line.erase(line.length() - 1, 1);
			}
			std::cout << line << std::endl;
			if(lineType == 0){ // vertice

			}else if(lineType == 1){ // coordenada texture

			}else if(lineType == 2){ // normals

			}else if(lineType == 3){ // face

			}
			
		}
	}

/*
	FILE *f = fopen(path, "rb");
	std::string content;
    
	if(f){
		ssize_t readCount;
		char *line = NULL;
		size_t len = 0;
        
		while((readCount = getline(&line, &len, f)) != EOF){
			if(line[0] == 'v' & line[1] == ' '){
				printf("LINHA COM VERTICE");
			}else if(line[0] == 'v' & line[1] == 't'){
				printf("COORDENADA DE TEXTURA");
			}else if(line[0] == 'v' & line[1] == 'n'){
				printf("NORMALS");
			}else if(line[0] == 'f' & line[1] == ' '){
				printf("FACE");
			}
		}
		fclose(f);
	}
*/
}
