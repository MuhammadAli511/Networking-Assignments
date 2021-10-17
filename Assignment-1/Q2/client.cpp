// Client side implementation of UDP client-server model
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

#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main()
{
	int sockfd;
	struct sockaddr_in	 servaddr,cliaddr;
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	//memset(&servaddr, 0, sizeof(servaddr));
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	string cont;
	while(cont != "N" && cont != "n")
	{
		string movie_Name;
		cout << "First enter your desired movie : " ;
		getline(cin,movie_Name);

		string choice;
		cout << "Enter polarity, rating or sentiments : ";
		cin >> choice;

		string send_String;
		send_String += movie_Name;
		send_String += "\n";
		send_String += choice;
		char sending[send_String.length()+1];
		int i = 0;
		for (;i < send_String.length() ; i++)
		{
			sending[i] = send_String[i];
		}
		sending[i] = '\0';
		socklen_t val1,val2;
		val1 = sizeof(cliaddr);
		sendto(sockfd, (const char *)sending, strlen(sending),0, (const struct sockaddr *) &servaddr,sizeof(servaddr));
		sleep(1);
		char buffer[5000];
		val2 = recvfrom(sockfd, (char *)buffer, 5000,0, (struct sockaddr *) &cliaddr,&val1);
		buffer[val2] = '\0';
		cout << buffer << endl ;
		cout << "Do you want to countinue Y/N .";
		cin >> cont;
		cin.ignore();
	}



	close(sockfd);
	return 0;
}


