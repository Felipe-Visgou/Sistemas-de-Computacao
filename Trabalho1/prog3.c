#include <stdio.h>
#include <math.h>
int main (void)
{
	int i, j, k;
	long int a;
	double b;
	a = pow(2.0,16);
	printf("Ola, eu sou prog3 (cpubound) \n");
	printf("prog3: FAZENDO CONTAS...\n");
	for( i = 0; i < a; i++)	
	{
		b = i/sqrt(i+1);
		for(k = 0; k < a; k++)
			j = 3;
	}
	printf("prog3: Terminei \n");
	return 0;
}
