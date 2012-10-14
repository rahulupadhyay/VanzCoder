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
		int numVertices = -1;
		char origem,destino,fora;
		printf("Arquivo encontrado\n");
		if(fscanf(arquivo,"%d", &numVertices)){
			int matrixAdj[numVertices][numVertices];
			memset(matrixAdj,-1,sizeof(matrixAdj));
			printf("Número de vertices %d\n", numVertices);
			fscanf(arquivo,"%c",&origem); /*Pula quebra linha*/
			fscanf(arquivo,"%c",&origem);
			fscanf(arquivo,"%c",&destino); /*Pula espaço em branco*/
			fscanf(arquivo,"%c",&destino);
			fscanf(arquivo,"%c",&fora);  /*Desconsidera quebra de linha*/
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
			/*------------ Termino da leitura. Aplica dijkstra no grafo --------------*/

			int matrixDijkstra[numVertices][4];
			int pivo,i;
			memset(matrixDijkstra,-1,sizeof(matrixAdj)); /*Limpa tabela*/
			for(i = 0; i < numVertices;i++){ /*Inicializa*/
				matrixDijkstra[i][2] = 1;
				matrixDijkstra[i][3] = 0;
			}
			matrixDijkstra[origem-65][0] = 0;
			
			int x,y = 0;
			for(x = 0; x < numVertices; x++){
				for(y = 0; y < 4; y++){	
					printf("%3d ", matrixDijkstra[x][y]);
				}
				printf("\n");
			}
	
			while(1){
				int index,processar = 0;
				for(index = 0; index < numVertices; index++){
					if(matrixDijkstra[index][2])
					processar = 1;
				}
				if(!processar)
					break;
				/*----------------Pega minimo-------------------------*/
				int min = -1;
				for(index = 0; index < numVertices; index++){
					if(matrixDijkstra[index][2]){
						if((min == -1) | (matrixDijkstra[index][0] < min)){
							pivo = index;
							min = matrixDijkstra[index][0];
						}
					}
				}
				/*-------------------------------------------------------*/
				matrixDijkstra[pivo][3] = 1; /*Processado*/
				matrixDijkstra[pivo][2] = 0;
				/*----- Percorre adjacentes -----*/
				printf("PIVO = %c\n",(pivo + 65));
				int adj;
				for(adj = 0; adj < numVertices; adj++ ){
					if(matrixAdj[pivo][adj] >= 0 && pivo != adj ){
						//printf("Custo atual = %d ----- Custo calculado = %d\n", matrixDijkstra[adj][0], (matrixDijkstra[pivo][0] + matrixAdj[pivo][adj]));
						if((matrixDijkstra[adj][0] == -1) || ( matrixDijkstra[adj][0] > (matrixDijkstra[pivo][0] + matrixAdj[pivo][adj]))){
							matrixDijkstra[adj][0] = matrixDijkstra[pivo][0] + matrixAdj[pivo][adj];
							matrixDijkstra[adj][1] = pivo;
							printf("Novo custo p/ %d = %d\n", adj,(matrixDijkstra[pivo][0] + matrixAdj[pivo][adj]));
							printf("Novo pai p/ %d = %d\n",adj, pivo);
						}
					}
				}
			}
			printf("\n");
			for(x = 0; x < numVertices; x++){
				printf("%c -> ", (65 + x));
				for(y = 0; y < 4; y++){	
					if(y == 1){
						printf("%c", (matrixDijkstra[x][y]+65));
					}else{
						printf("%3d ", matrixDijkstra[x][y]);
					}
				}
				printf("\n");
			}
	

		}else{
			printf("Erro na leitura do arquivo. Não foi possível ler o número de vértices na primeira linha.\n");
		}		
	}else{
		printf("Arquivo de entrada.txt não encontrado. Verifique!\n");
	}	
	
}	
