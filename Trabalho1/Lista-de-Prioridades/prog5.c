#include <stdio.h>
#include<unistd.h>
int main(void)
{
	int i, a;
	printf("prog5: Ola, eu sou prog5 \n");
	printf("prog5: Estou num I/O ... ZzZzZz\n");
	sleep(1);
	printf("prog5: I/O TERMINADO \n");
	printf("prog5: Computando... \n");
	for(i = 0; i < 1024; i++) a = 999;
	printf("prog5: TERMINADO \n");
	printf("prog5: Outro I/O \n");
	sleep(1);
	printf("prog5: TERMINADO \n");
	printf("prog5: Terminei \n");
	printf("-------------------------------------\n");
	return 0;
}
