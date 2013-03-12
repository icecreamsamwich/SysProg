/*
 * writeSharePricev.c
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
#define UPPER 4
#define LOWER 0
#define RANDHIGH 83
#define RANDLOW 27

int main(int argc, char *argv[])
{
	//time_t seconds;
	//srand((unsigned int) seconds);
	srand(time(NULL));

	//

	key_t key = 15;
	int shmid;
	//int sizeMem = 100;
	struct companyInfo * ptrCI = NULL;

	struct companyInfo arrayCompInfo[5];

	strcpy(arrayCompInfo[0].name, "A.I.B");
	arrayCompInfo[0].sharePrice = 428;
	strcpy(arrayCompInfo[1].name, "U.C.C");
	arrayCompInfo[1].sharePrice = 137;
	strcpy(arrayCompInfo[2].name, "C.I.T");
	arrayCompInfo[2].sharePrice = 246;
	strcpy(arrayCompInfo[3].name, "E.M.C");
	arrayCompInfo[3].sharePrice = 45;
	strcpy(arrayCompInfo[4].name, "V.H.I");
	arrayCompInfo[4].sharePrice = 876;


	int i;
	for(i=0;i<=4;i++){
		printf("Name of Company: %s\nShare Price: %d\n", arrayCompInfo[i].name, arrayCompInfo[i].sharePrice);
	}

	int sizeOfCompanyInfo = sizeof(struct companyInfo);
	int sizeOfFiveCompanyInfos = (5*(sizeOfCompanyInfo));
	printf("Size of an account: %d\n", sizeOfCompanyInfo);
	printf("Size of 5 accounts: %d\n", sizeOfFiveCompanyInfos);


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

	do
	{
		ptrCIlooper = ptrCI;
		int x;
		for(x=0;x<=4;x++)
		{
			memcpy (ptrCIlooper, &arrayCompInfo[x], sizeOfCompanyInfo);
			ptrCIlooper++;
		}
		int timer = rand() % (MAX - MIN +1) + MIN;
		printf("Timer: %d\n", timer);
		sleep(timer);
		int compInfoSelector = rand() % (UPPER - LOWER +1) + LOWER;
		printf("compInfoSelector: %d\n", compInfoSelector);
		int randNum = rand() % (RANDHIGH - RANDLOW +1) + RANDLOW;
		int newPrice = ((timer)*(randNum));
		printf("newPrice: %d\n", newPrice);
		printf("------------------------\n");
		arrayCompInfo[compInfoSelector].sharePrice = newPrice;
	}while(1);

	//	printf("Size: %d\n", (int) ptrToStatInfo->st_size);

	//	free (ptrCI);

	return 0;
}

