
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
			if(line[0] == 'v'){
				printf("LINHA COM VERTICE");
			}
		}
		fclose(f);
	}
}
