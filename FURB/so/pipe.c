
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int dp[2]; // posicao 0 = read ---- posicao 1 = write
	int n;
	char buf[100];

	if(pipe(dp) < 0){
		printf("Erro na criação do PIPE.\n");
		exit(1);
	}else{
		printf("dp1[0] = %d, dp1[1] = %d\n", dp[0], dp[1]);
	 	int p = fork();
		if(p == 0){
			// processo filho
			close(dp[1]);
			n = read(dp[0], buf, sizeof(buf));
			printf("Número de bytes lidos = %d\n", n);
			printf("buf lido = %s\n", buf);
			write(1, buf, 23); // escrevendo diretamente no stdout
			close(buf[0]);
		}else{
			// processo pai
			close(dp[0]); // pai só vai escrever. Então fecha read
			n = write(dp[1], "menssagem para o filho!", 23);
			printf("número de bytes escritos =  %d\n", n);
			close(dp[1]);
		}

	} // else
}
	
