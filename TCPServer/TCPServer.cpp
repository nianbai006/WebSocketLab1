//////////////////////////////////////////////////
// TCPServer.cpp�ļ�


#include "../common/InitSock.h"
#include <stdio.h>
CInitSock initSock;		// ��ʼ��Winsock��

int main()
{
	// �����׽���
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sListen == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		return 0;
	}
	
	// ���sockaddr_in�ṹ
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4567);
	sin.sin_addr.S_un.S_addr = inet_addr("10.223.143.24");

	// ������׽��ֵ�һ�����ص�ַ
	if(::bind(sListen, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Failed bind() \n");
		return 0;
	}
	
	// �������ģʽ
	if(::listen(sListen, 2) == SOCKET_ERROR)
	{
		printf("Failed listen() \n");
		return 0;
	}
	
	// ѭ�����ܿͻ�����������
	sockaddr_in remoteAddr; 
	int nAddrLen = sizeof(remoteAddr);
	SOCKET sClient;
	char szText[] = " TCP Server Demo! \r\n";
	while(TRUE)
	{
		// ����һ��������
		sClient = ::accept(sListen, (SOCKADDR*)&remoteAddr, &nAddrLen);
		if(sClient == INVALID_SOCKET)
		{
			printf("Failed accept()");
			continue;
		}
		
		printf(" receive%s \r\n", inet_ntoa(remoteAddr.sin_addr));

		// ��ͻ��˷�������
		::send(sClient, szText, strlen(szText), 0);
		// �ر�ͬ�ͻ��˵�����
		::closesocket(sClient);
	}
		
	// �رռ����׽���
	::closesocket(sListen);
    system("pause");
	return 0;
}