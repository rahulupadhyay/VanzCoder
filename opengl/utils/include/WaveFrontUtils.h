#include <WaveFrontObj.h>

/**
Classe utilitaria para trabalhar com arquivos Wavefront ( .obj )
Author: José Guilherme Vanz < guilherme.sft@gmail.com >
*/
class WaveFrontUtils
{
	/** Método carrega um arquivo WaveFront ( .obj ) para um objeto em memória ( WaveFrontObj ) */
	static WaveFrontObj LoadObj(char * path);
};
