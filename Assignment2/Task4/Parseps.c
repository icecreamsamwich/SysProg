/*
 * Parseps.c
 *
 *  Created on: Mar 1, 2013
 *      Author: samoleary
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	char listProcsPath[] = "/home/sam/Desktop/Lab6/Task4/listProcs";
	char listProcsExe[] = "listProcs";

	char listProcsRootPath[] = "/home/sam/Desktop/Lab6/Task4/listProcsRoot";
	char listProcsRootExe[] = "listProcsRoot";

	char listProcsInitdPath[] = "/home/sam/Desktop/Lab6/Task4/listProcsInitd";
	char listProcsInitdExe[] = "listProcsInitd";

	int parentProcID = getpid();
	int status;
	int childProc = fork();

	char *const args[] = {"ps", "-f", "--ppid", "1", NULL}; // Linux
//	char *const args[] = {"ps", "-fp", "1", NULL};			// Mac OSX
	char ps[] = "ps";


	if(childProc == 0)
	{
		int grandChildProc = fork();
		if (grandChildProc == 0)
		{
			execl(listProcsPath, listProcsExe, NULL); // ps aux | wc -l
		}
		else
		{
			waitpid(grandChildProc, &status, 0);
			execvp(ps, args); // ps -f --ppid 1
		}
	}
	else
	{
		waitpid(childProc, &status, 0);
		execl(listProcsRootPath, listProcsRootExe, NULL); // ps -u root | wc -l
	}

	return 0;
}
