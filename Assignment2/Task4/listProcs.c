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
	char aux[] = "aux";
	char wc[] = "wc";
	char minusl[] = "-l";

	int parentSisterPipe[2];	// write[1] read[0]
	int sisterProc;


	pipe(parentSisterPipe);

	sisterProc = fork();

	if(sisterProc == 0)
	{// Sister Process: wc -l
		dup2(parentSisterPipe[0], STDIN_FILENO);
		close(parentSisterPipe[1]);
		printf("Number of processes running:\n");
		execlp(wc, wc, minusl, NULL); // wc -l
	}
	else
	{// Parent Process: ps aux
		dup2(parentSisterPipe[1], STDOUT_FILENO);
		execlp(ps, ps, aux, NULL); // ps aux
	}

	return 0;
}
