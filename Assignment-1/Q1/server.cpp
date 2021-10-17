#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
    int serial_No[4] = {0};
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
    while (client_Count != 5)
    {
        client_socket = accept(server_socket, NULL, NULL);
        char recieve_String[1000];
        recv(client_socket, &recieve_String, sizeof(recieve_String), 0);
        time_t current_Time_Details = time(0);
        tm *pointer_Time = localtime(&current_Time_Details);
        string final_String;
        final_String += "Order Noted: ";
        string month = to_string(pointer_Time->tm_mon+1);
        string day = to_string(pointer_Time->tm_mday);
        string year = to_string(pointer_Time->tm_year + 1900);
        string hour = to_string(pointer_Time->tm_hour);
        string min = to_string(pointer_Time->tm_min);
        string sec = to_string(pointer_Time->tm_sec);
        final_String += month;
        final_String += "/";
        final_String += day;
        final_String += "/";
        final_String += year;
        final_String += "\t";
        final_String += hour;
        final_String += ":";
        final_String += min;
        final_String += ":";
        final_String += sec;
        final_String += "\n";
        final_String += "Serving Time: ";
        final_String += to_string(pointer_Time->tm_mon+1);
        final_String += "/";
        final_String += to_string(pointer_Time->tm_mday);
        final_String += "/";
        final_String += to_string(pointer_Time->tm_year + 1900);
        final_String += "\t";
        final_String += to_string(pointer_Time->tm_hour);
        final_String += ":";
        final_String += to_string(pointer_Time->tm_min + 15);
        final_String += ":";
        final_String += to_string(pointer_Time->tm_sec);
        char sending_String[final_String.length() + 1];
        int k = 0;
        for ( ; k < final_String.length() ; k++)
        {
            sending_String[k] = final_String[k];
        }
        sending_String[k] = '\0';
        send(client_socket, sending_String, sizeof(sending_String), 0);
        client_Count++;
        // Word Separation
        int space_Count = 0;
        int dash_Count = 0;
        string department;
        string name;
        string order;
        bool next_Line = false;
        for (int i = 0 ; i < strlen(recieve_String) ; i++)
        {
            if (recieve_String[i] == ' ')
            {
                space_Count++;
            }
            if (recieve_String[i] == '-')
            {
                dash_Count++;
            }
            if (space_Count == 2 && dash_Count == 0 && next_Line == false)
            {
                if (recieve_String[i] != ' ')
                {
                    department += recieve_String[i];
                }
            }
            if (dash_Count == 1)
            {
                if (recieve_String[i] != '-')
                {
                    name += recieve_String[i];
                }
            }
            if (recieve_String[i] == '\n')
            {
                next_Line = true;
                space_Count = 0;
            }
            if (space_Count >= 2 && next_Line == true)
            {
                order += recieve_String[i];
            }
        }
        ifstream write_File;
        if (department == "CS" || department == "cs")
        {
            serial_No[0]++;
            write_File.open("CS.txt");
            if (write_File)
            {
                ofstream write_File2("CS.txt",ios::app);
                string final_Date;
                final_Date += month;
                final_Date += "/";
                final_Date += day;
                final_Date += "/";
                final_Date += year;
                string final_Time;
                final_Date += hour;
                final_Date += ":";
                final_Date += min;
                final_Date += ":";
                final_Date += sec;
                write_File2 << to_string(serial_No[0]) << "\t" << department << "\t" << final_Date << "\t" << final_Time << "\t" << name << "\t" << order << endl;
            }
            else
            {
                ofstream write_File2("CS.txt");
                write_File2 << "Serial No\tDepartment\tDate\tTime\tName\tOrder" << endl ;
                string final_Date;
                final_Date += month;
                final_Date += "/";
                final_Date += day;
                final_Date += "/";
                final_Date += year;
                string final_Time;
                final_Date += hour;
                final_Date += ":";
                final_Date += min;
                final_Date += ":";
                final_Date += sec;
                write_File2 << to_string(serial_No[0]) << "\t" << department << "\t" << final_Date << "\t" << final_Time << "\t" << name << "\t" << order << endl;
            }
        }
        if (department == "SE" || department == "se")
        {
            serial_No[1]++;
            write_File.open("SE.txt");
            if (write_File)
            {
                ofstream write_File2("SE.txt",ios::app);
                string final_Date;
                final_Date += month;
                final_Date += "/";
                final_Date += day;
                final_Date += "/";
                final_Date += year;
                string final_Time;
                final_Date += hour;
                final_Date += ":";
                final_Date += min;
                final_Date += ":";
                final_Date += sec;
                write_File2 << to_string(serial_No[1]) << "\t" << department << "\t" << final_Date << "\t" << final_Time << "\t" << name << "\t" << order << endl;
            }
            else
            {
                ofstream write_File2("SE.txt");
                write_File2 << "Serial No\tDepartment\tDate\tTime\tName\tOrder" << endl ;
                string final_Date;
                final_Date += month;
                final_Date += "/";
                final_Date += day;
                final_Date += "/";
                final_Date += year;
                string final_Time;
                final_Date += hour;
                final_Date += ":";
                final_Date += min;
                final_Date += ":";
                final_Date += sec;
                write_File2 << to_string(serial_No[1]) << "\t" << department << "\t" << final_Date << "\t" << final_Time << "\t" << name << "\t" << order << endl;
            }
        }
        if (department == "dS" || department == "ds")
        {
            serial_No[2]++;
            cout << "Hello WOrld" << endl ;
            write_File.open("DS.txt");
            if (write_File)
            {
                ofstream write_File2("DS.txt",ios::app);
                string final_Date;
                final_Date += month;
                final_Date += "/";
                final_Date += day;
                final_Date += "/";
                final_Date += year;
                string final_Time;
                final_Date += hour;
                final_Date += ":";
                final_Date += min;
                final_Date += ":";
                final_Date += sec;
                write_File2 << to_string(serial_No[2]) << "\t" << department << "\t" << final_Date << "\t" << final_Time << "\t" << name << "\t" << order << endl;
            }
            else
            {
                ofstream write_File2("DS.txt");
                write_File2 << "Serial No\tDepartment\tDate\tTime\tName\tOrder" << endl ;
                string final_Date;
                final_Date += month;
                final_Date += "/";
                final_Date += day;
                final_Date += "/";
                final_Date += year;
                string final_Time;
                final_Date += hour;
                final_Date += ":";
                final_Date += min;
                final_Date += ":";
                final_Date += sec;
                write_File2 << to_string(serial_No[2]) << "\t" << department << "\t" << final_Date << "\t" << final_Time << "\t" << name << "\t" << order << endl;
            }
        }
        if (department == "AI" || department == "ai")
        {
            serial_No[3]++;
            write_File.open("AI.txt");
            if (write_File)
            {
                ofstream write_File2("AI.txt",ios::app);
                string final_Date;
                final_Date += month;
                final_Date += "/";
                final_Date += day;
                final_Date += "/";
                final_Date += year;
                string final_Time;
                final_Date += hour;
                final_Date += ":";
                final_Date += min;
                final_Date += ":";
                final_Date += sec;
                write_File2 << to_string(serial_No[3]) << "\t" << department << "\t" << final_Date << "\t" << final_Time << "\t" << name << "\t" << order << endl;
            }
            else
            {
                ofstream write_File2("AI.txt");
                write_File2 << "Serial No\tDepartment\tDate\tTime\tName\tOrder" << endl ;
                string final_Date;
                final_Date += month;
                final_Date += "/";
                final_Date += day;
                final_Date += "/";
                final_Date += year;
                string final_Time;
                final_Date += hour;
                final_Date += ":";
                final_Date += min;
                final_Date += ":";
                final_Date += sec;
                write_File2 << to_string(serial_No[3]) << "\t" << department << "\t" << final_Date << "\t" << final_Time << "\t" << name << "\t" << order << endl;
            }
        }
        
        

    }
    exit(client_socket);
}