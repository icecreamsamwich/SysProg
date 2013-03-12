#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
 
int main(int argc, char *argv[])
{
    if(argc != 2)    
        return 1;
 
    struct stat fileInfo;
    if(stat(argv[1],&fileInfo) < 0)    
       return 1;
 
		printf("File Owners UID: %d\n", fileInfo.st_uid);
		printf("Size of File: %d\n", fileInfo.st_size);
 		printf("Last file access: %s", ctime(&fileInfo.st_atime));

    
    return 0;
}
