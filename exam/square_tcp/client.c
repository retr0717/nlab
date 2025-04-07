#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    char buff[100];
    socklen_t len;
    struct sockaddr_in client;
    int sockfd, status, num;

    //create socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //socket creation status check.
    if(sockfd == -1)
        printf("\nSocket Creation Failed\n");
    
    //configure the client socket with server config for the connection.
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = 7000;

    //connect the server.
    len = sizeof(client);
    status = connect(sockfd, (struct sockaddr *) &client, sizeof(client));

    //check connect status.
    if(status == -1)
    {
        printf("\nConnection Failed\n");
        return -1;
    }
    
    num = 0;
    while(1)
    {
        printf("Enter The Input : ");
        scanf("%d", &num);

        //convert the integer to the network compataible format.
        sprintf(buff, "%d", num);

        //send to the server.
        status = send(sockfd, buff, strlen(buff)+1, 0);
        
        //check the send status.
        if(status == -1)
        {
            printf("\nSend Failed\n");
            return -1;
        }

        //receive response from the server.
        bzero(buff, sizeof(buff));
        status = recv(sockfd, buff, 100, 0);

        //check the response status from the server.
        if(status == -1)
            printf("\nResponse Failed To Get\n");
        
        printf("\nFactorial : %s\n", buff);
    }


    close(sockfd);
    return 0;
}