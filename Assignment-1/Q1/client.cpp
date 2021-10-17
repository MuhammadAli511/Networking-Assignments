#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main()
{
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(3001);
    connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

    string student_Department;
    string student_Name;
    string student_Rollno;
    string student_Order;
    int table_Number;
    int input_Validation[8];

tryAgain:
    cout << "Enter your department : ";
    getline(cin, student_Department);

    for (int i = 0; i < 8; i++)
    {
        input_Validation[i] = 1;
    }
    input_Validation[0] = student_Department.compare("CS");
    input_Validation[1] = student_Department.compare("AI");
    input_Validation[2] = student_Department.compare("DS");
    input_Validation[3] = student_Department.compare("SE");
    input_Validation[4] = student_Department.compare("cs");
    input_Validation[5] = student_Department.compare("se");
    input_Validation[6] = student_Department.compare("ai");
    input_Validation[7] = student_Department.compare("ds");
    for (int i = 0; i < 8; i++)
    {
        if (input_Validation[i] == 0)
        {
            goto passed;
        }
    }
    goto tryAgain;
passed:

    cout << "Enter your name : ";
    getline(cin, student_Name);

    cout << "Enter your Roll Number : ";
    getline(cin, student_Rollno);

    cout << "Enter your Order : ";
    getline(cin, student_Order);

    cout << "Enter your Table Number : ";
    cin >> table_Number;

    cout << "Department : " << student_Department << endl;
    cout << "Name : " << student_Name << endl;
    cout << "Roll Number : " << student_Rollno << endl;
    cout << "Order : " << student_Order << endl;
    cout << "Table Number " << table_Number << endl;

    string final_String = "Order By: ";

    final_String += student_Department;
    final_String += "-";
    final_String += student_Name;
    final_String += "-";
    final_String += student_Rollno;
    final_String += "-";
    final_String += to_string(table_Number);
    final_String += "\n";
    final_String += "Order Item: ";
    for (int i = 0; i < student_Order.length(); i++)
    {
        if (student_Order[i] == ',')
        {
            student_Order[i] = '-';
        }
    }
    final_String += student_Order;

    char sending_String[final_String.length() + 1];
    int m = 0;
    for (; m < final_String.length(); m++)
    {
        sending_String[m] = final_String[m];
    }
    sending_String[m] = '\n';
    send(sock, sending_String, sizeof(sending_String), 0);
    char recieve_String[1000];
    recv(sock, &recieve_String, sizeof(recieve_String), 0);
    cout << recieve_String << endl ;
    exit(sock);
}
