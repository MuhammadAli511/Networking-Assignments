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
#include <cstdlib>
#include <ctime>
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
	//memset(&cliaddr, 0, sizeof(cliaddr));

	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	socklen_t val1, val2;
	val1 = sizeof(cliaddr); //val1 is value/resuslt

	int check_List[] = {-1, -1, -1};

	int client_Count = 1;
	while (1)
	{
		while (client_Count != 4)
		{
			char client1_Connection[MAXLINE];
			val2 = recvfrom(sockfd, (char *)client1_Connection, MAXLINE, 0, (struct sockaddr *)&cliaddr, &val1);
			int index_Recieving = val2;
			client1_Connection[index_Recieving] = client_Count + 48;
			index_Recieving++;
			client1_Connection[index_Recieving] = '\0';
			cout << client1_Connection << endl;
			client_Count++;

			string send_randomS = "";
			int temp_RandomI;
		notUnique:
			srand(time(0));
			temp_RandomI = (rand() % 4);
			if (temp_RandomI == 0)
			{
				cout << "Transaction Failed" << endl;
				goto notUnique;
			}
			else
			{
				for (int j = 0; j < 3; j++)
				{
					if (temp_RandomI == check_List[j])
					{
						goto notUnique;
					}
				}
			}
			check_List[client_Count - 1] = temp_RandomI;
			
			send_randomS = to_string(temp_RandomI) ;
			cout << "Random Number : " << send_randomS << endl;
			char send_RandomC[send_randomS.length() + 1];
			int m = 0;
			for (; m < send_randomS.length() ; m++)
			{
				send_RandomC[m] = send_randomS[m];
			}
			send_RandomC[m] = '\0';
			sendto(sockfd, (const char *)send_RandomC, strlen(send_RandomC),0, (const struct sockaddr *) &cliaddr,val1);
		}
	}

	/*string appended_String = "Hello ";
	char sending_String[appended_String.length() + 1];
	int l = 0;
	for (; l < appended_String.length(); l++)
	{
		sending_String[l] = appended_String[l];
	}
	sending_String[l] = '\0';
	sendto(sockfd, (const char *)sending_String, strlen(sending_String), 0, (const struct sockaddr *)&cliaddr, val1);*/

	return 0;
}