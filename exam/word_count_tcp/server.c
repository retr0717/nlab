#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int word_count(char str[]);

int main()
{
    char buff[100];
    int sockfd, num, status, client_sockfd;
    struct sockaddr_in server;
    socklen_t len;

    // create the UDP socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // check socket creation status.
    if (sockfd == -1)
    {
        printf("\nSocket Creation Failed\n");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = 6000;
    server.sin_addr.s_addr = INADDR_ANY;

    // bind the server config to the socket.
    // to define the socket.
    len = sizeof(server);
    status = bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    // check the bind status.
    if (status == -1)
        printf("\nBind Failed\n");

    // listen for client connections.
    status = listen(sockfd, 10);

    // check the listen status.
    if (status == -1)
        printf("\nListen Failed\n");

    // accept the connection from the client when they execure the connect sys call.
    client_sockfd = accept(sockfd, (struct sockaddr *)&server, &len);

    // check the accept status.
    if (client_sockfd == -1)
        printf("\nClient Accept Failed\n");

    // receive from client
    len = sizeof(server);
    status = recv(client_sockfd, buff, 100, 0);
    // check the status of the recv
    if (status == -1)
        printf("\nReceive Failed\n");

    printf("\nString recv : %s\n", buff);

    // calculate the word count.
    num = word_count(buff);

    // clear the buffer.
    bzero(buff, sizeof(buff));

    // conver the num to string.
    sprintf(buff, "%d", num);

    // send to the server.
    status = send(client_sockfd, buff, 100, 0);

    // check the send status.
    if (status == -1)
        printf("\nSend Failed\n");

    printf("\nResult : %s\n", buff);

    return 0;
}

int word_count(char str[])
{
    int ans = 0, line_count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ' && str[i + 1] != ' ')
            ans++;
        else if (str[i] == '\n')
            line_count++;
    }

    printf("\nLine Count : %d\n Word Count : %d\n", line_count, ans);

    return ans;
}