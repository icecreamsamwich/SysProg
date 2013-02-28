#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include <string.h>

int main(int argc, char *argv[])
{
   FILE *myFile;
   char *const paramList[] = {"/bin/ls", NULL};
   char pathCommand[] = "/bin/ls";
   myFile = fopen("/home/samwich/SysProg/Assignment2/Task2/list.txt", "w");
   if(myFile == NULL)
   {
	perror("Failed to open file");
	return 1;
   }
   int myFileDes = fileno(myFile);
   if(dup2(myFileDes, STDOUT_FILENO) <0)
   {
	perror("Failed to redirect standard output");
	return 1;
   }
   if (argc == 2)
   {
	execv(pathCommand, paramList);
   }
   if(argc == 3)
   {
	char *const paramListNew[] = {"/bin/ls", argv[2], NULL};
	execv(pathCommand, paramListNew);
   }
   fclose(myFile);
   return 0;
}
