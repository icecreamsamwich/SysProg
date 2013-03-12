#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <libio.h> // To include NULL


int main(int argc, char *argv[])
{
    	if(argc != 2)    
        	return 1;
 
    	struct stat fileInfo;
    	if(stat(argv[1],&fileInfo) < 0)    
       		return 1;
 
	printf("File Owners UID: %d\n", fileInfo.st_uid);
	printf("File Owners GID: %d\n", fileInfo.st_gid);
	printf("Size of File: %d\n", fileInfo.st_size);
	printf("No. of blocks: %d\n", fileInfo.st_blocks);
 	printf("Last file access: %s", ctime(&fileInfo.st_atime));
	printf("Protection field: %o\n\n", fileInfo.st_mode);

	if (fileInfo.st_mode & S_IFDIR)
		printf("This is a directory\n");

	struct passwd *pPwdInfo = NULL;
	pPwdInfo = getpwuid(fileInfo.st_uid);
	printf("The file '%s' is owned by the user %s\n", argv[1], pPwdInfo->pw_name);
	printf("The file was last changed on: %s", ctime(&fileInfo.st_ctime));
    
    return 0;
}
