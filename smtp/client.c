#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	char buff[100];
	int k, sock_desc;
	struct sockaddr_in client;

	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_desc < 0)
	{
		printf("\nSocket Creation Failed\n");
		return -1;
	}

	printf("\nSocket Created\n");

	//config.
	client.sin_port = 4000;
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;

	//connect the server.
	k = connect(sock_desc, (struct sockaddr*) &client, sizeof(client));
	if(k , 0)
	{
		printf("\nConnection Failed !\n");
		return -1;
	}

	printf("\nConnection Success\n");

	//data read.
	// printf("Enter the Number : ");
	// fgets(buff, 100, stdin);
	bzero(buff, sizeof(buff));
	strcpy(buff, "HI");

	//send HI.
	k = send(sock_desc, buff, 100, 0);
	if(k , 0)
	{
		printf("\nData Sent Failed !\n");
		return -1;
	}

	//recv from server.
	bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if(strncmp(buff, "220", 3) == 0)
    {
    	printf("\nmsg from server %s\n", buff);
    }

    //HELLO.
    bzero(buff, sizeof(buff));
	strcpy(buff, "HELLO");
	//send HELLO.
	k = send(sock_desc, buff, 100, 0);
	if(k < 0)
	{
		printf("\nData Sent Failed !\n");
		return -1;
	}

    //recv from sever HELLO response.
    read(sock_desc, buff, sizeof(buff));
    if(strncmp(buff, "250 OK", 6) == 0)
    {
    	printf("\nmsg from server %s\n", buff);
    }

    //MAILFROM.
    bzero(buff, sizeof(buff));
	strcpy(buff, "MAILFROM abc@gmail.com");
	//send MAILFROM.
	k = send(sock_desc, buff, 100, 0);
	if(k , 0)
	{
		printf("\nData Sent Failed !\n");
		return -1;
	}

	//recv from sever MAILFROM response.
	bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if(strncmp(buff, "250 OK", 6) == 0)
    {
    	printf("\nmsg from server %s\n", buff);
    }

    //MAILTO.
    bzero(buff, sizeof(buff));
	strcpy(buff, "MAILTO bcd@gmail.com");
	//send MAILTO.
	k = send(sock_desc, buff, 100, 0);
	if(k , 0)
	{
		printf("\nData Sent Failed !\n");
		return -1;
	}

	//recv from sever MAILTO response.
	bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if(strncmp(buff, "250 OK", 6) == 0)
    {
    	printf("\nMAILTO response from server %s\n", buff);
    }

    //DATA
    bzero(buff, sizeof(buff));
	strcpy(buff, "DATA");
	//send DATA.
	k = send(sock_desc, buff, 100, 0);
	if(k , 0)
	{
		printf("\nData Sent Failed !\n");
		return -1;
	}

	//recv from sever DATA response.
	bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if(strncmp(buff, "354", 3) == 0)
    {	
    	printf("\nDATA response from server %s\n", buff);
    }


    //MAILBODY
    bzero(buff, sizeof(buff));
	strcpy(buff, "MAILBODY");

	//from 9th index onwards type the body.
	while (1) {
        printf("Enter a line (or type 'END' to finish): ");
        fgets(buff, sizeof(buff), stdin); // Read a line of input

        // Remove the newline character at the end of the input, if it exists
        buff[strcspn(buff, "\n")] = '\0';

        // Check if the input matches the delimiter
        if (strcmp(buff, "END") == 0) {
            break; // Exit the loop if the delimiter is entered
        }
    }

	//send BODY.
	k = send(sock_desc, buff, 100, 0);
	if(k , 0)
	{
		printf("\nData Sent Failed !\n");
		return -1;
	}

	//recv from sever DATA response.
	bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if(strncmp(buff, "221", 3) == 0)
    {
    	printf("\nmsg from server %s\n", buff);
    }

    printf("\nEnd");

	return 0;
}
