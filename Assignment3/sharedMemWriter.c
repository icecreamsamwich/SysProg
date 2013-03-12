/*
 * sharedMemWriter.c
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

	shmid = shmget(key, sizeMem, 0644| IPC_CREAT);
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

	strcpy(smPtr, "The Copied String(T)");
	printf("Value of smPtr: %s\n", smPtr);

	return 0;
}
