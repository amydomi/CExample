#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

/*
	SQLite 嵌入式简单应用
	从SQLite官方下载C源码，然后导入到项目中来才能使用。
	http://www.sqlite.org/download.html
*/

#define TRUE 1
#define FALSE 0

typedef int bool;

// SQL命令执行后的回调函数，会将查询来的数据带入此函数中处理
// asColName: 字段名	argv: 数据	argc:记录长度
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
	sqlite3 *db;	// 数据库的句柄
	char *zErrorMsg = 0;	//错误信息的指针
	int rc;
	bool flag = TRUE;
	char sql[255];	// SQL字符串
	
	// 先打开数据库，数据库文件不存在会自动创建
	rc = sqlite3_open("data.db", &db);
	if(rc) {
		puts("open database fail.");
		sqlite3_close(db);
		return -1;
	}
	
	// 循环读取命令
	while(flag) {

		puts("Please enter a valid SQL statement:");
		
		// 读取一行命令
		fgets(sql, sizeof(sql), stdin);
		sql[strlen(sql) - 1] = '\0';
		
		// 如果输入的命令是exit，退出程序，退出时使用sqlite3_close关闭数据库
		if(!strcmp("exit", sql)) {
			sqlite3_close(db);
			flag = FALSE;
			break;
		}
		
		// 执行一条SQL命令，callback是执行完成后的回调函数
		rc = sqlite3_exec(db, sql, callback, 0, &zErrorMsg);
		if( rc != SQLITE_OK) {
			printf("SQL error:%s\n", zErrorMsg);
			sqlite3_free(zErrorMsg);	// 使用完错误的字符串需要释放，sqlite内部应该是用动态分配的字符串
		} else {
			puts("Query OK.");
		}
	}

	return 0;
}