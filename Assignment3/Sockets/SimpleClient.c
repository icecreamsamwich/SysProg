/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "question.h"

int main()
{
	char name[15];
	scanf("%s", name);

	struct question firstQuestion;
	//char ans[2];
	int ans;
	char response[50];
	int score = 0;

	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch = 'A';

	/*  Create a socket for the client.  */

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/*  Name the socket, as agreed with the server.  */

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9734);
	len = sizeof(address);

	/*  Now connect our socket to the server's socket.  */

	result = connect(sockfd, (struct sockaddr *)&address, len);

	if(result == -1) {
		perror("oops: client3");
		return 1;
	}

	/*  We can now read/write via sockfd.  */

	write(sockfd, &name, sizeof(name));
	int count;
	for(count=0;count<=3;count++)
	{
		read(sockfd, &firstQuestion, sizeof(struct question));

		printf("%s\n%s\n%s\n%s\n%s\nAnswer: (1,2,3 or 4) \n", firstQuestion.question, firstQuestion.ansOne, firstQuestion.ansTwo, firstQuestion.ansThree, firstQuestion.ansFour);
		do
		{
		scanf("%d", &ans);
		} while(ans < 1 || ans > 4);
		write(sockfd, &ans, sizeof(ans));
		read(sockfd, &response, sizeof(response));
		printf("%s\n", response);
	}
	read(sockfd, &score, sizeof(score));
	printf("You scored: %d\n", score);

	close(sockfd);
	return 0;
}
