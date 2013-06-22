#include <vector>

class WaveFrontObj
{
	//TODO - Adicionar atributos e prototipos dos métodos
	private:
		std::vector< std::vector<float> > vertexes;
	public:
		void addVertex(std::vector<float> vertex);
};
