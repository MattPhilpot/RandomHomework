#include<stdio.h>
#include<sys/types.h>


int main(int argc, char * argv[])
{
	printf("I am the child process. My pid is %d.\n", getpid());
}

