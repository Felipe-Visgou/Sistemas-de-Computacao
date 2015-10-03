#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main (void){

int i,j, k;
double variable,temp, result = 0;

	printf("Ola, eu sou prog2 (cpubound) \n" );
	variable = 7293475.5222;

	for(k = 0; k < 15; k++){
		for(i = 0; i < 65536 ; i++) {
		temp = variable/(M_PI*1000);
		temp = variable *(M_PI*1000);
		for(j=0;j<1024;j++) result = 3;
		result = variable - temp;
		}
		printf("Fazendo contas... Variable: %lf\n",result);
	}
	printf("prog2: Terminei \n" );
	printf("-------------------------------------\n");
	return 0;
}
