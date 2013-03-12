#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include <string.h>

int main(int argc, char *argv[])
{
	if(argc < 2 || argc > 3 || strcmp(argv[1], "ls") != 0)
	{
		printf("Usage: ./redirect ls [-arg..]\n");
		return 1;
	}
	FILE *myFile;
	char *paramList[] = {"/bin/ls", NULL};
	char pathCommand[] = "/bin/ls";
	myFile = fopen("/Users/samoleary/Documents/GitHubProjects/SysProg/Assignment2/Task2/list.txt", "w");
	if(myFile == NULL)
	{
		perror("Failed to open file");
		return 1;
	}
	int myFileDes = fileno(myFile);
	if(dup2(myFileDes, STDOUT_FILENO) <0)
	{
		perror("Failed to redirect standard output");
		return 1;
	}
	if (argc == 2)
	{
		execv(pathCommand, paramList);
	}
	if(argc == 3)
	{
		char *paramList[] = {"/bin/ls", argv[2], NULL};
		execv(pathCommand, paramList);
	}
	fclose(myFile);
	return 0;
}
