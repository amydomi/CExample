#include <stdio.h>
#include <stdarg.h>

/*
	C语言里的函数参数和局部变量是从右往左入栈的。
	所以可以根据第一个参数指针进行向前推导得到后面每一个参数的地址，也就是可变参数。
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