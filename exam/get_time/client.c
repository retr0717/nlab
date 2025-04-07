#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main()
{
    char buff[100];
    int sockfd, num, status;
    struct sockaddr_in server;
    socklen_t len;

    //create the UDP socket.
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        //check socket creation status.
    if(sockfd == -1)
    {
        printf("\nSocket Creation Failed\n");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = 5000;
    server.sin_addr.s_addr = INADDR_ANY;

    while(1)
    {
        //send get time instruction.
        int opt;
        printf("\n1. get time 2. exit\n");
        printf("Enter the option : ");
        scanf("%d", &opt);

        if(opt == 1)
        {
            strcpy(buff, "GET_TIME");
        }
        else if(opt == 2)
        {
            close(sockfd);
            exit(0);
        }

        //send to the server.
        status = sendto(sockfd, buff, 100, 0, (struct sockaddr *) &server, sizeof(server));

        //check the send status.
        if(status == -1)
            printf("\nSend Failed\n");
        
        //receive the result from the server.
        bzero(buff, sizeof(buff));
        len = sizeof(server);
        status = recvfrom(sockfd, buff, 100, 0, (struct sockaddr *) &server, &len);
        //check the status of the recv
        if(status == -1)
            printf("\nReceive Failed\n");
        
        printf("\nResult : %s\n", buff);
    }

    return 0;
}