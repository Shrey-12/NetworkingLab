#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include <sys/types.h>

#define MAXLINE 200
int main(int argc, char **argv)
{

	int sockfd, n;
	struct sockaddr_in servaddr;
	if(argc !=3){
		printf("no port number supplied");
		return 1;
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("socket error");
		return 1;
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	int port=atoi(argv[2]);
	servaddr.sin_port = htons((uint16_t)port); /* daytime server */

	//Convert IPv4 and IPv6 addresses from text to binary form
	int x;
	x=inet_pton(AF_INET, argv[1],&servaddr.sin_addr);
	if (x< 0){
		printf("inet_pton error for %s",argv[1]);
		return 1;
	}

	if (connect(sockfd, (struct sockaddr *) &servaddr,sizeof(servaddr)) < 0){
		printf("connection errorr");
		return 1;
	}
	char data[MAXLINE];

			read(sockfd,data,sizeof(data));
		printf("%s",data);

	while(1){
		bzero(data, sizeof(data));
		printf("Enter the string : ");
		int n = 0;
        	while ((data[n++] = getchar()) != '\n');
		write(sockfd, data, sizeof(data));
		bzero(data,sizeof(data));
		read(sockfd,data,sizeof(data));
		printf("%s",data);
	}
	exit(0);

}
