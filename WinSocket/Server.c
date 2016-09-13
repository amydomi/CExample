#include <stdio.h>
#include <WinSock2.h>

/*
	WinSocket 服务器端简单通信示例
	关键使用到的函数。
	1.WSAStartup()	- 指明socket版本
	2.socket()		- 创建服务器socket对象
	3.bind()		- 绑定服务器地址，需要配置服务器信息（结构体：SOCKADDR_IN）
	4.listen()		- 监听socket
	5.accept()		- 阻塞等待客户端连接（当有客户端连接上此返回一个客户端socket对象）
	6.send()		- 向客户端发送消息
	7.recv()		- 接收客户端消息
	8.closesocket() - 断开客户端连接，销毁客户端socket对象

	while ... 继续等待下一个客户端连接上来
*/

// 使用 ws2_32.dll 网络相关的动态库
#pragma comment(lib, "ws2_32.lib")

#define TRUE 1
#define FALSE 0

typedef int bool;

#define SERVER_PORT 6001		// 端口

int main(int argc, char **argv)
{
	WORD wVersionRequestd;
	WSADATA wsaData;

	SOCKET socketSrv, socketClient;
	SOCKADDR_IN addrSrv, addrClient;

	int ret, len;

	char sandBuf[255], recvBuf[255];
	
	// 1.调用WinSocket前指明socket版本
	wVersionRequestd = MAKEWORD(2,2);
	ret = WSAStartup(wVersionRequestd, &wsaData);
	if(ret != 0) {
		puts("WSAStartup() failed!");
	}

	// ========开始使用Socket==============

	// 2.创建一个服务端Socket对象
	socketSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	// 3.指定服务端口、IP等信息
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_port = htons(SERVER_PORT);

	// 4.将socket绑定到相应的地址端口上
	bind(socketSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));

	// 5.监听Socket变化
	listen(socketSrv, 5); // 等待队列的最大长度为5
	
	len = sizeof(SOCKADDR);

	while(TRUE) {

		// 6.建立一个套接字通信,(阻塞在这里) 等待客户端连接
		socketClient = accept(socketSrv, (SOCKADDR *)&addrClient, &len);

		//////////////////////////// Socket 准备完毕，接下来就是发送和接收消息 ////////////////////////
		
		// 拼接一段字符串，发送给客户端
		sprintf_s(sandBuf, sizeof(sandBuf), "Server IP is %s", inet_ntoa(addrClient.sin_addr));
		
		// 7.1 向客户端发送消息
		send(socketClient, sandBuf, strlen(sandBuf) + 1, 0);
		
		// 7.2 接受客户端提交上来的数据
		recv(socketClient, recvBuf, sizeof(recvBuf), 0);
		printf("Client Message: %s\n", recvBuf);

		// 8. 断开与客户端的连接
		closesocket(socketClient);
	}

	return 0;
}