#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int p;
	sleep(10);
	p = fork();
	if(p == 0){
		execl("hello", "hello", NULL);
	}else{
		printf("Processo pai executando.\n");
		sleep(10);
	}

}

