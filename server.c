# include "headerFiles.h"
# include <stdio.h>

int main(void) {
    printf("## Hello Socket!\n## Author: Zachary Ma\n## Date: 2017/1/27\n\n");

    int s; // 套接字描述符
    int len;  // 回送字符串长度
    char buffer[256];   // 数据缓冲区
    struct sockaddr_in servAddr;    // 服务套接字地址
    struct sockaddr_in clntAddr;    // 客户套接字地址
    socklen_t clntAddrLen;        // 客户套接字地址长度

    // 建立服务器套接字地址
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;      // Address Family is not Protocal Family, but this will not go wrong because the value is the same except in BSD.
    servAddr.sin_port = htons(SERVER_PORT); // 端口号
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);   // 默认IP地址，INADDR_ANY就是指定地址为0.0.0.0的地址，意为监听所有
    // 创建套接字
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error: socket failed");
        exit(1);
    }
    // bind
    if ((bind(s,(struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)) {
        perror("Error:bind failed!");
        exit(1);
    }
    // run
    for(;;) {
        clntAddrLen = sizeof(clntAddr); // 垃圾书籍，忘了这一句话！！！2017年01月27日11:01:50 by Zachary.
        len = recvfrom(s, buffer, sizeof(buffer), 0,
            (struct sockaddr*)&clntAddr, &clntAddrLen);
        printf("Connection form %s, port %d \n",inet_ntoa(clntAddr.sin_addr),ntohs(clntAddr.sin_port));
        sendto(s, buffer, len, 0, (struct sockaddr*)&clntAddr, sizeof(clntAddr));
    }
    return 0;
}