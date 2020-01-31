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

extern int errno;

typedef void (*sighandler_t)(int);
static char *my_argv[100], *my_envp[100];
static char *arg1[100], *arg2[100];
static char *search_path[10];
static char *dir[100];
static int dir_len = 0;
const int arg_MAX = 10;
const int argLeng = 100;
int numpipes = 0;
char **memptr;
char quit[] = "q";
char chgdir[] = "cd";
int *pipepos = NULL;
char **frontcmd = NULL;
char **backcmd = NULL;
int argnum=0;
int spot=0;
int pos=0;
int lastpos=0;
int nextpos=0;
int i, j, xy;

//PIPE VARS
/************/
FILE *read_fp;
char buffer[BUFSIZ + 1];
int chars_read;
/***********/



/*SYSTEM CALLS WERE NOT PERMITED, DANG!
 void system_call(char *tmp){
 printf("%s\n",tmp);
 system(tmp);
 }
 */

void pipe_execvp(char *cmd, char *arg[])
{
	int i;
	i = fork();
	switch (i)
	{
			
		case -1:
			printf("Problem forking a child\n");
			
		case 0:
			if ( execvp(cmd, arg) == -1)
				exit(EXIT_FAILURE);
			else
				printf("HenPotShell$ ");
		case 1:
			wait(NULL);
			
			
	}
}

void pipe_command(/*int argc, char *argv[]*/   char com[])
{
	
/////////////////// START OF CUSTOM PARSER /////////////////// 
	
	char *com1 = (char *)malloc(sizeof(char) * 16);
	char *com2 = (char *)malloc(sizeof(char) * 16);
	char *cmd1 = (char *)malloc(sizeof(char) * 8);
	char *cmd2 = (char *)malloc(sizeof(char) * 8);

	char spacer[] = " ";
	int counter = 0;
	int breaker = 0;
	int cmdcount = 0;
	int x;
	int y;
//	printf("This is the starting argument: %s\n\n", com);
//	printf("Parsing first argument...\n");
	for(x = 0; x < (int)strlen(com); x++)
	{
		if(com[x] == ' ' && com[x+1] == '|')
			break;
		else
			counter++;
	}
	strncpy(com1, com, counter);
	for(x = 0; x<(int)strlen(com1); x++)
	{
		if(com1[x] == ' ')
			break;
		else
			cmdcount++;
	}
	strncpy(cmd1, com1, cmdcount);
//	printf("Printing cmd1: %s \n", cmd1);
//	printf("Printing arg1: %s \n\n",com1);
//	printf("Parsing next argument...\n");
	for(x = counter; x<(int)strlen(com); x++)
	{
		if(com[x-1] == ' ' && com[x-2] == '|')
			break;
		else
			counter++;
	}
	breaker = counter;
	y = 0;
	for(x = counter; x<(int)strlen(com); x++)
	{
		com2[x-breaker] = com[x];
	}
	cmdcount = 0;
	for(x = 0; x<(int)strlen(com2); x++)
	{
		if(com2[x] == ' ')
			break;
		else
			cmdcount++;
	}
	strncpy(cmd2, com2, cmdcount);
//	printf("Printing cmd2: %s \n", cmd2);
//	printf("Printing arg2: %s \n\n", com2);	
	
	//Parsing *com1 into *arg1[]
	x = 0;
	arg1[x] = strtok(com1, spacer);
	while( arg1[x] != NULL ) 
	{
		x++;
		arg1[x] = strtok(NULL, spacer);
	}

	//Parsing *com2 into *arg2[]
	x = 0;
	arg2[x] = strtok(com2, spacer);
	while( arg2[x] != NULL ) 
	{
		x++;
		arg2[x] = strtok(NULL, spacer);
	}


////////////// END OF PARSER ///// BEGINNING OF FORKING ////////////// 

	int fd[2], fd1[2], fd2[2];
	
	if (pipe(fd) == -1) /* create first pipe */ 
	{ 			
		perror("Pipe");   /* pipe fails */ 
		exit(1); 
	} 
	if (pipe(fd1) == -1) /* create first pipe */ 
	{ 			
		perror("Pipe");   /* pipe fails */ 
		exit(1); 
	} 
	if (pipe(fd2) == -1) /* create first pipe */ 
	{ 			
		perror("Pipe");   /* pipe fails */ 
		exit(1); 
	} 
    	pid_t pid,pid1,pid2; 
	int status,status1,status2; 
    	pid = fork(); 
	if (pid == -1) 
	{ 
		/* fork error - cannot create child */ 
		perror("Demo program"); 
		exit(1); 
	} 
    	else if (pid == 0) 
	{ 
		/* code for child */ 
		
		pid1=fork(); 
		
		if (pid1 == -1) 
		{ 
			/* fork error - cannot create child */ 
			perror("Fork Error"); 
			exit(1); 
		} 
		else if (pid1 == 0) 
		{ 
			/* code for grandchild */ 
			close (fd1[0]); 
		//	close(0);
			dup2(fd1[1], STDOUT_FILENO);
		//	close(fd1[0]);
		//	close(fd1[1]);
			pipe_execvp(cmd1, arg1);
			exit(1); 
		} 
		else 
		{ /* code for parent */ 
			
            		if ((pid1 = wait(&status)) == -1) //* Wait for child process.      */          
				perror("wait error\n"); 
            		else 
			{                       /* Check status.                */ 
				if (WIFSIGNALED(status) != 0) 
					printf(""); 
				else if (WIFEXITED(status) != 0) 
					printf(""); 
				else 
					printf(""); 
            		} 
			close (fd1[1]);			
		//	close(1);
			dup2(fd1[0], STDIN_FILENO);

			pipe_execvp(cmd2, arg2);
		//	close(fd1[1]);
		//	close(fd1[0]);			
			exit(EXIT_SUCCESS); 
			////////////////////////////next is child 1 ////////////// 
			exit(1); 
		}
	} 
    	else 
	{ /* code for grandparent */ 
		 
		close(fd[0]); 
		
		///////////////////////////////////////// 
		close (fd2[1]); 
		
		///////////////////////////////////////////////// 
		
		
		                       /* Check status.                */ 
			if (WIFSIGNALED(status) != 0) 
				printf(""); 
			else if (WIFEXITED(status) != 0) 
				printf(""); 
			else 
				printf(""); 
		
        exit(0); 

	} 
}


void handle_signal(int signo)
{
//	printf("\n [HenPotShell] ");
	fflush(stdout);
}


void fill_argv(char *tmp_argv)
{
	char *foo = tmp_argv;
	int index = 0;
	char ret[100];
	bzero(ret, 100);
	while(*foo != '\0') {
		if(index == 10)
			break;
		
		if(*foo == ' ') {
			if(my_argv[index] == NULL)
				my_argv[index] = (char *)malloc(sizeof(char) * strlen(ret) + 1);
			else {
				bzero(my_argv[index], strlen(my_argv[index]));
			}
			strncpy(my_argv[index], ret, strlen(ret));
			strncat(my_argv[index], "\0", 1);
			bzero(ret, 100);
			index++;
		} else {
			strncat(ret, foo, 1);
		}
		foo++;
	}
	my_argv[index] = (char *)malloc(sizeof(char) * strlen(ret) + 1);
	strncpy(my_argv[index], ret, strlen(ret));
	strncat(my_argv[index], "\0", 1);
}

void copy_envp(char **envp)
{
	int index = 0;
	for(;envp[index] != NULL; index++) {
		my_envp[index] = (char *)malloc(sizeof(char) * (strlen(envp[index]) + 1));
		memcpy(my_envp[index], envp[index], strlen(envp[index]));
	}
}

void get_path_string(char **tmp_envp, char *bin_path)
{
	int count = 0;
	char *tmp;
	while(1) {
		tmp = strstr(tmp_envp[count], "PATH");
		if(tmp == NULL) { 
			count++;
		} else {
			break;
		}
	}
	strncpy(bin_path, tmp, strlen(tmp));
}

void insert_path_str_to_search(char *path_str)
{
	int index=0;
	char *tmp = path_str;
	char ret[100];
	
	while(*tmp != '=')
		tmp++;
	tmp++;
	
	while(*tmp != '\0') {
		if(*tmp == ':') {
			strncat(ret, "/", 1);
			search_path[index] = (char *) malloc(sizeof(char) * (strlen(ret) + 1));
			strncat(search_path[index], ret, strlen(ret));
			strncat(search_path[index], "\0", 1);
			index++;
			bzero(ret, 100);
		} else {
			strncat(ret, tmp, 1);
		}
		tmp++;
	}
} 

int attach_path(char *cmd)
{
	char ret[100];
	int index;
	int fd;
	bzero(ret, 100);
	for(index=0;search_path[index]!=NULL;index++) {
		strcpy(ret, search_path[index]);
		strncat(ret, cmd, strlen(cmd));
		if((fd = open(ret, O_RDONLY)) > 0) {
			strncpy(cmd, ret, strlen(ret));
			close(fd);
			return 0;
		}
	}
	return 0;
}


/*THIS SECTION OF THE CODE IS THE ORIGINAL FROM THE AUTHOR 
 OF THE SKELETON OF THE "myshell" PROGRAM EXCEPT THAT execve IS NOT
 USED ANYMORE, INSTEAD I USE execvp TO OVERCOME THE NECESSITY OF A PATH.*/



void call_execvp(char *cmd)
{
	int i;
	i = fork();
	switch (i)
	{
			
		case -1:
			printf("Problem forking a child\n");
			
		case 0:
			if ( execvp(cmd, my_argv) == -1)
				exit(EXIT_FAILURE);
			else
				printf("HenPotShell$ ");
		case 1:
			wait(NULL);
			
			
	}
	
	/*
	 if(fork() == 0)	{
	 
	 }
	 if(fork() == -){}
	 else
	 {
	 wait(NULL);
	 }
	 */
	
}

void free_argv()
{
	int index;
	for(index=0;my_argv[index]!=NULL;index++) {
		bzero(my_argv[index], strlen(my_argv[index])+1);
		my_argv[index] = NULL;
		free(my_argv[index]);
	}
}

void free_dir()
{
	int index;
        for(index=0;dir[index]!=NULL;index++) 
	{
		dir[index] = NULL;
        }
}

int main(int argc, char *argv[], char *envp[])
{
	char c; 
	int i, fd;
	char *tmp = (char *)malloc(sizeof(char) * 100);
	char *path_str = (char *)malloc(sizeof(char) * 256);
	char *cmd = (char *)malloc(sizeof(char) * 100);

	int counter = 0;
	
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_signal);
	
	copy_envp(envp);
	get_path_string(my_envp, path_str);
	insert_path_str_to_search(path_str);
	
	if(fork() == 0)
	{
		execvp("/usr/bin/clear", argv);
		exit(1);
	} 
	else 
	{
		wait(NULL);
	}
	printf("HenPotShell$ ");
	fflush(stdout);
	while(c != EOF)
	{
		c = getchar();
		switch(c) 
		{
			case '|':
				numpipes++;
				strncat(tmp, &c, 1);
				break;
			case '\n': 
				if(tmp[0] == '\0') 
				{
					printf("HenPotShell$ ");
				}
				else 			
				{
					fill_argv(tmp);
					if( numpipes>0)
					{
						pipe_command(tmp);
					}
					else if(tmp[0]=='c' && tmp[1]=='d' && tmp[2]==' ')
					{
						if(chdir((char *)dir)==0)
							printf("chdir() successful\n", &dir);
						else
							printf("chdir() failed\n", &dir);
					}
					else if(tmp[0]=='c' && tmp[1]=='d')
					{
						if(chdir("..")==0)
							printf("chdir() successful\n", &dir);
						else
							printf("chdir() failed\n", &dir);
					}
					{
						strncpy(cmd, my_argv[0], strlen(my_argv[0]));
						strncat(cmd, "\0", 1);
						if(index(cmd, '/') == NULL)
						{
							if(strcmp(cmd, "ps") == 0)
								sscanf("ps","%s",cmd);
							if(strcmp(cmd, "top") == 0)
								sscanf("top","%s",cmd);		
							if(strcmp(cmd, "source") == 0)
								sscanf("source","%s",cmd);
							printf("\n");
							call_execvp(cmd);	
						}
						else
						{
							printf("%s: command not found\n", cmd);
						}
						
						if((fd = open(cmd, O_RDONLY)) > 0) {
							close(fd);
							call_execvp(cmd); (char *)malloc(sizeof(char) * 100);
						} 
						else 
						{
							//printf("%s: command not found\n", cmd);
							
						}
						
					}
					// printf(my_argv[]);
					free_argv();
				//	printf("[HenPotShell] ");
					bzero(cmd, 100);
				}
				bzero(tmp, 100);
				counter = 0;
				numpipes = 0;
				break;
			default: 
				{
				if(c == ' ')
					argnum++;
				strncat(tmp, &c, 1);
				if(counter==3 && tmp[0]=='c' && tmp[1]=='d' && tmp[2]==' ')
					free_dir();
					if(counter >=0)
				{
					strncat((char *)dir, &c, 1);
					dir_len++;
				}
				counter++;
				}//printf("\n%s\n",tmp);}
				break;
		}
	}
	printf("%s",cmd);
	free(cmd);
	printf("%s",cmd);
	
	free(tmp);
	free(path_str);
	for(i=0;my_envp[i]!=NULL;i++)
		free(my_envp[i]);
	for(i=0;i<10;i++)
		free(search_path[i]);
	printf("\n");
	return 0;
} 
