#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

/*
	WinSocket 客户端简单通信示例
	关键使用到的函数。
	1.WSAStartup()	- 指明socket版本
	2.socket()		- 创建客户端socket对象
	3.connect()		- 连接服务器，需要提供服务器的相关信息（SOCKADDR_IN结构体）
	4.recv()		- 接收服务器消息
	7.sand()		- 向服务器发送消息
	8.closesocket() - 断开客户端连接，销毁客户端socket对象
	WSACleanup()	  关闭 WSAStartup()
*/

// 使用 ws2_32.dll 网络相关的动态库
#pragma comment(lib, "ws2_32.lib")

// 服务器IP，端口
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

	// 1.调用WinSocket前指明socket版本
	wVersionRequestd = MAKEWORD(2,2);
	ret = WSAStartup(wVersionRequestd, &wsaData);
	if(ret != 0) {
		puts("WSAStartup() failed!");
		return -1;
	}
	
	// 2.创建客户端Socket对象
	socketClient = socket(AF_INET, SOCK_STREAM, 0);

	// 3.配置服务器端的连接信息
	addrSrv.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(SERVER_PORT);

	// 4.连接服务器
	ret = connect(socketClient, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	if(ret != 0) {
		puts("Server connection failed !");
		return -1;
	}
	
	//////////////////////////// Socket 准备完毕，接下来就是发送和接收消息 ////////////////////////

	// 5.1 接收服务器发送来的消息
	recv(socketClient, recvBuf, sizeof(recvBuf), 0);
	printf("Server message: %s\n", recvBuf);
	
	// 5.2 向服务器发送消息
	fgets(sandBuf, sizeof(sandBuf), stdin);
	sandBuf[strlen(sandBuf) - 1] = 0;

	send(socketClient, sandBuf, strlen(sandBuf) + 1, 0);

	// 6.断开服务器连接，清除socket独享
	closesocket(socketClient);
	WSACleanup();
	
	system("pause");
	return 0;
}