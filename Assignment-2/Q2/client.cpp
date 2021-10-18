#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main() {
	
	
	int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(3001);
    connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));
	
	cout << "1. Concatenate two strings " << endl ;
    cout << "2. Find the first occurence of a character in a string " << endl ;
    cout << "3. Compare two strings " << endl ;
    cout << "4. Check whether string is palindrome or not " << endl ;
    cout << "5. String number addition " << endl ;
    tryAgain:
    cout << "Enter a number from the above menu : ";
    int choice_SendingI;
    cin >> choice_SendingI;
    if (choice_SendingI < 1 || choice_SendingI > 5)
    {
        cout << "Enter a valid option ." << endl ;
        goto tryAgain;
    }
    char sending_choiceC[1];
    sending_choiceC[0] = char(choice_SendingI) + 48;
    send(sock, sending_choiceC, sizeof(sending_choiceC), 0);
    string sending_choiceS;
    for (int i = 0 ; i < 1 ; i++)
    {
        sending_choiceS += sending_choiceC[i];
    }
    
    if (sending_choiceS == "1")
    {
        string valueS1;
        cout << "Enter 1st string for concatenation : " ;
        cin.ignore();
        getline(cin,valueS1);
        char valueC1[valueS1.length()+1];
        int i = 0;
        for(; i < valueS1.length() ; i++)
        {
            valueC1[i] = valueS1[i];
        }
        valueC1[i] = '\0';
        send(sock, valueC1, sizeof(valueC1), 0);

        cout << "Enter 2nd string for concatenation : " ;
        string valueS2;
        getline(cin,valueS2);
        char valueC2[valueS2.length()+1];
        i = 0;
        for(; i < valueS2.length() ; i++)
        {
            valueC2[i] = valueS2[i];
        }
        valueC2[i] = '\0';
        send(sock, valueC2, sizeof(valueC2), 0);

        cout << "Combined String : " << endl ;
        char combinedRecieveC[500];
        recv(sock, &combinedRecieveC, sizeof(combinedRecieveC), 0);
        cout << combinedRecieveC;

    }
    else if (sending_choiceS == "2")
    {
        string value2S1;
        cout << "Enter 1st string for character searching : " ;
        cin.ignore();
        getline(cin,value2S1);
        char value2C1[value2S1.length()+1];
        int i = 0;
        for(; i < value2S1.length() ; i++)
        {
            value2C1[i] = value2S1[i];
        }
        value2C1[i] = '\0';
        send(sock, value2C1, sizeof(value2C1), 0);

        cout << "Enter character to be searched : " ;
        char search2Char1[1];
        cin >> search2Char1[0];
        send(sock, search2Char1, sizeof(search2Char1), 0);

        cout << "Character at index : ";
        char recieveIndex1[3];
        recv(sock, &recieveIndex1, sizeof(recieveIndex1), 0);
        cout << recieveIndex1 ;
    }
    /*else if (sending_choiceS == "3")
    {
        
    }
    else if (sending_choiceS == "4")
    {
        
    }
    else if (sending_choiceS == "5")
    {
        
    }*/







	
	
	
	exit(sock);

	return 0;
}
