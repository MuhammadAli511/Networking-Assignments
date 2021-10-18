#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3001);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_socket, 5);
    int client_socket;
    int client_Count = 0;

    client_socket = accept(server_socket, NULL, NULL);

    cout << "1. Concatenate two strings " << endl ;
    cout << "2. Find the first occurence of a character in a string " << endl ;
    cout << "3. Compare two strings " << endl ;
    cout << "4. Check whether string is palindrome or not " << endl ;
    cout << "5. String number addition " << endl ;
    
    char recieve_choiceC[1];
    recv(client_socket, &recieve_choiceC, sizeof(recieve_choiceC), 0);
    cout << "Client selected option = " << recieve_choiceC[0] << endl ;
    string recieve_choiceS;
    for (int i = 0 ; i < 1 ; i++)
    {
        recieve_choiceS += recieve_choiceC[i];
    }

    if (recieve_choiceS == "1")
    {
        char r1ValueC1[200];
        recv(client_socket, &r1ValueC1, sizeof(r1ValueC1), 0);
        char r1ValueC2[200];
        recv(client_socket, &r1ValueC2, sizeof(r1ValueC2), 0);
        string combinedSendS1;
        for (int i = 0 ; i < strlen(r1ValueC1) ; i++)
        {
            combinedSendS1 += r1ValueC1[i];
        }
        for (int i = 0 ; i < strlen(r1ValueC2) ; i++)
        {
            combinedSendS1 += r1ValueC2[i];
        }
        char combinedSendC1[combinedSendS1.length() + 1];
        int i = 0;
        for (; i < combinedSendS1.length() ; i++)
        {
            combinedSendC1[i] = combinedSendS1[i];
        }
        combinedSendC1[i] = '\0';
        send(client_socket, combinedSendC1, sizeof(combinedSendC1), 0);
    }
    else if  (recieve_choiceS == "2")
    {
        char r2ValueS1[200];
        recv(client_socket, &r2ValueS1, sizeof(r2ValueS1), 0);

        char r2ValueC1[1];
        recv(client_socket, &r2ValueC1, sizeof(r2ValueC1), 0);

        int found = -1;
        for (int i = 0 ; i < strlen(r2ValueS1) ; i++)
        {
            if (r2ValueC1[0] == r2ValueS1[i])
            {
                found = i;
                found++;
                break;
            }
        }
        string indexSend1 = to_string(found);
        int j = 0;
        char indexSend2[indexSend1.length()+1];
        for ( ; j < indexSend1.length() ; j++)
        {
            indexSend2[j] = indexSend1[j];
        }
        indexSend2[j] = '\0';
        send(client_socket, indexSend2, sizeof(indexSend2), 0);
    }
    /*else if  (recieve_choiceS == "3")
    {
        
    }
    else if  (recieve_choiceS == "4")
    {
        
    }
    else if  (recieve_choiceS == "5")
    {
        
    }*/










   

    exit(server_socket);
    return 0;
}
