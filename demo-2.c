#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i, y;
	
	system("mode con cols=150 lines=30");
	
	printf("\t┌─────────────────┐\n");
	printf("\t│                                  │\n");
	printf("\t│            九九乘法表            │\n");
	printf("\t│                                  │\n");
	printf("\t└─────────────────┘\n");
	
	for(i = 1; i <= 9; i++) {
		for(y = 1; y <= i; y++)
			printf("%d × %d = %d\t", y, i, (i * y));
		printf("\n\n");	
	}
	
	system("pause");
	return 0;
}