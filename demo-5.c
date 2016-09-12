#include <stdio.h>
#include <stdlib.h>

// ����ָ����Ϊ�������ݵ���Ӧ��ʾ��
int calculate(int, int, int (* callback)(int, int), const char **error);

int sub(int, int);
int add(int, int);

int main(int argc, char **argv)
{
	int a = 50, b = 20;
	int result;
	char *error = 0;
	
	result = calculate(a, b, add, &error);
	if(error == 0) {
		printf("%d + %d = %d\n", a, b, result);
	} else {
		puts(error);
	}
	
	result = calculate(a, b, sub, &error);
	if(error == 0) {
		printf("%d - %d = %d\n", a, b, result);
	} else {
		puts(error);
	}

	result = calculate(a, b, NULL, &error);
	if(error == 0) {
		printf("%d - %d = %d\n", a, b, result);
	} else {
		puts(error);
	}

	system("pause");
	return 0;
}

int calculate(int a, int b, int (* callback)(int, int), const char **error)
{
	//����ĺ���ָ���жϣ���ֹ����
	if(callback) {
		return callback(a, b);
	} else {
		*error = "���������Ǻ���ָ�롣";
		return 0;
	}
}

int sub(int a, int b)
{
	return a - b;
}
int add(int a, int b)
{
	return a + b;
}