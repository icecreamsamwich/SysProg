#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	if (argc != 3)
	{	
		printf("Usage: test rootName #Dirs\n");
	} 
	else
	{
		char dirName[256];
		int dirNumber = atoi(argv[2]);
		int count = 0;
	
		if (mkdir(argv[1], 0777) == -1)
		{
			perror("Making root directory failed");
		}
		else
		{
			if (chdir(argv[1]) == -1)
			{
				perror("Changing directory failed");
			}
			else
			{
			for (count = 1;count <= dirNumber; count ++)	
			{		
				sprintf(dirName, "lab%d", count);
				if (mkdir(dirName, 0777) == -1)
				{
					perror("Making one or more directories failed");
				}
			}
			}
		}
	}
}

