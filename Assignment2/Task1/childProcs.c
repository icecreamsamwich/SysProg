#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
   int rValue = fork();

   if(rValue == 0)
   {
	printf("Child 1 starting...\n");
	execl("./childCode", "childCode", NULL);
	printf("Passed 'execl'\n");
	return 1;
   }
   else
   {
	int status;
	pid_t childThatExitedID = wait(&status);
	printf("childThatExitedID: %d\n", childThatExitedID);
	if(childThatExitedID != -1)
	{
	   printf("Waited for child %ld\n", childThatExitedID);
	   if(WIFEXITED(status))
	   {
		printf("Child exit code %d\n", WEXITSTATUS(status));
	   }
	   else
	   {
		printf("Child terminated abnormally\n");
	   }
	}
   }
   if(rValue != wait(NULL))
   {
	perror("Parent failed to wait due to signal error");
	return 1;
   }

   return 0;
}
