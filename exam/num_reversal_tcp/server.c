//socket creation
//socket config
//socket bind
//socket listen
//socket accept
//read, write
//close.

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int reverse(int);

int main()
{
    char buff[100];
    int sockfd, status, num, client_sockfd;
    socklen_t len;
    struct sockaddr_in server;

    //create the socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //check the socket creation status.
    if(sockfd == -1)
    {
        printf("\nSocket Creation Failed\n");
        return -1;
    }

    //configure the server.
    server.sin_family = AF_INET; //Ipv4 family.
    server.sin_addr.s_addr = INADDR_ANY;// to assign the current machine ip by default.
    server.sin_port = 4000; // port where it will be running.

    //bind the server config to the socket.
    //to define the socket.
    len = sizeof(server);
    status = bind(sockfd, (struct sockaddr *) &server, sizeof(server));

    //check the bind status.
    if(status == -1)
        printf("\nBind Failed\n");
    
    //listen for client connections.
    status = listen(sockfd, 10);

    //check the listen status.
    if(status == -1)
        printf("\nListen Failed\n");
    
    //accept the connection from the client when they execure the connect sys call.
    client_sockfd = accept(sockfd, (struct sockaddr *) &server, &len);

    //check the accept status.
    if(client_sockfd == -1)
        printf("\nClient Accept Failed\n");
    
    //read from the client.
    while(1)
    {
        status = recv(client_sockfd, buff, 100, 0);
        if(status == -1)
            printf("\nRecv Failed\n");

        printf("Data Received : %s", buff);

        //convert the string to integer.
        sscanf(buff , "%d", &num);

        //perform the factorial operation.
        int ans = reverse(num);

        //send the ans to the client.
        bzero(buff, sizeof(buff));
        sprintf(buff, "%d", ans);
        
        status = send(client_sockfd, buff, 100, 0);
        if (status == -1)
        {
            printf("\nSend Failed\n");
        }
        
    }

    close(client_sockfd);
    close(sockfd);

    return 0;
}

int reverse(int num)
{
    int rev = 0, digit = 0;
    while(num != 0)
    {
        digit = num % 10;
        rev = (rev * 10) + digit;
        num = num / 10;
    }

    return rev;
}