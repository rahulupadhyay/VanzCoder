
#include "WaveFrontUtil.h"

void WaveFrontUtil::ReadObjFile(const char* path)
{
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
}
