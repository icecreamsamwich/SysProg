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
	int parentChildPipe[2];
	int childGrandChildPipe[2];

	if(argc < 3 || argc > 7)
	{
		perror("Usage: './TwoProcs <command> [-arg..] <command> [-arg..] <command> [-arg]'");
		return 1;
	}

	status = pipe(parentChildPipe);
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
		int grandChildPid = fork();
		if(grandChildPid == 0)
		{
			if(argc == 7)
			{
				close(parentChildPipe[0]);
				close(parentChildPipe[1]);
				dup2(childGrandChildPipe[0], STDIN_FILENO);
				close(childGrandChildPipe[1]);
				printf("argv[5]: %s\nargv[6]: %s\n", argv[5], argv[6]);
				runProc(argv[5], argv[6]);
			}
		}
		else
		{
			if(dup2(parentChildPipe[0], STDIN_FILENO) < 0)
			{
				perror("Failed to redirect standard input");
				return 1;
			}
			close(parentChildPipe[1]);
/*			if (argc == 7)
			{
				dup2(childGrandChildPipe[1], STDOUT_FILENO);
			}
*/			if(argc == 3)
			{
				runProc(argv[2], argv[2]);
			}
else if(argc == 5)
			{
				runProc(argv[3], argv[4]);
			}
			else if(argc == 7)
			{
				dup2(childGrandChildPipe[1], STDOUT_FILENO);
				runProc(argv[3], argv[4]);
			}
		}
	}
	else
	{
		if(dup2(parentChildPipe[1], STDOUT_FILENO) < 0)
		{
			perror("Failed to redirect standard output");
			return 1;
		}

		if(argc == 3)
		{
			runProc(argv[1], argv[1]);
		}
		if(argc == 5 || argc == 7)
		{
			runProc(argv[1], argv[2]);
		}
	}
	return 0;
}

void runProc(char comOne[], char comTwo[])
{
	int const count = 0;
	if(strcmp(comOne, comTwo) == 0)
	{ count++;
		if(execlp(comOne, comOne, NULL))
		{
			perror("runProc: first 'if': First process not found");
			printf("Check '%s': Command not recognized\n", comOne);
		}
	}
	else
	{ count++;
		if(execlp(comOne, comOne, comTwo, NULL))
		{
			perror("runProc: second 'if': First process not found");
			printf("Check '%s': Command not recognized\n", comOne);
		}
	}
}







