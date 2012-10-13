/*
 * Implementação da questão 1 do trabalho.
 * O prgrama espera um arquivo chamado entrada.txt para ser executado. Esse arquivo deve conter uma matrix como 
 * espeficiado no enunciado do trabalho
 * Aluno: José Guilherme Vanz
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void aplicaDijkstra();

int main()
{
	aplicaDijkstra();
}

/* Le arquivo de entrada e aplica dijkstra no grafo*/
void aplicaDijkstra()
{
	FILE *arquivo = fopen("entrada.txt","r");
	if(arquivo){ /*Verifica se arquivo existe*/
		printf("Arquivo encontrado\n");
		int numVertices = -1;
		char origem,destino,fora;
		if(fscanf(arquivo,"%d", &numVertices)){
			int matrixAdj[numVertices][numVertices];
			memset(matrixAdj,-1,sizeof(matrixAdj));
			printf("Número de vertices %d\n", numVertices);
			fscanf(arquivo,"%c",&origem); /*Pula quebra linha*/
			fscanf(arquivo,"%c",&origem);
			fscanf(arquivo,"%c",&destino); /*Pula espaço em branco*/
			fscanf(arquivo,"%c",&destino);
			fscanf(arquivo,"%c",&fora);
			printf("Caminho entre %c e %c\n",origem,destino);
			int linha = 0,coluna = 0;
			while(!feof(arquivo)){ /* Lê arquivo até o final*/
				char c;
				fscanf(arquivo,"%c",&c);
				if(c == '\n'){ /*Final de linha, muda o vertice*/
					linha++;
					coluna = 0;
				}else if(isdigit(c)){ /*Valor de aresta*/
					matrixAdj[linha][coluna] = atoi(&c);
				}else if(c == ' '){ /*Passo de coluna*/
					coluna++;
				}
			}
		}else{
			printf("Erro na leitura do arquivo. Não foi possível ler o número de vértices na primeira linha.\n");
		}		
	}else{
		printf("Arquivo de entrada.txt não encontrado. Verifique!\n");
	}	
	
	/*------------ Termino da leitura. Aplica dijkstra no grafo --------------*/


}
