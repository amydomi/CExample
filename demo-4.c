#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int boolean;

void execute(char *);

int main(void)
{
	char name[50];
	boolean flag = TRUE;
	
	while(flag) {
		puts("please type the a command:");
		scanf("%s", name);
		// 当输入了exit后退出程序
		if(!strcmp("exit", name)) {
			flag = FALSE;
			system("color 7");
			puts("Bye~!");
		} else {
			execute(name);
		}
	}
	return 0;
}

// 执行一些简单的DOS命令
void execute(char *name)
{
	if(!strcmp("color", name)) {
		system("color A");
	} else if(!strcmp("ls", name)) {
		system("dir");	// 使用ls替换dir命令
	} else if(!strcmp("default", name)) {
		system("color 7");
	} else if(!strcmp("cls", name)) {
		system("cls");
	} else {
		puts("Invalid command");
	}
}