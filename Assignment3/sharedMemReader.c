/*
 * sharedMemReader.c
 *
 *  Created on: Mar 4, 2013
 *      Author: samoleary
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
	key_t key = 15;
	int shmid;
	int sizeMem = 100;
	char * smPtr = NULL;

	shmid = shmget(key, 0,0);
	if (shmid == -1)
	{
		perror("shmget");
		return 1;
	}

	smPtr = (char * ) shmat(shmid, (void*) 0, 0);
	if (smPtr == (char*) -1)
	{
		perror("shmat error");
		return 1;
	}

	printf("ID of Memory Block: %d\n", (int) shmid);
	printf("Value of smPtr: %s\n", smPtr);

	if (smPtr != NULL)
		shmdt(smPtr);

	return 0;
}
