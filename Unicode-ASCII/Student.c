#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Student.h"

// ASCII版
StudentA * new_studentA(char *name, int age, float height)
{
	StudentA * stu = (StudentA *)malloc(sizeof(StudentA));
	stu->name = _strdup(name);
	stu->age = age;
	stu->height = height;

	return stu;
}

void print_studentA(StudentA *stu)
{
	printf("name is %s, age is %d, height is %.2f\n", stu->name, stu->age, stu->height);
}

void free_studentA(StudentA *stu)
{
	free(stu->name);
	free(stu);
}

// Unicode版本
StudentW * new_studentW(wchar_t *name, int age, float height)
{
	StudentW * stu = (StudentW *)malloc(sizeof(StudentW));
	stu->name = _wcsdup(name);
	stu->age = age;
	stu->height = height;

	return stu;
}

void print_studentW(StudentW *stu)
{
	wprintf(L"name is %s, age is %d, height is %.2f\n", stu->name, stu->age, stu->height);
}

void free_studentW(StudentW *stu)
{
	free(stu->name);
	free(stu);
}