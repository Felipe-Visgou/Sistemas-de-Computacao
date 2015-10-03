#include <stdio.h>
#include <math.h>
int main (void)
{
	int i, j, k;
	long int a;
	double b;
	a = pow(2.0,15);
	printf("Ola, eu sou prog4 (cpubound) \n");
	printf("prog4: FAZENDO CONTAS...\n");
	for( i = 0; i < a; i++)	
	{
		b = i/sqrt(i+1);
		for(k = 0; k < a; k++)
			j = 3;
	}
	printf("prog4: Terminei \n");
	return 0;
}
