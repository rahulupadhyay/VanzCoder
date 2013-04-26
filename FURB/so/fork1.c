#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int p;
	p = fork();
	if(p == 0){
		sleep(10);
		printf("Este eh o filho. p = %d.  PID = %d\n", p, getpid());
	}else{
		sleep(10);
		printf("Este eh o pai. p = %d.  PID = %d\n", p, getpid());
	}

}

