#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int square(int);

int main()
{
    char buff[100];
    int sockfd, num, status, client_sockfd;
    struct sockaddr_in server;
    socklen_t len;

    //create the TCP socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

        //check socket creation status.
    if(sockfd == -1)
    {
        printf("\nSocket Creation Failed\n");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = 7000;
    server.sin_addr.s_addr = INADDR_ANY;

    // bind the server config to the socket.
    // to define the socket.
    len = sizeof(server);
    status = bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    // check the bind status.
    if (status == -1)
    {
        printf("\nBind Failed\n");
        close(sockfd);
        return -1;
    }

    // listen for client connections.
    status = listen(sockfd, 10);

    // check the listen status.
    if (status == -1)
    {
        printf("\nListen Failed\n");
        close(sockfd);
        return -1;
    }

    // accept the connection from the client when they execure the connect sys call.
    client_sockfd = accept(sockfd, (struct sockaddr *)&server, &len);

    // check the accept status.
    if (client_sockfd == -1)
    {
        printf("\nClient Accept Failed\n");
        close(sockfd);
        return -1;
    }

    while(1)
    {
        //receive from client
        status = recv(client_sockfd, buff, 100, 0);
        //check the status of the recv
        if(status == -1)
        {
            printf("\nReceive Failed\n");
            break;
        }
        else if(status == 0)
        {
            printf("\nClient disconnected\n");
            break;
        }
        
        //convert the string to integer.
        sscanf(buff, "%d", &num);

        //calculate the square.
        num = square(num);
        
        //clear the buffer.
        bzero(buff, sizeof(buff));

        //convert the num to string.
        sprintf(buff, "%d", num);

        //send to the client.
        status = send(client_sockfd, buff, strlen(buff), 0);

        //check the send status.
        if(status == -1)
        {
            printf("\nSend Failed\n");
            break;
        }
        
        printf("\nResult : %s\n", buff);
    }
    
    // Clean up
    close(client_sockfd);
    close(sockfd);
    return 0;
}

int square(int num)
{
    return num*num;
}