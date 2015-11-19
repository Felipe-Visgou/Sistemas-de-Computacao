/* Exercício 4 - LAB 3

Dupla: Fernando Homem da Costa
		Felipe Vieira Côrtes
*/

/* 5) Faça um programa que leia 2 números reais
e imprima o resultado das 4 operações
básicas sobre estes 2 números.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void floatHandler(int sinal);

int main (void){
float num1;
float num2;
float num3;

void (*p)(int);

p = signal(SIGFPE, floatHandler);

printf("Digite o primeiro numero:\n");
scanf("%f",&num1);
printf("Digite o segundo numero:\n");
scanf("%f",&num2);
num3 = num1 + num2;
printf("Num1: %f + Num2: %f = %f\n",num1,num2,num3);
num3 = num1 - num2;
printf("Num1: %f - Num2: %f = %f\n",num1,num2,num3);
num3 = num1 * num2;
printf("Num1: %f * Num2: %f = %f\n",num1,num2,num3);
num3 = num1 / num2;
printf("Num1: %f / Num2: %f = %f\n",num1,num2,num3);

return 0;
}

void floatHandler(int sinal){
printf("SIGFPE capturado. \n");
exit(1);
}

/*Resultado com Float:
Num1: 1.000000 + Num2: 0.000000 = 1.000000
Num1: 1.000000 - Num2: 0.000000 = 1.000000
Num1: 1.000000 * Num2: 0.000000 = 0.000000
Num1: 1.000000 / Num2: 0.000000 = inf


/*Mudando para Int para poder capturar o SIGFPE*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void floatHandler(int sinal);

int main (void){
int num1;
int num2;
int num3;

void (*p)(int);

p = signal(SIGFPE, floatHandler);

printf("Digite o primeiro numero:\n");
scanf("%d",&num1);
printf("Digite o segundo numero:\n");
scanf("%d",&num2);
num3 = num1 + num2;
printf("Num1: %d + Num2: %d = %d\n",num1,num2,num3);
num3 = num1 - num2;
printf("Num1: %d - Num2: %d = %d\n",num1,num2,num3);
num3 = num1 * num2;
printf("Num1: %d * Num2: %d = %d\n",num1,num2,num3);
num3 = num1 / num2;
printf("Num1: %d / Num2: %d = %d\n",num1,num2,num3);

return 0;
}

void floatHandler(int sinal){
printf("SIGFPE capturado. \n");
exit(1);
}

/*Resultado com Int
Num1: 1 + Num2: 0 = 1
Num1: 1 - Num2: 0 = 1
Num1: 1 * Num2: 0 = 0
SIGFPE capturado.*/

/*Conclusão: Podemos observar que quando declaramos as variaveis como pontos fluantes não conseguimos
obter o SIGFPE.Entretanto, quando mudamos para int conseguimos obter o SIGFPE. Assim, podemos ver que int e float são tratados de formas diferentes pelo Hardware.*/


