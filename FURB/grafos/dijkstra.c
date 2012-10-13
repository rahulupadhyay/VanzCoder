/*
 * Implementação da questão 1 do trabalho 
 * Aluno: José Guilherme Vanz
 * */

#include<stdio.h>
#include<stdlib.h>

void leArquivoEntrada();
void aplicaDijkstra();

int main()
{
	leArquivoEntrada();
	aplicaDijkstra();
}

/* Le arquivo de entrada e cria o grafo*/
void leArquivoEntrada()
{
	FILE *arquivo = fopen("entrada.txt","r");
	if(arquivo){ /*Verifica se arquivo existe*/
		printf("Arquivo encontrado\n");
		int numVertices = -1;
		char[][] matrixAdj;
		if(fscanf(arquivo,"%d", &numVertices)){
			printf("Número de vertices %d\n", numVertices);
			while(!feof(arquivo)){ /* Lê arquivo até o final*/
				char c;
				
				}else{
					printf("Erro na leitura do arquivo\n");
				}
			}
		}else{
			printf("Erro na leitura do arquivo. Não foi possível ler o número de vértices na primeira linha.\n");
		}		
	}else{
		printf("Arquivo de entrada.txt não encontrado. Verifique!\n");
	}	
	
}

/* Aplica dijkstra verifica o menor caminho entre os pontos*/
void aplicaDijkstra()
{

}
