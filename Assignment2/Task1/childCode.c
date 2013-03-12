#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#include <stdlib.h>
#include <signal.h>

#include <time.h>

#define MIN 5
#define MAX 15

void handler(int mysig)
{
   int parentID = getppid();
   int childID = getpid();
   printf("Process %d about to die.\n", childID);
   kill(parentID, SIGUSR1);
   exit(1);
}

int main()
{
   signal(SIGINT, SIG_IGN);
   time_t seconds;
   srand((unsigned int) seconds);

   int child_id = getpid();
   int timer = rand() % (MAX - MIN +1) + MIN;
   printf("My PID: %d\nI will live for %d seconds\n", child_id, timer);
   signal(SIGALRM, handler);
   alarm(timer);

   sleep(timer + 1);
   return 0;
}
