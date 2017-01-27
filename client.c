# include "headerFiles.h"
# include <stdio.h>

int main(int argc, char* argv[])
{
    int s;
    int len;
    char* servName;
    int servPort;
    char* string;
    char buffer[256+1];
    struct sockaddr_in servAddr;

    if (argc != 4) {
        printf("Error, three arguments!!");
        exit(1);
    }

    servName = argv[1];
    servPort = atoi(argv[2]);
    string = argv[3];

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    inet_pton(AF_INET, servName, &servAddr.sin_addr);
    servAddr.sin_port = htons(servPort);

    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error! Socket failed.");
        exit(1);
    }

    len = sendto(s, string, strlen(string), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));

    recvfrom(s, buffer, len, 0, NULL, NULL);

    buffer[len] = '\0';
    printf("Echo string received:");
    fputs(buffer, stdout);
    printf("\n");
    close(s);
    exit(0);
}