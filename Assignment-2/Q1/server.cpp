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

int current_Amount;

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
		// For finding client 1
		int temp_VarSend;
		for (int q = 0 ; q < 3 ; q++)
		{
			if (order_Maintain[q] == 1)
			{
				temp_VarSend = q;
			}
		}
		// Client 1 end status
		char client1_EndStatus[100];
		val2 = recvfrom(sockfd, (char *)client1_EndStatus, MAXLINE, 0, (struct sockaddr *)&cliaddr[temp_VarSend], &val1[temp_VarSend]);
		
		
		// For finding client 2
		int temp_VarSend1;
		for (int q = 0 ; q < 3 ; q++)
		{
			if (order_Maintain[q] == 2)
			{
				temp_VarSend1 = q;
			}
		}

		// CLient 2 start status
		string stat1 = "Client2Start";
		char client2_StartStatus[stat1.length() + 1];
		int p = 0;
		for ( ; p < stat1.length() ; p++)
		{
			client2_StartStatus[p] = stat1[p];
		}
		client2_StartStatus[p] = '\0';
		sendto(sockfd, (const char *)client2_StartStatus, strlen(client2_StartStatus),0, (const struct sockaddr *) &cliaddr[temp_VarSend1],val1[temp_VarSend1]);


	

		// Client 2 end status
		char client2_EndStatus[100];
		val2 = recvfrom(sockfd, (char *)client2_EndStatus, MAXLINE, 0, (struct sockaddr *)&cliaddr[temp_VarSend1], &val1[temp_VarSend1]);
	

		// For finding client 3
		int temp_VarSend2;
		for (int q = 0 ; q < 3 ; q++)
		{
			if (order_Maintain[q] == 3)
			{
				temp_VarSend2 = q;
			}
		}

		// CLient 3 start status
		string stat2 = "Client3Start";
		char client3_StartStatus[stat2.length() + 1];
		int p1 = 0;
		for ( ; p1 < stat2.length() ; p1++)
		{
			client3_StartStatus[p1] = stat2[p1];
		}
		client3_StartStatus[p1] = '\0';
		sendto(sockfd, (const char *)client3_StartStatus, strlen(client3_StartStatus),0, (const struct sockaddr *) &cliaddr[temp_VarSend2],val1[temp_VarSend2]);
	
		srand(time(0));
		current_Amount = (rand() % 50001);
		int withdraw_Amount;
		cout << "You current account have : ";
		cout << current_Amount << endl ;

		tryAgain:
		cout << "Enter amount you want to withdraw (max: 25000): ";
		cin >> withdraw_Amount;
		if (withdraw_Amount > current_Amount)
		{
			cout << "Withdraw amount exceeds current account amount ." << endl;
			goto tryAgain;
		}
		if (withdraw_Amount > 25000)
		{
			cout << "Withdraw amount exceeds withdrawing limit ." << endl ;
			goto tryAgain;
		}
		string amount_Send;
		amount_Send += to_string(current_Amount);
		amount_Send += ":";
		amount_Send += to_string(withdraw_Amount);
		char amount_SendC[amount_Send.length() + 1];
		int p5 = 0;
		for (; p5 < amount_Send.length() ; p5++)
		{
			amount_SendC[p5] = amount_Send[p5];
		}
		amount_SendC[p5] = '\0';
		sendto(sockfd, (const char *)amount_SendC, strlen(amount_SendC),0, (const struct sockaddr *) &cliaddr[temp_VarSend2],val1[temp_VarSend2]);


		// Client 3 end status
		char client3_EndStatus[100];
		val2 = recvfrom(sockfd, (char *)client3_EndStatus, MAXLINE, 0, (struct sockaddr *)&cliaddr[temp_VarSend2], &val1[temp_VarSend2]);


	//}

	
	return 0;
}