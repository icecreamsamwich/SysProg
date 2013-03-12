#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libio.h> // To include NULL
#include <errno.h> 


int main(int argc, char *argv[])
{
	int uid = atoi(argv[1]);
	errno = 0;
	struct passwd *pPwdInfo = NULL;
	struct passwd *pPwdEntry = NULL;
	FILE *fpPasswd = fopen("/etc/passwd","r"); // Opens /etc/passwd to get a list of all users
	
	if (argc == 2) {
	pPwdInfo = getpwuid(uid);
	if ((errno) == -1) {	// To check if getpwuid failed
		perror("getpwuid failed!");
	}
	else
	{
		if (pPwdInfo != NULL) {
			printf("User Name: %s\n", pPwdInfo->pw_name);
			printf("User Password: %s\n", pPwdInfo->pw_passwd);
			printf("User ID: %d\n", pPwdInfo->pw_uid);
			printf("Group ID: %d\n", pPwdInfo->pw_gid);
			printf("User Info: %s\n", pPwdInfo->pw_gecos);
			printf("Home Directory: %s\n", pPwdInfo->pw_dir);
			printf("Shell Program: %s\n", pPwdInfo->pw_shell);
		}
		else
		{
			perror("No entry found matching the given UID");
		}
	}
	}
	else
	{
		printf("Usage userinfo <uid>\n");
	}
	while (!feof(fpPasswd)) {
		pPwdEntry = getpwent();
		if ( pPwdEntry->pw_gid == pPwdInfo->pw_gid){
			printf("*************Users with same Group ID***********\n");
			printf("User Name: %s\n", pPwdEntry->pw_name);
			printf("User Password: %s\n", pPwdEntry->pw_passwd);
			printf("User ID: %d\n", pPwdEntry->pw_uid);			
			printf("Group ID: %d\n", pPwdEntry->pw_gid);
			printf("User Info: %s\n", pPwdEntry->pw_gecos);			
			printf("Home Directory: %s\n", pPwdEntry->pw_dir);
			printf("Shell Program: %s\n", pPwdEntry->pw_shell);
		}
		if ( pPwdEntry->pw_gid == 0) {
			printf("*************Users with Group ID = 0***********\n");
			printf("User Name: %s\n", pPwdEntry->pw_name);
			printf("User Password: %s\n", pPwdEntry->pw_passwd);
			printf("User ID: %d\n", pPwdEntry->pw_uid);			
			printf("Group ID: %d\n", pPwdEntry->pw_gid);
			printf("User Info: %s\n", pPwdEntry->pw_gecos);			
			printf("Home Directory: %s\n", pPwdEntry->pw_dir);
			printf("Shell Program: %s\n", pPwdEntry->pw_shell);
		}
	
	}
	fclose(fpPasswd);
return 0;
}














