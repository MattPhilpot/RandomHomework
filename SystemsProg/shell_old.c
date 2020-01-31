#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define strlen 50

int childProcess(char* argv[strlen])
{
	printf("the child: %s \n", argv);
}

main () 
{
	pid_t pid;
   	pid_t x = 0;
   	int status;
	char* arg[strlen];
	char* str1[strlen];
	char* token;
	int i;
	for(i=0; i<strlen; i++)
	{
		arg[i] = NULL;
	}
	while(1)
	{
		printf("PhilpotShell$ ");
		scanf("%s%s%s%s%s%s", arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);

		printf("%s %s \n", arg[0], arg[1]);
		exit(1);
	   	switch (pid = fork()) 
		{
	      		case -1: 
				perror("fork failed");
	               	exit(1);
	      		case 0:
				childProcess(&arg[0]);
	               	exit(1);
	      		default:
				if((pid = wait(&status) == -1))
				{
					perror("wait error\n");
				}
				else
				{
					if (WIFSIGNALED(status) != 0)
						printf("Child process ended because of signal %d\n", WTERMSIG(status));
					else if (WIFEXITED(status) != 0)
						printf("Child process ended normally; status = %d\n",WEXITSTATUS(status));
					else
						printf("Child process did not end normally\n");
				}

				printf("you typed in: %s \n", arg);
	   	}
	}
}
