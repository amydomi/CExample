#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

/*
	WinSocket �ͻ��˼�ͨ��ʾ��
	�ؼ�ʹ�õ��ĺ�����
	1.WSAStartup()	- ָ��socket�汾
	2.socket()		- �����ͻ���socket����
	3.connect()		- ���ӷ���������Ҫ�ṩ�������������Ϣ��SOCKADDR_IN�ṹ�壩
	4.recv()		- ���շ�������Ϣ
	7.sand()		- �������������Ϣ
	8.closesocket() - �Ͽ��ͻ������ӣ����ٿͻ���socket����
	WSACleanup()	  �ر� WSAStartup()
*/

// ʹ�� ws2_32.dll ������صĶ�̬��
#pragma comment(lib, "ws2_32.lib")

// ������IP���˿�
#define SERVER_IP "192.168.1.111"
#define SERVER_PORT 6001

int main(int argc, char **argv)
{
	WORD wVersionRequestd;
	WSADATA wsaData;

	SOCKADDR_IN addrSrv;
	SOCKET socketClient;

	int ret;

	char sandBuf[255], recvBuf[255];

	// 1.����WinSocketǰָ��socket�汾
	wVersionRequestd = MAKEWORD(2,2);
	ret = WSAStartup(wVersionRequestd, &wsaData);
	if(ret != 0) {
		puts("WSAStartup() failed!");
		return -1;
	}
	
	// 2.�����ͻ���Socket����
	socketClient = socket(AF_INET, SOCK_STREAM, 0);

	// 3.���÷������˵�������Ϣ
	addrSrv.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(SERVER_PORT);

	// 4.���ӷ�����
	ret = connect(socketClient, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	if(ret != 0) {
		puts("Server connection failed !");
		return -1;
	}
	
	//////////////////////////// Socket ׼����ϣ����������Ƿ��ͺͽ�����Ϣ ////////////////////////

	// 5.1 ���շ���������������Ϣ
	recv(socketClient, recvBuf, sizeof(recvBuf), 0);
	printf("Server message: %s\n", recvBuf);
	
	// 5.2 �������������Ϣ
	fgets(sandBuf, sizeof(sandBuf), stdin);
	sandBuf[strlen(sandBuf) - 1] = 0;

	send(socketClient, sandBuf, strlen(sandBuf) + 1, 0);

	// 6.�Ͽ����������ӣ����socket����
	closesocket(socketClient);
	WSACleanup();
	
	system("pause");
	return 0;
}