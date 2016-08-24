#include <stdio.h>
#include <stdlib.h>

//动态内存的分配与释放
int main(int argc, char *argv[]) {
	
	int len, i, *array;
	puts("Please type the array length:");
	scanf("%d", &len);
	array = (int *)calloc(sizeof(int), len);
	for(i = 0; i < len; i++) {
		array[i] = i;
	}
	for(i = 0; i < len; i++) {
		printf("array[%d]=%d\t", i, array[i]);
	}
	free(array);
	return 0;
}
