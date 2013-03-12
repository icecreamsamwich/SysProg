/*
 * DMStruct.c
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

int main(int argc, char * argv[])
{
	struct stat* ptrToStatInfo = (struct stat*) malloc(sizeof(struct stat));

	struct stat fileInfo;

	if (stat(argv[1], &fileInfo) == -1)
	{
		perror("stat");
		return 1;
	}

	memcpy (ptrToStatInfo, &fileInfo, sizeof(struct stat));

	printf("Size: %d\n", (int) ptrToStatInfo->st_size);

	free (ptrToStatInfo);

	return 0;
}
