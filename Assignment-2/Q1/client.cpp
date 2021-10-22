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

string card_NoConst = "1234-5678-90123";
string pin_NoConst = "5678";

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
	val2 = recvfrom(sockfd, (char *)task_Assigned, 100, 0, (struct sockaddr *)&cliaddr, &val1);
	task_Assigned[val2] = '\0';
	cout << "Task No. Assigned to this terminal : " << task_Assigned << endl;




	if (task_Assigned[0] == '1')
	{
		char waitingForSignal[MAXLINE];
		val2 = recvfrom(sockfd, (char *)waitingForSignal, MAXLINE, 0, (struct sockaddr *)&cliaddr, &val1);
		waitingForSignal[val2] = '\0';


		string card_No_User;
		cout << "Enter your card no. : ";
		getline(cin, card_No_User);
		bool confirmationCardNo = false;
		if (card_NoConst.compare(card_No_User) == 0)
		{
			confirmationCardNo = true;
		}
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

		string user_Pin;
		cout << "Enter your pin number : ";
		getline(cin,user_Pin);
		bool checkPin = false;
		if (pin_NoConst.compare(user_Pin) == 0)
		{
			checkPin = true;
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



	

	if (task_Assigned[0] == '3')
	{
		char waitingForStatus2[MAXLINE];
		val2 = recvfrom(sockfd, (char *)waitingForStatus2, MAXLINE, 0, (struct sockaddr *)&cliaddr, &val1);
		waitingForStatus2[val2] = '\0';


		char all_Amount[MAXLINE];
		val2 = recvfrom(sockfd, (char *)all_Amount, MAXLINE, 0, (struct sockaddr *)&cliaddr, &val1);
		all_Amount[val2] = '\0';
		
		bool first = false;
		string current_AmountS;
		string withdraw_AmountS;
		for (int p6 = 0 ; p6 < val2 ; p6++)
		{
			if (all_Amount[p6] == ':')
			{
				first = true;
				continue;
			}
			if (first == false)
			{
				current_AmountS += all_Amount[p6];
			}
			else if (first = true)
			{
				withdraw_AmountS += all_Amount[p6];
			}
		}
		int current_Amount = stoi(current_AmountS);
		int withdraw_Amount = stoi(withdraw_AmountS);
		current_Amount = current_Amount - withdraw_Amount;
		cout << "Withdraw Amount : " << withdraw_Amount << endl ;
		cout << "Updated Account Balance : " << current_Amount << endl ;

		char task3_SendingStatus[] = "Task 3 completed";
		sendto(sockfd, (const char *)task3_SendingStatus, strlen(task3_SendingStatus), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

	}

	exit(sockfd);

	return 0;
}
