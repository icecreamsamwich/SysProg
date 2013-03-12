/*
 * readSharePrice.c
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
#include <time.h>
#include "CompanyInfo.h"

#define MIN 1
#define MAX 10

int main(int argc, char *argv[])
{
	time_t seconds;
	srand((unsigned int) seconds);

	key_t key = 15;
	int shmid;
	//int sizeMem = 100;
	struct companyInfo * ptrCI = NULL;

	struct companyInfo companyInfoReadIn;
	int sizeOfCompanyInfo = sizeof(companyInfoReadIn);
	int sizeOfFiveCompanyInfos = (5*(sizeOfCompanyInfo));


	shmid = shmget(key, sizeOfFiveCompanyInfos, 0644| IPC_CREAT);
	if (shmid == -1)
	{
		perror("shmget");
		return 1;
	}

	ptrCI = (struct companyInfo * ) shmat(shmid, (void*) 0, 0);
	if (ptrCI == (struct companyInfo*) -1)
	{
		perror("shmat error");
		return 1;
	}

	struct companyInfo * ptrCIlooper = ptrCI;
	int prevSharePrice[4];
	int bufferSharePrice;
	do
	{
		ptrCIlooper = ptrCI;
		int i;
		for(i=0;i<=4;i++)
		{
			bufferSharePrice = prevSharePrice[i];
			memcpy(&companyInfoReadIn, ptrCIlooper, sizeOfCompanyInfo);
			ptrCIlooper++;
			prevSharePrice[i] = companyInfoReadIn.sharePrice;
			printf("Name of Company: %s\nShare Price: %d\nDifference in Share Price: %d\n", companyInfoReadIn.name, companyInfoReadIn.sharePrice, ((companyInfoReadIn.sharePrice) - (bufferSharePrice)));
		}
		int timer = rand() % (MAX - MIN +1) + MIN;
		printf("Timer: %d\n", timer);
		printf("---------------------------------------\n");
		sleep(timer);
	}while(1);

	return 0;
}


