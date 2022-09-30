#include "./common/InitSock.h"
#include <stdio.h>

int main(){
    //创建套接字
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sListen == INVALID_SOCKET){
        printf("socket error");
        return 0;
    }
    //填充地址信息
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4567);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    //绑定套接字
    if(bind(sListen, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR){
        printf("bind error");
        return 0;
    }
    //开始监听
    if(listen(sListen, 5) == SOCKET_ERROR){
        printf("listen error");
        return 0;
    }
    //接收客户端连接
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    SOCKET sClient；
    char szText[] = "TCP Server Demo!\r\n";
    while (true)
    {
        //接收客户端连接
        sClient = accept(sListen, (SOCKADDR*)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET){
            printf("accept error");
            continue;
        }
        printf("accept client: %s\r\n", inet_ntoa(remoteAddr.sin_addr));
        //发送数据
        send(sClient, szText, strlen(szText), 0);
        //关闭套接字
        closesocket(sClient);

    }
    //关闭监听套接字
    closesocket(sListen);
    // //清除Windows Socket环境
    // WSACleanup();

    return 0;
}