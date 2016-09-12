#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

/*
	SQLite Ƕ��ʽ��Ӧ��
	��SQLite�ٷ�����CԴ�룬Ȼ���뵽��Ŀ��������ʹ�á�
	http://www.sqlite.org/download.html
*/

#define TRUE 1
#define FALSE 0

typedef int bool;

// SQL����ִ�к�Ļص��������Ὣ��ѯ�������ݴ���˺����д���
// asColName: �ֶ���	argv: ����	argc:��¼����
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	return 0;
}

int main(int argc, char **argv)
{
	sqlite3 *db;	// ���ݿ�ľ��
	char *zErrorMsg = 0;	//������Ϣ��ָ��
	int rc;
	bool flag = TRUE;
	char sql[255];	// SQL�ַ���
	
	// �ȴ����ݿ⣬���ݿ��ļ������ڻ��Զ�����
	rc = sqlite3_open("data.db", &db);
	if(rc) {
		puts("open database fail.");
		sqlite3_close(db);
		return -1;
	}
	
	// ѭ����ȡ����
	while(flag) {

		puts("Please enter a valid SQL statement:");
		
		// ��ȡһ������
		fgets(sql, sizeof(sql), stdin);
		sql[strlen(sql) - 1] = '\0';
		
		// ��������������exit���˳������˳�ʱʹ��sqlite3_close�ر����ݿ�
		if(!strcmp("exit", sql)) {
			sqlite3_close(db);
			flag = FALSE;
			break;
		}
		
		// ִ��һ��SQL���callback��ִ����ɺ�Ļص�����
		rc = sqlite3_exec(db, sql, callback, 0, &zErrorMsg);
		if( rc != SQLITE_OK) {
			printf("SQL error:%s\n", zErrorMsg);
			sqlite3_free(zErrorMsg);	// ʹ���������ַ�����Ҫ�ͷţ�sqlite�ڲ�Ӧ�����ö�̬������ַ���
		} else {
			puts("Query OK.");
		}
	}

	return 0;
}