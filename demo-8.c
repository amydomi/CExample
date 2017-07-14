#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1

void get_line(char *s, int len)
{
	int i;
	char c;
	for(i = 0; (c = getchar()) != '\n' && i < len - 1; ++i) {
		s[i] = c;
	}
	s[i] = '\0'; 
}

int main()
{
	FILE *f1 = NULL, *f2 = NULL;
	char name1[20];
	char name2[20];
	
	char str[20];
	
	while(TRUE) {
		puts("������Դ�ļ�����");
		get_line(name1, 20);
		f1 = fopen(name1, "r");
		if(NULL != f1) {
			puts("������Ŀ���ļ�����");
			get_line(name2, 20);
			if(0 != strcmp(name1, name2)) {
				f2 = fopen(name2, "w");
				while(fgets(str, 20, f1)) {
					fputs(str, f2);
				}
				fclose(f2);
			}
			puts("�ļ�������ɡ�");
		} else {
			printf("�ļ�%s�����ڡ�\n", name1);
		}
	}
	system("pause");
	return 0;
}