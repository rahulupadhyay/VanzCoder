#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>


int copiar(DIR*,DIR*, char*,char*);

int main(int argc, char * arg[])
{
	if(argc < 3){
		printf("ERROR - Número de parametros inválido!\n");
		printf("USO:\n");
		printf("vanzcp <dir a ser copiado> <diretorio destino>\n");
	}else{
		printf("Diretório origem: %s\nDiretório destino: %s\n", arg[1],arg[2]);
		DIR * origem = opendir(arg[1]);
		DIR * destino = opendir(arg[2]);
		if(!origem){
			printf("Diretório de origem não existe ou não pode ser aberto!\n");
			return -1;
		}else if(!destino){
			printf("Diretório de destino não existe ou não pode ser aberto!\n");
			return -2;
		}else{
			printf("Copiando...\n");
			if(!copiar(origem, destino, arg[1], arg[2])){
				printf("Copiado com sucesso\n");
				return 0;
			}
				printf("Erro durante a cópia\n");
				return -1;
		}
	}


}


int copiar(DIR * origem, DIR * destinoi, char * pathOrigem, char * pathDestino)
{
	struct dirent * files;
	while((files = readdir(origem)) != NULL){
		if(!strcmp(files->d_name,".") || !strcmp(files->d_name,"..")){
                	continue;		
		}else{
			char novoPathOrigem[255];
			char novoPathDestino[255];
			strcpy(novoPathOrigem,pathOrigem);
		        strcat(novoPathOrigem,files->d_name);

			strcpy(novoPathDestino,pathDestino);

			char argumentos[255];
			strcpy(argumentos,novoPathOrigem);
		        strcat(argumentos," ");
		        strcat(argumentos, novoPathDestino);

			int p = fork();
			if(p == 0){ // processo filho
				if(files->d_type == DT_DIR){
					execl("/bin/cp", "cp", "-r", novoPathOrigem, novoPathDestino, (char*)NULL);
					return -1;
				}
				execl("/bin/cp", "cp", novoPathOrigem, novoPathDestino, (char*)NULL);
				return -1;
			}
		}
	}
	return 0;
}

