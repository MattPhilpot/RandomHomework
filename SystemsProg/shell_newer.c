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

void childProcess(int counter, char *arg8[strlen], char *arg[strlen], char *arg1[strlen], char *arg2[strlen], char *arg3[strlen], char *arg4[strlen], char *arg5[strlen], char *arg6[strlen], char *arg7[strlen])
{
	char temp[] = {"/bin/"};
	strcat(temp, arg8);
	printf("TEST TEST TEST %s %s", temp, arg8);
	switch(counter)
	{
		case 1:
			execl(temp, arg8, (char *) 0);
			break;
		case 2:
			execl(temp, arg8, arg, (char *) 0);
			break;
		case 3:
			execl(temp, arg8, arg, arg1, (char *) 0);
			break;
		case 4:
			execl(temp, arg8, arg, arg1, arg2 (char *) 0);
			break;
		case 5:
			execl(temp, arg8, arg, arg1, arg2, arg3, (char *) 0);
			break;
		case 6:
			execl(temp, arg8, arg, arg1, arg2, arg3, arg4 (char *) 0);
			break;
		case 7:
			execl(temp, arg8, arg, arg1, arg2, arg3, arg4, arg5 (char *) 0);
			break;
		case 8:
			execl(temp, arg8, arg, arg1, arg2 ,arg3, arg4, arg5, arg6 (char *) 0);
			break;
		default:
			break;
				
	}

	char temp2[] = {"/usr"};
	strcat(temp2, temp);
	switch(counter)
	{
		case 1:
			execl(temp, arg8, (char *) 0);
			break;
		case 2:
			execl(temp, arg8, arg, (char *) 0);
			break;
		case 3:
			execl(temp, arg8, arg, arg1, (char *) 0);
			break;
		case 4:
			execl(temp, arg8, arg, arg1, arg2 (char *) 0);
			break;
		case 5:
			execl(temp, arg8, arg, arg1, arg2, arg3, (char *) 0);
			break;
		case 6:
			execl(temp, arg8, arg, arg1, arg2, arg3, arg4 (char *) 0);
			break;
		case 7:
			execl(temp, arg8, arg, arg1, arg2, arg3, arg4, arg5 (char *) 0);
			break;
		case 8:
			execl(temp, arg8, arg, arg1, arg2 ,arg3, arg4, arg5, arg6 (char *) 0);
			break;
		default:
			break;
				
	}
}

main (void) 
{
	pid_t pid;
   	pid_t x = 0;
   	int status;
	char *arg = malloc(strlen);
	char *arg1 = malloc(strlen);
	char *arg2 = malloc(strlen);
	char *arg3 = malloc(strlen);
	char *arg4 = malloc(strlen);
	char *arg5 = malloc(strlen);
	char *arg6 = malloc(strlen);
	char *arg7 = malloc(strlen);
	char *arg8 = malloc(strlen);
	char *str1 = malloc(strlen);
	const char spc[] = " ";
	str = malloc(sizeof(strlen));	
	int y = 1;
	int i;
	int counter;

	while(1)
	{
		counter = 0;
		for(i=0; i<strlen; i++)
		{
			arg[i] = NULL;
			arg1[i] = NULL;
			arg2[i] = NULL;
			arg3[i] = NULL;
			arg4[i] = NULL;
			arg5[i] = NULL;
			arg6[i] = NULL;
			arg7[i] = NULL;
		}
		printf("HenPotShell$ ");

		fgets(arg8, strlen-1, stdin);
		str1 = strtok(arg8,spc);
		while(str1 !=NULL)
		{
			printf("%s\n",str1);
			str1 = strtok(NULL," ");
			counter++;
			switch(counter)
			{
				case 1:
					//arg=str1;
					arg = str1;
					break;
				case 2:
					//arg=str1;
					arg1 = str1;
					break;
				case 3:
					arg2=str1;
					//strcpy(arg2, str1);
					break;
				case 4:
					arg3=str1;
					//strcpy(arg3, str1);
					break;
				case 5:
					arg4=str1;
					//strcpy(arg4, str1);
					break;
				case 6:
					arg5=str1;
					//strcpy(arg5, str1);
					break;
				case 7:
					arg6=str1;
					//strcpy(arg6, str1);
					break;
				case 8:
					//arg=str1;
					arg7 = str1;
					break;
				default:
					break;
				
			}
		}

		printf("arg1:%s\narg2:%s\narg3:%s\narg4:%s\narg5:%s\narg6:%s\narg7:%s\narg8:%s\narg9:%s\n",arg8,arg,arg1,arg2,arg3,arg4,arg5,arg6,arg7);
		printf("counter:%d\n",counter);

		exit(0);

	/*	char temp[] = {"/bin/"};
		strcat(temp, arg8);
		execl(temp, arg8, arg, (char *) 0);

		char temp2[] = {"/usr"};
		strcat(temp2, temp);
		execl(temp2, arg8, arg, (char *) 0);	*/	



//		scanf("%s%s", arg, arg2);
//		scanf("%s%s%s%s%s", arg, arg2, arg3, arg4, arg5);
//		printf("TEST TEST: %s : %s : %s : %s : %s", arg, arg2, arg3, arg4, arg5);
//--		char temp[] = {"/bin/"};
//--		strcat(temp, arg);
//		execl(temp, arg8, arg1, (char *) 0);
//		execl(temp, arg, arg2, arg3[0], arg4[0], arg5[0], (char *) 0 );
//		char temp2[] = {"/usr"};
//		strcat(temp2, temp);
//		execl(temp2, arg, arg2, (char *) 0);
//		execl(temp2, arg, arg2, arg3, arg4, arg5, (char *) 0 );  
		exit(0); 
	   	switch (pid = fork()) 
		{
	      		case -1: 
				perror("fork failed");
	               	exit(1);
	      		case 0:
				childProcess(counter, arg8, arg, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
//	               	exit(1);
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

				//printf("you typed in: %s \n", arg);
	   	}
	}
}
