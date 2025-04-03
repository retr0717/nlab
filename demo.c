#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>


char buff[100];
FILE *f1;

int main()
{
	int sockfd, csockfd, clength;
	struct sockaddr_in server, client;
	char str[100];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htnol("127.0.0.1");
	server.sin_port = htons("3000");

	int k;
	k = bind(sockfd, (struct sockaddr *) &server, sizeof(server));

	listen(sockfd, 10);

	clength = sizeof(server);
	csockfd = accept(sockfd, (struct sockaddr *) &server, &clength);


	read(csockfd, &str, 100);
	f1 = fopen(str, "r"):
	
	while(fgets(str, 100, f1) != NULL)
	{
		write(csockfd, str, 100);

	}
}
