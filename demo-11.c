#include <stdio.h>
#include <stdarg.h>

/*
	C������ĺ��������;ֲ������Ǵ���������ջ�ġ�
	���Կ��Ը��ݵ�һ������ָ�������ǰ�Ƶ��õ�����ÿһ�������ĵ�ַ��Ҳ���ǿɱ������
*/
void arg_func(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	char * a = va_arg(ap, char *);
	char * b = va_arg(ap, char *);
	char * c = va_arg(ap, char *);

	va_end(ap);

	puts(fmt);
	puts(a);
	puts(b);
	puts(c);
}

int main(int argc, char * argv[])
{
	arg_func("Hello", "world", "haha", "test", "zhu");
	return 0;
}