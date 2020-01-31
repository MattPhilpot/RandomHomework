#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *message = "Test Message";

main() {
int inData;
int p[2];
int q[2];
int r[2];
int data;
int maxSize = 256;

pid_t pid;

/* open pipe 1 */
if (pipe(p) == -1) 
{
	perror("pipe call 1");
	exit(1);
}

/* open pipe 3 */
if (pipe(r) == -1) 
{
	perror("pipe call 3");
	exit(1);
}

//p = parent to child
//q = child to grandchild
//r = grandchild to parent



switch(pid = fork()) 
{
	case -1:
   		perror("fork call");
   		exit(2);
	
	case 0:
		
	//	int q[2]; //q to grandchild
		/* open pipe 2 */
		if (pipe(q) == -1) 
		{
			perror("pipe call 2");
			exit(1);
		}
		close(p[1]);
		sleep(5);
		read(p[0],(int*) inData, maxSize);
		printf("test test: %d", inData);
		inData+=inData;
		close(p[0]);
   		write(q[1],(int*) inData, maxSize);

		switch(pid = fork()) 
		{
			case -1:
   				perror("fork call");
   				exit(2);
			case 0:
   				close(q[1]);
   				read(q[0],(int*) inData, maxSize);
				close(q[0]);
				printf("The Data received from B is: %d", inData);
		//		write(r[1], inbuf, MSGSIZE);
   				break;

			default:
				waitpid(-1, (int*) pid, 0);
				wait(NULL);
   		}

		break;
	
	default:
       //	waitpid(-1, (int*) pid, WNOHANG);
		printf("Please enter a number you would like to have operated upon: ");
		scanf(" %d", &data);
		printf("You entered %d. That will now be operated upon...", data);
   		write(p[1],(int*) data, maxSize);
		close(p[1]);
		waitpid(-1, (int*) pid, 0);
   	//	read(r[0], inbuf, MSGSIZE);
   wait(NULL);
   }
exit(0);
}

