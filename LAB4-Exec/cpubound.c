#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main (void){

int i,j;
double variable,temp, result = 0;

	printf("Digite um numero inteiro:\n");
	scanf(" %lf",&variable);

	while(1){
		for(i = 0; i < 65536 ; i++) {
		temp = variable/(M_PI*1000);
		temp = variable *(M_PI*1000);
		for(j=0;j<1024;j++) result = 3;
		result = variable - temp;
		}
		printf("Variable: %lf\n",result);
	}
	
	return 0;
}

