#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i, y;
	
	system("mode con cols=150 lines=30");
	
	printf("\t©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´\n");
	printf("\t©¦                                  ©¦\n");
	printf("\t©¦            ¾Å¾Å³Ë·¨±í            ©¦\n");
	printf("\t©¦                                  ©¦\n");
	printf("\t©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼\n");
	
	for(i = 1; i <= 9; i++) {
		for(y = 1; y <= i; y++)
			printf("%d ¡Á %d = %d\t", y, i, (i * y));
		printf("\n\n");	
	}
	
	system("pause");
	return 0;
}