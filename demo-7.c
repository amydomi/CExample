#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

/*
	域名查询
	#include <netdb.h>
	
	struct hostent *gethostbyname(const char *name);
	
	结构体描述：
	struct hostent {
		char  *h_name;            // 域名
		char **h_aliases;         // 主机的可选名字，以NULL做为结束标记
		int    h_addrtype;
		int    h_length;          // ip地址的长度，ipv4对应4个字节
		char **h_addr_list;       // 一般主机可以有多个ip地址
#define h_addr  h_addr_list[0]	  // 为兼容旧版本存在的，默认显示第一个IP
	}
*/


#pragma comment(lib, "ws2_32.lib")

#define TRUE 1
#define FALSE 0

typedef int bool;

 int main(int argc, char **argv)
 {
	 WSADATA wsaData;

	 int ret, i;
	 struct hostent *host;

	 char hostName[255];
	 bool flag = TRUE;

	 if(ret = WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		// 没有成功加载Socket，无法使用WSAGetLastError,只能使用返回值来做错误判断
		printf("WSAStartup failed with error %d \n", ret);
		return -1;
	 }

	 // ----------------- 开始使用 Socket ----------------------
	 
	 while(flag) {
		 puts("Please type in domain：");
		 fgets(hostName, sizeof(hostName), stdin);
		 hostName[strlen(hostName) - 1] = 0;
		 
		 if(!strcmp("exit", hostName)) {
			 flag = FALSE;
			 break;
		 }
		
		 // 使用gethostbyname返回一个域名的结构信息
		 host = gethostbyname(hostName);
		 if(host == NULL) {
			printf("Resolve host failed with error %d \n", h_errno);
		 } else {

			// 域名
			printf("Host is %s\n", host->h_name);

			// 遍历别名
			for(i =0; host->h_aliases[i]; i++) {
				printf("IP alias is %s\n", host->h_aliases[i]);
			}

			// 为兼容旧版本存在的，默认执行 host->h_addr_list[0]
			// printf("IP address is %s\n", inet_ntoa(*(IN_ADDR *)host->h_addr));

			// 遍历多个IP地址
			for (i = 0; host->h_addr_list[i]; i++) {
				printf("IP address is %s\n", inet_ntoa(*(IN_ADDR *)host->h_addr_list[i]));
			}
			
			// ip地址的长度, ipv4对应4个字节
			printf("address length: %d bytes\n\n", host->h_length);

		 }
	 }

	 // 结束访问记得调用WSACleanup
	 if(WSACleanup() != 0) {
		 printf("WSACleanup failed with error %d \n", h_errno);
		 return -1;
	 }

	 return 0;
 }