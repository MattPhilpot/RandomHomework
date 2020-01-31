#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define strlen 50

main()
{
	char *str[4]; //{"/bin/ls", "ls", "-l", "-s"};
	int i;
	for(i=0; i<strlen; i++)
	{
		str[i] = NULL;
	}

	execl("/bin/ls", "ls", "-l", str[0], (char *) 0 );

}