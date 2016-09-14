#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

/*
	������ѯ
	#include <netdb.h>
	
	struct hostent *gethostbyname(const char *name);
	
	�ṹ��������
	struct hostent {
		char  *h_name;            // ����
		char **h_aliases;         // �����Ŀ�ѡ���֣���NULL��Ϊ�������
		int    h_addrtype;
		int    h_length;          // ip��ַ�ĳ��ȣ�ipv4��Ӧ4���ֽ�
		char **h_addr_list;       // һ�����������ж��ip��ַ
#define h_addr  h_addr_list[0]	  // Ϊ���ݾɰ汾���ڵģ�Ĭ����ʾ��һ��IP
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
		// û�гɹ�����Socket���޷�ʹ��WSAGetLastError,ֻ��ʹ�÷���ֵ���������ж�
		printf("WSAStartup failed with error %d \n", ret);
		return -1;
	 }

	 // ----------------- ��ʼʹ�� Socket ----------------------
	 
	 while(flag) {
		 puts("Please type in domain��");
		 fgets(hostName, sizeof(hostName), stdin);
		 hostName[strlen(hostName) - 1] = 0;
		 
		 if(!strcmp("exit", hostName)) {
			 flag = FALSE;
			 break;
		 }
		
		 // ʹ��gethostbyname����һ�������Ľṹ��Ϣ
		 host = gethostbyname(hostName);
		 if(host == NULL) {
			printf("Resolve host failed with error %d \n", h_errno);
		 } else {

			// ����
			printf("Host is %s\n", host->h_name);

			// ��������
			for(i =0; host->h_aliases[i]; i++) {
				printf("IP alias is %s\n", host->h_aliases[i]);
			}

			// Ϊ���ݾɰ汾���ڵģ�Ĭ��ִ�� host->h_addr_list[0]
			// printf("IP address is %s\n", inet_ntoa(*(IN_ADDR *)host->h_addr));

			// �������IP��ַ
			for (i = 0; host->h_addr_list[i]; i++) {
				printf("IP address is %s\n", inet_ntoa(*(IN_ADDR *)host->h_addr_list[i]));
			}
			
			// ip��ַ�ĳ���, ipv4��Ӧ4���ֽ�
			printf("address length: %d bytes\n\n", host->h_length);

		 }
	 }

	 // �������ʼǵõ���WSACleanup
	 if(WSACleanup() != 0) {
		 printf("WSACleanup failed with error %d \n", h_errno);
		 return -1;
	 }

	 return 0;
 }