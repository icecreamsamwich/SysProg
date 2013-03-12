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
	// ps aux | wc -l
	char ps[] = "ps";
	char wc[] = "wc";
	char minusl[] = "-l";
	char minusu[] = "-u";
	char root[] = "root";

	char *const args[] = {ps, minusu, root, NULL};
	char *const args2[] = {wc, minusl, NULL};

	int brotherBrochildPipe[2]; //write[1] read[0]
	int brotherProc;

	pipe(brotherBrochildPipe);
	int broChildProc = fork();
	if(broChildProc == 0)
	{
		dup2(brotherBrochildPipe[0], STDIN_FILENO);
		close(brotherBrochildPipe[1]);
		printf("Number of processes owned by root:\n");
		execvp(wc, args2);
	}
	else
	{
		dup2(brotherBrochildPipe[1], STDOUT_FILENO);
		execvp(ps, args);
	}



	return 0;
}
