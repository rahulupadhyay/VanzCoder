

#include "ObjParserWavefront.h"

void ObjParserWavefront::parser(const char* fileName, &ObjModel model)
{
	FILE *f = fopen(fileName, "rb");
    	std::string content;
    	if(f){
        	ssize_t readCount;
        	char *line = NULL;
        	size_t len = 0;
        
        	while((readCount = getline(&line, &len, f)) != EOF){
        	    content += line;
        	    if(line[0] == 'v'){ // linha com vertice

        	    }else if(){ // texture-coordinate

        	    }else if(){ //normals

        	    }else if(){ //faces

        	    }else{
        	    	//qualquer outra coisa
        	    }

        	}
        
        	fclose(f);
    	}
    	return content;
}