#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int pidArray[4];

void ctrlCHandler(int mysig)
{
   int count;
   for(count=0;count<5;count++)
   {
	printf("Parent killing PID: %d\n", pidArray[count]);
	kill(pidArray[count], SIGKILL);
   }
}

void handler(int mysig)
{
   printf("A child has died\n");
}

int main()
{
   signal(SIGINT, ctrlCHandler);
   int status;
   int forkCount;
   for(forkCount=0;forkCount<5;forkCount++)
   {
	int child = fork();
	pidArray[forkCount] = child;
	if(child == 0)
	{
	   int myID = getpid();
	   printf("Child %d starting: PID: %d...\n", (forkCount + 1), myID);
	   execl("/home/samwich/SysProg/Assignment2/Task1/childCode", "childCode", NULL);
	   printf("Passed 'execl'\n");
	   return 1;
	}
   }

   signal(SIGUSR1, handler);

   int count;
   for(count = 0; count <= 4; count++)
   {
	waitpid(pidArray[count], &status, 0);
   }

   return 0;
}
