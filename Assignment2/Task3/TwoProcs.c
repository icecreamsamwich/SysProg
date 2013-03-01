#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void runProc(char comOne[], char comTwo[]);

int main(int argc, char *argv[])
{
	int status;
	int childPid;
	int grandChildPid;
	int fileIDs[2];
	int newFIDS[2];
	
	if(argc < 3 || argc > 7)
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
		
		if(argc == 3)
		{
			runProc(argv[2], argv[2]);
		}
		if(argc == 5)
		{
			runProc(argv[3], argv[4]);
		}
	}
	else
	{
		if(argc != 7)
		{
			if(dup2(fileIDs[1], STDOUT_FILENO) < 0)
			{
				perror("Failed to redirect standard output");
				return 1;
			}
		
			if(argc == 3)
			{
				runProc(argv[1], argv[1]);
			}
			if(argc == 5)
			{
				runProc(argv[1], argv[2]);
			}
		}
		else if (argc == 7)
		{
			grandChildPid = fork();
			if (grandChildPid == -1)
			{
				perror("Creating grandChild process failed");
				return 1;
			}
			
		}
	}
	return 0;
}

void runProc(char comOne[], char comTwo[])
{
	if(strcmp(comOne, comTwo) == 0)
	{
		if(execlp(comOne, comOne, NULL))
		{
			perror("runProc: first 'if': First process not found");
			printf("Check '%s': Command not recognized\n", comOne);
		}
	}
	else
	{
		if(execlp(comOne, comOne, comTwo, NULL))
		{
			perror("runProc: second 'if': First process not found");
			printf("Check '%s': Command not recognized\n", comOne);
		}
	}
}

		
		
		
		
	

