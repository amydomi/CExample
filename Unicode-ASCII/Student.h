#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string.h>

// ASCII版本
typedef struct tagStudentA
{
	char *name;
	int age;
	float height;
} StudentA;

StudentA * new_studentA(char *, int, float);
void print_studentA(StudentA *);
void free_studentA(StudentA *);

// Unicode版本
typedef struct tagStudentW
{
	wchar_t *name;
	int age;
	float height;
} StudentW;

StudentW * new_studentW(wchar_t *, int, float);
void print_studentW(StudentW *);
void free_studentW(StudentW *);

// 通用版本
#ifdef _UNICODE
#define _T(x)	L##x
#define Student StudentW
#define new_student new_studentW
#define print_student print_studentW
#define free_student free_studentW
#else
#define _T(x)	x
#define Student StudentA
#define new_student new_studentA
#define print_student print_studentA
#define free_student free_studentA
#endif

#endif