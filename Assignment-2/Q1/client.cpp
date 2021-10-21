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

#define PORT 8080
#define MAXLINE 1024

int main()
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr[2];
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
	val2 = recvfrom(sockfd, (char *)task_Assigned, 100, 0, (struct sockaddr *)&cliaddr, &val1);
	task_Assigned[val2] = '\0';
	cout << "Task No. Assigned to this terminal : " << task_Assigned << endl;

	if (task_Assigned[0] == '1')
	{
		string Card_No1;
		char card_No_RecieveC[100];
		val2 = recvfrom(sockfd, (char *)card_No_RecieveC, 100, 0, (struct sockaddr *)&cliaddr, &val1);
		card_No_RecieveC[val2] = '\0';
		for (int x = 0; x < strlen(card_No_RecieveC); x++)
		{
			Card_No1 += card_No_RecieveC[x];
		}
		//cout << "Card No. : " << card_No_RecieveC << endl;
		string reading_CardNo;
		ifstream readCardDb("CardDB");
		bool confirmationCardNo = true;
		while (getline(readCardDb, reading_CardNo))
		{
			for (int i = 0; i < reading_CardNo.length(); i++)
			{
				if (reading_CardNo[i] != card_No_RecieveC[i])
				{
					confirmationCardNo = false;
					break;
				}
			}
			if (confirmationCardNo == true)
			{
				break;
			}
		}
		readCardDb.close();
		if (confirmationCardNo == true)
		{
			cout << "Entered card number is correct ." << endl;
			char task1_SendingStatus[] = "Task 1 completed";
			sendto(sockfd, (const char *)task1_SendingStatus, strlen(task1_SendingStatus), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
		}
		else if (confirmationCardNo == false)
		{
			cout << "Entered card number is not correct ." << endl;
			char task1_SendingStatus[] = "Task 1 not completed";
			sendto(sockfd, (const char *)task1_SendingStatus, strlen(task1_SendingStatus), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
		}
	}
	if (task_Assigned[0] == '2')
	{
		char waitingForStatus[MAXLINE];
		val2 = recvfrom(sockfd, (char *)waitingForStatus, MAXLINE, 0, (struct sockaddr *)&cliaddr, &val1);
		waitingForStatus[val2] = '\0';
		string Card_No2;
		bool pass1 = false;
		for (int p = 0; p < val2; p++)
		{
			if (waitingForStatus[p] == ':')
			{
				pass1 = true;
				continue;
			}
			if (pass1 == true)
			{
				Card_No2 += waitingForStatus[p];
			}
		}

		char pin_Recieved[100];
		val2 = recvfrom(sockfd, (char *)pin_Recieved, 100, 0, (struct sockaddr *)&cliaddr, &val1);
		pin_Recieved[val2] = '\0';
		string reading_Pin;
		ifstream readPinDb("PinDB");

		bool eligible = false;
		bool checkPin = false;
		int s = 0;
		while (getline(readPinDb, reading_Pin))
		{
			s=0;
			string fileCardNo;
			while (reading_Pin[s] != ':')
			{
				fileCardNo += reading_Pin[s];
				s++;
			}
			if (fileCardNo.compare(Card_No2) == 0)
			{
				break;
			}
		}
		s++;

		string pin_RecievedS;
		for (int f = 0 ; f < val2 ; f++)
		{
			pin_RecievedS += pin_Recieved[f];
		}
		string comparePin;
		for (; s < reading_Pin.length() ; s++)
		{
			comparePin += reading_Pin[s];
		}
		if (comparePin.compare(pin_RecievedS) == 0)
		{
			checkPin = true;
		}
		else
		{
			checkPin = false;
		}
		

		if (checkPin == false)
		{
			cout << "Invalid Pin" << endl;
			char task2_SendingStatus[] = "Task 2 not completed";
			sendto(sockfd, (const char *)task2_SendingStatus, strlen(task2_SendingStatus), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
		}
		else if (checkPin == true)
		{
			cout << "Correct Pin" << endl;
			char task2_SendingStatus[] = "Task 2 completed";
			sendto(sockfd, (const char *)task2_SendingStatus, strlen(task2_SendingStatus), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
		}
	}

	exit(sockfd);

	return 0;
}
