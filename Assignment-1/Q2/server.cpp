// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
using namespace std;

#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	//memset(&servaddr, 0, sizeof(servaddr));
	//memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	

	while(1)
	{
		socklen_t val1, val2;
		val1 = sizeof(cliaddr); //val1 is value/resuslt
		char buffer[MAXLINE];
		val2 = recvfrom(sockfd, (char *)buffer, MAXLINE,0, ( struct sockaddr *) &cliaddr,&val1);
		buffer[val2] = '\0';
		string movie_Name;
		string specification;
		bool test = false;
		for (int i = 0 ; i < strlen(buffer) ; i++)
		{
			if (buffer[i] == '\n')
			{
				test = true;
				continue;
			}
			if (test == false)
			{
				movie_Name += buffer[i];
			}
			else if (test == true)
			{
				specification += buffer[i];
			}
		}

		
		string file_Name;
		file_Name += movie_Name;
		file_Name += "/";
		file_Name += specification;
		file_Name += ".txt";
		ifstream read_File(file_Name);
		string read_Line;
		int count = 0;
		string appended_String;
		while(getline(read_File,read_Line))
		{
			appended_String += read_Line;
		}
		char sending_String[appended_String.length()+1];
		int l = 0;
		for (;l < appended_String.length() ; l++)
		{
			sending_String[l] = appended_String[l];
		}
		sending_String[l] = '\0';
		sendto(sockfd, (const char *)sending_String, strlen(sending_String),0, (const struct sockaddr *) &cliaddr,val1);

	}
	
	return 0;
}
