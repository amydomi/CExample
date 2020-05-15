#include <stdio.h>
#include <stdlib.h>

#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

//
// DNS����
// ͨ��������ѯIP��ַ (���ص�һ��IP��ַ)
//
// hostName ����
// ipBuffer Ip��ַ (������Ϊ16���ֽ�)
// ��ѯ�ɹ�����Ip��ַ���뻺������������TRUE�����򷵻�FALSE
//
BOOL GetFirstIpByDomain(const char *domain, char * ipBuffer)
{
	int WSA_return;
	WSADATA WSAData;

	WSA_return = WSAStartup(0x0202, &WSAData);

	addrinfo hints, *res;
	in_addr addr;

	if (WSA_return == 0)
	{
		memset(&hints, 0, sizeof(addrinfo));
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_family = AF_INET;

		if (getaddrinfo(domain, NULL, &hints, &res) != 0) {
			return FALSE;
		}
		memset(ipBuffer, 0, 16);
		addr.s_addr = ((sockaddr_in*)(res->ai_addr))->sin_addr.s_addr;
		if (InetNtopA(AF_INET, &addr, ipBuffer, 16) == NULL)
		{
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

//
// DNS����
// ͨ��������ѯIP��ַ (���ض�IP)
//
// hostName ����
// ipBuffer ���Ip��ַ (������Ϊ16���ֽ�)
// ���ز�ѯ��IP����
//
int GetAllIpByDomain(const char *domain, char ipBuffer[][16])
{
	int WSA_return;
	WSADATA WSAData;

	WSA_return = WSAStartup(0x0202, &WSAData);

	addrinfo hints, *result, *ptr;
	in_addr addr;
	int ipNumber = 0;

	if (WSA_return == 0)
	{
		memset(&hints, 0, sizeof(addrinfo));
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_family = AF_INET;

		if (getaddrinfo(domain, NULL, &hints, &result) != 0) {
			return ipNumber;
		}
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next, ipNumber++) {
			addr = ((sockaddr_in*)(ptr->ai_addr))->sin_addr;
			memset(ipBuffer[ipNumber], 0, 16);
			InetNtopA(AF_INET, &addr, ipBuffer[ipNumber], 16);
		}
	}
	return ipNumber;
}

int main()
{
	while (true)
	{
		char domain[150];
		char ipAddress[13][16]; // ���13��IP

		memset(&ipAddress, 0, sizeof(ipAddress));

		puts("������Ҫ����������");
		scanf_s("%s", domain, 150);

		if (strcmp("exit", domain) == 0) break;

		int num = GetAllIpByDomain(domain, ipAddress);

		if (num > 0) {
			for (int i = 0; i < num; i++) {
				printf("%s\n", ipAddress[i]);
			}
		} else {
			puts("DNS����ʧ�ܣ�������Ч��δ������");
		}

		puts("-------------------------------");
	}
	system("pause");
	return 0;
}