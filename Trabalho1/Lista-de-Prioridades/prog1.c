#include <stdio.h>
#include<unistd.h>
int main(void)
{
	printf("prog1: Ola, eu sou prog1 (iobound) \n");
	printf("prog1: ESTOU NUM I/O ... ZzZzZz\n");
	sleep(3);
	printf("prog1: Terminei \n");
	printf("-------------------------------------\n");
	return 0;
}
