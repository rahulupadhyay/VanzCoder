#include <iostream>
#include <fstream>

/**
Classe utilitaria para trabalhar com arquivos Wavefront ( .obj )
Author: José Guilherme Vanz < guilherme.sft@gmail.com >
*/
class WaveFrontUtils
{
public:
	/** Método carrega um arquivo WaveFront ( .obj ) para um objeto em memória ( WaveFrontObj ) */
	static void LoadObj(char * path);
};
