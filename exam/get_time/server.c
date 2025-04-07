#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>

int fact(int);

int main()
{
    char buff[100];
    int sockfd, num, status;
    struct sockaddr_in server;
    socklen_t len;

    //time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);

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

    //bind the socket.
    status = bind(sockfd, (struct sockaddr *) &server, sizeof(server));

    //check the bind status.
    if(status == -1)
        printf("\nBind Failed\n");

    while(1)
    {
        //receive from client
        len = sizeof(server);
        status = recvfrom(sockfd, buff, 100, 0, (struct sockaddr *) &server, &len);
        //check the status of the recv
        if(status == -1)
            printf("\nReceive Failed\n");

        //check the string.
        if(strncmp(buff, "GET_TIME", 8) == 0)
        {
            bzero(buff, sizeof(buff));
            strcpy(buff, asctime(info));
        }

        //send to the server.
        status = sendto(sockfd, buff, 100, 0, (struct sockaddr *) &server, sizeof(server));

        //check the send status.
        if(status == -1)
            printf("\nSend Failed\n");
        
        printf("\nResult : %s\n", buff);
    }
    
    return 0;
}