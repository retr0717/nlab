#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	char buff[100];
	socklen_t len;
	int k , sock_desc, temp_sock_desc;
	struct sockaddr_in server, client;

	//creating socket.
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	//check the status of creation.
	if(sock_desc < 0)
	{
		printf("\nSocket Creation Failed!\n");
		return -1;
	}

	printf("\nSocket Creation Success!\n");

	//configure the server socket.
	server.sin_family = AF_INET; //ipv4 
	server.sin_port = 4000; //port
	server.sin_addr.s_addr = INADDR_ANY; //ip of this machine.


	//configure client socket.
	client.sin_family = AF_INET; //ipv4.
	client.sin_port = 4000; //port.
	client.sin_addr.s_addr = INADDR_ANY; //ip of the machine.

	//bind the socket and the server(config).
	k = bind(sock_desc, (struct sockaddr *) &server, sizeof(server));
	if(k < 0)
	{
		printf("\nSocket Bind Failed !\n");
		return -1;
	}

	printf("\nSocket Bind Success\n");

	//listen for connections.
	k = listen(sock_desc, 5);
	if(k < 0)
	{
		printf("\nListening For Connections Failed !\n");
		return -1;
	}

	printf("\nListening for connections\n");

	//accepting client connections.
	len = sizeof(client);
	temp_sock_desc = accept(sock_desc, (struct sockaddr*) &client, &len);
	if(temp_sock_desc < 0)
	{
		printf("\nAccept Connetion Failed !\n");
		return -1;
	}

	printf("\nStarted Accepting Connections\n");

	//recv data from the client.
	k = recv(temp_sock_desc, buff, 100, 0);
	if( k < 0)
	{
		printf("\nData Recv Failed !\n");
		return -1;
	}

	//recv HI
	printf("msg from client : %s", buff);
	//clear buffer.
	buff[0] = '\0';
	// and send that buffer to client
	strcpy(buff, "220");//220 plus ip. 
    write(temp_sock_desc, buff, sizeof(buff));

    //recv HELLO
    k = recv(temp_sock_desc, buff, 100, 0);
	if( k < 0)
	{
		printf("\nData Recv Failed !\n");
		return -1;
	}

	printf("\nmsg from client : %s", buff);
	//clear buffer.
	buff[0] = '\0';
	// and send that buffer to client
	strcpy(buff, "250 OK");//220 plus ip. 
    write(temp_sock_desc, buff, sizeof(buff));


    //recv MAILFROM
    k = recv(temp_sock_desc, buff, 100, 0);
	if( k < 0)
	{
		printf("\nData Recv Failed !\n");
		return -1;
	}

	printf("\nmsg from client : %s", buff);
	//clear buffer.
	buff[0] = '\0';
	// and send that buffer to client
	strcpy(buff, "250 OK"); 
    write(temp_sock_desc, buff, sizeof(buff));

    //recv MAILTO
    k = recv(temp_sock_desc, buff, 100, 0);
	if( k < 0)
	{
		printf("\nData Recv Failed !\n");
		return -1;
	}

	printf("\nmsg from client : %s", buff);
	//clear buffer.
	buff[0] = '\0';
	// and send that buffer to client
	strcpy(buff, "250 OK"); 
    write(temp_sock_desc, buff, sizeof(buff));

    //recv DATA
    buff[0] = '\0';
    k = recv(temp_sock_desc, buff, 100, 0);
	if( k < 0)
	{
		printf("\nData Recv Failed !\n");
		return -1;
	}
	
	printf("\nmsg from client : %s", buff);
	//clear buffer.
	buff[0] = '\0';
	// and send that buffer to client
	strcpy(buff, "354"); 
    write(temp_sock_desc, buff, sizeof(buff));

    //MAILBODY
    buff[0] = '\0';
    k = recv(temp_sock_desc, buff, 100, 0);
	if( k < 0)
	{
		printf("\nData Recv Failed !\n");
		return -1;
	}

	if(strncmp(buff, "MAILBODY", 8) == 0)
		printf("\nmsg from client : %s", buff);

	//clear buffer.
	buff[0] = '\0';
	// and send that buffer to client
	strcpy(buff, "221"); 
    write(temp_sock_desc, buff, sizeof(buff));

	close(temp_sock_desc);
	close(sock_desc);

	return 0;
}
