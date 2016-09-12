#include <stdio.h>
#include <stdlib.h>

// 函数指针作为参数传递的与应用示例
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
	//传入的函数指针判断，防止出错
	if(callback) {
		return callback(a, b);
	} else {
		*error = "参数必须是函数指针。";
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