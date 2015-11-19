/* Exercício 5 - LAB 3

Dupla: Fernando Homem da Costa
		Felipe Vieira Côrtes
*/

/* 6) Faça um programa para monitorar e informar o
preço de chamadas telefônicas. O programa
deverá ser executado em background.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>


void usr1Handler(int signal);
void usr2Handler(int signal);

int duracao;
int ini;
int fim;

int main (int argc, char *argv[]){

signal(SIGUSR1, usr1Handler);
signal(SIGUSR2, usr2Handler);
for(;;);


return 0;

}

void usr1Handler(int signal){
	ini = time(NULL);
	printf("A chamada comecou..\n");
}

void usr2Handler(int signal){
	int preco;
	fim = time(NULL);
	duracao = fim - ini;
	printf("A chamada terminou com %d segundos\n", duracao);
	if(duracao < 60)
		preco = duracao*2;
	else
		preco = 60*2 + (duracao -60);
	printf("O preco da chamada foi de %d centavos \n", preco);
}

/* Saida do terminal 
ubuntu@ubuntu:~/Documents/LAB3$ ./tel &
[1] 7845
ubuntu@ubuntu:~/Documents/LAB3$ kill -s SIGUSR1 7845
ubuntu@ubuntu:~/Documents/LAB3$ A chamada comecou..

ubuntu@ubuntu:~/Documents/LAB3$ kill -s SIGUSR2 7845
ubuntu@ubuntu:~/Documents/LAB3$ A chamada terminou com 24 segundos
O preco da chamada foi de 48 centavos 

ubuntu@ubuntu:~/Documents/LAB3$ kill -s SIGUSR1 7845
ubuntu@ubuntu:~/Documents/LAB3$ A chamada comecou..

ubuntu@ubuntu:~/Documents/LAB3$ kill -s SIGUSR2 7845
ubuntu@ubuntu:~/Documents/LAB3$ A chamada terminou com 292 segundos
O preco da chamada foi de 352 centavos 

ubuntu@ubuntu:~/Documents/LAB3$ kill 7845
*/
/* Conclusao
 Com o '&' faz o programa rodar em background e faz seu pid aparecer na saida do terminal,
assim basta mandar o sinal de que a chamada comecou (SIGUSR1) e depois mandar o sinal do 
termino da chamada (SIGUSR2). Bem no tratamento do sinal SIGUSR2 faz-se os calculos de quanto
custou a chamada */
