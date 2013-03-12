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
	struct question firstQuestion;
	strcpy(firstQuestion.question, "What is the capital of Ireland?");
	strcpy(firstQuestion.ansOne, "1: Cork");
	strcpy(firstQuestion.ansTwo,"2: Galway");
	strcpy(firstQuestion.ansThree,"3: Dublin");
	strcpy(firstQuestion.ansFour,"4: Belfast");
	firstQuestion.index = 0;
	struct question secondQuestion;
	strcpy(secondQuestion.question, "Where is London?");
	strcpy(secondQuestion.ansOne, "1: Japan");
	strcpy(secondQuestion.ansTwo,"2: England");
	strcpy(secondQuestion.ansThree,"3: Ireland");
	strcpy(secondQuestion.ansFour,"4: America");
	secondQuestion.index = 1;
	struct question thirdQuestion;
	strcpy(thirdQuestion.question, "Which of these can breath underwater?");
	strcpy(thirdQuestion.ansOne, "1: Human");
	strcpy(thirdQuestion.ansTwo,"2: Dog");
	strcpy(thirdQuestion.ansThree,"3: Wildebeast");
	strcpy(thirdQuestion.ansFour,"4: Fish");
	thirdQuestion.index = 2;
	struct question fourthQuestion;
	strcpy(fourthQuestion.question, "What is red and bad for your teeth?");
	strcpy(fourthQuestion.ansOne, "1: Bricks");
	strcpy(fourthQuestion.ansTwo,"2: Apples");
	strcpy(fourthQuestion.ansThree,"3: Tomatoes");
	strcpy(fourthQuestion.ansFour,"4: Cherries");
	fourthQuestion.index = 3;

	int intAnswers[] = {3,2,4,1};


	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	/*  Remove any old socket and create an unnamed socket for the server.  */

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/*  Name the socket.  */

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); //htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	/*  Create a connection queue and wait for clients.  */

	printf("Server Socket ID: %d\n", server_sockfd);
	listen(server_sockfd, 5);
	while(1) {
		char name[15];
		int ans;
		char result[50];
		int count;

		printf("server waiting\n");

		/*  Accept a connection.  */

		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		if (client_sockfd != -1)
		{
			printf("Connection from %s\n", inet_ntoa(client_address.sin_addr));
			printf("Client Socket ID: %d\n", client_sockfd);
		}
		/*  We can now read/write to client on client_sockfd.  */

		read(client_sockfd, &name, sizeof(name));
		printf("Clients name: %s\n", name);
		int score = 0;
		for(count=0;count<4;count++)
		{
			switch(count)
			{
			case 0:
				write(client_sockfd, &firstQuestion, sizeof(struct question));
				break;
			case 1:
				write(client_sockfd, &secondQuestion, sizeof(struct question));
				break;
			case 2:
				write(client_sockfd, &thirdQuestion, sizeof(struct question));
				break;
			case 3:
				write(client_sockfd, &fourthQuestion, sizeof(struct question));
			break;
			}

			read(client_sockfd, &ans, sizeof(ans));
			printf("Received answer: %d\nActual answer: %d\n", ans, intAnswers[count]);
			if(ans == intAnswers[count])
			{
				strcpy(result,"Congratulations! Correct Answer!");
				score++;
			}
			else
			{
				strcpy(result,"Incorrect Answer!");
			}
			write(client_sockfd, &result, sizeof(result));
		}
		write(client_sockfd, &score, sizeof(score));
		close(client_sockfd);
	}
	return 0;
}

