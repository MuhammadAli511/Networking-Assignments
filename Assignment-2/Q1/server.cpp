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
	struct sockaddr_in servaddr, cliaddr[3];
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

	socklen_t val1[3];
	for (int p = 0; p < 3 ; p++)
	{
		val1[p] = sizeof(cliaddr[p]);
	}
	socklen_t val2;
	int check_List[] = {-1, -1, -1};
	int order_Maintain[] = {-1, -1, -1};
	int client_Count = 1;
	int index_cliaddr = 0;
	//while (1)
	//{
		while (client_Count != 4)
		{
			char client1_Connection[MAXLINE];
			val2 = recvfrom(sockfd, (char *)client1_Connection, MAXLINE, 0, (struct sockaddr *)&cliaddr[index_cliaddr], &val1[index_cliaddr]);
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
			check_List[index_cliaddr] = temp_RandomI;
			order_Maintain[index_cliaddr] = temp_RandomI;
			send_randomS = to_string(temp_RandomI) ;
			cout << "Random Number : " << send_randomS << endl;
			char send_RandomC[send_randomS.length() + 1];
			int m = 0;
			for (; m < send_randomS.length() ; m++)
			{
				send_RandomC[m] = send_randomS[m];
			}
			send_RandomC[m] = '\0';
			sendto(sockfd, (const char *)send_RandomC, strlen(send_RandomC),0, (const struct sockaddr *) &cliaddr[index_cliaddr],val1[index_cliaddr]);
			index_cliaddr++;
		}
		// For card input
		string card_No_User;
		cout << "Enter your card no. : ";
		getline(cin, card_No_User);
		char card_No_UserC[card_No_User.length() + 1];
		int n = 0;
		for (; n < card_No_User.length() ; n++)
		{
			card_No_UserC[n] = card_No_User[n];
		}
		card_No_UserC[n] = '\0';
		int temp_VarSend;
		for (int q = 0 ; q < 3 ; q++)
		{
			if (order_Maintain[q] == 1)
			{
				temp_VarSend = q;
			}
		}
		sendto(sockfd, (const char *)card_No_UserC, strlen(card_No_UserC),0, (const struct sockaddr *) &cliaddr[temp_VarSend],val1[temp_VarSend]);
	


		char client1_EndStatus[100];
		val2 = recvfrom(sockfd, (char *)client1_EndStatus, MAXLINE, 0, (struct sockaddr *)&cliaddr[temp_VarSend], &val1[temp_VarSend]);
		
		
		// For pin input
		int temp_VarSend1;
		for (int q = 0 ; q < 3 ; q++)
		{
			if (order_Maintain[q] == 2)
			{
				temp_VarSend1 = q;
			}
		}

		string stat1 = "Client2Start";
		stat1 += ":";
		stat1 += card_No_UserC;
		char client2_StartStatus[stat1.length() + 1];
		int p = 0;
		for ( ; p < stat1.length() ; p++)
		{
			client2_StartStatus[p] = stat1[p];
		}
		client2_StartStatus[p] = '\0';
		sendto(sockfd, (const char *)client2_StartStatus, strlen(client2_StartStatus),0, (const struct sockaddr *) &cliaddr[temp_VarSend1],val1[temp_VarSend1]);

		string user_Pin;
		cout << "Enter your pin number : ";
		getline(cin,user_Pin);
		char user_PinC[user_Pin.length() + 1 ];
		int u = 0;
		for (;u < user_Pin.length() ; u++)
		{
			user_PinC[u] = user_Pin[u];
		}
		user_PinC[u] = '\0';
		sendto(sockfd, (const char *)user_PinC, strlen(user_PinC),0, (const struct sockaddr *) &cliaddr[temp_VarSend1],val1[temp_VarSend1]);
	
		char client2_EndStatus[100];
		val2 = recvfrom(sockfd, (char *)client2_EndStatus, MAXLINE, 0, (struct sockaddr *)&cliaddr[temp_VarSend1], &val1[temp_VarSend1]);
	
	
	//}

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