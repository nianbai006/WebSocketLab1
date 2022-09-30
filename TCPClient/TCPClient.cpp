//////////////////////////////////////////////////////////
// TCPClient.cpp�ļ�

#include "../common/InitSock.h"
#include <stdio.h>
CInitSock initSock; // ��ʼ��Winsock��

int main()
{
    // �����׽���
    SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        printf(" Failed socket() \n");
        return 0;
    }

    // Ҳ�������������bind������һ�����ص�ַ
    // ����ϵͳ�����Զ�����

    // ��дԶ�̵�ַ��Ϣ
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(4567);
    // ע�⣬����Ҫ��д����������TCPServer�������ڻ�����IP��ַ
    // �����ļ����û��������ֱ��ʹ��127.0.0.1����
    servAddr.sin_addr.S_un.S_addr = inet_addr("10.223.143.24");

    if (::connect(s, (sockaddr *)&servAddr, sizeof(servAddr)) == -1)
    {
        printf(" Failed connect() \n");
        return 0;
    }

    // Ben: ��������
    char szText[] = " I am a TCP Client! \r\n";
    // ��������˷�������
    ::send(s, szText, strlen(szText), 0);

    // ��������
    char buff[256];
    int nRecv = ::recv(s, buff, 256, 0);
    if (nRecv > 0)
    {
        buff[nRecv] = '\0';
        printf("receive %s", buff);
    }

    // �ر��׽���
    ::closesocket(s);
    return 0;
}
