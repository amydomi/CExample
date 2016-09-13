#include <stdio.h>
#include <WinSock2.h>

/*
	WinSocket �������˼�ͨ��ʾ��
	�ؼ�ʹ�õ��ĺ�����
	1.WSAStartup()	- ָ��socket�汾
	2.socket()		- ����������socket����
	3.bind()		- �󶨷�������ַ����Ҫ���÷�������Ϣ���ṹ�壺SOCKADDR_IN��
	4.listen()		- ����socket
	5.accept()		- �����ȴ��ͻ������ӣ����пͻ��������ϴ˷���һ���ͻ���socket����
	6.send()		- ��ͻ��˷�����Ϣ
	7.recv()		- ���տͻ�����Ϣ
	8.closesocket() - �Ͽ��ͻ������ӣ����ٿͻ���socket����

	while ... �����ȴ���һ���ͻ�����������
*/

// ʹ�� ws2_32.dll ������صĶ�̬��
#pragma comment(lib, "ws2_32.lib")

#define TRUE 1
#define FALSE 0

typedef int bool;

#define SERVER_PORT 6001		// �˿�

int main(int argc, char **argv)
{
	WORD wVersionRequestd;
	WSADATA wsaData;

	SOCKET socketSrv, socketClient;
	SOCKADDR_IN addrSrv, addrClient;

	int ret, len;

	char sandBuf[255], recvBuf[255];
	
	// 1.����WinSocketǰָ��socket�汾
	wVersionRequestd = MAKEWORD(2,2);
	ret = WSAStartup(wVersionRequestd, &wsaData);
	if(ret != 0) {
		puts("WSAStartup() failed!");
	}

	// ========��ʼʹ��Socket==============

	// 2.����һ�������Socket����
	socketSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	// 3.ָ������˿ڡ�IP����Ϣ
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_port = htons(SERVER_PORT);

	// 4.��socket�󶨵���Ӧ�ĵ�ַ�˿���
	bind(socketSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));

	// 5.����Socket�仯
	listen(socketSrv, 5); // �ȴ����е���󳤶�Ϊ5
	
	len = sizeof(SOCKADDR);

	while(TRUE) {

		// 6.����һ���׽���ͨ��,(����������) �ȴ��ͻ�������
		socketClient = accept(socketSrv, (SOCKADDR *)&addrClient, &len);

		//////////////////////////// Socket ׼����ϣ����������Ƿ��ͺͽ�����Ϣ ////////////////////////
		
		// ƴ��һ���ַ��������͸��ͻ���
		sprintf_s(sandBuf, sizeof(sandBuf), "Server IP is %s", inet_ntoa(addrClient.sin_addr));
		
		// 7.1 ��ͻ��˷�����Ϣ
		send(socketClient, sandBuf, strlen(sandBuf) + 1, 0);
		
		// 7.2 ���ܿͻ����ύ����������
		recv(socketClient, recvBuf, sizeof(recvBuf), 0);
		printf("Client Message: %s\n", recvBuf);

		// 8. �Ͽ���ͻ��˵�����
		closesocket(socketClient);
	}

	return 0;
}