#include "headerfiles.h"
#include <stdio.h>

int main(){
	int ls;
	int s;
	char buffer[25+1];
	char * ptr = buffer;
	int len = 0;
	int maxlen = sizeof(buffer);

	int receive_n = 0;

	int waitSize = 16;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	int clientAddrlen;

	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;//?
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(SERVER_PORT);
	if((ls = socket(PF_INET,SOCK_STREAM,0))<0){
		perror("Error: Listen socket failed!");
		exit(0);
	}

	if(bind(ls,&serverAddr,sizeof(serverAddr))<0){
		perror("Error: binding failed!");
		exit(0);
	}

	if(listen(ls,waitSize)<0){
		perror("Error: Listening failed!");
		exit(0);
	}

	for(;;){
		//printf("1\n");
		fflush(stdout);
		if((s = accept(ls,&clientAddr,&clientAddrlen))<0){
			perror("Error: accept failed!");
			exit(1);
		}

		printf("2\n");
		fflush(stdout);
		// printf("here\n");
		while((receive_n=recv(s,ptr,maxlen,0))>0){
			ptr += receive_n;
			maxlen -= receive_n;
			len += receive_n;

			printf("2.5\n");
		}

		printf("3\n");
		printf("%s",buffer);
		fflush(stdout);
		send(s,buffer,len,0);
		close(s);
	}
}