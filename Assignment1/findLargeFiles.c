#include <sys/types.h>
#include <dirent.h>
#include <libio.h> // To include NULL
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <string.h>

int main(int argc, char *argv[]) {
   struct dirent *direntp;
   struct dirent *subDirentp;
   DIR *dirp;
   DIR *subDirp;
   struct stat fileInfo;
   char name[30];
   //if(stat(argv[1],&fileInfo) < 0)    
   //   	return 1;

   if ((dirp = opendir("/home/sam/Desktop/Sam")) == NULL) {
      perror ("Failed to open directory");
      return 1;
   }   

   while ((direntp = readdir(dirp)) != NULL)
  {
//      if (direntp->d_type == DT_DIR)
//      {
      	printf("Name: %s\nSubdirectories: \n", direntp->d_name);
//	strcpy(name,direntp->d_name);
//	if ((subDirp = opendir(name)) == NULL) {
//	  perror("Failed to open subdirectory\n");
//	  return 1; }

//	while ((subDirentp = readdir(subDirp)) != NULL)
//	{
//	  printf("SubName: %s\n", subDirentp->d_name);
//	}
//    }
  }

   while ((closedir(dirp) == -1) && (errno == EINTR)) ;
   return 0;
}

