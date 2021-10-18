#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>

using namespace std;

int convertToInteger(string val)
{
    if (val == "zero" || val == "zero")
    {
        return 0;
    }
    else if (val == "one" || val == "ONE")
    {
        return 1;
    }
    else if (val == "two" || val == "TWO")
    {
        return 2;
    }
    else if (val == "three" || val == "THREE")
    {
        return 3;
    }
    else if (val == "four" || val == "FOUR")
    {
        return 4;
    }
    else if (val == "five" || val == "FIVE")
    {
        return 5;
    }
    else if (val == "six" || val == "SIX")
    {
        return 6;
    }
    else if (val == "seven" || val == "SEVEN")
    {
        return 7;
    }
    else if (val == "eight" || val == "EIGHT")
    {
        return 8;
    }
    else if (val == "nine" || val == "NINE")
    {
        return 9;
    }
    else if (val == "ten" || val == "TEN")
    {
        return 10;
    }
    else if (val == "eleven" || val == "ELEVEN")
    {
        return 11;
    }
    else if (val == "twelve" || val == "TWELVE")
    {
        return 12;
    }
    else if (val == "thirteen" || val == "THIRTEEN")
    {
        return 13;
    }
    else if (val == "fourteen" || val == "FOURTEEN")
    {
        return 14;
    }
    else if (val == "fifteen" || val == "FIFTEEN")
    {
        return 15;
    }
    else if (val == "sixteen" || val == "SIXTEEN")
    {
        return 16;
    }
    else if (val == "seventeen" || val == "SEVENTEEN")
    {
        return 17;
    }
    else if (val == "eighteen" || val == "EIGHTEEN")
    {
        return 18;
    }
    else if (val == "nineteen" || val == "NINETEEN")
    {
        return 19;
    }
    else if (val == "twenty" || val == "TWENTY")
    {
        return 20;
    }
}

string convertToString(int val)
{
    if (val == 1)
    {
        return "one";
    }
    else if (val == 2)
    {
        return "two";
    }
    else if (val == 3)
    {
        return "three";
    }
    else if (val == 4)
    {
        return "four";
    }
    else if (val == 5)
    {
        return "five";
    }
    else if (val == 6)
    {
        return "six";
    }
    else if (val == 7)
    {
        return "seven";
    }
    else if (val == 8)
    {
        return "eight";
    }
    else if (val == 9)
    {
        return "nine";
    }
    else if (val == 10)
    {
        return "ten";
    }
    else if (val == 11)
    {
        return "eleven";
    }
    else if (val == 12)
    {
        return "twelve";
    }
    else if (val == 13)
    {
        return "thirteen";
    }
    else if (val == 14)
    {
        return "fourteen";
    }
    else if (val == 15)
    {
        return "fifteen";
    }
    else if (val == 16)
    {
        return "sixteen";
    }
    else if (val == 17)
    {
        return "seventeen";
    }
    else if (val == 18)
    {
        return "eighteen";
    }
    else if (val == 19)
    {
        return "nineteen";
    }
    else if (val == 20)
    {
        return "twenty";
    }
}

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

    while (1)
    {
        client_socket = accept(server_socket, NULL, NULL);
        pid_t pid1 = fork();
        if (pid1 == 0)
        {

            char recieve_choiceC[1];
            recv(client_socket, &recieve_choiceC, sizeof(recieve_choiceC), 0);
            cout << "Client selected option = " << recieve_choiceC[0] << endl;
            string recieve_choiceS;
            for (int i = 0; i < 1; i++)
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
                for (int i = 0; i < strlen(r1ValueC1); i++)
                {
                    combinedSendS1 += r1ValueC1[i];
                }
                for (int i = 0; i < strlen(r1ValueC2); i++)
                {
                    combinedSendS1 += r1ValueC2[i];
                }
                char combinedSendC1[combinedSendS1.length() + 1];
                int i = 0;
                for (; i < combinedSendS1.length(); i++)
                {
                    combinedSendC1[i] = combinedSendS1[i];
                }
                combinedSendC1[i] = '\0';
                cout << combinedSendC1;
                send(client_socket, combinedSendC1, sizeof(combinedSendC1), 0);
            }
            else if (recieve_choiceS == "2")
            {
                char r2ValueS1[200];
                recv(client_socket, &r2ValueS1, sizeof(r2ValueS1), 0);

                char r2ValueC1[1];
                recv(client_socket, &r2ValueC1, sizeof(r2ValueC1), 0);

                int found = -1;
                for (int i = 0; i < strlen(r2ValueS1); i++)
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
                char indexSend2[indexSend1.length() + 1];
                for (; j < indexSend1.length(); j++)
                {
                    indexSend2[j] = indexSend1[j];
                }
                indexSend2[j] = '\0';
                send(client_socket, indexSend2, sizeof(indexSend2), 0);
            }
            else if (recieve_choiceS == "3")
            {
                char r3ValueC1[200];
                recv(client_socket, &r3ValueC1, sizeof(r3ValueC1), 0);
                char r3ValueC2[200];
                recv(client_socket, &r3ValueC2, sizeof(r3ValueC2), 0);
                string valueIsTrue = "True";
                int k = 0;
                char cValueIsTrue[valueIsTrue.length() + 1];

                string valueIsFalse = "False";
                int l = 0;
                char cValueIsFalse[valueIsFalse.length() + 1];
                if (strlen(r3ValueC1) != strlen(r3ValueC2))
                {
                    goto returningFalse;
                }
                for (int i = 0; i < strlen(r3ValueC1); i++)
                {
                    if (r3ValueC1[i] != r3ValueC2[i])
                    {
                        goto returningFalse;
                    }
                }
                for (; k < valueIsTrue.length(); k++)
                {
                    cValueIsTrue[k] = valueIsTrue[k];
                }
                cValueIsTrue[k] = '\0';
                send(client_socket, cValueIsTrue, sizeof(cValueIsTrue), 0);
                goto end;

            returningFalse:
                for (; l < valueIsFalse.length(); l++)
                {
                    cValueIsFalse[l] = valueIsFalse[l];
                }
                cValueIsFalse[l] = '\0';
                send(client_socket, cValueIsFalse, sizeof(cValueIsFalse), 0);
            end:
                cout << "";
            }
            else if (recieve_choiceS == "4")
            {
                char r4ValueC1[200];
                recv(client_socket, &r4ValueC1, sizeof(r4ValueC1), 0);

                string valueIsTrue = "True";
                int k = 0;
                char cValueIsTrue[valueIsTrue.length() + 1];

                string valueIsFalse = "False";
                int l = 0;
                char cValueIsFalse[valueIsFalse.length() + 1];

                int z = strlen(r4ValueC1) - 1;
                for (int i = 0; i < strlen(r4ValueC1) / 2; i++)
                {
                    if (r4ValueC1[i] != r4ValueC1[z])
                    {
                        goto returningFalse1;
                    }
                    z--;
                }
                for (; k < valueIsTrue.length(); k++)
                {
                    cValueIsTrue[k] = valueIsTrue[k];
                }
                cValueIsTrue[k] = '\0';
                send(client_socket, cValueIsTrue, sizeof(cValueIsTrue), 0);
                goto end1;

            returningFalse1:
                for (; l < valueIsFalse.length(); l++)
                {
                    cValueIsFalse[l] = valueIsFalse[l];
                }
                cValueIsFalse[l] = '\0';
                send(client_socket, cValueIsFalse, sizeof(cValueIsFalse), 0);
            end1:
                cout << "";
            }
            else if (recieve_choiceS == "5")
            {
                char r5ValueC1[200];
                recv(client_socket, &r5ValueC1, sizeof(r5ValueC1), 0);
                char r5ValueC2[200];
                recv(client_socket, &r5ValueC2, sizeof(r5ValueC2), 0);

                string num1S;
                for (int y = 0; y < strlen(r5ValueC1); y++)
                {
                    num1S += r5ValueC1[y];
                }
                string num2S;
                for (int y = 0; y < strlen(r5ValueC2); y++)
                {
                    num2S += r5ValueC2[y];
                }
                int num1I = convertToInteger(num1S);
                int num2I = convertToInteger(num2S);
                int totalSumI = num1I + num2I;
                string totalSumS = convertToString(totalSumI);
                char totalSumC[totalSumS.length() + 1];
                int f = 0;
                for (; f < totalSumS.length(); f++)
                {
                    totalSumC[f] = totalSumS[f];
                }
                totalSumC[f] = '\0';
                send(client_socket, totalSumC, sizeof(totalSumC), 0);
            }
        }
    }

    exit(server_socket);
    return 0;
}
