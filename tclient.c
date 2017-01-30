#include "headerfiles.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int s;
	int n;
	int len=0;

	char * serverName;
	int serverPort;
	char * string;

	char buffer[25+1];
	char *ptr = buffer;
	int maxlen=sizeof(buffer);

	struct sockaddr_in serverAddr;

	if(argc != 4){
		printf("Error: Argument must be 3!");
		return 0;
	}

	serverName = argv[1];
	serverPort = atoi(argv[2]);
	string  = argv[3];

	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET,serverName,&serverAddr.sin_addr);
	serverAddr.sin_port = htons(serverPort);

	if((s = socket(PF_INET,SOCK_STREAM,0))<0){
		perror("Error: socket creation failed!");
		exit(0);
	}
	if(connect(s,(struct sockaddr_in*)&serverAddr,sizeof(serverAddr))<0){
		perror("Error: Connection failed!");
		exit(0);
	}
	printf("%s\n",string);
	send(s,string,strlen(string),0);

	send(s,"At\xff",3,0);
	while((n=recv(s,ptr,maxlen,0))>0){
		ptr += n;
		maxlen -= n;
		len += n;
	}
	buffer[len] = 0;
	printf("Echo string received %s\n", buffer);

	close(s);
	return 0;
}