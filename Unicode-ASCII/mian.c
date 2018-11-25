#include <locale.h>

#include "Student.h"

int main()
{
	setlocale(LC_ALL, "chs");

	Student * s1 = new_student(_T("ÕÅÈı"), 25, 1.85f);
	print_student(s1);
	free_student(s1);
	return 0;
}