/*
 * DMString.c
 *
 *  Created on: Mar 4, 2013
 *      Author: samoleary
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char * ptr = NULL;
	ptr = malloc(256);

	strcpy(ptr, "Howdy");
	printf("Message is %s\n", ptr);

	free(ptr);
}
