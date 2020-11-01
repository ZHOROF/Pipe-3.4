#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>





int main(void){
	void sigint_handler(int sig);
	int number, pipefds[2], buffer;

	if (signal(SIGINT, sigint_handler) == SIG_ERR){
	  perror("signal");
	  exit(1);
	}

	pipe(pipefds);
	pid_t pid = fork();

	if(pid == 0){
	  close(pipefds[0]);
	  printf("This is a child process\n");
	  printf("Enter a number: \n");
	  scanf("%d", &number);
	  write(pipefds[1], &number, sizeof(number));
	 // printf("This is child process\n");

	  exit(EXIT_SUCCESS);
	}


	else if(pid > 0){
		//printf("This is parent process\n");
		wait(NULL);
		close(pipefds[1]);
		read(pipefds[0], &buffer, sizeof(int));
		close(pipefds[0]);
		printf("This is parent process\n");

		for(int i=2; i<=buffer /2; i++){
		   if(buffer % i == 0){
			printf("%d is not a prime number.\n", buffer);
			exit(EXIT_SUCCESS);
		   }

		   else{
			printf("%d is a prime number.\n", buffer);
			exit(EXIT_SUCCESS);
		   }
		}
	}

	else{
	  perror("INVALID");
	}

	return EXIT_SUCCESS;
}

void sigint_handler(int sig){
	printf("Please do not interrupt!\n");
}


