#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void runProc(char comOne[], char comTwo[], char *args[]);

int main(int argc, char *argv[])
{
	int status;
	int childPid;
	int fileIDs[2];
	
	if(argc < 3 || argc > 5)
	{
		perror("Usage: './TwoProcs <command> [-arg..] <command> [-arg..] <command> [-arg]'");
		return 1;
	}
	
	status = pipe(fileIDs);
	if(status == -1)
	{
		perror("Failed to create the pipe");
		return 1;
	}
	
	childPid = fork();
	if (childPid == -1)
	{
		perror("Creating child process failed");
		return 1;
	}

	if (childPid == 0)
	{
		if(dup2(fileIDs[0], STDIN_FILENO) < 0)
		{	
			perror("Failed to redirect standard input");
			return 1;
		}
		close(fileIDs[1]);
		
		if(argc = 3)
		{
			runProc(argv[2], argv[2]);
		}
	}
	else
	{
		if(dup2(fileIDs[1], STDOUT_FILENO) < 0)
		{
			perror("Failed to redirect standard output");
			return 1;
		}
		if(argc = 3)
		{
			runProc(argv[1], argv[1]);
		}
	}
	return 0;
}

void runProc(char comOne[], char comTwo[], char *args[])
{
	if(strcmp(argOne, argTwo) == 0)
	{
		if(execlp(argOne, argOne, NULL))
		{
			perror("runProc: First process not found");
			printf("Check '%s': Command not recognized\n", argOne);
		}
	}
}

		
		
		
		
	

