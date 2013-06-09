/**
 * Author: José Guilherme Vanz <guilherme.sft@gmai.com>
 */ 

#include <WaveFrontObj.h>

//TODO
void WaveFrontObj::addVertex(std::vector<float> vertex)
{
	if(vertex){
		this->vertexes.push_back(vertex);
	}
}
