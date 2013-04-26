#include<unistd.h>


main()
{
	char buff[100];
	int dp[2], n, p;
	if(pipe(dp) < 0){
		printf("ERRO");
		exit(1);
	}else{
		p = fork();
		if(p != 0){ // pai
			close(dp[0]);
			close[1];
			dup(dp[1]);
			close(dp[1]);
			execl("/bin/ls", "ls", NULL);
		}else{ // filho
			close(dp[1]);
			close(0);
			dup(dp[0]);
			close(dp[0]);
			execl("/bin/more", "more", NULL);
		}
	}


}
