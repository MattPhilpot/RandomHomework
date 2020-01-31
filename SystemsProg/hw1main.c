#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

main () {
   pid_t pid;
   pid_t x = 0;
   int status;

   switch (pid = fork()) {
      case -1: perror("fork failed");
               exit(1);
      case 0: // x = getpid();
	      // printf("test test test: %d.\n", x);
	       execl("prnt", "prnt", (char *) 0 );
               perror("exec failed");
               exit(1);
      default: waitpid(-1, (int*) pid, 0);
               printf("I am the parent process. My child's pid is %d. \n", pid);
               exit(0);
   }
}

