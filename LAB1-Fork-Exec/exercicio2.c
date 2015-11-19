/* LABORATÓRIO INF1019
   Felipe Vieira Côrtes - 1321881	
   Daniel Siles - 1311291
*/
/* 2) Agora, usando a mesma estrutura de processos pai e filho, declare uma 
variável visível ao pai e ao filho, no pai inicialize a variável com1 e imprima seu 
valor antes do fork(). No filho, altere o valor da variável para 5 e imprima o seu 
valor entes do exit(). Agora, no pai, imprima novamente o valor da variável após o 
filho ter alterado a variável - após a waitpid(). Justifique os resultados obtidos. */
#include <stdio.h>
#include <stdlib.h>
static int var;
int main (void)
{
	int status;
	int p;
	var = 1;
	printf("variavel : %d \n", var);
if((p = fork())!=0)
{
	printf(" PID PAI: %d \n", getpid());
	waitpid(-1, &status, 0);
	printf("PID FILHO : %d \n, variavel : %d", p, var);
}
else
{
	var = 5;
	printf(" (else) PID FILHO: %d \n variavel no filho %d \n", getpid(), var);
	exit(0);
}
exit(0);
}
