#include "../common/InitSock.h"
#include <stdio.h>
CInitSock initSock;
int main()
{
    //创建套接字
    SOCKET sClient = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sClient == INVALID_SOCKET)
    {
        printf("socket error");
        return 0;
    }
    //填充地址信息
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4567);
    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //连接服务器
    if (::connect(sClient, (SOCKADDR *)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("connect error");
        return 0;
    }
    //接收数据
    char buff[256];
    int nRecv = ::recv(sClient, buff, 256, 0);
    if (nRecv > 0)
    {
        buff[nRecv] = 0x00;
        printf("recieve%s", buff);
    }
    //关闭套接字
    ::closesocket(sClient);
    return 0;
}
