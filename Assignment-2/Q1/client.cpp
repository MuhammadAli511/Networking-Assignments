#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;

#define PORT 8080
#define MAXLINE 1024

int main()
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	//memset(&servaddr, 0, sizeof(servaddr));
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	socklen_t val1, val2;
	val1 = sizeof(cliaddr);




	char client1_connect_C[MAXLINE] = "Client ";
	sendto(sockfd, (const char *)client1_connect_C, strlen(client1_connect_C), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));


	char task_Assigned[100];
	val2 = recvfrom(sockfd, (char *)task_Assigned, 100,0, (struct sockaddr *) &cliaddr,&val1);
	task_Assigned[val2] = '\0';
	cout << "Task No. Assigned to this terminal : " << task_Assigned << endl ;

	exit(sockfd);

	return 0;
}
